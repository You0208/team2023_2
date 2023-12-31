#pragma once

#include "Graphics/Model.h"
#include "Graphics/Texture.h"
#include "Graphics/Sprite.h"
#include "Scene.h"
#include <thread>

// ローディングシーン
class SceneLoading :public Scene
{
public:
    SceneLoading(Scene* nextScene) :nextScene(nextScene) {}
    SceneLoading() {}
    ~SceneLoading()override {}

    // 初期化
    void Initialize()override;

    // 終了化
    void Finalize()override;

    // 更新処理
    void Update(float elapsedTime)override;

    // 描画処理
    void Render()override;

private:
    // ローディングスレッド
    static void LoadingThread(SceneLoading* scene);

private:
    std::unique_ptr<Sprite>	sprite;
    std::unique_ptr<Texture> texture;
    float angle = 0.0f;
    Scene* nextScene = nullptr;
    std::thread* thread = nullptr;
};
