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
    static constexpr float ScrollVelocityRate = 0.01f;              // �X�N���[�����x��ԌW��
    static constexpr float ScrollVelocityRate_ac = 0.001f;          // �X�N���[�����x��ԌW��(�������)
    static constexpr float MaxVelocity = -300.0f;                   // Velocity�̍ő�l
    static const int Gap = 2;                                       // �v���C���[�̈ʒu�ƃX�e�[�W���폜����ʒu�̍�
    static const int MaxBreakTime = 2;                                       // 

    // �e�󕠃��x���ł̃v���C���[�̍ő呬�x
    static constexpr float MaxPlayerVelocity[3] =
    {
        90.0f,     // �󕠃��x���F��
        60.0f,      // �󕠃��x���F��
        20.0f       // �󕠃��x���F��
    };
    // �e�󕠃��x���ł̃X�e�[�W�̍ő�X�N���[�����x
    static constexpr float MaxStageScrollVelocity[3] =
    {
        -150.0f,    // �󕠃��x���F��
        -100.0f,    // �󕠃��x���F��
        -75.0f      // �󕠃��x���F��
    };
    // �e�󕠃��x���ł̒n�`�̍ő�X�N���[�����x
    static constexpr float MaxTerrainScrollVelocity[3] =
    {
        -150.0f,    // �󕠃��x���F��
        -100.0f,    // �󕠃��x���F��
        -75.0f      // �󕠃��x���F��
    };

    // �X�e�[�W���؂�ւ�鋫��
    static constexpr int StageChangeLine[Stage::StageMax] =
    {
        5,      // �X�e�[�W2�؂�ւ�
        5,      // �X�e�[�W3�؂�ւ�
        5,      // �X�e�[�W4�؂�ւ�
        5,      // �X�e�[�W5�؂�ւ�
        5,      // �N���A
    };

    // �e�X�e�[�W���x���ł̃X�R�A�̏펞���Z��
    static constexpr float MaxAlwaysAddScore[Stage::StageMax + 1] =
    {
        1.0f,       // �X�e�[�W:1
        2.0f,       // �X�e�[�W:2
        3.0f,       // �X�e�[�W:3
        4.0f,       // �X�e�[�W:4
        5.0f,        // �X�e�[�W:5
        1.0f        // �G���h���X���[�h
    };
    // �e�󕠃��x���ł̃X�R�A�̏펞���Z�ʂ̔{��
    static constexpr float MaxAlwaysAddScoreMagnification[3] =
    {
        2.0f,       // �󕠃��x���F�� 
        1.0f,       // �󕠃��x���F�� 
        0.5f        // �󕠃��x���F�� 
    };
    // �N���A�{�[�i�X
    static constexpr int StageClearcBonus[Stage::StageMax + 1] =
    {
        100,       // �X�e�[�W:1
        200,       // �X�e�[�W:2
        300,       // �X�e�[�W:3
        400,       // �X�e�[�W:4
        500,       // �X�e�[�W:5
        0,         // �G���h���X���[�h(�o�O�h�~)
    };

    struct SpawnData
    {
        DirectX::XMFLOAT3 position;     // �����ʒu
        bool IsDepthSpawn;              // ��������
    };

