#pragma once

#include "patch.h"
#include "sine_oscillator.h"
#include "square_oscillator.h"
#include "noise_oscillator.h"

#include "feedforward_comb_filter.h"
#include "feedback_comb_filter.h"
#include "allpass_filter.h"
#include "iir_filter.h"
#include "delay_filter.h"
#include "reverb_filter.h"
#include "sampler.h"

struct HarmonicaPatch : public Patch
{
	SineOscillator sineOsc;
	SquareOscillator squareOsc1;
	SquareOscillator squareOsc2;
	NoiseOscillator noiseOsc1;
	DelayFilter delayFilter;
	AllPassFilter allpassFilter;
	IIRFilter iirFilter;
	FeedforwardCombFilter ffcFilter;
	FeedbackCombFilter fbFilter;
	Sampler sampler;
	ReverberatorJCREV reverb;

	HarmonicaPatch(double volume = 1.0)
		: Patch(volume),
		delayFilter(500.0),
		iirFilter(0.0000300565),
		ffcFilter(500.0, 0.2),
		fbFilter(500.0, 0.2),
		allpassFilter(500.0, 0.7)
	{
		envelopeADSR.attackTime = 0.05;
		envelopeADSR.decayTime = 1.0;
		envelopeADSR.sustainAmplitude = 0.95;
		envelopeADSR.releaseTime = 0.1;
		outputFrequency = 0.0;
		masterVolume = volume;

		//sampler.Open("D:\\Projects\\Audio\\Project_Audio\\Project_Audio\\Data\\babe.wav");
	}

	double Run(double time)
	{
		// Doubling the frequency is one octave higher
		double modulatedAmplitude = envelopeADSR.ModulatedAmplitude(time);
		double result = modulatedAmplitude *
		(
			1.0 * squareOsc1.Oscillate(outputFrequency * 1.0) + // LFO(0.001, 5.0)
			0.5 * squareOsc2.Oscillate(outputFrequency * 3.0) +
			0.25 * noiseOsc1.Oscillate(outputFrequency)
		);

		// Sine wave
		result = modulatedAmplitude * sineOsc.Oscillate(outputFrequency);
		
		// Sampler
		//result =  modulatedAmplitude * sampler.Sample(modulatedAmplitude);
		
		// Filter testing
		//result = delayFilter.Filter(result);
		//result = allpassFilter.Filter(result);
		//result = iirFilter.Filter(result);
		//result = ffcFilter.Filter(result);
		
		//result = fbFilter.Filter(result);
		result = allpassFilter.Filter(result);
		//result = reverb.Filter(result);


		result *= masterVolume;

		return result;
	}
};