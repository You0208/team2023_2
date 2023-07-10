#pragma once

#include "Graphics/Model.h"
#include "Graphics/Sprite.h"
#include "Graphics/Texture.h"
#include "Audio/Audio.h"
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
    bool AddPointPerform();

private:
    // BGM
    std::unique_ptr<AudioSource> b_gameClear;
    // SE
    std::unique_ptr<AudioSource> s_choice;		// 決定音
    std::unique_ptr<AudioSource> s_selection;	// 選択音

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

    std::unique_ptr<Sprite>	s_black;
    std::unique_ptr<Texture> t_black;

    std::unique_ptr<Sprite>	s_White;
    std::unique_ptr<Texture> t_White;

    std::unique_ptr<Texture>	texture_fonts_number;		// フォントテクスチャ(数字のみ)
    std::unique_ptr<Text>		text_number;				// フォント(数字のみ)

    enum AddPointPerformState
    {
        begin = 0,      // 初期設定
        FeadIn,         // 出現
        FeadOut,        // 消滅
        end,            // 終了
    };
    DirectX::XMFLOAT2 p_pos = { PointPositionX,PointPositionY };// ポイント表示位置
    int addPoint = 0;                                           // 追加ポイント
    DirectX::XMFLOAT2 ap_pos{ PointPositionX,PointPositionY };  // 追加ポイント表示位置
    DirectX::XMFLOAT4 ap_color{ 0.741f, 0.435f, 0.435f, 0.0f };;       // 追加ポイント表示位置
    int addPointPerformState = AddPointPerformState::begin;

    float Theta = 0.0f;
    float HamuY = 400.0f;
    float time = 0;

    bool IsWhite = true;

    float iconPosX[2] = { 1200.0f,1200.0f };
    int selectNum = 0;

    bool IsNext = false;

    // UVスクロールデータ
    UVScrollData uvScrollData;
    // マスク画像
    std::unique_ptr<Texture> maskTexture;

    float dissolveThreshold;
    float edgeThreshold; // 縁の閾値
    DirectX::XMFLOAT4 edgeColor; // 縁の色
};