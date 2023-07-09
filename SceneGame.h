#pragma once

#include <vector>
#include <fstream>
#include <string>
#include <string>
#include "Graphics/Model.h"
#include "Graphics/Sprite.h"
#include "Graphics/Texture.h"
#include "CameraController.h"
#include "Player.h"
#include "Stage.h"
#include "Terrain.h"
#include "StageManager.h"
#include "Scene.h"
#include "Graphics/Texture.h"
#include "Graphics/RenderTarget.h"
#include "Graphics/DepthStencil.h"
#include "Light.h"
#include "PostprocessingRenderer.h"
#include "Effect.h"
#include "Obstacle.h"
#include "sky.h"
#include "Audio/Audio.h"

// �Q�[���V�[��
class SceneGame :public Scene
{
public:
	SceneGame() {}
	~SceneGame() override {}

	// ������
	void Initialize()override;

	// �I����
	void Finalize()override;

	// �X�V����
	void Update(float elapsedTime)override;

	// �`�揈��
	void Render()override;

	// �`�揈��
	void DrawDebugParameter(DirectX::XMFLOAT4X4& transform, const char* label);

	// �O���b�h�`��
	void DrawGrid(ID3D11DeviceContext* context, int subdivisions, float scale);

	// ��Q���ƃv���C���[�̓����蔻��
	void CollisionPlayerVsObs();

	// �Z���N�g���
	void SelectUpdate(float elapsedTime);

	// ���[��
	void RuleUpdate(float elapsedTime);

	// �J�ڏ���
	void TransUpdate(float elapsedTime);

	// ���S���o
	void DeathUpdate(float elapsedTime);

	// ���񂾏u�Ԃ̒l�ω�
	void DeathMoment();

	// �쎀���o
	void DidFromHunger(float elapsedTime);

	// ��Q���Ə�Q���̓����蔻��
	void CollisionObsVsObs();

private:
	// 3D��Ԃ̕`��
	void Render3DScene();

	// �V���h�E�}�b�v�̕`��
	void RenderShadowmap();

	void accelUpdate(float elapsedTime);

	// �󕠃Q�[�W�̍X�V
	void UpdateHungerGage();

	// �X�e�[�W���x���ŔX�V
	void UpdateStageUI();

private:	// �X�R�A�ۑ��pSceneTitle�Ɏ����Ă���
	int HighScore = 0;					// �ǂݍ��񂾃X�R�A
	std::ofstream write;				// �����o���p�ϐ�
	std::ifstream read;					// �ǂݏo���p�ϐ�
	static constexpr char* fileName = "Data/Save/HighScore.txt";	// �J���t�@�C����

	// �n�C�X�R�A�̓ǂݎ��
	void InputHighScore();

	// �n�C�X�R�A�̏�������
	void OutputHighScore();

	// �n�C�X�R�A�̍X�V
	void UpdateHighScore(Player* player)	{ HighScore = (std::max)(HighScore, player->GetScore()); }

	// �n�C�X�R�A�̃��Z�b�g(�������݂��s��)
	void ResetHighScore();

private:
	int DeathTimer = 0;
	bool accel = false;
	float accelFrame = 120.0f;
	float p_w = 0.0f;

	bool isTrans = false;// �J�ڒ���
	DirectX::XMFLOAT3 target;// �Z���N�g�p
	float range;// �Z���N�g�p
	float rotation;// �Z���N�g�p

	int fontNo = 4;	// �t�H���g�ԍ�
	DirectX::XMFLOAT2 text_size = { 50.0f,50.0f };
	DirectX::XMFLOAT2 text_pos = { 0.0f,105.0f };
	DirectX::XMFLOAT4 text_color = { 0.0f,1.0f,0.0f,1.0f };

	enum SelectNum
	{
		SELECT_PLAY = 0,
		SELECT_RULE,
		SELECT_FIN
	};
	float iconPosX[3] = { 1175.0f,1175.0f,1175.0f };
	int selectNum = 0;


	// ���[���p
	bool IsRule;
	bool ruleIn;//���[������
	bool ruleOut;//���[������

	// ���[���ʒu
	float rulePos = -1080;

	Player* player = nullptr;

	Sky* sky = nullptr;

	StageManager* stageManager = nullptr;

	CameraController* cameraController = nullptr;

	bool isPaused = false;//�|�[�Y
	DirectX::XMFLOAT2 StageUI_Position = { 1920.0f ,0.0f};						// �X�e�[�W���x���̊Ŕ̍��W

