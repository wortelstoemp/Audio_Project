#pragma once

// ADSR Evelope for controlling the amplitude of a wave
// (ADSR = Attack, Decay, Sustain, Release)
// Gives timbre to the instrument
struct EnvelopeADSR
{
	double attackTime;
	double decayTime;
	double sustainAmplitude;
	double releaseTime;

	double targetAmplitude;
	double notePressedTime;
	double noteReleasedTime;

	EnvelopeADSR()
	{
		attackTime = 0.1;
		decayTime = 0.01;
		sustainAmplitude = 0.8;
		releaseTime = 0.20;

		targetAmplitude = 1.0;
		notePressedTime = 0.0;
		noteReleasedTime = 0.0;
	}

	void NotePressed(double time)
	{
		notePressedTime = time;
	}

	void NoteReleased(double time)
	{
		noteReleasedTime = time;
	}

	// Calculate modulated amplitude for given time
	double ModulatedAmplitude(double time)
	{
		double modulatedAmplitude = 0.0;

		if (notePressedTime > noteReleasedTime) {
			double duration = time - notePressedTime;
			// Attack
			if (duration <= attackTime) {
				// Approach the target amplitude
				modulatedAmplitude = (duration / attackTime) * targetAmplitude;
			}
			// Decay
			if (duration > attackTime && duration <= (attackTime + decayTime)) {
				// Decrease the amplitude to sustain level
				modulatedAmplitude = ((duration - attackTime) / decayTime) * (sustainAmplitude - targetAmplitude) + targetAmplitude;
			}
			// Sustain
			if (duration > (attackTime + decayTime)) {
				modulatedAmplitude = sustainAmplitude;
			}
		} else {
			// Release
			double releaseAmplitude = 0.0;
			double duration = noteReleasedTime - notePressedTime;
			if (duration <= attackTime) {
				releaseAmplitude = (duration / attackTime) * targetAmplitude;
			}
			if (duration > attackTime && duration <= (attackTime + decayTime)) {
				releaseAmplitude = ((duration - attackTime) / decayTime) * (sustainAmplitude - targetAmplitude) + targetAmplitude;
			}
			if (duration > (attackTime + decayTime)) {
				releaseAmplitude = sustainAmplitude;
			}

			modulatedAmplitude = ((time - noteReleasedTime) / releaseTime) * (0.0 - releaseAmplitude) + releaseAmplitude;
		}

		// Ensure positive amplitude and clamp to certain precision
		if (modulatedAmplitude <= 0.0) {
			modulatedAmplitude = 0.0;
		}

		return modulatedAmplitude;
	}
};