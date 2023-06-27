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
    //�s��X�V
    UpdateTransform();

    //���f���s��X�V
    model->UpdateTransform(transform);
}

void Sky::Draw(RenderContext rc, ModelShader* shader)
{
    //�X�e�[�W�`��
    shader->Draw(rc, model.get());
}

void Sky::UpdateTransform()
{
    //�X�P�[���s����쐬
    DirectX::XMMATRIX S = DirectX::XMMatrixScaling(scale.x, scale.y, scale.z);
    //��]�s����쐬
    DirectX::XMMATRIX R = DirectX::XMMatrixRotationRollPitchYaw(angle.x, angle.y, angle.z);
    //�ʒu�s����쐬
    DirectX::XMMATRIX T = DirectX::XMMatrixTranslation(position.x, position.y, position.z);
    //�R�̍s���g�ݍ��킹�A���[���h�s����쐬
    DirectX::XMMATRIX W = S * R * T;
    //�v�Z�������[���h�s������o��
    DirectX::XMStoreFloat4x4(&transform, W);
}
