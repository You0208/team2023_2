#pragma once
#include <vector>
#include "Graphics/Shader.h"
#include "Graphics/Model.h"
#include "BaseStage.h"

// 地面
class Terrain : public BaseStage
{
public:
    static const int StageSideMax       = 2;        // ステージの最大数(左右)
    static const int StageDepthMax      = 3;        // ステージの最大数(奥行)
    static constexpr float StageSize    = 500.0f;    // ステージのサイズ
public:
    Terrain();

    void DrawDebugGUI() {};

    // 初期化
    void Initialize();

    // 更新処理
    void Update(float elapsedTime);

    // 描画処理
    void Draw(RenderContext rc, ModelShader* shader);
};

