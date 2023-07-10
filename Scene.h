#pragma once

// シーン
class Scene
{
protected:
	// SceneOverとSceneClearの両方で使うのでSceneにおいている
	static constexpr float PointPositionX = 1524.0f;    // 追加ポイント位置(X)
	static constexpr float PointPositionY = 122.0f;      // 追加ポイント位置(Y)
	static  float AddPointMoveAmount;// 追加ポイント移動量
	static constexpr float rate = 0.005f;
public:
	Scene() {}
	virtual ~Scene() {}

	// 初期化
	virtual void Initialize() = 0;

	// 終了化
	virtual void Finalize() = 0;

	// 更新処理
	virtual void Update(float elapsedTime) = 0;

	// 描画処理
	virtual void Render() = 0;

	// 準備完了しているか
	bool IsReady() const { return ready; }

	// 準備完了設定
	void SetReady() { ready = true; }

protected:
	static int HighScore;											//	ハイスコア
	static int Point;												// ポイント
	static constexpr char* fileName = "Data/Save/Save.txt";	// 開くファイル名

	// ハイスコアの更新
	static void UpdateHighScore(const int score);

	// ハイスコアのリセット(書き込みも行う)
	static void ResetHighScore();
public:
	// セーブファイルの読み取り
	static void InputSave();

	// セーブファイルの書き込み
	static void OutputSave();

private:
	bool	ready = false;
};
