#pragma once
#include "Graphics/Shader.h"
#include "Graphics/Model.h"

//�v���C���[
class Player
{
public:
    static constexpr float LeanAngle = 30.0f;       // ���E�ړ����̌X���p�x
    static constexpr float LeanRate  = 0.03f;       // �X���̕�ԌW��
    static constexpr float LeanRate_0= 0.01f;       // �߂�X����ԌW��
public:

    Player();
    ~Player() {}

    //�X�V����  
    void Update(float elapsedTime);

    // �`�揈��
    void Draw(RenderContext rc, ModelShader* shader);

    //�f�o�b�OGUI�`��
    void DrawDebugGUI();

    //�s��X�V����
    void UpdateTransform();

    // �_���[�W��^����
    bool ApplyDamage(int damage, float invincibleTime);
    
    // �ʒu�X�V
    void SetPosition(const DirectX::XMFLOAT3& position) { this->position = position; }
    // ��]�X�V
    void SetAngle(const DirectX::XMFLOAT3& angle) { this->angle = angle; }
    // �X�P�[���X�V
    void SetScale(const DirectX::XMFLOAT3& scale) { this->scale = scale; }
    // ���x�X�V
    void SetVelocity(const DirectX::XMFLOAT3& velocity) { this->velocity = velocity; }

    // �ʒu�擾
    const DirectX::XMFLOAT3& GetPosition() const { return position; }
    // ��]�擾
    const DirectX::XMFLOAT3& GetAngle() const { return angle; }
    // �X�P�[���擾
    const DirectX::XMFLOAT3& GetScale() const { return scale; }
    // ���a�擾
    float GetRadius() const { return radius; }
    // �����擾
    float GetHeight() const { return height; }
    // ���N��Ԃ��擾
    int GetHealth() const { return health; }
    // �ő匒�N��Ԃ��擾
    int GetMaxHealth() const { return maxHealth; }
    // �_���[�W�A�j�����Đ����ł��邩���擾
    bool GetIsDamageAnim() const { return isDamageAnim; }

private:

    // ���x�����X�V
    void UpdateVelocity(float elapsedTime);

    // ���G���ԍX�V
    void UpdateInvincibleTimer(float elapsedTime);

    // �X�e�B�b�N���͒l����ړ��x�N�g�����擾
    float GetMoveVecX() const;

    // �������͍X�V����
    void UpdataHorizontalVelocity(float elapsedFrame);

    // �����ړ��X�V����
    void UpdateHorizontalMove(float elapsedTime);

    // �_���[�W���󂯂��Ƃ��ɌĂ΂��
    virtual void OnDamaged() {}

    // ���S�������ɌĂ΂��
    virtual void OnDead() {}

    // == �ǉ������֐�(���̕��͂��Ƃō폜����) ==

    // �ҋ@��Ԃ֑J��
    void TransitionIdleState();
    // �ҋ@��ԍX�V
    void UpdateIdleState(float elapsedTime);

    // �_���[�W��Ԃ֑J��
    void TransitionDamageState();
    // �_���[�W��ԍX�V
    void UpdateDamageState(float elapsedTime);

    // ������Ԃ֑J��
    void TransitionNodState();

    // �X������
    void Lean(float elapsedTime,float rate);
    
public:
    // ���f����scene��render�ŌĂяo���̂�public
    std::unique_ptr<Model>  model      = nullptr;       // ���f��
private:
    enum class State
    {
        Idle
        , Damage
    };
    enum Anination
    {
        Anim_Idle,     // �ҋ@
        Anim_Nod,       // ����
        Anim_Damage,    // �_���[�W
    };

    DirectX::XMFLOAT3   position       = { 0,0,0 };     // �ʒu
    DirectX::XMFLOAT3   angle          = { 0,0,0 };     // �p�x
    DirectX::XMFLOAT3   scale          = { 1,1,1 };     // �X�P�[��
    DirectX::XMFLOAT3   velocity       = { 0,0,0 };     // ���x
    DirectX::XMFLOAT4X4   transform    = {
        1,0,0,0,
        0,1,0,0,
        0,0,1,0,
        0,0,0,1,
    };
    float   height                     = 2.0f;           // ����
    float   radius                     = 0.5f;           // ���a

    float   acceleration               = 10.0f;          // ������
    float   moveSpeed                  = 10.0f;          // �ړ����x
    float   maxMoveSpeed               = 30.0f;          // �ő�ړ����x

    float   friction                   = 0.5f;           // ����
    
    float   moveVecX                   = 0.0f;           // �ړ������x�N�g��

    int     health                     = 5;              // �̗�
    int     maxHealth                  = 5;              // �ő�̗�
    float   invincibleTimer            = 1.0f;           // ���G����

    // ��]���x
    float   turnSpeed                  = DirectX::XMConvertToRadians(720);

    // �ǉ������ϐ�(���̕��͂��Ƃŏ���)
    State   state                       = State::Idle;  // ���݂̏��
    bool    isDamageAnim                = false;        // �_���[�W�A�j�����Đ�����
    bool    wait[3]                     = {};
};