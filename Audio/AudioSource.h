#pragma once

#include <memory>
#include <xaudio2.h>
#include "Audio/AudioResource.h"

// �I�[�f�B�I�\�[�X
class AudioSource
{
public:
	AudioSource(IXAudio2* xaudio, std::shared_ptr<AudioResource>& resource);
	~AudioSource();

	// �Đ�
	void Play(bool loop);

	// ��~
	void Stop();

	// �{�����[���̐ݒ�
	void SetVolume(float v) { volume = v; }

private:
	IXAudio2SourceVoice*			sourceVoice = nullptr;
	std::shared_ptr<AudioResource>	resource;

	float volume = 1.0f;	// �{�����[��
	float MaxVolume = 1.0f;	// ���̃{�����[����ۑ�����

	bool Fade{false};		// �t�F�[�h�C��������������
	bool a[3]{};
};
