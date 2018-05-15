#pragma once

#include <iostream>
#include <cstring>

#include <sndfile.h>

#define AUDIO_FILE_BUFFER_SAMPLE_COUNT 4*1024

class AudioFileInputStreamer
{
private:
	SNDFILE* file;
	SF_INFO info;
	const char* filename;
	double buffer[AUDIO_FILE_BUFFER_SAMPLE_COUNT];
	int chunkIndex;
	int index;

public:
	AudioFileInputStreamer()
	{
		std::memset(buffer, 0, sizeof(double)*AUDIO_FILE_BUFFER_SAMPLE_COUNT);
		chunkIndex = AUDIO_FILE_BUFFER_SAMPLE_COUNT;
		index = 0;
	}

	~AudioFileInputStreamer()
	{
		if (file) {
			sf_close(file);
		}
	}

	void Open(const char* filename)
	{
		this->filename = filename;
		if (!(file = sf_open(filename, SFM_READ, &info))) {
			std::cerr << "Could not open file." << std::endl;
		}
	}

	double ReadSample()
	{
		double sample = 0.0;

		if (index >= FrameCount()) {
			if (file) {
				sf_close(file);
			}
			if (!(file = sf_open(filename, SFM_READ, &info))) {
				std::cerr << "Could not open file." << std::endl;
			}
			index = 0;
		}
		if (chunkIndex >= AUDIO_FILE_BUFFER_SAMPLE_COUNT) {
			// Read next chunk
			chunkIndex = 0;
			sf_read_double(file, buffer, AUDIO_FILE_BUFFER_SAMPLE_COUNT);
		}
		sample = buffer[chunkIndex];
		chunkIndex += ChannelCount();
		index += ChannelCount();

		return sample;
	}

	inline int SampleRate() const
	{
		return info.samplerate;
	}

	inline int ChannelCount() const
	{
		return info.channels;
	}

	inline long long FrameCount() const
	{
		return info.frames;
	}
};