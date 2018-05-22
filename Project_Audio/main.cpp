#include <iostream>

#include "audio_settings.h"
#include "audio_core.h"
#include "audio_io.h"
#include "keyboard.h"

#include "oscillator.h"
#include "sine_oscillator.h"
#include "saw_oscillator.h"
#include "square_oscillator.h"
#include "envelope_adsr.h"
#include "patch.h"

#include "bell_patch.h"
#include "harmonica_patch.h"
#include "example_patches.h"


int main()
{
	std::cout << "Synthesizer 1.0 by Tom Quareme and Dries Reyskens" << std::endl;

	AudioDevice audio_device;
	{
		auto audio_devices = AudioCore32Bit::EnumerateDevices();
		if (audio_devices.size() < 1) {
			std::cerr << "No audio device found!" << std::endl;
			return 1;
		}
		audio_device = audio_devices[0];
		std::wcout << "Audio device: " << audio_device << std::endl;
	}

	/*std::cout << std::endl <<
		"Qwerty keyboard layout example:" << std::endl << std::endl <<
		"|   |   | |   |   |   |   | |   | |   |   |" << std::endl <<
		"|   | W | | E |   |   | T | | Y | | U |   |" << std::endl <<
		"|   |___| |___|   |   |___| |___| |___|   |" << std::endl <<
		"|     |     |     |     |     |     |     |" << std::endl <<
		"|  A  |  S  |  D  |  F  |  G  |  H  |  J  |" << std::endl <<
		"|_____|_____|_____|_____|_____|_____|_____|" << std::endl << std::endl;*/

	std::cout << std::endl <<
		"Azerty keyboard layout example:" << std::endl << std::endl <<
		"|   |   | |   |   |   |   | |   | |   |   |" << std::endl <<
		"|   | Z | | E |   |   | T | | Y | | U |   |" << std::endl <<
		"|   |___| |___|   |   |___| |___| |___|   |" << std::endl <<
		"|     |     |     |     |     |     |     |" << std::endl <<
		"|  Q  |  S  |  D  |  F  |  G  |  H  |  J  |" << std::endl <<
		"|_____|_____|_____|_____|_____|_____|_____|" << std::endl << std::endl;

	std::cout << "Use up and down arrow keys to adjust frequency in steps of 10 Hz." << std::endl;
	std::cout << "Use Esc key to stop the synth. Reload program to select another patch." << std::endl;


	AudioSettings::Properties().Init(48000, 1, 8, 512);

	AudioCore32Bit synth
	(
		audio_device,
		AudioSettings::Properties().SampleRate(),		// sampleRate 
		AudioSettings::Properties().ChannelCount(),	// channelCount
		AudioSettings::Properties().BlockCount(),		// blockCount, 
		AudioSettings::Properties().BlockSampleCount()	// blockSampleCount
	);
	
	////////////////////////////////////////////////////////////////////////////
	// NOTE: Create and set patches here
	//Patch* patch = new HarmonicaPatch(0.4);
	Patch* patch = new Example15Patch(0.4);
	// other patches...

	synth.SetPatch(patch);
	////////////////////////////////////////////////////////////////////////////

	// Keyboard loop
	Keyboard keyboard;
	keyboard.Loop(&synth, patch);

	// Cleanup
	delete patch;

	return 0;
}