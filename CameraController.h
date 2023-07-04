#pragma once

#include<DirectXMath.h>

//カメラコントローラー
class CameraController
{
public:
    CameraController() {}
    ~CameraController() {}

    // 更新処理
    void Update(float elapsedTime);

    // ターゲット位置設定
    void setTarget(const DirectX::XMFLOAT3& target) { this->target = target; }

    // ターゲット位置設定
    void setTargetY(float y) { this->target.y = y; }

    void setRange(float i) { range = i; }

    float getRange() { return range; }

    DirectX::XMFLOAT3 getAngle() { return angle; }

    // カメラシェイク
    void Shake(int time,float);

    // 死亡時のカメラ
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