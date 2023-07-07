#include<imgui.h>
#include "Obstacle.h"
#include "Tool.h"
#include "Graphics/Graphics.h"
#include "EffectManager.h"

//-------------------------------------------------------------------------------------------------------
// 
//		 ��Q��
// 
//-------------------------------------------------------------------------------------------------------

// �`�揈��
void Obstacle::Draw(RenderContext rc, ModelShader* shader)
{
    shader->Draw(rc, model.get());
    DrawDebugPrimitive();
}

//�X�V����
void Obstacle::Update(float elapsedTime)
{
    if (once) {
        if (Type == ITEMS)
        {
            // �G�t�F�N�g�̍Đ�
            handle = ItemEffect->Play(position);
            once = false;
        }
    }
    // �q�b�g�G�t�F�N�g�Đ�
    {
        // �G�t�F�N�g�̍��W��ύX
        ItemEffect->SetPosition(handle, position);
    }
    if (Type == ITEMS)
    {
        angle.y += DirectX::XMConvertToRadians(1);//��
    }
    // ���x�����X�V
    UpdateVelocity(elapsedTime);

    //�I�u�W�F�N�g�s����X�V
    UpdateTransform();

    //���f���s��X�V
    model->UpdateTransform(transform);
}

//�f�o�b�OGUI�`��
void Obstacle::DrawDebugGUI()
{
    ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(ImVec2(300, 300), ImGuiCond_FirstUseEver);

    if (ImGui::Begin("Player", nullptr, ImGuiWindowFlags_None))
    {
        //�g�����X�t�H�[��
        if (ImGui::CollapsingHeader("Transform", ImGuiTreeNodeFlags_DefaultOpen))
        {
            //�ʒu
            ImGui::InputFloat3("Position", &position.x);
            //��]
            DirectX::XMFLOAT3 a;
            a.x = DirectX::XMConvertToDegrees(angle.x);
            a.y = DirectX::XMConvertToDegrees(angle.y);
            a.z = DirectX::XMConvertToDegrees(angle.z);
            ImGui::InputFloat3("Angle", &a.x);
            angle.x = DirectX::XMConvertToRadians(a.x);
            angle.y = DirectX::XMConvertToRadians(a.y);
            angle.z = DirectX::XMConvertToRadians(a.z);
            //�X�P�[��
            ImGui::InputFloat3("Scale", &scale.x);
        }
    }
    ImGui::End();
}

//�s��X�V����
void Obstacle::UpdateTransform()
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

void Obstacle::GetItem()
{
    if (Type == TYPE::ITEMS)
    {
        position.y = lerp(position.y, 5.0f, 0.03f);
        angle.y += DirectX::XMConvertToRadians(1);
        //�I�u�W�F�N�g�s����X�V
        UpdateTransform();

        //���f���s��X�V
        model->UpdateTransform(transform);
    }
}

// ���񏈗�
void Obstacle::Turn(float elapsedTime, float vx, float vz, float speed)
{
    speed *= elapsedTime;

    // �i�s�x�N�g�����[���x�N�g���̏ꍇ�͏�������K�v�Ȃ�
    float length = sqrtf(vx * vx + vz * vz);
    if (length < 0.01f)return;
    // �i�s�x�N�g����P�ʃx�N�g����
    vx /= length;
    vz /= length;
    // ���g�̉�]�l����O���������߂�
    float frontX = sinf(angle.y);
    float frontZ = cosf(angle.y);

    //��]�p�����߂邽�߁A2�̒P�ʃx�N�g���̓��ς��v�Z����
    float dot = (frontX * vx) + (frontZ * vz);
    //���ϒl��-1.0~1.0�ŕ\������Ă���A2�̒P�ʃx�N�g���̊p�x��
    //�������ق�1.0�ɋ߂Â��Ƃ��������𗘗p���ĉ�]���x�𒲐�����
    float rot = 1.0 - dot;
    if (rot > speed)rot = speed;

    // ���E������s�����߂ɓ�̒P�ʃx�N�g���̊O�όv�Z����
    float cross = (frontZ * vx) - (vz * frontX);

    // 2D�̊O�ϒl�����̏ꍇ�����̏ꍇ�ɂ���č��E���肪�s����
    // ���E������s�����Ƃɂ���č��E����]����
    if (cross < 0.0f)
    {
        angle.y -= rot;
    }
    else
    {
        angle.y += rot;
    }
}

