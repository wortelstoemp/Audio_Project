#pragma once

// Author: Tom Quareme (2018)
//
// Keyboard positions (101, 102 and 106 key keyboards):
// https://www.ibm.com/support/knowledgecenter/ssw_aix_71/com.ibm.aix.keyboardtechref/doc/kybdtech/figures/kybdt1.jpg
// https://www.ibm.com/support/knowledgecenter/ssw_aix_71/com.ibm.aix.keyboardtechref/doc/kybdtech/figures/kybdt2.jpg
// https://www.ibm.com/support/knowledgecenter/ssw_aix_71/com.ibm.aix.keyboardtechref/doc/kybdtech/figures/kybdt3.jpg
//
// Virtual-Key Codes on MSDN:
// https://msdn.microsoft.com/en-us/library/windows/desktop/dd375731(v=vs.85).aspx
//
// Scan codes:
// https://docs.microsoft.com/en-us/previous-versions/visualstudio/visual-studio-6.0/images/aa299374.l0ckey1%28en-us%2cvs.60%29.gif
// https://docs.microsoft.com/en-us/previous-versions/visualstudio/visual-studio-6.0/images/aa299374.l0ckey2%28en-us%2cvs.60%29.gif

#include <Windows.h>

#include <iostream>
#include <string>
#include <vector>

#include "audio_core.h"
#include "patch.h"

// Maps keyboard notes to appropriate scan codes of keyboard
enum KeyboardNote
{
	KEYBOARD_NOTE_C = 0x1e,			// Q (azerty BE), A (qwerty US) or position 31
	KEYBOARD_NOTE_CSHARP = 0x11,	// Z (azerty BE), W (qwerty US) or position 18
	KEYBOARD_NOTE_D = 0x1f,			// S (azerty BE), S (qwerty US) or position 32
	KEYBOARD_NOTE_DSHARP = 0x12,	// E (azerty BE), E (qwerty US) or position 19
	KEYBOARD_NOTE_E = 0x20,			// D (azerty BE), D (qwerty US) or position 33
	KEYBOARD_NOTE_F = 0x21,			// F (azerty BE), F (qwerty US) or position 34
	KEYBOARD_NOTE_FSHARP = 0x14,	// T (azerty BE), T (qwerty US) or position 21
	KEYBOARD_NOTE_G = 0x22,			// G (azerty BE), G (qwerty US) or position 35
	KEYBOARD_NOTE_GSHARP = 0x15,	// Y (azerty BE), Y (qwerty US) or position 22
	KEYBOARD_NOTE_A = 0x23,			// H (azerty BE), H (qwerty US) or position 36
	KEYBOARD_NOTE_ASHARP = 0x16,	// U (azerty BE), U (qwerty US) or position 23
	KEYBOARD_NOTE_B = 0x24,			// J (azerty BE), J (qwerty US) or position 37

	KEYBOARD_NOTE_UP = 0x48,		// UP ARROW
	KEYBOARD_NOTE_DOWN = 0x50,		// DOWN ARROW

	KEYBOARD_NOTE_COUNT = 12,
	KEYBOARD_OTHER_COUNT = 2
};

struct Keyboard
{
	std::vector<KeyboardNote> notes;
	std::vector<std::string> noteNames;

	int currentKeyIndex = -1;
	
	Keyboard()
	{
		notes.reserve(KEYBOARD_NOTE_COUNT + KEYBOARD_OTHER_COUNT);
		{
			notes.push_back(KEYBOARD_NOTE_C);
			notes.push_back(KEYBOARD_NOTE_CSHARP);
			notes.push_back(KEYBOARD_NOTE_D);
			notes.push_back(KEYBOARD_NOTE_DSHARP);
			notes.push_back(KEYBOARD_NOTE_E);
			notes.push_back(KEYBOARD_NOTE_F);
			notes.push_back(KEYBOARD_NOTE_FSHARP);
			notes.push_back(KEYBOARD_NOTE_G);
			notes.push_back(KEYBOARD_NOTE_GSHARP);
			notes.push_back(KEYBOARD_NOTE_A);
			notes.push_back(KEYBOARD_NOTE_ASHARP);
			notes.push_back(KEYBOARD_NOTE_B);

			notes.push_back(KEYBOARD_NOTE_UP);
			notes.push_back(KEYBOARD_NOTE_DOWN);
		}
		noteNames.reserve(KEYBOARD_NOTE_COUNT + KEYBOARD_OTHER_COUNT);
		{
			noteNames.push_back("C");
			noteNames.push_back("C#");
			noteNames.push_back("D");
			noteNames.push_back("D#");
			noteNames.push_back("E");
			noteNames.push_back("F");
			noteNames.push_back("F#");
			noteNames.push_back("G");
			noteNames.push_back("G#");
			noteNames.push_back("A");
			noteNames.push_back("A#");
			noteNames.push_back("B");

			noteNames.push_back("UP");
			noteNames.push_back("DOWN");
		}
	}

	int NoteCount()
	{
		return KEYBOARD_NOTE_COUNT;
	}

	void PrintCurrentKey()
	{
		if (currentKeyIndex < 0) {
			return;
		}

		std::cout << noteNames[currentKeyIndex];
	}

	int ScancodeToKeycode(int scancode)
	{
		return MapVirtualKey(scancode, MAPVK_VSC_TO_VK);
	}

	bool NonNotePressed(int scancode)
	{
		int key = ScancodeToKeycode(scancode);
		return KeyPressed(key);
	}

	bool KeyPressed(int key)
	{
		return (GetAsyncKeyState(key) & 0x8000);
	}

	bool NotePressed(int index)
	{
		if (index < 0) {
			return false;
		}

		int key = ScancodeToKeycode(notes[index]);
		return KeyPressed(key);
	}

	template<typename T>
	void Loop(AudioCore<T>* core, Patch* patch)
	{
		bool noteKeyPressed = false;
		bool freqUpPressed = false;
		bool freqDownPressed = false;

		bool keyboardLoop = true;
		while (keyboardLoop) {
			noteKeyPressed = false;
			
			if (GetAsyncKeyState(VK_UP) != 0) {
				freqUpPressed = true;
			} else if (freqUpPressed) {
				// On release
				freqUpPressed = false;
				patch->IncreaseFrequencyShifter();
				patch->outputFrequency = patch->NoteToFrequency(currentKeyIndex);
				std::cout << "\rNote On : " << patch->outputFrequency << "Hz                             ";
			}
			if (GetAsyncKeyState(VK_DOWN) != 0) {
				freqDownPressed = true;
			}
			else if (freqDownPressed) {
				// On release
				freqDownPressed = false;
				patch->DecreaseFrequencyShifter();
				patch->outputFrequency = patch->NoteToFrequency(currentKeyIndex);
				std::cout << "\rNote On : " << patch->outputFrequency << "Hz                             ";
			}

			for (int k = 0; k < NoteCount(); k++) {
				if (NotePressed(k)) {
					if (currentKeyIndex != k) {
						currentKeyIndex = k;
						patch->envelopeADSR.NotePressed(core->GetTime());

						patch->outputFrequency = patch->NoteToFrequency(k);
						std::cout << "\rNote On : " << patch->outputFrequency << "Hz                             ";
					}

					noteKeyPressed = true;
				}
			}

			if (!noteKeyPressed) {
				if (currentKeyIndex != -1) {
					currentKeyIndex = -1;
					patch->envelopeADSR.NoteReleased(core->GetTime());

					std::cout << "\rNote Off                                 ";
				}
			}
		}
	}
};