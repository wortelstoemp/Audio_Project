#pragma once

#include <cstdlib>
#include <cmath>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
#include <vector>

#include "audio_io.h"
#include "audio_settings.h"

class Sampler
{
private:
	AudioFileInputStreamer stream;
public:
	Sampler()
	{
	}

	void Open(const char* filename)
	{
		stream.Open(filename);
		AudioSettings::Properties().SampleRate(stream.SampleRate());
	}

	double Sample(double amplitude)
	{
		if (amplitude < 0.001) {
			return 0.0;
		}

		double output = stream.ReadSample();

		return output;
	}
};