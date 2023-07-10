#include "BaseStage.h"
#include "SceneManager.h"

void BaseStage::GetDelete()
{
    //TODO　見直し
    for (int i = 0; i < obstacles.size(); i++)
    {
        if (obstacles[i]->IsGet)
        {
            // エフェクト終了
            if (obstacles[i]->ItemEffect != nullptr)
            {
                obstacles[i]->ItemEffect->Stop(obstacles[i]->handle);
                obstacles[i]->once=true;
                //delete obstacles[i]->ItemEffect;
                //obstacles[i]->ItemEffect = nullptr;
            }
            delete obstacles[i];
            // 要素を削除する
            obstacles.erase(obstacles.begin() + i);
        }
    }
}

// 初期化
void BaseStage::clear()
{
}

// スクロール処理
void BaseStage::UpdateVelocity(float elapsedTime)
{
    // [scrollVelocity]がnullptrでなければ[velocity]に代入
    if (scrollVelocity != nullptr) velocity = *scrollVelocity;

    position.x += velocity.x * elapsedTime;
    position.z += velocity.z * elapsedTime;
}

//行列更新処理
void BaseStage::UpdateTransform()
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

// ステージの生成
void BaseStage::StageSpawn()
{
    // 奥行
    DepthSpawn();

    // 左
    LeftSpawn();

    // 右
    RightSpawn();
}

// 奥行のステージ生成
bool BaseStage::DepthSpawn()
{
    float spawnLine = -(scale.z * modelSize.z);
    if (spawnLine >= position.z)
    {
        // 生成フラグを立てる
        isSpawn = true;

        // 生成処理
        spawnPosition = { position.x,position.y,position.z + (scale.z * modelSize.z * stageDepthMax) };
        return true;
    }
    return false;
}

bool BaseStage::LeftSpawn()
{
    float spawnLine = -(scale.x * modelSize.x * ((stageSideMax) * 0.5f));
    if (spawnLine >= position.x)
    {
        // 生成フラグを立てる
        isSpawn = true;

        // 生成処理
        spawnPosition = { position.x + (scale.x * modelSize.x * stageSideMax) ,position.y,position.z };
        return true;
    }
    return false;
}

bool BaseStage::RightSpawn()
{
    float spawnLine = (scale.x * modelSize.x * ((stageSideMax) * 0.5f));
    if (spawnLine <= position.x)
    {
        // 生成フラグを立てる
        isSpawn = true;

        // 生成処理
        spawnPosition = { position.x - (scale.x * modelSize.x * stageSideMax) ,position.y,position.z };
        return true;
    }
    return false;
}

// ステージの削除
void BaseStage::StageDelete()
{
    // 原点より1ステージ分後ろに下がったら
    float deleteLine = -(scale.z * modelSize.z);
    if (deleteLine >= position.z)
    {
        // 削除フラグを立てる
        isDestroy = true;
    }

    // 左
    deleteLine = -(scale.x * modelSize.x * ((stageSideMax) * 0.5f));
    if (deleteLine >= position.x)
    {
        // 削除フラグを立てる
        isDestroy = true;
    }

    // 右
    deleteLine = (scale.x * modelSize.x * ((stageSideMax) * 0.5f));
    if (deleteLine <= position.x)
    {
        // 削除フラグを立てる
        isDestroy = true;
    }
}
