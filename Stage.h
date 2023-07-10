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
    // �X�e�[�W2�ȍ~ 
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
    // �G���A16
    static void AreaInfo16(Stage* stage);
    // �G���A17
    static void AreaInfo17(Stage* stage);
    // �G���A18
    static void AreaInfo18(Stage* stage);
    // �G���A19
    static void AreaInfo19(Stage* stage);
    // �G���A20
    static void AreaInfo20(Stage* stage);
    // �G���A21
    static void AreaInfo21(Stage* stage);
    // �G���A22
    static void AreaInfo22(Stage* stage);
    // �G���A23
    static void AreaInfo23(Stage* stage);
    // �G���A24
    static void AreaInfo24(Stage* stage);
    // �G���A25
    static void AreaInfo25(Stage* stage);
    // �G���A26
    static void AreaInfo26(Stage* stage);
    // �G���A27
    static void AreaInfo27(Stage* stage);
    // �G���A28
    static void AreaInfo28(Stage* stage);
    // �G���A29
    static void AreaInfo29(Stage* stage);
    // �G���A30
    static void AreaInfo30(Stage* stage);
    // �G���A31
    static void AreaInfo31(Stage* stage);
    // �G���A32
    static void AreaInfo32(Stage* stage);
    // �G���A33
    static void AreaInfo33(Stage* stage);
    // �G���A34
    static void AreaInfo34(Stage* stage);
    // �G���A35
    static void AreaInfo35(Stage* stage);
    // �G���A36
    static void AreaInfo36(Stage* stage);
    // �G���A37
    static void AreaInfo37(Stage* stage);
    // �G���A38
    static void AreaInfo38(Stage* stage);
    // �G���A39
    static void AreaInfo39(Stage* stage);
    // �G���A40
    static void AreaInfo40(Stage* stage);

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