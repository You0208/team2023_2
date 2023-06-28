#include<imgui.h>
#include "Camera.h"
#include "Player.h"
#include "Input/Input.h"
#include "Graphics/Graphics.h"

//-------------------------------------------------------------------------------------------------------
// 
//		 プレイヤー
// 
//-------------------------------------------------------------------------------------------------------

//コンストラクタ   
Player::Player()
{
    model = std::make_unique< Model>("Data/Model/Player/Hamster.mdl");

    //モデルが大きいのでスケーリング
    scale.x = scale.y = scale.z = 1.0f;

    // 初期位置浮かす
    position.y = 5.0f;

    // 待機ステートへ遷移
    TransitionIdleState();
}

//更新処理
void Player::Update(float elapsedTime)
{
    // Bボタンでダメージ状態へ遷移(仮)
    GamePad& gamePad = Input::Instance().GetGamePad();
    if (gamePad.GetButtonDown() & GamePad::BTN_B)
    {
        TransitionDamageState();
    }

    // 状態毎の更新処理(時間に余裕あれば変更したい)
    switch (state)
    {
    case Player::State::Idle:
        UpdateIdleState(elapsedTime);
        break;
    case Player::State::Damage:
        UpdateDamageState(elapsedTime);
        break;
    }

    UpdateScale(MaxScale[hungerLevel], ScaleRate);

    //オブジェクト行列を更新
    UpdateTransform();

    // モデルアニメーション更新処理
    model->UpdateAnimation(elapsedTime);

    //モデル行列更新
    model->UpdateTransform(transform);
}

// 描画処理
void Player::Draw(RenderContext rc, ModelShader* shader)
{
    shader->Draw(rc, model.get());
}

// ダメージを与える
bool Player::ApplyDamage(int damage, float invincibleTime)
{
    // ダメージが０の場合は健康状態を変更する必要がない
    if (damage == 0)return false;

    // 死亡している間は健康状態を変更しない
    if (health <= 0)return false;

    if (invincibleTimer > 0.0f)return false;

    invincibleTimer = invincibleTime;

    // ダメージ処理
    health -= damage;

    // 死亡通知
    if (health <= 0)
    {
        OnDead();
    }
    else
    {
        OnDamaged();
    }

    // 健康状態が変更した場合はtrueを返す
    return true;
}

// 移動入力処理
void Player::InputMove(float elapsedTime)
{
    // 進行ベクトル取得
    DirectX::XMFLOAT3 moveVec = GetMoveVec();

    // 移動処理
    // 移動方向ベクトルを設定
    moveVecX = moveVec.x;

    // 最大速度設定
    //maxMoveSpeed = moveSpeed;
}

// 速度処理更新
void Player::UpdateVelocity(float elapsedTime)
{
    // 経過フレーム
    float elapsedFrame = 60.0f * elapsedTime;

    // 水平速力更新処理
    UpdataHorizontalVelocity(elapsedFrame);

    // 水平移動更新処理
    UpdateHorizontalMove(elapsedTime);
}

// 無敵時間更新
void Player::UpdateInvincibleTimer(float elapsedTime)
{
    if (invincibleTimer > 0.0f)
    {
        invincibleTimer -= elapsedTime;
    }
}

//デバッグGUI描画
void Player::DrawDebugGUI()
{
    ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(ImVec2(300, 300), ImGuiCond_FirstUseEver);

    if (ImGui::Begin("Player", nullptr, ImGuiWindowFlags_None))
    {
        //トランスフォーム
        if (ImGui::CollapsingHeader("Transform", ImGuiTreeNodeFlags_DefaultOpen))
        {
            //位置
            ImGui::InputFloat3("Position", &position.x);
            //回転
            DirectX::XMFLOAT3 a;
            a.x = DirectX::XMConvertToDegrees(angle.x);
            a.y = DirectX::XMConvertToDegrees(angle.y);
            a.z = DirectX::XMConvertToDegrees(angle.z);
            ImGui::InputFloat3("Angle", &a.x);
            angle.x = DirectX::XMConvertToRadians(a.x);
            angle.y = DirectX::XMConvertToRadians(a.y);
            angle.z = DirectX::XMConvertToRadians(a.z);
            //スケール
            ImGui::InputFloat3("Scale", &scale.x);
            // 速度
            ImGui::InputFloat3("velocity", &velocity.x);
        }
    }


    ImGui::SliderInt("hungerLevel", &hungerLevel, 0, 2);

    ImGui::End();
}

//行列更新処理
void Player::UpdateTransform()
{
    //スケール行列を作成
    DirectX::XMMATRIX S = DirectX::XMMatrixScaling(scale.x, scale.y, scale.z);
    //回転行列を作成
    DirectX::XMMATRIX R = DirectX::XMMatrixRotationRollPitchYaw(angle.x, angle.y, angle.z);
    //位置行列を作成
    DirectX::XMMATRIX T = DirectX::XMMatrixTranslation(position.x, position.y, position.z);
    //３つの行列を組み合わせ、ワールド行列を作成
    DirectX::XMMATRIX W = S * R * T;
    //計算したワールド行列を取り出す
    DirectX::XMStoreFloat4x4(&transform, W);
}

