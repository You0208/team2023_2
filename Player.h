#pragma once
#include "Graphics/Shader.h"
#include "Graphics/Model.h"
#include "SceneOver.h"
#include "SceneManager.h"

//�v���C���[
class Player
{
public:
    static constexpr float ScaleRate = 0.002f;  // �X�P�[���g�k�̕�ԌW��

    static constexpr float LeanAngle    = 30.0f;        // ���E�ړ����̌X���p�x
    static constexpr float LeanRate     = 0.03f;        // �X���̕�ԌW��
    static constexpr float LeanRate_0   = 0.01f;        // �߂鎞�̌X����ԌW��

    static constexpr float MaxHungerPoint       = 100.0f;   // �󕠗ʂ̍ő�l
    static constexpr float DecreaseHungerPoint   = 1.0f;    // �󕠗ʂ̌�����
    // �e�󕠃��x���ł̃X�P�[��
    static constexpr float MaxScale[3] =
    {
        0.7f,       // �󕠃��x���F��
        1.0f,       // �󕠃��x���F��
        1.3f        // �󕠃��x���F��
    };
    // �󕠃��x�����؂�ւ�鋫��
    static constexpr float HungerLevelLine[2] =
    {
        33.0f,      // ����ȏオ�󕠃��x���F��
        66.0f       // ����ȏオ�󕠃��x���F��
    };

public:

    Player();
    ~Player() {}

    // �Z���N�g�p�X�V
    void SelectUpdate(float elapsedTime);

    // �N���A�p�X�V
    void ClearUpdate(float elapsedTime);

    //�X�V����  
    void Update(float elapsedTime,bool IsSelect = false);

    // �`�揈��
    void Draw(RenderContext rc, ModelShader* shader);

    //�f�o�b�OGUI�`��
    void DrawDebugGUI();

    //�s��X�V����
    void UpdateTransform();

    // ���S�������ɌĂ΂��
    void OnDead() {
        IsDeath = true;
        position.z -= 1.5f;
    }

    void DidFromHunger();

    // �ʒu�X�V
    void SetPosition(const DirectX::XMFLOAT3& position) { this->position = position; }
    // ��]�X�V
    void SetAngle(const DirectX::XMFLOAT3& angle) { this->angle = angle; }
    void SetAngleY(const float angle) { this->angle.y = angle; }
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
    // �X�R�A�����Z����
    static void AddScore(int s) { score += s; }

    // �X�R�A���擾
    static int GetScore() { return score; }
    static void ScoreClear() { score = 0; }
    // �󕠃��x���擾
    int GetHungerLevel() const { return hungerLevel; }
    // �󕠃|�C���g�擾
    float GetHungerPoint() const { return hungerPoint; }

    // ===== ��g�p�@��Ŏg�������H =====
    
    // �_���[�W��^����
    bool ApplyDamage(int damage, float invincibleTime);
    // �󕠃|�C���g���Z
    void AddHungerPoint(float add);

private:

    // �X������
    void Lean(float elapsedTime, float rate);

    // �X�P�[���X�V
    void UpdateScale(float maxScale, float rate);

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

    // �󕠃|�C���g�X�V
    void UpdateHungerPoint(float elapsedTime);
    // �󕠃��x���X�V
    void UpdateHungerLevel();
    // �󕠃|�C���g���Z
    void RemoveHungerPoint(float elapsedTime,float Remove);

    // ===== ��g�p�@��Ŏg�������H =====

    // �X�e�B�b�N���͒l����ړ��x�N�g�����擾
    float GetMoveVecX() const;

    // ���G���ԍX�V
    void UpdateInvincibleTimer(float elapsedTime);

    // �_���[�W���󂯂��Ƃ��ɌĂ΂��
    virtual void OnDamaged() {}
    
public:
    // ���f����scene��render�ŌĂяo���̂�public
    std::unique_ptr<Model>  model      = nullptr;       // ���f��

    bool IsDeath = false;

    bool IsBreakTime = false;        // �u���C�N�^�C���ł��邩
    bool Gashi = false;// �쎀
private:
    enum class State
    {
        Idle
        , Damage
    };
    enum Anination
    {
        Anim_Idle,      // �ҋ@
        Anim_Nod,       // ����
        Anim_Damage,    // �_���[�W
    };

    DirectX::XMFLOAT3   position       = { 0,0,0 };     // �ʒu
    DirectX::XMFLOAT3   angle          = { DirectX::XMConvertToRadians(25),0,0 };     // �p�x
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

    int     maxHealth                  = 5;              // �ő�̗�
    float   invincibleTimer            = 1.0f;           // ���G����

    static int score;
    // ��]���x
    float   turnSpeed                  = DirectX::XMConvertToRadians(720);

    // �ǉ������ϐ�(���̕��͂��Ƃŏ���)
    State   state                       = State::Idle;  // ���݂̏��
    bool    isDamageAnim                = false;        // �_���[�W�A�j�����Đ�����
    bool    a[3]                        = {};

    int     hungerLevel                 = 1;            // �󕠃��x��
    float   hungerPoint                = 66.0f;         // �󕠃|�C���g

    // ===== ��g�p�@��Ŏg�������H =====
    int     health = 5;              // �̗�
};