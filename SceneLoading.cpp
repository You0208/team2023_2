#include "SceneLoading.h"
#include"Graphics/Graphics.h"
#include "SceneLoading.h"
#include "SceneManager.h"

// ������
void SceneLoading::Initialize()
{
    // �e�N�X�`����ǂݍ���
    texture = std::make_unique<Texture>("Data/Texture/Loading.png");
    // �X�v���C�g
    sprite = std::make_unique<Sprite>();
    sprite->SetShaderResourceView(texture->GetShaderResourceView(), texture->GetWidth(), texture->GetHeight());


    // �e�N�X�`����ǂݍ���
    t_black = std::make_unique<Texture>("Data/Texture/black.png");
    // �X�v���C�g
    s_black = std::make_unique<Sprite>();
    s_black->SetShaderResourceView(t_black->GetShaderResourceView(), t_black->GetWidth(), t_black->GetHeight());


    // �}�X�N�e�N�X�`���̓ǂݍ���
    maskTexture = std::make_unique<Texture>("Data/Texture/dissolve.png");
    dissolveThreshold = 1.0f;
    edgeThreshold = 0.2f; // ����臒l
    edgeColor = { 1, 0, 0, 1 }; // ���̐F

    // �X���b�h�J�n
    thread = new std::thread(LoadingThread, this);
}

// �I����
void SceneLoading::Finalize()
{
    // �X���b�h�I����
    if (thread != nullptr)
    {
        thread->join();
        delete thread;
        thread = nullptr;
    }
}

// �X�V����
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

        // ���̃V�[���̏���������������V�[����؂�ւ���
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

// �`�揈��
void SceneLoading::Render()
{
    Graphics& graphics = Graphics::Instance();
    ID3D11DeviceContext* dc = graphics.GetDeviceContext();
    ID3D11RenderTargetView* rtv = graphics.GetRenderTargetView();
    ID3D11DepthStencilView* dsv = graphics.GetDepthStencilView();

    // ��ʃN���A�������_�[�^�[�Q�b�g�ݒ�
    FLOAT color[] = { 0.0f, 0.0f, 0.0f, 1.0f };	// RGBA(0.0�`1.0)
    dc->ClearRenderTargetView(rtv, color);
    dc->ClearDepthStencilView(dsv, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
    dc->OMSetRenderTargets(1, &rtv, dsv);

    // �`�揈��
    RenderContext rc;
    rc.deviceContext = dc;

    // 2D�X�v���C�g�`��
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
    // COM�֘A�̏������ŃX���b�h���ɌĂԕK�v������
    CoInitialize(nullptr);

    // ���̃V�[���̏������s��
    scene->nextScene->Initialize();

    // �X���b�h���I���O��COM�֘A�̏I����
    CoUninitialize();

    // ���̃V�[���̏��������ݒ�
    scene->nextScene->SetReady();

}