// ���x�����X�V
void Obstacle::UpdateVelocity(float elapsedTime)
{
    // �o�߃t���[��
    float elapsedFrame = 60.0f * elapsedTime;

    // ���x�����ݒ�
    velocity = *scrollVelocity;

    // ���x�̒ǉ��X�V
    UpdataAdditionVelocity(elapsedFrame);

    // �ړ��X�V����
    UpdateMove(elapsedTime);
}

// �ړ��X�V����
void Obstacle::UpdateMove(float elapsedTime)
{
    // �ړ�����
    position.x += velocity.x * elapsedTime;
    position.y += velocity.y * elapsedTime;
    position.z += velocity.z * elapsedTime;
}

// �R�[��
Cola::Cola()
{
    //���f����ǂݍ���
    model = std::make_unique<Model>("Data/Model/Obstacle/cola/Cola.mdl");
    scale.x = scale.y = scale.z = 5.0f;
    angle.y = DirectX::XMConvertToRadians(180);
    height = 19.0f;
    radius = 6.0f;
    Type = TYPE::CYLINDER;
    CollisionNum = 1;
}
// �X�V����
void Cola::Update(float elapsedTime)
{
    // ���N���X�X�V����
    Obstacle::Update(elapsedTime);
}

void Cola::DrawDebugPrimitive()
{
    DebugRenderer* debugRenderer = Graphics::Instance().GetDebugRenderer();
    //�Փ˔���p�̃f�o�b�O�~����`��
    debugRenderer->DrawCylinder(position, radius, height, DirectX::XMFLOAT4(0, 0, 0, 1));
}


// �|�b�L�[ 
Pokey::Pokey()
{
    //���f����ǂݍ���
    model = std::make_unique<Model>("Data/Model/Obstacle/pocky/pozky.mdl");
    angle.y = DirectX::XMConvertToRadians(180);
    scale.x = scale.y = scale.z = 5.0f;
    // �����蔻��C��
    radius = 2.1f;
    height = 35.0f;
    Type = TYPE::CYLINDERS;
    CollisionNum = 5;
}
// �`�揈��
void Pokey::Update(float elapsedTime)
{
    // ���N���X�`�揈��
    Obstacle::Update(elapsedTime);
}

void Pokey::DrawDebugPrimitive()
{
    DebugRenderer* debugRenderer = Graphics::Instance().GetDebugRenderer();
    //�Փ˔���p�̃f�o�b�O�~����`��
    for (int n = 0; n < CollisionNum; ++n)
    {
        debugRenderer->DrawCylinder({ (position.x - (CollisionNum * radius) + radius) + (n * radius * 2.0f) ,position.y,position.z }, radius, height, DirectX::XMFLOAT4(1, 0, 0, 1));
    }
}

// �v���b�c
Prits::Prits()
{
    //���f����ǂݍ���
    model = std::make_unique<Model>("Data/Model/Obstacle/prits/prits.mdl");
    angle.y = DirectX::XMConvertToRadians(180);
    scale.x = scale.y = scale.z = 5.0f;
    // �����蔻��C��
    height = 35.0f;
    radius = 2.7;
    Type = TYPE::CYLINDERS;
    CollisionNum = 4;

}
void Prits::DrawDebugPrimitive()
{
    DebugRenderer* debugRenderer = Graphics::Instance().GetDebugRenderer();
    //�Փ˔���p�̃f�o�b�O�~����`��
    for (int n = 0; n < CollisionNum; ++n)
    {
        debugRenderer->DrawCylinder({ (position.x - (CollisionNum * radius) + radius) + (n * radius * 2.0f) ,position.y,position.z }, radius, height, DirectX::XMFLOAT4(0, 0, 0, 1));
    }
}


// �}�V���}��
// �X�V����
void Marshmallow_Base::Update(float elapsedTime)
{
    // ���N���X�`�揈��
    Obstacle::Update(elapsedTime);
    radius = 2.0f;
    Type = TYPE::ITEMS;
    score = 5;
    hungerPoint = 5;
    scale.x = scale.y = scale.z = 3.0f;
    // �q�b�g�G�t�F�N�g�Đ�
    {
        // �G�t�F�N�g�̍��W��ύX
        ItemEffect->SetPosition(handle, position);
    }
}
void Marshmallow_Base::DrawDebugPrimitive()
{
    //DebugRenderer* debugRenderer = Graphics::Instance().GetDebugRenderer();
    ////�Փ˔���p�̃f�o�b�O�~����`��
    //debugRenderer->DrawSphere(position, radius, DirectX::XMFLOAT4(0, 0, 0, 1));
}
// �R���X�g���N�^
Marshmallow_Blue::Marshmallow_Blue()
{
    //���f����ǂݍ���
    model = std::make_unique<Model>("Data/Model/Obstacle/marshmallow/marshmallow_blue.mdl");
    // �G�t�F�N�g�̍Đ�
    handle = ItemEffect->Play(position);

}
// �}�V���}��(�s���N)
Marshmallow_Pink::Marshmallow_Pink()
{
    //���f����ǂݍ���
    model = std::make_unique<Model>("Data/Model/Obstacle/marshmallow/marshmallow_pink.mdl");
}

