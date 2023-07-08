#pragma once

// シーン
class Scene
{
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
	static constexpr char* fileName = "Data/Save/HighScore.txt";	// 開くファイル名

	// ハイスコアの読み取り
	static void InputHighScore();

	// ハイスコアの書き込み
	static void OutputHighScore();

	// ハイスコアの更新
	static void UpdateHighScore(const int score);

	// ハイスコアのリセット(書き込みも行う)
	static void ResetHighScore();

private:
	bool	ready = false;
};
