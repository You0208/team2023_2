#pragma once

#include "Graphics/Model.h"
#include "Graphics/Sprite.h"
#include "Graphics/Texture.h"
#include "Scene.h"


// タイトルシーン
class SceneClear :public Scene
{
public:
    SceneClear() {}
    ~SceneClear()override {}

    // 初期化
    void Initialize()override;

    // 終了化
    void Finalize()override;

    // 更新処理
    void Update(float elapsedTime)override;

    // 描画処理
    void Render()override;

private:
    std::unique_ptr<Sprite>	sprite;
    std::unique_ptr<Texture> texture;
    // UVスクロールデータ
    UVScrollData uvScrollData;
    // マスク画像
    std::unique_ptr<Texture> maskTexture;

    float dissolveThreshold;
    float edgeThreshold; // 縁の閾値
    DirectX::XMFLOAT4 edgeColor; // 縁の色
};