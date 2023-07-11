#include "Graphics/Graphics.h"
#include "SceneLoading.h"
#include "SceneGame.h"
#include "SceneManager.h"
#include "SceneTitle.h"
#include "Input/Input.h"

// 初期化
void SceneTitle::Initialize()
{
    // スプライト初期化
    texture = std::make_unique<Texture>("Data/Texture/Title/black.png");
    // スプライト
    sprite = std::make_unique<Sprite>();
    sprite->SetShaderResourceView(texture->GetShaderResourceView(), texture->GetWidth(), texture->GetHeight());

    // スプライト初期化
    t_back = std::make_unique<Texture>("Data/Texture/Title/back.png");
    // スプライト
    s_back = std::make_unique<Sprite>();
    s_back->SetShaderResourceView(t_back->GetShaderResourceView(), t_back->GetWidth(), t_back->GetHeight());

    // スプライト初期化
    t_frame = std::make_unique<Texture>("Data/Texture/Title/frame.png");
    // スプライト
    s_frame = std::make_unique<Sprite>();
    s_frame->SetShaderResourceView(t_frame->GetShaderResourceView(), t_frame->GetWidth(), t_frame->GetHeight());

    // スプライト初期化
    t_hamu = std::make_unique<Texture>("Data/Texture/Title/hamster.png");
    // スプライト
    s_hamu = std::make_unique<Sprite>();
    s_hamu->SetShaderResourceView(t_hamu->GetShaderResourceView(), t_hamu->GetWidth(), t_hamu->GetHeight());

    // スプライト初期化
    t_logo = std::make_unique<Texture>("Data/Texture/Title/titlelogo.png");
    // スプライト
    s_logo = std::make_unique<Sprite>();
    s_logo->SetShaderResourceView(t_logo->GetShaderResourceView(), t_logo->GetWidth(), t_logo->GetHeight());

    // スプライト初期化
    t_start = std::make_unique<Texture>("Data/Texture/Title/start.png");
    // スプライト
    s_start = std::make_unique<Sprite>();
    s_start->SetShaderResourceView(t_start->GetShaderResourceView(), t_start->GetWidth(), t_start->GetHeight());

    // マスクテクスチャの読み込み
    maskTexture = std::make_unique<Texture>("Data/Texture/dissolve.png");
    dissolveThreshold = 1.0f;
    edgeThreshold = 0.2f; // 縁の閾値
    edgeColor = { 1, 0, 0, 1 }; // 縁の色

    // オーディオ初期化
    b_title = Audio::Instance().LoadAudioSource("Data/Audio/BGM/BGM_Title.wav");
    b_title->SetVolume(0.15f);
    b_title->Play(true);

    s_choice = Audio::Instance().LoadAudioSource("Data/Audio/SE/Choice.wav");
    s_choice->SetVolume(0.3f);
}

// 終了化
void SceneTitle::Finalize()
{
    b_title->Stop();
}

