#include "Sky.h"

Sky::Sky()
{
    model = std::make_unique<Model>("Data/Model/Debug/back.mdl");
    angle.x = DirectX::XMConvertToRadians(180);
    angle.z = DirectX::XMConvertToRadians(180);
    scale.x = scale.y = scale.z = 6.0f;
    position.z = 510.0f;
}

void Sky::Update(float elapsedTime)
{
    //行列更新
    UpdateTransform();

    //モデル行列更新
    model->UpdateTransform(transform);
}

void Sky::Draw(RenderContext rc, ModelShader* shader)
{
    //ステージ描画
    shader->Draw(rc, model.get());
}

void Sky::UpdateTransform()
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
