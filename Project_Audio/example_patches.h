#pragma once

#include "patch.h"

#include "sine_oscillator.h"
#include "square_oscillator.h"
#include "saw_oscillator.h"
#include "triangle_oscillator.h"
#include "noise_oscillator.h"

#include "lfo.h"
#include "feedforward_comb_filter.h"
#include "feedback_comb_filter.h"
#include "allpass_filter.h"
#include "iir_filter.h"
#include "highpass_filter.h"
#include "lowpass_filter.h"
#include "delay_filter.h"
#include "reverb_filter.h"
#include "sampler.h"
#include "mixer.h"

// Example 01: "1: Sine oscillator"
struct Example01Patch : public Patch
{
	SineOscillator sineOsc;

	Example01Patch(double volume = 1.0)
		: Patch(volume)
	{
		envelopeADSR.attackTime = 0.01;
		envelopeADSR.decayTime = 0.0;
		envelopeADSR.sustainAmplitude = 1.0;
		envelopeADSR.releaseTime = 0.1;
		outputFrequency = 0.0;
		masterVolume = volume;
	}

	double Run(double time)
	{
		double modulatedAmplitude = envelopeADSR.ModulatedAmplitude(time);
		double result = modulatedAmplitude * sineOsc.Oscillate(outputFrequency);

		result *= masterVolume;

		return result;
	}
};

// Example 02: "1: Square oscillator"
struct Example02Patch : public Patch
{
	SquareOscillator squareOsc;

	Example02Patch(double volume = 1.0)
		: Patch(volume)
	{
		envelopeADSR.attackTime = 0.01;
		envelopeADSR.decayTime = 0.0;
		envelopeADSR.sustainAmplitude = 1.0;
		envelopeADSR.releaseTime = 0.1;
		outputFrequency = 0.0;
		masterVolume = volume;
	}

	double Run(double time)
	{
		double modulatedAmplitude = envelopeADSR.ModulatedAmplitude(time);
		double result = modulatedAmplitude * squareOsc.Oscillate(outputFrequency);

		result *= masterVolume;

		return result;
	}
};

// Example 03: "3: Saw oscillator"
struct Example03Patch : public Patch
{
	SawOscillator sawOsc;

	Example03Patch(double volume = 1.0)
		: Patch(volume)
	{
		envelopeADSR.attackTime = 0.01;
		envelopeADSR.decayTime = 0.0;
		envelopeADSR.sustainAmplitude = 1.0;
		envelopeADSR.releaseTime = 0.1;
		outputFrequency = 0.0;
		masterVolume = volume;
	}

	double Run(double time)
	{
		double modulatedAmplitude = envelopeADSR.ModulatedAmplitude(time);
		double result = modulatedAmplitude * sawOsc.Oscillate(outputFrequency);

		result *= masterVolume;

		return result;
	}
};

// Example 04: "4: Triangle oscillator"
struct Example04Patch : public Patch
{
	TriangleOscillator triangleOsc;

	Example04Patch(double volume = 1.0)
		: Patch(volume)
	{
		envelopeADSR.attackTime = 0.01;
		envelopeADSR.decayTime = 0.0;
		envelopeADSR.sustainAmplitude = 1.0;
		envelopeADSR.releaseTime = 0.1;
		outputFrequency = 0.0;
		masterVolume = volume;
	}

	double Run(double time)
	{
		double modulatedAmplitude = envelopeADSR.ModulatedAmplitude(time);
		double result = modulatedAmplitude * triangleOsc.Oscillate(outputFrequency);

		result *= masterVolume;

		return result;
	}
};

// Example 05: "5: Noise oscillator"
struct Example05Patch : public Patch
{
	NoiseOscillator noiseOsc;

	Example05Patch(double volume = 1.0)
		: Patch(volume)
	{
		envelopeADSR.attackTime = 0.01;
		envelopeADSR.decayTime = 0.0;
		envelopeADSR.sustainAmplitude = 1.0;
		envelopeADSR.releaseTime = 0.1;
		outputFrequency = 0.0;
		masterVolume = volume;
	}

	double Run(double time)
	{
		double modulatedAmplitude = envelopeADSR.ModulatedAmplitude(time);
		double result = modulatedAmplitude * noiseOsc.Oscillate(outputFrequency);

		result *= masterVolume;

		return result;
	}
};

