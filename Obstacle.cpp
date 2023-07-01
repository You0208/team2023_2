#include<imgui.h>
#include "Obstacle.h"
#include "Tool.h"
#include "Graphics/Graphics.h"

//-------------------------------------------------------------------------------------------------------
// 
//		 障害物
// 
//-------------------------------------------------------------------------------------------------------

// 描画処理
void Obstacle::Draw(RenderContext rc, ModelShader* shader)
{
    shader->Draw(rc, model.get());
    DrawDebugPrimitive();
}

//更新処理
void Obstacle::Update(float elapsedTime)
{
    if (Type == ITEMS)
    {
        angle.y += DirectX::XMConvertToRadians(1);//回す
    }
    // 速度処理更新
    UpdateVelocity(elapsedTime);

    //オブジェクト行列を更新
    UpdateTransform();

    //モデル行列更新
    model->UpdateTransform(transform);
}

//デバッグGUI描画
void Obstacle::DrawDebugGUI()
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
        }
    }
    ImGui::End();
}

//行列更新処理
void Obstacle::UpdateTransform()
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

void Obstacle::GetItem()
{
    if (Type == TYPE::ITEMS)
    {
        position.y=lerp(position.y, 5.0f, 0.03f);
        angle.y += DirectX::XMConvertToRadians(1);
        //オブジェクト行列を更新
        UpdateTransform();

        //モデル行列更新
        model->UpdateTransform(transform);
    }
}

// 旋回処理
void Obstacle::Turn(float elapsedTime, float vx, float vz, float speed)
{
    speed *= elapsedTime;

    // 進行ベクトルがゼロベクトルの場合は処理する必要なし
    float length = sqrtf(vx * vx + vz * vz);
    if (length < 0.01f)return;
    // 進行ベクトルを単位ベクトル化
    vx /= length;
    vz /= length;
    // 自身の回転値から前方向を求める
    float frontX = sinf(angle.y);
    float frontZ = cosf(angle.y);

    //回転角を求めるため、2つの単位ベクトルの内積を計算する
    float dot = (frontX * vx) + (frontZ * vz);
    //内積値は-1.0~1.0で表現されており、2つの単位ベクトルの角度が
    //小さいほど1.0に近づくという性質を利用して回転速度を調整する
    float rot = 1.0 - dot;
    if (rot > speed)rot = speed;

    // 左右判定を行うために二つの単位ベクトルの外積計算する
    float cross = (frontZ * vx) - (vz * frontX);

    // 2Dの外積値が正の場合か負の場合によって左右判定が行える
    // 左右判定を行うことによって左右を回転する
    if (cross < 0.0f)
    {
        angle.y -= rot;
    }
    else
    {
        angle.y += rot;
    }
}

// 速度処理更新
void Obstacle::UpdateVelocity(float elapsedTime)
{
    // 経過フレーム
    float elapsedFrame = 60.0f * elapsedTime;

    // 速度初期設定
    velocity = *scrollVelocity;

    // 速度の追加更新
    UpdataAdditionVelocity(elapsedFrame);

    // 移動更新処理
    UpdateMove(elapsedTime);
}

// 移動更新処理
void Obstacle::UpdateMove(float elapsedTime)
{
    // 移動処理
    position.x += velocity.x * elapsedTime;
    position.y += velocity.y * elapsedTime;
    position.z += velocity.z * elapsedTime;
}

// コーラ
Cola::Cola()
{
    //モデルを読み込み
    model = std::make_unique<Model>("Data/Model/Obstacle/cola/Cola.mdl");
    angle.y = DirectX::XMConvertToRadians(180);
    height = 3.8f;
    radius = 1.2f;
    Type = TYPE::CYLINDER;
    CollisionNum = 1;
}
// 更新処理
void Cola::Update(float elapsedTime)
{
    // 基底クラス更新処理
    Obstacle::Update(elapsedTime);
}

