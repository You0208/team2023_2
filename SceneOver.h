#pragma once

#include "Graphics/Model.h"
#include "Graphics/Sprite.h"
#include "Graphics/Texture.h"
#include "Audio/Audio.h"
#include "Scene.h"

// �^�C�g���V�[��
class SceneOver :public Scene
{
public:
    SceneOver() {}
    ~SceneOver()override {}

    // ������
    void Initialize()override;

    // �I����
    void Finalize()override;

    // �X�V����
    void Update(float elapsedTime)override;

    // �`�揈��
    void Render()override;

private:
    // BGM
    std::unique_ptr<AudioSource> b_gameOver;
    // SE
    std::unique_ptr<AudioSource> s_choice;		// ���艹
    std::unique_ptr<AudioSource> s_selection;	// �I����

    std::unique_ptr<Sprite>	s_high;
    std::unique_ptr<Texture> t_high;

    std::unique_ptr<Sprite>	s_100p;
    std::unique_ptr<Texture> t_100p;

    std::unique_ptr<Sprite>	s_over;
    std::unique_ptr<Texture> t_over;

    std::unique_ptr<Sprite>	s_back;
    std::unique_ptr<Texture> t_back;

    std::unique_ptr<Sprite>	s_hamu;
    std::unique_ptr<Texture> t_hamu;

    std::unique_ptr<Sprite>	s_point;
    std::unique_ptr<Texture> t_point;

    std::unique_ptr<Sprite>	s_result;
    std::unique_ptr<Texture> t_result;

    std::unique_ptr<Sprite>	s_title;
    std::unique_ptr<Texture> t_title;

    std::unique_ptr<Sprite>	s_restart;
    std::unique_ptr<Texture> t_restart;

    std::unique_ptr<Sprite>	s_black;
    std::unique_ptr<Texture> t_black;


    enum OverNum
    {
        OVER_100 = 0,
        OVER_RE,
        OVER_TITLE
    };
    float iconPosX[3] = { 1200.0f,1200.0f,1200.0f };
    int selectNum = 0;


    // UV�X�N���[���f�[�^
    UVScrollData uvScrollData;
    // �}�X�N�摜
    std::unique_ptr<Texture> maskTexture;

    bool isNext = false;
    float dissolveThreshold;
    float edgeThreshold; // ����臒l
    DirectX::XMFLOAT4 edgeColor; // ���̐F
};