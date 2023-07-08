#pragma once

#include "Graphics/Model.h"
#include "Graphics/Sprite.h"
#include "Graphics/Texture.h"
#include "Audio/Audio.h"
#include "Scene.h"

// �^�C�g���V�[��
class SceneOver :public Scene
{
private:
    static constexpr float PointPositionX = 1600.0f;    // �ǉ��|�C���g�ʒu(X)
    static constexpr float PointPositionY = 30.0f;      // �ǉ��|�C���g�ʒu(Y)
    static  float AddPointMoveAmount;// �ǉ��|�C���g�ړ���

public:
    SceneOver() {}
    ~SceneOver()override {}

    // ������
    void Initialize()override;

    // �I����
    void Finalize()override;

    // �X�V����
    void Update(float elapsedTime)override;

    // �`�揈��
    void Render()override;

private:
    // �|�C���g�̉��Z(�|�C���g�����Z���ꂽ��ture��Ԃ�)
    bool AddPoint();
    // �ǉ��|�C���g���o(�I�������true��Ԃ�)
    bool AddPointPerform();

private:
    // BGM
    std::unique_ptr<AudioSource> b_gameOver;
    // SE
    std::unique_ptr<AudioSource> s_choice;		// ���艹
    std::unique_ptr<AudioSource> s_selection;	// �I����

    std::unique_ptr<Sprite>	s_high;
    std::unique_ptr<Texture> t_high;

    std::unique_ptr<Sprite>	s_100p;
    std::unique_ptr<Texture> t_100p;

    std::unique_ptr<Sprite>	s_over;
    std::unique_ptr<Texture> t_over;

    std::unique_ptr<Sprite>	s_back;
    std::unique_ptr<Texture> t_back;

    std::unique_ptr<Sprite>	s_hamu;
    std::unique_ptr<Texture> t_hamu;

    std::unique_ptr<Sprite>	s_point;
    std::unique_ptr<Texture> t_point;

    std::unique_ptr<Sprite>	s_result;
    std::unique_ptr<Texture> t_result;

    std::unique_ptr<Sprite>	s_title;
    std::unique_ptr<Texture> t_title;

    std::unique_ptr<Sprite>	s_restart;
    std::unique_ptr<Texture> t_restart;

    std::unique_ptr<Texture>	texture_fonts_number;		// �t�H���g�e�N�X�`��(�����̂�)
    std::unique_ptr<Text>		text_number;				// �t�H���g(�����̂�)

    enum AddPointPerformState
    {
        begin = 0,      // �����ݒ�
        FeadIn,         // �o��
        FeadOut,        // ����
        end,            // �I��
    };

    DirectX::XMFLOAT2 p_pos = { PointPositionX,PointPositionY };// �|�C���g�\���ʒu
    int addPoint = 0;                                           // �ǉ��|�C���g
    DirectX::XMFLOAT2 ap_pos{ PointPositionX,PointPositionY };  // �ǉ��|�C���g�\���ʒu
    DirectX::XMFLOAT4 ap_color{ 0.0f, 0.0f, 0.0f, 1.0f };       // �ǉ��|�C���g�\���ʒu
    int addPointPerformState = AddPointPerformState::begin;

    enum OverNum
    {
        OVER_100 = 0,
        OVER_RE,
        OVER_TITLE
    };
    float iconPosX[3] = { 1200.0f,1200.0f,1200.0f };
    int selectNum = 0;


    // UV�X�N���[���f�[�^
    UVScrollData uvScrollData;
    // �}�X�N�摜
    std::unique_ptr<Texture> maskTexture;

    float dissolveThreshold;
    float edgeThreshold; // ����臒l
    DirectX::XMFLOAT4 edgeColor; // ���̐F
};