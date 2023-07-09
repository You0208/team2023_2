#include "Stage.h"
#include "SceneManager.h"
#include<imgui.h>
//-------------------------------------------------------------------------------------------------------
// 
//		 �X�e�[�W
// 
//-------------------------------------------------------------------------------------------------------

bool Stage::IsEndless = false;

// ��Q���̂Ȃ��X�e�[�W
Stage::SpawnObstacleInfo Stage::StageNONE[] =
{
    {AreaInfo00,Stage::SpawnLevel::low}
    ,{AreaInfo00,Stage::SpawnLevel::middle}
    ,{AreaInfo00,Stage::SpawnLevel::high}

    ,{nullptr,0} // END
};

// �X�e�[�W1
Stage::SpawnObstacleInfo Stage::StageInfo01[] =
{
 {AreaInfo01,Stage::SpawnLevel::low}
    ,{AreaInfo01,Stage::SpawnLevel::middle}
    ,{AreaInfo01,Stage::SpawnLevel::high}


    ,{AreaInfo02,Stage::SpawnLevel::low}
    ,{AreaInfo02,Stage::SpawnLevel::middle}
    ,{AreaInfo02,Stage::SpawnLevel::high}
    ,{AreaInfo03,Stage::SpawnLevel::low}
    ,{AreaInfo03,Stage::SpawnLevel::middle}
    ,{AreaInfo03,Stage::SpawnLevel::high}
    ,{AreaInfo04,Stage::SpawnLevel::low}
    ,{AreaInfo04,Stage::SpawnLevel::middle}
    ,{AreaInfo04,Stage::SpawnLevel::high}
    ,{AreaInfo05,Stage::SpawnLevel::low}
    ,{AreaInfo05,Stage::SpawnLevel::middle}
    ,{AreaInfo05,Stage::SpawnLevel::high}
    ,{AreaInfo06,Stage::SpawnLevel::low}
    ,{AreaInfo06,Stage::SpawnLevel::middle}
    ,{AreaInfo06,Stage::SpawnLevel::high}
    ,{AreaInfo07,Stage::SpawnLevel::low}
    ,{AreaInfo07,Stage::SpawnLevel::middle}
    ,{AreaInfo07,Stage::SpawnLevel::high}
    ,{AreaInfo08,Stage::SpawnLevel::low}
    ,{AreaInfo08,Stage::SpawnLevel::middle}
    ,{AreaInfo08,Stage::SpawnLevel::high}
    ,{AreaInfo09,Stage::SpawnLevel::low}
    ,{AreaInfo09,Stage::SpawnLevel::middle}
    ,{AreaInfo09,Stage::SpawnLevel::high}
    ,{AreaInfo10,Stage::SpawnLevel::low}
    ,{AreaInfo10,Stage::SpawnLevel::middle}
    ,{AreaInfo10,Stage::SpawnLevel::high}
    ,{AreaInfo11,Stage::SpawnLevel::low}
    ,{AreaInfo11,Stage::SpawnLevel::middle}
    ,{AreaInfo11,Stage::SpawnLevel::high}
    ,{AreaInfo12,Stage::SpawnLevel::low}
    ,{AreaInfo12,Stage::SpawnLevel::middle}
    ,{AreaInfo12,Stage::SpawnLevel::high}
    ,{AreaInfo13,Stage::SpawnLevel::low}
    ,{AreaInfo13,Stage::SpawnLevel::middle}
    ,{AreaInfo13,Stage::SpawnLevel::high}
    ,{AreaInfo14,Stage::SpawnLevel::low}
    ,{AreaInfo14,Stage::SpawnLevel::middle}
    ,{AreaInfo14,Stage::SpawnLevel::high}
    //            ,{AreaInfo15,Stage::SpawnLevel::low}
    //,{AreaInfo15,Stage::SpawnLevel::middle}
    //,{AreaInfo15,Stage::SpawnLevel::high}

,{nullptr,0} // END
};
// �X�e�[�W2
Stage::SpawnObstacleInfo Stage::StageInfo02[] =
{
 {AreaInfo01,Stage::SpawnLevel::low}
    ,{AreaInfo01,Stage::SpawnLevel::middle}
    ,{AreaInfo01,Stage::SpawnLevel::high}


    ,{AreaInfo02,Stage::SpawnLevel::low}
    ,{AreaInfo02,Stage::SpawnLevel::middle}
    ,{AreaInfo02,Stage::SpawnLevel::high}
    ,{AreaInfo03,Stage::SpawnLevel::low}
    ,{AreaInfo03,Stage::SpawnLevel::middle}
    ,{AreaInfo03,Stage::SpawnLevel::high}
    ,{AreaInfo04,Stage::SpawnLevel::low}
    ,{AreaInfo04,Stage::SpawnLevel::middle}
    ,{AreaInfo04,Stage::SpawnLevel::high}
    ,{AreaInfo05,Stage::SpawnLevel::low}
    ,{AreaInfo05,Stage::SpawnLevel::middle}
    ,{AreaInfo05,Stage::SpawnLevel::high}
    ,{AreaInfo06,Stage::SpawnLevel::low}
    ,{AreaInfo06,Stage::SpawnLevel::middle}
    ,{AreaInfo06,Stage::SpawnLevel::high}
    ,{AreaInfo07,Stage::SpawnLevel::low}
    ,{AreaInfo07,Stage::SpawnLevel::middle}
    ,{AreaInfo07,Stage::SpawnLevel::high}
    ,{AreaInfo08,Stage::SpawnLevel::low}
    ,{AreaInfo08,Stage::SpawnLevel::middle}
    ,{AreaInfo08,Stage::SpawnLevel::high}
    ,{AreaInfo09,Stage::SpawnLevel::low}
    ,{AreaInfo09,Stage::SpawnLevel::middle}
    ,{AreaInfo09,Stage::SpawnLevel::high}
    ,{AreaInfo10,Stage::SpawnLevel::low}
    ,{AreaInfo10,Stage::SpawnLevel::middle}
    ,{AreaInfo10,Stage::SpawnLevel::high}
    ,{AreaInfo11,Stage::SpawnLevel::low}
    ,{AreaInfo11,Stage::SpawnLevel::middle}
    ,{AreaInfo11,Stage::SpawnLevel::high}
    ,{AreaInfo12,Stage::SpawnLevel::low}
    ,{AreaInfo12,Stage::SpawnLevel::middle}
    ,{AreaInfo12,Stage::SpawnLevel::high}
    ,{AreaInfo13,Stage::SpawnLevel::low}
    ,{AreaInfo13,Stage::SpawnLevel::middle}
    ,{AreaInfo13,Stage::SpawnLevel::high}
    ,{AreaInfo14,Stage::SpawnLevel::low}
    ,{AreaInfo14,Stage::SpawnLevel::middle}
    ,{AreaInfo14,Stage::SpawnLevel::high}
    //            ,{AreaInfo15,Stage::SpawnLevel::low}
    //,{AreaInfo15,Stage::SpawnLevel::middle}
    //,{AreaInfo15,Stage::SpawnLevel::high}

,{nullptr,0} // END
};
// �X�e�[�W3
Stage::SpawnObstacleInfo Stage::StageInfo03[] =
{
 {AreaInfo01,Stage::SpawnLevel::low}
    ,{AreaInfo01,Stage::SpawnLevel::middle}
    ,{AreaInfo01,Stage::SpawnLevel::high}


    ,{AreaInfo02,Stage::SpawnLevel::low}
    ,{AreaInfo02,Stage::SpawnLevel::middle}
    ,{AreaInfo02,Stage::SpawnLevel::high}
    ,{AreaInfo03,Stage::SpawnLevel::low}
    ,{AreaInfo03,Stage::SpawnLevel::middle}
    ,{AreaInfo03,Stage::SpawnLevel::high}
    ,{AreaInfo04,Stage::SpawnLevel::low}
    ,{AreaInfo04,Stage::SpawnLevel::middle}
    ,{AreaInfo04,Stage::SpawnLevel::high}
    ,{AreaInfo05,Stage::SpawnLevel::low}
    ,{AreaInfo05,Stage::SpawnLevel::middle}
    ,{AreaInfo05,Stage::SpawnLevel::high}
    ,{AreaInfo06,Stage::SpawnLevel::low}
    ,{AreaInfo06,Stage::SpawnLevel::middle}
    ,{AreaInfo06,Stage::SpawnLevel::high}
    ,{AreaInfo07,Stage::SpawnLevel::low}
    ,{AreaInfo07,Stage::SpawnLevel::middle}
    ,{AreaInfo07,Stage::SpawnLevel::high}
    ,{AreaInfo08,Stage::SpawnLevel::low}
    ,{AreaInfo08,Stage::SpawnLevel::middle}
    ,{AreaInfo08,Stage::SpawnLevel::high}
    ,{AreaInfo09,Stage::SpawnLevel::low}
    ,{AreaInfo09,Stage::SpawnLevel::middle}
    ,{AreaInfo09,Stage::SpawnLevel::high}
    ,{AreaInfo10,Stage::SpawnLevel::low}
    ,{AreaInfo10,Stage::SpawnLevel::middle}
    ,{AreaInfo10,Stage::SpawnLevel::high}
    ,{AreaInfo11,Stage::SpawnLevel::low}
    ,{AreaInfo11,Stage::SpawnLevel::middle}
    ,{AreaInfo11,Stage::SpawnLevel::high}
    ,{AreaInfo12,Stage::SpawnLevel::low}
    ,{AreaInfo12,Stage::SpawnLevel::middle}
    ,{AreaInfo12,Stage::SpawnLevel::high}
    ,{AreaInfo13,Stage::SpawnLevel::low}
    ,{AreaInfo13,Stage::SpawnLevel::middle}
    ,{AreaInfo13,Stage::SpawnLevel::high}
    ,{AreaInfo14,Stage::SpawnLevel::low}
    ,{AreaInfo14,Stage::SpawnLevel::middle}
    ,{AreaInfo14,Stage::SpawnLevel::high}
    //            ,{AreaInfo15,Stage::SpawnLevel::low}
    //,{AreaInfo15,Stage::SpawnLevel::middle}
    //,{AreaInfo15,Stage::SpawnLevel::high}

,{nullptr,0} // END
};
// �X�e�[�W4
Stage::SpawnObstacleInfo Stage::StageInfo04[] =
{
 {AreaInfo01,Stage::SpawnLevel::low}
    ,{AreaInfo01,Stage::SpawnLevel::middle}
    ,{AreaInfo01,Stage::SpawnLevel::high}


    ,{AreaInfo02,Stage::SpawnLevel::low}
    ,{AreaInfo02,Stage::SpawnLevel::middle}
    ,{AreaInfo02,Stage::SpawnLevel::high}
    ,{AreaInfo03,Stage::SpawnLevel::low}
    ,{AreaInfo03,Stage::SpawnLevel::middle}
    ,{AreaInfo03,Stage::SpawnLevel::high}
    ,{AreaInfo04,Stage::SpawnLevel::low}
    ,{AreaInfo04,Stage::SpawnLevel::middle}
    ,{AreaInfo04,Stage::SpawnLevel::high}
    ,{AreaInfo05,Stage::SpawnLevel::low}
    ,{AreaInfo05,Stage::SpawnLevel::middle}
    ,{AreaInfo05,Stage::SpawnLevel::high}
    ,{AreaInfo06,Stage::SpawnLevel::low}
    ,{AreaInfo06,Stage::SpawnLevel::middle}
    ,{AreaInfo06,Stage::SpawnLevel::high}
    ,{AreaInfo07,Stage::SpawnLevel::low}
    ,{AreaInfo07,Stage::SpawnLevel::middle}
    ,{AreaInfo07,Stage::SpawnLevel::high}
    ,{AreaInfo08,Stage::SpawnLevel::low}
    ,{AreaInfo08,Stage::SpawnLevel::middle}
    ,{AreaInfo08,Stage::SpawnLevel::high}
    ,{AreaInfo09,Stage::SpawnLevel::low}
    ,{AreaInfo09,Stage::SpawnLevel::middle}
    ,{AreaInfo09,Stage::SpawnLevel::high}
    ,{AreaInfo10,Stage::SpawnLevel::low}
    ,{AreaInfo10,Stage::SpawnLevel::middle}
    ,{AreaInfo10,Stage::SpawnLevel::high}
    ,{AreaInfo11,Stage::SpawnLevel::low}
    ,{AreaInfo11,Stage::SpawnLevel::middle}
    ,{AreaInfo11,Stage::SpawnLevel::high}
    ,{AreaInfo12,Stage::SpawnLevel::low}
    ,{AreaInfo12,Stage::SpawnLevel::middle}
    ,{AreaInfo12,Stage::SpawnLevel::high}
    ,{AreaInfo13,Stage::SpawnLevel::low}
    ,{AreaInfo13,Stage::SpawnLevel::middle}
    ,{AreaInfo13,Stage::SpawnLevel::high}
    ,{AreaInfo14,Stage::SpawnLevel::low}
    ,{AreaInfo14,Stage::SpawnLevel::middle}
    ,{AreaInfo14,Stage::SpawnLevel::high}
    //            ,{AreaInfo15,Stage::SpawnLevel::low}
    //,{AreaInfo15,Stage::SpawnLevel::middle}
    //,{AreaInfo15,Stage::SpawnLevel::high}

,{nullptr,0} // END
};
// �X�e�[�W5
Stage::SpawnObstacleInfo Stage::StageInfo05[] =
{
 {AreaInfo01,Stage::SpawnLevel::low}
    ,{AreaInfo01,Stage::SpawnLevel::middle}
    ,{AreaInfo01,Stage::SpawnLevel::high}


    ,{AreaInfo02,Stage::SpawnLevel::low}
    ,{AreaInfo02,Stage::SpawnLevel::middle}
    ,{AreaInfo02,Stage::SpawnLevel::high}
    ,{AreaInfo03,Stage::SpawnLevel::low}
    ,{AreaInfo03,Stage::SpawnLevel::middle}
    ,{AreaInfo03,Stage::SpawnLevel::high}
    ,{AreaInfo04,Stage::SpawnLevel::low}
    ,{AreaInfo04,Stage::SpawnLevel::middle}
    ,{AreaInfo04,Stage::SpawnLevel::high}
    ,{AreaInfo05,Stage::SpawnLevel::low}
    ,{AreaInfo05,Stage::SpawnLevel::middle}
    ,{AreaInfo05,Stage::SpawnLevel::high}
    ,{AreaInfo06,Stage::SpawnLevel::low}
    ,{AreaInfo06,Stage::SpawnLevel::middle}
    ,{AreaInfo06,Stage::SpawnLevel::high}
    ,{AreaInfo07,Stage::SpawnLevel::low}
    ,{AreaInfo07,Stage::SpawnLevel::middle}
    ,{AreaInfo07,Stage::SpawnLevel::high}
    ,{AreaInfo08,Stage::SpawnLevel::low}
    ,{AreaInfo08,Stage::SpawnLevel::middle}
    ,{AreaInfo08,Stage::SpawnLevel::high}
    ,{AreaInfo09,Stage::SpawnLevel::low}
    ,{AreaInfo09,Stage::SpawnLevel::middle}
    ,{AreaInfo09,Stage::SpawnLevel::high}
    ,{AreaInfo10,Stage::SpawnLevel::low}
    ,{AreaInfo10,Stage::SpawnLevel::middle}
    ,{AreaInfo10,Stage::SpawnLevel::high}
    ,{AreaInfo11,Stage::SpawnLevel::low}
    ,{AreaInfo11,Stage::SpawnLevel::middle}
    ,{AreaInfo11,Stage::SpawnLevel::high}
    ,{AreaInfo12,Stage::SpawnLevel::low}
    ,{AreaInfo12,Stage::SpawnLevel::middle}
    ,{AreaInfo12,Stage::SpawnLevel::high}
    ,{AreaInfo13,Stage::SpawnLevel::low}
    ,{AreaInfo13,Stage::SpawnLevel::middle}
    ,{AreaInfo13,Stage::SpawnLevel::high}
    ,{AreaInfo14,Stage::SpawnLevel::low}
    ,{AreaInfo14,Stage::SpawnLevel::middle}
    ,{AreaInfo14,Stage::SpawnLevel::high}
    //            ,{AreaInfo15,Stage::SpawnLevel::low}
    //,{AreaInfo15,Stage::SpawnLevel::middle}
    //,{AreaInfo15,Stage::SpawnLevel::high}

,{nullptr,0} // END
};// �X�e�[�W5
// �G���h���X���[�h
Stage::SpawnObstacleInfo Stage::StageInfoEndless[] =
{
 {AreaInfo01,Stage::SpawnLevel::low}
    ,{AreaInfo01,Stage::SpawnLevel::middle}
    ,{AreaInfo01,Stage::SpawnLevel::high}


    ,{AreaInfo02,Stage::SpawnLevel::low}
    ,{AreaInfo02,Stage::SpawnLevel::middle}
    ,{AreaInfo02,Stage::SpawnLevel::high}
    ,{AreaInfo03,Stage::SpawnLevel::low}
    ,{AreaInfo03,Stage::SpawnLevel::middle}
    ,{AreaInfo03,Stage::SpawnLevel::high}
    ,{AreaInfo04,Stage::SpawnLevel::low}
    ,{AreaInfo04,Stage::SpawnLevel::middle}
    ,{AreaInfo04,Stage::SpawnLevel::high}
    ,{AreaInfo05,Stage::SpawnLevel::low}
    ,{AreaInfo05,Stage::SpawnLevel::middle}
    ,{AreaInfo05,Stage::SpawnLevel::high}
    ,{AreaInfo06,Stage::SpawnLevel::low}
    ,{AreaInfo06,Stage::SpawnLevel::middle}
    ,{AreaInfo06,Stage::SpawnLevel::high}
    ,{AreaInfo07,Stage::SpawnLevel::low}
    ,{AreaInfo07,Stage::SpawnLevel::middle}
    ,{AreaInfo07,Stage::SpawnLevel::high}
    ,{AreaInfo08,Stage::SpawnLevel::low}
    ,{AreaInfo08,Stage::SpawnLevel::middle}
    ,{AreaInfo08,Stage::SpawnLevel::high}
    ,{AreaInfo09,Stage::SpawnLevel::low}
    ,{AreaInfo09,Stage::SpawnLevel::middle}
    ,{AreaInfo09,Stage::SpawnLevel::high}
    ,{AreaInfo10,Stage::SpawnLevel::low}
    ,{AreaInfo10,Stage::SpawnLevel::middle}
    ,{AreaInfo10,Stage::SpawnLevel::high}
    ,{AreaInfo11,Stage::SpawnLevel::low}
    ,{AreaInfo11,Stage::SpawnLevel::middle}
    ,{AreaInfo11,Stage::SpawnLevel::high}
    ,{AreaInfo12,Stage::SpawnLevel::low}
    ,{AreaInfo12,Stage::SpawnLevel::middle}
    ,{AreaInfo12,Stage::SpawnLevel::high}
    ,{AreaInfo13,Stage::SpawnLevel::low}
    ,{AreaInfo13,Stage::SpawnLevel::middle}
    ,{AreaInfo13,Stage::SpawnLevel::high}
    ,{AreaInfo14,Stage::SpawnLevel::low}
    ,{AreaInfo14,Stage::SpawnLevel::middle}
    ,{AreaInfo14,Stage::SpawnLevel::high}
    //            ,{AreaInfo15,Stage::SpawnLevel::low}
    //,{AreaInfo15,Stage::SpawnLevel::middle}
    //,{AreaInfo15,Stage::SpawnLevel::high}

,{nullptr,0} // END
};

