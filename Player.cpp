#include<imgui.h>
#include "Camera.h"
#include "Player.h"
#include "Input/Input.h"
#include "Graphics/Graphics.h"

//-------------------------------------------------------------------------------------------------------
// 
//		 �v���C���[
// 
//-------------------------------------------------------------------------------------------------------

//�R���X�g���N�^   
Player::Player()
{
    model = std::make_unique< Model>("Data/Model/Player/Hamster.mdl");

    //���f�����傫���̂ŃX�P�[�����O
    scale.x = scale.y = scale.z = 1.0f;

    // �����ʒu������
    position.y = 5.0f;

    // �ҋ@�X�e�[�g�֑J��
    TransitionIdleState();
}

//�X�V����
void Player::Update(float elapsedTime)
{
    // B�{�^���Ń_���[�W��Ԃ֑J��(��)
    GamePad& gamePad = Input::Instance().GetGamePad();
    if (gamePad.GetButtonDown() & GamePad::BTN_B)
    {
        TransitionDamageState();
    }

    // ��Ԗ��̍X�V����(���Ԃɗ]�T����ΕύX������)
    switch (state)
    {
    case Player::State::Idle:
        UpdateIdleState(elapsedTime);
        break;
    case Player::State::Damage:
        UpdateDamageState(elapsedTime);
        break;
    }

    //  �󕠃��x���̍X�V
    UpdateHungerPoint(elapsedTime);

    // �X�P�[���̍X�V
    UpdateScale(MaxScale[hungerLevel], ScaleRate);

    //�I�u�W�F�N�g�s����X�V
    UpdateTransform();

    // ���f���A�j���[�V�����X�V����
    model->UpdateAnimation(elapsedTime);

    //���f���s��X�V
    model->UpdateTransform(transform);
}

// �`�揈��
void Player::Draw(RenderContext rc, ModelShader* shader)
{
    shader->Draw(rc, model.get());
}

// �_���[�W��^����
bool Player::ApplyDamage(int damage, float invincibleTime)
{
    // �_���[�W���O�̏ꍇ�͌��N��Ԃ�ύX����K�v���Ȃ�
    if (damage == 0)return false;

    // ���S���Ă���Ԃ͌��N��Ԃ�ύX���Ȃ�
    if (health <= 0)return false;

    if (invincibleTimer > 0.0f)return false;

    invincibleTimer = invincibleTime;

    // �_���[�W����
    health -= damage;

    // ���S�ʒm
    if (health <= 0)
    {
        OnDead();
    }
    else
    {
        OnDamaged();
    }

    // ���N��Ԃ��ύX�����ꍇ��true��Ԃ�
    return true;
}

// ���x�����X�V
void Player::UpdateVelocity(float elapsedTime)
{
    // �o�߃t���[��
    float elapsedFrame = 60.0f * elapsedTime;

    // �������͍X�V����
    UpdataHorizontalVelocity(elapsedFrame);

    // �����ړ��X�V����
    UpdateHorizontalMove(elapsedTime);
}

// ���G���ԍX�V
void Player::UpdateInvincibleTimer(float elapsedTime)
{
    if (invincibleTimer > 0.0f)
    {
        invincibleTimer -= elapsedTime;
    }
}

//�f�o�b�OGUI�`��
void Player::DrawDebugGUI()
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
            // ���x
            ImGui::InputFloat3("velocity", &velocity.x);
        }
    }


    if (ImGui::CollapsingHeader("HungerPoint", ImGuiTreeNodeFlags_DefaultOpen))
    {
        // �󕠃��x��
        ImGui::SliderInt("hungerLevel", &hungerLevel, 0, 2);
        // �󕠗�
        ImGui::SliderFloat("hungerAmount", &hungerPoint, 0.0f, MaxHungerPoint);
        // ���Z��
        static float add = 10.0f;
        ImGui::InputFloat("AddAmount", &add);
        // �󕠗ʉ��Z
        if (ImGui::Button("add"))
        {
            AddHungerPoint(add);
        }
    }

    ImGui::End();
}

//�s��X�V����
void Player::UpdateTransform()
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

// �X�e�B�b�N���͒l����ړ��x�N�g�����擾
float Player::GetMoveVecX() const
{
    // ���͏����擾
    GamePad& gamePad = Input::Instance().GetGamePad();
    float ax = gamePad.GetAxisLX();

    return ax;
}

