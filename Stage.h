#pragma once
#include <vector>
#include "Graphics/Shader.h"
#include "Graphics/Model.h"
#include "BaseStage.h"
#include "Obstacle.h"

// ステージ
class Stage: public BaseStage
{
public:
    static const int StageMax               = 5;        //ステージの最大数
    static const int StageSideMax           = 2;	    //ステージの最大数(左右)
    static const int StageDepthMax          = 3;	    //ステージの最大数(奥行)
    static constexpr float StageSize        = 500.0f;    //ステージのサイズ

public:
    Stage(int stageNo,bool Endless);
    ~Stage();

    void DrawDebugGUI(){}

    // 初期化
    void Initialize();

    //更新処理
    void Update(float elapsedTime);

    // 描画処理
    void Draw(RenderContext rc, ModelShader* shader);

    // アイテム・障害物の追加
    void AddObstacle(Obstacle* obstacle) { obstacles.emplace_back(obstacle); }

    //エンドレスモードに挑戦できるフラグ
    void FoldIsEndless() { IsEndless = false; }

private:
    // ステージの生成
    void StageSpawn()override;

private:                  // 障害物
    float offset        = 0.2f;
    static bool IsEndless;    // エンドレスモードに挑戦できるフラグ

private:
    // エリア情報
      // エリア00
    static void AreaInfo00(Stage* stage) {}
    // エリア01
    static void AreaInfo01(Stage* stage);
    // エリア02
    static void AreaInfo02(Stage* stage);
    // エリア03
    static void AreaInfo03(Stage* stage);
    // エリア04
    static void AreaInfo04(Stage* stage);
    // エリア05
    static void AreaInfo05(Stage* stage);
    // エリア06
    static void AreaInfo06(Stage* stage);
    // エリア07
    static void AreaInfo07(Stage* stage);
    // エリア08
    static void AreaInfo08(Stage* stage);
    // ステージ2以降 
    // エリア09
    static void AreaInfo09(Stage* stage);
    // エリア10
    static void AreaInfo10(Stage* stage);
    // エリア11
    static void AreaInfo11(Stage* stage);
    // エリア12
    static void AreaInfo12(Stage* stage);
    // エリア13
    static void AreaInfo13(Stage* stage);
    // エリア14
    static void AreaInfo14(Stage* stage);
    // エリア15
    static void AreaInfo15(Stage* stage);
    // エリア16
    static void AreaInfo16(Stage* stage);
    // エリア17
    static void AreaInfo17(Stage* stage);
    // エリア18
    static void AreaInfo18(Stage* stage);
    // エリア19
    static void AreaInfo19(Stage* stage);
    // エリア20
    static void AreaInfo20(Stage* stage);
    // エリア21
    static void AreaInfo21(Stage* stage);
    // エリア22
    static void AreaInfo22(Stage* stage);
    // エリア23
    static void AreaInfo23(Stage* stage);
    // エリア24
    static void AreaInfo24(Stage* stage);
    // エリア25
    static void AreaInfo25(Stage* stage);
    // エリア26
    static void AreaInfo26(Stage* stage);
    // エリア27
    static void AreaInfo27(Stage* stage);
    // エリア28
    static void AreaInfo28(Stage* stage);
    // エリア29
    static void AreaInfo29(Stage* stage);
    // エリア30
    static void AreaInfo30(Stage* stage);
    // エリア31
    static void AreaInfo31(Stage* stage);
    // エリア32
    static void AreaInfo32(Stage* stage);
    // エリア33
    static void AreaInfo33(Stage* stage);
    // エリア34
    static void AreaInfo34(Stage* stage);
    // エリア35
    static void AreaInfo35(Stage* stage);
    // エリア36
    static void AreaInfo36(Stage* stage);
    // エリア37
    static void AreaInfo37(Stage* stage);
    // エリア38
    static void AreaInfo38(Stage* stage);
    // エリア39
    static void AreaInfo39(Stage* stage);
    // エリア40
    static void AreaInfo40(Stage* stage);

    // デバッグ用INFO
    static void  AreaInfoDebug(Stage* stage);
public:
    typedef	void(*AreaInfo)(Stage* stage);
    
    // 生成レベル
    enum SpawnLevel
    {
        high,
        middle,
        low,
    };
    // 生成する障害物の情報
    struct SpawnObstacleInfo
    {
        AreaInfo info;          // 生成する障害物のデータ
        int spawnRate;          // 生成する確率(高・中・低)
    };

    // 生成するエリア情報(関数ポインタ)を返す
    AreaInfo RandSpawn(Stage::SpawnObstacleInfo* data);

private:
    // ステージ情報
    // ステージNONE
    static SpawnObstacleInfo StageNONE[];
    // ステージ01
    static SpawnObstacleInfo StageInfo01[];
    // ステージ02
    static SpawnObstacleInfo StageInfo02[];
    // ステージ03
    static SpawnObstacleInfo StageInfo03[];
    // ステージ04
    static SpawnObstacleInfo StageInfo04[];
    // ステージ05
    static SpawnObstacleInfo StageInfo05[];
    // ステージエンドレス
    static SpawnObstacleInfo StageInfoEndless[];

    // ステージDebug
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
    // デバッグ用
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