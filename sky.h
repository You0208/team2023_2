#pragma once
#include "Graphics/Shader.h"
#include "Graphics/Model.h"

//プレイヤー
class Sky
{
public:
    Sky();
    ~Sky() {}

    //更新処理  
    void Update(float elapsedTime);

    // 描画処理
    void Draw(RenderContext rc, ModelShader* shader);

    // 位置更新
    void SetPosition(const DirectX::XMFLOAT3& position) { this->position = position; }

    //行列更新処理
    void UpdateTransform();
public:
    // モデルはsceneのrenderで呼び出すのでpublic
    std::unique_ptr<Model>  model = nullptr;       // モデル
    float space = 900;
private:
    DirectX::XMFLOAT3   position = { 0,0,0 };     // 位置
    DirectX::XMFLOAT3   angle = { 0,0,0 };     // 角度
    DirectX::XMFLOAT3   scale = { 1,1,1 };     // スケール
    DirectX::XMFLOAT3   velocity = { 0,0,0 };     // 速度
    DirectX::XMFLOAT4X4   transform = {
        1,0,0,0,
        0,1,0,0,
        0,0,1,0,
        0,0,0,1,
    };
    float   height = 2.0f;           // 高さ
    float   radius = 0.5f;           // 半径

    float   acceleration = 10.0f;          // 加速力
    float   moveSpeed = 50.0f;          // 移動速度
    float   maxMoveSpeed = 100.0f;          // 最大移動速度

    float   friction = 0.5f;           // 減速

    float   moveVecX = 0.0f;           // 移動方向ベクトル
    float   moveVecZ = 0.0f;           // 移動方向ベクトル

    int     health = 5;              // 体力
    int     maxHealth = 5;              // 最大体力
    float   invincibleTimer = 1.0f;           // 無敵時間

    // 回転速度
    float   turnSpeed = DirectX::XMConvertToRadians(720);
};

