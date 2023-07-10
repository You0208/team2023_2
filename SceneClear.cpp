#include "Graphics/Graphics.h"
#include "SceneLoading.h"
#include "SceneGame.h"
#include "SceneManager.h"
#include "SceneClear.h"
#include "SceneTitle.h"
#include "Input/Input.h"

// 初期化
void SceneClear::Initialize()
{
    // オーディオ初期化
    b_gameClear = Audio::Instance().LoadAudioSource("Data/Audio/BGM/BGM_GameClear.wav");
    b_gameClear->SetVolume(0.2f);
    b_gameClear->Play(true);
    s_choice = Audio::Instance().LoadAudioSource("Data/Audio/SE/Choice.wav");
    s_choice->SetVolume(0.3f);
    s_selection = Audio::Instance().LoadAudioSource("Data/Audio/SE/Selection.wav");
    s_selection->SetVolume(1.0f);

    // クリア
    // スプライト初期化
    t_back = std::make_unique<Texture>("Data/Texture/Clear/back.png");
    // スプライト
    s_back = std::make_unique<Sprite>();
    s_back->SetShaderResourceView(t_back->GetShaderResourceView(), t_back->GetWidth(), t_back->GetHeight());

    // エンドレス
    // スプライト初期化
    t_endles = std::make_unique<Texture>("Data/Texture/Clear/endles.png");
    // スプライト
    s_endles = std::make_unique<Sprite>();
    s_endles->SetShaderResourceView(t_endles->GetShaderResourceView(), t_endles->GetWidth(), t_endles->GetHeight());

    // ハム
    // スプライト初期化
    t_ham = std::make_unique<Texture>("Data/Texture/Clear/hamster.png");
    // スプライト
    s_ham = std::make_unique<Sprite>();
    s_ham->SetShaderResourceView(t_ham->GetShaderResourceView(), t_ham->GetWidth(), t_ham->GetHeight());

    // ポイント
    // スプライト初期化
    t_point = std::make_unique<Texture>("Data/Texture/Clear/point.png");
    // スプライト
    s_point = std::make_unique<Sprite>();
    s_point->SetShaderResourceView(t_point->GetShaderResourceView(), t_point->GetWidth(), t_point->GetHeight());

    // リザルト
    // スプライト初期化
    t_result = std::make_unique<Texture>("Data/Texture/Clear/result.png");
    // スプライト
    s_result = std::make_unique<Sprite>();
    s_result->SetShaderResourceView(t_result->GetShaderResourceView(), t_result->GetWidth(), t_result->GetHeight());

    // スコア
    // スプライト初期化
    t_score = std::make_unique<Texture>("Data/Texture/Clear/score.png");
    // スプライト
    s_score = std::make_unique<Sprite>();
    s_score->SetShaderResourceView(t_score->GetShaderResourceView(), t_score->GetWidth(), t_score->GetHeight());

    // タイトル
    // スプライト初期化
    t_title = std::make_unique<Texture>("Data/Texture/Clear/title.png");
    // スプライト
    s_title = std::make_unique<Sprite>();
    s_title->SetShaderResourceView(t_title->GetShaderResourceView(), t_title->GetWidth(), t_title->GetHeight());

    // 黒
    // スプライト初期化
    t_black = std::make_unique<Texture>("Data/Texture/black.png");
    // スプライト
    s_black = std::make_unique<Sprite>();
    s_black->SetShaderResourceView(t_black->GetShaderResourceView(), t_black->GetWidth(), t_black->GetHeight());

    // 白
    // スプライト初期化
    t_White = std::make_unique<Texture>("Data/Texture/White.png");
    // スプライト
    s_White = std::make_unique<Sprite>();
    s_White->SetShaderResourceView(t_White->GetShaderResourceView(), t_White->GetWidth(), t_White->GetHeight());


    // マスクテクスチャの読み込み
    maskTexture = std::make_unique<Texture>("Data/Texture/dissolve.png");
    dissolveThreshold = 1.0f;
    edgeThreshold = 0.2f; // 縁の閾値
    edgeColor = { 1, 0, 0, 1 }; // 縁の色
}

// 終了化
void SceneClear::Finalize()
{
}

