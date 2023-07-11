#include "CameraController.h"
#include "Camera.h"
#include "Tool.h"
#include"Input/Input.h"

//�X�V����
void CameraController::Update(float elapsedTime)
{
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
    //if (angle.y < -DirectX::XM_PI)
    //{
    //    angle.y += DirectX::XM_2PI;
    //}
    //if (angle.y > -DirectX::XM_PI)
    //{
    //    angle.y -= DirectX::XM_2PI;
    //}

    //�J�����̎��_�ƒ����_��ݒ�
    Camera::Instance().SetLookAt(eye, target, DirectX::XMFLOAT3(0, 1, 0));
}

void CameraController::Shake(int t,float n)
{
    if (flag)
    {
        switch (state)
        {
        case 0:
            time = t;
            state++;
            break;
        case 1:
            time -= 1;
            if (time > 0)
            {
                if(time%2==0)target.x = ((1 ^ (-time / 10)) * cosf(time / 0.5f) * cosf(time / 1))*0.15f;
                else if (time % 2 != 0)target.y = n + ((1 ^ (-time / 10)) * cosf(time / 0.5f) * cosf(time / 1)) * 0.15f;
            }
            else if (time <= 0)
            {
                time = 0;
                state = 0;
                flag = false;
            }
        }
    }
}


void CameraController::DeathCamera()
{
    if (angle.x < DirectX::XMConvertToRadians(70.0f))
        angle.x += DirectX::XMConvertToRadians(0.1f);
    if (angle.y < DirectX::XMConvertToRadians(45.0f))
    {
        angle.y += DirectX::XMConvertToRadians(0.1f);
    }
}

void CameraController::DidFromHungerCamera()
{
    range = lerp(range, 15.0f, 0.01f);
    if (angle.x < DirectX::XMConvertToRadians(70.0f))
        angle.x += DirectX::XMConvertToRadians(0.1f);
    if (angle.y < DirectX::XMConvertToRadians(45.0f))
    {
        angle.y += DirectX::XMConvertToRadians(0.1f);
    }
}
