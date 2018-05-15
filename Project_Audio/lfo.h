#pragma once

#include <cmath>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// LFO: Low Frequency Oscillator
// Use this unit to modulate the frequency.
// Adds vibrato to the sound wave.
struct LFO
{
	double amplitude;
	double frequency;

	LFO()
	{
		amplitude = 0.0;
		frequency = 0.0;
	}

	LFO(double amplitude, double frequency)
	{
		this->amplitude = amplitude;
		this->frequency = frequency;
	}

	double ModulatedFrequency(double frequency, double time)
	{
		double modFreq = this->amplitude * frequency * (std::sin(2 * M_PI * this->frequency * time));

		return modFreq;
	}
};