// �f�o�b�O�p�X�e�[�W
Stage::SpawnObstacleInfo Stage::stageDebug[] =
{
    {AreaInfoDebug,Stage::SpawnLevel::high}
    ,{AreaInfoDebug,Stage::SpawnLevel::middle}
    ,{AreaInfoDebug,Stage::SpawnLevel::low}
    ,{nullptr,0} // END
};

// ��������G���A���(�֐��̃|�C���^)��Ԃ�
Stage::AreaInfo Stage::RandSpawn(Stage::SpawnObstacleInfo* data)
{
    // �e�o������m��(���v100�ɂȂ�悤�ɂ���)
    int High = 60;       // �� (0�`High)
    int Middle = 30;     // �� (High�`High + Middle)
    int Low = 10;        // �� (High + Middle�`100)

    // �������x������
    int spawnLevel = 0;
    int n = rand() % 100;
    // High��菬����(0�`High�ȓ�)�Ȃ̂Ń��x����high�ɐݒ�
    if (n <= High) spawnLevel = SpawnLevel::high;
    // [High+Middle]���傫��([High+Middle]�`100�ȓ�)�Ȃ̂Ń��x����low�ɐݒ�
    else if (n >= High + Middle)spawnLevel = SpawnLevel::low;
    // ���x����middle�ɐݒ�
    else spawnLevel = SpawnLevel::middle;

    std::vector<AreaInfo> areaInfo;             // �������x���������������G���A�����i�[����R���e�i
    for (; data->info != nullptr; ++data)
    {
        // �������x���������Ȃ�[areaInfo]�ɒǉ�
        if (data->spawnRate == spawnLevel)
        {
            areaInfo.emplace_back(data->info);
        }
    }

    // �����_���ȃG���A����Ԃ�
    return areaInfo.at(rand() % areaInfo.size());
}