// �r�[���Y
Jellybeans_Base::Jellybeans_Base()
{
    scale.x = scale.y = scale.z = 0.6f;
}
// �r�[���Y
// �X�V����
void Jellybeans_Base::Update(float elapsedTime)
{
    // ���N���X�`�揈��
    Obstacle::Update(elapsedTime);
    radius = 1.0f;
    Type = TYPE::ITEMS;
    score = 3;
    hungerPoint = 3;
}
void Jellybeans_Base::DrawDebugPrimitive()
{
    DebugRenderer* debugRenderer = Graphics::Instance().GetDebugRenderer();
    //�Փ˔���p�̃f�o�b�O�~����`��
    debugRenderer->DrawSphere(position, radius, DirectX::XMFLOAT4(0, 0, 0, 1));
}
// �r�[���Y(���F)
Jellybeans_Yellow::Jellybeans_Yellow()
{
    Jellybeans_Base();
    //���f����ǂݍ���
    model = std::make_unique<Model>("Data/Model/Obstacle/jellybeans/jellybeans_yellow.mdl");
}
// �r�[���Y(�s���N)
Jellybeans_Pink::Jellybeans_Pink()
{
    Jellybeans_Base();
    //���f����ǂݍ���
    model = std::make_unique<Model>("Data/Model/Obstacle/jellybeans/jellybeans_pink.mdl");
}
// �r�[���Y(�O���[��)
Jellybeans_Green::Jellybeans_Green()
{
    Jellybeans_Base();
    //���f����ǂݍ���
    model = std::make_unique<Model>("Data/Model/Obstacle/jellybeans/jellybeans_green.mdl");
}
// �r�[���Y(�I�����W)
Jellybeans_Orange::Jellybeans_Orange()
{
    Jellybeans_Base();
    //���f����ǂݍ���
    model = std::make_unique<Model>("Data/Model/Obstacle/jellybeans/jellybeans_orange.mdl");
}


// �`���R�{�[��
Chocolate_ball::Chocolate_ball()
{
    //���f����ǂݍ���
    model = std::make_unique<Model>("Data/Model/Obstacle/chocolate_ball/chocolate_ball.mdl");
    scale.x = scale.y = scale.z = 5.0f;
    angle.y = DirectX::XMConvertToRadians(180);
    height = 30.0f;
    radius = 2.5f;
    Type = TYPE::CYLINDERS;
    CollisionNum = 3;
}
void Chocolate_ball::Update(float elapsedTime)
{
    // ���N���X�`�揈��
    Obstacle::Update(elapsedTime);
}

void Chocolate_ball::DrawDebugPrimitive()
{
    DebugRenderer* debugRenderer = Graphics::Instance().GetDebugRenderer();
    //�Փ˔���p�̃f�o�b�O�~����`��
    for (int n = 0; n < CollisionNum; ++n)
    {
        debugRenderer->DrawCylinder({ (position.x - (CollisionNum * radius) + radius) + (n * radius * 2.0f) ,position.y,position.z }, radius, height, DirectX::XMFLOAT4(0, 0, 0, 1));
    }
}


// �O���[�v�W���[�X
Grape_can::Grape_can()
{
    //���f����ǂݍ���
    model = std::make_unique<Model>("Data/Model/Obstacle/grape_can/grape_can.mdl");
    scale.x = scale.y = scale.z = 5.0f;
    angle.y = DirectX::XMConvertToRadians(180);
    height = 19.0f;
    radius = 6.0f;
    Type = TYPE::CYLINDER;
    CollisionNum = 1;
}

void Grape_can::DrawDebugPrimitive()
{
    DebugRenderer* debugRenderer = Graphics::Instance().GetDebugRenderer();
    //�Փ˔���p�̃f�o�b�O�~����`��
    debugRenderer->DrawCylinder(position, radius, height, DirectX::XMFLOAT4(0, 0, 0, 1));
}

