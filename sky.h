#pragma once
#include "Graphics/Shader.h"
#include "Graphics/Model.h"

//�v���C���[
class Sky
{
public:
    Sky();
    ~Sky() {}

    //�X�V����  
    void Update(float elapsedTime);

    // �`�揈��
    void Draw(RenderContext rc, ModelShader* shader);

    // �ʒu�X�V
    void SetPosition(const DirectX::XMFLOAT3& position) { this->position = position; }

    //�s��X�V����
    void UpdateTransform();
public:
    // ���f����scene��render�ŌĂяo���̂�public
    std::unique_ptr<Model>  model = nullptr;       // ���f��
    float space = 900;
private:
    DirectX::XMFLOAT3   position = { 0,0,0 };     // �ʒu
    DirectX::XMFLOAT3   angle = { 0,0,0 };     // �p�x
    DirectX::XMFLOAT3   scale = { 1,1,1 };     // �X�P�[��
    DirectX::XMFLOAT3   velocity = { 0,0,0 };     // ���x
    DirectX::XMFLOAT4X4   transform = {
        1,0,0,0,
        0,1,0,0,
        0,0,1,0,
        0,0,0,1,
    };
    float   height = 2.0f;           // ����
    float   radius = 0.5f;           // ���a

    float   acceleration = 10.0f;          // ������
    float   moveSpeed = 50.0f;          // �ړ����x
    float   maxMoveSpeed = 100.0f;          // �ő�ړ����x

    float   friction = 0.5f;           // ����

    float   moveVecX = 0.0f;           // �ړ������x�N�g��
    float   moveVecZ = 0.0f;           // �ړ������x�N�g��

    int     health = 5;              // �̗�
    int     maxHealth = 5;              // �ő�̗�
    float   invincibleTimer = 1.0f;           // ���G����

    // ��]���x
    float   turnSpeed = DirectX::XMConvertToRadians(720);
};

