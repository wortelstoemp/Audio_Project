// Based on: 
// - Handmade Hero Audio Platform Layer by Casey Muratori
// - OneLoneCoder's Audio Platform Layer

// Author (adaptations): Tom Quareme

// Currently only Microsoft Windows is supported.
// In the future we might use Handmade Penguin tutorials to
// create a platform layer in SDL2 in order to support
// Microsoft Windows, Linux and macOS together.

#pragma once

#pragma comment(lib, "winmm.lib")

#include <cmath>
#include <cstdint>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <atomic>
#include <condition_variable>
#include <thread>

#include <Windows.h>

#include "patch.h"

static double AudioCoreClip(double sampleValue, double maximumValue)
{
	if (sampleValue >= 0.0) {
		return std::fmin(sampleValue, maximumValue);
	} 
	
	return std::fmax(sampleValue, -maximumValue);
}

template<class T>
class AudioCore;

typedef std::wstring AudioDevice;
typedef AudioCore<int8_t> AudioCore8Bit;
typedef AudioCore<int16_t> AudioCore16Bit;
typedef AudioCore<int32_t> AudioCore32Bit;
typedef AudioCore<int64_t> AudioCore64Bit;

template<class T>
class AudioCore
{
private:
	Patch* patch = nullptr;
	double(*patchFunction)(Patch*, double);

	unsigned int sampleRate;
	unsigned int channelCount;
	unsigned int blockCount;
	unsigned int blockSampleCount;
	unsigned int currentBlock;

	T* blockMemory;
	WAVEHDR* waveHeaders;
	HWAVEOUT outputDevice;

	std::thread audioThread;
	std::atomic<bool> initialized;
	std::atomic<unsigned int> freeBlockCount;
	std::condition_variable conditionalBlockNotZero;
	std::mutex mutexBlockNotZero;
	std::atomic<double> totalTime;

	bool Create(AudioDevice audioDevice, unsigned int sampleRate = 44100, unsigned int channelCount = 1, unsigned int blockCount = 8, unsigned int blockSampleCount = 512)
	{
		this->initialized = false;
		this->sampleRate = sampleRate;
		this->channelCount = channelCount;
		this->blockCount = blockCount;
		this->blockSampleCount = blockSampleCount;
		this->freeBlockCount = this->blockCount;
		this->currentBlock = 0;
		this->blockMemory = nullptr;
		this->waveHeaders = nullptr;
		this->patchFunction = nullptr;

		std::vector<AudioDevice> devices = EnumerateDevices();
		const auto device = std::find(devices.begin(), devices.end(), audioDevice);

		// When there is an audio device
		if (device != devices.end()) {
			const int deviceID = distance(devices.begin(), device);
			WAVEFORMATEX waveFormat;
			{
				waveFormat.wFormatTag = WAVE_FORMAT_PCM;
				waveFormat.nSamplesPerSec = this->sampleRate;
				waveFormat.wBitsPerSample = sizeof(T) * 8;
				waveFormat.nChannels = this->channelCount;
				waveFormat.nBlockAlign = (waveFormat.wBitsPerSample / 8) * waveFormat.nChannels;
				waveFormat.nAvgBytesPerSec = waveFormat.nSamplesPerSec * waveFormat.nBlockAlign;
				waveFormat.cbSize = 0;
			}

			// Try to open the audio device
			if (waveOutOpen(&this->outputDevice, deviceID, &waveFormat, (DWORD_PTR)waveOutProcWrap, (DWORD_PTR)this, CALLBACK_FUNCTION) != S_OK) {
				return Destroy();
			}
		}

		// Memory allocations of block memory and wave headers
		this->blockMemory = new T[this->blockCount * this->blockSampleCount];
		if (!this->blockMemory) {
			return Destroy();
		}
		ZeroMemory(this->blockMemory, sizeof(T) * this->blockCount * this->blockSampleCount);

		this->waveHeaders = new WAVEHDR[this->blockCount];
		if (!this->waveHeaders) {
			return Destroy();
		}
		ZeroMemory(this->waveHeaders, sizeof(WAVEHDR) * this->blockCount);

		// Couple the wave headers and block memory
		for (unsigned int i = 0; i < this->blockCount; i++) {
			this->waveHeaders[i].dwBufferLength = this->blockSampleCount * sizeof(T);
			this->waveHeaders[i].lpData = (LPSTR)(this->blockMemory + (i * this->blockSampleCount));
		}
		this->initialized = true;

		// Create and start audio thread
		this->audioThread = std::thread(&AudioCore::AudioThread, this);
		std::unique_lock<std::mutex> lock(this->mutexBlockNotZero);
		this->conditionalBlockNotZero.notify_one();

		return true;
	}

