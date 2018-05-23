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
class Example01Patch : public Patch
{
private:
	SineOscillator sineOsc;

public:
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
class Example02Patch : public Patch
{
private:
	SquareOscillator squareOsc;

public:
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
class Example03Patch : public Patch
{
private:
	SawOscillator sawOsc;

public:
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
class Example04Patch : public Patch
{
private:
	TriangleOscillator triangleOsc;

public:
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
class Example05Patch : public Patch
{
private:
	NoiseOscillator noiseOsc;

public:
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
class Example06Patch : public Patch
{
private:
	SawOscillator sawOsc;

public:
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
class Example07Patch : public Patch
{
private:
	SawOscillator sawOsc;
	DelayFilter delay;

public:
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
class Example08Patch : public Patch
{
private:
	SawOscillator sawOsc;
	FeedforwardCombFilter ffcf;

public:
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
class Example09Patch : public Patch
{
private:
	SineOscillator sineOsc;
	FeedbackCombFilter fbcf;

public:
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
class Example10Patch : public Patch
{
private:
	Sampler sampler;
	FeedbackCombFilter fbcf;

public:
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
class Example11Patch : public Patch
{
private:
	SquareOscillator squareOsc1;
	SquareOscillator squareOsc2;
	NoiseOscillator noiseOsc;

public:
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
class Example12Patch : public Patch
{
private:
	SawOscillator sawOsc;
	IIRFilter iir;

public:
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
class Example13Patch : public Patch
{
private:
	SineOscillator sineOsc;
	AllPassFilter allpass;

public:
	Example13Patch(double volume = 1.0)
		: Patch(volume),
		allpass(50.0, 0.7)
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
class Example14Patch : public Patch
{
private:
	NoiseOscillator noiseOsc;
	LowPassFilter lpf;

public:
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
class Example15Patch : public Patch
{
private:
	NoiseOscillator noiseOsc;
	HighPassFilter hpf;

public:
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

// Example 16: "16: Low Frequency Oscillator (LFO)"
class Example16Patch : public Patch
{
private:
	SineRealTimeOscillator sineOsc;

public:
	Example16Patch(double volume = 1.0)
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
		double result = modulatedAmplitude * sineOsc.Oscillate(time, outputFrequency, 0.0, LFO(0.02, 5.0));

		result *= masterVolume;

		return result;
	}
};

// Example 17: "17: Reverb Filter (3 serial AP's)"
class Example17Patch : public Patch
{
private:
	SineOscillator sineOsc;
	ReverberatorAP reverb;

public:
	Example17Patch(double volume = 1.0)
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
		result = reverb.Filter(result);

		result *= masterVolume;

		return result;
	}
};

// Example 18: "18: Reverb Filter (3 serial AP's + 4 parallel FFCF's)"
class Example18Patch : public Patch
{
private:
	SineOscillator sineOsc;
	ReverberatorJCREV reverb;

public:
	Example18Patch(double volume = 1.0)
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
		result = reverb.Filter(result);

		result *= masterVolume;

		return result;
	}
};