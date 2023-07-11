#include "Graphics/Graphics.h"
#include "SceneLoading.h"
#include "SceneGame.h"
#include "SceneManager.h"
#include "StageManager.h"
#include "SceneOver.h"
#include "SceneTitle.h"
#include "Input/Input.h"
#include "Player.h"
#include "Tool.h"
// ������
void SceneOver::Initialize()
{
    // �I�[�f�B�I������
    b_gameOver = Audio::Instance().LoadAudioSource("Data/Audio/BGM/BGM_GameOver.wav");
    b_gameOver->SetVolume(0.2f);
    b_gameOver->Play(false);
    s_choice = Audio::Instance().LoadAudioSource("Data/Audio/SE/Choice.wav");
    s_choice->SetVolume(0.3f);
    s_selection = Audio::Instance().LoadAudioSource("Data/Audio/SE/Selection.wav");
    s_selection->SetVolume(1.0f);

    // �t�H���g
    texture_fonts_number = std::make_unique<Texture>("Data/fonts/font7.png");
    text_number = std::make_unique<Text>();
    text_number->SetShaderResourceView(texture_fonts_number->GetShaderResourceView(),
        texture_fonts_number->GetWidth(), texture_fonts_number->GetHeight());

    // �|�C���g�̉��Z
    AddPoint();

    NotUseOVER_100 = (
        (StageManager::GetEndless())
        || (StageManager::stageNo == 0)
        || (Point < 100)
        );
    
    // �G���h���X���[�h�̎��̓��g���C�o���Ȃ�����
    NotUseOVER_RE = StageManager::GetEndless();

    selectNum = NotUseOVER_100 ? (NotUseOVER_RE ? 2 : 1) : 0;

    //ESC�����悤��
    SceneManager::Instance().NotFinish = false;
    //-------------------------------------------------------------------------------------------------------
    // ���@���̉��̓V�F�[�_�[�֘A
    //-------------------------------------------------------------------------------------------------------

    // ���X�^�[�g
    // �X�v���C�g������
    t_restart = std::make_unique<Texture>("Data/Texture/GameOver/restart.png");
    // �X�v���C�g
    s_restart = std::make_unique<Sprite>();
    s_restart->SetShaderResourceView(t_restart->GetShaderResourceView(), t_restart->GetWidth(), t_restart->GetHeight());


    // �^�C�g��
    // �X�v���C�g������
    t_title = std::make_unique<Texture>("Data/Texture/GameOver/title.png");
    // �X�v���C�g
    s_title = std::make_unique<Sprite>();
    s_title->SetShaderResourceView(t_title->GetShaderResourceView(), t_title->GetWidth(), t_title->GetHeight());
    
    // ���U���g
    // �X�v���C�g������
    t_result = std::make_unique<Texture>("Data/Texture/GameOver/result.png");
    // �X�v���C�g
    s_result = std::make_unique<Sprite>();
    s_result->SetShaderResourceView(t_result->GetShaderResourceView(), t_result->GetWidth(), t_result->GetHeight());


    // �X�R�A
    // �X�v���C�g������
    t_high = std::make_unique<Texture>("Data/Texture/GameOver/score.png");
    // �X�v���C�g
    s_high = std::make_unique<Sprite>();
    s_high->SetShaderResourceView(t_high->GetShaderResourceView(), t_high->GetWidth(), t_high->GetHeight());

    // �n�C�X�R�A
    // �X�v���C�g������
    t_HighScore = std::make_unique<Texture>("Data/Texture/highscore.png");
    // �X�v���C�g
    s_HighScore = std::make_unique<Sprite>();
    s_HighScore->SetShaderResourceView(t_HighScore->GetShaderResourceView(), t_HighScore->GetWidth(), t_HighScore->GetHeight());

    // 100�|�C���g
    // �X�v���C�g������
    t_100p = std::make_unique<Texture>("Data/Texture/GameOver/100point_use.png");
    // �X�v���C�g
    s_100p = std::make_unique<Sprite>();
    s_100p->SetShaderResourceView(t_100p->GetShaderResourceView(), t_100p->GetWidth(), t_100p->GetHeight());

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

    // ��
    // �X�v���C�g������
    t_black = std::make_unique<Texture>("Data/Texture/black.png");
    // �X�v���C�g
    s_black = std::make_unique<Sprite>();
    s_black->SetShaderResourceView(t_black->GetShaderResourceView(), t_black->GetWidth(), t_black->GetHeight());

    // �}�X�N�e�N�X�`���̓ǂݍ���
    maskTexture = std::make_unique<Texture>("Data/Texture/dissolve.png");
    dissolveThreshold = 1.0f;
    edgeThreshold = 0.2f; // ����臒l
    edgeColor = { 1, 0, 0, 1 }; // ���̐F
}

