#pragma once

#include "Graphics/Model.h"
#include "Graphics/Sprite.h"
#include "Graphics/Texture.h"
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
    std::unique_ptr<Sprite>	sprite;
    std::unique_ptr<Texture> texture;

    std::unique_ptr<Sprite>	s_over;
    std::unique_ptr<Texture> t_over;

    std::unique_ptr<Sprite>	s_back;
    std::unique_ptr<Texture> t_back;

    std::unique_ptr<Sprite>	s_hamu;
    std::unique_ptr<Texture> t_hamu;

    std::unique_ptr<Sprite>	s_point;
    std::unique_ptr<Texture> t_point;

    // UV�X�N���[���f�[�^
    UVScrollData uvScrollData;
    // �}�X�N�摜
    std::unique_ptr<Texture> maskTexture;

    float dissolveThreshold;
    float edgeThreshold; // ����臒l
    DirectX::XMFLOAT4 edgeColor; // ���̐F
};