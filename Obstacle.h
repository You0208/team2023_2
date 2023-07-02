#pragma once
#include <vector>
#include "graphics/shader.h"
#include "graphics/model.h"

enum TYPE
{
    CYLINDER,
    CYLINDERS,
    ITEMS,
    GATE,
};

enum HIT_CHECK_TYPE
{
    ACTIVE,     // �ϋɓI�ɓ����蔻����Ƃ�
    DEACTIVE,   // ��ϋɓI�ɓ����蔻����Ƃ�
    NOT         // �����蔻����Ƃ�Ȃ�
};

// ��Q���i���N���X�j
class Obstacle 
{
public:
    Obstacle(){}

    ~Obstacle() {}

    // �`�揈��
    void Draw(RenderContext rc, ModelShader* shader) ;

    // �X�V����
    virtual void Update(float elapsedTime);

    //�f�o�b�OGUI�`��
    void DrawDebugGUI();

    //�s��X�V����
    void UpdateTransform();

    // �ʒu�擾
    const DirectX::XMFLOAT3& GetPosition() const { return position; }

    // �ʒu�ݒ�
    void SetPosition(DirectX::XMFLOAT3 p)  { position = p; }
    void SetOriginPosition(DirectX::XMFLOAT3* p)  { OriginPosition = p; }

    // ���a�擾
    float GetRadius() const { return radius; }

    // �����擾
    float GetHeight() const { return height; }

    // �A�C�e���擾���o
    void GetItem();

    // == �ǉ������֐�(���̕��͂��Ƃō폜����) ==
    void SetScrollVelocity(DirectX::XMFLOAT3* ScrollVelocity) { scrollVelocity = ScrollVelocity; }

private:
    // ���񏈗�
    void Turn(float elapsedtime, float vx, float vz, float speed);

    // ���x�����X�V
    void UpdateVelocity(float elapsedTime);

    // ���x�̒ǉ��X�V
    virtual void UpdataAdditionVelocity(float elapsedFrame) {}

    // �ړ��X�V����
    void UpdateMove(float elapsedTime);

    // �f�o�b�O�v���~�e�B�u�`��
    virtual void DrawDebugPrimitive() {};
public:
    // ���f���͌Ăяo���̂�public
    std::unique_ptr<Model>  model       =    nullptr;        // ���f��

    int score = 0;
    int hungerPoint = 0;
    int Type = 0;
    int HitCheckTYpe = HIT_CHECK_TYPE::DEACTIVE;
    int CollisionNum = 0;
    bool IsHit = false;                                     // �΃v���C���[
    bool IsHitVsObs = false;                                // ��Obstacle
protected:
    DirectX::XMFLOAT3   position        = { 0,0,0 };        // �ʒu
    DirectX::XMFLOAT3*  OriginPosition  = nullptr;          // �X�e�[�W�̌��_
    DirectX::XMFLOAT3   angle           = { 0,0,0 };        // �p�x
    DirectX::XMFLOAT3   scale           = { 1,1,1 };        // �X�P�[��
    DirectX::XMFLOAT3   velocity        = { 0,0,0 };        // ���x
    DirectX::XMFLOAT3*  scrollVelocity  = &velocity;        // �X�N���[�����x�̃|�C���^(�����l�͎�����velocity)
    DirectX::XMFLOAT4X4   transform = {
        1,0,0,0,
        0,1,0,0,
        0,0,1,0,
        0,0,0,1,
    };
    float   height                      = 2.0f;             // ����
    float   radius                      = 0.5f;             // ���a

    float   moveVecX                    = 0.0f;             // �ړ������x�N�g��
    float   moveVecZ                    = 0.0f;             // �ړ������x�N�g��

    float   gravity                     = -1.0f;            // �d��

    bool    isGround                    = false;            // �n�ʔ���

    float   friction                    = 0.5f;             // ���C��
    float   acceleration                = 1.0f;             // ������
    float   maxMoveSpeed                = 5.0f;             // �ő�ړ����x
    float	airControl                  = 0.3f;             // ��C
};


// �R�[��
class Cola : public Obstacle
{
public:
    Cola();
    // �X�V����
    void Update(float elapsedTime)override;

    // �f�o�b�O�v���~�e�B�u�`��
    void DrawDebugPrimitive()override;
};


// �|�b�L�[
class Pokey : public Obstacle
{
public:
    Pokey();
    // �X�V����
    void Update(float elapsedTime)override;

    // �f�o�b�O�v���~�e�B�u�`��
    void DrawDebugPrimitive()override;
};

