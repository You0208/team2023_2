#include "Terrain.h"

// コンストラクタ
Terrain::Terrain()
{
    //ステージモデルを読み込み
    model = std::make_unique<Model>("Data/Model/Debug/cube.mdl");
    scale = { StageSize,0.5f ,StageSize };
    stageSideMax = StageSideMax;
    stageDepthMax = StageDepthMax;
}

// 初期化
void Terrain::Initialize()
{
}

// 更新処理
void Terrain::Update(float elapsedTime)
{
    // スクロール
    UpdateVelocity(elapsedTime);

    //行列更新
    UpdateTransform();

    //モデル行列更新
    if (model != nullptr)
        model->UpdateTransform(transform);

    // ステージ生成
    StageSpawn();

    // ステージ削除
    StageDelete();
}

// 描画処理
void Terrain::Draw(RenderContext rc, ModelShader* shader)
{
    //ステージ描画
    if (model != nullptr)
        shader->Draw(rc, model.get());
}