// �R���X�g���N�^�in�̓X�e�[�W�̎�ށj
Stage::Stage(int stageNo)
{
    stageNo = (std::min)(stageNo, IsEndless ? (StageMax + 1) : StageMax);

    //�X�e�[�W���f����ǂݍ���
    //model = std::make_unique<Model>("Data/Model/Debug/cube.mdl");

    // �����ݒ�
    scale = { StageSize,0.5f ,StageSize };
    stageSideMax = StageSideMax;
    stageDepthMax = StageDepthMax;

    //if (SceneManager::Instance().IsNoneStage || stageNo < 0)
    if (stageNo < 0)
    {
        AreaInfo infoN = RandSpawn(StageNONE);
        infoN(this);
    }
    else 
    {
        AreaInfo info = RandSpawn(stageInfo[stageNo]);
        //AreaInfo info = RandSpawn(StageDebug[stageNo]);
        info(this);
    }

    //StageInfoDebug(this,ObstacleNumber);
}

Stage::~Stage()
{
    for (auto& it : obstacles)
    {
        delete it;
        it = nullptr;
    }
}

// �X�V����
void Stage::Update(float elapsedTime)
{
    // �X�N���[��
    UpdateVelocity(elapsedTime);

    //�s��X�V
    UpdateTransform();

    //���f���s��X�V
    if (model != nullptr)
        model->UpdateTransform(transform);
    
    //��Q���X�V
    for (auto& it : obstacles)
    {
        it->Update(elapsedTime);
    }

    // �X�e�[�W����
    StageSpawn();

    // �X�e�[�W�폜
    StageDelete();
}

void Stage::Initialize()
{
    //��Q���X�V
    for (auto& it : obstacles)
    {
        it->SetPosition({ it->GetPosition().x + position.x,it->GetPosition().y + position.y,it->GetPosition().z + position.z });
    }
}

// �`�揈��
void Stage::Draw(RenderContext rc, ModelShader* shader)
{
    //�X�e�[�W�`��
    if (model != nullptr)
        shader->Draw(rc, model.get());

    //��Q���`��
    for (auto& it : obstacles)
    {
        it->Draw(rc, shader);
    }
}


// �X�e�[�W�̐���
void Stage::StageSpawn()
{
    // ���s
    isDepthSpawn = DepthSpawn();
    // ��
    LeftSpawn();
    // �E
    RightSpawn();
}

// �A�C�e���E��Q������
template<typename T>
void SpawnObstacle(DirectX::XMFLOAT3 position, Stage* stage)
{
    // �X�e�[�W�O�̏ꍇ�͐������Ȃ�
    if (
        (position.x >= Stage::StageSize) ||
        (position.x <= -Stage::StageSize) ||
        (position.z >= Stage::StageSize) ||
        (position.z <= -Stage::StageSize)
        ) return;

    Obstacle* obstacle = new T();
    DirectX::XMFLOAT3 Position =
    {
        position.x,
        position.y,
        position.z
    };
    obstacle->SetPosition(Position);
    obstacle->SetOriginPosition(stage->GetPosition());
    obstacle->SetScrollVelocity(stage->GetAddressOfVelocity());
    stage->AddObstacle(obstacle);
}

