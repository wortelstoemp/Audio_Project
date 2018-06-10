#pragma once

#include <iostream>

#include "patch.h"

#include "sine_oscillator.h"
#include "square_oscillator.h"
#include "saw_oscillator.h"
#include "triangle_oscillator.h"
#include "noise_oscillator.h"

#include "lfo.h"
#include "feedforward_comb_filter.h"
#include "feedback_comb_filter.h"
#include "allpass_filter.h"
#include "iir_filter.h"
#include "highpass_filter.h"
#include "lowpass_filter.h"
#include "delay_filter.h"
#include "reverb_filter.h"
#include "sampler.h"
#include "mixer.h"

// Example 01: "1: Sine oscillator"
class Example01Patch : public Patch
{
private:
	SineOscillator sineOsc;

public:
	Example01Patch(double volume = 1.0)
		: Patch(volume)
	{
		envelopeADSR.attackTime = 0.01;
		envelopeADSR.decayTime = 0.0;
		envelopeADSR.sustainAmplitude = 1.0;
		envelopeADSR.releaseTime = 0.1;
		outputFrequency = 0.0;
		masterVolume = volume;
	}

	double Run(double time)
	{
		double modulatedAmplitude = envelopeADSR.ModulatedAmplitude(time);
		double result = modulatedAmplitude * sineOsc.Oscillate(outputFrequency);

		result *= masterVolume;

		return result;
	}
};

// Example 02: "2: Square oscillator"
class Example02Patch : public Patch
{
private:
	SquareOscillator squareOsc;

public:
	Example02Patch(double volume = 1.0)
		: Patch(volume)
	{
		envelopeADSR.attackTime = 0.01;
		envelopeADSR.decayTime = 0.0;
		envelopeADSR.sustainAmplitude = 1.0;
		envelopeADSR.releaseTime = 0.1;
		outputFrequency = 0.0;
		masterVolume = volume;
	}

	double Run(double time)
	{
		double modulatedAmplitude = envelopeADSR.ModulatedAmplitude(time);
		double result = modulatedAmplitude * squareOsc.Oscillate(outputFrequency);

		result *= masterVolume;

		return result;
	}
};

// Example 03: "3: Saw oscillator"
class Example03Patch : public Patch
{
private:
	SawOscillator sawOsc;

public:
	Example03Patch(double volume = 1.0)
		: Patch(volume)
	{
		envelopeADSR.attackTime = 0.01;
		envelopeADSR.decayTime = 0.0;
		envelopeADSR.sustainAmplitude = 1.0;
		envelopeADSR.releaseTime = 0.1;
		outputFrequency = 0.0;
		masterVolume = volume;
	}

	double Run(double time)
	{
		double modulatedAmplitude = envelopeADSR.ModulatedAmplitude(time);
		double result = modulatedAmplitude * sawOsc.Oscillate(outputFrequency);

		result *= masterVolume;

		return result;
	}
};

// Example 04: "4: Triangle oscillator"
class Example04Patch : public Patch
{
private:
	TriangleOscillator triangleOsc;

public:
	Example04Patch(double volume = 1.0)
		: Patch(volume)
	{
		envelopeADSR.attackTime = 0.01;
		envelopeADSR.decayTime = 0.0;
		envelopeADSR.sustainAmplitude = 1.0;
		envelopeADSR.releaseTime = 0.1;
		outputFrequency = 0.0;
		masterVolume = volume;
	}

	double Run(double time)
	{
		double modulatedAmplitude = envelopeADSR.ModulatedAmplitude(time);
		double result = modulatedAmplitude * triangleOsc.Oscillate(outputFrequency);

		result *= masterVolume;

		return result;
	}
};

// Example 05: "5: Noise oscillator"
class Example05Patch : public Patch
{
private:
	NoiseOscillator noiseOsc;

public:
	Example05Patch(double volume = 1.0)
		: Patch(volume)
	{
		envelopeADSR.attackTime = 0.01;
		envelopeADSR.decayTime = 0.0;
		envelopeADSR.sustainAmplitude = 1.0;
		envelopeADSR.releaseTime = 0.1;
		outputFrequency = 0.0;
		masterVolume = volume;
	}

	double Run(double time)
	{
		double modulatedAmplitude = envelopeADSR.ModulatedAmplitude(time);
		double result = modulatedAmplitude * noiseOsc.Oscillate(outputFrequency);

		result *= masterVolume;

		return result;
	}
};

// Example 06: "6: ADSR Envelope"
class Example06Patch : public Patch
{
private:
	SawOscillator sawOsc;

public:
	Example06Patch(double volume = 1.0)
		: Patch(volume)
	{
		envelopeADSR.attackTime = 1.0;
		envelopeADSR.decayTime = 1.0;
		envelopeADSR.sustainAmplitude = 0.3;
		envelopeADSR.releaseTime = 1.0;
		outputFrequency = 0.0;
		masterVolume = volume;
	}