void Cola::DrawDebugPrimitive()
{
    DebugRenderer* debugRenderer = Graphics::Instance().GetDebugRenderer();
    //衝突判定用のデバッグ円柱を描画
    debugRenderer->DrawCylinder(position, radius, height, DirectX::XMFLOAT4(0, 0, 0, 1));
}


// ポッキー 
Pokey::Pokey()
{
    //モデルを読み込み
    model = std::make_unique<Model>("Data/Model/Obstacle/pocky/pozky.mdl");
    angle.y = DirectX::XMConvertToRadians(180);
    height = 7.0f;
    Type = TYPE::CYLINDERS;
    CollisionNum = 5;
}
// 描画処理
void Pokey::Update(float elapsedTime)
{
    // 基底クラス描画処理
    Obstacle::Update(elapsedTime);
}

void Pokey::DrawDebugPrimitive()
{
    DebugRenderer* debugRenderer = Graphics::Instance().GetDebugRenderer();
    //衝突判定用のデバッグ円柱を描画
    for (int n = 0; n < CollisionNum; ++n)
    {
        debugRenderer->DrawCylinder({ (position.x - (5.0f * 0.5f) + radius) + (n * radius * 2.0f) ,position.y,position.z }, radius, height, DirectX::XMFLOAT4(0, 0, 0, 1));
    }
}

// プリッツ
Prits::Prits()
{
    //モデルを読み込み
    model = std::make_unique<Model>("Data/Model/Obstacle/prits/prits.mdl");
    angle.y = DirectX::XMConvertToRadians(180);
}


// マシュマロ
// 更新処理
void Marshmallow_Base::Update(float elapsedTime)
{
    // 基底クラス描画処理
    Obstacle::Update(elapsedTime);
    radius = 1.0f;
    Type = TYPE::ITEMS;
    score = 5;
    hungerPoint = 5;
}
void Marshmallow_Base::DrawDebugPrimitive()
{
    DebugRenderer* debugRenderer = Graphics::Instance().GetDebugRenderer();
    //衝突判定用のデバッグ円柱を描画
    debugRenderer->DrawSphere(position, radius, DirectX::XMFLOAT4(0, 0, 0, 1));
}
// コンストラクタ
Marshmallow_Blue::Marshmallow_Blue()
{
    //モデルを読み込み
    model = std::make_unique<Model>("Data/Model/Obstacle/marshmallow/marshmallow_blue.mdl");
}
// マシュマロ(ピンク)
Marshmallow_Pink::Marshmallow_Pink()
{
    //モデルを読み込み
    model = std::make_unique<Model>("Data/Model/Obstacle/marshmallow/marshmallow_pink.mdl");
}


// ビーンズ
// 更新処理
void Jellybeans_Base::Update(float elapsedTime)
{
    // 基底クラス描画処理
    Obstacle::Update(elapsedTime);
    radius = 1.0f;
    Type = TYPE::ITEMS;
    score = 3;
    hungerPoint = 3;
}
void Jellybeans_Base::DrawDebugPrimitive()
{
    DebugRenderer* debugRenderer = Graphics::Instance().GetDebugRenderer();
    //衝突判定用のデバッグ円柱を描画
    debugRenderer->DrawSphere(position, radius, DirectX::XMFLOAT4(0, 0, 0, 1));
}
// ビーンズ(黄色)
Jellybeans_Yellow::Jellybeans_Yellow()
{
    Jellybeans_Base();
    //モデルを読み込み
    model = std::make_unique<Model>("Data/Model/Obstacle/jellybeans/jellybeans_yellow.mdl");
}
// ビーンズ(ピンク)
Jellybeans_Pink::Jellybeans_Pink()
{
    Jellybeans_Base();
    //モデルを読み込み
    model = std::make_unique<Model>("Data/Model/Obstacle/jellybeans/jellybeans_pink.mdl");
}
// ビーンズ(グリーン)
Jellybeans_Green::Jellybeans_Green()
{
    Jellybeans_Base();
    //モデルを読み込み
    model = std::make_unique<Model>("Data/Model/Obstacle/jellybeans/jellybeans_green.mdl");
}


