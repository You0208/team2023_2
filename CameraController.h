#pragma once

#include<DirectXMath.h>

//�J�����R���g���[���[
class CameraController
{
public:
    CameraController() {}
    ~CameraController() {}

    // �X�V����
    void Update(float elapsedTime);

    // �^�[�Q�b�g�ʒu�ݒ�
    void setTarget(const DirectX::XMFLOAT3& target) { this->target = target; }

    // �^�[�Q�b�g�ʒu�ݒ�
    void setTargetY(float y) { this->target.y = y; }

    void setRange(float i) { range = i; }

    float getRange() { return range; }

    DirectX::XMFLOAT3 getAngle() { return angle; }

    // �J�����V�F�C�N
    void Shake(int time,float);

    // ���S���̃J����
    void DeathCamera();

    bool flag=false;
private:
    int time;
    int state = 0;

    DirectX::XMFLOAT3   target = { 0,0,0 };
    DirectX::XMFLOAT3   angle = { 0,0,0 };
    float               rollSpeed = DirectX::XMConvertToRadians(90);
    float               range = 8.0f;

    float               maxAngleX = DirectX::XMConvertToRadians(45);
    float               minAngleX = DirectX::XMConvertToRadians(-45);

};