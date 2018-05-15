#pragma once

#include <cstdlib>

#include "audio_settings.h"
#include "oscillator.h"

// Generates random white noise with amplitude in [-1,1]
class NoiseOscillator : public Oscillator
{
public:
	NoiseOscillator() : Oscillator()
	{
		FillWavetable();
	}

	void FillWavetable()
	{
		const int sampleCount = wavetable.size();
		for (int i = 0; i < sampleCount; i++) {
			// This is deterministic noise, but sounds enough like noise
			// and is the same every time.
			wavetable[i] = 2.0 * (rand() / (double)RAND_MAX) - 1.0;
		}
	}
};