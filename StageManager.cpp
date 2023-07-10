#include "StageManager.h"
#include "Tool.h"
#include<imgui.h>
#include <Input/Input.h>

int StageManager::stageNo = 0;

// �R���X�g���N�^
StageManager::StageManager()
{
    // �������x�ݒ�
    stageScrollVelocity.z = MaxStageScrollVelocity[1];
    terrainScrollVelocity.z = MaxTerrainScrollVelocity[1];

    scrollVelocityRate = ScrollVelocityRate;
}

// �f�X�g���N�^
StageManager::~StageManager()
{
    Clear();
}

void StageManager::DrawDebugGUI()
{
    Stage::DrawDebugGUI_();

    ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(ImVec2(300, 300), ImGuiCond_FirstUseEver);

    if (ImGui::Begin("StageManager", nullptr, ImGuiWindowFlags_None))
    {
        ImGui::SliderFloat("scrollVelocityZ", &stageScrollVelocity.z, 0.0f, -300.0f);
        ImGui::SliderFloat("terrainScrollVelocityZ", &terrainScrollVelocity.z, 0.0f, -300.0f);
    }

    ImGui::Text("DoneStageNu:%ld", doneStageNum);
    ImGui::Text("stageNo:%ld", stageNo);
    ImGui::Text("accelerationTimer:%d", static_cast<int>(accelerationTimer));

    ImGui::Text("IsBreakTime:%d", static_cast<int>(IsBreakTime));
    ImGui::Text("IsSpawnNone:%d", static_cast<int>(IsSpawnNone_Side));

    // �c��x�e����
    ImGui::Text("IsBreakTime:%lf", breakTimer);

    ImGui::Text("[I][J][K][L] : camera");
    ImGui::Text("[A][D] : player");
    ImGui::Text("[X] : HitAnime");
    ImGui::Text("[C] : pause");

    ImGui::End();
}

// �X�V����
void StageManager::Update(Player* player, float elapsedTIme)
{

    // �v���C���[�̃_���[�W�A�j���Đ��͈ȉ��̏������s��Ȃ�
    if(player->GetIsDamageAnim()) return;

    // �X�R�A�̍X�V(�펞���Z)
    UpdateScore(player, elapsedTIme);

    // �X�e�[�W�؂�ւ�
    SetBreakTime_State();

    // �ړ����͏���
    InputMove(elapsedTIme);

    // ���x�����X�V
    UpdateVelocity(elapsedTIme, player);

    // doneStageNum�̉��Z
    AddDoneStageNum(elapsedTIme);

    // �X�e�[�W�̍X�V
    StageUpdate(elapsedTIme);

    // �n�`�X�V
    TerrainUpdate(elapsedTIme);

    // �x�e���ԍX�V
    UpdateBreakTime(elapsedTIme, player);
    player->IsBreakTime = IsBreakTime;
}

// �Z���N�g�X�V
void StageManager::StageSelectUpdate(float elapsedTIme)
{
    stageScrollVelocity = { 0,0,0 };
    terrainScrollVelocity = { 0,0,0 };
    // �X�e�[�W�̍X�V
    StageUpdate(elapsedTIme);

    // �n�`�X�V
    TerrainUpdate(elapsedTIme);
}

void StageManager::StageDeathUpdate(float elapsedTIme)
{
    //VZ = lerp(VZ, 100.0f, 0.001f);
    //stageScrollVelocity = { 0,0,VZ };
    //terrainScrollVelocity = { 0,0,VZ };
    stageScrollVelocity = { 0,0,0 };
    terrainScrollVelocity = { 0,0,0 };
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
    for (BaseStage* terrain : terrains)
    {
        terrain->Draw(rc, shader);
    }
}

