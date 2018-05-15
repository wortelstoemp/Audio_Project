#pragma once

#include <cmath>
#include <vector>

#include "audio_settings.h"

// Exponential Time Averaging filters are low-pass filters, with roll-off -6dB/oct. 
// The only free parameter is the cut-off frequency, specified by the time constant. 
// Higher time constants yield a lower cut-off frequency.
class IIRFilter
{
private:
	double previousOutput;
	double alpha;

public:
	IIRFilter(double timeConstant = 0.001)
	{
		previousOutput = 0.0;
		alpha = std::exp(-1.0 / (AudioSettings::Properties().SampleRate() * timeConstant));
	}

	double Filter(double input)
	{
		// y[n] = (1-alpha)*x[n] + alpha*y[n-1]
		// In the book we use alpha = 0.5,
		// but here we can adjust alpha via a time constant
		double output = alpha*previousOutput + (1.0-alpha)*input;
		previousOutput = output;

		return output;
	}
};