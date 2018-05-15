#pragma once

#include <vector>

class DelayFilter
{
private:
	std::vector<double> buffer;
	int index;
	int delaySampleCount;

public:
	DelayFilter(int sampleRateHz = 44100, double delayMilliseconds = 1000.0)
	{
		this->index = 0;
		this->delaySampleCount = (int)(delayMilliseconds * sampleRateHz / 1000.0);
		buffer.resize(this->delaySampleCount);
	}

	// Returns a delayed sample and delays the current sample
	double Filter(double input)
	{
		double output = buffer[index];
		buffer[index] = input;
		index = (index + 1) % delaySampleCount;

		return output;
	}
};