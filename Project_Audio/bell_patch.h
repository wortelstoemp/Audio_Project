#pragma once

#include "patch.h"
#include "sine_oscillator.h"

struct BellPatch : public Patch
{
	SineOscillator sineOsc1;
	SineOscillator sineOsc2;
	SineOscillator sineOsc3;

	BellPatch(double volume = 1.0)
	{
		envelopeADSR.attackTime = 0.01;
		envelopeADSR.decayTime = 1.0;
		envelopeADSR.sustainAmplitude = 0.0;
		envelopeADSR.releaseTime = 1.0;
		outputFrequency = 0.0;
		masterVolume = volume;
	}

	double Run(double time)
	{
		// Doubling the frequency is one octave higher
		double result = envelopeADSR.ModulatedAmplitude(time) * 
		(
			1.0 * sineOsc1.Oscillate(outputFrequency * 2.0) +
			0.5 * sineOsc2.Oscillate(outputFrequency * 3.0) +
			0.25 * sineOsc3.Oscillate(outputFrequency * 4.0)
		);

		result *= masterVolume;

		return result;
	}
};