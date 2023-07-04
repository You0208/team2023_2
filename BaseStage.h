#pragma once
#include "Graphics/Shader.h"
#include "Graphics/Model.h"
#include "Obstacle.h"

// �X�e�[�W�̊��N���X
class BaseStage
{
public:
    BaseStage() {};
    virtual ~BaseStage() {};

    virtual void DrawDebugGUI() = 0;

    // ������
    virtual void Initialize() = 0;

    // �X�V����
    virtual void Update(float elapsedTime) = 0;

    // �`�揈��
    virtual void Draw(RenderContext rc, ModelShader* shader) = 0;

    void SetScrollVelocity(DirectX::XMFLOAT3* v) { scrollVelocity = v; };   // �X�N���[�����x�̃|�C���^���Z�b�g
    void SetPosition(DirectX::XMFLOAT3 p) { position = p; }                 // �ʒu�ݒ�
    bool GetIsDestroy() { return isDestroy; }                               // �폜�t���O�擾
    bool GetIsSpawn() { return isSpawn; }                                   // �����t���O�擾
    DirectX::XMFLOAT3 GetSpawnPosition() { return spawnPosition; }          // �����ʒu�擾
    DirectX::XMFLOAT3* GetAddressOfVelocity() { return &velocity; }         // velocity�̃|�C���^�[�擾
    DirectX::XMFLOAT3* GetPosition() { return &position; }

    static const int GetSpawnStageCount() { return SpawnStageCount; }               // �X�e�[�W�̐�������Ԃ�
    static void clear();                                                           // ������
protected:
    // �X�N���[������
    virtual void UpdateVelocity(float elapsedTime);

    //�s��X�V����
    virtual void UpdateTransform();

    // �X�e�[�W�̐���
    virtual void StageSpawn();
    // ���s�̃X�e�[�W����
    bool DepthSpawn();
    // ���̃X�e�[�W����
    bool LeftSpawn();
    // �E�̃X�e�[�W����
    bool RightSpawn();

    // �X�e�[�W�̍폜
    void StageDelete();

public:
    std::unique_ptr<Model> model = nullptr;

    std::vector<Obstacle*> obstacles;
protected:
    int stageSideMax                = 1;	                    // �X�e�[�W�̍ő吔(���E)
    int stageDepthMax               = 1;	                    // �X�e�[�W�̍ő吔(���s)
    DirectX::XMFLOAT3   position    = { 0.0f,0.0f,0.0f };       // �ʒu
    DirectX::XMFLOAT3   angle       = { 0.0f,0.0f,0.0f };       // �p�x
    DirectX::XMFLOAT3   scale       = { 1.0f,1.0f,1.0f };       // �X�P�[��
    DirectX::XMFLOAT3   modelSize   = { 1.0f,1.0f,1.0f };       // ���f���̃T�C�Y
    DirectX::XMFLOAT3   velocity    = { 0.0f,0.0f,0.0f };       // ���x
    const DirectX::XMFLOAT3* scrollVelocity = nullptr;          // �X�N���[�����x�̃|�C���^
    DirectX::XMFLOAT4X4 transform   = {
        1,0,0,0,
        0,1,0,0,
        0,0,1,0,
        0,0,0,1,
    };

    // �X�e�[�W����
    DirectX::XMFLOAT3 spawnPosition = { 0.0f,0.0f ,0.0f };      // �X�e�[�W�̐����ʒu
    bool isSpawn                    = false;                    // �X�e�[�W�����t���O
    // �X�e�[�W�폜
    bool isDestroy                  = false;                    // �X�e�[�W�폜�t���O
    bool a[2] = {};

    static int SpawnStageCount;                                 // ���������X�e�[�W�̐�
};

