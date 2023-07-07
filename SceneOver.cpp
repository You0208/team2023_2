#include "Graphics/Graphics.h"
#include "SceneLoading.h"
#include "SceneGame.h"
#include "SceneManager.h"
#include "SceneOver.h"
#include "Input/Input.h"

// 初期化
void SceneOver::Initialize()
{
    // スプライト初期化
    texture = std::make_unique<Texture>("Data/Texture/Title.png");
    // スプライト
    sprite = std::make_unique<Sprite>();
    sprite->SetShaderResourceView(texture->GetShaderResourceView(), texture->GetWidth(), texture->GetHeight());

    // ゲームオーバー
    // スプライト初期化
    t_over = std::make_unique<Texture>("Data/Texture/Title.png");
    // スプライト
    s_over = std::make_unique<Sprite>();
    s_over->SetShaderResourceView(t_over->GetShaderResourceView(), t_over->GetWidth(), t_over->GetHeight());

    // 戻る
    // スプライト初期化
    t_back = std::make_unique<Texture>("Data/Texture/Title.png");
    // スプライト
    s_back = std::make_unique<Sprite>();
    s_back->SetShaderResourceView(t_back->GetShaderResourceView(), t_back->GetWidth(), t_back->GetHeight());

    // ハム
    // スプライト初期化
    t_hamu = std::make_unique<Texture>("Data/Texture/Title.png");
    // スプライト
    s_hamu = std::make_unique<Sprite>();
    s_hamu->SetShaderResourceView(t_hamu->GetShaderResourceView(), t_hamu->GetWidth(), t_hamu->GetHeight());

    // ハム
    // スプライト初期化
    t_point = std::make_unique<Texture>("Data/Texture/Title.png");
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
        SceneManager::Instance().IsNoneStage = true;
        SceneManager::Instance().ChangeScene(new SceneGame);
    }

    s_over->Update(0.0f, 0.0f,
        Graphics::Instance().GetScreenWidth(), Graphics::Instance().GetScreenHeight(),
        0.0f, 0.0f,
        static_cast<float>(t_over->GetWidth()), static_cast<float>(t_over->GetHeight()),
        0.0f,
        1.0f, 1.0f, 1.0f, 1.0f);

    s_back->Update(0.0f, 0.0f,
        Graphics::Instance().GetScreenWidth(), Graphics::Instance().GetScreenHeight(),
        0.0f, 0.0f,
        static_cast<float>(t_back->GetWidth()), static_cast<float>(t_back->GetHeight()),
        0.0f,
        1.0f, 1.0f, 1.0f, 1.0f);

    s_hamu->Update(0.0f, 0.0f,
        Graphics::Instance().GetScreenWidth(), Graphics::Instance().GetScreenHeight(),
        0.0f, 0.0f,
        static_cast<float>(t_hamu->GetWidth()), static_cast<float>(t_hamu->GetHeight()),
        0.0f,
        1.0f, 1.0f, 1.0f, 1.0f);

    s_point->Update(0.0f, 0.0f,
        Graphics::Instance().GetScreenWidth(), Graphics::Instance().GetScreenHeight(),
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
        shader->Draw(rc, s_over.get());
        shader->Draw(rc, s_back.get());
        shader->Draw(rc, s_hamu.get());
        shader->Draw(rc, s_point.get());
        shader->End(rc);
    }
}
