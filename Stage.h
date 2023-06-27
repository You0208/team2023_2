#pragma once
#include <vector>
#include "Graphics/Shader.h"
#include "Graphics/Model.h"
#include "BaseStage.h"
#include "Obstacle.h"

//ステージ
class Stage: public BaseStage
{
public:
    static const int StageKindMax           = 2;        //ステージの種類の最大数
    static const int ObsTypeMax             = 2;        //障害物の種類の最大数
    static const int StageSideMax           = 3;	    //ステージの最大数(左右)
    static const int StageDepthMax          = 5;	    //ステージの最大数(奥行)
    static constexpr float StageSize        = 30.0f;    //ステージのサイズ
    static const int ObsMax                 = 30;       //障害物の最大数

public:
    Stage();
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

private:                  // 障害物

    float offset        = 0.2f;

private:
    // ステージ情報
    // ステージ01
    static void StageInfo01(Stage* stage);
    // ステージ02
    static void StageInfo02(Stage* stage);

private:
    // デバッグ用
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