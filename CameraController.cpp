#include "CameraController.h"
#include "Camera.h"
#include"Input/Input.h"

//�X�V����
void CameraController::Update(float elapsedTime)
{
    GamePad& gamePad = Input::Instance().GetGamePad();
    float ax = gamePad.GetAxisRX();
    float ay = gamePad.GetAxisRY();
    // �J�����̉�]���x
    float speed = rollSpeed * elapsedTime;

    // �X�e�B�b�N�̓��͒l�ɍ��킹��X����Y������]
    angle.x -= ay * speed;
    angle.y += ax * speed;

    // �J�����̉�]�l����]�s��ɕϊ�
    DirectX::XMMATRIX Transform = DirectX::XMMatrixRotationRollPitchYaw(angle.x, angle.y, angle.z);

    // ��]�s�񂩂�O�����Ƀx�N�g�����o��
    DirectX::XMVECTOR Front = Transform.r[2];
    DirectX::XMFLOAT3 front;
    DirectX::XMStoreFloat3(&front, Front);

    DirectX::XMFLOAT3 eye = {};
    eye.x = target.x - front.x * range;// front=�����A�������|���Z���邱�ƂŒ������킩��
    eye.y = target.y - front.y * range;// �ڕW�n�_����J�����̋������������ƂŃJ�����̈ʒu���o��
    eye.z = target.z - front.z * range;// ����W�y�[�W
    // X���̃J������]�𐧌�
    angle.x = min(angle.x, maxAngleX);
    angle.x = max(angle.x, minAngleX);
    //�͔͉𓚁�
    if (angle.x < minAngleX)
    {
        angle.x = minAngleX;
    }
    if (angle.x > maxAngleX)
    {
        angle.x = maxAngleX;
    }

    // Y���̉�]�l��-3.14~3.14�Ɏ��܂�悤�ɂ���
    if (angle.y < -DirectX::XM_PI)
    {
        angle.y += DirectX::XM_2PI;
    }
    if (angle.y > -DirectX::XM_PI)
    {
        angle.y -= DirectX::XM_2PI;
    }

    //�J�����̎��_�ƒ����_��ݒ�
    Camera::Instance().SetLookAt(eye, target, DirectX::XMFLOAT3(0, 1, 0));
}