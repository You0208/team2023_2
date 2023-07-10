#pragma once

#include "Graphics/Model.h"
#include "Graphics/Sprite.h"
#include "Graphics/Texture.h"
#include "Audio/Audio.h"
#include "Scene.h"


// �^�C�g���V�[��
class SceneClear :public Scene
{
public:
    SceneClear() {}
    ~SceneClear()override {}

    // ������
    void Initialize()override;

    // �I����
    void Finalize()override;

    // �X�V����
    void Update(float elapsedTime)override;

    // �`�揈��
    void Render()override;

private:
    bool AddPointPerform();

private:
    // BGM
    std::unique_ptr<AudioSource> b_gameClear;
    // SE
    std::unique_ptr<AudioSource> s_choice;		// ���艹
    std::unique_ptr<AudioSource> s_selection;	// �I����

    std::unique_ptr<Sprite>	s_back;
    std::unique_ptr<Texture> t_back;

    std::unique_ptr<Sprite>	s_endles;
    std::unique_ptr<Texture> t_endles;

    std::unique_ptr<Sprite>	s_ham;
    std::unique_ptr<Texture> t_ham;

    std::unique_ptr<Sprite>	s_point;
    std::unique_ptr<Texture> t_point;

    std::unique_ptr<Sprite>	s_result;
    std::unique_ptr<Texture> t_result;

    std::unique_ptr<Sprite>	s_score;
    std::unique_ptr<Texture> t_score;

    std::unique_ptr<Sprite>	s_title;
    std::unique_ptr<Texture> t_title;

    std::unique_ptr<Sprite>	s_black;
    std::unique_ptr<Texture> t_black;

    std::unique_ptr<Sprite>	s_White;
    std::unique_ptr<Texture> t_White;

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
    DirectX::XMFLOAT4 ap_color{ 0.741f, 0.435f, 0.435f, 0.0f };;       // �ǉ��|�C���g�\���ʒu
    int addPointPerformState = AddPointPerformState::begin;

    float Theta = 0.0f;
    float HamuY = 400.0f;
    float time = 0;

    bool IsWhite = true;

    float iconPosX[2] = { 1200.0f,1200.0f };
    int selectNum = 0;

    bool IsNext = false;

    // UV�X�N���[���f�[�^
    UVScrollData uvScrollData;
    // �}�X�N�摜
    std::unique_ptr<Texture> maskTexture;

    float dissolveThreshold;
    float edgeThreshold; // ����臒l
    DirectX::XMFLOAT4 edgeColor; // ���̐F
};