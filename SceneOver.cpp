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
    t_high = std::make_unique<Texture>("Data/Texture/GameOver/highscore_point.png");
    // �X�v���C�g
    s_high = std::make_unique<Sprite>();
    s_high->SetShaderResourceView(t_high->GetShaderResourceView(), t_high->GetWidth(), t_high->GetHeight());

    // 100�|�C���g
    // �X�v���C�g������
    t_100p = std::make_unique<Texture>("Data/Texture/GameOver/100point_use.png");
    // �X�v���C�g
    s_100p = std::make_unique<Sprite>();
    s_100p->SetShaderResourceView(t_100p->GetShaderResourceView(), t_100p->GetWidth(), t_100p->GetHeight());

    // �G���h���X
    // �X�v���C�g������
    t_endles = std::make_unique<Texture>("Data/Texture/GameOver/endles.png");
    // �X�v���C�g
    s_endles = std::make_unique<Sprite>();
    s_endles->SetShaderResourceView(t_endles->GetShaderResourceView(), t_endles->GetWidth(), t_endles->GetHeight());

    // �I�[�o�[
    // �X�v���C�g������
    t_over = std::make_unique<Texture>("Data/Texture/GameOver/gameover.png");
    // �X�v���C�g
    s_over = std::make_unique<Sprite>();
    s_over->SetShaderResourceView(t_over->GetShaderResourceView(), t_over->GetWidth(), t_over->GetHeight());

    // �w�i
    // �X�v���C�g������
    t_back = std::make_unique<Texture>("Data/Texture/GameOver/back.png");
    // �X�v���C�g
    s_back = std::make_unique<Sprite>();
    s_back->SetShaderResourceView(t_back->GetShaderResourceView(), t_back->GetWidth(), t_back->GetHeight());

    // �n���X�^�[
    // �X�v���C�g������
    t_hamu = std::make_unique<Texture>("Data/Texture/GameOver/hamster.png");
    // �X�v���C�g
    s_hamu = std::make_unique<Sprite>();
    s_hamu->SetShaderResourceView(t_hamu->GetShaderResourceView(), t_hamu->GetWidth(), t_hamu->GetHeight());

    // �|�C���g
    // �X�v���C�g������
    t_point = std::make_unique<Texture>("Data/Texture/GameOver/point.png");
    // �X�v���C�g
    s_point = std::make_unique<Sprite>();
    s_point->SetShaderResourceView(t_point->GetShaderResourceView(), t_point->GetWidth(), t_point->GetHeight());


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

    s_high->Update(0.0f, 0.0f,
        static_cast<float>(t_high->GetWidth()), static_cast<float>(t_high->GetHeight()),
        0.0f, 0.0f,
        static_cast<float>(t_high->GetWidth()), static_cast<float>(t_high->GetHeight()),
        0.0f,
        1.0f, 1.0f, 1.0f, 1.0f);

    s_100p->Update(0.0f, 0.0f,
        static_cast<float>(t_100p->GetWidth()), static_cast<float>(t_100p->GetHeight()),
        0.0f, 0.0f,
        static_cast<float>(t_100p->GetWidth()), static_cast<float>(t_100p->GetHeight()),
        0.0f,
        1.0f, 1.0f, 1.0f, 1.0f);

    s_endles->Update(0.0f, 0.0f,
        static_cast<float>(t_endles->GetWidth()), static_cast<float>(t_endles->GetHeight()),
        0.0f, 0.0f,
        static_cast<float>(t_endles->GetWidth()), static_cast<float>(t_endles->GetHeight()),
        0.0f,
        1.0f, 1.0f, 1.0f, 1.0f);

    s_over->Update(0.0f, 0.0f,
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

    s_hamu->Update(0.0f, 0.0f,
        static_cast<float>(t_hamu->GetWidth()), static_cast<float>(t_hamu->GetHeight()),
        0.0f, 0.0f,
        static_cast<float>(t_hamu->GetWidth()), static_cast<float>(t_hamu->GetHeight()),
        0.0f,
        1.0f, 1.0f, 1.0f, 1.0f);

    s_point->Update(0.0f, 0.0f,
        static_cast<float>(t_point->GetWidth()), static_cast<float>(t_point->GetHeight()),
        0.0f, 0.0f,
        static_cast<float>(t_point->GetWidth()), static_cast<float>(t_point->GetHeight()),
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
        shader->Draw(rc, s_high.get());
        shader->Draw(rc, s_100p.get());
        shader->Draw(rc, s_endles.get());
        shader->Draw(rc, s_over.get());
        shader->Draw(rc, s_back.get());
        shader->Draw(rc, s_hamu.get());
        shader->Draw(rc, s_point.get());
        shader->End(rc);
    }
}
