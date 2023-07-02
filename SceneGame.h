#pragma once

#include <vector>
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

	// ��Q���Ə�Q���̓����蔻��
	void CollisionObsVsObs();

private:
	// 3D��Ԃ̕`��
	void Render3DScene();

	// �V���h�E�}�b�v�̕`��
	void RenderShadowmap();

	// �󕠃Q�[�W�̍X�V
	void UpdateHungerGage();

private:
	
	Player* player = nullptr;

	Sky* sky = nullptr;

	StageManager* stageManager = nullptr;

	CameraController* cameraController = nullptr;

	bool isPaused = false;//�|�[�Y

	Effect* hitEffect = nullptr;
	Effect* accelEffect = nullptr;

	std::unique_ptr<Texture>	texture_hungerGage;			// �󕠃Q�[�W�̃e�N�X�`��(��)
	std::unique_ptr<Texture>	texture_hungerGageFrame;	// �󕠃Q�[�W�̃t���[���̃e�N�X�`��
	std::unique_ptr<Sprite>		sprite_hungerGage;			// �󕠃Q�[�W
	std::unique_ptr<Sprite>		sprite_hungerGageFrame;		// �󕠃Q�[�W�̃t���[��
	std::unique_ptr<Sprite>		sprite_hungerGageBack;		// �󕠃Q�[�W�̔w�i
	//-------------------------------------------------------------------------------------------------------
	// ���@���̉��̓V�F�[�_�[�֘A
	//-------------------------------------------------------------------------------------------------------
	std::unique_ptr<Sprite>	sprite;
	std::unique_ptr<Texture> texture;

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
