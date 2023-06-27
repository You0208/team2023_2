#pragma once
#include <vector>
#include "Graphics/Shader.h"
#include "Graphics/Model.h"
#include "BaseStage.h"
#include "Obstacle.h"

//�X�e�[�W
class Stage: public BaseStage
{
public:
    static const int StageKindMax           = 2;        //�X�e�[�W�̎�ނ̍ő吔
    static const int ObsTypeMax             = 2;        //��Q���̎�ނ̍ő吔
    static const int StageSideMax           = 3;	    //�X�e�[�W�̍ő吔(���E)
    static const int StageDepthMax          = 5;	    //�X�e�[�W�̍ő吔(���s)
    static constexpr float StageSize        = 30.0f;    //�X�e�[�W�̃T�C�Y
    static const int ObsMax                 = 30;       //��Q���̍ő吔

public:
    Stage();
    ~Stage();

    void DrawDebugGUI(){}

    // ������
    void Initialize();

    //�X�V����
    void Update(float elapsedTime);

    // �`�揈��
    void Draw(RenderContext rc, ModelShader* shader);

    // �A�C�e���E��Q���̒ǉ�
    void AddObstacle(Obstacle* obstacle) { obstacles.emplace_back(obstacle); }

private:                  // ��Q��

    float offset        = 0.2f;

private:
    // �X�e�[�W���
    // �X�e�[�W01
    static void StageInfo01(Stage* stage);
    // �X�e�[�W02
    static void StageInfo02(Stage* stage);

private:
    // �f�o�b�O�p
    enum  ObstacleName
    {
        cola,
        pokey,
        marshmallow_Blue,
        marshmallow_Pink,
        jellybeans_Yellow,
        jellybeans_Pink,
        jellybeans_Green,
        chocolate_ball,
        grape_can,
        orange_gum,
        candy_gate,
        orange_can,
        marble_chocolate,
        cupcake_Choco,
        cupcake_Pink,

        Max
    };
    static int ObstacleNumber;
    static void StageInfoDebug(Stage* stage,int n);
public:
    static void DrawDebugGUI_();
};