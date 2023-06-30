#include "Graphics/Graphics.h"
#include "SceneLoading.h"
#include "SceneGame.h"
#include "SceneManager.h"
#include "SceneOver.h"
#include "Input/Input.h"

// ������
void SceneOver::Initialize()
{
    // �X�v���C�g������
    texture = std::make_unique<Texture>("Data/Texture/Title.png");
    // �X�v���C�g
    sprite = std::make_unique<Sprite>();
    sprite->SetShaderResourceView(texture->GetShaderResourceView(), texture->GetWidth(), texture->GetHeight());
    // �}�X�N�e�N�X�`���̓ǂݍ���
    maskTexture = std::make_unique<Texture>("Data/Texture/dissolve_animation.png");
    dissolveThreshold = 1.0f;
    edgeThreshold = 0.2f; // ����臒l
    edgeColor = { 1, 0, 0, 1 }; // ���̐F
}

// �I����
void SceneOver::Finalize()
{
}

// �X�V����
void SceneOver::Update(float elapsedTime)
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

// �`�揈��
void SceneOver::Render()
{
    Graphics& graphics = Graphics::Instance();
    ID3D11DeviceContext* dc = graphics.GetDeviceContext();
    ID3D11RenderTargetView* rtv = graphics.GetRenderTargetView();
    ID3D11DepthStencilView* dsv = graphics.GetDepthStencilView();

    // ��ʃN���A�������_�[�^�[�Q�b�g�ݒ�
    FLOAT color[] = { 0.0f, 0.0f, 0.5f, 1.0f };	// RGBA(0.0�`1.0)
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
    }
}
