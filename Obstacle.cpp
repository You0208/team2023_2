#include<imgui.h>
#include "Obstacle.h"
#include "Graphics/Graphics.h"

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

    velocity = *scrollVelocity;

    // �������͍X�V����
    //UpdataVerticalVelocity(elapsedFrame);

    // �������͍X�V����
    //UpdataHorizontalVelocity(elapsedFrame);

    // �����ړ��X�V����
    //UpdateVerticalMove(elapsedTime);

    // �����ړ��X�V����
    UpdateHorizontalMove(elapsedTime);
}

// �������͍X�V����
void Obstacle::UpdataHorizontalVelocity(float elapsedFrame)
{
    // XZ���ʂ̑��͂���������
    float length = sqrtf(velocity.x * velocity.x + velocity.z * velocity.z);
    if (length > 0.0f)
    {
        // ���C��
        float friction = this->friction * elapsedFrame;

        // �󒆂ɂ���Ƃ��͖��C�͂����炷
        if (!isGround)friction *= airControl;

        // ���C�ɂ�鉡�����̌�������
        if (length > friction)
        {
            float vx = velocity.x / length;
            float vz = velocity.z / length;

            velocity.x -= vx * friction;
            velocity.z -= vz * friction;
        }
        // �������̑��͂����C�͈ȉ��ɂȂ����̂ő��͂𖳌���
        else
        {
            velocity.x = 0;
            velocity.z = 0;
        }
    }

    // XZ���ʂ̑��͂���������
    if (length <= maxMoveSpeed)
    {
        // �ړ��x�N�g�����[���x�N�g���o�Ȃ��Ȃ��������
        float moveVecLength = sqrtf(moveVecX * moveVecX + moveVecZ * moveVecZ);
        if (moveVecLength > 0.0f)
        {
            // ������
            float acceleration = this->acceleration * elapsedFrame;

            // �󒆂ɂ���Ƃ��͖��C�͂����炷
            if (!isGround)acceleration *= airControl;

            // �ړ��x�N�g���ɂ���������
            velocity.x += moveVecX * acceleration;
            velocity.z += moveVecZ * acceleration;

            // �ő呬�x����
            float length = sqrtf(velocity.x * velocity.x + velocity.z * velocity.z);
            if (length > maxMoveSpeed)
            {
                float vx = velocity.x / length;
                float vz = velocity.z / length;

                velocity.x = vx * maxMoveSpeed;
                velocity.z = vz * maxMoveSpeed;
            }
        }
    }
    // �ړ��x�N�g�������Z�b�g
    moveVecX = 0.0f;
    moveVecZ = 0.0f;
}

// �����ړ��X�V����
void Obstacle::UpdateHorizontalMove(float elapsedTime)
{
    // �ړ�����
    position.x += velocity.x * elapsedTime;
    position.z += velocity.z * elapsedTime;
}

// �������͍X�V����
void Obstacle::UpdataVerticalVelocity(float elapsedFrame)
{
    // �d�͏���
    velocity.y += gravity * elapsedFrame;//�O���r�e�B�ƒP�ʂ����킹�邽�߂�elapsedFrame���g���Ă���
}

// �����ړ��X�V����
void Obstacle::UpdateVerticalMove(float elapsedTime)
{
    // �ړ�����
    position.y += velocity.y * elapsedTime;

    // �n�ʔ���
    if (position.y < 0.0f)
    {
        position.y = 0.0f;
        velocity.y = 0.0f;
        isGround = true;
    }
    else
    {
        isGround = false;
    }
}


// �R�[��
Cola::Cola()
{
    //���f����ǂݍ���
    model = std::make_unique<Model>("Data/Model/Obstacle/cola/Cola.mdl");
    angle.y = DirectX::XMConvertToRadians(180);
    height = 3.8f;
    radius = 1.2f;
    Type = 0;
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
    model = std::make_unique<Model>("Data/Model/Obstacle/pocky/pooky.mdl");
    angle.y = DirectX::XMConvertToRadians(180);
    height = 7.0f;
    Type = 1;
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
        debugRenderer->DrawCylinder({ (position.x - (5.0f * 0.5f) + radius) + (n * radius * 2.0f) ,position.y,position.z }, radius, height, DirectX::XMFLOAT4(0, 0, 0, 1));
    }
}



// �}�V���}��
// �X�V����
void Marshmallow_Base::Update(float elapsedTime)
{
    // ���N���X�`�揈��
    Obstacle::Update(elapsedTime);
}
// �R���X�g���N�^
Marshmallow_Blue::Marshmallow_Blue()
{
    //���f����ǂݍ���
    model = std::make_unique<Model>("Data/Model/Obstacle/marshmallow/marshmallow_blue.mdl");
}
// �}�V���}��(�s���N)
Marshmallow_Pink::Marshmallow_Pink()
{
    //���f����ǂݍ���
    model = std::make_unique<Model>("Data/Model/Obstacle/marshmallow/marshmallow_pink.mdl");
}


// �r�[���Y
// �X�V����
void Jellybeans_Base::Update(float elapsedTime)
{
    // ���N���X�`�揈��
    Obstacle::Update(elapsedTime);
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


// �`���R�{�[��
Chocolate_ball::Chocolate_ball()
{
    //���f����ǂݍ���
    model = std::make_unique<Model>("Data/Model/Obstacle/chocolate_ball/chocolate_ball.mdl");
    angle.y = DirectX::XMConvertToRadians(180);
}
void Chocolate_ball::Update(float elapsedTime)
{
    // ���N���X�`�揈��
    Obstacle::Update(elapsedTime);
}


// �O���[�v�W���[�X
Grape_can::Grape_can()
{
    //���f����ǂݍ���
    model = std::make_unique<Model>("Data/Model/Obstacle/grape_can/grape_can.mdl");
    angle.y = DirectX::XMConvertToRadians(180);
}


// �I�����W�K��
Orange_gum::Orange_gum()
{
    //���f����ǂݍ���
    model = std::make_unique<Model>("Data/Model/Obstacle/orange_gum/orange_gum.mdl");
    angle.y = DirectX::XMConvertToRadians(180);
    scale = { 3.0f,3.0f ,3.0f };
}


// �L�����f�B�[�Q�[�g
Candy_gate::Candy_gate()
{
    //���f����ǂݍ���
    model = std::make_unique<Model>("Data/Model/Obstacle/candy_gate/candy_gate.mdl");
    angle.y = DirectX::XMConvertToRadians(180);
    scale = { 3.0f,3.0f ,3.0f };
}


// �I�����W�W���[�X
Orange_can::Orange_can()
{
    //���f����ǂݍ���
    model = std::make_unique<Model>("Data/Model/Obstacle/orange_can/orange_can.mdl");
    angle.y = DirectX::XMConvertToRadians(180);
}


// �}�[�u���`���R
Marble_chocolate::Marble_chocolate()
{
    //���f����ǂݍ���
    model = std::make_unique<Model>("Data/Model/Obstacle/marble_chocolate/marble_chocolate.mdl");
    angle.y = DirectX::XMConvertToRadians(180);
}


// �J�b�v�P�[�L(�`���R)
Cupcake_Choco::Cupcake_Choco()
{
    model = std::make_unique<Model>("Data/Model/Obstacle/cupcake/cupcake_choco.mdl");
}
// �J�b�v�P�[�L(�s���N)
Cupcake_Pink::Cupcake_Pink()
{
    model = std::make_unique<Model>("Data/Model/Obstacle/cupcake/cupcake_pink.mdl");
}