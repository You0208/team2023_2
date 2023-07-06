#pragma once

#include "Scene.h"

// シーンマネージャー
class SceneManager
{
private:
    SceneManager() {}
    ~SceneManager() {}

public:
    // 唯一のインスタンス取得
    static SceneManager& Instance()
    {
        static SceneManager instance;
        return instance;
    }

    // 更新処理
    void Update(float elapsedTime);

    // 描画処理
    void Render();

    // シーンクリア
    void Clear();

    // シーンの切り替え
    void ChangeScene(Scene* scene);

public:
    bool IsNoneStage = false;
    bool IsSelect = false;

    bool IsFinishAll = false;
private:
    Scene* currentScene = nullptr;
    Scene* nextScene = nullptr;
};