// �G���A01
void Stage::AreaInfo01(Stage* stage)
{
    SpawnObstacle<Cola>({ 220.0f,0.0f,-100.0f }, stage);
    SpawnObstacle<Orange_can>({ 200.0f,0.0f,100.0f }, stage);
    SpawnObstacle<Grape_can>({ -230.0f,0.0f,0.0f }, stage);
    SpawnObstacle<Cola>({ 120.0f,0.0f,-50.0f }, stage);
    SpawnObstacle<Orange_can>({ 190.0f,0.0f,50.0f }, stage);
    SpawnObstacle<Grape_can>({ -230.0f,0.0f,0.0f }, stage);
    SpawnObstacle<Cola>({ 180.0f,0.0f,-100.0f }, stage);
    SpawnObstacle<Orange_can>({ -120.0f,0.0f,90.0f }, stage);
    SpawnObstacle<Grape_can>({ -230.0f,0.0f,100.0f }, stage);
    SpawnObstacle<Cola>({ -180.0f,0.0f,-40.0f }, stage);
    SpawnObstacle<Orange_can>({ -20.0f,0.0f,-90.0f }, stage);
    SpawnObstacle<Grape_can>({ -10.0f,0.0f,10.0f }, stage);
    SpawnObstacle<Cola>({ -80.0f,0.0f,170.0f }, stage);
    SpawnObstacle<Orange_can>({ -20.0f,0.0f,220.0f }, stage);
    SpawnObstacle<Grape_can>({ 220.0f,0.0f,210.0f }, stage);
    SpawnObstacle<Cola>({ -10.0f,0.0f,170.0f }, stage);
    SpawnObstacle<Orange_can>({ -20.0f,0.0f,-150.0f }, stage);
    SpawnObstacle<Grape_can>({ 70.0f,0.0f,120.0f }, stage);
    SpawnObstacle<Cola>({ -70.0f,0.0f,-50.0f }, stage);
    SpawnObstacle<Orange_can>({ -100.0f,0.0f,-80.0f }, stage);
    SpawnObstacle<Grape_can>({ -20.0f,0.0f,120.0f }, stage);
    SpawnObstacle<Cola>({ -120.0f,0.0f,-50.0f }, stage);
    SpawnObstacle<Orange_can>({ -90.0f,0.0f,-40.0f }, stage);
    SpawnObstacle<Grape_can>({ -170.0f,0.0f,-120.0f }, stage);
    SpawnObstacle<Cola>({ -220.0f,0.0f,-100.0f }, stage);
    SpawnObstacle<Orange_can>({ -230.0f,0.0f,-70.0f }, stage);
    SpawnObstacle<Grape_can>({ -210.0f,0.0f,230.0f }, stage);
    SpawnObstacle<Cola>({ 240.0f,0.0f,230.0f }, stage);
    SpawnObstacle<Orange_can>({ 40.0f,0.0f,-90.0f }, stage);
    SpawnObstacle<Grape_can>({ 20.0f,0.0f,-50.0f }, stage);
    SpawnObstacle<Jellybeans_Yellow>({ -90.0f,3.0f,-220.0f }, stage);
    SpawnObstacle<Jellybeans_Pink>({ 240.0f,3.0f,-80.0f }, stage);
    SpawnObstacle<Jellybeans_Green>({ 100.0f,3.0f,0.0f }, stage);
    SpawnObstacle<Jellybeans_Yellow>({ 20.0f,3.0f,40.0f }, stage);
    SpawnObstacle<Jellybeans_Pink>({ -110.0f,3.0f,0.0f }, stage);
    SpawnObstacle<Jellybeans_Green>({ -240.0f,3.0f,200.0f }, stage);
    SpawnObstacle<Jellybeans_Yellow>({ 150.0f,3.0f,90.0f }, stage);
    SpawnObstacle<Jellybeans_Pink>({ 170.0f,3.0f,170.0f }, stage);
    SpawnObstacle<Jellybeans_Green>({ 120.0f,3.0f,240.0f }, stage);
}
// �G���A02
void Stage::AreaInfo02(Stage* stage)
{
    SpawnObstacle<Cola>({ 120.0f,0.0f,-50.0f }, stage);
    SpawnObstacle<Cola>({ 70.0f,0.0f,50.0f }, stage);
    SpawnObstacle<Cola>({ 10.0f,0.0f,-170.0f }, stage);
    SpawnObstacle<Cola>({ -70.0f,0.0f,-200.0f }, stage);
    SpawnObstacle<Cola>({ -170.0f,0.0f,-20.0f }, stage);
    SpawnObstacle<Cola>({ 90.0f,0.0f,-20.0f }, stage);
    SpawnObstacle<Cola>({ 210.0f,0.0f,190.0f }, stage);
    SpawnObstacle<Cola>({ 170.0f,0.0f,100.0f }, stage);
    SpawnObstacle<Orange_can>({ -100.0f,0.0f,-80.0f }, stage);
    SpawnObstacle<Orange_can>({ 100.0f,0.0f,80.0f }, stage);
    SpawnObstacle<Orange_can>({ 50.0f,0.0f,180.0f }, stage);
    SpawnObstacle<Orange_can>({ 150.0f,0.0f,-50.0f }, stage);
    SpawnObstacle<Orange_can>({ 200.0f,0.0f,90.0f }, stage);
    SpawnObstacle<Orange_can>({ -200.0f,0.0f,130.0f }, stage);
    SpawnObstacle<Orange_can>({ 140.0f,0.0f,70.0f }, stage);
    SpawnObstacle<Orange_can>({ -30.0f,0.0f,230.0f }, stage);

    SpawnObstacle<Grape_can>({ 0.0f,0.0f,0.0f }, stage);
    SpawnObstacle<Grape_can>({ 230.0f,0.0f,120.0f }, stage);
    SpawnObstacle<Grape_can>({ 170.0f,0.0f,-40.0f }, stage);
    SpawnObstacle<Grape_can>({ -230.0f,0.0f,-90.0f }, stage);
    SpawnObstacle<Grape_can>({ -160.0f,0.0f,-150.0f }, stage);
    SpawnObstacle<Grape_can>({ 100.0f,0.0f,120.0f }, stage);
    SpawnObstacle<Grape_can>({ 120.0f,0.0f,20.0f }, stage);
    SpawnObstacle<Grape_can>({ 180.0f,0.0f,20.0f }, stage);
}
// �G���A03
void Stage::AreaInfo03(Stage* stage)
{

    SpawnObstacle<Orange_can>({ 0.0f,0.0f,15.0f }, stage);
    SpawnObstacle<Orange_can>({ 15.0f,0.0f,15.0f }, stage);
    SpawnObstacle<Orange_can>({ 7.0f,18.0f,15.0f }, stage);
    SpawnObstacle<Orange_can>({ 50.0f,0.0f,15.0f }, stage);
    SpawnObstacle<Orange_can>({ 65.0f,0.0f,15.0f }, stage);
    SpawnObstacle<Orange_can>({ 57.0f,18.0f,15.0f }, stage);
    SpawnObstacle<Orange_can>({ 150.0f,0.0f,-100.0f }, stage);
    SpawnObstacle<Orange_can>({ -100.0f,0.0f,-120.0f }, stage);
    SpawnObstacle<Orange_can>({ 230.0f,0.0f,80.0f }, stage);
    SpawnObstacle<Orange_can>({ -230.0f,0.0f,80.0f }, stage);
    SpawnObstacle<Orange_can>({ 60.0f,0.0f,170.0f }, stage);
    SpawnObstacle<Orange_can>({ -60.0f,0.0f,200.0f }, stage);
    SpawnObstacle<Orange_can>({ 100.0f,0.0f,-230.0f }, stage);
    SpawnObstacle<Orange_can>({ 75.0f,0.0f,230.0f }, stage);
    SpawnObstacle<Orange_can>({ 150.0f,0.0f,-200.0f }, stage);
    SpawnObstacle<Orange_can>({ 110.0f,0.0f,60.0f }, stage);
    SpawnObstacle<Orange_can>({ -150.0f,0.0f,-200.0f }, stage);
    SpawnObstacle<Orange_can>({ -110.0f,0.0f,60.0f }, stage);
    SpawnObstacle<Orange_can>({ -180.0f,0.0f,-50.0f }, stage);
    SpawnObstacle<Orange_can>({ -20.0f,0.0f,90.0f }, stage);
    SpawnObstacle<Orange_can>({ -80.0f,0.0f,-90.0f }, stage);
    SpawnObstacle<Orange_can>({ -50.0f,0.0f,140.0f }, stage);
    SpawnObstacle<Orange_can>({ 50.0f,0.0f,90.0f }, stage);

    SpawnObstacle<Macaron_Maccha>({ 35.0f,3.0f,0.0f }, stage);
}
// �G���A04
void Stage::AreaInfo04(Stage* stage)
{
    SpawnObstacle<Cola>({ 0.0f,0.0f,-100.0f }, stage);
    SpawnObstacle<Cola>({ 15.0f,0.0f,-100.0f }, stage);
    SpawnObstacle<Cola>({ 30.0f,0.0f,-100.0f }, stage);
    SpawnObstacle<Cola>({ 0.0f,0.0f,-115.0f }, stage);
    SpawnObstacle<Cola>({ 0.0f,0.0f,-130.0f }, stage);
    SpawnObstacle<Cola>({ 15.0f,0.0f,-115.0f }, stage);
    SpawnObstacle<Cola>({ 30.0f,0.0f,-115.0f }, stage);
    SpawnObstacle<Cola>({ 15.0f,0.0f,-130.0f }, stage);
    SpawnObstacle<Cola>({ 30.0f,0.0f,-130.0f }, stage);
    SpawnObstacle<Cola>({ 7.0f,18.0f,-107.0f }, stage);
    SpawnObstacle<Cola>({ 23.0f,18.0f,-107.0f }, stage);
    SpawnObstacle<Cola>({ 7.0f,18.0f,-123.0f }, stage);
    SpawnObstacle<Cola>({ 23.0f,18.0f,-123.0f }, stage);
    SpawnObstacle<Cola>({ 15.0f,36.0f,-115.0f }, stage);

    SpawnObstacle<Cola>({ 100.0f,0.0f,-100.0f }, stage);
    SpawnObstacle<Cola>({ 115.0f,0.0f,-100.0f }, stage);
    SpawnObstacle<Cola>({ 130.0f,0.0f,-100.0f }, stage);
    SpawnObstacle<Cola>({ 100.0f,0.0f,-115.0f }, stage);
    SpawnObstacle<Cola>({ 100.0f,0.0f,-130.0f }, stage);
    SpawnObstacle<Cola>({ 115.0f,0.0f,-115.0f }, stage);
    SpawnObstacle<Cola>({ 130.0f,0.0f,-115.0f }, stage);
    SpawnObstacle<Cola>({ 115.0f,0.0f,-130.0f }, stage);
    SpawnObstacle<Cola>({ 130.0f,0.0f,-130.0f }, stage);
    SpawnObstacle<Cola>({ 107.0f,18.0f,-107.0f }, stage);
    SpawnObstacle<Cola>({ 123.0f,18.0f,-107.0f }, stage);
    SpawnObstacle<Cola>({ 107.0f,18.0f,-123.0f }, stage);
    SpawnObstacle<Cola>({ 123.0f,18.0f,-123.0f }, stage);
    SpawnObstacle<Cola>({ 115.0f,36.0f,-115.0f }, stage);

    SpawnObstacle<Cola>({ 150.0f,0.0f,100.0f }, stage);
    SpawnObstacle<Cola>({ 200.0f,0.0f,150.0f }, stage);
    SpawnObstacle<Cola>({ -150.0f,0.0f,100.0f }, stage);
    SpawnObstacle<Cola>({ -200.0f,0.0f,150.0f }, stage);
    SpawnObstacle<Cola>({ 150.0f,0.0f,-100.0f }, stage);
    SpawnObstacle<Cola>({ 200.0f,0.0f,-150.0f }, stage);
    SpawnObstacle<Cola>({ -150.0f,0.0f,-100.0f }, stage);
    SpawnObstacle<Cola>({ -200.0f,0.0f,-150.0f }, stage);
    SpawnObstacle<Cola>({ 90.0f,0.0f,-90.0f }, stage);
    SpawnObstacle<Cola>({ 40.0f,0.0f,-90.0f }, stage);
    SpawnObstacle<Cola>({ 85.0f,0.0f,-70.0f }, stage);
    SpawnObstacle<Cola>({ 45.0f,0.0f,-70.0f }, stage);
    SpawnObstacle<Cola>({ 80.0f,0.0f,-50.0f }, stage);
    SpawnObstacle<Cola>({ 50.0f,0.0f,-50.0f }, stage);

    SpawnObstacle<Cola>({ 80.0f,0.0f,-220.0f }, stage);
    SpawnObstacle<Cola>({ 50.0f,0.0f,-220.0f }, stage);
    SpawnObstacle<Cola>({ 80.0f,18.0f,-220.0f }, stage);
    SpawnObstacle<Cola>({ 50.0f,18.0f,-220.0f }, stage);
    SpawnObstacle<Cola>({ 100.0f,0.0f,220.0f }, stage);
    SpawnObstacle<Cola>({ 30.0f,0.0f,220.0f }, stage);
    SpawnObstacle<Cola>({ 10.0f,0.0f,200.0f }, stage);
    SpawnObstacle<Cola>({ 120.0f,0.0f,200.0f }, stage);
    SpawnObstacle<Cola>({ -90.0f,0.0f,100.0f }, stage);
    SpawnObstacle<Cola>({ 220.0f,0.0f,100.0f }, stage);
    SpawnObstacle<Cola>({ -20.0f,0.0f,50.0f }, stage);
    SpawnObstacle<Cola>({ 150.0f,0.0f,50.0f }, stage);
    SpawnObstacle<Macaron_Maccha>({ 65.0f,3.0f,-20.0f }, stage);
}
// �G���A05
void Stage::AreaInfo05(Stage* stage)
{
    SpawnObstacle<Cola>({ 0.0f,0.0f,-100.0f }, stage);
    SpawnObstacle<Cola>({ 15.0f,0.0f,-100.0f }, stage);
    SpawnObstacle<Cola>({ 30.0f,0.0f,-100.0f }, stage);
    SpawnObstacle<Cola>({ 0.0f,0.0f,-115.0f }, stage);
    SpawnObstacle<Cola>({ 0.0f,0.0f,-130.0f }, stage);
    SpawnObstacle<Cola>({ 15.0f,0.0f,-115.0f }, stage);
    SpawnObstacle<Cola>({ 30.0f,0.0f,-115.0f }, stage);
    SpawnObstacle<Cola>({ 15.0f,0.0f,-130.0f }, stage);
    SpawnObstacle<Cola>({ 30.0f,0.0f,-130.0f }, stage);
    SpawnObstacle<Cola>({ 7.0f,18.0f,-107.0f }, stage);
    SpawnObstacle<Cola>({ 23.0f,18.0f,-107.0f }, stage);
    SpawnObstacle<Cola>({ 7.0f,18.0f,-123.0f }, stage);
    SpawnObstacle<Cola>({ 23.0f,18.0f,-123.0f }, stage);
    SpawnObstacle<Cola>({ 15.0f,36.0f,-115.0f }, stage);

    SpawnObstacle<Cola>({ 100.0f,0.0f,-100.0f }, stage);
    SpawnObstacle<Cola>({ 115.0f,0.0f,-100.0f }, stage);
    SpawnObstacle<Cola>({ 130.0f,0.0f,-100.0f }, stage);
    SpawnObstacle<Cola>({ 100.0f,0.0f,-115.0f }, stage);
    SpawnObstacle<Cola>({ 100.0f,0.0f,-130.0f }, stage);
    SpawnObstacle<Cola>({ 115.0f,0.0f,-115.0f }, stage);
    SpawnObstacle<Cola>({ 130.0f,0.0f,-115.0f }, stage);
    SpawnObstacle<Cola>({ 115.0f,0.0f,-130.0f }, stage);
    SpawnObstacle<Cola>({ 130.0f,0.0f,-130.0f }, stage);
    SpawnObstacle<Cola>({ 107.0f,18.0f,-107.0f }, stage);
    SpawnObstacle<Cola>({ 123.0f,18.0f,-107.0f }, stage);
    SpawnObstacle<Cola>({ 107.0f,18.0f,-123.0f }, stage);
    SpawnObstacle<Cola>({ 123.0f,18.0f,-123.0f }, stage);
    SpawnObstacle<Cola>({ 115.0f,36.0f,-115.0f }, stage);

    SpawnObstacle<Cola>({ 150.0f,0.0f,100.0f }, stage);
    SpawnObstacle<Cola>({ 200.0f,0.0f,150.0f }, stage);
    SpawnObstacle<Cola>({ -150.0f,0.0f,100.0f }, stage);
    SpawnObstacle<Cola>({ -200.0f,0.0f,150.0f }, stage);
    SpawnObstacle<Cola>({ 150.0f,0.0f,-100.0f }, stage);
    SpawnObstacle<Cola>({ 200.0f,0.0f,-150.0f }, stage);
    SpawnObstacle<Cola>({ -150.0f,0.0f,-100.0f }, stage);
    SpawnObstacle<Cola>({ -200.0f,0.0f,-150.0f }, stage);
    SpawnObstacle<Cola>({ 90.0f,0.0f,-90.0f }, stage);
    SpawnObstacle<Cola>({ 40.0f,0.0f,-90.0f }, stage);
    SpawnObstacle<Cola>({ 85.0f,0.0f,-70.0f }, stage);
    SpawnObstacle<Cola>({ 45.0f,0.0f,-70.0f }, stage);
    SpawnObstacle<Cola>({ 80.0f,0.0f,-50.0f }, stage);
    SpawnObstacle<Cola>({ 50.0f,0.0f,-50.0f }, stage);

    SpawnObstacle<Cola>({ 80.0f,0.0f,-220.0f }, stage);
    SpawnObstacle<Cola>({ 50.0f,0.0f,-220.0f }, stage);
    SpawnObstacle<Cola>({ 80.0f,18.0f,-220.0f }, stage);
    SpawnObstacle<Cola>({ 50.0f,18.0f,-220.0f }, stage);
    SpawnObstacle<Cola>({ 100.0f,0.0f,220.0f }, stage);
    SpawnObstacle<Cola>({ 30.0f,0.0f,220.0f }, stage);
    SpawnObstacle<Cola>({ 10.0f,0.0f,200.0f }, stage);
    SpawnObstacle<Cola>({ 120.0f,0.0f,200.0f }, stage);
    SpawnObstacle<Cola>({ -90.0f,0.0f,100.0f }, stage);
    SpawnObstacle<Cola>({ 220.0f,0.0f,100.0f }, stage);
    SpawnObstacle<Cola>({ -20.0f,0.0f,50.0f }, stage);
    SpawnObstacle<Cola>({ 150.0f,0.0f,50.0f }, stage);
    SpawnObstacle<Macaron_Maccha>({ 65.0f,3.0f,-20.0f }, stage);
}
// �G���A06
void Stage::AreaInfo06(Stage* stage)
{


    SpawnObstacle<Grape_can>({ 0.0f,0.0f,0.0f }, stage);
    SpawnObstacle<Grape_can>({ 50.0f,0.0f,50.0f }, stage);
    SpawnObstacle<Grape_can>({ -50.0f,0.0f,-50.0f }, stage);
    SpawnObstacle<Grape_can>({ 100.0f,0.0f,150.0f }, stage);
    SpawnObstacle<Grape_can>({ 50.0f,0.0f,100.0f }, stage);
    SpawnObstacle<Grape_can>({ -150.0f,0.0f,-50.0f }, stage);
    SpawnObstacle<Grape_can>({ 200.0f,0.0f,150.0f }, stage);
    SpawnObstacle<Grape_can>({ 230.0f,0.0f,100.0f }, stage);
    SpawnObstacle<Grape_can>({ -230.0f,0.0f,-50.0f }, stage);
    SpawnObstacle<Grape_can>({ -100.0f,0.0f,200.0f }, stage);
    SpawnObstacle<Grape_can>({ -200.0f,0.0f,-200.0f }, stage);
    SpawnObstacle<Grape_can>({ -170.0f,0.0f,-70.0f }, stage);
    SpawnObstacle<Grape_can>({ 170.0f,0.0f,70.0f }, stage);
    SpawnObstacle<Grape_can>({ 170.0f,0.0f,-200.0f }, stage);
    SpawnObstacle<Grape_can>({ 120.0f,0.0f,20.0f }, stage);
    SpawnObstacle<Grape_can>({ 120.0f,0.0f,-20.0f }, stage);
    SpawnObstacle<Grape_can>({ 25.0f,0.0f,180.0f }, stage);
    SpawnObstacle<Grape_can>({ 25.0f,0.0f,-140.0f }, stage);
    SpawnObstacle<Grape_can>({ 240.0f,0.0f,90.0f }, stage);
    SpawnObstacle<Grape_can>({ -240.0f,0.0f,-140.0f }, stage);
    SpawnObstacle<Marshmallow_Blue>({ 20.0f,3.0f,0.0f }, stage);
    SpawnObstacle<Marshmallow_Blue>({ 230.0f,3.0f,130.0f }, stage);
    SpawnObstacle<Marshmallow_Pink>({ 70.0f,3.0f,-45.0f }, stage);
    SpawnObstacle<Marshmallow_Pink>({ -180.0f,3.0f,-210.0f }, stage);

}
// �G���A07
void Stage::AreaInfo07(Stage* stage)
{
    SpawnObstacle<Pokey>({ -25.0f,0.0f,0.0f }, stage);
    SpawnObstacle<Pokey>({ -50.0f,0.0f,-50.0f }, stage);
    SpawnObstacle<Pokey>({ -100.0f,0.0f,-75.0f }, stage);
    SpawnObstacle<Pokey>({ -150.0f,0.0f,-150.0f }, stage);
    SpawnObstacle<Pokey>({ -200.0f,0.0f,-200.0f }, stage);
    SpawnObstacle<Pokey>({ -230.0f,0.0f,-230.0f }, stage);
    SpawnObstacle<Prits>({ 25.0f,0.0f,0.0f }, stage);
    SpawnObstacle<Prits>({ 50.0f,0.0f,-50.0f }, stage);
    SpawnObstacle<Prits>({ 100.0f,0.0f,-75.0f }, stage);
    SpawnObstacle<Prits>({ 150.0f,0.0f,-150.0f }, stage);
    SpawnObstacle<Prits>({ 200.0f,0.0f,-200.0f }, stage);
    SpawnObstacle<Prits>({ 230.0f,0.0f,-230.0f }, stage);
    SpawnObstacle<Macaron_Maccha>({ 0.0f,3.0f,0.0f }, stage);
}
// �G���A08
void Stage::AreaInfo08(Stage* stage)
{
    SpawnObstacle<Pokey>({ 75.0f,0.0f,-100.0f }, stage);
    SpawnObstacle<Pokey>({ -75.0f,0.0f,-100.0f }, stage);
    SpawnObstacle<Pokey>({ 180.0f,0.0f,-200.0f }, stage);
    SpawnObstacle<Pokey>({ -180.0f,0.0f,-200.0f }, stage);
    SpawnObstacle<Pokey>({ 20.0f,0.0f,-240.0f }, stage);
    SpawnObstacle<Pokey>({ -20.0f,0.0f,-240.0f }, stage);
    SpawnObstacle<Pokey>({ 15.0f,0.0f,180.0f }, stage);
    SpawnObstacle<Pokey>({ -15.0f,0.0f,180.0f }, stage);

    SpawnObstacle<Pokey>({ -25.0f,0.0f,0.0f }, stage);
    SpawnObstacle<Pokey>({ 25.0f,0.0f,0.0f }, stage);
    SpawnObstacle<Pokey>({ -25.0f,35.5f,0.0f }, stage);
    SpawnObstacle<Pokey>({ 25.0f,35.5f,0.0f }, stage);
    SpawnObstacle<Pokey>({ -15.0f,71.0f,0.0f }, stage);
    SpawnObstacle<Pokey>({ 15.0f,71.0f,0.0f }, stage);
    SpawnObstacle<Pokey>({ 0.0f,106.5f,0.0f }, stage);
    SpawnObstacle<Pokey>({ 50.0f,0.0f,50.0f }, stage);
    SpawnObstacle<Pokey>({ 100.0f,0.0f,100.0f }, stage);
    SpawnObstacle<Pokey>({ -50.0f,0.0f,50.0f }, stage);
    SpawnObstacle<Pokey>({ -100.0f,0.0f,100.0f }, stage);
    SpawnObstacle<Pokey>({ -150.0f,0.0f,200.0f }, stage);
    SpawnObstacle<Pokey>({ 150.0f,0.0f,200.0f }, stage);
    SpawnObstacle<Pokey>({ -230.0f,0.0f,230.0f }, stage);
    SpawnObstacle<Pokey>({ 230.0f,0.0f,230.0f }, stage);
    SpawnObstacle<Cupcake_Choco>({ 0.0f,3.0f,0.0f }, stage);
}
// �G���A09
void Stage::AreaInfo09(Stage* stage)
{
    SpawnObstacle<Chocolate_ball>({ 100.0f,0.0f,0.0f }, stage);
    SpawnObstacle<Chocolate_ball>({ -100.0f,0.0f,0.0f }, stage);
    SpawnObstacle<Chocolate_ball>({ 242.5f,0.0f,0.0f }, stage);
    SpawnObstacle<Chocolate_ball>({ -242.5f,0.0f,0.0f }, stage);
    SpawnObstacle<Chocolate_ball>({ 0.0f,0.0f,100.0f }, stage);
    SpawnObstacle<Chocolate_ball>({ 175.0f,0.0f,200.0f }, stage);
    SpawnObstacle<Chocolate_ball>({ -175.0f,0.0f,200.0f }, stage);
    SpawnObstacle<Chocolate_ball>({ -130.0f,0.0f,100.0f }, stage);
    SpawnObstacle<Chocolate_ball>({ 130.0f,0.0f,100.0f }, stage);
    SpawnObstacle<Chocolate_ball>({ 40.0f,0.0f,-40.0f }, stage);
    SpawnObstacle<Chocolate_ball>({ -40.0f,0.0f,-40.0f }, stage);
    SpawnObstacle<Pokey>({ -25.0f,0.0f,0.0f }, stage);
    SpawnObstacle<Pokey>({ 25.0f,0.0f,0.0f }, stage);
    SpawnObstacle<Pokey>({ -155.0f,0.0f,0.0f }, stage);
    SpawnObstacle<Pokey>({ 155.0f,0.0f,0.0f }, stage);
    SpawnObstacle<Pokey>({ -75.0f,0.0f,200.0f }, stage);
    SpawnObstacle<Pokey>({ 75.0f,0.0f,200.0f }, stage);
    SpawnObstacle<Pokey>({ -125.0f,0.0f,-200.0f }, stage);
    SpawnObstacle<Pokey>({ 125.0f,0.0f,-200.0f }, stage);
    SpawnObstacle<Marshmallow_Pink>({ 0.0f,3.0f,0.0f }, stage);
}
// �G���A10
void Stage::AreaInfo10(Stage* stage)
{
    SpawnObstacle<Orange_gum>({ 50.0f,0.0f,0.0f }, stage);
    SpawnObstacle<Orange_gum>({ -50.0f,0.0f,0.0f }, stage);
    SpawnObstacle<Orange_gum>({ -50.0f,0.0f,100.0f }, stage);
    SpawnObstacle<Orange_gum>({ 50.0f,0.0f,100.0f }, stage);
    SpawnObstacle<Orange_gum>({ -150.0f,0.0f,120.0f }, stage);
    SpawnObstacle<Orange_gum>({ 150.0f,0.0f,120.0f }, stage);
    SpawnObstacle<Orange_gum>({ -200.0f,0.0f,180.0f }, stage);
    SpawnObstacle<Orange_gum>({ 200.0f,0.0f,180.0f }, stage);
    SpawnObstacle<Orange_gum>({ -100.0f,0.0f,-180.0f }, stage);
    SpawnObstacle<Orange_gum>({ 100.0f,0.0f,-180.0f }, stage);
    SpawnObstacle<Orange_can>({ 70.0f,0.0f,-100.0f }, stage);
    SpawnObstacle<Orange_can>({ -70.0f,0.0f,-100.0f }, stage);
    SpawnObstacle<Orange_can>({ 220.0f,0.0f,-50.0f }, stage);
    SpawnObstacle<Orange_can>({ -220.0f,0.0f,-50.0f }, stage);
    SpawnObstacle<Orange_can>({ 180.0f,0.0f,-150.0f }, stage);
    SpawnObstacle<Orange_can>({ -180.0f,0.0f,-150.0f }, stage);
    SpawnObstacle<Orange_can>({ 30.0f,0.0f,0.0f }, stage);
    SpawnObstacle<Orange_can>({ -30.0f,0.0f,0.0f }, stage);
    SpawnObstacle<Macaron_Maccha>({ 40.0f,3.0f,0.0f }, stage);
    SpawnObstacle<Macaron_Maccha>({ 240.0f,3.0f,0.0f }, stage);
    SpawnObstacle<Macaron_Maccha>({ -120.0f,3.0f,240.0f }, stage);
}
// �G���A11
void Stage::AreaInfo11(Stage* stage)
{
    SpawnObstacle<Cola>({ -240.0f,0.0f,0.0f }, stage);
    SpawnObstacle<Cola>({ -228.0f,0.0f,0.0f }, stage);
    SpawnObstacle<Cola>({ -216.0f,0.0f,0.0f }, stage);
    SpawnObstacle<Cola>({ -204.0f,0.0f,0.0f }, stage);
    SpawnObstacle<Cola>({ -192.0f,0.0f,0.0f }, stage);
    SpawnObstacle<Cola>({ -180.0f,0.0f,0.0f }, stage);

    SpawnObstacle<Jellybeans_Green>({ -162.0f,3.0f,0.0f }, stage);
    SpawnObstacle<Orange_can>({ -144.0f,0.0f,0.0f }, stage);
    SpawnObstacle<Orange_can>({ -132.0f,0.0f,0.0f }, stage);
    SpawnObstacle<Orange_can>({ -120.0f,0.0f,0.0f }, stage);
    SpawnObstacle<Orange_can>({ -108.0f,0.0f,0.0f }, stage);
    SpawnObstacle<Orange_can>({ -96.0f,0.0f,0.0f }, stage);
    SpawnObstacle<Orange_can>({ -84.0f,0.0f,0.0f }, stage);
    SpawnObstacle<Jellybeans_Green>({ -66.0f,3.0f,0.0f }, stage);
    SpawnObstacle<Grape_can>({ -50.0f,0.0f,0.0f }, stage);
    SpawnObstacle<Grape_can>({ -38.0f,0.0f,0.0f }, stage);
    SpawnObstacle<Grape_can>({ -26.0f,0.0f,0.0f }, stage);
    SpawnObstacle<Grape_can>({ -14.0f,0.0f,0.0f }, stage);
    SpawnObstacle<Grape_can>({ -2.0f,0.0f,0.0f }, stage);
    SpawnObstacle<Grape_can>({ 10.0f,0.0f,0.0f }, stage);
    SpawnObstacle<Jellybeans_Green>({ 28.0f,3.0f,0.0f }, stage);
    SpawnObstacle<Cola>({ 46.0f,0.0f,0.0f }, stage);
    SpawnObstacle<Cola>({ 58.0f,0.0f,0.0f }, stage);
    SpawnObstacle<Cola>({ 70.0f,0.0f,0.0f }, stage);
    SpawnObstacle<Cola>({ 82.0f,0.0f,0.0f }, stage);
    SpawnObstacle<Cola>({ 94.0f,0.0f,0.0f }, stage);
    SpawnObstacle<Cola>({ 106.0f,0.0f,0.0f }, stage);
    SpawnObstacle<Jellybeans_Green>({ 126.0f,3.0f,0.0f }, stage);
    SpawnObstacle<Orange_can>({ 142.0f,0.0f,0.0f }, stage);
    SpawnObstacle<Orange_can>({ 154.0f,0.0f,0.0f }, stage);
    SpawnObstacle<Orange_can>({ 166.0f,0.0f,0.0f }, stage);
    SpawnObstacle<Orange_can>({ 178.0f,0.0f,0.0f }, stage);
    SpawnObstacle<Orange_can>({ 190.0f,0.0f,0.0f }, stage);
    SpawnObstacle<Orange_can>({ 202.0f,0.0f,0.0f }, stage);
}
// �G���A12
void Stage::AreaInfo12(Stage* stage)
{
    SpawnObstacle<Pokey>({ 0.0f,0.0f,-100.0f }, stage);
    SpawnObstacle<Prits>({ 0.0f,0.0f,0.0f }, stage);
    SpawnObstacle<Chocolate_ball>({ 0.0f,0.0f,100.0f }, stage);
    SpawnObstacle<Pokey>({ 100.0f,0.0f,100.0f }, stage);
    SpawnObstacle<Prits>({ 100.0f,0.0f,0.0f }, stage);
    SpawnObstacle<Chocolate_ball>({ 70.0f,0.0f,100.0f }, stage);
    SpawnObstacle<Pokey>({ 30.0f,0.0f,-30.0f }, stage);
    SpawnObstacle<Prits>({ 50.0f,0.0f,-220.0f }, stage);
    SpawnObstacle<Chocolate_ball>({ 10.0f,0.0f,-150.0f }, stage);
    SpawnObstacle<Pokey>({ 90.0f,0.0f,190.0f }, stage);
    SpawnObstacle<Prits>({ 220.0f,0.0f,230.0f }, stage);
    SpawnObstacle<Chocolate_ball>({ -230.0f,0.0f,230.0f }, stage);
    SpawnObstacle<Pokey>({ -100.0f,0.0f,40.0f }, stage);
    SpawnObstacle<Prits>({ -150.0f,0.0f,60.0f }, stage);
    SpawnObstacle<Chocolate_ball>({ -130.0f,0.0f,60.0f }, stage);
    SpawnObstacle<Pokey>({ -100.0f,0.0f,-10.0f }, stage);
    SpawnObstacle<Prits>({ -150.0f,0.0f,-60.0f }, stage);
    SpawnObstacle<Chocolate_ball>({ -130.0f,0.0f,-120.0f }, stage);
    SpawnObstacle<Pokey>({ -50.0f,0.0f,80.0f }, stage);
    SpawnObstacle<Prits>({ -230.0f,0.0f,-230.0f }, stage);
    SpawnObstacle<Chocolate_ball>({ -220.0f,0.0f,-190.0f }, stage);
    SpawnObstacle<Pokey>({ 200.0f,0.0f,80.0f }, stage);
    SpawnObstacle<Prits>({ 240.0f,0.0f,-70.0f }, stage);
    SpawnObstacle<Chocolate_ball>({ 40.0f,0.0f,90.0f }, stage);
    SpawnObstacle<Pokey>({ 235.0f,0.0f,180.0f }, stage);
    SpawnObstacle<Prits>({ 140.0f,0.0f,130.0f }, stage);
    SpawnObstacle<Chocolate_ball>({ 150.0f,0.0f,90.0f }, stage);
    SpawnObstacle<Jellybeans_Yellow>({ 25.0f,3.0f,-240.0f }, stage);
    SpawnObstacle<Jellybeans_Pink>({ 40.0f,3.0f,130.0f }, stage);
    SpawnObstacle<Jellybeans_Green>({ 75.0f,3.0f,120.0f }, stage);
    SpawnObstacle<Jellybeans_Yellow>({ 240.0f,3.0f,-160.0f }, stage);
}
// �G���A13
void Stage::AreaInfo13(Stage* stage)
{
    SpawnObstacle<Cola>({ 20.0f,0.0f,100.0f }, stage);
    SpawnObstacle<Cola>({ 40.0f,0.0f,-170.0f }, stage);
    SpawnObstacle<Cola>({ 190.0f,0.0f,110.0f }, stage);
    SpawnObstacle<Cola>({ -125.0f,0.0f,240.0f }, stage);
    SpawnObstacle<Pokey>({ -20.0f,0.0f,25.0f }, stage);
    SpawnObstacle<Pokey>({ 120.0f,0.0f,125.0f }, stage);
    SpawnObstacle<Pokey>({ 230.0f,0.0f,-125.0f }, stage);
    SpawnObstacle<Pokey>({ 170.0f,0.0f,180.0f }, stage);
    SpawnObstacle<Prits>({ 40.0f,0.0f,-25.0f }, stage);
    SpawnObstacle<Prits>({ 90.0f,0.0f,-80.0f }, stage);
    SpawnObstacle<Prits>({ 160.0f,0.0f,80.0f }, stage);
    SpawnObstacle<Prits>({ 210.0f,0.0f,190.0f }, stage);
    SpawnObstacle<Grape_can>({ 150.0f,0.0f,0.0f }, stage);
    SpawnObstacle<Grape_can>({ -10.0f,0.0f,90.0f }, stage);
    SpawnObstacle<Grape_can>({ -100.0f,0.0f,200.0f }, stage);
    SpawnObstacle<Grape_can>({ 50.0f,0.0f,-180.0f }, stage);
    SpawnObstacle<Orange_gum>({ -80.0f,0.0f,-150.0f }, stage);
    SpawnObstacle<Orange_gum>({ -20.0f,0.0f,180.0f }, stage);
    SpawnObstacle<Orange_gum>({ -200.0f,0.0f,60.0f }, stage);
    SpawnObstacle<Orange_gum>({ -120.0f,0.0f,45.0f }, stage);
    SpawnObstacle<Orange_can>({ 140.0f,0.0f,240.0f }, stage);
    SpawnObstacle<Orange_can>({ 100.0f,0.0f,-180.0f }, stage);
    SpawnObstacle<Orange_can>({ 240.0f,0.0f,-240.0f }, stage);
    SpawnObstacle<Orange_can>({ -180.0f,0.0f,-190.0f }, stage);
    SpawnObstacle<Marshmallow_Blue>({ -240.0f,3.0f,0.0f }, stage);
    SpawnObstacle<Marshmallow_Pink>({ 150.0f,3.0f,130.0f }, stage);
    SpawnObstacle<Marshmallow_Blue>({ 120.0f,3.0f,-240.0f }, stage);
}
// �G���A14
void Stage::AreaInfo14(Stage* stage)
{
    SpawnObstacle<Prits>({ 0.0f,0.0f,-240.0f }, stage);
    SpawnObstacle<Prits>({ 50.0f,0.0f,-240.0f }, stage);
    SpawnObstacle<Prits>({ 100.0f,0.0f,-240.0f }, stage);
    SpawnObstacle<Prits>({ 150.0f,0.0f,-240.0f }, stage);
    SpawnObstacle<Prits>({ 200.0f,0.0f,-240.0f }, stage);
    SpawnObstacle<Prits>({ 230.0f,0.0f,-240.0f }, stage);
    SpawnObstacle<Prits>({ -50.0f,0.0f,-240.0f }, stage);
    SpawnObstacle<Prits>({ -100.0f,0.0f,-240.0f }, stage);
    SpawnObstacle<Prits>({ -150.0f,0.0f,-240.0f }, stage);
    SpawnObstacle<Prits>({ -200.0f,0.0f,-240.0f }, stage);
    SpawnObstacle<Prits>({ -230.0f,0.0f,-240.0f }, stage);

    SpawnObstacle<Chocolate_ball>({ 25.0f,0.0f,-120.0f }, stage);
    SpawnObstacle<Chocolate_ball>({ 75.0f,0.0f,-120.0f }, stage);
    SpawnObstacle<Chocolate_ball>({ 125.0f,0.0f,-120.0f }, stage);
    SpawnObstacle<Chocolate_ball>({ 175.0f,0.0f,-120.0f }, stage);
    SpawnObstacle<Chocolate_ball>({ 225.0f,0.0f,-120.0f }, stage);
    SpawnObstacle<Chocolate_ball>({ -25.0f,0.0f,-120.0f }, stage);
    SpawnObstacle<Chocolate_ball>({ -75.0f,0.0f,-120.0f }, stage);
    SpawnObstacle<Chocolate_ball>({ -125.0f,0.0f,-120.0f }, stage);
    SpawnObstacle<Chocolate_ball>({ -175.0f,0.0f,-120.0f }, stage);
    SpawnObstacle<Chocolate_ball>({ -225.0f,0.0f,-120.0f }, stage);

    SpawnObstacle<Chocolate_ball>({ 0.0f,0.0f,0.0f }, stage);
    SpawnObstacle<Chocolate_ball>({ 50.0f,0.0f,0.0f }, stage);
    SpawnObstacle<Chocolate_ball>({ 100.0f,0.0f,0.0f }, stage);
    SpawnObstacle<Chocolate_ball>({ 150.0f,0.0f,0.0f }, stage);
    SpawnObstacle<Chocolate_ball>({ 200.0f,0.0f,0.0f }, stage);
    SpawnObstacle<Chocolate_ball>({ 230.0f,0.0f,0.0f }, stage);
    SpawnObstacle<Chocolate_ball>({ -50.0f,0.0f,0.0f }, stage);
    SpawnObstacle<Chocolate_ball>({ -100.0f,0.0f,0.0f }, stage);
    SpawnObstacle<Chocolate_ball>({ -150.0f,0.0f,0.0f }, stage);
    SpawnObstacle<Chocolate_ball>({ -200.0f,0.0f,0.0f }, stage);
    SpawnObstacle<Chocolate_ball>({ -230.0f,0.0f,0.0f }, stage);

    SpawnObstacle<Chocolate_ball>({ 25.0f,0.0f,120.0f }, stage);
    SpawnObstacle<Chocolate_ball>({ 75.0f,0.0f,120.0f }, stage);
    SpawnObstacle<Chocolate_ball>({ 125.0f,0.0f,120.0f }, stage);
    SpawnObstacle<Chocolate_ball>({ 175.0f,0.0f,120.0f }, stage);
    SpawnObstacle<Chocolate_ball>({ 225.0f,0.0f,120.0f }, stage);
    SpawnObstacle<Chocolate_ball>({ -25.0f,0.0f,120.0f }, stage);
    SpawnObstacle<Chocolate_ball>({ -75.0f,0.0f,120.0f }, stage);
    SpawnObstacle<Chocolate_ball>({ -125.0f,0.0f,120.0f }, stage);
    SpawnObstacle<Chocolate_ball>({ -175.0f,0.0f,120.0f }, stage);
    SpawnObstacle<Chocolate_ball>({ -225.0f,0.0f,120.0f }, stage);

    SpawnObstacle<Pokey>({ 0.0f,0.0f,240.0f }, stage);
    SpawnObstacle<Pokey>({ 50.0f,0.0f,240.0f }, stage);
    SpawnObstacle<Pokey>({ 100.0f,0.0f,240.0f }, stage);
    SpawnObstacle<Pokey>({ 150.0f,0.0f,240.0f }, stage);
    SpawnObstacle<Pokey>({ 200.0f,0.0f,240.0f }, stage);
    SpawnObstacle<Pokey>({ 230.0f,0.0f,240.0f }, stage);
    SpawnObstacle<Pokey>({ -50.0f,0.0f,240.0f }, stage);
    SpawnObstacle<Pokey>({ -100.0f,0.0f,240.0f }, stage);
    SpawnObstacle<Pokey>({ -150.0f,0.0f,240.0f }, stage);
    SpawnObstacle<Pokey>({ -200.0f,0.0f,240.0f }, stage);
    SpawnObstacle<Pokey>({ -230.0f,0.0f,240.0f }, stage);

}
// �G���A15
void Stage::AreaInfo15(Stage* stage)
{
    SpawnObstacle<Prits>({ 0.0f,0.0f,0.0f }, stage);
    SpawnObstacle<Candy_gate>({ 100.0f,0.0f,0.0f }, stage);
    SpawnObstacle<Cola>({ -100.0f,0.0f,0.0f }, stage);
    SpawnObstacle<Macaron_Maccha>({ 170.0f,3.0f,20.0f }, stage);
    SpawnObstacle<Marshmallow_Pink>({ 165.0f,3.0f,220.0f }, stage);
    SpawnObstacle<Marshmallow_Blue>({ 160.0f,3.0f,0.0f }, stage);
    SpawnObstacle<Orange_can>({ 70.0f,0.0f,0.0f }, stage);
    SpawnObstacle<Jellybeans_Yellow>({ 150.0f,3.0f,220.0f }, stage);
    SpawnObstacle<Jellybeans_Pink>({ 150.0f,3.0f,0.0f }, stage);
    SpawnObstacle<Jellybeans_Green>({ 145.0f,3.0f,0.0f }, stage);
    SpawnObstacle<Jellybeans_Orange>({ 140.0f,3.0f,0.0f }, stage);
    SpawnObstacle<Macaron_Pink>({ 180.0f,3.0f,220.0f }, stage);
    SpawnObstacle<Macaron_Maccha>({ 130.0f,3.0f,0.0f }, stage);
    SpawnObstacle<Cupcake_Pink>({ 195.0f,3.0f,220.0f }, stage);
    SpawnObstacle<Pudding>({ 210.0f,3.0f,220.0f }, stage);
    SpawnObstacle<Marble_chocolate>({ 0.0f,0.0f,220.0f }, stage);
    SpawnObstacle<Husen_gum>({ -220.0f,0.0f,0.0f }, stage);
    SpawnObstacle<Orange_gum>({ -240.0f,0.0f,-100.0f }, stage);
}

