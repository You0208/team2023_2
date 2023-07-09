#pragma once

#include "Graphics/Shader.h"
#include <vector>
#include "Player.h"
#include "Stage.h"
#include "Terrain.h"
#include <set>

// ステージマネージャー
class StageManager
{
private:
    static constexpr float ScrollVelocityRate = 0.01f;              // スクロール速度補間係数
    static constexpr float ScrollVelocityRate_ac = 0.001f;          // スクロール速度補間係数(加速状態)
    static constexpr float MaxVelocity = -300.0f;                   // Velocityの最大値
    static const int Gap = 2;                                       // プレイヤーの位置とステージを削除する位置の差
    static const int MaxBreakTime = 2;                                       // 

    // 各空腹レベルでのプレイヤーの最大速度
    static constexpr float MaxPlayerVelocity[3] =
    {
        90.0f,     // 空腹レベル：低
        60.0f,      // 空腹レベル：中
        20.0f       // 空腹レベル：高
    };
    // 各空腹レベルでのステージの最大スクロール速度
    static constexpr float MaxStageScrollVelocity[3] =
    {
        -150.0f,    // 空腹レベル：低
        -100.0f,    // 空腹レベル：中
        -75.0f      // 空腹レベル：高
    };
    // 各空腹レベルでの地形の最大スクロール速度
    static constexpr float MaxTerrainScrollVelocity[3] =
    {
        -150.0f,    // 空腹レベル：高
        -100.0f,    // 空腹レベル：中
        -75.0f      // 空腹レベル：低
    };

    // ステージが切り替わる境目
    static constexpr int StageChangeLine[Stage::StageMax] =
    {
        5,      // ステージ2切り替え
        5,      // ステージ3切り替え
        5,      // ステージ4切り替え
        5,      // ステージ5切り替え
        5,      // クリア
    };

    // 各ステージレベルでのスコアの常時加算量
    static constexpr float MaxAlwaysAddScore[Stage::StageMax + 1] =
    {
        1.0f,       // ステージ:1
        2.0f,       // ステージ:2
        3.0f,       // ステージ:3
        4.0f,       // ステージ:4
        5.0f,        // ステージ:5
        1.0f        // エンドレスモード
    };
    // 各空腹レベルでのスコアの常時加算量の倍率
    static constexpr float MaxAlwaysAddScoreMagnification[3] =
    {
        2.0f,       // 空腹レベル：低 
        1.0f,       // 空腹レベル：中 
        0.5f        // 空腹レベル：高 
    };
    // クリアボーナス
    static constexpr int StageClearcBonus[Stage::StageMax + 1] =
    {
        100,       // ステージ:1
        200,       // ステージ:2
        300,       // ステージ:3
        400,       // ステージ:4
        500,       // ステージ:5
        0,         // エンドレスモード(バグ防止)
    };

    struct SpawnData
    {
        DirectX::XMFLOAT3 position;     // 生成位置
        bool IsDepthSpawn;              // 生成原因
    };

public:
    StageManager();
    ~StageManager();

    void DrawDebugGUI();

    // 更新処理
    void Update(Player* player, float elapsedTIme);

    // セレクト画面での更新
    void StageSelectUpdate(float elapsedTIme);

    // 死亡時の更新
    void StageDeathUpdate(float elapsedTIme);

    // 描画処理
    void Draw(RenderContext rc, ModelShader* shader);

    // 障害物表示:シェーダー用
    void ObsDraw(RenderContext rc, ModelShader* shader);

    // ステージ登録
    void Register(Stage* stage);

    // 全削除
    void Clear();

    // ステージ生成
    void StageSpawn(SpawnData data);

    // 地形生成
    void TerrainSpawn(DirectX::XMFLOAT3 position);

    // 加速処理
    void AddVelocity(float addVelocity,float timer);

    // プレイヤーが超えたステージの数を返す
    int GetDoneStageNum() const{ return doneStageNum; }