void StageManager::ObsDraw(RenderContext rc, ModelShader* shader)
{   // �X�e�[�W�`��
    for (BaseStage* stage : stages)
    {
        for (auto& it : stage->obstacles)
        {
            it->Draw(rc, shader);
        }
    }
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
void StageManager::StageSpawn(SpawnData data)
{
    int No = (SceneManager::Instance().IsNoneStage && !data.IsDepthSpawn) ||
        // ���s�̐������֎~����Ă���������͍��E�̐������֎~����Ă��č��E�ɐ��������ꍇ-1��Ԃ�
        IsSpawnNone_Depth || (IsSpawnNone_Side && !data.IsDepthSpawn)
        // Stage�̈�������0�ȉ��̏ꍇStageNONE�����������
        ? -1 : stageNo;            

    Stage* s = new Stage(No);                       //�X�e�[�W�𐶐�
    s->SetPosition(data.position);                       // �����ŃX�e�[�W�̃|�W�V���������߂�
    s->SetScrollVelocity(&stageScrollVelocity);     // ���ʂ̃X�N���[�����x��ݒ�
    s->Initialize();                                // ��Q������
    stages.emplace_back(s);                         // �R���e�i�ǉ�
}

// �X�e�[�W�̍X�V
void StageManager::StageUpdate(float elapsedTIme)
{
    // �X�e�[�W�̐���
    for (SpawnData data : stagesSpawns)
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
            SpawnData data = { stage->GetSpawnPosition(), stage->GetisIsDepthSpawn() };
            stagesSpawns.emplace_back(data);
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
    Terrain* s = new Terrain;                       //�n�`�𐶐�
    s->SetPosition(position);                       // �����ŃX�e�[�W�̃|�W�V���������߂�
    s->SetScrollVelocity(&terrainScrollVelocity);   // ���ʂ̃X�N���[�����x��ݒ�
    s->Initialize();
    terrains.emplace_back(s);
}

void StageManager::AddVelocity(float addVelocity, float timer)
{
    accelerationTimer = timer;
    stageScrollVelocity.z -= addVelocity;
    terrainScrollVelocity.z -= addVelocity;
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

    // �v���C���[�̍ő呬�x�X�V
    maxPlayerVelocity = MaxPlayerVelocity[player->GetHungerLevel()];

    // �������͍X�V����
    UpdataHorizontalVelocity(elapsedFrame, player);

    player->SetVelocity({ -stageScrollVelocity.x,0.0f,0.0f });

    // ������ԂȂ�
    if (accelerationTimer >= 0.0f)
    {
        accelerationTimer      -= elapsedTime;
        scrollVelocityRate      = ScrollVelocityRate_ac;
        stageScrollVelocity.z   = (std::max)(stageScrollVelocity.z, MaxVelocity);
        terrainScrollVelocity.z = (std::max)(terrainScrollVelocity.z, MaxVelocity);
    }
    else scrollVelocityRate = ScrollVelocityRate;

    // �X�e�[�W�̃X�N���[�����x�X�V
    UpdateScrollVelocity(stageScrollVelocity, MaxStageScrollVelocity[player->GetHungerLevel()], scrollVelocityRate);
    
    // �n�`�̃X�N���[�����x�X�V
    UpdateScrollVelocity(terrainScrollVelocity, MaxTerrainScrollVelocity[player->GetHungerLevel()], scrollVelocityRate);
}

// �������͍X�V����
void StageManager::UpdataHorizontalVelocity(float elapsedFrame, Player* player)
{
    float length = sqrtf(stageScrollVelocity.x * stageScrollVelocity.x);

#if 0
    // �󕠏�Ԃł���Ƃ�
    if (player->GetHungerLevel() == 0)
    {
        // XZ���ʂ̑��͂���������

        // �L�[�𗣂��Ƃ����~�܂��Ăق��̂Ō��������Ȃ�
        float length = sqrtf((stageScrollVelocity.x * stageScrollVelocity.x));
        if (length > 0.0f)
        {
            // ���C��
            float friction = this->friction * elapsedFrame;

            // ���C�ɂ�鉡�����̌�������[09]
            if (length > friction)
            {
                float vx = stageScrollVelocity.x / length;
                stageScrollVelocity.x -= vx * friction;
            }
            // �������̑��͂����C�͈ȉ��ɂȂ����̂ő��͂𖳌���[09]
            else
            {
                stageScrollVelocity.x = 0.0f;
            }
        }
    }
    // �󕠏�ԂłȂ��Ƃ�
    else
    {
        // moveVecX��0�Ȃ�Velocity��0�ɂ���
        if ((moveVecX < FLT_EPSILON) && (moveVecX > -FLT_EPSILON))
        {
            stageScrollVelocity.x = 0.0f;
        }
    }
#else
    if ((moveVecX < FLT_EPSILON) && (moveVecX > -FLT_EPSILON))
    {
        stageScrollVelocity.x = 0.0f;
    }

#endif

    // XZ���ʂ̑��͂���������
    if (length <= maxPlayerVelocity)
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
            if (length > maxPlayerVelocity)
            {
                float vx = stageScrollVelocity.x / length;

                stageScrollVelocity.x = vx * maxPlayerVelocity;
            }
        }
    }


    // �n�`�f�[�^�̑��͂ɑ��
    terrainScrollVelocity.x = stageScrollVelocity.x;

    // �ړ��x�N�g�������Z�b�g
    moveVecX = 0.0f;
}

