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
    std::unique_ptr<Sprite>	s_back;
    std::unique_ptr<Texture> t_back;

    std::unique_ptr<Sprite>	s_endles;
    std::unique_ptr<Texture> t_endles;

    std::unique_ptr<Sprite>	s_ham;
    std::unique_ptr<Texture> t_ham;

    std::unique_ptr<Sprite>	s_point;
    std::unique_ptr<Texture> t_point;

    std::unique_ptr<Sprite>	s_result;
    std::unique_ptr<Texture> t_result;

    std::unique_ptr<Sprite>	s_score;
    std::unique_ptr<Texture> t_score;

    std::unique_ptr<Sprite>	s_title;
    std::unique_ptr<Texture> t_title;

    float iconPosX[2] = { 1200.0f,1200.0f };
    int selectNum = 0;

    // UVスクロールデータ
    UVScrollData uvScrollData;
    // マスク画像
    std::unique_ptr<Texture> maskTexture;

    float dissolveThreshold;
    float edgeThreshold; // 縁の閾値
    DirectX::XMFLOAT4 edgeColor; // 縁の色
};