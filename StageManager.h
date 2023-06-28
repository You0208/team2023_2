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
public:
    StageManager();
    ~StageManager();

    void DrawDebugGUI();

    // 更新処理
    void Update(Player* player, float elapsedTIme);

    // 描画処理
    void Draw(RenderContext rc, ModelShader* shader);

    // ステージ登録
    void Register(Stage* stage);

    // 全削除
    void Clear();

    // ステージ生成
    void StageSpawn(DirectX::XMFLOAT3 position);

    // 地形生成
    void TerrainSpawn(DirectX::XMFLOAT3 position);


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

private:
    // ステージデータ
    DirectX::XMFLOAT3 stageScrollVelocity = { 0.0f,0.0f ,-10.0f };      // 共通のスクロール速度のポインタ
    std::vector<BaseStage*>             stages;                         // ステージリスト
    std::set<BaseStage*>                stageRemoves;                   // 削除リスト
    std::vector<DirectX::XMFLOAT3>      stagesSpawns;                   // 生成リスト(位置だけ持っている)

    // 地形データ
    DirectX::XMFLOAT3 terrainScrollVelocity = { 0.0f,0.0f ,-10.0f };    // 共通のスクロール速度のポインタ
    std::vector<BaseStage*>             terrains;                       // ステージリスト
    std::set<BaseStage*>                terrainRemoves;                 // 削除リスト
    std::vector<DirectX::XMFLOAT3>      terrainSpawns;                  // 生成リスト(位置だけ持っている)


    float moveVecX = 0.0f;                                              // 移動方向ベクトル
    float maxMoveSpeed = 40.0f;                                         // 最大移動速度
    float friction = 0.5f;                                              // 減速
    float acceleration = 10.0f;                                         // 加速力
};