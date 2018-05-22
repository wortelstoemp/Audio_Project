#pragma once

#include <cmath>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#include "audio_settings.h"
#include "oscillator.h"

// Generates a sine wave with amplitude in [-1,1]
/*double SineOscillator(double frequency, double phase, double time, LFO lfo = LFO(0.0, 0.0))
{
	double modFreq = lfo.ModulatedFrequency(frequency, time);
	double result = std::sin(2 * M_PI * frequency * time + modFreq + phase);

	return result;
}*/

class SineOscillator : public Oscillator
{
public:
	SineOscillator() : Oscillator()
	{
		FillWavetable();
	}

	void FillWavetable()
	{
		const int sampleCount = wavetable.size();
		for (int i = 0; i < sampleCount; i++) {
			const double time = ((double)i) / ((double)AudioSettings::Properties().SampleRate());

			wavetable[i] = std::sin(2 * M_PI * frequency * time);
		}
	}
};