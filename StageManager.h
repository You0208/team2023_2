#pragma once

#include "Graphics/Shader.h"
#include <vector>
#include "Player.h"
#include "Stage.h"
#include "Terrain.h"
#include <set>

// �X�e�[�W�}�l�[�W���[
class StageManager
{
private:
    static constexpr float ScrollVelocityRate = 0.1f;          // �X�N���[�����x��ԌW��

    // �e�󕠃��x���ł̃X�e�[�W�̍ő�X�N���[�����x
    static constexpr float MaxStageScrollVelocity[3] =
    {
        20.0f,      // �󕠃��x���F��
        50.0f,      // �󕠃��x���F��
        100.0f      // �󕠃��x���F��
    };
    // �e�󕠃��x���ł̃X�e�[�W�̍ő�X�N���[�����x
    static constexpr float MaxTerrainScrollVelocity[3] =
    {
        100.0f,      // �󕠃��x���F��
        50.0f,      // �󕠃��x���F��
        20.0f      // �󕠃��x���F��
    };

public:
    StageManager();
    ~StageManager();

    void DrawDebugGUI();

    // �X�V����
    void Update(Player* player, float elapsedTIme);

    // �`�揈��
    void Draw(RenderContext rc, ModelShader* shader);

    // �X�e�[�W�o�^
    void Register(Stage* stage);

    // �S�폜
    void Clear();

    // �X�e�[�W����
    void StageSpawn(DirectX::XMFLOAT3 position);

    // �n�`����
    void TerrainSpawn(DirectX::XMFLOAT3 position);


private:
    // �X�e�[�W�̍X�V
    void StageUpdate(float elapsedTIme);

    // �n�`�̍X�V
    void TerrainUpdate(float elapsedTIme);

    // �ړ����͏���
    void InputMove(float elapsedTime);

    // ���x�����X�V
    void UpdateVelocity(float elapsedTime,Player* player);

    // �X�e�B�b�N���͒l����ړ��x�N�g�����擾
    DirectX::XMFLOAT3 GetMoveVec();

    // �������͍X�V����
    void UpdataHorizontalVelocity(float elapsedFrame);

    // �X�e�[�W�̃X�N���[�����x�X�V
    void UpdateScrollVelocity(DirectX::XMFLOAT3 ScrollVelocity,float maxVelocity,float rate);
private:
    // �X�e�[�W�f�[�^
    DirectX::XMFLOAT3 stageScrollVelocity = { 0.0f,0.0f ,-10.0f };      // ���ʂ̃X�N���[�����x�̃|�C���^
    std::vector<BaseStage*>             stages;                         // �X�e�[�W���X�g
    std::set<BaseStage*>                stageRemoves;                   // �폜���X�g
    std::vector<DirectX::XMFLOAT3>      stagesSpawns;                   // �������X�g(�ʒu���������Ă���)

    // �n�`�f�[�^
    DirectX::XMFLOAT3 terrainScrollVelocity = { 0.0f,0.0f ,-10.0f };    // ���ʂ̃X�N���[�����x�̃|�C���^
    std::vector<BaseStage*>             terrains;                       // �X�e�[�W���X�g
    std::set<BaseStage*>                terrainRemoves;                 // �폜���X�g
    std::vector<DirectX::XMFLOAT3>      terrainSpawns;                  // �������X�g(�ʒu���������Ă���)


    float moveVecX = 0.0f;                                              // �ړ������x�N�g��
    float maxMoveSpeed = 20.0f;                                         // �ő�ړ����x
    float friction = 0.5f;                                              // ����
    float acceleration = 10.0f;                                         // ������
};