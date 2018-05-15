#pragma once

#include <cmath>
#include <atomic>
#include <mutex>
#include <vector>

#include "audio_settings.h"
#include "audio_core.h"
#include "envelope_adsr.h"

class Patch
{
private:
	double frequencyShifter;
public:
	EnvelopeADSR envelopeADSR;
	std::atomic<double> outputFrequency;
	double masterVolume;
	double cNoteBaseFrequency;

	const double root12Of2 = pow(2.0, 1.0 / 12.0);	// 12 notes per octave

	Patch(double volume = 1.0, double cNoteFreq = 261.626)
	{
		// C4 = 261.626 Hz: http://www.sengpielaudio.com/calculator-notenames.htm
		cNoteBaseFrequency = cNoteFreq;
		masterVolume = volume;
		outputFrequency = 0.0;
		frequencyShifter = 0.0;
	}

	virtual double Run(double time) = 0;

	double NoteToFrequency(int index)
	{
		double result = cNoteBaseFrequency * std::pow(root12Of2, index) + frequencyShifter;

		if (result < 0.0) {
			result = 0.0;
			frequencyShifter = 0.0;
		}
		if (result > 20000.0) {
			result = 20000.0;
			frequencyShifter = 0.0;
		}
		
		return result;
	}

	void IncreaseFrequencyShifter(double value = 10.0)
	{
		frequencyShifter += value;
	}

	void DecreaseFrequencyShifter(double value = 10.0)
	{
		frequencyShifter -= value;
	}
};

double PatchRun(Patch* patch, double time)
{
	double result = patch->Run(time);

	return result;
}