// �t�[�Z���K��
Husen_gum::Husen_gum()
{
    //���f����ǂݍ���
    model = std::make_unique<Model>("Data/Model/Obstacle/husen_gum/husen_gum.mdl");
    angle.y = DirectX::XMConvertToRadians(180);
    scale.x = scale.y = scale.z = 9.0f;
    height = 9.0f;
    radius = 1.5f;
    Type = TYPE::CYLINDERS;
    CollisionNum = 3;
}

void Husen_gum::DrawDebugPrimitive()
{
    DebugRenderer* debugRenderer = Graphics::Instance().GetDebugRenderer();
    //�Փ˔���p�̃f�o�b�O�~����`��
    for (int n = 0; n < CollisionNum; ++n)
    {
        debugRenderer->DrawCylinder({ (position.x - (CollisionNum * radius) + radius) + (n * radius * 2.0f) ,position.y,position.z }, radius, height, DirectX::XMFLOAT4(0, 0, 0, 1));
    }
}

// �ǉ��̍X�V����
void Husen_gum::UpdataAdditionVelocity(float elapsedFrame)
{
    if (isUp && position.y >= OriginPosition->y + MaxUp) isUp = false;
    if (!isUp && position.y <= OriginPosition->y + MaxDown) isUp = true;

    velocity.y = isUp ? MoveSpeed : -MoveSpeed;
}


// �I�����W�K��
Orange_gum::Orange_gum()
{
    //���f����ǂݍ���
    model = std::make_unique<Model>("Data/Model/Obstacle/orange_gum/orange_gum.mdl");
    angle.y = DirectX::XMConvertToRadians(180);
    scale.x = scale.y = scale.z = 9.0f;
    height = 9.0f;
    radius = 1.5f;
    Type = TYPE::CYLINDERS;
    CollisionNum = 3;
}

void Orange_gum::DrawDebugPrimitive()
{
    DebugRenderer* debugRenderer = Graphics::Instance().GetDebugRenderer();
    //�Փ˔���p�̃f�o�b�O�~����`��
    for (int n = 0; n < CollisionNum; ++n)
    {
        debugRenderer->DrawCylinder({ (position.x - (CollisionNum * radius) + radius) + (n * radius * 2.0f) ,position.y,position.z }, radius, height, DirectX::XMFLOAT4(0, 0, 0, 1));
    }
}


// �L�����f�B�[�Q�[�g
Candy_gate::Candy_gate()
{
    //���f����ǂݍ���
    model = std::make_unique<Model>("Data/Model/Obstacle/candy_gate/candy_gate.mdl");
    angle.y = DirectX::XMConvertToRadians(180);
    scale.x = scale.y = scale.z = 6.0f;
    height = 20.0f;
    Type = TYPE::GATE;
    CollisionNum = 19;
}

void Candy_gate::DrawDebugPrimitive()
{
    DebugRenderer* debugRenderer = Graphics::Instance().GetDebugRenderer();
    //�Փ˔���p�̃f�o�b�O�~����`��
    for (int n = 0; n < CollisionNum; ++n)
    {
        debugRenderer->DrawCylinder({ (position.x - (CollisionNum * 0.5f) + radius) + (n * radius * 2.0f) ,position.y,position.z }, radius, height, DirectX::XMFLOAT4(0, 0, 0, 1));
    }
}


// �I�����W�W���[�X
Orange_can::Orange_can()
{
    //���f����ǂݍ���
    model = std::make_unique<Model>("Data/Model/Obstacle/orange_can/orange_can.mdl");
    angle.y = DirectX::XMConvertToRadians(180);
    scale.x = scale.y = scale.z = 5.0f;
    height = 19.0f;
    radius = 6.0f;
    Type = TYPE::CYLINDER;
    CollisionNum = 1;
}

void Orange_can::DrawDebugPrimitive()
{
    DebugRenderer* debugRenderer = Graphics::Instance().GetDebugRenderer();
    //�Փ˔���p�̃f�o�b�O�~����`��
    debugRenderer->DrawCylinder(position, radius, height, DirectX::XMFLOAT4(0, 0, 0, 1));
}