// BreakTime_State���Z�b�g
void StageManager::SetBreakTime_State()
{
    //�@�u���C�N�^�C���͈ȉ��̏��������Ȃ�
    if (IsBreakTime) return;

    for (int i = stageNo ;i < Stage::StageMax - 1;++i)
    {
        if (doneStageNum >= StageChangeLine[i] - (Stage::StageDepthMax - 1))    // 1���͎��@�̌��ɍs���̂�
        {
            IsSpawnNone_Depth = true;
            IsSpawnNone_Side = true;
            breakTime_State = StageChangeLine[i];
            break;
        }
    }       
}

// �x�e���ԍX�V
void StageManager::UpdateBreakTime(float elapsedFrame, Player* player)
{
    if (IsSpawnNone_Depth)
    {
        // �u���C�N�^�C���J�n����X�e�[�W�𒴂����@���@�u���C�N�^�C���łȂ��Ƃ�
        if (!IsBreakTime && breakTime_State <= doneStageNum)
        {
            player->AddScore(StageClearcBonus[stageNo]);    // �X�e�[�W�N���A��V
            stageNo++;                                      // ���̃X�e�[�W�ɐ؂�ւ�
            IsBreakTime = true;
            breakTime_End = doneStageNum + MaxBreakTime;
        }

        // �X�e�[�W�̐����ĊJ
        if (IsBreakTime && breakTime_End - MaxBreakTime <= doneStageNum)
        {
            IsSpawnNone_Depth = false;
        }
    }
    // �u���C�N�^�C���Ȃ�
    else if (IsBreakTime && breakTime_End <= doneStageNum)
    {
        IsSpawnNone_Side = false;
        IsBreakTime = false;
        doneStageNum = 0;
    }


}

// doneStageNum�̉��Z
void StageManager::AddDoneStageNum(float elapsedTIme)
{
    // �X�e�[�W�̈ʒu(z)
    static float z = + (Stage::StageSize*0.5f);     // ��������ʂ̒��S����n�܂邽��
    z -= stageScrollVelocity.z * elapsedTIme;

    // �X�e�[�W���傫���Ȃ��
    if (z >= Stage::StageSize)
    {
        z = 0.0f;
        ++doneStageNum;
    }
}

// �X�R�A�̍X�V(�펞���Z)
void StageManager::UpdateScore(Player* player, float elapsedTime)
{
    // �u���C�N�^�C�����Ȃ���Z���Ȃ�
    if (IsBreakTime) return;
    // ���Z��
    static float s = 0.0f;

    s += MaxAlwaysAddScore[stageNo] * MaxAlwaysAddScoreMagnification[player->GetHungerLevel()] * elapsedTime;
    
    // ���Z�ʂ�1�𒴂���ƃX�R�A�����Z����
    if (s >= 1.0f)
    {
        player->AddScore(1);    // �X�R�A���Z
        s -= 1.0f;
    }
}

// �X�N���[�����x�X�V
void StageManager::UpdateScrollVelocity(DirectX::XMFLOAT3& ScrollVelocity, float maxVelocity, float rate)
{
    float length = ScrollVelocity.z - maxVelocity;
    // �l�������ȏꍇ�͏������Ȃ�
    if (fabs(length) > 1e-8f)
    {
        //return a + t * (b - a);
        ScrollVelocity.z = ScrollVelocity.z + rate * (maxVelocity - ScrollVelocity.z);
    }
}