// �I����
void SceneOver::Finalize()
{
    scoreUpdate = false;    // �n�C�X�R�A�X�V�t���O��܂�
}

// �X�V����
void SceneOver::Update(float elapsedTime)
{
    //-------------------------------------------------------------------------------------------------------
 // ���@���̉��̓V�F�[�_�[�֘A
 //-------------------------------------------------------------------------------------------------------

    s_black->Update(0.0f, 0.0f,
        Graphics::Instance().GetScreenWidth(), Graphics::Instance().GetScreenHeight(),
        0.0f, 0.0f,
        static_cast<float>(t_black->GetWidth()), static_cast<float>(t_black->GetHeight()),
        0.0f,
        1.0f, 1.0f, 1.0f, 1.0f);

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
        //�@�F
        NotUseOVER_RE ? 0.5f : 1.0f,
        NotUseOVER_RE ? 0.5f : 1.0f,
        NotUseOVER_RE ? 0.5f : 1.0f,
        1.0f
    );

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
        //�@�F
        NotUseOVER_100 ? 0.5f : 1.0f,
        NotUseOVER_100 ? 0.5f : 1.0f,
        NotUseOVER_100 ? 0.5f : 1.0f,
        1.0f
    );

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

    s_point->Update(1920.0f - t_point->GetWidth(), 0.0f,
        static_cast<float>(t_point->GetWidth()), static_cast<float>(t_point->GetHeight()),
        0.0f, 0.0f,
        static_cast<float>(t_point->GetWidth()), static_cast<float>(t_point->GetHeight()),
        0.0f,
        1.0f, 1.0f, 1.0f, 1.0f);

    s_HighScore->Update(HighScorePoition.x, HighScorePoition.y,
        static_cast<float>(t_HighScore->GetWidth()), static_cast<float>(t_HighScore->GetHeight()),
        0.0f, 0.0f,
        static_cast<float>(t_HighScore->GetWidth()), static_cast<float>(t_HighScore->GetHeight()),
        0.0f,
        HighScoreColor.x, HighScoreColor.y, HighScoreColor.z, HighScoreColor.w);


    if(!isNext)dissolveThreshold -= 1.0 * elapsedTime;
    if (dissolveThreshold <= 0.0f)
    {
        dissolveThreshold = 0.0f;
        start = true;
    }
    if (isNext)dissolveThreshold += 1.0 * elapsedTime;
    if (!start)return;
    // �ǉ��|�C���g���o
    AddPointPerform();

    GamePad& gamePad = Input::Instance().GetGamePad();
    // �A�C�R���I������
    if (gamePad.GetButtonDown() & GamePad::BTN_UP && !isNext)
    {
        s_selection->Stop();        // SE��~ 
        s_selection->Play(false);   // SE�Đ�
        selectNum--;
    }
    if (gamePad.GetButtonDown() & GamePad::BTN_DOWN  && !isNext)
    {
        s_selection->Stop();        // SE��~ 
        s_selection->Play(false);   // SE�Đ�
        selectNum++;
    }

    int selectNumMax = 2;
    //int selectNumMin = 0;
    int selectNumMin = NotUseOVER_100 ? (NotUseOVER_RE ? 2 : 1) : 0;

    if (selectNum > selectNumMax)selectNum = selectNumMin;
    if (selectNum < selectNumMin)selectNum = selectNumMax;
    // selectNum�̒l�ɉ�����iconPosX�̗v�f��ݒ�
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
        s_choice->Stop();
        s_choice->Play(false);
        isNext = true;
    }
    if (dissolveThreshold >= 1.0f)
    {
        switch (selectNum)
        {
        case OVER_100:
            if(addPointPerformState != AddPointPerformState::end) Point += addPoint;

            Point -= 100;   // 100�|�C���g�g�p
            SceneManager::Instance().IsSelect = false;
            SceneManager::Instance().IsNoneStage = true;
            StageManager::FoldEndless();    // �G���h���X���[�h���͌ĂׂȂ����O�̂��߃G���h���X�t���O��܂�
            SceneManager::Instance().ChangeScene(new SceneGame);
            break;
        case OVER_RE:
            StageManager::stageNo = 0;
            StageManager::FoldEndless();    // �G���h���X���[�h���͌ĂׂȂ����O�̂��߃G���h���X�t���O��܂�
            SceneManager::Instance().IsSelect = false;
            SceneManager::Instance().IsNoneStage = true;
            SceneManager::Instance().ChangeScene(new SceneGame);
            break;
        case OVER_TITLE:
            StageManager::stageNo = 0;
            StageManager::FoldEndless();    // �G���h���X�t���O��܂�
            SceneManager::Instance().IsSelect = true;
            SceneManager::Instance().ChangeScene(new SceneTitle);
            break;
        }
    }

    if (scoreUpdate)HighscoreTime += 60.0f * elapsedTime;

    if (HighscoreTime >= 60)
    {
        HighscoreTime = 0;
    }

    if (HighscoreTime <= 30)
    {
        HighScoreColor.w = 0.0f;
    }
    else
    {
        HighScoreColor.w = 1.0f;
    }

 
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
        shader->Draw(rc, s_back.get());
        shader->Draw(rc, s_high.get());
        shader->Draw(rc, s_100p.get());
        shader->Draw(rc, s_over.get());
        shader->Draw(rc, s_hamu.get());
        shader->Draw(rc, s_point.get());
        shader->Draw(rc, s_result.get());
        shader->Draw(rc, s_title.get());
        shader->Draw(rc, s_restart.get());
        shader->Draw(rc, s_HighScore.get());

        // �X�R�A
        text_number->textOut(rc
            , Player::GetScore()
            , 1340.0f, 460.0f
            , 45.0f, 45.0f
            , 1.0f, 1.0f, 1.0f, 1.0f
        );
        // �n�C�X�R�A
        text_number->textOut(rc
            , HighScore
            , p_pos.x, 31.0f
            , 45.0f, 45.0f
            , 1.0f, 1.0f, 1.0f, 1.0f
        );
        // �|�C���g
        text_number->textOut(rc
            , Point
            , p_pos.x, p_pos.y
            , 45.0f, 45.0f
            , 1.0f, 1.0f, 1.0f, 1.0f
        );
        // �ǉ��|�C���g
        text_number->textOut(rc
            , addPoint
            , p_pos.x, ap_pos.y
            , 45.0f, 45.0f
            , ap_color.x, ap_color.y, ap_color.z, ap_color.w
        );
        shader->End(rc);

        rc.maskData.maskTexture = maskTexture->GetShaderResourceView().Get();
        rc.maskData.dissolveThreshold = dissolveThreshold;
        SpriteShader* shader_mask = graphics.GetShader(SpriteShaderId::Mask);
        shader_mask->Begin(rc);
        shader_mask->Draw(rc, s_black.get());
        shader_mask->End(rc);
    }
}