// チョコボール
Chocolate_ball::Chocolate_ball()
{
    //モデルを読み込み
    model = std::make_unique<Model>("Data/Model/Obstacle/chocolate_ball/chocolate_ball.mdl");
    angle.y = DirectX::XMConvertToRadians(180);
    height = 6.0f;
    Type = TYPE::CYLINDERS;
    CollisionNum = 3;
}
void Chocolate_ball::Update(float elapsedTime)
{
    // 基底クラス描画処理
    Obstacle::Update(elapsedTime);
}

void Chocolate_ball::DrawDebugPrimitive()
{
    DebugRenderer* debugRenderer = Graphics::Instance().GetDebugRenderer();
    //衝突判定用のデバッグ円柱を描画
    for (int n = 0; n < CollisionNum; ++n)
    {
        debugRenderer->DrawCylinder({ (position.x - (CollisionNum * 0.5f) + radius) + (n * radius * 2.0f) ,position.y,position.z }, radius, height, DirectX::XMFLOAT4(0, 0, 0, 1));
    }
}


// グレープジュース
Grape_can::Grape_can()
{
    //モデルを読み込み
    model = std::make_unique<Model>("Data/Model/Obstacle/grape_can/grape_can.mdl");
    angle.y = DirectX::XMConvertToRadians(180);
    height = 3.8f;
    radius = 1.2f;
    Type = TYPE::CYLINDER;
    CollisionNum = 1;
}

void Grape_can::DrawDebugPrimitive()
{
    DebugRenderer* debugRenderer = Graphics::Instance().GetDebugRenderer();
    //衝突判定用のデバッグ円柱を描画
    debugRenderer->DrawCylinder(position, radius, height, DirectX::XMFLOAT4(0, 0, 0, 1));
}


// フーセンガム
Husen_gum::Husen_gum()
{
    //モデルを読み込み
    model = std::make_unique<Model>("Data/Model/Obstacle/husen_gum/husen_gum.mdl");
    angle.y = DirectX::XMConvertToRadians(180);
    scale = { 5.0f,5.0f ,5.0f };
    height = 5.0f;
    radius = 0.6f;
    Type = TYPE::CYLINDER;
    CollisionNum = 3;
}

void Husen_gum::DrawDebugPrimitive()
{
    DebugRenderer* debugRenderer = Graphics::Instance().GetDebugRenderer();
    //衝突判定用のデバッグ円柱を描画
    for (int n = 0; n < CollisionNum; ++n)
    {
        debugRenderer->DrawCylinder({ (position.x - (CollisionNum * 0.5f) + radius) + (n * radius * 2.0f) ,position.y,position.z }, radius, height, DirectX::XMFLOAT4(0, 0, 0, 1));
    }
}

// 追加の更新処理
void Husen_gum::UpdataAdditionVelocity(float elapsedFrame)
{
    if (isUp && position.y >= MaxUp) isUp = false;
    if (!isUp && position.y <= MaxDown) isUp = true;

    velocity.y = isUp ? MoveSpeed * elapsedFrame : -MoveSpeed * elapsedFrame;
}


// オレンジガム
Orange_gum::Orange_gum()
{
    //モデルを読み込み
    model = std::make_unique<Model>("Data/Model/Obstacle/orange_gum/orange_gum.mdl");
    angle.y = DirectX::XMConvertToRadians(180);
    scale = { 3.0f,3.0f ,3.0f };
    height = 3.0f;
    radius = 0.5f;
    Type = TYPE::CYLINDERS;
    CollisionNum = 3;
}

void Orange_gum::DrawDebugPrimitive()
{
    DebugRenderer* debugRenderer = Graphics::Instance().GetDebugRenderer();
    //衝突判定用のデバッグ円柱を描画
    for (int n = 0; n < CollisionNum; ++n)
    {
        debugRenderer->DrawCylinder({ (position.x - (CollisionNum * 0.5f) + radius) + (n * radius * 2.0f) ,position.y,position.z }, radius, height, DirectX::XMFLOAT4(0, 0, 0, 1));
    }
}


