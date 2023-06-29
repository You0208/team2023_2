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
    static const int StageSideMax           = 2;	    //�X�e�[�W�̍ő吔(���E)
    static const int StageDepthMax          = 3;	    //�X�e�[�W�̍ő吔(���s)
    static constexpr float StageSize        = 50.0f;    //�X�e�[�W�̃T�C�Y

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
    // �G���A���
    // �G���A00
    static void AreaInfo00(Stage* stage){}
    // �G���A01
    static void AreaInfo01(Stage* stage);
    // �G���A02
    static void AreaInfo02(Stage* stage);

public:
    typedef	void(*AreaInfo)(Stage* stage);
    
    // �������x��
    enum SpawnLevel
    {
        high,
        middle,
        low,
    };
    // ���������Q���̏��
    struct SpawnObstacleInfo
    {
        AreaInfo info;          // ���������Q���̃f�[�^
        int spawnRate;          // ��������m��(���E���E��)
    };

    // ��������G���A���(�֐��|�C���^)��Ԃ�
    AreaInfo RandSpawn(Stage::SpawnObstacleInfo* data);

private:
    // �X�e�[�W���
    // �X�e�[�W01
    static SpawnObstacleInfo StageInfo01[];
    // �X�e�[�W02
    static SpawnObstacleInfo StageInfo02[];

    static constexpr SpawnObstacleInfo* stageInfo[StageKindMax]
    {
        StageInfo01
        ,StageInfo02
    };

    // None�X�e�[�W
    //static void StageInfo
private:
    // �f�o�b�O�p
    enum  ObstacleName
    {
        cola,
        pokey,
        prits,
        marshmallow_Blue,
        marshmallow_Pink,
        jellybeans_Yellow,
        jellybeans_Pink,
        jellybeans_Green,
        chocolate_ball,
        grape_can,
        orange_gum,
        husen_gum,
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