// 更新処理
void SceneClear::Update(float elapsedTime)
{
    if (!IsNext)dissolveThreshold -= 1.0 * elapsedTime;
    if (dissolveThreshold <= 0.0f) {
        dissolveThreshold = 0.0f;
        IsWhite = false;
    }
    if (IsNext)dissolveThreshold += 1.0 * elapsedTime;

    HamuY += cosf(Theta) * 1.0f;
    Theta += 0.01f;
    time += 60.0f * elapsedTime;

    if (time >= 60)
    {
        time = 0;
    }

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
    if (selectNum > 1)selectNum = 0;
    if (selectNum < 0)selectNum = 1;
    // selectNumの値に応じてiconPosXの要素を設定
    for (int i = 0; i < 2; i++)
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
        IsNext = true;
        s_choice->Play(false);
    }
    if (dissolveThreshold >= 1.0f)
    {
        switch (selectNum)
        {
        case 0:
            break;
        case 1:
            SceneManager::Instance().ChangeScene(new SceneTitle);
            break;
        }
    }

    //-------------------------------------------------------------------------------------------------------
    // ↓　この下はシェーダー関連
    //-------------------------------------------------------------------------------------------------------

    s_black->Update(0.0f, 0.0f,
        Graphics::Instance().GetScreenWidth(), Graphics::Instance().GetScreenHeight(),
        0.0f, 0.0f,
        static_cast<float>(t_black->GetWidth()), static_cast<float>(t_black->GetHeight()),
        0.0f,
        1.0f, 1.0f, 1.0f, 1.0f);

    s_White->Update(0.0f, 0.0f,
        Graphics::Instance().GetScreenWidth(), Graphics::Instance().GetScreenHeight(),
        0.0f, 0.0f,
        static_cast<float>(t_black->GetWidth()), static_cast<float>(t_black->GetHeight()),
        0.0f,
        1.0f, 1.0f, 1.0f, 1.0f);

    s_back->Update(0.0f, 0.0f,
        Graphics::Instance().GetScreenWidth(), Graphics::Instance().GetScreenHeight(),
        0.0f, 0.0f,
        static_cast<float>(t_back->GetWidth()), static_cast<float>(t_back->GetHeight()),
        0.0f,
        1.0f, 1.0f, 1.0f, 1.0f);

    s_endles->Update(iconPosX[0], 600.0f,
        static_cast<float>(t_endles->GetWidth()), static_cast<float>(t_endles->GetHeight()),
        0.0f, 0.0f,
        static_cast<float>(t_endles->GetWidth()), static_cast<float>(t_endles->GetHeight()),
        0.0f,
        1.0f, 1.0f, 1.0f, 1.0f);

    s_ham->Update(400.0f, HamuY,
        static_cast<float>(t_ham->GetWidth()), static_cast<float>(t_ham->GetHeight()),
        0.0f, 0.0f,
        static_cast<float>(t_ham->GetWidth()), static_cast<float>(t_ham->GetHeight()),
        0.0f,
        1.0f, 1.0f, 1.0f, 1.0f);

    s_point->Update(1320.0f, 0.0f,
        static_cast<float>(t_point->GetWidth()), static_cast<float>(t_point->GetHeight()),
        0.0f, 0.0f,
        static_cast<float>(t_point->GetWidth()), static_cast<float>(t_point->GetHeight()),
        0.0f,
        1.0f, 1.0f, 1.0f, 1.0f);

    s_result->Update(1300.0f, 300.0f,
        static_cast<float>(t_result->GetWidth()), static_cast<float>(t_result->GetHeight()),
        0.0f, 0.0f,
        static_cast<float>(t_result->GetWidth()), static_cast<float>(t_result->GetHeight()),
        0.0f,
        1.0f, 1.0f, 1.0f, 1.0f);
    
    s_score->Update(1125.0f, 430.0f,
        static_cast<float>(t_score->GetWidth()), static_cast<float>(t_score->GetHeight()),
        0.0f, 0.0f,
        static_cast<float>(t_score->GetWidth()), static_cast<float>(t_score->GetHeight()),
        0.0f,
        1.0f, 1.0f, 1.0f, 1.0f);

    s_title->Update(iconPosX[1], 755.0f,
        static_cast<float>(t_title->GetWidth()), static_cast<float>(t_title->GetHeight()),
        0.0f, 0.0f,
        static_cast<float>(t_title->GetWidth()), static_cast<float>(t_title->GetHeight()),
        0.0f,
        1.0f, 1.0f, 1.0f, 1.0f);

}

// 描画処理
void SceneClear::Render()
{
    Graphics& graphics = Graphics::Instance();
    ID3D11DeviceContext* dc = graphics.GetDeviceContext();
    ID3D11RenderTargetView* rtv = graphics.GetRenderTargetView();
    ID3D11DepthStencilView* dsv = graphics.GetDepthStencilView();

    // 画面クリア＆レンダーターゲット設定
    FLOAT color[] = { 0.0f, 0.0f, 0.5f, 1.0f };	// RGBA(0.0〜1.0)
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
        shader->Draw(rc, s_endles.get());
        shader->Draw(rc, s_ham.get());
        shader->Draw(rc, s_point.get());
        shader->Draw(rc, s_result.get());
        shader->Draw(rc, s_score.get());
        shader->Draw(rc, s_title.get());
        shader->End(rc);

        rc.maskData.maskTexture = maskTexture->GetShaderResourceView().Get();
        rc.maskData.dissolveThreshold = dissolveThreshold;
        SpriteShader* shader_mask = graphics.GetShader(SpriteShaderId::Mask);
        shader_mask->Begin(rc);
        shader_mask->Draw(rc, s_black.get());
        if(IsWhite)shader_mask->Draw(rc, s_White.get());
        shader_mask->End(rc);
    }
}
 