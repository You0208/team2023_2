#pragma once

#include <memory>
#include <xaudio2.h>
#include "Audio/AudioResource.h"

// オーディオソース
class AudioSource
{
public:
	AudioSource(IXAudio2* xaudio, std::shared_ptr<AudioResource>& resource);
	~AudioSource();

	// 再生
	void Play(bool loop);

	// 停止
	void Stop();

	// ボリュームの設定
	void SetVolume(float v) { volume = v; }

private:
	IXAudio2SourceVoice*			sourceVoice = nullptr;
	std::shared_ptr<AudioResource>	resource;

	float volume = 1.0f;	// ボリューム
};