	double Run(double time)
	{
		double modulatedAmplitude = envelopeADSR.ModulatedAmplitude(time);
		double result = modulatedAmplitude * sawOsc.Oscillate(outputFrequency);

		result *= masterVolume;

		return result;
	}
};

// Example 07: "7: Delay Line"
class Example07Patch : public Patch
{
private:
	SawOscillator sawOsc;
	DelayFilter delay;

public:
	Example07Patch(double volume = 1.0)
		: Patch(volume),
		delay(AudioSettings::Properties().SampleRate(), 1000.0)
	{
		envelopeADSR.attackTime = 0.01;
		envelopeADSR.decayTime = 0.0;
		envelopeADSR.sustainAmplitude = 1.0;
		envelopeADSR.releaseTime = 0.1;
		outputFrequency = 0.0;
		masterVolume = volume;
	}

	double Run(double time)
	{
		double modulatedAmplitude = envelopeADSR.ModulatedAmplitude(time);
		double result = modulatedAmplitude * sawOsc.Oscillate(outputFrequency);

		result = delay.Filter(result);

		result *= masterVolume;

		return result;
	}
};

// Example 08: "8: Feedforward Comb Filter"
class Example08Patch : public Patch
{
private:
	SawOscillator sawOsc;
	FeedforwardCombFilter ffcf;

public:
	Example08Patch(double volume = 1.0)
		: Patch(volume),
		ffcf(500.0, 0.4)
	{
		envelopeADSR.attackTime = 0.01;
		envelopeADSR.decayTime = 0.0;
		envelopeADSR.sustainAmplitude = 1.0;
		envelopeADSR.releaseTime = 0.1;
		outputFrequency = 0.0;
		masterVolume = volume;
	}

	double Run(double time)
	{
		double modulatedAmplitude = envelopeADSR.ModulatedAmplitude(time);
		double result = modulatedAmplitude * sawOsc.Oscillate(outputFrequency);

		result = ffcf.Filter(result);

		result *= masterVolume;

		return result;
	}
};

// Example 09: "9: Feedback Comb Filter"
class Example09Patch : public Patch
{
private:
	SineOscillator sineOsc;
	FeedbackCombFilter fbcf;

public:
	Example09Patch(double volume = 1.0)
		: Patch(volume),
		fbcf(500.0, 0.4)
	{
		envelopeADSR.attackTime = 0.01;
		envelopeADSR.decayTime = 0.0;
		envelopeADSR.sustainAmplitude = 1.0;
		envelopeADSR.releaseTime = 0.1;
		outputFrequency = 0.0;
		masterVolume = volume;
	}

	double Run(double time)
	{
		double modulatedAmplitude = envelopeADSR.ModulatedAmplitude(time);
		double result = modulatedAmplitude * sineOsc.Oscillate(outputFrequency);

		result = fbcf.Filter(result);

		result *= masterVolume;

		return result;
	}
};

// Example 10: "10: Sampler"
class Example10Patch : public Patch
{
private:
	Sampler sampler;
	FeedbackCombFilter fbcf;

public:
	Example10Patch(double volume = 1.0)
		: Patch(volume),
		fbcf(500.0, 0.4)
	{
		envelopeADSR.attackTime = 1.0;
		envelopeADSR.decayTime = 1.0;
		envelopeADSR.sustainAmplitude = 0.3;
		envelopeADSR.releaseTime = 1.0;
		outputFrequency = 0.0;
		masterVolume = volume;

		std::string filename;
		std::string path = ".\\Data\\";
		std::cout << "Enter filename (reads after Data\\): ";
		std::cin >> filename;
		sampler.Open((path + filename).c_str());
	}

	double Run(double time)
	{
		double modulatedAmplitude = envelopeADSR.ModulatedAmplitude(time);
		double result = sampler.Sample(modulatedAmplitude);
		result = fbcf.Filter(result);

		result *= masterVolume;

		return result;
	}
};

// Example 11: "11: Mixer3"
class Example11Patch : public Patch
{
private:
	SquareOscillator squareOsc1;
	SquareOscillator squareOsc2;
	NoiseOscillator noiseOsc;

public:
	Example11Patch(double volume = 1.0)
		: Patch(volume)
	{
		envelopeADSR.attackTime = 0.05;
		envelopeADSR.decayTime = 1.0;
		envelopeADSR.sustainAmplitude = 0.95;
		envelopeADSR.releaseTime = 0.1;
		outputFrequency = 0.0;
		masterVolume = volume;
	}

