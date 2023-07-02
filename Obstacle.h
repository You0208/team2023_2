#pragma once
#include <vector>
#include "graphics/shader.h"
#include "graphics/model.h"

enum TYPE
{
    CYLINDER,
    CYLINDERS,
    ITEMS,
    GATE,
};

enum HIT_CHECK_TYPE
{
    ACTIVE,     // 積極的に当たり判定をとる
    DEACTIVE,   // 非積極的に当たり判定をとる
    NOT         // 当たり判定をとらない
};

// 障害物（基底クラス）
class Obstacle 
{
public:
    Obstacle(){}

    ~Obstacle() {}

    // 描画処理
    void Draw(RenderContext rc, ModelShader* shader) ;

    // 更新処理
    virtual void Update(float elapsedTime);

    //デバッグGUI描画
    void DrawDebugGUI();

    //行列更新処理
    void UpdateTransform();

    // 位置取得
    const DirectX::XMFLOAT3& GetPosition() const { return position; }

    // 位置設定
    void SetPosition(DirectX::XMFLOAT3 p)  { position = p; }
    void SetOriginPosition(DirectX::XMFLOAT3* p)  { OriginPosition = p; }

    // 半径取得
    float GetRadius() const { return radius; }

    // 高さ取得
    float GetHeight() const { return height; }

    // アイテム取得演出
    void GetItem();

    // == 追加した関数(この文はあとで削除する) ==
    void SetScrollVelocity(DirectX::XMFLOAT3* ScrollVelocity) { scrollVelocity = ScrollVelocity; }

private:
    // 旋回処理
    void Turn(float elapsedtime, float vx, float vz, float speed);

    // 速度処理更新
    void UpdateVelocity(float elapsedTime);

    // 速度の追加更新
    virtual void UpdataAdditionVelocity(float elapsedFrame) {}

    // 移動更新処理
    void UpdateMove(float elapsedTime);

    // デバッグプリミティブ描画
    virtual void DrawDebugPrimitive() {};
public:
    // モデルは呼び出すのでpublic
    std::unique_ptr<Model>  model       =    nullptr;        // モデル

    int score = 0;
    int hungerPoint = 0;
    int Type = 0;
    int HitCheckTYpe = HIT_CHECK_TYPE::DEACTIVE;
    int CollisionNum = 0;
    bool IsHit = false;                                     // 対プレイヤー
    bool IsHitVsObs = false;                                // 対Obstacle
protected:
    DirectX::XMFLOAT3   position        = { 0,0,0 };        // 位置
    DirectX::XMFLOAT3*  OriginPosition  = nullptr;          // ステージの原点
    DirectX::XMFLOAT3   angle           = { 0,0,0 };        // 角度
    DirectX::XMFLOAT3   scale           = { 1,1,1 };        // スケール
    DirectX::XMFLOAT3   velocity        = { 0,0,0 };        // 速度
    DirectX::XMFLOAT3*  scrollVelocity  = &velocity;        // スクロール速度のポインタ(初期値は自分のvelocity)
    DirectX::XMFLOAT4X4   transform = {
        1,0,0,0,
        0,1,0,0,
        0,0,1,0,
        0,0,0,1,
    };
    float   height                      = 2.0f;             // 高さ
    float   radius                      = 0.5f;             // 半径

    float   moveVecX                    = 0.0f;             // 移動方向ベクトル
    float   moveVecZ                    = 0.0f;             // 移動方向ベクトル

    float   gravity                     = -1.0f;            // 重力

    bool    isGround                    = false;            // 地面判定

    float   friction                    = 0.5f;             // 摩擦力
    float   acceleration                = 1.0f;             // 加速力
    float   maxMoveSpeed                = 5.0f;             // 最大移動速度
    float	airControl                  = 0.3f;             // 空気
};


// コーラ
class Cola : public Obstacle
{
public:
    Cola();
    // 更新処理
    void Update(float elapsedTime)override;

    // デバッグプリミティブ描画
    void DrawDebugPrimitive()override;
};


// ポッキー
class Pokey : public Obstacle
{
public:
    Pokey();
    // 更新処理
    void Update(float elapsedTime)override;

