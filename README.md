# Project Audio

## Copyright
This program is created by Tom Quareme and Andries Reyskens.
All rights reserved.


## 1 Audio Engine
As an **extra**, this project uses a custom audio engine build on top of the Windows
operating system. The main influence here is the audio engine of Handmade Hero
by Casey Muratori and the Windows audio engine of Javidx9 (OneLoneCoder).
We use the WaveOut API to send sound to the hardware.
The audio engine or synthesizer can be found in the **audio_core.h** file. This 
synthesizer produces samples in 8, 16, 32 or 64 bit. The samples get send to the
sound card which essentially is a Digital-to-Analogue Converter (DAC). To be able
to do this in realtime with a certain sample rate (e.g. 44.1KHz), we do the following:

1. We make a queue of sample blocks each of a fixed length. In our application we
use 8 blocks each with 256 samples. When one uses too many blocks, one gets too much
latency, which is not desirable for keyboard playing. On the other side of the spectrum, 
if one uses 1 block with 1 sample, the sound driver needs to send interrupts at a too
high frequency to the OS and the amount of context switching will be too high.
Using 8 blocks of 256 samples per block is the best middleground between latency and 
performance.

2. Samples get send in those sample blocks in a queued fashion.

3. Sample blocks get send to the sound driver as described above and get outputted.

4. The sound driver then sends an interupt to the OS.

5. Repeat from 2.

Given that we use the APIs delivered by Windows, this program **only runs on 
Windows**! In the future this might be done in SDL2 for cross-platform purposes.
The WaveOutAPI can enumerate the available sound devices for us. We then just
select the first available sound device. Next we create a background thread.
We set properties like the sample rate, the number of bits per sample,
the amount of channels and the way our sample blocks are layed out in memory.
Then the sound device gets opened. The specified queue of sample blocks needs
to be allocated. This queue in fact is one contiguous array of memory, but
we logically divide it in blocks to deliver it to the sound driver.

When everything is setup, a background thread in CPU space starts running.
This thread mainly is a while loop which waits for a message of the sound driver
so a new block can be filled. This communication is done via a conditional variable
and wait() and notify() functions. Next we prepare the new block for processing and
fill it with data. For each sample within the block, we call the sample generator
function of the patch along with the current time, which can be found in **patch.h**.
When using stereo this is done for the left and right channels.
Finally we write the block to the queue. The WaveOutAPI does the rest.


## 2 Patches
### 2.1 Sine Oscillator
The sine oscillator is our first and default patch which can be loaded into the synth.
In order to avoid realtime computation of a sine for each sample, we use a wavetable.
To be generic, we make a base class Oscillator with a wavetable and an Oscillate function
which reads and interpolates values of this wavetable according to wavetable theory.
FillWavetable() will be implemented for each different oscillator type.
The sine oscillator can be found in **sine_oscillator.h**. It sounds like a smooth and
pure sound wave.

### 2.2 Square Oscillator
As an **extra**, we have also implemented a square oscillator which is implemented
in **square_oscillator.h**. This wave sounds more artificial, like it is used in older 
computer games. It also uses a wavetable.

### 2.3 Saw Oscillator
As an **extra**, we have also implemented a saw oscillator which is implemented
in **saw_oscillator.h**. This wave sounds like a saw. Definitely harsher than
a sine wave, but more natural than a square wave. It also uses a wavetable.

### 2.4 Triangle Oscillator
As an **extra**, we have also implemented a triangle oscillator which is implemented
in **triangle_oscillator.h**. This wave sounds like a cross between a sine wave and
a square wave. It also uses a wavetable.

### 2.5 Noise Oscillator
As an **extra**, we have also implemented a noise oscillator which is implemented
in **noise_oscillator.h**. This wave sounds like random white noise.
It also uses a wavetable.

### 2.6 ADSR Envelope
As an **extra**, we have also implemented an ADSR envelope, which can be found
in **envelope_adsr.h**. In this case it is used to modulate the amplitude of the
wave. ADSR = Attack, Decay, Sustain and Release. The parameters for the ADSR envelope
are set programmatically. Parameters include:
1. Attack time
2. Decay time
3. Sustain amplitude
4. Release time
5. Peak or target amplitude
6. The time when a note is pressed
7. The time when a note is released

The modulated amplitude gets computed in the **ModulatedAmplitude()** method.

## 3 Usage
Please follow these steps:
1. Open the folder **ReleaseBinaries** in the command prompt.
2. Open **Project_Audio.exe** which is a x86 Windows executable.
3. Type the number of the listed patches you want to use.
4. When opening "10: Sampler", you need to type the name of the sample you want to use.
This sample should be placed in **ReleaseBinaries/Data**.
To load the sample you only need to type its name, not the path. For example: **babe.wav**.
5. Use the keys on the shown keyboard to play.
Note that the mapping only works for **AZERTY keyboards** and **only ONE key can be pressed
at a time** to get a clear sound. Polyphony is currently not supported.
6. Use the **up** and **down arrow keys** to shift the frequency by 10Hz while playing.
7. Press Esc to end the application.
8. Open the application again like in step 1 to open a new patch. 

## 4 Extras summarized
Here is a list of all the extras implemented:
1. Custom audio engine on top of the operating system.
2. Square oscillator.
3. Saw oscillator.
4. Triangle oscillator.
5. Noise oscillator.
6. ADSR envelope.
7. Mixers of more than 2 samples (up to 8).
8. Low-pass filter.
9. High-pass filter.
10. Low Frequency Oscillator (LFO).
