#pragma once

#include "Graphics/Model.h"
#include "Graphics/Sprite.h"
#include "Graphics/Texture.h"
#include "Audio/Audio.h"
#include "Scene.h"

// タイトルシーン
class SceneOver :public Scene
{
private:
    static constexpr float PointPositionX = 1600.0f;    // 追加ポイント位置(X)
    static constexpr float PointPositionY = 30.0f;      // 追加ポイント位置(Y)
    static  float AddPointMoveAmount;// 追加ポイント移動量

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
    // ポイントの加算(ポイントが加算されたらtureを返す)
    bool AddPoint();
    // 追加ポイント演出(終了するとtrueを返す)
    bool AddPointPerform();

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
    DirectX::XMFLOAT4 ap_color{ 0.0f, 0.0f, 0.0f, 1.0f };       // 追加ポイント表示位置
    int addPointPerformState = AddPointPerformState::begin;

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

    float dissolveThreshold;
    float edgeThreshold; // 縁の閾値
    DirectX::XMFLOAT4 edgeColor; // 縁の色
};