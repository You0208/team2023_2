#include "CameraController.h"
#include "Camera.h"
#include "Tool.h"
#include"Input/Input.h"

//更新処理
void CameraController::Update(float elapsedTime)
{
    // カメラの回転値を回転行列に変換
    DirectX::XMMATRIX Transform = DirectX::XMMatrixRotationRollPitchYaw(angle.x, angle.y, angle.z);

    // 回転行列から前方向にベクトルを出す
    DirectX::XMVECTOR Front = Transform.r[2];
    DirectX::XMFLOAT3 front;
    DirectX::XMStoreFloat3(&front, Front);

    DirectX::XMFLOAT3 eye = {};
    eye.x = target.x - front.x * range;// front=方向、長さを掛け算することで長さがわかる
    eye.y = target.y - front.y * range;// 目標地点からカメラの距離を引くことでカメラの位置が出る
    eye.z = target.z - front.z * range;// 解説８ページ
    // X軸のカメラ回転を制限
    angle.x = min(angle.x, maxAngleX);
    angle.x = max(angle.x, minAngleX);
    //模範解答↓
    if (angle.x < minAngleX)
    {
        angle.x = minAngleX;
    }
    if (angle.x > maxAngleX)
    {
        angle.x = maxAngleX;
    }

    // Y軸の回転値を-3.14~3.14に収まるようにする
    //if (angle.y < -DirectX::XM_PI)
    //{
    //    angle.y += DirectX::XM_2PI;
    //}
    //if (angle.y > -DirectX::XM_PI)
    //{
    //    angle.y -= DirectX::XM_2PI;
    //}

    //カメラの視点と注視点を設定
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
