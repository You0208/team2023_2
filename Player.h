#pragma once
#include "Graphics/Shader.h"
#include "Graphics/Model.h"
#include "SceneOver.h"
#include "SceneManager.h"

//プレイヤー
class Player
{
public:
    static constexpr float ScaleRate = 0.002f;  // スケール拡縮の補間係数

    static constexpr float LeanAngle    = 30.0f;        // 左右移動時の傾き角度
    static constexpr float LeanRate     = 0.03f;        // 傾きの補間係数
    static constexpr float LeanRate_0   = 0.01f;        // 戻る時の傾き補間係数

    static constexpr float MaxHungerPoint       = 100.0f;   // 空腹量の最大値
    static constexpr float DecreaseHungerPoint   = 1.0f;    // 空腹量の減少量
    // 各空腹レベルでのスケール
    static constexpr float MaxScale[3] =
    {
        0.7f,       // 空腹レベル：低
        1.0f,       // 空腹レベル：中
        1.3f        // 空腹レベル：高
    };
    // 空腹レベルが切り替わる境目
    static constexpr float HungerLevelLine[2] =
    {
        33.0f,      // これ以上が空腹レベル：中
        66.0f       // これ以上が空腹レベル：高
    };

public:

    Player();
    ~Player() {}

    // セレクト用更新
    void SelectUpdate(float elapsedTime);

    // クリア用更新
    void ClearUpdate(float elapsedTime);

    //更新処理  
    void Update(float elapsedTime,bool IsSelect = false);

    // 描画処理
    void Draw(RenderContext rc, ModelShader* shader);

    //デバッグGUI描画
    void DrawDebugGUI();

    //行列更新処理
    void UpdateTransform();

    // 死亡した時に呼ばれる
    void OnDead() {
        IsDeath = true;
        position.z -= 1.5f;
    }

    void DidFromHunger();

    // 位置更新
    void SetPosition(const DirectX::XMFLOAT3& position) { this->position = position; }
    // 回転更新
    void SetAngle(const DirectX::XMFLOAT3& angle) { this->angle = angle; }
    void SetAngleY(const float angle) { this->angle.y = angle; }
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
    // スコアを加算する
    static void AddScore(int s) { score += s; }

    // スコアを取得
    static int GetScore() { return score; }
    static void ScoreClear() { score = 0; }
    // 空腹レベル取得
    int GetHungerLevel() const { return hungerLevel; }
    // 空腹ポイント取得
    float GetHungerPoint() const { return hungerPoint; }

    // ===== 非使用　後で使うかも？ =====
    
    // ダメージを与える
    bool ApplyDamage(int damage, float invincibleTime);
    // 空腹ポイント加算
    void AddHungerPoint(float add);

private:

    // 傾き処理
    void Lean(float elapsedTime, float rate);

    // スケール更新
    void UpdateScale(float maxScale, float rate);

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

    // 空腹ポイント更新
    void UpdateHungerPoint(float elapsedTime);
    // 空腹レベル更新
    void UpdateHungerLevel();
    // 空腹ポイント減算
    void RemoveHungerPoint(float elapsedTime,float Remove);

    // ===== 非使用　後で使うかも？ =====

    // スティック入力値から移動ベクトルを取得
    float GetMoveVecX() const;

    // 無敵時間更新
    void UpdateInvincibleTimer(float elapsedTime);

    // ダメージを受けたときに呼ばれる
    virtual void OnDamaged() {}
    
public:
    // モデルはsceneのrenderで呼び出すのでpublic
    std::unique_ptr<Model>  model      = nullptr;       // モデル

    bool IsDeath = false;

    bool IsBreakTime = false;        // ブレイクタイムであるか
    bool Gashi = false;// 餓死
private:
    enum class State
    {
        Idle
        , Damage
    };
    enum Anination
    {
        Anim_Idle,      // 待機
        Anim_Nod,       // 頷く
        Anim_Damage,    // ダメージ
    };

    DirectX::XMFLOAT3   position       = { 0,0,0 };     // 位置
    DirectX::XMFLOAT3   angle          = { DirectX::XMConvertToRadians(25),0,0 };     // 角度
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

    int     maxHealth                  = 5;              // 最大体力
    float   invincibleTimer            = 1.0f;           // 無敵時間

    static int score;
    // 回転速度
    float   turnSpeed                  = DirectX::XMConvertToRadians(720);

    // 追加した変数(この文はあとで消す)
    State   state                       = State::Idle;  // 現在の状態
    bool    isDamageAnim                = false;        // ダメージアニメが再生中か
    bool    a[3]                        = {};

    int     hungerLevel                 = 1;            // 空腹レベル
    float   hungerPoint                = 66.0f;         // 空腹ポイント

    // ===== 非使用　後で使うかも？ =====
    int     health = 5;              // 体力
};