// �}�[�u���`���R
Marble_chocolate::Marble_chocolate()
{
    //���f����ǂݍ���
    model = std::make_unique<Model>("Data/Model/Obstacle/marble_chocolate/marble_chocolate.mdl");
    scale.x = scale.y = scale.z = 4.0f;
    angle.y = DirectX::XMConvertToRadians(180);
    height = 8.0f;
    radius = 4.0f;
    Type = TYPE::CYLINDERS;
    HitCheckTYpe = HIT_CHECK_TYPE::ACTIVE;
    CollisionNum = 5;
}

void Marble_chocolate::DrawDebugPrimitive()
{
    DebugRenderer* debugRenderer = Graphics::Instance().GetDebugRenderer();
    //�Փ˔���p�̃f�o�b�O�~����`��
    for (int n = 0; n < CollisionNum; ++n)
    {
        debugRenderer->DrawCylinder({ (position.x - (CollisionNum * radius) + radius) + (n * radius * 2.0f) ,position.y,position.z }, radius, height, DirectX::XMFLOAT4(0, 0, 0, 1));
    }
}

// ���x�̒ǉ��X�V
void Marble_chocolate::UpdataAdditionVelocity(float elapsedFrame)
{
    float size = 45.0f;

    // �X�e�[�W�O�ɍs����
    // ��ʊO�ɍs���Ȃ��悤�ɏ����]�T�������Ĉ����Ԃ��Ă���
    if (
        (position.x + (height * 0.5f) >= OriginPosition->x + size)
        || (position.x - (height * 0.5f) <= OriginPosition->x - size)
        || IsHitVsObs
        )
    {
        isleft = !isleft;
        IsHitVsObs = false;

        position.x = (std::min)(OriginPosition->x + size - (height * 0.5f), (std::max)(position.x, OriginPosition->x - size + (height * 0.5f)));
    }

    velocity.x += isleft ? -MoveSpeed : MoveSpeed;
}


Cupcake_Base::Cupcake_Base()
{
    radius = 2.5f;
    Type = TYPE::ITEMS;
    hungerPoint = 10;
    score = 10;
    scale.x = scale.y = scale.z = 1.25f;
}
// �J�b�v�P�[�L(�`���R)
Cupcake_Choco::Cupcake_Choco()
{
    model = std::make_unique<Model>("Data/Model/Obstacle/cupcake/cupcake_choco.mdl");
    Cupcake_Base();
}
// �J�b�v�P�[�L(�s���N)
Cupcake_Pink::Cupcake_Pink()
{
    model = std::make_unique<Model>("Data/Model/Obstacle/cupcake/cupcake_pink.mdl");
    Cupcake_Base();
}

void Cupcake_Base::DrawDebugPrimitive()
{
    DebugRenderer* debugRenderer = Graphics::Instance().GetDebugRenderer();
    //�Փ˔���p�̃f�o�b�O�~����`��
    debugRenderer->DrawSphere(position, radius, DirectX::XMFLOAT4(0, 0, 0, 1));
}

// �v����
Pudding::Pudding()
{
    model = std::make_unique<Model>("Data/Model/Obstacle/pudding/pudding.mdl");
    radius = 5.0f;
    Type = TYPE::ITEMS;
    hungerPoint = 50;
    score = 50;

    scale.x = scale.y = scale.z = 0.8f;
}
void Pudding::DrawDebugPrimitive()
{
    DebugRenderer* debugRenderer = Graphics::Instance().GetDebugRenderer();
    //�Փ˔���p�̃f�o�b�O�~����`��
    debugRenderer->DrawSphere(position, radius, DirectX::XMFLOAT4(0, 0, 0, 1));
}

// �}�J����
Macaron_Base::Macaron_Base()
{
    radius = 2.5f;
    Type = TYPE::ITEMS;
    hungerPoint = 10;
    score = 10;
    scale.x = scale.y = scale.z = 0.8f;
}
void Macaron_Base::DrawDebugPrimitive()
{
    DebugRenderer* debugRenderer = Graphics::Instance().GetDebugRenderer();
    //�Փ˔���p�̃f�o�b�O�~����`��
    debugRenderer->DrawSphere(position, radius, DirectX::XMFLOAT4(0, 0, 0, 1));
}
// ����
Macaron_Maccha::Macaron_Maccha()
{
    model = std::make_unique<Model>("Data/Model/Obstacle/macaron/macaron_maccha.mdl");
    Macaron_Base();
}
// �s���N
Macaron_Pink::Macaron_Pink()
{
    model = std::make_unique<Model>("Data/Model/Obstacle/macaron/macaron_pink.mdl");
    Macaron_Base();
}