public:
    StageManager();
    ~StageManager();

    void DrawDebugGUI();

    // �X�V����
    void Update(Player* player, float elapsedTIme);

    // �Z���N�g��ʂł̍X�V
    void StageSelectUpdate(float elapsedTIme);

    // ���S���̍X�V
    void StageDeathUpdate(float elapsedTIme);

    // �`�揈��
    void Draw(RenderContext rc, ModelShader* shader);

    // ��Q���\��:�V�F�[�_�[�p
    void ObsDraw(RenderContext rc, ModelShader* shader);

    // �X�e�[�W�o�^
    void Register(Stage* stage);

    // �S�폜
    void Clear();

    // �X�e�[�W����
    void StageSpawn(SpawnData data);

    // �n�`����
    void TerrainSpawn(DirectX::XMFLOAT3 position);

    // ��������
    void AddVelocity(float addVelocity,float timer);

    // �v���C���[���������X�e�[�W�̐���Ԃ�
    int GetDoneStageNum() const{ return doneStageNum; }

    void setVelocityZ(int i) {  stageScrollVelocity.z = i; }

    float getVelocityZ() const { return stageScrollVelocity.z; }

    // ���̃X�e�[�W�ԍ���Ԃ�
    int GetStageNo() const { return stageNo; }

    // �N���A�t���O�擾
    static bool const GetIsClear() { return IsClear; }
    // �G���h���X�t���O�擾
    static bool const GetEndless() { return Endless; }

    // �N���A�t���O��܂�
    static void FoldIsClear() { IsClear = false; }
    // �G���h���X�t���O��܂�
    static void FoldEndless() { Endless = false; }

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
    void UpdataHorizontalVelocity(float elapsedFrame, Player* player);

    // BreakTime_State���Z�b�g
    void SetBreakTime_State();

    // �x�e���ԍX�V
    void UpdateBreakTime(float elapsedFrame, Player* player);

    // doneStageNum�̉��Z
    void AddDoneStageNum(float elapsedTIme);

    // �X�R�A�̍X�V(�펞���Z)
    void UpdateScore(Player* player,float elapsedTime);

public:
    bool IsStart = true;
    float VZ = 0;

    std::vector<BaseStage*>             stages;                         // �X�e�[�W���X�g
    // �X�e�[�W�̃X�N���[�����x�X�V
    void UpdateScrollVelocity(DirectX::XMFLOAT3& ScrollVelocity,float maxVelocity,float rate);

    bool IsBreakTime = false;                                           // �x�e�t���O
    bool IsSpawnNone_Side = false;                                      // �����Ȃ��X�e�[�W�𐶐�����t���O(�T�C�h)
    bool IsSpawnNone_Depth = false;                                     // �����Ȃ��X�e�[�W�𐶐�����t���O(���s)
    static int   stageNo;                                               // ���݂̃X�e�[�W

    // �f�o�b�O�̂��߂�public�ɂ����Ă�
    static bool IsClear;                                                // �N���A�t���O
private:
    // �X�e�[�W�f�[�^
    DirectX::XMFLOAT3 stageScrollVelocity = { 0.0f,0.0f ,-10.0f };      // ���ʂ̃X�N���[�����x�̃|�C���^
    std::set<BaseStage*>                stageRemoves;                   // �폜���X�g
    std::vector<SpawnData>              stagesSpawns;                   // �������X�g(�ʒu���������Ă���)

    // �n�`�f�[�^
    DirectX::XMFLOAT3 terrainScrollVelocity = { 0.0f,0.0f ,-10.0f };    // ���ʂ̃X�N���[�����x�̃|�C���^
    std::vector<BaseStage*>             terrains;                       // �X�e�[�W���X�g
    std::set<BaseStage*>                terrainRemoves;                 // �폜���X�g
    std::vector<DirectX::XMFLOAT3>      terrainSpawns;                  // �������X�g(�ʒu���������Ă���)

    float breakTimer = 0.0f;                                             // �x�e�^�C�}�[
    int breakTime = 0;                                                   // �x�e�^�C�}�[
    int breakTime_State = 0;                                             // �u���C�N�^�C���J�n����X�e�[�W
    int breakTime_End = 0;                                               // �u���C�N�^�C���I������X�e�[�W
    bool IsClearVerge = false;                                           // �N���A�ڑO�t���O
    static bool Endless;                                                 // �G���h���X���[�h�t���O

    float moveVecX = 0.0f;                                              // �ړ������x�N�g��
    float maxPlayerVelocity = 20.0f;                                    // �v���C���[�̍ő呬�x
    int doneStageNum        = 0;                                        // �v���C���[���������X�e�[�W�̐�

   // ===== ��g�p�@��Ŏg�������H =====
    float friction = 5.0f;                                              // ����
    float acceleration = 10.0f;                                         // ������

    float scrollVelocityRate = 0.0f;                                    // �X�N���[�����x��ԌW��
    float accelerationTimer = 0.0f;                                     // �����^�C�}�[(0�ȏ�̂Ƃ�������Ԃł���)
};