#pragma once

// Based on:
// https://en.wikipedia.org/wiki/Comb_filter#Feedback_form
// https://www.nireaktor.com/wp-content/uploads/2012/12/pic1.jpg

#include "audio_settings.h"
#include "delay_filter.h"
#include "mixer.h"

// Produces a series of echoes with decreasing volume each time.
class FeedbackCombFilter
{
private:
	DelayFilter delayFilter;
	double output;
	double gain;
public:
	FeedbackCombFilter(double delayMilliseconds = 1000.0, double gain = 0.1)
		: delayFilter(AudioSettings::Properties().SampleRate(), delayMilliseconds),
		gain(gain),
		output(0.0)
	{
	}

	double Filter(double input)
	{
		// output[i] = input[i] + alpha * output[i-D]
		double delayedOutput = delayFilter.Filter(output);
		output = Mixer2(input, delayedOutput, 1.0, gain);
		return output;
	}
};