// スティック入力値から移動ベクトルを取得
DirectX::XMFLOAT3 Player::GetMoveVec() const
{
    // 入力情報を取得
    GamePad& gamePad = Input::Instance().GetGamePad();
    float ax = gamePad.GetAxisLX();
    DirectX::XMFLOAT3 vec = { ax ,0.0f,0.0f };

    return vec;
}

// 水平速力更新処理
void Player::UpdataHorizontalVelocity(float elapsedFrame)
{
    // XZ平面の速力を減速する
    float length = sqrtf(velocity.x * velocity.x);
    if (length > 0.0f)
    {
        // 摩擦力
        float friction = this->friction * elapsedFrame;

        // 摩擦による横方向の減速処理
        if (length > friction)
        {
            float vx = velocity.x / length;

            velocity.x -= vx * friction;
        }
        // 横方向の速力が摩擦力以下になったので速力を無効化
        else
        {
            velocity.x = 0;
        }
    }

    // XZ平面の速力を加速する
    if (length <= maxMoveSpeed)
    {
        // 移動ベクトルがゼロベクトル出ないなら加速する
        float moveVecLength = sqrtf(moveVecX * moveVecX);
        if (moveVecLength > 0.0f)
        {
            // 加速力
            float acceleration = this->acceleration * elapsedFrame;

            // 移動ベクトルによる加速処理
            velocity.x += moveVecX * acceleration;

            // 最大速度制限
            float length = sqrtf(velocity.x * velocity.x);
            if (length > maxMoveSpeed)
            {
                float vx = velocity.x / length;

                velocity.x = vx * maxMoveSpeed;
            }
        }
    }
    // 移動ベクトルをリセット
    moveVecX = 0.0f;
}

// 水平移動更新処理
void Player::UpdateHorizontalMove(float elapsedTime)
{
    // 移動処理
    position.x += velocity.x * elapsedTime;
}

// 待機状態へ遷移
void Player::TransitionIdleState()
{
    state = State::Idle;

    // アニメーション再生
    model->PlayAnimation(Anim_Idle, true, 0.0f);
}
// 待機状態更新
void Player::UpdateIdleState(float elapsedTime)
{
    //// 移動入力処理
    //InputMove(elapsedTime);

    //// 速度処理更新
    //UpdateVelocity(elapsedTime);

    // 傾き処理
    Lean(elapsedTime, velocity.x, LeanSpeed);
}


// ダメージ状態へ遷移
void Player::TransitionDamageState()
{
    state = State::Damage;

    // アニメーション再生
    model->PlayAnimation(Anim_Damage, false);
    isDamageAnim = true;        // ダメージアニメ再生開始
}
// ダメージ状態更新
void Player::UpdateDamageState(float elapsedTime)
{
    // アニメーション再生が終わったら待機状態へ遷移
    if (!model->IsPlayAnimation())
    {
        TransitionIdleState();
        isDamageAnim = false;   // ダメージアニメ再生終了
    }
}


// 頷き状態へ遷移
void Player::TransitionNodState()
{
    // アニメーション再生
    model->PlayAnimation(Anim_Nod, false);
}

// 傾き処理
void Player::Lean(float elapsedTime, float vx, float add)
{
    // まっすぐにする(速度が０)
    if (vx > -FLT_EPSILON && vx < FLT_EPSILON)
    {
        // 左に傾いている
        if (angle.z > FLT_EPSILON)
        {
            angle.z -= DirectX::XMConvertToRadians(add);

            // 超過修正
            angle.z = (std::max)(angle.z, 0.0f);
        }
        // 右に傾いている
        if (angle.z < -FLT_EPSILON)
        {
            angle.z += DirectX::XMConvertToRadians(add);

            // 超過修正
            angle.z = (std::min)(angle.z, 0.0f);
        }
    }
    // 左に傾ける(速度が0未満)
    else if (vx < 0)
    {
        angle.z += DirectX::XMConvertToRadians(add);

        // 超過修正
        angle.z = (std::min)(angle.z,DirectX::XMConvertToRadians(LeanAngle));
    }
    // 左に傾ける(速度が0より大きい)
    else if (vx > 0)
    {
        angle.z -= DirectX::XMConvertToRadians(add);

        // 超過修正e
        angle.z = (std::max)(angle.z, DirectX::XMConvertToRadians(-LeanAngle));
    }
}

// スケール更新
void Player::UpdateScale(float maxScale, float rate)
{
    float length = maxScale - scale.x;
    // 値が微小な場合は処理しない
    if (fabs(length) > 1e-8f)
    {
        //return a + t * (b - a);
        scale.x = scale.y = scale.z = scale.x + rate * (maxScale - scale.x);
    }
}
