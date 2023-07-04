#pragma once
#include "Graphics/Shader.h"
#include "Graphics/Model.h"
#include "Obstacle.h"

// ステージの基底クラス
class BaseStage
{
public:
    BaseStage() {};
    virtual ~BaseStage() {};

    virtual void DrawDebugGUI() = 0;

    // 初期化
    virtual void Initialize() = 0;

    // 更新処理
    virtual void Update(float elapsedTime) = 0;

    // 描画処理
    virtual void Draw(RenderContext rc, ModelShader* shader) = 0;

    void SetScrollVelocity(DirectX::XMFLOAT3* v) { scrollVelocity = v; };   // スクロール速度のポインタをセット
    void SetPosition(DirectX::XMFLOAT3 p) { position = p; }                 // 位置設定
    bool GetIsDestroy() { return isDestroy; }                               // 削除フラグ取得
    bool GetIsSpawn() { return isSpawn; }                                   // 生成フラグ取得
    DirectX::XMFLOAT3 GetSpawnPosition() { return spawnPosition; }          // 生成位置取得
    DirectX::XMFLOAT3* GetAddressOfVelocity() { return &velocity; }         // velocityのポインター取得
    DirectX::XMFLOAT3* GetPosition() { return &position; }

    static const int GetSpawnStageCount() { return SpawnStageCount; }               // ステージの生成数を返す
    static void clear();                                                           // 初期化
protected:
    // スクロール処理
    virtual void UpdateVelocity(float elapsedTime);

    //行列更新処理
    virtual void UpdateTransform();

    // ステージの生成
    virtual void StageSpawn();
    // 奥行のステージ生成
    bool DepthSpawn();
    // 左のステージ生成
    bool LeftSpawn();
    // 右のステージ生成
    bool RightSpawn();

    // ステージの削除
    void StageDelete();

public:
    std::unique_ptr<Model> model = nullptr;

    std::vector<Obstacle*> obstacles;
protected:
    int stageSideMax                = 1;	                    // ステージの最大数(左右)
    int stageDepthMax               = 1;	                    // ステージの最大数(奥行)
    DirectX::XMFLOAT3   position    = { 0.0f,0.0f,0.0f };       // 位置
    DirectX::XMFLOAT3   angle       = { 0.0f,0.0f,0.0f };       // 角度
    DirectX::XMFLOAT3   scale       = { 1.0f,1.0f,1.0f };       // スケール
    DirectX::XMFLOAT3   modelSize   = { 1.0f,1.0f,1.0f };       // モデルのサイズ
    DirectX::XMFLOAT3   velocity    = { 0.0f,0.0f,0.0f };       // 速度
    const DirectX::XMFLOAT3* scrollVelocity = nullptr;          // スクロール速度のポインタ
    DirectX::XMFLOAT4X4 transform   = {
        1,0,0,0,
        0,1,0,0,
        0,0,1,0,
        0,0,0,1,
    };

    // ステージ生成
    DirectX::XMFLOAT3 spawnPosition = { 0.0f,0.0f ,0.0f };      // ステージの生成位置
    bool isSpawn                    = false;                    // ステージ生成フラグ
    // ステージ削除
    bool isDestroy                  = false;                    // ステージ削除フラグ
    bool a[2] = {};

    static int SpawnStageCount;                                 // 生成したステージの数
};

