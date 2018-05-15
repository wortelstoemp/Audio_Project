#pragma once

// Based on:
// https://en.wikipedia.org/wiki/Comb_filter#Feedforward_form
// https://www.nireaktor.com/wp-content/uploads/2012/12/pic1.jpg
// https://ccrma.stanford.edu/~jos/pasp/Feedforward_Comb_Filters.html

#include "audio_settings.h"
#include "delay_filter.h"
#include "mixer.h"

// Produces one echo.
class FeedforwardCombFilter
{
private:
	DelayFilter delayFilter;
	double gain;
public:
	FeedforwardCombFilter(double delayMilliseconds = 1000.0, double gain = 0.1)
		: delayFilter(AudioSettings::Properties().SampleRate(), delayMilliseconds),
		gain(gain)
	{
	}

	double Filter(double input)
	{
		// output[i] = input[i] + gain * input[i-D]
		double delayedInput = delayFilter.Filter(input);
		double output = Mixer2(input, delayedInput, 1.0, gain);
		return output;
	}
};