// Example 06: "6: ADSR Envelope"
struct Example06Patch : public Patch
{
	SawOscillator sawOsc;

	Example06Patch(double volume = 1.0)
		: Patch(volume)
	{
		envelopeADSR.attackTime = 1.0;
		envelopeADSR.decayTime = 1.0;
		envelopeADSR.sustainAmplitude = 0.3;
		envelopeADSR.releaseTime = 1.0;
		outputFrequency = 0.0;
		masterVolume = volume;
	}

	double Run(double time)
	{
		double modulatedAmplitude = envelopeADSR.ModulatedAmplitude(time);
		double result = modulatedAmplitude * sawOsc.Oscillate(outputFrequency);

		result *= masterVolume;

		return result;
	}
};

// Example 07: "7: Delay Line"
struct Example07Patch : public Patch
{
	SawOscillator sawOsc;
	DelayFilter delay;

	Example07Patch(double volume = 1.0)
		: Patch(volume),
		delay(AudioSettings::Properties().SampleRate(), 1000.0)
	{
		envelopeADSR.attackTime = 0.01;
		envelopeADSR.decayTime = 0.0;
		envelopeADSR.sustainAmplitude = 1.0;
		envelopeADSR.releaseTime = 0.1;
		outputFrequency = 0.0;
		masterVolume = volume;
	}

	double Run(double time)
	{
		double modulatedAmplitude = envelopeADSR.ModulatedAmplitude(time);
		double result = modulatedAmplitude * sawOsc.Oscillate(outputFrequency);

		result = delay.Filter(result);

		result *= masterVolume;

		return result;
	}
};

// Example 08: "8: Feedforward Comb Filter"
struct Example08Patch : public Patch
{
	SawOscillator sawOsc;
	FeedforwardCombFilter ffcf;

	Example08Patch(double volume = 1.0)
		: Patch(volume),
		ffcf(500.0, 0.4)
	{
		envelopeADSR.attackTime = 0.01;
		envelopeADSR.decayTime = 0.0;
		envelopeADSR.sustainAmplitude = 1.0;
		envelopeADSR.releaseTime = 0.1;
		outputFrequency = 0.0;
		masterVolume = volume;
	}

	double Run(double time)
	{
		double modulatedAmplitude = envelopeADSR.ModulatedAmplitude(time);
		double result = modulatedAmplitude * sawOsc.Oscillate(outputFrequency);

		result = ffcf.Filter(result);

		result *= masterVolume;

		return result;
	}
};

// Example 09: "9: Feedback Comb Filter"
struct Example09Patch : public Patch
{
	SineOscillator sineOsc;
	FeedbackCombFilter fbcf;

	Example09Patch(double volume = 1.0)
		: Patch(volume),
		fbcf(500.0, 0.4)
	{
		envelopeADSR.attackTime = 0.01;
		envelopeADSR.decayTime = 0.0;
		envelopeADSR.sustainAmplitude = 1.0;
		envelopeADSR.releaseTime = 0.1;
		outputFrequency = 0.0;
		masterVolume = volume;
	}

	double Run(double time)
	{
		double modulatedAmplitude = envelopeADSR.ModulatedAmplitude(time);
		double result = modulatedAmplitude * sineOsc.Oscillate(outputFrequency);

		result = fbcf.Filter(result);

		result *= masterVolume;

		return result;
	}
};

// Example 10: "10: Sampler"
struct Example10Patch : public Patch
{
	Sampler sampler;
	FeedbackCombFilter fbcf;

	Example10Patch(double volume = 1.0)
		: Patch(volume),
		fbcf(500.0, 0.4)
	{
		envelopeADSR.attackTime = 1.0;
		envelopeADSR.decayTime = 1.0;
		envelopeADSR.sustainAmplitude = 0.3;
		envelopeADSR.releaseTime = 1.0;
		outputFrequency = 0.0;
		masterVolume = volume;

		sampler.Open("D:\\Projects\\Audio\\Project_Audio\\Project_Audio\\Data\\babe.wav");
	}

	double Run(double time)
	{
		double modulatedAmplitude = envelopeADSR.ModulatedAmplitude(time);
		double result = sampler.Sample(modulatedAmplitude);
		result = fbcf.Filter(result);

		result *= masterVolume;

		return result;
	}
};

