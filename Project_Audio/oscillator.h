#pragma once

#include <cstdlib>
#include <cmath>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
#include <vector>

#include "audio_settings.h"

#define OSCILLATOR_WAVETABLE_SAMPLE_COUNT 65538

inline double Interpolate(const std::vector<double>& wavetable, double index)
{
	int i = static_cast<int>(index);
	double fractional = index - i;

	double v1 = wavetable[i];
	int j = (i + 1) % wavetable.size();
	double v2 = wavetable[j];
	double result = v1 + (v2 - v1) * fractional;

	return result;
}

class Oscillator
{
protected:
	std::vector<double> wavetable;
	double index;
	double frequency;

public:
	Oscillator()
	{
		const int sampleCount = OSCILLATOR_WAVETABLE_SAMPLE_COUNT;
		this->frequency = ((double)AudioSettings::Properties().SampleRate()) / sampleCount;
		this->wavetable.resize(sampleCount);
		index = 0;
	}

	virtual void FillWavetable() = 0;

	double Oscillate(double desiredFrequency)
	{
		const int sampleCount = wavetable.size();
		const double increment = (sampleCount * desiredFrequency) / AudioSettings::Properties().SampleRate();
		
		index = std::fmod((index + increment), sampleCount);
		double output = Interpolate(wavetable, index);
		
		return output;
	}
};