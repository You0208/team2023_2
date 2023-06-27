#pragma once
#include <vector>
#include "graphics/shader.h"
#include "graphics/model.h"

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

    // ���a�擾
    float GetRadius() const { return radius; }

    // �����擾
    float GetHeight() const { return height; }

    // == �ǉ������֐�(���̕��͂��Ƃō폜����) ==
    void SetScrollVelocity(DirectX::XMFLOAT3* ScrollVelocity) { scrollVelocity = ScrollVelocity; }

private:
    // ���񏈗�
    void Turn(float elapsedtime, float vx, float vz, float speed);

    // ���x�����X�V
    void UpdateVelocity(float elapsedTime);

    // �������͍X�V����
    void UpdataHorizontalVelocity(float elapsedFrame);

    // �����ړ��X�V����
    void UpdateHorizontalMove(float elapsedTime);

    // �������͍X�V����
    void UpdataVerticalVelocity(float elapsedFrame);

    // �����ړ��X�V����
    void UpdateVerticalMove(float elapsedTime);

public:
    // ���f���͌Ăяo���̂�public
    std::unique_ptr<Model>  model       =    nullptr;        // ���f��

protected:
    DirectX::XMFLOAT3   position        = { 0,0,0 };        // �ʒu
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
};


// �|�b�L�[
class Pokey : public Obstacle
{
public:
    Pokey();
    // �X�V����
    void Update(float elapsedTime)override;
};


// �}�V���}��(�x�[�X)
class Marshmallow_Base : public Obstacle
{
public:
    Marshmallow_Base() {}
    // �X�V����
    void Update(float elapsedTime)override;
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
};


// �O���[�v�W���[�X
class Grape_can : public Obstacle
{
public:
    Grape_can();
};


// �I�����W�K��
class Orange_gum : public Obstacle
{
public:
    Orange_gum();
};


// �L�����f�B�[�Q�[�g
class Candy_gate : public Obstacle
{
public:
    Candy_gate();
};


// �I�����W�W���[�X
class Orange_can : public Obstacle
{
public:
    Orange_can();
};


// �}�[�u���`���R
class Marble_chocolate : public Obstacle
{
public:
    Marble_chocolate();
};


// �J�b�v�P�[�L(�x�[�X)
class Cupcake_Base : public Obstacle
{
public:
    Cupcake_Base(){}
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