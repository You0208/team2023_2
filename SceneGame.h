#pragma once

#include <vector>
#include "Graphics/Model.h"
#include "Graphics/Sprite.h"
#include "Graphics/Texture.h"
#include "Light.h"
#include "CameraController.h"
#include "Player.h"
#include "Stage.h"
#include "Terrain.h"
#include "StageManager.h"
#include "Scene.h"
#include "Graphics/Texture.h"
#include "Graphics/RenderTarget.h"
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

private:
	// 3D��Ԃ̕`��
	void Render3DScene();

private:
	
	Player* player = nullptr;

	Sky* sky = nullptr;

	StageManager* stageManager = nullptr;

	CameraController* cameraController = nullptr;

	bool isPaused = false;//�|�[�Y

	Effect* hitEffect = nullptr;
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
};
