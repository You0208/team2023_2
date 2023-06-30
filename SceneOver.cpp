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

    sprite->Update(0.0f, 0.0f,
        100.0f, 100.0f,
        0.0f, 0.0f,
        static_cast<float>(texture->GetWidth()), static_cast<float>(texture->GetHeight()),
        0.0f,
        1.0f, 1.0f, 1.0f, 1.0f);

    sprite->Update(0.0f, 0.0f,
        Graphics::Instance().GetScreenWidth(), Graphics::Instance().GetScreenHeight(),
        0.0f, 0.0f,
        static_cast<float>(texture->GetWidth()), static_cast<float>(texture->GetHeight()),
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
        shader->Draw(rc, sprite.get());
        shader->End(rc);
    }
}
