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
    static constexpr float ScrollVelocityRate = 0.01f;          // スクロール速度補間係数

    // 各空腹レベルでのプレイヤーの最大速度
    static constexpr float MaxPlayerVelocity[3] =
    {
        60.0f,      // 空腹レベル：低
        50.0f,      // 空腹レベル：中
        20.0f       // 空腹レベル：高
    };
    // 各空腹レベルでのステージの最大スクロール速度
    static constexpr float MaxStageScrollVelocity[3] =
    {
        -100.0f,    // 空腹レベル：低
        -50.0f,     // 空腹レベル：中
        -20.0f      // 空腹レベル：高
    };
    // 各空腹レベルでのステージの最大スクロール速度
    static constexpr float MaxTerrainScrollVelocity[3] =
    {
        -100.0f,    // 空腹レベル：高
        -50.0f,     // 空腹レベル：中
        -20.0f      // 空腹レベル：低
    };

    // ステージが切り替わる境目
    static constexpr int StageChangeLine[Stage::StageMax - 1] =
    {
        10
    };

public:
    StageManager();
    ~StageManager();

    void DrawDebugGUI();

    // 更新処理
    void Update(Player* player, float elapsedTIme);

    // 描画処理
    void Draw(RenderContext rc, ModelShader* shader);

    // 障害物表示:シェーダー用
    void ObsDraw(RenderContext rc, ModelShader* shader);

    // ステージ登録
    void Register(Stage* stage);

    // 全削除
    void Clear();

    // ステージ生成
    void StageSpawn(DirectX::XMFLOAT3 position);

    // 地形生成
    void TerrainSpawn(DirectX::XMFLOAT3 position);

    // 加速処理
    void AddVelocity();

    // 生成したステージ数を返す
    int GetSpawnStageCount() { return BaseStage::GetSpawnStageCount() / Stage::StageSideMax; }

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
    void UpdataHorizontalVelocity(float elapsedFrame);

    // ステージの切り替え
    void ChangeStage();

public:
    bool IsStart = true;

    std::vector<BaseStage*>             stages;                         // ステージリスト
    // ステージのスクロール速度更新
    void UpdateScrollVelocity(DirectX::XMFLOAT3& ScrollVelocity,float maxVelocity,float rate);

private:
    // ステージデータ
    DirectX::XMFLOAT3 stageScrollVelocity = { 0.0f,0.0f ,-10.0f };      // 共通のスクロール速度のポインタ
    std::set<BaseStage*>                stageRemoves;                   // 削除リスト
    std::vector<DirectX::XMFLOAT3>      stagesSpawns;                   // 生成リスト(位置だけ持っている)

    // 地形データ
    DirectX::XMFLOAT3 terrainScrollVelocity = { 0.0f,0.0f ,-10.0f };    // 共通のスクロール速度のポインタ
    std::vector<BaseStage*>             terrains;                       // ステージリスト
    std::set<BaseStage*>                terrainRemoves;                 // 削除リスト
    std::vector<DirectX::XMFLOAT3>      terrainSpawns;                  // 生成リスト(位置だけ持っている)


    float moveVecX = 0.0f;                                              // 移動方向ベクトル
    float maxPlayerVelocity = 20.0f;                                    // プレイヤーの最大速度
    int   stageNo           = 0;                                        // 現在のステージ
                                                                        // ===== 非使用　後で使うかも？ =====
    float friction = 0.5f;                                              // 減速
    float acceleration = 10.0f;                                         // 加速力
};