#pragma once

// http://www.earlevel.com/main/1997/01/19/a-bit-about-reverb/

#include "audio_settings.h"
#include "delay_filter.h"
#include "mixer.h"

// Creates a musically richer sound => chorus effect
class AllPassFilter
{
private:
	DelayFilter delayFilter;
	double gain;
	double output;
public:
	AllPassFilter(double delayMilliseconds = 1000.0, double gain = 0.1)
		: delayFilter(AudioSettings::Properties().SampleRate(), delayMilliseconds),
		gain(gain),
		output(0.0)
	{
	}

	double Filter(double input)
	{
		// Feedforward + feedback comb filter
		// v[i] = x[i] - g*v[i-D]
		// y[i] = g*v[i] + v[i-D] 
		// => y[i] = -g*x[i] + x[i-D] + g*y[i-D]
		const double delayedOutput = delayFilter.Filter(output);
		const double delayedInput = delayFilter.Filter(input);
		output = -gain * input + delayedInput + gain*delayedOutput;
		return output;
	}
};