#pragma once
#include "Graphics/Shader.h"
#include "Graphics/Model.h"

//プレイヤー
class Player
{
public:
    static constexpr float LeanAngle = 30.0f;       // 左右移動時の傾き角度
    static constexpr float LeanRate  = 0.03f;       // 傾きの補間係数
    static constexpr float LeanRate_0= 0.01f;       // 戻る傾き補間係数
public:

    Player();
    ~Player() {}

    //更新処理  
    void Update(float elapsedTime);

    // 描画処理
    void Draw(RenderContext rc, ModelShader* shader);

    //デバッグGUI描画
    void DrawDebugGUI();

    //行列更新処理
    void UpdateTransform();

    // ダメージを与える
    bool ApplyDamage(int damage, float invincibleTime);
    
    // 位置更新
    void SetPosition(const DirectX::XMFLOAT3& position) { this->position = position; }
    // 回転更新
    void SetAngle(const DirectX::XMFLOAT3& angle) { this->angle = angle; }
    // スケール更新
    void SetScale(const DirectX::XMFLOAT3& scale) { this->scale = scale; }
    // 速度更新
    void SetVelocity(const DirectX::XMFLOAT3& velocity) { this->velocity = velocity; }

    // 位置取得
    const DirectX::XMFLOAT3& GetPosition() const { return position; }
    // 回転取得
    const DirectX::XMFLOAT3& GetAngle() const { return angle; }
    // スケール取得
    const DirectX::XMFLOAT3& GetScale() const { return scale; }
    // 半径取得
    float GetRadius() const { return radius; }
    // 高さ取得
    float GetHeight() const { return height; }
    // 健康状態を取得
    int GetHealth() const { return health; }
    // 最大健康状態を取得
    int GetMaxHealth() const { return maxHealth; }
    // ダメージアニメが再生中であるかを取得
    bool GetIsDamageAnim() const { return isDamageAnim; }

private:

    // 速度処理更新
    void UpdateVelocity(float elapsedTime);

    // 無敵時間更新
    void UpdateInvincibleTimer(float elapsedTime);

    // スティック入力値から移動ベクトルを取得
    float GetMoveVecX() const;

    // 水平速力更新処理
    void UpdataHorizontalVelocity(float elapsedFrame);

    // 水平移動更新処理
    void UpdateHorizontalMove(float elapsedTime);

    // ダメージを受けたときに呼ばれる
    virtual void OnDamaged() {}

    // 死亡した時に呼ばれる
    virtual void OnDead() {}

    // == 追加した関数(この文はあとで削除する) ==

    // 待機状態へ遷移
    void TransitionIdleState();
    // 待機状態更新
    void UpdateIdleState(float elapsedTime);

    // ダメージ状態へ遷移
    void TransitionDamageState();
    // ダメージ状態更新
    void UpdateDamageState(float elapsedTime);

    // 頷き状態へ遷移
    void TransitionNodState();

    // 傾き処理
    void Lean(float elapsedTime,float rate);
    
public:
    // モデルはsceneのrenderで呼び出すのでpublic
    std::unique_ptr<Model>  model      = nullptr;       // モデル
private:
    enum class State
    {
        Idle
        , Damage
    };
    enum Anination
    {
        Anim_Idle,     // 待機
        Anim_Nod,       // 頷く
        Anim_Damage,    // ダメージ
    };

    DirectX::XMFLOAT3   position       = { 0,0,0 };     // 位置
    DirectX::XMFLOAT3   angle          = { 0,0,0 };     // 角度
    DirectX::XMFLOAT3   scale          = { 1,1,1 };     // スケール
    DirectX::XMFLOAT3   velocity       = { 0,0,0 };     // 速度
    DirectX::XMFLOAT4X4   transform    = {
        1,0,0,0,
        0,1,0,0,
        0,0,1,0,
        0,0,0,1,
    };
    float   height                     = 2.0f;           // 高さ
    float   radius                     = 0.5f;           // 半径

    float   acceleration               = 10.0f;          // 加速力
    float   moveSpeed                  = 10.0f;          // 移動速度
    float   maxMoveSpeed               = 30.0f;          // 最大移動速度

    float   friction                   = 0.5f;           // 減速
    
    float   moveVecX                   = 0.0f;           // 移動方向ベクトル

    int     health                     = 5;              // 体力
    int     maxHealth                  = 5;              // 最大体力
    float   invincibleTimer            = 1.0f;           // 無敵時間

    // 回転速度
    float   turnSpeed                  = DirectX::XMConvertToRadians(720);

    // 追加した変数(この文はあとで消す)
    State   state                       = State::Idle;  // 現在の状態
    bool    isDamageAnim                = false;        // ダメージアニメが再生中か
    bool    wait[3]                     = {};
};