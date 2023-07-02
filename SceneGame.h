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

	// 障害物と障害物の当たり判定
	void CollisionObsVsObs();

private:
	// 3D空間の描画
	void Render3DScene();

	// シャドウマップの描画
	void RenderShadowmap();

	// 空腹ゲージの更新
	void UpdateHungerGage();

private:
	
	Player* player = nullptr;

	Sky* sky = nullptr;

	StageManager* stageManager = nullptr;

	CameraController* cameraController = nullptr;

	bool isPaused = false;//ポーズ

	Effect* hitEffect = nullptr;
	Effect* accelEffect = nullptr;

	std::unique_ptr<Texture>	texture_hungerGage;			// 空腹ゲージのテクスチャ(白)
	std::unique_ptr<Texture>	texture_hungerGageFrame;	// 空腹ゲージのフレームのテクスチャ
	std::unique_ptr<Sprite>		sprite_hungerGage;			// 空腹ゲージ
	std::unique_ptr<Sprite>		sprite_hungerGageFrame;		// 空腹ゲージのフレーム
	std::unique_ptr<Sprite>		sprite_hungerGageBack;		// 空腹ゲージの背景
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

	// オフスクリーンレンダリング用描画ターゲット
	std::unique_ptr<RenderTarget> renderTarget;

	// シャドウマップ用情報
	Light* mainDirectionalLight = nullptr; // シャドウマップを生成する平行光源
	std::unique_ptr<DepthStencil> shadowmapDepthStencil; // シャドウマップ用深度ステンシルバッファ
	float shadowDrawRect = 100.0f; // シャドウマップに描画する範囲
	DirectX::XMFLOAT4X4 lightViewProjection; // ライトビュープロジェクション行列
	DirectX::XMFLOAT3 shadowColor = { 0.89f, 0.6f, 0.92f }; // 影の色
	float shadowBias = 0.001f; // 深度比較用のオフセット値

	// ポストプロセス
	std::unique_ptr<PostprocessingRenderer> postprocessingRenderer;
};
