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

	// セレクト画面
	void SelectUpdate(float elapsedTime);

	// ルール
	void RuleUpdate(float elapsedTime);

	// 遷移処理
	void TransUpdate(float elapsedTime);

	// 死亡演出
	void DeathUpdate(float elapsedTime);

	// 死んだ瞬間の値変化
	void DeathMoment();

	// 餓死演出
	void DidFromHunger(float elapsedTime);

	// 障害物と障害物の当たり判定
	void CollisionObsVsObs();

private:
	// 3D空間の描画
	void Render3DScene();

	// シャドウマップの描画
	void RenderShadowmap();

	void accelUpdate(float elapsedTime);

	// 空腹ゲージの更新
	void UpdateHungerGage();

	// ステージレベル看板更新
	void UpdateStageUI();

private:	// スコア保存用SceneTitleに持っていく
	int HighScore = 0;					// 読み込んだスコア
	std::ofstream write;				// 書き出し用変数
	std::ifstream read;					// 読み出し用変数
	static constexpr char* fileName = "Data/Save/HighScore.txt";	// 開くファイル名

	// ハイスコアの読み取り
	void InputHighScore();

	// ハイスコアの書き込み
	void OutputHighScore();

	// ハイスコアの更新
	void UpdateHighScore(Player* player)	{ HighScore = (std::max)(HighScore, player->GetScore()); }

	// ハイスコアのリセット(書き込みも行う)
	void ResetHighScore();

private:
	int DeathTimer = 0;
	bool accel = false;
	float accelFrame = 120.0f;
	float p_w = 0.0f;

	bool isTrans = false;// 遷移中か
	DirectX::XMFLOAT3 target;// セレクト用
	float range;// セレクト用
	float rotation;// セレクト用

	int fontNo = 4;	// フォント番号
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


	// ルール用
	bool IsRule;
	bool ruleIn;//ルール入場
	bool ruleOut;//ルール入場

	// ルール位置
	float rulePos = -1080;

	Player* player = nullptr;

	Sky* sky = nullptr;

	StageManager* stageManager = nullptr;

	CameraController* cameraController = nullptr;

	bool isPaused = false;//ポーズ
	DirectX::XMFLOAT2 StageUI_Position = { 1920.0f ,0.0f};						// ステージレベルの看板の座標

	Effect* hitEffect = nullptr;
	Effect* accelEffect = nullptr;

	// BGM
	std::unique_ptr<AudioSource> b_game;
	std::unique_ptr<AudioSource> b_select;

	// SE
	std::unique_ptr<AudioSource> s_speed;		// 加速音
	std::unique_ptr<AudioSource> s_heal;		// 空腹ゲージ増加音
	std::unique_ptr<AudioSource> s_clash;		// 衝突音
	std::unique_ptr<AudioSource> s_choice;		// 決定音
	std::unique_ptr<AudioSource> s_selection;	// 選択音

	
	//-------------------------------------------------------------------------------------------------------
	// ↓　この下はシェーダー関連
	//-------------------------------------------------------------------------------------------------------

	std::unique_ptr<Texture>	texture_hungerGage;			// 空腹ゲージのテクスチャ(白)
	std::unique_ptr<Texture>	texture_hungerGageFrame;	// 空腹ゲージのフレームのテクスチャ
	std::unique_ptr<Texture>	texture_StageUI;			// ステージレベルの看板のテクスチャ
	std::unique_ptr<Sprite>		sprite_hungerGage;			// 空腹ゲージ
	std::unique_ptr<Sprite>		sprite_hungerGageFrame;		// 空腹ゲージのフレーム
	std::unique_ptr<Sprite>		sprite_hungerGageBack;		// 空腹ゲージの背景
	std::unique_ptr<Sprite>		sprite_StageUI;				// ステージレベルの看板
	std::unique_ptr<Texture>	texture_fonts[7];			// フォントテクスチャ
	std::unique_ptr<Text>		text[7];					// フォント
	std::unique_ptr<Texture>	texture_fonts_number;		// フォントテクスチャ(数字のみ)
	std::unique_ptr<Text>		text_number;				// フォント(数字のみ)

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
