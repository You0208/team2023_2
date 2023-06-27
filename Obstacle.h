#pragma once
#include <vector>
#include "graphics/shader.h"
#include "graphics/model.h"

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

    // 半径取得
    float GetRadius() const { return radius; }

    // 高さ取得
    float GetHeight() const { return height; }

    // == 追加した関数(この文はあとで削除する) ==
    void SetScrollVelocity(DirectX::XMFLOAT3* ScrollVelocity) { scrollVelocity = ScrollVelocity; }

private:
    // 旋回処理
    void Turn(float elapsedtime, float vx, float vz, float speed);

    // 速度処理更新
    void UpdateVelocity(float elapsedTime);

    // 水平速力更新処理
    void UpdataHorizontalVelocity(float elapsedFrame);

    // 水平移動更新処理
    void UpdateHorizontalMove(float elapsedTime);

    // 垂直速力更新処理
    void UpdataVerticalVelocity(float elapsedFrame);

    // 垂直移動更新処理
    void UpdateVerticalMove(float elapsedTime);

public:
    // モデルは呼び出すのでpublic
    std::unique_ptr<Model>  model       =    nullptr;        // モデル

protected:
    DirectX::XMFLOAT3   position        = { 0,0,0 };        // 位置
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
};


// ポッキー
class Pokey : public Obstacle
{
public:
    Pokey();
    // 更新処理
    void Update(float elapsedTime)override;
};


// マシュマロ(ベース)
class Marshmallow_Base : public Obstacle
{
public:
    Marshmallow_Base() {}
    // 更新処理
    void Update(float elapsedTime)override;
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
};


// グレープジュース
class Grape_can : public Obstacle
{
public:
    Grape_can();
};


// オレンジガム
class Orange_gum : public Obstacle
{
public:
    Orange_gum();
};


// キャンディーゲート
class Candy_gate : public Obstacle
{
public:
    Candy_gate();
};


// オレンジジュース
class Orange_can : public Obstacle
{
public:
    Orange_can();
};


// マーブルチョコ
class Marble_chocolate : public Obstacle
{
public:
    Marble_chocolate();
};


// カップケーキ(ベース)
class Cupcake_Base : public Obstacle
{
public:
    Cupcake_Base(){}
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