// �|�C���g�̉��Z
bool SceneOver::AddPoint()
{
    int add = Player::GetScore() / 10;
    if (add == 0) return false;
    return true;
}

// �ǉ��|�C���g���o
bool SceneOver::AddPointPerform()
{
    static float taget = p_pos.y + AddPointMoveAmount;  // �ړ�(�o��)����ʒu
    switch (addPointPerformState)
    {
    case SceneOver::begin:
        addPoint = Player::GetScore() / 10;
        taget = p_pos.y + AddPointMoveAmount;
        ap_pos.y = taget;
        ap_color.w = 0.0f;
        addPointPerformState = AddPointPerformState::FeadIn;
    case SceneOver::FeadIn:
        ap_color.w = lerp<float>(ap_color.w, 1.0f, rate);

        if((fabs(1.0f - ap_color.w) < 0.01f))
        {
            ap_pos.y = taget;
            ap_color.w = 1.0f;
            addPointPerformState = AddPointPerformState::FeadOut;
        }
        break;
    case SceneOver::FeadOut:
        ap_pos.y = lerp<float>(ap_pos.y, p_pos.y, rate);
        ap_color.w = lerp<float>(ap_color.w, 0.0f, rate);

        if ((fabs(p_pos.y - ap_pos.y) < 8.0f))
        {
            Point += addPoint;
            ap_pos.y = p_pos.y;
            ap_color.w = 0.0f;
            NotUseOVER_100 = (
                (StageManager::GetEndless())
                || (StageManager::stageNo == 0)
                || (Point < 100)
                );
            addPointPerformState = AddPointPerformState::end;
        }

        break;
    case SceneOver::end:
        //addPointPerformState = AddPointPerformState::begin;
        break;
    default:
        break;
    }

    return true;
}
