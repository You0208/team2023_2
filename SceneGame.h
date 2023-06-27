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

// ゲームシーン
class SceneGame :public Scene
{
public:
	SceneGame() {}
	~SceneGame() override {}

	// 初期化
	void Initialize()override;

	// 終了化
	void Finalize()override;

	// 更新処理
	void Update(float elapsedTime)override;

	// 描画処理
	void Render()override;

	// 描画処理
	void DrawDebugParameter(DirectX::XMFLOAT4X4& transform, const char* label);

	// グリッド描画
	void DrawGrid(ID3D11DeviceContext* context, int subdivisions, float scale);

	// 障害物とプレイヤーの当たり判定
	void CollisionPlayerVsObs();

private:
	// 3D空間の描画
	void Render3DScene();

private:
	
	Player* player = nullptr;

	Sky* sky = nullptr;

	StageManager* stageManager = nullptr;

	CameraController* cameraController = nullptr;

	bool isPaused = false;//ポーズ

	Effect* hitEffect = nullptr;
	//-------------------------------------------------------------------------------------------------------
	// ↓　この下はシェーダー関連
	//-------------------------------------------------------------------------------------------------------
	std::unique_ptr<Sprite>	sprite;
	std::unique_ptr<Texture> texture;

	// UVスクロールデータ
	UVScrollData uvScrollData;

	// マスク画像
	std::unique_ptr<Texture> maskTexture;

	float dissolveThreshold;
	float edgeThreshold; // 縁の閾値
	DirectX::XMFLOAT4 edgeColor; // 縁の色

	//	色調補正情報
	ColorGradingData		colorGradingData;

	// ガウスフィルターデータ
	GaussianFilterData gaussianFilterData;
	std::unique_ptr<Sprite> gaussianBlurSprite;
};