// �v���b�c
class Prits : public Obstacle
{
public:
    Prits();
};

// �}�V���}��(�x�[�X)
class Marshmallow_Base : public Obstacle
{
public:
    Marshmallow_Base() {}
    // �X�V����
    void Update(float elapsedTime)override;

    // �f�o�b�O�v���~�e�B�u�`��
    void DrawDebugPrimitive()override;
};
// �}�V���}��(��)
class Marshmallow_Blue : public Marshmallow_Base
{
public:
    Marshmallow_Blue();
};
// �}�V���}��(�s���N)
class Marshmallow_Pink : public Marshmallow_Base
{
public:
    Marshmallow_Pink();
};


// �r�[���Y(�x�[�X)
class Jellybeans_Base : public Obstacle
{
public:
    Jellybeans_Base() { scale = { 0.5f,0.5f ,0.5f }; }
    // �X�V����
    void Update(float elapsedTime)override;
    // �f�o�b�O�v���~�e�B�u�`��
    void DrawDebugPrimitive()override;
};
// �r�[���Y(���F)
class Jellybeans_Yellow : public Jellybeans_Base
{
public:
    Jellybeans_Yellow();
};
// �r�[���Y(�s���N)
class Jellybeans_Pink : public Jellybeans_Base
{
public:
    Jellybeans_Pink();
};
// �r�[���Y(�O���[��)
class Jellybeans_Green : public Jellybeans_Base
{
public:
    Jellybeans_Green();
};


// �`���R�{�[��
class Chocolate_ball : public Obstacle
{
public:
    Chocolate_ball();
    // �X�V����
    void Update(float elapsedTime)override;
    // �f�o�b�O�v���~�e�B�u�`��
    void DrawDebugPrimitive()override;
};


// �O���[�v�W���[�X
class Grape_can : public Obstacle
{
public:
    Grape_can();
    // �f�o�b�O�v���~�e�B�u�`��
    void DrawDebugPrimitive()override;
};


// �I�����W�K��
class Orange_gum : public Obstacle
{
public:
    Orange_gum();
    // �f�o�b�O�v���~�e�B�u�`��
    void DrawDebugPrimitive()override;
};

// �t�[�Z���K��
class Husen_gum : public Obstacle
{
public:
    static float constexpr MaxUp        = 10.0f;      // �㉺�ړ��̍ő�l      
    static float constexpr MaxDown      = 0.0f;      // �㉺�ړ��̍ŏ��l 
    static float constexpr MaxPos[2] =
    {
        MaxDown,
        MaxUp
    };

    static float constexpr MoveSpeed    = 100.0f;      // �㉺�ړ��̑��x

public:
    Husen_gum();
    // �f�o�b�O�v���~�e�B�u�`��
    void DrawDebugPrimitive()override;

private:
    // �ǉ��̑��͍X�V����
    void UpdataAdditionVelocity(float elapsedFrame) override;

private:
    bool isUp = true;
    bool a[3] = {};
};

// �L�����f�B�[�Q�[�g
class Candy_gate : public Obstacle
{
public:
    Candy_gate();
    // �f�o�b�O�v���~�e�B�u�`��
    void DrawDebugPrimitive()override;
};


// �I�����W�W���[�X
class Orange_can : public Obstacle
{
public:
    Orange_can();
    // �f�o�b�O�v���~�e�B�u�`��
    void DrawDebugPrimitive()override;
};


// �}�[�u���`���R
class Marble_chocolate : public Obstacle
{
private:
    static float constexpr MaxMoveDistance = 30.0f;     // �ړ������̍ő�lD
    static float constexpr MoveSpeed = 50.0f;     // �ړ������̍ő�lD

public:
    Marble_chocolate();
    // �f�o�b�O�v���~�e�B�u�`��
    void DrawDebugPrimitive()override;

private:
    // ���x�̒ǉ��X�V
    void UpdataAdditionVelocity(float elapsedFrame)override;

private:
    bool isleft = false;
};


// �J�b�v�P�[�L(�x�[�X)
class Cupcake_Base : public Obstacle
{
public:
    Cupcake_Base(){}
    // �f�o�b�O�v���~�e�B�u�`��
    void DrawDebugPrimitive()override;
};
// �J�b�v�P�[�L(�`���R)
class Cupcake_Choco : public Cupcake_Base
{
public:
    Cupcake_Choco();
};
// �J�b�v�P�[�L(�s���N)
class Cupcake_Pink : public Cupcake_Base
{
public:
    Cupcake_Pink();
};