#include "Graphics/Graphics.h"
#include "SceneLoading.h"
#include "SceneGame.h"
#include "SceneManager.h"
#include "SceneTitle.h"
#include "Input/Input.h"

// ������
void SceneTitle::Initialize()
{
    // �X�v���C�g������
    texture = std::make_unique<Texture>("Data/Texture/Title/black.png");
    // �X�v���C�g
    sprite = std::make_unique<Sprite>();
    sprite->SetShaderResourceView(texture->GetShaderResourceView(), texture->GetWidth(), texture->GetHeight());

    // �X�v���C�g������
    t_back = std::make_unique<Texture>("Data/Texture/Title/back.png");
    // �X�v���C�g
    s_back = std::make_unique<Sprite>();
    s_back->SetShaderResourceView(t_back->GetShaderResourceView(), t_back->GetWidth(), t_back->GetHeight());

    // �X�v���C�g������
    t_frame = std::make_unique<Texture>("Data/Texture/Title/frame.png");
    // �X�v���C�g
    s_frame = std::make_unique<Sprite>();
    s_frame->SetShaderResourceView(t_frame->GetShaderResourceView(), t_frame->GetWidth(), t_frame->GetHeight());

    // �X�v���C�g������
    t_hamu = std::make_unique<Texture>("Data/Texture/Title/hamster.png");
    // �X�v���C�g
    s_hamu = std::make_unique<Sprite>();
    s_hamu->SetShaderResourceView(t_hamu->GetShaderResourceView(), t_hamu->GetWidth(), t_hamu->GetHeight());

    // �X�v���C�g������
    t_logo = std::make_unique<Texture>("Data/Texture/Title/titlelogo.png");
    // �X�v���C�g
    s_logo = std::make_unique<Sprite>();
    s_logo->SetShaderResourceView(t_logo->GetShaderResourceView(), t_logo->GetWidth(), t_logo->GetHeight());

    // �X�v���C�g������
    t_start = std::make_unique<Texture>("Data/Texture/Title/start.png");
    // �X�v���C�g
    s_start = std::make_unique<Sprite>();
    s_start->SetShaderResourceView(t_start->GetShaderResourceView(), t_start->GetWidth(), t_start->GetHeight());

    // �}�X�N�e�N�X�`���̓ǂݍ���
    maskTexture = std::make_unique<Texture>("Data/Texture/dissolve.png");
    dissolveThreshold = 1.0f;
    edgeThreshold = 0.2f; // ����臒l
    edgeColor = { 1, 0, 0, 1 }; // ���̐F

    // �I�[�f�B�I������
    b_title = Audio::Instance().LoadAudioSource("Data/Audio/BGM/BGM_Title.wav");
    b_title->SetVolume(0.15f);
    b_title->Play(true);

    s_choice = Audio::Instance().LoadAudioSource("Data/Audio/SE/Choice.wav");
    s_choice->SetVolume(0.3f);
}

// �I����
void SceneTitle::Finalize()
{
    b_title->Stop();
}

// �X�V����
void SceneTitle::Update(float elapsedTime)
{
    GamePad& gamePad = Input::Instance().GetGamePad();

    // �����{�^������������Q�[���V�[���̐؂�ւ�
    // �Ȃɂ��{�^�����������烍�[�f�B���O�V�[��������ŃQ�[����ʂ֐؂�ւ�
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

    // �w�i
    s_back->Update(0.0f, 0.0f,
        Graphics::Instance().GetScreenWidth(), Graphics::Instance().GetScreenHeight(),
        0.0f, 0.0f,
        static_cast<float>(t_back->GetWidth()), static_cast<float>(t_back->GetHeight()),
        0.0f,
        1.0f, 1.0f, 1.0f, 1.0f);

    // �t���[��
    s_frame->Update(0.0f, 0.0f,
        Graphics::Instance().GetScreenWidth(), Graphics::Instance().GetScreenHeight(),
        0.0f, 0.0f,
        static_cast<float>(t_frame->GetWidth()), static_cast<float>(t_frame->GetHeight()),
        0.0f,
        1.0f, 1.0f, 1.0f, 1.0f);

    // �n��
    s_hamu->Update(1095.0f, HamuY,
        static_cast<float>(t_hamu->GetWidth()), static_cast<float>(t_hamu->GetHeight()),
        0.0f, 0.0f,
        static_cast<float>(t_hamu->GetWidth()), static_cast<float>(t_hamu->GetHeight()),
        0.0f,
        1.0f, 1.0f, 1.0f, 1.0f);

    // ���S
    s_logo->Update(0.0f, 0.0f,
        static_cast<float>(t_logo->GetWidth()), static_cast<float>(t_logo->GetHeight()),
        0.0f, 0.0f,
        static_cast<float>(t_logo->GetWidth()), static_cast<float>(t_logo->GetHeight()),
        0.0f,
        1.0f, 1.0f, 1.0f, 1.0f);

    // �X�^�[�g
    s_start->Update(110.0f, 700.0f,
        static_cast<float>(t_start->GetWidth()), static_cast<float>(t_start->GetHeight()),
        0.0f, 0.0f,
        static_cast<float>(t_start->GetWidth()), static_cast<float>(t_start->GetHeight()),
        0.0f,
        1.0f, 1.0f, 1.0f, Trans);

}

// �`�揈��
void SceneTitle::Render()
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
