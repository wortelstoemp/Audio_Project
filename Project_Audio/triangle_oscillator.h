#pragma once

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
#include <cmath>

#include "audio_settings.h"
#include "oscillator.h"
#include "lfo.h"

// Generates a triangle wave with amplitude in [-1,1]
class TriangleOscillator : public Oscillator
{
public:
	TriangleOscillator() : Oscillator()
	{
		FillWavetable();
	}

	void FillWavetable()
	{
		const int sampleCount = wavetable.size();
		for (int i = 0; i < sampleCount; i++) {
			const double time = ((double)i) / ((double)AudioSettings::Properties().SampleRate());

			wavetable[i] = (2.0 / M_PI) * std::asin(std::sin(2.0 * M_PI * frequency * time));
		}
	}
};