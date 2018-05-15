#pragma once

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
#include <cmath>

#include "audio_settings.h"
#include "oscillator.h"

// Generates a sawtooth wave with amplitude in [-1,1]
class SawOscillator : public Oscillator
{
public:
	SawOscillator() : Oscillator()
	{
		FillWavetable();
	}

	void FillWavetable()
	{
		const int sampleCount = wavetable.size();
		for (int i = 0; i < sampleCount; i++) {
			const double time = ((double)i) / ((double)AudioSettings::Properties().SampleRate());

			wavetable[i] = (2.0 / M_PI) * (frequency * M_PI * std::fmod(time, 1.0 / frequency) - (M_PI / 2.0));
		}
	}
};