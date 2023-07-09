#pragma once

#include "Graphics/Model.h"
#include "Graphics/Sprite.h"
#include "Graphics/Texture.h"
#include "Audio/Audio.h"
#include "Scene.h"

// タイトルシーン
class SceneOver :public Scene
{
public:
    SceneOver() {}
    ~SceneOver()override {}

    // 初期化
    void Initialize()override;

    // 終了化
    void Finalize()override;

    // 更新処理
    void Update(float elapsedTime)override;

    // 描画処理
    void Render()override;

private:
    // BGM
    std::unique_ptr<AudioSource> b_gameOver;
    // SE
    std::unique_ptr<AudioSource> s_choice;		// 決定音
    std::unique_ptr<AudioSource> s_selection;	// 選択音

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


    // UVスクロールデータ
    UVScrollData uvScrollData;
    // マスク画像
    std::unique_ptr<Texture> maskTexture;

    bool isNext = false;
    float dissolveThreshold;
    float edgeThreshold; // 縁の閾値
    DirectX::XMFLOAT4 edgeColor; // 縁の色
};