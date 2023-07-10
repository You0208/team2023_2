#include "SceneLoading.h"
#include"Graphics/Graphics.h"
#include "SceneLoading.h"
#include "SceneManager.h"

// 初期化
void SceneLoading::Initialize()
{
    // テクスチャを読み込む
    texture = std::make_unique<Texture>("Data/Texture/Loading.png");
    // スプライト
    sprite = std::make_unique<Sprite>();
    sprite->SetShaderResourceView(texture->GetShaderResourceView(), texture->GetWidth(), texture->GetHeight());


    // テクスチャを読み込む
    t_black = std::make_unique<Texture>("Data/Texture/black.png");
    // スプライト
    s_black = std::make_unique<Sprite>();
    s_black->SetShaderResourceView(t_black->GetShaderResourceView(), t_black->GetWidth(), t_black->GetHeight());


    // マスクテクスチャの読み込み
    maskTexture = std::make_unique<Texture>("Data/Texture/dissolve.png");
    dissolveThreshold = 1.0f;
    edgeThreshold = 0.2f; // 縁の閾値
    edgeColor = { 1, 0, 0, 1 }; // 縁の色

    // スレッド開始
    thread = new std::thread(LoadingThread, this);
}

// 終了化
void SceneLoading::Finalize()
{
    // スレッド終了化
    if (thread != nullptr)
    {
        thread->join();
        delete thread;
        thread = nullptr;
    }
}

// 更新処理
void SceneLoading::Update(float elapsedTime)
{
    constexpr float speed = 180;
    if (!next) {
        timer++;
        dissolveThreshold -= 1.0 * elapsedTime;
        if (dissolveThreshold <= 0.0f)dissolveThreshold = 0.0f;

        if (timer % 300 == 0)
        {
            p_w += 1920;
            if (p_w > 5760)
            {
                p_w = 0.0f;
            }
        }

        // 次のシーンの準備が完了したらシーンを切り替える
        if (nextScene->IsReady())
        {
            if(timer>=1000)
            next = true;
        }
    }
    else
    {
        dissolveThreshold += 1.0 * elapsedTime;
        if (dissolveThreshold >= 1.0f)
        {
            SceneManager::Instance().ChangeScene(nextScene);
            nextScene = nullptr;
        }
    }

    sprite->Update(0.0f, 0.0f,
        Graphics::Instance().GetScreenWidth(), Graphics::Instance().GetScreenHeight(),
        p_w, 0.0f,
        1920, static_cast<float>(texture->GetHeight()), 
        angle,
        1.0f, 1.0f, 1.0f, 1.0f);

    s_black->Update(0.0f, 0.0f,
        Graphics::Instance().GetScreenWidth(), Graphics::Instance().GetScreenHeight(),
        p_w, 0.0f,
        1920,static_cast<float>(t_black->GetHeight()),
        angle,
        1.0f, 1.0f, 1.0f, 1.0f);
}

// 描画処理
void SceneLoading::Render()
{
    Graphics& graphics = Graphics::Instance();
    ID3D11DeviceContext* dc = graphics.GetDeviceContext();
    ID3D11RenderTargetView* rtv = graphics.GetRenderTargetView();
    ID3D11DepthStencilView* dsv = graphics.GetDepthStencilView();

    // 画面クリア＆レンダーターゲット設定
    FLOAT color[] = { 0.0f, 0.0f, 0.0f, 1.0f };	// RGBA(0.0〜1.0)
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

        rc.maskData.maskTexture = maskTexture->GetShaderResourceView().Get();
        rc.maskData.dissolveThreshold = dissolveThreshold;
        SpriteShader* shader_mask = graphics.GetShader(SpriteShaderId::Mask);
        shader_mask->Begin(rc);
        shader_mask->Draw(rc, s_black.get());
        shader_mask->End(rc);
    }
}

void SceneLoading::LoadingThread(SceneLoading* scene)
{
    // COM関連の初期化でスレッド毎に呼ぶ必要がある
    CoInitialize(nullptr);

    // 次のシーンの初期を行う
    scene->nextScene->Initialize();

    // スレッドが終わる前にCOM関連の終了化
    CoUninitialize();

    // 次のシーンの準備完了設定
    scene->nextScene->SetReady();

}
