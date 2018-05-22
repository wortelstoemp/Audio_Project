#pragma once

#include <cmath>
#include <vector>

#include "audio_settings.h"

// High-pass filter implementation based on IIR
class HighPassFilter
{
private:
	double previousOutput;
	double alpha;

public:
	HighPassFilter(double timeConstant = 0.001)
	{
		previousOutput = 0.0;
		alpha = std::exp(-1.0 / (AudioSettings::Properties().SampleRate() * timeConstant));
	}

	double Filter(double input)
	{
		// y[n] = (1-alpha)*x[n] + alpha*y[n-1]
		// In the book we use alpha = 0.5,
		// but here we can adjust alpha via a time constant
		double output = (1.0 - alpha)*input - alpha*previousOutput;
		previousOutput = output;

		return output;
	}
};