// キャンディーゲート
Candy_gate::Candy_gate()
{
    //モデルを読み込み
    model = std::make_unique<Model>("Data/Model/Obstacle/candy_gate/candy_gate.mdl");
    angle.y = DirectX::XMConvertToRadians(180);
    scale = { 3.0f,3.0f ,3.0f };
    height = 9.0f;
    Type = TYPE::GATE;
    CollisionNum = 9;
}

void Candy_gate::DrawDebugPrimitive()
{
    DebugRenderer* debugRenderer = Graphics::Instance().GetDebugRenderer();
    //衝突判定用のデバッグ円柱を描画
    for (int n = 0; n < CollisionNum; ++n)
    {
        debugRenderer->DrawCylinder({ (position.x - (CollisionNum * 0.5f) + radius) + (n * radius * 2.0f) ,position.y,position.z }, radius, height, DirectX::XMFLOAT4(0, 0, 0, 1));
    }
}


// オレンジジュース
Orange_can::Orange_can()
{
    //モデルを読み込み
    model = std::make_unique<Model>("Data/Model/Obstacle/orange_can/orange_can.mdl");
    angle.y = DirectX::XMConvertToRadians(180);
    height = 3.8f;
    radius = 1.2f;
    Type = TYPE::CYLINDER;
    CollisionNum = 1;
}

void Orange_can::DrawDebugPrimitive()
{
    DebugRenderer* debugRenderer = Graphics::Instance().GetDebugRenderer();
    //衝突判定用のデバッグ円柱を描画
    debugRenderer->DrawCylinder(position, radius, height, DirectX::XMFLOAT4(0, 0, 0, 1));
}


// マーブルチョコ
Marble_chocolate::Marble_chocolate()
{
    //モデルを読み込み
    model = std::make_unique<Model>("Data/Model/Obstacle/marble_chocolate/marble_chocolate.mdl");
    angle.y = DirectX::XMConvertToRadians(180);
    height = 7.0f;
    Type = TYPE::CYLINDERS;
    CollisionNum = 1;
}

void Marble_chocolate::DrawDebugPrimitive()
{
    DebugRenderer* debugRenderer = Graphics::Instance().GetDebugRenderer();
    //衝突判定用のデバッグ円柱を描画
    for (int n = 0; n < CollisionNum; ++n)
    {
        debugRenderer->DrawCylinder({ (position.x - (CollisionNum * 0.5f) + radius) + (n * radius * 2.0f) ,position.y,position.z }, radius, height, DirectX::XMFLOAT4(0, 0, 0, 1));
    }
}

// 速度の追加更新
void Marble_chocolate::UpdataAdditionVelocity(float elapsedFrame)
{
    // ステージ外に行くと
    // 画面外に行かないように少し余裕を持って引き返している
    if (
        (position.x + (height * 0.5f) >= OriginPosition->x + 45.0f)
        ||(position.x - (height * 0.5f) <= OriginPosition->x - 45.0f)
        )
    {
        isleft = !isleft;
    }

    velocity.x += isleft ? -MoveSpeed : MoveSpeed;
}


// カップケーキ(チョコ)
Cupcake_Choco::Cupcake_Choco()
{
    model = std::make_unique<Model>("Data/Model/Obstacle/cupcake/cupcake_choco.mdl");
    radius = 2.5f;
    Type = TYPE::ITEMS;
    hungerPoint = 10;
    score = 10;
}
// カップケーキ(ピンク)
Cupcake_Pink::Cupcake_Pink()
{
    model = std::make_unique<Model>("Data/Model/Obstacle/cupcake/cupcake_pink.mdl");
    radius = 2.5f;
    Type = TYPE::ITEMS;
    score = 10;
    hungerPoint = 10;
}

void Cupcake_Base::DrawDebugPrimitive()
{
    DebugRenderer* debugRenderer = Graphics::Instance().GetDebugRenderer();
    //衝突判定用のデバッグ円柱を描画
    debugRenderer->DrawSphere(position, radius, DirectX::XMFLOAT4(0, 0, 0, 1));
}
