#include "StageManager.h"
#include<imgui.h>
#include <Input/Input.h>

// �R���X�g���N�^
StageManager::StageManager()
{
}

// �f�X�g���N�^
StageManager::~StageManager()
{
    Clear();
}

void StageManager::DrawDebugGUI()
{
    //for (BaseStage* stage : stages)
    //{
    //    stage->DrawDebugGUI();
    //}

    Stage::DrawDebugGUI_();

    ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(ImVec2(300, 300), ImGuiCond_FirstUseEver);

    if (ImGui::Begin("StageManager", nullptr, ImGuiWindowFlags_None))
    {
        ImGui::SliderFloat("scrollVelocityZ", &stageScrollVelocity.z, 0.0f, -100.0f);
        ImGui::SliderFloat("terrainScrollVelocityZ", &terrainScrollVelocity.z, 0.0f, -100.0f);
    }

    // �X�N���[����~
    if (ImGui::Button("STOP")) {
        stageScrollVelocity = { 0.0f,0.0f ,0.0f };
        terrainScrollVelocity = { 0.0f,0.0f ,0.0f };
    }
    // �X�N���[���X�^�[�g
    if (ImGui::Button("STATE")) {
        stageScrollVelocity = { 0.0f,0.0f ,-10.0f };
        terrainScrollVelocity = { 0.0f,0.0f ,-10.0f };
    }

    ImGui::Text("[I][J][K][L] : camera");
    ImGui::Text("[A][D] : player");
    ImGui::Text("[X] : HitAnime");

    ImGui::End();
}

// �X�V����
void StageManager::Update(Player* player, float elapsedTIme)
{
    // �v���C���[�̃_���[�W�A�j���Đ��͈ȉ��̏������s��Ȃ�
    if(player->GetIsDamageAnim()) return;

    // �ړ����͏���
    InputMove(elapsedTIme);

    // ���x�����X�V
    UpdateVelocity(elapsedTIme, player);

    // �X�e�[�W�̍X�V
    StageUpdate(elapsedTIme);

    // �n�`�X�V
    TerrainUpdate(elapsedTIme);
}

// �`�揈��
void StageManager::Draw(RenderContext rc, ModelShader* shader)
{
    // �X�e�[�W�`��
    for (BaseStage* stage : stages)
    {
        stage->Draw(rc, shader);
    }

    // �n�`�`��
    /*for (BaseStage* terrain : terrains)
    {
        terrain->Draw(rc, shader);
    }*/
}

// �X�e�[�W�o�^
void StageManager::Register(Stage* stage)
{
    stages.emplace_back(stage);
}

// �X�e�[�W�S�폜
void StageManager::Clear()
{
    // <�X�e�[�W>
    // ���X�g�폜
    for (BaseStage* stage : stages)
    {
        delete stage;
        stage = nullptr;
    }
    stages.clear();
    // �폜���X�g�폜
    for (BaseStage* remove : stageRemoves)
    {
        delete remove;
        remove = nullptr;
    }
    stageRemoves.clear();
    // �X�|�[���f�[�^�폜
    stagesSpawns.clear();


    // <�n�`>
    // ���X�g�폜
    for (BaseStage* stage : terrains)
    {
        delete stage;
        stage = nullptr;
    }
    terrains.clear();
    // �폜���X�g�폜
    for (BaseStage* remove : terrainRemoves)
    {
        delete remove;
        remove = nullptr;
    }
    terrainRemoves.clear();
    // �X�|�[���f�[�^�폜
    terrainSpawns.clear();
}

// �X�e�[�W����
void StageManager::StageSpawn(DirectX::XMFLOAT3 position)
{
    //Stage* s = new Stage();//�����_���Ȏ�ނ̃X�e�[�W�𐶐�
    Stage* s = new Stage;           //�X�e�[�W�𐶐�
    s->SetPosition(position);// �����ŃX�e�[�W�̃|�W�V���������߂�
    s->SetScrollVelocity(&stageScrollVelocity);  // ���ʂ̃X�N���[�����x��ݒ�
    s->Initialize();
    stages.emplace_back(s);
}

// �X�e�[�W�̍X�V
void StageManager::StageUpdate(float elapsedTIme)
{
    // �X�e�[�W�̐���
    for (DirectX::XMFLOAT3 data : stagesSpawns)
    {
        StageSpawn(data);
    }
    stagesSpawns.clear();

    // �X�e�[�W�̍X�V����
    for (BaseStage* stage : stages)
    {
        stage->Update(elapsedTIme);

        // �폜���X�g�ǉ�
        if (stage->GetIsDestroy())
        {
            stageRemoves.insert(stage);
        }

        // �������X�g�ǉ�
        if (stage->GetIsSpawn())
        {
            stagesSpawns.emplace_back(stage->GetSpawnPosition());
        }
    }

    // �X�e�[�W�̍폜
    for (BaseStage* remove : stageRemoves)
    {
        std::vector<BaseStage*>::iterator it
            = std::find(stages.begin(), stages.end(), remove);

        // remove�̃f�[�^��stages�ɂ����
        if (it != stages.end())
        {
            stages.erase(it);
        }
        delete remove;
    }
    // �j�����X�g���N���A
    stageRemoves.clear();
}

