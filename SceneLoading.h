#pragma once

#include "Graphics/Model.h"
#include "Graphics/Texture.h"
#include "Graphics/Sprite.h"
#include "Scene.h"
#include <thread>

// ���[�f�B���O�V�[��
class SceneLoading :public Scene
{
public:
    SceneLoading(Scene* nextScene) :nextScene(nextScene) {}
    SceneLoading() {}
    ~SceneLoading()override {}

    // ������
    void Initialize()override;

    // �I����
    void Finalize()override;

    // �X�V����
    void Update(float elapsedTime)override;

    // �`�揈��
    void Render()override;

private:
    // ���[�f�B���O�X���b�h
    static void LoadingThread(SceneLoading* scene);

private:
    float p_w = 0;
    int timer = 0;
    bool next = false;
    float Trans = 0.0f;

    std::unique_ptr<Sprite>	sprite;
    std::unique_ptr<Texture> texture;

    std::unique_ptr<Sprite>	s_black;
    std::unique_ptr<Texture> t_black;

    float angle = 0.0f;
    Scene* nextScene = nullptr;
    std::thread* thread = nullptr;

    // �}�X�N�摜
    std::unique_ptr<Texture> maskTexture;
    float dissolveThreshold;
    float edgeThreshold; // ����臒l
    DirectX::XMFLOAT4 edgeColor; // ���̐F
};