    // デバッグプリミティブ描画
    void DrawDebugPrimitive()override;
};

// プリッツ
class Prits : public Obstacle
{
public:
    Prits();
};

// マシュマロ(ベース)
class Marshmallow_Base : public Obstacle
{
public:
    Marshmallow_Base() {}
    // 更新処理
    void Update(float elapsedTime)override;

    // デバッグプリミティブ描画
    void DrawDebugPrimitive()override;
};
// マシュマロ(青)
class Marshmallow_Blue : public Marshmallow_Base
{
public:
    Marshmallow_Blue();
};
// マシュマロ(ピンク)
class Marshmallow_Pink : public Marshmallow_Base
{
public:
    Marshmallow_Pink();
};


// ビーンズ(ベース)
class Jellybeans_Base : public Obstacle
{
public:
    Jellybeans_Base() { scale = { 0.5f,0.5f ,0.5f }; }
    // 更新処理
    void Update(float elapsedTime)override;
    // デバッグプリミティブ描画
    void DrawDebugPrimitive()override;
};
// ビーンズ(黄色)
class Jellybeans_Yellow : public Jellybeans_Base
{
public:
    Jellybeans_Yellow();
};
// ビーンズ(ピンク)
class Jellybeans_Pink : public Jellybeans_Base
{
public:
    Jellybeans_Pink();
};
// ビーンズ(グリーン)
class Jellybeans_Green : public Jellybeans_Base
{
public:
    Jellybeans_Green();
};


// チョコボール
class Chocolate_ball : public Obstacle
{
public:
    Chocolate_ball();
    // 更新処理
    void Update(float elapsedTime)override;
    // デバッグプリミティブ描画
    void DrawDebugPrimitive()override;
};


// グレープジュース
class Grape_can : public Obstacle
{
public:
    Grape_can();
    // デバッグプリミティブ描画
    void DrawDebugPrimitive()override;
};


// オレンジガム
class Orange_gum : public Obstacle
{
public:
    Orange_gum();
    // デバッグプリミティブ描画
    void DrawDebugPrimitive()override;
};

// フーセンガム
class Husen_gum : public Obstacle
{
public:
    static float constexpr MaxUp        = 10.0f;      // 上下移動の最大値      
    static float constexpr MaxDown      = 0.0f;      // 上下移動の最小値 
    static float constexpr MaxPos[2] =
    {
        MaxDown,
        MaxUp
    };

    static float constexpr MoveSpeed    = 100.0f;      // 上下移動の速度

public:
    Husen_gum();
    // デバッグプリミティブ描画
    void DrawDebugPrimitive()override;

private:
    // 追加の速力更新処理
    void UpdataAdditionVelocity(float elapsedFrame) override;

private:
    bool isUp = true;
    bool a[3] = {};
};

// キャンディーゲート
class Candy_gate : public Obstacle
{
public:
    Candy_gate();
    // デバッグプリミティブ描画
    void DrawDebugPrimitive()override;
};


// オレンジジュース
class Orange_can : public Obstacle
{
public:
    Orange_can();
    // デバッグプリミティブ描画
    void DrawDebugPrimitive()override;
};


// マーブルチョコ
class Marble_chocolate : public Obstacle
{
private:
    static float constexpr MaxMoveDistance = 30.0f;     // 移動距離の最大値D
    static float constexpr MoveSpeed = 50.0f;     // 移動距離の最大値D

public:
    Marble_chocolate();
    // デバッグプリミティブ描画
    void DrawDebugPrimitive()override;

private:
    // 速度の追加更新
    void UpdataAdditionVelocity(float elapsedFrame)override;

private:
    bool isleft = false;
};


// カップケーキ(ベース)
class Cupcake_Base : public Obstacle
{
public:
    Cupcake_Base(){}
    // デバッグプリミティブ描画
    void DrawDebugPrimitive()override;
};
// カップケーキ(チョコ)
class Cupcake_Choco : public Cupcake_Base
{
public:
    Cupcake_Choco();
};
// カップケーキ(ピンク)
class Cupcake_Pink : public Cupcake_Base
{
public:
    Cupcake_Pink();
};