#include "BaseStage.h"

int BaseStage::SpawnStageCount = 0;

// ������
void BaseStage::clear()
{
    SpawnStageCount = 0;
}

// �X�N���[������
void BaseStage::UpdateVelocity(float elapsedTime)
{
    // [scrollVelocity]��nullptr�łȂ����[velocity]�ɑ��
    if (scrollVelocity != nullptr) velocity = *scrollVelocity;

    position.x += velocity.x * elapsedTime;
    position.z += velocity.z * elapsedTime;
}

//�s��X�V����
void BaseStage::UpdateTransform()
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

// �X�e�[�W�̐���
void BaseStage::StageSpawn()
{
    // ���s
    DepthSpawn();

    // ��
    LeftSpawn();

    // �E
    RightSpawn();
}

// ���s�̃X�e�[�W����
bool BaseStage::DepthSpawn()
{
    float spawnLine = -(scale.z * modelSize.z);
    if (spawnLine >= position.z)
    {
        // �����t���O�𗧂Ă�
        isSpawn = true;

        // ��������
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
        // �����t���O�𗧂Ă�
        isSpawn = true;

        // ��������
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
        // �����t���O�𗧂Ă�
        isSpawn = true;

        // ��������
        spawnPosition = { position.x - (scale.x * modelSize.x * stageSideMax) ,position.y,position.z };
        return true;
    }
    return false;
}

// �X�e�[�W�̍폜
void BaseStage::StageDelete()
{
    // ���_���1�X�e�[�W�����ɉ���������
    float deleteLine = -(scale.z * modelSize.z);
    if (deleteLine >= position.z)
    {
        // �폜�t���O�𗧂Ă�
        isDestroy = true;
    }

    // ��
    deleteLine = -(scale.x * modelSize.x * ((stageSideMax) * 0.5f));
    if (deleteLine >= position.x)
    {
        // �폜�t���O�𗧂Ă�
        isDestroy = true;
    }

    // �E
    deleteLine = (scale.x * modelSize.x * ((stageSideMax) * 0.5f));
    if (deleteLine <= position.x)
    {
        // �폜�t���O�𗧂Ă�
        isDestroy = true;
    }
}
