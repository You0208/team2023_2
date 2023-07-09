#pragma once
#include <vector>
#include "Graphics/Shader.h"
#include "Graphics/Model.h"
#include "BaseStage.h"
#include "Obstacle.h"

// �X�e�[�W
class Stage: public BaseStage
{
public:
    static const int StageMax               = 5;        //�X�e�[�W�̍ő吔
    static const int StageSideMax           = 2;	    //�X�e�[�W�̍ő吔(���E)
    static const int StageDepthMax          = 3;	    //�X�e�[�W�̍ő吔(���s)
    static constexpr float StageSize        = 500.0f;    //�X�e�[�W�̃T�C�Y

public:
    Stage(int stageNo,bool Endless);
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

    //�G���h���X���[�h�ɒ���ł���t���O
    void FoldIsEndless() { IsEndless = false; }

private:
    // �X�e�[�W�̐���
    void StageSpawn()override;

private:                  // ��Q��
    float offset        = 0.2f;
    static bool IsEndless;    // �G���h���X���[�h�ɒ���ł���t���O

private:
    // �G���A���
      // �G���A00
    static void AreaInfo00(Stage* stage) {}
    // �G���A01
    static void AreaInfo01(Stage* stage);
    // �G���A02
    static void AreaInfo02(Stage* stage);
    // �G���A03
    static void AreaInfo03(Stage* stage);
    // �G���A04
    static void AreaInfo04(Stage* stage);
    // �G���A05
    static void AreaInfo05(Stage* stage);
    // �G���A06
    static void AreaInfo06(Stage* stage);
    // �G���A07
    static void AreaInfo07(Stage* stage);
    // �G���A08
    static void AreaInfo08(Stage* stage);
    // �G���A09
    static void AreaInfo09(Stage* stage);
    // �G���A10
    static void AreaInfo10(Stage* stage);
    // �G���A11
    static void AreaInfo11(Stage* stage);
    // �G���A12
    static void AreaInfo12(Stage* stage);
    // �G���A13
    static void AreaInfo13(Stage* stage);
    // �G���A14
    static void AreaInfo14(Stage* stage);
    // �G���A15
    static void AreaInfo15(Stage* stage);

    // �f�o�b�O�pINFO
    static void  AreaInfoDebug(Stage* stage);
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
    // �X�e�[�WNONE
    static SpawnObstacleInfo StageNONE[];
    // �X�e�[�W01
    static SpawnObstacleInfo StageInfo01[];
    // �X�e�[�W02
    static SpawnObstacleInfo StageInfo02[];
    // �X�e�[�W03
    static SpawnObstacleInfo StageInfo03[];
    // �X�e�[�W04
    static SpawnObstacleInfo StageInfo04[];
    // �X�e�[�W05
    static SpawnObstacleInfo StageInfo05[];
    // �X�e�[�W�G���h���X
    static SpawnObstacleInfo StageInfoEndless[];

    // �X�e�[�WDebug
    static SpawnObstacleInfo stageDebug[];

    static constexpr SpawnObstacleInfo* StageDebug[StageMax + 1]
    {
        stageDebug
        ,stageDebug
        ,stageDebug
        ,stageDebug
        ,stageDebug
        ,stageDebug
    };

    static constexpr SpawnObstacleInfo* stageInfo[StageMax + 1]
    {
        StageInfo01
        ,StageInfo02
        ,StageInfo03
        ,StageInfo04
        ,StageInfo05
        ,StageInfoEndless
    };

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
        jellybeans_Orange,
        chocolate_ball,
        grape_can,
        orange_gum,
        husen_gum,
        candy_gate,
        orange_can,
        marble_chocolate,
        cupcake_Choco,
        cupcake_Pink,
        pudding,
        macaron_Maccha,
        macaron_Ping,

        Max
    };
    static int ObstacleNumber;
    static void StageInfoDebug(Stage* stage,int n);
public:
    static void DrawDebugGUI_();
};