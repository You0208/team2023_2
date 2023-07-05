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
    Stage(int stageNo);
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

private:
    // ステージの生成
    void StageSpawn()override;

private:                  // 障害物
    float offset        = 0.2f;

private:
    // エリア情報
    // エリア00
    static void AreaInfo00(Stage* stage){}
    // エリア01
    static void AreaInfo01(Stage* stage);
    // エリア02
    static void AreaInfo02(Stage* stage);
    // エリア03
    static void AreaInfo03(Stage* stage);

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

    // ステージDebug
    static SpawnObstacleInfo stageDebug[];

    static constexpr SpawnObstacleInfo* StageDebug[StageMax]
    {
        stageDebug
        ,stageDebug
        ,stageDebug
        ,stageDebug
        ,stageDebug
    };

    static constexpr SpawnObstacleInfo* stageInfo[StageMax]
    {
        StageInfo01
        ,StageInfo02
        ,StageInfo03
        ,StageInfo04
        ,StageInfo05
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