	bool Destroy()
	{
		return false;
	}

public:
	AudioCore(AudioDevice audioDevice, unsigned int sampleRate = 44100, unsigned int channelCount = 1, unsigned int blockCount = 8, unsigned int blockSampleCount = 512)
	{
		Create(audioDevice, sampleRate, channelCount, blockCount, blockSampleCount);
	}

	~AudioCore()
	{
		Destroy();
	}

	void Stop()
	{
		this->initialized = false;
		this->audioThread.join();
	}

	virtual double UserProcess(double time)
	{
		return 0.0;
	}

	double Time()
	{
		return this->totalTime;
	}

	static std::vector<AudioDevice> EnumerateDevices()
	{
		const int deviceCount = waveOutGetNumDevs();
		std::vector<AudioDevice> devices;
		WAVEOUTCAPS waveOutCaps;
		for (int i = 0; i < deviceCount; i++)
			if (waveOutGetDevCaps(i, &waveOutCaps, sizeof(WAVEOUTCAPS)) == S_OK) {
				devices.push_back(waveOutCaps.szPname);
			}

		return devices;
	}

	void SetPatch(Patch* p)
	{
		this->patch = p;
		this->patchFunction = PatchRun;
	}

private:
	// When sound card sends requests to fill its blocks
	void waveOutProc(HWAVEOUT hWaveOut, UINT uMsg, DWORD dwParam1, DWORD dwParam2)
	{
		if (uMsg != WOM_DONE) { 
			return; 
		}

		this->freeBlockCount++;
		std::unique_lock<std::mutex> lock(mutexBlockNotZero);
		conditionalBlockNotZero.notify_one();
	}

	// Static wrapper for sound card handler
	static void CALLBACK waveOutProcWrap(HWAVEOUT hWaveOut, UINT uMsg, DWORD dwInstance, DWORD dwParam1, DWORD dwParam2)
	{
		((AudioCore*)dwInstance)->waveOutProc(hWaveOut, uMsg, dwParam1, dwParam2);
	}

	// In this thread we provide a loop where the sound card will send requests to us.
	// When such a request happens we will fill memory blocks of the sound card with audio samples.
	void AudioThread()
	{
		this->totalTime = 0.0;
		double deltaTime = 1.0 / (double)sampleRate;

		// Maximum integer for a specific datatype T
		T maxInteger = (T)pow(2, (sizeof(T) * 8) - 1) - 1;
		double maxSample = (double)maxInteger;
		T previousSample = 0;

		while (initialized) {
			// Wait for available block
			if (this->freeBlockCount == 0) {
				std::unique_lock<std::mutex> lock(mutexBlockNotZero);
				conditionalBlockNotZero.wait(lock);
			}

			// Prepare block for processing
			this->freeBlockCount--;
			if (this->waveHeaders[this->currentBlock].dwFlags & WHDR_PREPARED) {
				waveOutUnprepareHeader(this->outputDevice, &this->waveHeaders[this->currentBlock], sizeof(WAVEHDR));
			}

			T newSample = 0;
			int currentBlock = this->currentBlock * this->blockSampleCount;

			for (unsigned int i = 0; i < this->blockSampleCount; i++) {
				if (!this->patchFunction) {
					newSample = (T)(AudioCoreClip(UserProcess(this->totalTime), 1.0) * maxSample);
				} else {
					newSample = (T)(AudioCoreClip(this->patchFunction(patch, this->totalTime), 1.0) * maxSample);
				}

				this->blockMemory[currentBlock + i] = newSample;
				previousSample = newSample;
				this->totalTime = this->totalTime + deltaTime;
			}

			// Send block to sound device
			waveOutPrepareHeader(this->outputDevice, &this->waveHeaders[this->currentBlock], sizeof(WAVEHDR));
			waveOutWrite(this->outputDevice, &this->waveHeaders[this->currentBlock], sizeof(WAVEHDR));
			this->currentBlock++;
			this->currentBlock %= this->blockCount;
		}
	}
};