	double Run(double time)
	{
		double modulatedAmplitude = envelopeADSR.ModulatedAmplitude(time);
		double square1 = squareOsc1.Oscillate(outputFrequency);
		double square2 = squareOsc2.Oscillate(3*outputFrequency);
		double noise = noiseOsc.Oscillate(outputFrequency);
		double result = modulatedAmplitude * Mixer3(square1, square2, noise, 1.0, 0.5, 0.25);

		result *= masterVolume;

		return result;
	}
};

// Example 12: "12: IIR Filter"
class Example12Patch : public Patch
{
private:
	SawOscillator sawOsc;
	IIRFilter iir;

public:
	Example12Patch(double volume = 1.0)
		: Patch(volume),
		iir(0.001)
	{
		envelopeADSR.attackTime = 0.01;
		envelopeADSR.decayTime = 0.0;
		envelopeADSR.sustainAmplitude = 1.0;
		envelopeADSR.releaseTime = 0.1;
		outputFrequency = 0.0;
		masterVolume = volume;
	}

	double Run(double time)
	{
		double modulatedAmplitude = envelopeADSR.ModulatedAmplitude(time);
		double result = modulatedAmplitude * sawOsc.Oscillate(outputFrequency);
		result = iir.Filter(result);

		result *= 1.25 * masterVolume;

		return result;
	}
};

// Example 13: "13: All-pass Filter"
class Example13Patch : public Patch
{
private:
	SineOscillator sineOsc;
	AllPassFilter allpass;

public:
	Example13Patch(double volume = 1.0)
		: Patch(volume),
		allpass(50.0, 0.7)
	{
		envelopeADSR.attackTime = 0.01;
		envelopeADSR.decayTime = 0.0;
		envelopeADSR.sustainAmplitude = 1.0;
		envelopeADSR.releaseTime = 0.1;
		outputFrequency = 0.0;
		masterVolume = volume;
	}

	double Run(double time)
	{
		double modulatedAmplitude = envelopeADSR.ModulatedAmplitude(time);
		double result = modulatedAmplitude * sineOsc.Oscillate(outputFrequency);
		result = allpass.Filter(result);

		result *= masterVolume;

		return result;
	}
};

// Example 14: "14: Low-pass Filter"
class Example14Patch : public Patch
{
private:
	NoiseOscillator noiseOsc;
	LowPassFilter lpf;

public:
	Example14Patch(double volume = 1.0)
		: Patch(volume),
		lpf(0.001)
	{
		envelopeADSR.attackTime = 0.01;
		envelopeADSR.decayTime = 0.0;
		envelopeADSR.sustainAmplitude = 1.0;
		envelopeADSR.releaseTime = 0.1;
		outputFrequency = 0.0;
		masterVolume = volume;
	}

	double Run(double time)
	{
		double modulatedAmplitude = envelopeADSR.ModulatedAmplitude(time);
		double result = modulatedAmplitude * noiseOsc.Oscillate(outputFrequency);
		result = lpf.Filter(result);

		result *= masterVolume;

		return result;
	}
};

// Example 15: "15: High-pass Filter"
class Example15Patch : public Patch
{
private:
	NoiseOscillator noiseOsc;
	HighPassFilter hpf;

public:
	Example15Patch(double volume = 1.0)
		: Patch(volume),
		hpf(0.001)
	{
		envelopeADSR.attackTime = 0.01;
		envelopeADSR.decayTime = 0.0;
		envelopeADSR.sustainAmplitude = 1.0;
		envelopeADSR.releaseTime = 0.1;
		outputFrequency = 0.0;
		masterVolume = volume;
	}

	double Run(double time)
	{
		double modulatedAmplitude = envelopeADSR.ModulatedAmplitude(time);
		double result = modulatedAmplitude * noiseOsc.Oscillate(outputFrequency);
		result = hpf.Filter(result);
		result *= masterVolume;

		return result;
	}
};

// Example 16: "16: Low Frequency Oscillator (LFO)"
class Example16Patch : public Patch
{
private:
	SineRealTimeOscillator sineOsc;

public:
	Example16Patch(double volume = 1.0)
		: Patch(volume)
	{
		envelopeADSR.attackTime = 0.01;
		envelopeADSR.decayTime = 0.0;
		envelopeADSR.sustainAmplitude = 1.0;
		envelopeADSR.releaseTime = 0.1;
		outputFrequency = 0.0;
		masterVolume = volume;
	}

	double Run(double time)
	{
		double modulatedAmplitude = envelopeADSR.ModulatedAmplitude(time);
		double result = modulatedAmplitude * sineOsc.Oscillate(time, outputFrequency, 0.0, LFO(0.02, 5.0));

		result *= masterVolume;

		return result;
	}
};

