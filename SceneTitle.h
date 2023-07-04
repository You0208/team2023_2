#pragma once

#include "Graphics/Model.h"
#include "Graphics/Sprite.h"
#include "Graphics/Texture.h"
#include "Scene.h"

// �^�C�g���V�[��
class SceneTitle :public Scene
{
public:
    SceneTitle() {}
    ~SceneTitle()override {}

    // ������
    void Initialize()override;

    // �I����
    void Finalize()override;

    // �X�V����
    void Update(float elapsedTime)override;

    // �`�揈��
    void Render()override;

private:
    std::unique_ptr<Sprite>	sprite;
    std::unique_ptr<Texture> texture;

    std::unique_ptr<Sprite>	s_back;
    std::unique_ptr<Texture> t_back;

    std::unique_ptr<Sprite>	s_frame;
    std::unique_ptr<Texture> t_frame;

    std::unique_ptr<Sprite>	s_hamu;
    std::unique_ptr<Texture> t_hamu;

    std::unique_ptr<Sprite>	s_logo;
    std::unique_ptr<Texture> t_logo;

    std::unique_ptr<Sprite>	s_start;
    std::unique_ptr<Texture> t_start;

    // UV�X�N���[���f�[�^
    UVScrollData uvScrollData;
    // �}�X�N�摜
    std::unique_ptr<Texture> maskTexture;

    float Trans = 0.0f;
    float Trans_A = 0.0f;
    float Theta = 0.0f;
    float HamuY = 260.0f;
    float time = 0;

    bool next = false;

    float dissolveThreshold;
    float edgeThreshold; // ����臒l
    DirectX::XMFLOAT4 edgeColor; // ���̐F
};