// Example 11: "11: Mixer"
struct Example11Patch : public Patch
{
	SquareOscillator squareOsc1;
	SquareOscillator squareOsc2;
	NoiseOscillator noiseOsc;

	Example11Patch(double volume = 1.0)
		: Patch(volume)
	{
		envelopeADSR.attackTime = 0.05;
		envelopeADSR.decayTime = 1.0;
		envelopeADSR.sustainAmplitude = 0.95;
		envelopeADSR.releaseTime = 0.1;
		outputFrequency = 0.0;
		masterVolume = volume;
	}

	double Run(double time)
	{
		double modulatedAmplitude = envelopeADSR.ModulatedAmplitude(time);
		double square1 = squareOsc1.Oscillate(outputFrequency);
		double square2 = squareOsc2.Oscillate(3*outputFrequency);
		double noise = noiseOsc.Oscillate(outputFrequency);
		double result = modulatedAmplitude * Mixer3(square1, square2, noise, 1.0, 0.5, 0.25);

		result *= masterVolume;

		return result;
	}
};

// Example 12: "12: IIR Filter"
struct Example12Patch : public Patch
{
	SawOscillator sawOsc;
	IIRFilter iir;

	Example12Patch(double volume = 1.0)
		: Patch(volume),
		iir(0.001)
	{
		envelopeADSR.attackTime = 0.01;
		envelopeADSR.decayTime = 0.0;
		envelopeADSR.sustainAmplitude = 1.0;
		envelopeADSR.releaseTime = 0.1;
		outputFrequency = 0.0;
		masterVolume = volume;
	}

	double Run(double time)
	{
		double modulatedAmplitude = envelopeADSR.ModulatedAmplitude(time);
		double result = modulatedAmplitude * sawOsc.Oscillate(outputFrequency);
		result = iir.Filter(result);

		result *= 1.25 * masterVolume;

		return result;
	}
};

// Example 13: "13: All-pass Filter"
struct Example13Patch : public Patch
{
	SineOscillator sineOsc;
	AllPassFilter allpass;

	Example13Patch(double volume = 1.0)
		: Patch(volume),
		allpass(500.0, 0.7)
	{
		envelopeADSR.attackTime = 0.01;
		envelopeADSR.decayTime = 0.0;
		envelopeADSR.sustainAmplitude = 1.0;
		envelopeADSR.releaseTime = 0.1;
		outputFrequency = 0.0;
		masterVolume = volume;
	}

	double Run(double time)
	{
		double modulatedAmplitude = envelopeADSR.ModulatedAmplitude(time);
		double result = modulatedAmplitude * sineOsc.Oscillate(outputFrequency);
		result = allpass.Filter(result);

		result *= masterVolume;

		return result;
	}
};

// Example 14: "14: Low-pass Filter"
struct Example14Patch : public Patch
{
	NoiseOscillator noiseOsc;
	LowPassFilter lpf;

	Example14Patch(double volume = 1.0)
		: Patch(volume),
		lpf(0.001)
	{
		envelopeADSR.attackTime = 0.01;
		envelopeADSR.decayTime = 0.0;
		envelopeADSR.sustainAmplitude = 1.0;
		envelopeADSR.releaseTime = 0.1;
		outputFrequency = 0.0;
		masterVolume = volume;
	}

	double Run(double time)
	{
		double modulatedAmplitude = envelopeADSR.ModulatedAmplitude(time);
		double result = modulatedAmplitude * noiseOsc.Oscillate(outputFrequency);
		result = lpf.Filter(result);

		result *= masterVolume;

		return result;
	}
};

// Example 15: "15: High-pass Filter"
struct Example15Patch : public Patch
{
	NoiseOscillator noiseOsc;
	HighPassFilter hpf;

	Example15Patch(double volume = 1.0)
		: Patch(volume),
		hpf(0.001)
	{
		envelopeADSR.attackTime = 0.01;
		envelopeADSR.decayTime = 0.0;
		envelopeADSR.sustainAmplitude = 1.0;
		envelopeADSR.releaseTime = 0.1;
		outputFrequency = 0.0;
		masterVolume = volume;
	}

	double Run(double time)
	{
		double modulatedAmplitude = envelopeADSR.ModulatedAmplitude(time);
		double result = modulatedAmplitude * noiseOsc.Oscillate(outputFrequency);
		result = hpf.Filter(result);
		result *= masterVolume;

		return result;
	}
};