    void setVelocityZ(int i) {  stageScrollVelocity.z = i; }

    float getVelocityZ() const { return stageScrollVelocity.z; }

    // 今のステージ番号を返す
    int GetStageNo() const { return stageNo; }

    // クリアフラグ取得
    static bool const GetIsClear() { return IsClear; }
    // エンドレスフラグ取得
    static bool const GetEndless() { return Endless; }

    // クリアフラグを折る
    static void FoldIsClear() { IsClear = false; }
    // エンドレスフラグを折る
    static void FoldEndless() { Endless = false; }

private:
    // ステージの更新
    void StageUpdate(float elapsedTIme);

    // 地形の更新
    void TerrainUpdate(float elapsedTIme);

    // 移動入力処理
    void InputMove(float elapsedTime);

    // 速度処理更新
    void UpdateVelocity(float elapsedTime,Player* player);

    // スティック入力値から移動ベクトルを取得
    DirectX::XMFLOAT3 GetMoveVec();

    // 水平速力更新処理
    void UpdataHorizontalVelocity(float elapsedFrame, Player* player);

    // BreakTime_Stateをセット
    void SetBreakTime_State();

    // 休憩時間更新
    void UpdateBreakTime(float elapsedFrame, Player* player);

    // doneStageNumの加算
    void AddDoneStageNum(float elapsedTIme);

    // スコアの更新(常時加算)
    void UpdateScore(Player* player,float elapsedTime);

public:
    bool IsStart = true;
    float VZ = 0;

    std::vector<BaseStage*>             stages;                         // ステージリスト
    // ステージのスクロール速度更新
    void UpdateScrollVelocity(DirectX::XMFLOAT3& ScrollVelocity,float maxVelocity,float rate);

    bool IsBreakTime = false;                                           // 休憩フラグ
    bool IsSpawnNone_Side = false;                                      // 何もないステージを生成するフラグ(サイド)
    bool IsSpawnNone_Depth = false;                                     // 何もないステージを生成するフラグ(奥行)
    static int   stageNo;                                               // 現在のステージ

    // デバッグのためにpublicにおいてる
    static bool IsClear;                                                // クリアフラグ
private:
    // ステージデータ
    DirectX::XMFLOAT3 stageScrollVelocity = { 0.0f,0.0f ,-10.0f };      // 共通のスクロール速度のポインタ
    std::set<BaseStage*>                stageRemoves;                   // 削除リスト
    std::vector<SpawnData>              stagesSpawns;                   // 生成リスト(位置だけ持っている)

    // 地形データ
    DirectX::XMFLOAT3 terrainScrollVelocity = { 0.0f,0.0f ,-10.0f };    // 共通のスクロール速度のポインタ
    std::vector<BaseStage*>             terrains;                       // ステージリスト
    std::set<BaseStage*>                terrainRemoves;                 // 削除リスト
    std::vector<DirectX::XMFLOAT3>      terrainSpawns;                  // 生成リスト(位置だけ持っている)

    float breakTimer = 0.0f;                                             // 休憩タイマー
    int breakTime = 0;                                                   // 休憩タイマー
    int breakTime_State = 0;                                             // ブレイクタイム開始するステージ
    int breakTime_End = 0;                                               // ブレイクタイム終了するステージ
    bool IsClearVerge = false;                                           // クリア目前フラグ
    static bool Endless;                                                 // エンドレスモードフラグ

    float moveVecX = 0.0f;                                              // 移動方向ベクトル
    float maxPlayerVelocity = 20.0f;                                    // プレイヤーの最大速度
    int doneStageNum        = 0;                                        // プレイヤーが超えたステージの数

   // ===== 非使用　後で使うかも？ =====
    float friction = 5.0f;                                              // 減速
    float acceleration = 10.0f;                                         // 加速力

    float scrollVelocityRate = 0.0f;                                    // スクロール速度補間係数
    float accelerationTimer = 0.0f;                                     // 加速タイマー(0以上のとき加速状態である)
};