	Effect* hitEffect = nullptr;
	Effect* accelEffect = nullptr;

	// BGM
	std::unique_ptr<AudioSource> b_game;
	std::unique_ptr<AudioSource> b_select;

	// SE
	std::unique_ptr<AudioSource> s_speed;		// ������
	std::unique_ptr<AudioSource> s_heal;		// �󕠃Q�[�W������
	std::unique_ptr<AudioSource> s_clash;		// �Փˉ�
	std::unique_ptr<AudioSource> s_choice;		// ���艹
	std::unique_ptr<AudioSource> s_selection;	// �I����

	
	//-------------------------------------------------------------------------------------------------------
	// ���@���̉��̓V�F�[�_�[�֘A
	//-------------------------------------------------------------------------------------------------------

	std::unique_ptr<Texture>	texture_hungerGage;			// �󕠃Q�[�W�̃e�N�X�`��(��)
	std::unique_ptr<Texture>	texture_hungerGageFrame;	// �󕠃Q�[�W�̃t���[���̃e�N�X�`��
	std::unique_ptr<Texture>	texture_StageUI;			// �X�e�[�W���x���̊Ŕ̃e�N�X�`��
	std::unique_ptr<Sprite>		sprite_hungerGage;			// �󕠃Q�[�W
	std::unique_ptr<Sprite>		sprite_hungerGageFrame;		// �󕠃Q�[�W�̃t���[��
	std::unique_ptr<Sprite>		sprite_hungerGageBack;		// �󕠃Q�[�W�̔w�i
	std::unique_ptr<Sprite>		sprite_StageUI;				// �X�e�[�W���x���̊Ŕ�
	std::unique_ptr<Texture>	texture_fonts[7];			// �t�H���g�e�N�X�`��
	std::unique_ptr<Text>		text[7];					// �t�H���g
	std::unique_ptr<Texture>	texture_fonts_number;		// �t�H���g�e�N�X�`��(�����̂�)
	std::unique_ptr<Text>		text_number;				// �t�H���g(�����̂�)

	std::unique_ptr<Sprite>	sprite;
	std::unique_ptr<Texture> texture;

	std::unique_ptr<Sprite>	sprite_line;
	std::unique_ptr<Texture> texture_line;

	std::unique_ptr<Sprite>	s_finish;
	std::unique_ptr<Texture> t_finish;

	std::unique_ptr<Sprite>	s_play;
	std::unique_ptr<Texture> t_play;

	std::unique_ptr<Sprite>	s_rulu;
	std::unique_ptr<Texture> t_rulu;

	std::unique_ptr<Sprite>	s_select;
	std::unique_ptr<Texture> t_select;

	std::unique_ptr<Sprite>	s_score;
	std::unique_ptr<Texture> t_score;

	std::unique_ptr<Sprite>	s_black;
	std::unique_ptr<Texture> t_black;

	// UV�X�N���[���f�[�^
	UVScrollData uvScrollData;

	// �}�X�N�摜
	std::unique_ptr<Texture> maskTexture;

	float dissolveThreshold;
	float edgeThreshold; // ����臒l
	DirectX::XMFLOAT4 edgeColor; // ���̐F

	//	�F���␳���
	ColorGradingData		colorGradingData;

	// �K�E�X�t�B���^�[�f�[�^
	GaussianFilterData gaussianFilterData;
	std::unique_ptr<Sprite> gaussianBlurSprite;

	// �I�t�X�N���[�������_�����O�p�`��^�[�Q�b�g
	std::unique_ptr<RenderTarget> renderTarget;

	// �V���h�E�}�b�v�p���
	Light* mainDirectionalLight = nullptr; // �V���h�E�}�b�v�𐶐����镽�s����
	std::unique_ptr<DepthStencil> shadowmapDepthStencil; // �V���h�E�}�b�v�p�[�x�X�e���V���o�b�t�@
	float shadowDrawRect = 100.0f; // �V���h�E�}�b�v�ɕ`�悷��͈�
	DirectX::XMFLOAT4X4 lightViewProjection; // ���C�g�r���[�v���W�F�N�V�����s��
	DirectX::XMFLOAT3 shadowColor = { 0.89f, 0.6f, 0.92f }; // �e�̐F
	float shadowBias = 0.001f; // �[�x��r�p�̃I�t�Z�b�g�l

	// �|�X�g�v���Z�X
	std::unique_ptr<PostprocessingRenderer> postprocessingRenderer;
};