// Example 17: "17: Reverb Filter (3 serial AP's + 4 FBCF's)"
class Example17Patch : public Patch
{
private:
	SineOscillator sineOsc;
	Reverberator reverb;

public:
	Example17Patch(double volume = 1.0)
		: Patch(volume)
	{
		envelopeADSR.attackTime = 0.01;
		envelopeADSR.decayTime = 0.0;
		envelopeADSR.sustainAmplitude = 1.0;
		envelopeADSR.releaseTime = 0.1;
		outputFrequency = 0.0;
		masterVolume = volume;
	}

	double Run(double time)
	{
		double modulatedAmplitude = envelopeADSR.ModulatedAmplitude(time);
		double result = modulatedAmplitude * sineOsc.Oscillate(outputFrequency);
		result = reverb.Filter(result);

		result *= masterVolume;

		return result;
	}
};

// Example 18: "18: Reverb Filter (3 serial AP's + 4 parallel FFCF's)"
class Example18Patch : public Patch
{
private:
	SineOscillator sineOsc;
	ReverberatorJCREV reverb;

public:
	Example18Patch(double volume = 1.0)
		: Patch(volume)
	{
		envelopeADSR.attackTime = 0.01;
		envelopeADSR.decayTime = 0.0;
		envelopeADSR.sustainAmplitude = 1.0;
		envelopeADSR.releaseTime = 0.1;
		outputFrequency = 0.0;
		masterVolume = volume;
	}

	double Run(double time)
	{
		double modulatedAmplitude = envelopeADSR.ModulatedAmplitude(time);
		double result = modulatedAmplitude * sineOsc.Oscillate(outputFrequency);
		result = reverb.Filter(result);

		result *= masterVolume;

		return result;
	}
};

static const int PATCH_EXAMPLE_COUNT = 18;
static const char* PATCH_EXAMPLES[PATCH_EXAMPLE_COUNT] = {
	"1: Sine Oscillator [DEFAULT]",
	"2: Square Oscillator",
	"3: Saw Oscillator",
	"4: Triangle Oscillator",
	"5: Noise Oscillator",
	"6: ADSR Envelope",
	"7: Delay Line",
	"8: Feedforward Comb Filter",
	"9: Feedback Comb Filter",
	"10: Sampler",
	"11: Mixer3",
	"12: IIR Filter",
	"13: All-pass Filter",
	"14: Low-pass Filter",
	"15: High-pass Filter",
	"16: Low Frequency Oscillator (LFO)",
	"17: Reverb Filter (3 serial AP's + 4 parallel FBCF's)",
	"18: Reverb Filter (3 serial AP's + 4 parallel FFCF's)"
};

// This function allocates memory for the example patch.
// Use the corresponding function DeleteExamplePatch to cleanup memory !!!
Patch* SelectAndAllocateExamplePatch()
{
	std::cout << "Patches:" << std::endl;
	for (int i = 0; i < PATCH_EXAMPLE_COUNT; i++) {
		std::cout << "\t" << PATCH_EXAMPLES[i] << std::endl;
	}

	int patchNumber = 1;
	std::cout << std::endl << "Enter one of the patch numbers: ";
	std::cin >> patchNumber;
	if (patchNumber < 1 || patchNumber > PATCH_EXAMPLE_COUNT) {
		patchNumber = 1;
	}
	const int patchIndex = patchNumber - 1;
	std::cout << "Selected patch '" << PATCH_EXAMPLES[patchIndex] << "'." << std::endl;

	Patch* patch = nullptr;

	switch (patchNumber) {
		case 1: {
			patch = new Example01Patch(0.4);
		} break;
		case 2: {
			patch = new Example02Patch(0.5);
		} break;
		case 3: {
			patch = new Example03Patch(0.5);
		} break;
		case 4: {
			patch = new Example04Patch(0.5);
		} break;
		case 5: {
			patch = new Example05Patch(0.5);
		} break;
		case 6: {
			patch = new Example06Patch(0.5);
		} break;
		case 7: {
			patch = new Example07Patch(0.5);
		} break;
		case 8: {
			patch = new Example08Patch(0.5);
		} break;
		case 9: {
			patch = new Example09Patch(0.5);
		} break;
		case 10: {
			patch = new Example10Patch(0.5);
		} break;
		case 11: {
			patch = new Example11Patch(0.5);
		} break;
		case 12: {
			patch = new Example12Patch(0.5);
		} break;
		case 13: {
			patch = new Example13Patch(0.5);
		} break;
		case 14: {
			patch = new Example14Patch(0.5);
		} break;
		case 15: {
			patch = new Example15Patch(0.8);
		} break;
		case 16: {
			patch = new Example16Patch(0.5);
		} break;
		case 17: {
			patch = new Example17Patch(0.5);
		} break;
		case 18: {
			patch = new Example18Patch(0.5);
		} break;
		default: {
			patch = new Example01Patch(0.5);
		} break;
	}

	return patch;
}

void DeleteExamplePatch(Patch* patch)
{
	delete patch;
}