// �������͍X�V����
void Player::UpdataHorizontalVelocity(float elapsedFrame)
{
    // XZ���ʂ̑��͂���������
    float length = sqrtf(velocity.x * velocity.x);
    if (length > 0.0f)
    {
        // ���C��
        float friction = this->friction * elapsedFrame;

        // ���C�ɂ�鉡�����̌�������
        if (length > friction)
        {
            float vx = velocity.x / length;

            velocity.x -= vx * friction;
        }
        // �������̑��͂����C�͈ȉ��ɂȂ����̂ő��͂𖳌���
        else
        {
            velocity.x = 0;
        }
    }

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
            velocity.x += moveVecX * acceleration;

            // �ő呬�x����
            float length = sqrtf(velocity.x * velocity.x);
            if (length > maxMoveSpeed)
            {
                float vx = velocity.x / length;

                velocity.x = vx * maxMoveSpeed;
            }
        }
    }
    // �ړ��x�N�g�������Z�b�g
    moveVecX = 0.0f;
}

// �����ړ��X�V����
void Player::UpdateHorizontalMove(float elapsedTime)
{
    // �ړ�����
    position.x += velocity.x * elapsedTime;
}

// �ҋ@��Ԃ֑J��
void Player::TransitionIdleState()
{
    state = State::Idle;

    // �A�j���[�V�����Đ�
    model->PlayAnimation(Anim_Idle, true, 0.0f);
}
// �ҋ@��ԍX�V
void Player::UpdateIdleState(float elapsedTime)
{
    //// �ړ����͏���
    //InputMove(elapsedTime);

    //// ���x�����X�V
    //UpdateVelocity(elapsedTime);

    // �X������
    Lean(elapsedTime, LeanRate);
}


// �_���[�W��Ԃ֑J��
void Player::TransitionDamageState()
{
    state = State::Damage;

    // �A�j���[�V�����Đ�
    model->PlayAnimation(Anim_Damage, false,0.1f);
    isDamageAnim = true;        // �_���[�W�A�j���Đ��J�n
}
// �_���[�W��ԍX�V
void Player::UpdateDamageState(float elapsedTime)
{
    // �A�j���[�V�����Đ����I�������ҋ@��Ԃ֑J��
    if (!model->IsPlayAnimation())
    {
        TransitionIdleState();
        isDamageAnim = false;   // �_���[�W�A�j���Đ��I��
    }
}


// ������Ԃ֑J��
void Player::TransitionNodState()
{
    // �A�j���[�V�����Đ�
    model->PlayAnimation(Anim_Nod, false);
}

// �X������
void Player::Lean(float elapsedTime, float rate)
{
    float vx = velocity.x;
    float Angle = 0.0f;
    float Rate = LeanRate_0;

    // vx��0.0�łȂ��Ȃ�(�L�[��������Ă�����)
    if ((vx > FLT_EPSILON) || (vx < -FLT_EPSILON))
    {
        Angle = vx > FLT_EPSILON ? DirectX::XMConvertToRadians(-LeanAngle) : DirectX::XMConvertToRadians(LeanAngle);
        Rate = LeanRate;
    }
    angle.z = angle.z + (Rate) * (Angle - angle.z);
}

// �X�P�[���X�V
void Player::UpdateScale(float maxScale, float rate)
{
    float length = maxScale - scale.x;
    // �l�������ȏꍇ�͏������Ȃ�
    if (fabs(length) > 1e-8f)
    {
        //return a + t * (b - a);
        scale.x = scale.y = scale.z = scale.x + rate * (maxScale - scale.x);
    }
}

void Player::UpdateHungerPoint(float elapsedTime)
{
    // �펞�󕠗ʂ���������
    RemoveHungerPoint(elapsedTime, 1.0f);

    // �󕠃��x���X�V
    UpdateHungerLevel();
}

// �󕠃��x���X�V
void Player::UpdateHungerLevel()
{
    if (hungerPoint >= HungerLevelLine[1]) hungerLevel = 2;
    else if (hungerPoint < HungerLevelLine[0])hungerLevel = 0;
    else hungerLevel = 1;
}

// �󕠃|�C���g���Z
void Player::AddHungerPoint(float add)
{
    // �ő�l�ȏ�Ȃ�return����
    if (hungerPoint >= MaxHungerPoint) return;
    hungerPoint += add;
    // ���ߏC��
    hungerPoint = (std::min)(hungerPoint, MaxHungerPoint);
}

void Player::RemoveHungerPoint(float elapsedTime,float Remove)
{
    // 0�ȉ��Ȃ�return����
    if (hungerPoint <= 0.0f) return;
    hungerPoint -= Remove * elapsedTime;
    // ���ߏC��
    hungerPoint = (std::max)(hungerPoint, 0.0f);
}