// �f�o�b�O�p�G���A
void Stage::AreaInfoDebug(Stage* stage)
{
    //SpawnObstacle<Marshmallow_Blue>({ 0.0f,0.0f,0.0f }, stage);
    //SpawnObstacle<Marshmallow_Blue>({ 20.0f,0.0f,0.0f }, stage);
    //SpawnObstacle<Marshmallow_Blue>({ 40.0f,0.0f,0.0f }, stage);
    //SpawnObstacle<Marshmallow_Blue>({ 60.0f,0.0f,0.0f }, stage);

    SpawnObstacle<Macaron_Maccha>({ 0.0f,0.0f,0.0f }, stage);
    SpawnObstacle<Macaron_Maccha>({ 100.0f,0.0f,0.0f }, stage);

    SpawnObstacle<Macaron_Maccha>({ 0.0f,3.0f,20.0f }, stage);
}


// === �ȉ��f�o�b�O�p�֐� ===
int Stage::ObstacleNumber = husen_gum;
void Stage::StageInfoDebug(Stage* stage,int n)
{
    switch (n)
    {
    case cola:
        SpawnObstacle<Cola>({ 0.0f,0.0f,0.0f }, stage);
        break;
    case pokey:
        SpawnObstacle<Pokey>({ 0.0f,0.0f,0.0f }, stage);
        break;
    case prits:
        SpawnObstacle<Prits>({ 0.0f,0.0f,0.0f }, stage);
        break;
    case marshmallow_Blue:
        SpawnObstacle<Marshmallow_Blue>({ 0.0f,0.0f,0.0f }, stage);
        break;
    case marshmallow_Pink:
        SpawnObstacle<Marshmallow_Pink>({ 0.0f,0.0f,0.0f }, stage);
        break;
    case jellybeans_Yellow:
        SpawnObstacle<Jellybeans_Yellow>({ 0.0f,0.0f,0.0f }, stage);
        break;
    case jellybeans_Pink:
        SpawnObstacle<Jellybeans_Pink>({ 0.0f,0.0f,0.0f }, stage);
        break;
    case jellybeans_Green:
        SpawnObstacle<Jellybeans_Green>({ 0.0f,0.0f,0.0f }, stage);
        break;
    case jellybeans_Orange:
        SpawnObstacle<Jellybeans_Orange>({ 0.0f,5.0f,0.0f }, stage);
        break;
    case chocolate_ball:
        SpawnObstacle<Chocolate_ball>({ 0.0f,0.0f,0.0f }, stage);
        break;
    case grape_can:
        SpawnObstacle<Grape_can>({ 0.0f,0.0f,0.0f }, stage);
        break;
    case orange_gum:
        SpawnObstacle<Orange_gum>({ 0.0f,0.0f,0.0f }, stage);
        break;
    case husen_gum:
        SpawnObstacle<Husen_gum>({ 0.0f,0.0f,0.0f }, stage);
        break;
    case candy_gate:
        SpawnObstacle<Candy_gate>({ 0.0f,0.0f,0.0f }, stage);
        break;
    case orange_can:
        SpawnObstacle<Orange_can>({ 0.0f,0.0f,0.0f }, stage);
        break;
    case marble_chocolate:
        SpawnObstacle<Marble_chocolate>({ 0.0f,0.0f,0.0f }, stage);
        break;
    case cupcake_Choco:
        SpawnObstacle<Cupcake_Choco>({ 0.0f,0.0f,0.0f }, stage);
        break;
    case cupcake_Pink:
        SpawnObstacle<Cupcake_Pink>({ 0.0f,0.0f,0.0f }, stage);
        break;
    case pudding:
        SpawnObstacle<Pudding>({ 0.0f,0.0f,0.0f }, stage);
        break;
    case macaron_Maccha:
        SpawnObstacle<Macaron_Maccha>({ 0.0f,0.0f,0.0f }, stage);
        break;
    case macaron_Ping:
        SpawnObstacle<Macaron_Pink>({ 0.0f,0.0f,0.0f }, stage);
        break;
    }
}