// �n�`�̍X�V
void StageManager::TerrainUpdate(float elapsedTIme)
{
    // �X�e�[�W�̐���
    for (DirectX::XMFLOAT3 data : terrainSpawns)
    {
        TerrainSpawn(data);
    }
    terrainSpawns.clear();

    // �X�e�[�W�̍X�V����
    for (BaseStage* stage : terrains)
    {
        stage->Update(elapsedTIme);

        // �폜���X�g�ǉ�
        if (stage->GetIsDestroy())
        {
            terrainRemoves.insert(stage);
        }

        // �������X�g�ǉ�
        if (stage->GetIsSpawn())
        {
            terrainSpawns.emplace_back(stage->GetSpawnPosition());
        }
    }

    // �X�e�[�W�̍폜
    for (BaseStage* remove : terrainRemoves)
    {
        std::vector<BaseStage*>::iterator it
            = std::find(terrains.begin(), terrains.end(), remove);

        // remove�̃f�[�^��stages�ɂ����
        if (it != terrains.end())
        {
            terrains.erase(it);
        }
        delete remove;
    }
    // �j�����X�g���N���A
    terrainRemoves.clear();
}

// �n�`����
void StageManager::TerrainSpawn(DirectX::XMFLOAT3 position)
{
    Terrain* s = new Terrain;           //�n�`�𐶐�
    s->SetPosition(position);// �����ŃX�e�[�W�̃|�W�V���������߂�
    s->SetScrollVelocity(&terrainScrollVelocity);  // ���ʂ̃X�N���[�����x��ݒ�
    s->Initialize();
    terrains.emplace_back(s);
}

// �X�e�B�b�N���͒l����ړ��x�N�g�����擾
DirectX::XMFLOAT3 StageManager::GetMoveVec()
{
    // ���͏����擾
    GamePad& gamePad = Input::Instance().GetGamePad();
    float ax = gamePad.GetAxisLX();
    DirectX::XMFLOAT3 vec = { ax ,0.0f,0.0f };

    return vec;
}

// �ړ����͏���
void StageManager::InputMove(float elapsedTime)
{
    // �i�s�x�N�g���擾
    DirectX::XMFLOAT3 moveVec = GetMoveVec();

    // �ړ������x�N�g����ݒ�
    // (���]������)
    moveVecX = moveVec.x * -1;
}

// ���x�����X�V
void StageManager::UpdateVelocity(float elapsedTime, Player* player)
{
    // �o�߃t���[��
    float elapsedFrame = 60.0f * elapsedTime;

    // �������͍X�V����
    UpdataHorizontalVelocity(elapsedFrame);

    player->SetVelocity({ -stageScrollVelocity.x,0.0f,0.0f });
}

// �������͍X�V����
void StageManager::UpdataHorizontalVelocity(float elapsedFrame)
{
    // XZ���ʂ̑��͂���������
    float length = sqrtf(stageScrollVelocity.x * stageScrollVelocity.x);
    //if (length > 0.0f)
    //{
    //    // ���C��
    //    float friction = this->friction * elapsedFrame;

    //    // ���C�ɂ�鉡�����̌�������
    //    if (length > friction)
    //    {
    //        float vx = stageScrollVelocity.x / length;

    //        stageScrollVelocity.x -= vx * friction;
    //    }
    //    // �������̑��͂����C�͈ȉ��ɂȂ����̂ő��͂𖳌���
    //    else
    //    {
    //        stageScrollVelocity.x = 0;
    //    }
    //}

    // XZ���ʂ̑��͂���������
    if (length <= maxMoveSpeed)
    {
        // �ړ��x�N�g�����[���x�N�g���o�Ȃ��Ȃ��������
        float moveVecLength = sqrtf(moveVecX * moveVecX);
        if (moveVecLength > 0.0f)
        {
            // ������
            float acceleration = this->acceleration * elapsedFrame;

            // �ړ��x�N�g���ɂ���������
            stageScrollVelocity.x += moveVecX * acceleration;

            // �ő呬�x����
            float length = sqrtf(stageScrollVelocity.x * stageScrollVelocity.x);
            if (length > maxMoveSpeed)
            {
                float vx = stageScrollVelocity.x / length;

                stageScrollVelocity.x = vx * maxMoveSpeed;
            }
        }
    }

    // moveVecX��0�Ȃ�Velocity��0�ɂ���
    if ((moveVecX < FLT_EPSILON) && (moveVecX > -FLT_EPSILON))
    {
        stageScrollVelocity.x = 0.0f;
    }

    // �n�`�f�[�^�̑��͂ɑ��
    terrainScrollVelocity.x = stageScrollVelocity.x;

    // �ړ��x�N�g�������Z�b�g
    moveVecX = 0.0f;
}