// 更新処理
void SceneTitle::Update(float elapsedTime)
{
    GamePad& gamePad = Input::Instance().GetGamePad();

    // 何かボタンを押したらゲームシーンの切り替え
    // なにかボタンを押したらローディングシーンを挟んでゲーム画面へ切り替え
    const GamePadButton anyButton =
        GamePad::BTN_A
        | GamePad::BTN_B
        | GamePad::BTN_X
        | GamePad::BTN_Y
        ;
    if (gamePad.GetButtonDown() & anyButton)
    {
        s_choice->Play(false);
        Trans = 1.0f;
        next = true;
    }

    if (!next)
    {
        dissolveThreshold -= 1.0 * elapsedTime;
        if (dissolveThreshold <= 0.0f)dissolveThreshold = 0.0f;

        HamuY += cosf(Theta) * 1.0f;
        Theta += 0.01f;
        time += 60.0f * elapsedTime;

        if (time >= 60)
        {
            time = 0;
        }

        if (time <= 30)
        {
            Trans = 0.0f;
        }
        else
        {
            Trans = 1.0f;
        }
    }
    else
    {
        dissolveThreshold += 1.0 * elapsedTime;
        if (dissolveThreshold >= 1.0f) {
            SceneManager::Instance().IsSelect = true;
            SceneManager::Instance().IsNoneStage = true;
            SceneManager::Instance().ChangeScene(new SceneLoading(new SceneGame));
        }
    }

    sprite->Update(0.0f, 0.0f,
        Graphics::Instance().GetScreenWidth(), Graphics::Instance().GetScreenHeight(),
        0.0f, 0.0f,
        static_cast<float>(texture->GetWidth()), static_cast<float>(texture->GetHeight()),
        0.0f,
        1.0f, 1.0f, 1.0f, 1.0f);

    // 背景
    s_back->Update(0.0f, 0.0f,
        Graphics::Instance().GetScreenWidth(), Graphics::Instance().GetScreenHeight(),
        0.0f, 0.0f,
        static_cast<float>(t_back->GetWidth()), static_cast<float>(t_back->GetHeight()),
        0.0f,
        1.0f, 1.0f, 1.0f, 1.0f);

    // フレーム
    s_frame->Update(0.0f, 0.0f,
        Graphics::Instance().GetScreenWidth(), Graphics::Instance().GetScreenHeight(),
        0.0f, 0.0f,
        static_cast<float>(t_frame->GetWidth()), static_cast<float>(t_frame->GetHeight()),
        0.0f,
        1.0f, 1.0f, 1.0f, 1.0f);

    // ハム
    s_hamu->Update(1095.0f, HamuY,
        static_cast<float>(t_hamu->GetWidth()), static_cast<float>(t_hamu->GetHeight()),
        0.0f, 0.0f,
        static_cast<float>(t_hamu->GetWidth()), static_cast<float>(t_hamu->GetHeight()),
        0.0f,
        1.0f, 1.0f, 1.0f, 1.0f);

    // ロゴ
    s_logo->Update(0.0f, 0.0f,
        static_cast<float>(t_logo->GetWidth()), static_cast<float>(t_logo->GetHeight()),
        0.0f, 0.0f,
        static_cast<float>(t_logo->GetWidth()), static_cast<float>(t_logo->GetHeight()),
        0.0f,
        1.0f, 1.0f, 1.0f, 1.0f);

    // スタート
    s_start->Update(110.0f, 700.0f,
        static_cast<float>(t_start->GetWidth()), static_cast<float>(t_start->GetHeight()),
        0.0f, 0.0f,
        static_cast<float>(t_start->GetWidth()), static_cast<float>(t_start->GetHeight()),
        0.0f,
        1.0f, 1.0f, 1.0f, Trans);

}

// 描画処理
void SceneTitle::Render()
{
    Graphics& graphics = Graphics::Instance();
    ID3D11DeviceContext* dc = graphics.GetDeviceContext();
    ID3D11RenderTargetView* rtv = graphics.GetRenderTargetView();
    ID3D11DepthStencilView* dsv = graphics.GetDepthStencilView();

    // 画面クリア＆レンダーターゲット設定
    FLOAT color[] = { 0.0f, 0.0f, 0.0f, 1.0f };	// RGBA(0.0～1.0)
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
        shader->Draw(rc, s_frame.get());
        shader->Draw(rc, s_hamu.get());
        shader->Draw(rc, s_logo.get());
        shader->Draw(rc, s_start.get());
        //shader->Draw(rc, sprite.get());
        shader->End(rc);


        rc.maskData.maskTexture = maskTexture->GetShaderResourceView().Get();
        rc.maskData.dissolveThreshold = dissolveThreshold;
        SpriteShader* shader_mask = graphics.GetShader(SpriteShaderId::Mask);
        shader_mask->Begin(rc);
        shader_mask->Draw(rc, sprite.get());
        shader_mask->End(rc);
    }
}
