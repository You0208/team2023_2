#include "Graphics/Graphics.h"
#include "SceneLoading.h"
#include "SceneGame.h"
#include "SceneManager.h"
#include "StageManager.h"
#include "SceneOver.h"
#include "SceneTitle.h"
#include "Input/Input.h"
#include "Player.h"

// 初期化
void SceneOver::Initialize()
{
    // オーディオ初期化
    b_gameOver = Audio::Instance().LoadAudioSource("Data/Audio/BGM/BGM_GameOver.wav");
    b_gameOver->SetVolume(0.2f);
    b_gameOver->Play(false);
    s_choice = Audio::Instance().LoadAudioSource("Data/Audio/SE/Choice.wav");
    s_choice->SetVolume(0.3f);
    s_selection = Audio::Instance().LoadAudioSource("Data/Audio/SE/Selection.wav");
    s_selection->SetVolume(1.0f);

    // フォント
    texture_fonts_number = std::make_unique<Texture>("Data/fonts/font7.png");
    text_number = std::make_unique<Text>();
    text_number->SetShaderResourceView(texture_fonts_number->GetShaderResourceView(),
        texture_fonts_number->GetWidth(), texture_fonts_number->GetHeight());

    //-------------------------------------------------------------------------------------------------------
    // ↓　この下はシェーダー関連
    //-------------------------------------------------------------------------------------------------------

    // リスタート
    // スプライト初期化
    t_restart = std::make_unique<Texture>("Data/Texture/GameOver/restart.png");
    // スプライト
    s_restart = std::make_unique<Sprite>();
    s_restart->SetShaderResourceView(t_restart->GetShaderResourceView(), t_restart->GetWidth(), t_restart->GetHeight());


    // タイトル
    // スプライト初期化
    t_title = std::make_unique<Texture>("Data/Texture/GameOver/title.png");
    // スプライト
    s_title = std::make_unique<Sprite>();
    s_title->SetShaderResourceView(t_title->GetShaderResourceView(), t_title->GetWidth(), t_title->GetHeight());
    
    // リザルト
    // スプライト初期化
    t_result = std::make_unique<Texture>("Data/Texture/GameOver/result.png");
    // スプライト
    s_result = std::make_unique<Sprite>();
    s_result->SetShaderResourceView(t_result->GetShaderResourceView(), t_result->GetWidth(), t_result->GetHeight());


    // スコア
    // スプライト初期化
    t_high = std::make_unique<Texture>("Data/Texture/GameOver/score.png");
    // スプライト
    s_high = std::make_unique<Sprite>();
    s_high->SetShaderResourceView(t_high->GetShaderResourceView(), t_high->GetWidth(), t_high->GetHeight());

    // 100ポイント
    // スプライト初期化
    t_100p = std::make_unique<Texture>("Data/Texture/GameOver/100point_use.png");
    // スプライト
    s_100p = std::make_unique<Sprite>();
    s_100p->SetShaderResourceView(t_100p->GetShaderResourceView(), t_100p->GetWidth(), t_100p->GetHeight());

    // オーバー
    // スプライト初期化
    t_over = std::make_unique<Texture>("Data/Texture/GameOver/gameover.png");
    // スプライト
    s_over = std::make_unique<Sprite>();
    s_over->SetShaderResourceView(t_over->GetShaderResourceView(), t_over->GetWidth(), t_over->GetHeight());

    // 背景
    // スプライト初期化
    t_back = std::make_unique<Texture>("Data/Texture/GameOver/back.png");
    // スプライト
    s_back = std::make_unique<Sprite>();
    s_back->SetShaderResourceView(t_back->GetShaderResourceView(), t_back->GetWidth(), t_back->GetHeight());

    // ハムスター
    // スプライト初期化
    t_hamu = std::make_unique<Texture>("Data/Texture/GameOver/hamster.png");
    // スプライト
    s_hamu = std::make_unique<Sprite>();
    s_hamu->SetShaderResourceView(t_hamu->GetShaderResourceView(), t_hamu->GetWidth(), t_hamu->GetHeight());

    // ポイント
    // スプライト初期化
    t_point = std::make_unique<Texture>("Data/Texture/GameOver/point.png");
    // スプライト
    s_point = std::make_unique<Sprite>();
    s_point->SetShaderResourceView(t_point->GetShaderResourceView(), t_point->GetWidth(), t_point->GetHeight());


    // マスクテクスチャの読み込み
    maskTexture = std::make_unique<Texture>("Data/Texture/dissolve_animation.png");
    dissolveThreshold = 1.0f;
    edgeThreshold = 0.2f; // 縁の閾値
    edgeColor = { 1, 0, 0, 1 }; // 縁の色
}

// 終了化
void SceneOver::Finalize()
{
}

