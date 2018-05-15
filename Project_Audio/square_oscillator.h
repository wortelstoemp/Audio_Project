#pragma once

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
#include <cmath>

#include "audio_settings.h"
#include "oscillator.h"
#include "lfo.h"

// Generates a square wave with amplitude in [-1,1]
class SquareOscillator : public Oscillator
{
public:
	SquareOscillator() : Oscillator()
	{
		FillWavetable();
	}

	void FillWavetable()
	{
		const int sampleCount = wavetable.size();
		for (int i = 0; i < sampleCount; i++) {
			const double time = ((double)i) / ((double)AudioSettings::Properties().SampleRate());

			const double v = std::sin(2 * M_PI * frequency * time);
			wavetable[i] = (v > 0.0) ? 1.0 : -1.0;
		}
	}
};