#include "Stage.h"
#include<imgui.h>
//-------------------------------------------------------------------------------------------------------
// 
//		 �X�e�[�W
// 
//-------------------------------------------------------------------------------------------------------

typedef	void(*StageInfo)(Stage* stage);

// �R���X�g���N�^�in�̓X�e�[�W�̎�ށj
Stage::Stage()
{
    //�X�e�[�W���f����ǂݍ���
    //model = std::make_unique<Model>("Data/Model/Debug/cube.mdl");

    // �����ݒ�
    scale           = { StageSize,0.5f ,StageSize };
    stageSideMax    = StageSideMax;
    stageDepthMax   = StageDepthMax;

    // �A�C�e���E��Q������
    int n = rand() % Stage::StageKindMax;

    StageInfo stageInfo[Stage::StageKindMax] =
    {
        StageInfo01
        ,StageInfo02
    };

    //stageInfo[1](this);

    // �f�o�b�O�p
    StageInfoDebug(this, ObstacleNumber);
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

    float positionY = position.y;
    // ���N���X��[Marshmallow_Base]�Ȃ�
    if (std::is_base_of<Marshmallow_Base,T>::value == true)     positionY += 1.0f;
    if (std::is_base_of<Jellybeans_Base,T>::value == true)      positionY += 2.0f;
    if (std::is_base_of<Cupcake_Base,T>::value == true)         positionY += 1.0f;


    Obstacle* obstacle = new T();
    DirectX::XMFLOAT3 Position =
    {
        position.x,
        positionY,
        position.z
    };
    obstacle->SetPosition(Position);
    obstacle->SetScrollVelocity(stage->GetAddressOfVelocity());
    stage->AddObstacle(obstacle);
}

// �X�e�[�W01
void Stage::StageInfo01(Stage* stage)
{
    SpawnObstacle<Cola>({ -10.0f,0.0f,0.0f }, stage);
    SpawnObstacle<Cola>({ 0.0f,0.0f,0.0f }, stage);
    SpawnObstacle<Pokey>({ 10.0f,0.0f,0.0f }, stage);
}

// �X�e�[�W02
void Stage::StageInfo02(Stage* stage)
{
    SpawnObstacle<Marble_chocolate>({ 0.0f,0.0f,0.0f }, stage);
}



// === �ȉ��f�o�b�O�p�֐� ===
int Stage::ObstacleNumber = 0;
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
    case chocolate_ball:
        SpawnObstacle<Chocolate_ball>({ 0.0f,0.0f,0.0f }, stage);
        break;
    case grape_can:
        SpawnObstacle<Grape_can>({ 0.0f,0.0f,0.0f }, stage);
        break;
    case orange_gum:
        SpawnObstacle<Orange_gum>({ 0.0f,0.0f,0.0f }, stage);
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
    }
}


// �[�x�X�e���V��
namespace
{
    const char* obstacle_name[] =
    {
        "cola",
        "pokey",
        "marshmallow_Blue",
        "marshmallow_Pink",
        "jellybeans_Yellow",
        "jellybeans_Pink",
        "jellybeans_Green",
        "chocolate_ball",
        "grape_can",
        "orange_gum",
        "candy_gate",
        "orange_can",
        "marble_chocolate",
        "cupcake_Choco",
        "cupcake_Pink"
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