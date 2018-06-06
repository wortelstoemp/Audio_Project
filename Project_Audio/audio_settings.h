#pragma once

class AudioSettings
{
public:
	void Init(int initSampleRate = 44100, int initChannelCount = 1, int initBlockCount = 8, int initBlockSampleCount = 512)
	{
		this->sampleRate = initSampleRate;
		this->channelCount = initChannelCount;
		this->blockCount = initBlockCount;
		this->blockSampleCount = initBlockSampleCount;
	}

	static AudioSettings& Properties()
	{
		static AudioSettings instance;

		return instance;
	}

	void SampleRate(int value)
	{
		sampleRate = value;
	}

	int SampleRate() const
	{
		return sampleRate;
	}

	int ChannelCount() const
	{
		return channelCount;
	}

	int BlockCount() const
	{
		return blockCount;
	}

	int BlockSampleCount() const
	{
		return blockSampleCount;
	}

private:
	AudioSettings() {}
	AudioSettings(AudioSettings const&);
	void operator=(AudioSettings const&);

	int sampleRate;
	int channelCount;
	int blockCount;
	int blockSampleCount;
};