// 更新処理
void SceneOver::Update(float elapsedTime)
{
    GamePad& gamePad = Input::Instance().GetGamePad();
    // アイコン選択処理
    if (gamePad.GetButtonDown() & GamePad::BTN_UP)
    {
        s_selection->Stop();        // SE停止 
        s_selection->Play(false);   // SE再生
        selectNum--;
    }
    if (gamePad.GetButtonDown() & GamePad::BTN_DOWN)
    {
        s_selection->Stop();        // SE停止 
        s_selection->Play(false);   // SE再生
        selectNum++;
    }
    if (selectNum > 2)selectNum = 0;
    if (selectNum < 0)selectNum = 2;
    // selectNumの値に応じてiconPosXの要素を設定
    for (int i = 0; i < 3; i++)
    {
        if (i == selectNum)
        {
            iconPosX[i] = 1075.0f;
        }
        else
        {
            iconPosX[i] = 1175.0f;
        }
    }

    if (gamePad.GetButtonDown() & GamePad::BTN_B)
    {
        switch (selectNum)
        {
        case OVER_100:

            SceneManager::Instance().IsSelect = false;
            SceneManager::Instance().IsNoneStage = true;
            SceneManager::Instance().ChangeScene(new SceneGame);
            break;
        case OVER_RE:
            StageManager::stageNo = 0;
            SceneManager::Instance().IsSelect = false;
            SceneManager::Instance().IsNoneStage = true;
            SceneManager::Instance().ChangeScene(new SceneGame);
            break;
        case OVER_TITLE:
            SceneManager::Instance().ChangeScene(new SceneTitle);
            break;
        }
    }


    //-------------------------------------------------------------------------------------------------------
    // ↓　この下はシェーダー関連
    //-------------------------------------------------------------------------------------------------------

    s_result->Update(1300.0f, 300.0f,
        static_cast<float>(t_result->GetWidth()), static_cast<float>(t_result->GetHeight()),
        0.0f, 0.0f,
        static_cast<float>(t_result->GetWidth()), static_cast<float>(t_result->GetHeight()),
        0.0f,
        1.0f, 1.0f, 1.0f, 1.0f);

    s_title->Update(iconPosX[OVER_TITLE], 910.0f,
        static_cast<float>(t_title->GetWidth()), static_cast<float>(t_title->GetHeight()),
        0.0f, 0.0f,
        static_cast<float>(t_title->GetWidth()), static_cast<float>(t_title->GetHeight()),
        0.0f,
        1.0f, 1.0f, 1.0f, 1.0f);

    s_restart->Update(iconPosX[OVER_RE], 755.0f,
        static_cast<float>(t_restart->GetWidth()), static_cast<float>(t_restart->GetHeight()),
        0.0f, 0.0f,
        static_cast<float>(t_restart->GetWidth()), static_cast<float>(t_restart->GetHeight()),
        0.0f,
        1.0f, 1.0f, 1.0f, 1.0f);

    s_high->Update(1125.0f, 430.0f,
        static_cast<float>(t_high->GetWidth()), static_cast<float>(t_high->GetHeight()),
        0.0f, 0.0f,
        static_cast<float>(t_high->GetWidth()), static_cast<float>(t_high->GetHeight()),
        0.0f,
        1.0f, 1.0f, 1.0f, 1.0f);

    s_100p->Update(iconPosX[OVER_100], 600.0f,
        static_cast<float>(t_100p->GetWidth()), static_cast<float>(t_100p->GetHeight()),
        0.0f, 0.0f,
        static_cast<float>(t_100p->GetWidth()), static_cast<float>(t_100p->GetHeight()),
        0.0f,
        1.0f, 1.0f, 1.0f, 1.0f);

    s_over->Update(235.0f, 130.0f,
        static_cast<float>(t_over->GetWidth()), static_cast<float>(t_over->GetHeight()),
        0.0f, 0.0f,
        static_cast<float>(t_over->GetWidth()), static_cast<float>(t_over->GetHeight()),
        0.0f,
        1.0f, 1.0f, 1.0f, 1.0f);

    s_back->Update(0.0f, 0.0f,
        static_cast<float>(t_back->GetWidth()), static_cast<float>(t_back->GetHeight()),
        0.0f, 0.0f,
        static_cast<float>(t_back->GetWidth()), static_cast<float>(t_back->GetHeight()),
        0.0f,
        1.0f, 1.0f, 1.0f, 1.0f);

    s_hamu->Update(130.0f, 385.0f,
        static_cast<float>(t_hamu->GetWidth()), static_cast<float>(t_hamu->GetHeight()),
        0.0f, 0.0f,
        static_cast<float>(t_hamu->GetWidth()), static_cast<float>(t_hamu->GetHeight()),
        0.0f,
        1.0f, 1.0f, 1.0f, 1.0f);

    s_point->Update(1320.0f, 0.0f,
        static_cast<float>(t_point->GetWidth()), static_cast<float>(t_point->GetHeight()),
        0.0f, 0.0f,
        static_cast<float>(t_point->GetWidth()), static_cast<float>(t_point->GetHeight()),
        0.0f,
        1.0f, 1.0f, 1.0f, 1.0f);

}

// 描画処理
void SceneOver::Render()
{
    Graphics& graphics = Graphics::Instance();
    ID3D11DeviceContext* dc = graphics.GetDeviceContext();
    ID3D11RenderTargetView* rtv = graphics.GetRenderTargetView();
    ID3D11DepthStencilView* dsv = graphics.GetDepthStencilView();

    // 画面クリア＆レンダーターゲット設定
    FLOAT color[] = { 0.0f, 0.0f, 0.5f, 1.0f };	// RGBA(0.0～1.0)
    dc->ClearRenderTargetView(rtv, color);
    dc->ClearDepthStencilView(dsv, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
    dc->OMSetRenderTargets(1, &rtv, dsv);

    // 描画処理
    RenderContext rc;
    rc.deviceContext = dc;

    // 2Dスプライト描画
    {
        SpriteShader* shader = graphics.GetShader(SpriteShaderId::Default);
        shader->Begin(rc);
        shader->Draw(rc, s_back.get());
        shader->Draw(rc, s_high.get());
        shader->Draw(rc, s_100p.get());
        shader->Draw(rc, s_over.get());
        shader->Draw(rc, s_hamu.get());
        shader->Draw(rc, s_point.get());
        shader->Draw(rc, s_result.get());
        shader->Draw(rc, s_title.get());
        shader->Draw(rc, s_restart.get());
        text_number->textOut(rc
            , Player::GetScore()
            , 1350.0f, 460.0f
            , 45.0f, 45.0f
            , 1.0f, 1.0f, 1.0f, 1.0f
        );
        shader->End(rc);
    }
}