// �[�x�X�e���V��
namespace
{
    const char* obstacle_name[] =
    {
        "cola",
        "pokey",
        "prits",
        "marshmallow_Blue",
        "marshmallow_Pink",
        "jellybeans_Yellow",
        "jellybeans_Pink",
        "jellybeans_Green",
        "jellybeans_Orange",
        "chocolate_ball",
        "grape_can",
        "orange_gum",
        "husen_gum",
        "candy_gate",
        "orange_can",
        "marble_chocolate",
        "cupcake_Choco",
        "cupcake_Pink",
        "pudding",
        "macaron_Maccha",
        "macaron_Pink",
    };  
    const char* OBSTACLE_NAME = obstacle_name[0];
}

//�f�o�b�OGUI�`��
void Stage::DrawDebugGUI_()
{
    ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(ImVec2(300, 300), ImGuiCond_FirstUseEver);

    if (ImGui::Begin("Stage", nullptr, ImGuiWindowFlags_None))
    {
        // �����I�u�W�F�N�g�̐ݒ�
        if (ImGui::BeginCombo("SpawnItem", OBSTACLE_NAME, ImGuiComboFlags_NoArrowButton))
        {
            for (int n = 0; n < IM_ARRAYSIZE(obstacle_name); n++)
            {
                bool is_selected = (OBSTACLE_NAME == obstacle_name[n]);
                if (ImGui::Selectable(obstacle_name[n]))
                {
                    ObstacleNumber = n;
                    OBSTACLE_NAME = obstacle_name[n];
                }
                if (is_selected) ImGui::SetItemDefaultFocus();
            }
            ImGui::EndCombo();
        }
    }
    ImGui::End();
}