#include "Stage.h"
#include "SceneManager.h"
#include<imgui.h>
//-------------------------------------------------------------------------------------------------------
// 
//		 ステージ
// 
//-------------------------------------------------------------------------------------------------------

bool Stage::IsEndless = false;

// 障害物のないステージ
Stage::SpawnObstacleInfo Stage::StageNONE[] =
{
    {AreaInfo00,Stage::SpawnLevel::low}
    ,{AreaInfo00,Stage::SpawnLevel::middle}
    ,{AreaInfo00,Stage::SpawnLevel::high}

    ,{nullptr,0} // END
};

// ステージ1
Stage::SpawnObstacleInfo Stage::StageInfo01[] =
{
 {AreaInfo01,Stage::SpawnLevel::low}
    ,{AreaInfo01,Stage::SpawnLevel::middle}
    ,{AreaInfo01,Stage::SpawnLevel::high}
    ,{AreaInfo02,Stage::SpawnLevel::low}
    ,{AreaInfo02,Stage::SpawnLevel::middle}
    ,{AreaInfo02,Stage::SpawnLevel::high}
    ,{AreaInfo03,Stage::SpawnLevel::low}
    ,{AreaInfo03,Stage::SpawnLevel::middle}
    ,{AreaInfo03,Stage::SpawnLevel::high}
    ,{AreaInfo04,Stage::SpawnLevel::low}
    ,{AreaInfo04,Stage::SpawnLevel::middle}
    ,{AreaInfo04,Stage::SpawnLevel::high}
    ,{AreaInfo05,Stage::SpawnLevel::low}
    ,{AreaInfo05,Stage::SpawnLevel::middle}
    ,{AreaInfo05,Stage::SpawnLevel::high}
    ,{AreaInfo06,Stage::SpawnLevel::low}
    ,{AreaInfo06,Stage::SpawnLevel::middle}
    ,{AreaInfo06,Stage::SpawnLevel::high}
    ,{AreaInfo07,Stage::SpawnLevel::low}
    ,{AreaInfo07,Stage::SpawnLevel::middle}
    ,{AreaInfo07,Stage::SpawnLevel::high}
    ,{AreaInfo08,Stage::SpawnLevel::low}
    ,{AreaInfo08,Stage::SpawnLevel::middle}
    ,{AreaInfo08,Stage::SpawnLevel::high}




    //{AreaInfo09,Stage::SpawnLevel::low}
    //,{AreaInfo09,Stage::SpawnLevel::middle}
    //,{AreaInfo09,Stage::SpawnLevel::high}
    //,{AreaInfo10,Stage::SpawnLevel::low}
    //,{AreaInfo10,Stage::SpawnLevel::middle}
    //,{AreaInfo10,Stage::SpawnLevel::high}
    //,{AreaInfo11,Stage::SpawnLevel::low}
    //,{AreaInfo11,Stage::SpawnLevel::middle}
    //,{AreaInfo11,Stage::SpawnLevel::high}
    //,{AreaInfo12,Stage::SpawnLevel::low}
    //,{AreaInfo12,Stage::SpawnLevel::middle}
    //,{AreaInfo12,Stage::SpawnLevel::high}
    //,{AreaInfo13,Stage::SpawnLevel::low}
    //,{AreaInfo13,Stage::SpawnLevel::middle}
    //,{AreaInfo13,Stage::SpawnLevel::high}
    //,{AreaInfo14,Stage::SpawnLevel::low}
    //,{AreaInfo14,Stage::SpawnLevel::middle}
    //,{AreaInfo14,Stage::SpawnLevel::high}
    //,{AreaInfo15,Stage::SpawnLevel::low}
    //,{AreaInfo15,Stage::SpawnLevel::middle}
    //,{AreaInfo15,Stage::SpawnLevel::high}
    //    ,{AreaInfo16,Stage::SpawnLevel::low}
    //,{AreaInfo16,Stage::SpawnLevel::middle}
    //,{AreaInfo16,Stage::SpawnLevel::high}




    //    {AreaInfo17,Stage::SpawnLevel::low}
    //,{AreaInfo17,Stage::SpawnLevel::middle}
    //,{AreaInfo17,Stage::SpawnLevel::high}
    //,{AreaInfo18,Stage::SpawnLevel::low}
    //,{AreaInfo18,Stage::SpawnLevel::middle}
    //,{AreaInfo18,Stage::SpawnLevel::high}
    //,{AreaInfo19,Stage::SpawnLevel::low}
    //,{AreaInfo19,Stage::SpawnLevel::middle}
    //,{AreaInfo19,Stage::SpawnLevel::high}
    //,{AreaInfo20,Stage::SpawnLevel::low}
    //,{AreaInfo20,Stage::SpawnLevel::middle}
    //,{AreaInfo20,Stage::SpawnLevel::high}
    //,{AreaInfo21,Stage::SpawnLevel::low}
    //,{AreaInfo21,Stage::SpawnLevel::middle}
    //,{AreaInfo21,Stage::SpawnLevel::high}
    //,{AreaInfo22,Stage::SpawnLevel::low}
    //,{AreaInfo22,Stage::SpawnLevel::middle}
    //,{AreaInfo22,Stage::SpawnLevel::high}
    //,{AreaInfo23,Stage::SpawnLevel::low}
    //,{AreaInfo23,Stage::SpawnLevel::middle}
    //,{AreaInfo23,Stage::SpawnLevel::high}
    //    ,{AreaInfo24,Stage::SpawnLevel::low}
    //,{AreaInfo24,Stage::SpawnLevel::middle}
    //,{AreaInfo24,Stage::SpawnLevel::high}


    // {AreaInfo25,Stage::SpawnLevel::low}
    //,{AreaInfo25,Stage::SpawnLevel::middle}
    //,{AreaInfo25,Stage::SpawnLevel::high}
    //,{AreaInfo26,Stage::SpawnLevel::low}
    //,{AreaInfo26,Stage::SpawnLevel::middle}
    //,{AreaInfo26,Stage::SpawnLevel::high}
    //,{AreaInfo27,Stage::SpawnLevel::low}
    //,{AreaInfo27,Stage::SpawnLevel::middle}
    //,{AreaInfo27,Stage::SpawnLevel::high}
    //,{AreaInfo28,Stage::SpawnLevel::low}
    //,{AreaInfo28,Stage::SpawnLevel::middle}
    //,{AreaInfo28,Stage::SpawnLevel::high}
    //,{AreaInfo29,Stage::SpawnLevel::low}
    //,{AreaInfo29,Stage::SpawnLevel::middle}
    //,{AreaInfo29,Stage::SpawnLevel::high}
    //,{AreaInfo30,Stage::SpawnLevel::low}
    //,{AreaInfo30,Stage::SpawnLevel::middle}
    //,{AreaInfo30,Stage::SpawnLevel::high}
    //,{AreaInfo31,Stage::SpawnLevel::low}
    //,{AreaInfo31,Stage::SpawnLevel::middle}
    //,{AreaInfo31,Stage::SpawnLevel::high}
    //    ,{AreaInfo32,Stage::SpawnLevel::low}
    //,{AreaInfo32,Stage::SpawnLevel::middle}
    //,{AreaInfo32,Stage::SpawnLevel::high}

    //{AreaInfo33, Stage::SpawnLevel::low}
    //, { AreaInfo33,Stage::SpawnLevel::middle }
    //    , { AreaInfo33,Stage::SpawnLevel::high }
    //    , { AreaInfo34,Stage::SpawnLevel::low }
    //    , { AreaInfo34,Stage::SpawnLevel::middle }
    //    , { AreaInfo34,Stage::SpawnLevel::high }
    //    , { AreaInfo35,Stage::SpawnLevel::low }
    //    , { AreaInfo35,Stage::SpawnLevel::middle }
    //    , { AreaInfo35,Stage::SpawnLevel::high }
    //    , { AreaInfo36,Stage::SpawnLevel::low }
    //    , { AreaInfo36,Stage::SpawnLevel::middle }
    //    , { AreaInfo36,Stage::SpawnLevel::high }
    //    , { AreaInfo37,Stage::SpawnLevel::low }
    //    , { AreaInfo37,Stage::SpawnLevel::middle }
    //    , { AreaInfo37,Stage::SpawnLevel::high }
    //    , { AreaInfo38,Stage::SpawnLevel::low }
    //    , { AreaInfo38,Stage::SpawnLevel::middle }
    //    , { AreaInfo38,Stage::SpawnLevel::high }
    //    , { AreaInfo39,Stage::SpawnLevel::low }
    //    , { AreaInfo39,Stage::SpawnLevel::middle }
    //    , { AreaInfo39,Stage::SpawnLevel::high }
    //    , { AreaInfo40,Stage::SpawnLevel::low }
    //    , { AreaInfo40,Stage::SpawnLevel::middle }
    //    , { AreaInfo40,Stage::SpawnLevel::high }

,{nullptr,0} // END
};
// ステージ2
Stage::SpawnObstacleInfo Stage::StageInfo02[] =
{
    {AreaInfo09,Stage::SpawnLevel::low}
    ,{AreaInfo09,Stage::SpawnLevel::middle}
    ,{AreaInfo09,Stage::SpawnLevel::high}
    ,{AreaInfo10,Stage::SpawnLevel::low}
    ,{AreaInfo10,Stage::SpawnLevel::middle}
    ,{AreaInfo10,Stage::SpawnLevel::high}
    ,{AreaInfo11,Stage::SpawnLevel::low}
    ,{AreaInfo11,Stage::SpawnLevel::middle}
    ,{AreaInfo11,Stage::SpawnLevel::high}
    ,{AreaInfo12,Stage::SpawnLevel::low}
    ,{AreaInfo12,Stage::SpawnLevel::middle}
    ,{AreaInfo12,Stage::SpawnLevel::high}
    ,{AreaInfo13,Stage::SpawnLevel::low}
    ,{AreaInfo13,Stage::SpawnLevel::middle}
    ,{AreaInfo13,Stage::SpawnLevel::high}
    ,{AreaInfo14,Stage::SpawnLevel::low}
    ,{AreaInfo14,Stage::SpawnLevel::middle}
    ,{AreaInfo14,Stage::SpawnLevel::high}
    ,{AreaInfo15,Stage::SpawnLevel::low}
    ,{AreaInfo15,Stage::SpawnLevel::middle}
    ,{AreaInfo15,Stage::SpawnLevel::high}
        ,{AreaInfo16,Stage::SpawnLevel::low}
    ,{AreaInfo16,Stage::SpawnLevel::middle}
    ,{AreaInfo16,Stage::SpawnLevel::high}

,{nullptr,0} // END
};
// ステージ3
Stage::SpawnObstacleInfo Stage::StageInfo03[] =
{
        {AreaInfo17,Stage::SpawnLevel::low}
    ,{AreaInfo17,Stage::SpawnLevel::middle}
    ,{AreaInfo17,Stage::SpawnLevel::high}
    ,{AreaInfo18,Stage::SpawnLevel::low}
    ,{AreaInfo18,Stage::SpawnLevel::middle}
    ,{AreaInfo18,Stage::SpawnLevel::high}
    ,{AreaInfo19,Stage::SpawnLevel::low}
    ,{AreaInfo19,Stage::SpawnLevel::middle}
    ,{AreaInfo19,Stage::SpawnLevel::high}
    ,{AreaInfo20,Stage::SpawnLevel::low}
    ,{AreaInfo20,Stage::SpawnLevel::middle}
    ,{AreaInfo20,Stage::SpawnLevel::high}
    ,{AreaInfo21,Stage::SpawnLevel::low}
    ,{AreaInfo21,Stage::SpawnLevel::middle}
    ,{AreaInfo21,Stage::SpawnLevel::high}
    ,{AreaInfo22,Stage::SpawnLevel::low}
    ,{AreaInfo22,Stage::SpawnLevel::middle}
    ,{AreaInfo22,Stage::SpawnLevel::high}
    ,{AreaInfo23,Stage::SpawnLevel::low}
    ,{AreaInfo23,Stage::SpawnLevel::middle}
    ,{AreaInfo23,Stage::SpawnLevel::high}
        ,{AreaInfo24,Stage::SpawnLevel::low}
    ,{AreaInfo24,Stage::SpawnLevel::middle}
    ,{AreaInfo24,Stage::SpawnLevel::high}

,{nullptr,0} // END
};
// ステージ4
Stage::SpawnObstacleInfo Stage::StageInfo04[] =
{
     {AreaInfo25,Stage::SpawnLevel::low}
    ,{AreaInfo25,Stage::SpawnLevel::middle}
    ,{AreaInfo25,Stage::SpawnLevel::high}
    ,{AreaInfo26,Stage::SpawnLevel::low}
    ,{AreaInfo26,Stage::SpawnLevel::middle}
    ,{AreaInfo26,Stage::SpawnLevel::high}
    ,{AreaInfo27,Stage::SpawnLevel::low}
    ,{AreaInfo27,Stage::SpawnLevel::middle}
    ,{AreaInfo27,Stage::SpawnLevel::high}
    ,{AreaInfo28,Stage::SpawnLevel::low}
    ,{AreaInfo28,Stage::SpawnLevel::middle}
    ,{AreaInfo28,Stage::SpawnLevel::high}
    ,{AreaInfo29,Stage::SpawnLevel::low}
    ,{AreaInfo29,Stage::SpawnLevel::middle}
    ,{AreaInfo29,Stage::SpawnLevel::high}
    ,{AreaInfo30,Stage::SpawnLevel::low}
    ,{AreaInfo30,Stage::SpawnLevel::middle}
    ,{AreaInfo30,Stage::SpawnLevel::high}
    ,{AreaInfo31,Stage::SpawnLevel::low}
    ,{AreaInfo31,Stage::SpawnLevel::middle}
    ,{AreaInfo31,Stage::SpawnLevel::high}
        ,{AreaInfo32,Stage::SpawnLevel::low}
    ,{AreaInfo32,Stage::SpawnLevel::middle}
    ,{AreaInfo32,Stage::SpawnLevel::high}

,{nullptr,0} // END
};
// ステージ5
Stage::SpawnObstacleInfo Stage::StageInfo05[] =
{

     {AreaInfo01,Stage::SpawnLevel::low}
    ,{AreaInfo01,Stage::SpawnLevel::middle}
    ,{AreaInfo01,Stage::SpawnLevel::high}
    ,{AreaInfo02,Stage::SpawnLevel::low}
    ,{AreaInfo02,Stage::SpawnLevel::middle}
    ,{AreaInfo02,Stage::SpawnLevel::high}
    ,{AreaInfo03,Stage::SpawnLevel::low}
    ,{AreaInfo03,Stage::SpawnLevel::middle}
    ,{AreaInfo03,Stage::SpawnLevel::high}
    ,{AreaInfo04,Stage::SpawnLevel::low}
    ,{AreaInfo04,Stage::SpawnLevel::middle}
    ,{AreaInfo04,Stage::SpawnLevel::high}
    ,{AreaInfo05,Stage::SpawnLevel::low}
    ,{AreaInfo05,Stage::SpawnLevel::middle}
    ,{AreaInfo05,Stage::SpawnLevel::high}
    ,{AreaInfo06,Stage::SpawnLevel::low}
    ,{AreaInfo06,Stage::SpawnLevel::middle}
    ,{AreaInfo06,Stage::SpawnLevel::high}
    ,{AreaInfo07,Stage::SpawnLevel::low}
    ,{AreaInfo07,Stage::SpawnLevel::middle}
    ,{AreaInfo07,Stage::SpawnLevel::high}
    ,{AreaInfo08,Stage::SpawnLevel::low}
    ,{AreaInfo08,Stage::SpawnLevel::middle}
    ,{AreaInfo08,Stage::SpawnLevel::high}
        ,{AreaInfo09,Stage::SpawnLevel::low}
    ,{AreaInfo09,Stage::SpawnLevel::middle}
    ,{AreaInfo09,Stage::SpawnLevel::high}
    ,{AreaInfo10,Stage::SpawnLevel::low}
    ,{AreaInfo10,Stage::SpawnLevel::middle}
    ,{AreaInfo10,Stage::SpawnLevel::high}
    ,{AreaInfo11,Stage::SpawnLevel::low}
    ,{AreaInfo11,Stage::SpawnLevel::middle}
    ,{AreaInfo11,Stage::SpawnLevel::high}
    ,{AreaInfo12,Stage::SpawnLevel::low}
    ,{AreaInfo12,Stage::SpawnLevel::middle}
    ,{AreaInfo12,Stage::SpawnLevel::high}
    ,{AreaInfo13,Stage::SpawnLevel::low}
    ,{AreaInfo13,Stage::SpawnLevel::middle}
    ,{AreaInfo13,Stage::SpawnLevel::high}
    ,{AreaInfo14,Stage::SpawnLevel::low}
    ,{AreaInfo14,Stage::SpawnLevel::middle}
    ,{AreaInfo14,Stage::SpawnLevel::high}
    ,{AreaInfo15,Stage::SpawnLevel::low}
    ,{AreaInfo15,Stage::SpawnLevel::middle}
    ,{AreaInfo15,Stage::SpawnLevel::high}
        ,{AreaInfo16,Stage::SpawnLevel::low}
    ,{AreaInfo16,Stage::SpawnLevel::middle}
    ,{AreaInfo16,Stage::SpawnLevel::high}
            ,{AreaInfo17,Stage::SpawnLevel::low}
    ,{AreaInfo17,Stage::SpawnLevel::middle}
    ,{AreaInfo17,Stage::SpawnLevel::high}
    ,{AreaInfo18,Stage::SpawnLevel::low}
    ,{AreaInfo18,Stage::SpawnLevel::middle}
    ,{AreaInfo18,Stage::SpawnLevel::high}
    ,{AreaInfo19,Stage::SpawnLevel::low}
    ,{AreaInfo19,Stage::SpawnLevel::middle}
    ,{AreaInfo19,Stage::SpawnLevel::high}
    ,{AreaInfo20,Stage::SpawnLevel::low}
    ,{AreaInfo20,Stage::SpawnLevel::middle}
    ,{AreaInfo20,Stage::SpawnLevel::high}
    ,{AreaInfo21,Stage::SpawnLevel::low}
    ,{AreaInfo21,Stage::SpawnLevel::middle}
    ,{AreaInfo21,Stage::SpawnLevel::high}
    ,{AreaInfo22,Stage::SpawnLevel::low}
    ,{AreaInfo22,Stage::SpawnLevel::middle}
    ,{AreaInfo22,Stage::SpawnLevel::high}
    ,{AreaInfo23,Stage::SpawnLevel::low}
    ,{AreaInfo23,Stage::SpawnLevel::middle}
    ,{AreaInfo23,Stage::SpawnLevel::high}
        ,{AreaInfo24,Stage::SpawnLevel::low}
    ,{AreaInfo24,Stage::SpawnLevel::middle}
    ,{AreaInfo24,Stage::SpawnLevel::high}
         ,{AreaInfo25,Stage::SpawnLevel::low}
    ,{AreaInfo25,Stage::SpawnLevel::middle}
    ,{AreaInfo25,Stage::SpawnLevel::high}
    ,{AreaInfo26,Stage::SpawnLevel::low}
    ,{AreaInfo26,Stage::SpawnLevel::middle}
    ,{AreaInfo26,Stage::SpawnLevel::high}
    ,{AreaInfo27,Stage::SpawnLevel::low}
    ,{AreaInfo27,Stage::SpawnLevel::middle}
    ,{AreaInfo27,Stage::SpawnLevel::high}
    ,{AreaInfo28,Stage::SpawnLevel::low}
    ,{AreaInfo28,Stage::SpawnLevel::middle}
    ,{AreaInfo28,Stage::SpawnLevel::high}
    ,{AreaInfo29,Stage::SpawnLevel::low}
    ,{AreaInfo29,Stage::SpawnLevel::middle}
    ,{AreaInfo29,Stage::SpawnLevel::high}
    ,{AreaInfo30,Stage::SpawnLevel::low}
    ,{AreaInfo30,Stage::SpawnLevel::middle}
    ,{AreaInfo30,Stage::SpawnLevel::high}
    ,{AreaInfo31,Stage::SpawnLevel::low}
    ,{AreaInfo31,Stage::SpawnLevel::middle}
    ,{AreaInfo31,Stage::SpawnLevel::high}
        ,{AreaInfo32,Stage::SpawnLevel::low}
    ,{AreaInfo32,Stage::SpawnLevel::middle}
    ,{AreaInfo32,Stage::SpawnLevel::high}
    // {AreaInfo33,Stage::SpawnLevel::low}
    //,{AreaInfo33,Stage::SpawnLevel::middle}
    //,{AreaInfo33,Stage::SpawnLevel::high}
    //,{AreaInfo34,Stage::SpawnLevel::low}
    //,{AreaInfo34,Stage::SpawnLevel::middle}
    //,{AreaInfo34,Stage::SpawnLevel::high}
    //,{AreaInfo35,Stage::SpawnLevel::low}
    //,{AreaInfo35,Stage::SpawnLevel::middle}
    //,{AreaInfo35,Stage::SpawnLevel::high}
    //,{AreaInfo36,Stage::SpawnLevel::low}
    //,{AreaInfo36,Stage::SpawnLevel::middle}
    //,{AreaInfo36,Stage::SpawnLevel::high}
    //,{AreaInfo37,Stage::SpawnLevel::low}
    //,{AreaInfo37,Stage::SpawnLevel::middle}
    //,{AreaInfo37,Stage::SpawnLevel::high}
    //,{AreaInfo38,Stage::SpawnLevel::low}
    //,{AreaInfo38,Stage::SpawnLevel::middle}
    //,{AreaInfo38,Stage::SpawnLevel::high}
    //,{AreaInfo39,Stage::SpawnLevel::low}
    //,{AreaInfo39,Stage::SpawnLevel::middle}
    //,{AreaInfo39,Stage::SpawnLevel::high}
    //,{AreaInfo40,Stage::SpawnLevel::low}
    //,{AreaInfo40,Stage::SpawnLevel::middle}
    //,{AreaInfo40,Stage::SpawnLevel::high}



,{nullptr,0} // END
};
// エンドレスモード
Stage::SpawnObstacleInfo Stage::StageInfoEndless[] =
{
 {AreaInfo01,Stage::SpawnLevel::low}
    ,{AreaInfo01,Stage::SpawnLevel::middle}
    ,{AreaInfo01,Stage::SpawnLevel::high}


    ,{AreaInfo02,Stage::SpawnLevel::low}
    ,{AreaInfo02,Stage::SpawnLevel::middle}
    ,{AreaInfo02,Stage::SpawnLevel::high}
    ,{AreaInfo03,Stage::SpawnLevel::low}
    ,{AreaInfo03,Stage::SpawnLevel::middle}
    ,{AreaInfo03,Stage::SpawnLevel::high}
    ,{AreaInfo04,Stage::SpawnLevel::low}
    ,{AreaInfo04,Stage::SpawnLevel::middle}
    ,{AreaInfo04,Stage::SpawnLevel::high}
    ,{AreaInfo05,Stage::SpawnLevel::low}
    ,{AreaInfo05,Stage::SpawnLevel::middle}
    ,{AreaInfo05,Stage::SpawnLevel::high}
    ,{AreaInfo06,Stage::SpawnLevel::low}
    ,{AreaInfo06,Stage::SpawnLevel::middle}
    ,{AreaInfo06,Stage::SpawnLevel::high}
    ,{AreaInfo07,Stage::SpawnLevel::low}
    ,{AreaInfo07,Stage::SpawnLevel::middle}
    ,{AreaInfo07,Stage::SpawnLevel::high}
    ,{AreaInfo08,Stage::SpawnLevel::low}
    ,{AreaInfo08,Stage::SpawnLevel::middle}
    ,{AreaInfo08,Stage::SpawnLevel::high}
    ,{AreaInfo09,Stage::SpawnLevel::low}
    ,{AreaInfo09,Stage::SpawnLevel::middle}
    ,{AreaInfo09,Stage::SpawnLevel::high}
    ,{AreaInfo10,Stage::SpawnLevel::low}
    ,{AreaInfo10,Stage::SpawnLevel::middle}
    ,{AreaInfo10,Stage::SpawnLevel::high}
    ,{AreaInfo11,Stage::SpawnLevel::low}
    ,{AreaInfo11,Stage::SpawnLevel::middle}
    ,{AreaInfo11,Stage::SpawnLevel::high}
    ,{AreaInfo12,Stage::SpawnLevel::low}
    ,{AreaInfo12,Stage::SpawnLevel::middle}
    ,{AreaInfo12,Stage::SpawnLevel::high}
    ,{AreaInfo13,Stage::SpawnLevel::low}
    ,{AreaInfo13,Stage::SpawnLevel::middle}
    ,{AreaInfo13,Stage::SpawnLevel::high}
    ,{AreaInfo14,Stage::SpawnLevel::low}
    ,{AreaInfo14,Stage::SpawnLevel::middle}
    ,{AreaInfo14,Stage::SpawnLevel::high}
    //            ,{AreaInfo15,Stage::SpawnLevel::low}
    //,{AreaInfo15,Stage::SpawnLevel::middle}
    //,{AreaInfo15,Stage::SpawnLevel::high}

,{nullptr,0} // END
};

// デバッグ用ステージ
Stage::SpawnObstacleInfo Stage::stageDebug[] =
{
    {AreaInfoDebug,Stage::SpawnLevel::high}
    ,{AreaInfoDebug,Stage::SpawnLevel::middle}
    ,{AreaInfoDebug,Stage::SpawnLevel::low}
    ,{nullptr,0} // END
};

// 生成するエリア情報(関数のポインタ)を返す
Stage::AreaInfo Stage::RandSpawn(Stage::SpawnObstacleInfo* data)
{
    // 各出現する確率(合計100になるようにする)
    int High = 60;       // 高 (0～High)
    int Middle = 30;     // 中 (High～High + Middle)
    int Low = 10;        // 低 (High + Middle～100)

    // 生成レベル決定
    int spawnLevel = 0;
    int n = rand() % 100;
    // Highより小さい(0～High以内)なのでレベルをhighに設定
    if (n <= High) spawnLevel = SpawnLevel::high;
    // [High+Middle]より大きい([High+Middle]～100以内)なのでレベルをlowに設定
    else if (n >= High + Middle)spawnLevel = SpawnLevel::low;
    // レベルをmiddleに設定
    else spawnLevel = SpawnLevel::middle;

    std::vector<AreaInfo> areaInfo;             // 生成レベルが同じだったエリア情報を格納するコンテナ
    for (; data->info != nullptr; ++data)
    {
        // 生成レベルが同じなら[areaInfo]に追加
        if (data->spawnRate == spawnLevel)
        {
            areaInfo.emplace_back(data->info);
        }
    }

    // ランダムなエリア情報を返す
    return areaInfo.at(rand() % areaInfo.size());
}

// コンストラクタ（nはステージの種類）
Stage::Stage(int stageNo, bool Endless)
{
    IsEndless = Endless;

    stageNo = (std::min)(stageNo, IsEndless ? StageMax : (StageMax - 1));

    //ステージモデルを読み込み
    //model = std::make_unique<Model>("Data/Model/Debug/cube.mdl");

    // 初期設定
    scale = { StageSize,0.5f ,StageSize };
    stageSideMax = StageSideMax;
    stageDepthMax = StageDepthMax;

    //if (SceneManager::Instance().IsNoneStage || stageNo < 0)
    if (stageNo < 0)
    {
        AreaInfo infoN = RandSpawn(StageNONE);
        infoN(this);
    }
    else 
    {
        AreaInfo info = RandSpawn(stageInfo[stageNo]);
        //AreaInfo info = RandSpawn(StageDebug[stageNo]);
        info(this);
    }

    //StageInfoDebug(this,ObstacleNumber);
}

Stage::~Stage()
{
    for (auto& it : obstacles)
    {
        delete it;
        it = nullptr;
    }
}

// 更新処理
void Stage::Update(float elapsedTime)
{
    // スクロール
    UpdateVelocity(elapsedTime);

    //行列更新
    UpdateTransform();

    //モデル行列更新
    if (model != nullptr)
        model->UpdateTransform(transform);
    
    //障害物更新
    for (auto& it : obstacles)
    {
        it->Update(elapsedTime);
    }

    // ステージ生成
    StageSpawn();

    // ステージ削除
    StageDelete();
}

void Stage::Initialize()
{
    //障害物更新
    for (auto& it : obstacles)
    {
        it->SetPosition({ it->GetPosition().x + position.x,it->GetPosition().y + position.y,it->GetPosition().z + position.z });
    }
}

// 描画処理
void Stage::Draw(RenderContext rc, ModelShader* shader)
{
    //ステージ描画
    if (model != nullptr)
        shader->Draw(rc, model.get());

    //障害物描画
    for (auto& it : obstacles)
    {
        it->Draw(rc, shader);
    }
}


// ステージの生成
void Stage::StageSpawn()
{
    // 奥行
    isDepthSpawn = DepthSpawn();
    // 左
    LeftSpawn();
    // 右
    RightSpawn();
}

// アイテム・障害物生成
template<typename T>
void SpawnObstacle(DirectX::XMFLOAT3 position, Stage* stage)
{
    // ステージ外の場合は生成しない
    if (
        (position.x >= Stage::StageSize) ||
        (position.x <= -Stage::StageSize) ||
        (position.z >= Stage::StageSize) ||
        (position.z <= -Stage::StageSize)
        ) return;

    Obstacle* obstacle = new T();
    DirectX::XMFLOAT3 Position =
    {
        position.x,
        position.y,
        position.z
    };
    obstacle->SetPosition(Position);
    obstacle->SetOriginPosition(stage->GetPosition());
    obstacle->SetScrollVelocity(stage->GetAddressOfVelocity());
    stage->AddObstacle(obstacle);
}

// エリア01
void Stage::AreaInfo01(Stage* stage)
{
    SpawnObstacle<Cola>({ 240.0f,0.0f,-150.0f }, stage);
    SpawnObstacle<Cola>({ 225.0f,0.0f,-150.0f }, stage);
    SpawnObstacle<Cola>({ 210.0f,0.0f,-150.0f }, stage);
    SpawnObstacle<Cola>({ 195.0f,0.0f,-150.0f }, stage);
    SpawnObstacle<Cola>({ 180.0f,0.0f,-150.0f }, stage);
    SpawnObstacle<Jellybeans_Orange>({ 130.0f,3.0f,-150.0f }, stage);
    SpawnObstacle<Jellybeans_Orange>({ 140.0f,3.0f,-150.0f }, stage);
    SpawnObstacle<Jellybeans_Orange>({ 150.0f,3.0f,-150.0f }, stage);
    SpawnObstacle<Jellybeans_Orange>({ 160.0f,3.0f,-150.0f }, stage);
    SpawnObstacle<Jellybeans_Orange>({ 170.0f,3.0f,-150.0f }, stage);
    SpawnObstacle<Cola>({ 120.0f,0.0f,-150.0f }, stage);
    SpawnObstacle<Cola>({ 105.0f,0.0f,-150.0f }, stage);
    SpawnObstacle<Cola>({ 90.0f,0.0f,-150.0f }, stage);
    SpawnObstacle<Cola>({ 75.0f,0.0f,-150.0f }, stage);
    SpawnObstacle<Cola>({ 60.0f,0.0f,-150.0f }, stage);
    SpawnObstacle<Jellybeans_Yellow>({ 50.0f,3.0f,-150.0f }, stage);
    SpawnObstacle<Jellybeans_Yellow>({ 40.0f,3.0f,-150.0f }, stage);
    SpawnObstacle<Jellybeans_Yellow>({ 30.0f,3.0f,-150.0f }, stage);
    SpawnObstacle<Jellybeans_Yellow>({ 20.0f,3.0f,-150.0f }, stage);
    SpawnObstacle<Jellybeans_Yellow>({ 10.0f,3.0f,-150.0f }, stage);
    SpawnObstacle<Cola>({ 0.0f,0.0f,-150.0f }, stage);
    SpawnObstacle<Cola>({ -15.0f,0.0f,-150.0f }, stage);
    SpawnObstacle<Cola>({ -30.0f,0.0f,-150.0f }, stage);
    SpawnObstacle<Cola>({ -45.0f,0.0f,-150.0f }, stage);
    SpawnObstacle<Cola>({ -60.0f,0.0f,-150.0f }, stage);
    SpawnObstacle<Jellybeans_Pink>({ -70.0f,3.0f,-150.0f }, stage);
    SpawnObstacle<Jellybeans_Pink>({ -80.0f,3.0f,-150.0f }, stage);
    SpawnObstacle<Jellybeans_Pink>({ -90.0f,3.0f,-150.0f }, stage);
    SpawnObstacle<Jellybeans_Pink>({ -100.0f,3.0f,-150.0f }, stage);
    SpawnObstacle<Jellybeans_Pink>({ -110.0f,3.0f,-150.0f }, stage);
    SpawnObstacle<Cola>({ -120.0f,0.0f,-150.0f }, stage);
    SpawnObstacle<Cola>({ -135.0f,0.0f,-150.0f }, stage);
    SpawnObstacle<Cola>({ -150.0f,0.0f,-150.0f }, stage);
    SpawnObstacle<Cola>({ -165.0f,0.0f,-150.0f }, stage);
    SpawnObstacle<Cola>({ -180.0f,0.0f,-150.0f }, stage);

    SpawnObstacle<Jellybeans_Orange>({ 240.0f,3.0f,150.0f }, stage);
    SpawnObstacle<Jellybeans_Orange>({ 225.0f,3.0f,150.0f }, stage);
    SpawnObstacle<Jellybeans_Orange>({ 210.0f,3.0f,150.0f }, stage);
    SpawnObstacle<Jellybeans_Orange>({ 195.0f,3.0f,150.0f }, stage);
    SpawnObstacle<Jellybeans_Orange>({ 180.0f,3.0f,150.0f }, stage);
    SpawnObstacle<Grape_can>({ 130.0f,0.0f,150.0f }, stage);
    SpawnObstacle<Grape_can>({ 140.0f,0.0f,150.0f }, stage);
    SpawnObstacle<Grape_can>({ 150.0f,0.0f,150.0f }, stage);
    SpawnObstacle<Grape_can>({ 160.0f,0.0f,150.0f }, stage);
    SpawnObstacle<Grape_can>({ 170.0f,0.0f,150.0f }, stage);
    SpawnObstacle<Jellybeans_Yellow>({ 120.0f,3.0f,150.0f }, stage);
    SpawnObstacle<Jellybeans_Yellow>({ 105.0f,3.0f,150.0f }, stage);
    SpawnObstacle<Jellybeans_Yellow>({ 90.0f,3.0f,150.0f }, stage);
    SpawnObstacle<Jellybeans_Yellow>({ 75.0f,3.0f,150.0f }, stage);
    SpawnObstacle<Jellybeans_Yellow>({ 60.0f,3.0f,150.0f }, stage);
    SpawnObstacle<Grape_can>({ 50.0f,0.0f,150.0f }, stage);
    SpawnObstacle<Grape_can>({ 40.0f,0.0f,150.0f }, stage);
    SpawnObstacle<Grape_can>({ 30.0f,0.0f,150.0f }, stage);
    SpawnObstacle<Grape_can>({ 20.0f,0.0f,150.0f }, stage);
    SpawnObstacle<Grape_can>({ 10.0f,0.0f,150.0f }, stage);
    SpawnObstacle<Jellybeans_Pink>({ 0.0f,3.0f,150.0f }, stage);
    SpawnObstacle<Jellybeans_Pink>({ -15.0f,3.0f,150.0f }, stage);
    SpawnObstacle<Jellybeans_Pink>({ -30.0f,3.0f,150.0f }, stage);
    SpawnObstacle<Jellybeans_Pink>({ -45.0f,3.0f,150.0f }, stage);
    SpawnObstacle<Jellybeans_Pink>({ -60.0f,3.0f,150.0f }, stage);
    SpawnObstacle<Grape_can>({ -70.0f,0.0f,150.0f }, stage);
    SpawnObstacle<Grape_can>({ -80.0f,0.0f,150.0f }, stage);
    SpawnObstacle<Grape_can>({ -90.0f,0.0f,150.0f }, stage);
    SpawnObstacle<Grape_can>({ -100.0f,0.0f,150.0f }, stage);
    SpawnObstacle<Grape_can>({ -110.0f,0.0f,150.0f }, stage);
    SpawnObstacle<Jellybeans_Green>({ -120.0f,3.0f,150.0f }, stage);
    SpawnObstacle<Jellybeans_Green>({ -135.0f,3.0f,150.0f }, stage);
    SpawnObstacle<Jellybeans_Green>({ -150.0f,3.0f,150.0f }, stage);
    SpawnObstacle<Jellybeans_Green>({ -165.0f,3.0f,150.0f }, stage);
    SpawnObstacle<Jellybeans_Green>({ -180.0f,3.0f,-150.0f }, stage);
}
// エリア02
void Stage::AreaInfo02(Stage* stage)
{
    SpawnObstacle<Pokey>({ -150.0f,0.0f,-150.0f }, stage);
    SpawnObstacle<Pokey>({ -125.0f,0.0f,-150.0f }, stage);
    SpawnObstacle<Pokey>({ -100.0f,0.0f,-150.0f }, stage);
    SpawnObstacle<Marshmallow_Blue>({ -80.0f,3.0f,-150.0f }, stage);
    SpawnObstacle<Marshmallow_Blue>({ -60.0f,3.0f,-150.0f }, stage);
    SpawnObstacle<Marshmallow_Blue>({ -40.0f,3.0f,-150.0f }, stage);
    SpawnObstacle<Marshmallow_Blue>({ -20.0f,3.0f,-150.0f }, stage);
    SpawnObstacle<Pokey>({ 0.0f,0.0f,-150.0f }, stage);
    SpawnObstacle<Pokey>({ 25.0f,0.0f,-150.0f }, stage);
    SpawnObstacle<Pokey>({ 50.0f,0.0f,-150.0f }, stage);
    SpawnObstacle<Marshmallow_Blue>({ 70.0f,3.0f,-150.0f }, stage);
    SpawnObstacle<Marshmallow_Blue>({ 90.0f,3.0f,-150.0f }, stage);
    SpawnObstacle<Marshmallow_Blue>({ 110.0f,3.0f,-150.0f }, stage);
    SpawnObstacle<Marshmallow_Blue>({ 130.0f,3.0f,-150.0f }, stage);
    SpawnObstacle<Pokey>({ 150.0f,0.0f,-150.0f }, stage);
    SpawnObstacle<Pokey>({ 175.0f,0.0f,-150.0f }, stage);
    SpawnObstacle<Pokey>({ 200.0f,0.0f,-150.0f }, stage);
    SpawnObstacle<Prits>({ -80.0f,0.0f,150.0f }, stage);
    SpawnObstacle<Prits>({ -50.0f,0.0f,150.0f }, stage);
    SpawnObstacle<Prits>({ -20.0f,0.0f,150.0f }, stage);
    SpawnObstacle<Marshmallow_Pink>({ 0.0f,3.0f,150.0f }, stage);
    SpawnObstacle<Marshmallow_Pink>({ 10.0f,3.0f,150.0f }, stage);
    SpawnObstacle<Marshmallow_Pink>({ 20.0f,3.0f,150.0f }, stage);
    SpawnObstacle<Marshmallow_Pink>({ 30.0f,3.0f,150.0f }, stage);
    SpawnObstacle<Marshmallow_Pink>({ 40.0f,3.0f,150.0f }, stage);
    SpawnObstacle<Marshmallow_Pink>({ 50.0f,3.0f,150.0f }, stage);
    SpawnObstacle<Prits>({ 70.0f,0.0f,150.0f }, stage);
    SpawnObstacle<Prits>({ 100.0f,0.0f,150.0f }, stage);
    SpawnObstacle<Prits>({ 130.0f,0.0f,150.0f }, stage);
}
// エリア03
void Stage::AreaInfo03(Stage* stage)
{
    SpawnObstacle<Orange_can>({ -240.0f,0.0f,-150.0f }, stage);
    SpawnObstacle<Orange_can>({ -225.0f,0.0f,-150.0f }, stage);
    SpawnObstacle<Orange_can>({ -210.0f,0.0f,-150.0f }, stage);
    SpawnObstacle<Orange_can>({ -195.0f,0.0f,-150.0f }, stage);
    SpawnObstacle<Orange_can>({ -180.0f,0.0f,-150.0f }, stage);
    SpawnObstacle<Orange_can>({ -165.0f,0.0f,-150.0f }, stage);

    SpawnObstacle<Orange_can>({ -150.0f,0.0f,-50.0f }, stage);
    SpawnObstacle<Orange_can>({ -135.0f,0.0f,-50.0f }, stage);
    SpawnObstacle<Orange_can>({ -120.0f,0.0f,-50.0f }, stage);
    SpawnObstacle<Orange_can>({ -105.0f,0.0f,-50.0f }, stage);
    SpawnObstacle<Orange_can>({ -90.0f,0.0f,-50.0f }, stage);
    SpawnObstacle<Orange_can>({ -75.0f,0.0f,-50.0f }, stage);
    SpawnObstacle<Jellybeans_Orange>({ -20.0f,3.0f,-50.0f }, stage);
    SpawnObstacle<Jellybeans_Orange>({ -30.0f,3.0f,-50.0f }, stage);
    SpawnObstacle<Jellybeans_Orange>({ -40.0f,3.0f,-50.0f }, stage);
    SpawnObstacle<Jellybeans_Orange>({ -50.0f,3.0f,-50.0f }, stage);
    SpawnObstacle<Jellybeans_Orange>({ -60.0f,3.0f,-50.0f }, stage);
    SpawnObstacle<Jellybeans_Orange>({ -10.0f,3.0f,-50.0f }, stage);
    SpawnObstacle<Jellybeans_Orange>({ 0.0f,3.0f,-50.0f }, stage);
    SpawnObstacle<Jellybeans_Orange>({ 10.0f,3.0f,-50.0f }, stage);
    SpawnObstacle<Jellybeans_Orange>({ 20.0f,3.0f,-50.0f }, stage);
    SpawnObstacle<Jellybeans_Orange>({ 30.0f,3.0f,-50.0f }, stage);
    SpawnObstacle<Jellybeans_Orange>({ 40.0f,3.0f,-50.0f }, stage);
    SpawnObstacle<Jellybeans_Orange>({ 50.0f,3.0f,-50.0f }, stage);
    SpawnObstacle<Jellybeans_Orange>({ 60.0f,3.0f,-50.0f }, stage);

    SpawnObstacle<Orange_can>({ 150.0f,0.0f,-50.0f }, stage);
    SpawnObstacle<Orange_can>({ 135.0f,0.0f,-50.0f }, stage);
    SpawnObstacle<Orange_can>({ 120.0f,0.0f,-50.0f }, stage);
    SpawnObstacle<Orange_can>({ 105.0f,0.0f,-50.0f }, stage);
    SpawnObstacle<Orange_can>({ 90.0f,0.0f,-50.0f }, stage);
    SpawnObstacle<Orange_can>({ 75.0f,0.0f,-50.0f }, stage);


    SpawnObstacle<Orange_can>({ 240.0f,0.0f,-150.0f }, stage);
    SpawnObstacle<Orange_can>({ 225.0f,0.0f,-150.0f }, stage);
    SpawnObstacle<Orange_can>({ 210.0f,0.0f,-150.0f }, stage);
    SpawnObstacle<Orange_can>({ 195.0f,0.0f,-150.0f }, stage);
    SpawnObstacle<Orange_can>({ 180.0f,0.0f,-150.0f }, stage);
    SpawnObstacle<Orange_can>({ 165.0f,0.0f,-150.0f }, stage);

    SpawnObstacle<Orange_can>({ 60.0f,0.0f,150.0f }, stage);
    SpawnObstacle<Orange_can>({ 45.0f,0.0f,150.0f }, stage);
    SpawnObstacle<Orange_can>({ 30.0f,0.0f,150.0f }, stage);
    SpawnObstacle<Orange_can>({ 15.0f,0.0f,150.0f }, stage);
    SpawnObstacle<Orange_can>({ 0.0f,0.0f,150.0f }, stage);
    SpawnObstacle<Orange_can>({ -60.0f,0.0f,150.0f }, stage);
    SpawnObstacle<Orange_can>({ -45.0f,0.0f,150.0f }, stage);
    SpawnObstacle<Orange_can>({ -30.0f,0.0f,150.0f }, stage);
    SpawnObstacle<Orange_can>({ -15.0f,0.0f,150.0f }, stage);
}
// エリア04
void Stage::AreaInfo04(Stage* stage)
{
    SpawnObstacle<Cola>({ 0.0f,0.0f,-100.0f }, stage);
    SpawnObstacle<Cola>({ 15.0f,0.0f,-100.0f }, stage);
    SpawnObstacle<Cola>({ 30.0f,0.0f,-100.0f }, stage);
    SpawnObstacle<Cola>({ 0.0f,0.0f,-115.0f }, stage);
    SpawnObstacle<Cola>({ 0.0f,0.0f,-130.0f }, stage);
    SpawnObstacle<Cola>({ 15.0f,0.0f,-115.0f }, stage);
    SpawnObstacle<Cola>({ 30.0f,0.0f,-115.0f }, stage);
    SpawnObstacle<Cola>({ 15.0f,0.0f,-130.0f }, stage);
    SpawnObstacle<Cola>({ 30.0f,0.0f,-130.0f }, stage);
    SpawnObstacle<Cola>({ 7.0f,18.0f,-107.0f }, stage);
    SpawnObstacle<Cola>({ 23.0f,18.0f,-107.0f }, stage);
    SpawnObstacle<Cola>({ 7.0f,18.0f,-123.0f }, stage);
    SpawnObstacle<Cola>({ 23.0f,18.0f,-123.0f }, stage);
    SpawnObstacle<Cola>({ 15.0f,36.0f,-115.0f }, stage);

    SpawnObstacle<Cola>({ 100.0f,0.0f,-100.0f }, stage);
    SpawnObstacle<Cola>({ 115.0f,0.0f,-100.0f }, stage);
    SpawnObstacle<Cola>({ 130.0f,0.0f,-100.0f }, stage);
    SpawnObstacle<Cola>({ 100.0f,0.0f,-115.0f }, stage);
    SpawnObstacle<Cola>({ 100.0f,0.0f,-130.0f }, stage);
    SpawnObstacle<Cola>({ 115.0f,0.0f,-115.0f }, stage);
    SpawnObstacle<Cola>({ 130.0f,0.0f,-115.0f }, stage);
    SpawnObstacle<Cola>({ 115.0f,0.0f,-130.0f }, stage);
    SpawnObstacle<Cola>({ 130.0f,0.0f,-130.0f }, stage);
    SpawnObstacle<Cola>({ 107.0f,18.0f,-107.0f }, stage);
    SpawnObstacle<Cola>({ 123.0f,18.0f,-107.0f }, stage);
    SpawnObstacle<Cola>({ 107.0f,18.0f,-123.0f }, stage);
    SpawnObstacle<Cola>({ 123.0f,18.0f,-123.0f }, stage);
    SpawnObstacle<Cola>({ 115.0f,36.0f,-115.0f }, stage);

    SpawnObstacle<Cola>({ 150.0f,0.0f,100.0f }, stage);
    SpawnObstacle<Cola>({ 200.0f,0.0f,150.0f }, stage);
    SpawnObstacle<Cola>({ -150.0f,0.0f,100.0f }, stage);
    SpawnObstacle<Cola>({ -200.0f,0.0f,150.0f }, stage);
    SpawnObstacle<Cola>({ 150.0f,0.0f,-100.0f }, stage);
    SpawnObstacle<Cola>({ 200.0f,0.0f,-150.0f }, stage);
    SpawnObstacle<Cola>({ -150.0f,0.0f,-100.0f }, stage);
    SpawnObstacle<Cola>({ -200.0f,0.0f,-150.0f }, stage);
    SpawnObstacle<Cola>({ 90.0f,0.0f,-90.0f }, stage);
    SpawnObstacle<Cola>({ 40.0f,0.0f,-90.0f }, stage);
    SpawnObstacle<Cola>({ 85.0f,0.0f,-70.0f }, stage);
    SpawnObstacle<Cola>({ 45.0f,0.0f,-70.0f }, stage);
    SpawnObstacle<Cola>({ 80.0f,0.0f,-50.0f }, stage);
    SpawnObstacle<Cola>({ 50.0f,0.0f,-50.0f }, stage);

    SpawnObstacle<Cola>({ 80.0f,0.0f,-220.0f }, stage);
    SpawnObstacle<Cola>({ 50.0f,0.0f,-220.0f }, stage);
    SpawnObstacle<Cola>({ 80.0f,18.0f,-220.0f }, stage);
    SpawnObstacle<Cola>({ 50.0f,18.0f,-220.0f }, stage);
    SpawnObstacle<Cola>({ 100.0f,0.0f,220.0f }, stage);
    SpawnObstacle<Cola>({ 30.0f,0.0f,220.0f }, stage);
    SpawnObstacle<Cola>({ 10.0f,0.0f,200.0f }, stage);
    SpawnObstacle<Cola>({ 120.0f,0.0f,200.0f }, stage);
    SpawnObstacle<Cola>({ -90.0f,0.0f,100.0f }, stage);
    SpawnObstacle<Cola>({ 220.0f,0.0f,100.0f }, stage);
    SpawnObstacle<Cola>({ -20.0f,0.0f,50.0f }, stage);
    SpawnObstacle<Cola>({ 150.0f,0.0f,50.0f }, stage);
    SpawnObstacle<Macaron_Maccha>({ 65.0f,3.0f,-20.0f }, stage);
}
// エリア05
void Stage::AreaInfo05(Stage* stage)
{
    SpawnObstacle<Grape_can>({ 0.0f,0.0f,0.0f }, stage);
    SpawnObstacle<Grape_can>({ 50.0f,0.0f,50.0f }, stage);
    SpawnObstacle<Grape_can>({ -50.0f,0.0f,-50.0f }, stage);
    SpawnObstacle<Grape_can>({ 100.0f,0.0f,150.0f }, stage);
    SpawnObstacle<Grape_can>({ 50.0f,0.0f,100.0f }, stage);
    SpawnObstacle<Grape_can>({ -150.0f,0.0f,-50.0f }, stage);
    SpawnObstacle<Grape_can>({ 200.0f,0.0f,150.0f }, stage);
    SpawnObstacle<Grape_can>({ 230.0f,0.0f,100.0f }, stage);
    SpawnObstacle<Grape_can>({ -230.0f,0.0f,-50.0f }, stage);
    SpawnObstacle<Grape_can>({ -100.0f,0.0f,200.0f }, stage);
    SpawnObstacle<Grape_can>({ -200.0f,0.0f,-200.0f }, stage);
    SpawnObstacle<Grape_can>({ -170.0f,0.0f,-70.0f }, stage);
    SpawnObstacle<Grape_can>({ 170.0f,0.0f,70.0f }, stage);
    SpawnObstacle<Grape_can>({ 170.0f,0.0f,-200.0f }, stage);
    SpawnObstacle<Grape_can>({ 120.0f,0.0f,20.0f }, stage);
    SpawnObstacle<Grape_can>({ 120.0f,0.0f,-20.0f }, stage);
    SpawnObstacle<Grape_can>({ -90.0f,0.0f,-140.0f }, stage);
    SpawnObstacle<Grape_can>({ 25.0f,0.0f,180.0f }, stage);
    SpawnObstacle<Grape_can>({ -25.0f,0.0f,-140.0f }, stage);
    SpawnObstacle<Grape_can>({ 25.0f,0.0f,-140.0f }, stage);
    SpawnObstacle<Grape_can>({ 240.0f,0.0f,90.0f }, stage);
    SpawnObstacle<Grape_can>({ -240.0f,0.0f,-140.0f }, stage);
    SpawnObstacle<Grape_can>({ -50.0f,0.0f,100.0f }, stage);
    SpawnObstacle<Grape_can>({ -20.0f,0.0f,150.0f }, stage);
    SpawnObstacle<Grape_can>({ 70.0f,0.0f,150.0f }, stage);
    SpawnObstacle<Marshmallow_Blue>({ 100.0f,3.0f,-150.0f }, stage);
    SpawnObstacle<Marshmallow_Blue>({ 230.0f,3.0f,130.0f }, stage);
    SpawnObstacle<Marshmallow_Blue>({ 50.0f,3.0f,240.0f }, stage);
    SpawnObstacle<Marshmallow_Blue>({ 150.0f,3.0f,10.0f }, stage);
    SpawnObstacle<Marshmallow_Pink>({ 70.0f,3.0f,-45.0f }, stage);
    SpawnObstacle<Marshmallow_Pink>({ -180.0f,3.0f,-210.0f }, stage);
    SpawnObstacle<Marshmallow_Pink>({ -90.0f,3.0f,50.0f }, stage);
    SpawnObstacle<Marshmallow_Pink>({ -30.0f,3.0f,150.0f }, stage);

}
// エリア06
void Stage::AreaInfo06(Stage* stage)
{
    SpawnObstacle<Orange_gum>({ -50.0f,0.0f,100.0f }, stage);
    SpawnObstacle<Orange_gum>({ 50.0f,0.0f,100.0f }, stage);
    SpawnObstacle<Orange_gum>({ -150.0f,0.0f,120.0f }, stage);
    SpawnObstacle<Orange_gum>({ 150.0f,0.0f,120.0f }, stage);
    SpawnObstacle<Orange_gum>({ -200.0f,0.0f,180.0f }, stage);
    SpawnObstacle<Orange_gum>({ 200.0f,0.0f,180.0f }, stage);
    SpawnObstacle<Orange_gum>({ -100.0f,0.0f,-180.0f }, stage);
    SpawnObstacle<Orange_gum>({ 100.0f,0.0f,-180.0f }, stage);
    SpawnObstacle<Orange_can>({ 70.0f,0.0f,-100.0f }, stage);
    SpawnObstacle<Orange_can>({ -70.0f,0.0f,-100.0f }, stage);
    SpawnObstacle<Orange_can>({ 220.0f,0.0f,-50.0f }, stage);
    SpawnObstacle<Orange_can>({ -220.0f,0.0f,-50.0f }, stage);
    SpawnObstacle<Orange_can>({ 180.0f,0.0f,-150.0f }, stage);
    SpawnObstacle<Orange_can>({ -180.0f,0.0f,-150.0f }, stage);
    SpawnObstacle<Orange_can>({ 30.0f,0.0f,0.0f }, stage);
    SpawnObstacle<Orange_can>({ -30.0f,0.0f,0.0f }, stage);
    SpawnObstacle<Macaron_Maccha>({ 40.0f,3.0f,0.0f }, stage);
    SpawnObstacle<Macaron_Maccha>({ 240.0f,3.0f,0.0f }, stage);
    SpawnObstacle<Macaron_Maccha>({ -120.0f,3.0f,240.0f }, stage);



}
// エリア07
void Stage::AreaInfo07(Stage* stage)
{
    SpawnObstacle<Cola>({ -240.0f,0.0f,0.0f }, stage);
    SpawnObstacle<Cola>({ -228.0f,0.0f,0.0f }, stage);
    SpawnObstacle<Cola>({ -216.0f,0.0f,0.0f }, stage);
    SpawnObstacle<Cola>({ -204.0f,0.0f,0.0f }, stage);
    SpawnObstacle<Cola>({ -192.0f,0.0f,0.0f }, stage);
    SpawnObstacle<Cola>({ -180.0f,0.0f,0.0f }, stage);
    SpawnObstacle<Cola>({ -240.0f,18.0f,0.0f }, stage);
    SpawnObstacle<Cola>({ -228.0f,18.0f,0.0f }, stage);
    SpawnObstacle<Cola>({ -216.0f,18.0f,0.0f }, stage);
    SpawnObstacle<Cola>({ -204.0f,18.0f,0.0f }, stage);
    SpawnObstacle<Cola>({ -192.0f,18.0f,0.0f }, stage);
    SpawnObstacle<Cola>({ -180.0f,18.0f,0.0f }, stage);

    SpawnObstacle<Cola>({ -180.0f,0.0f,-150.0f }, stage);
    SpawnObstacle<Cola>({ -168.0f,0.0f,-150.0f }, stage);
    SpawnObstacle<Orange_can>({ -156.0f,0.0f,-150.0f }, stage);
    SpawnObstacle<Orange_can>({ -144.0f,0.0f,-150.0f }, stage);

    SpawnObstacle<Jellybeans_Green>({ -120.0f,3.0f,-150.0f }, stage);
    SpawnObstacle<Jellybeans_Green>({ -162.0f,3.0f,0.0f }, stage);
    SpawnObstacle<Orange_can>({ -144.0f,0.0f,0.0f }, stage);
    SpawnObstacle<Orange_can>({ -132.0f,0.0f,0.0f }, stage);
    SpawnObstacle<Orange_can>({ -120.0f,0.0f,0.0f }, stage);
    SpawnObstacle<Orange_can>({ -108.0f,0.0f,0.0f }, stage);
    SpawnObstacle<Orange_can>({ -96.0f,0.0f,0.0f }, stage);
    SpawnObstacle<Orange_can>({ -84.0f,0.0f,0.0f }, stage);

    SpawnObstacle<Orange_can>({ -144.0f,18.0f,0.0f }, stage);
    SpawnObstacle<Orange_can>({ -132.0f,18.0f,0.0f }, stage);
    SpawnObstacle<Orange_can>({ -120.0f,18.0f,0.0f }, stage);
    SpawnObstacle<Orange_can>({ -108.0f,18.0f,0.0f }, stage);
    SpawnObstacle<Orange_can>({ -96.0f,18.0f,0.0f }, stage);
    SpawnObstacle<Orange_can>({ -84.0f,18.0f,0.0f }, stage);
    SpawnObstacle<Jellybeans_Green>({ -20.0f,3.0f,-150.0f }, stage);
    SpawnObstacle<Jellybeans_Green>({ -66.0f,3.0f,0.0f }, stage);
    SpawnObstacle<Orange_can>({ -84.0f,0.0f,-150.0f }, stage);
    SpawnObstacle<Orange_can>({ -72.0f,0.0f,-150.0f }, stage);
    SpawnObstacle<Grape_can>({ -62.0f,0.0f,-150.0f }, stage);
    SpawnObstacle<Grape_can>({ -50.0f,0.0f,-150.0f }, stage);

    SpawnObstacle<Grape_can>({ -50.0f,18.0f,0.0f }, stage);
    SpawnObstacle<Grape_can>({ -38.0f,18.0f,0.0f }, stage);
    SpawnObstacle<Grape_can>({ -26.0f,18.0f,0.0f }, stage);
    SpawnObstacle<Grape_can>({ -14.0f,18.0f,0.0f }, stage);
    SpawnObstacle<Grape_can>({ -2.0f,18.0f,0.0f }, stage);
    SpawnObstacle<Grape_can>({ 10.0f,18.0f,0.0f }, stage);
    SpawnObstacle<Grape_can>({ -50.0f,0.0f,0.0f }, stage);
    SpawnObstacle<Grape_can>({ -38.0f,0.0f,0.0f }, stage);
    SpawnObstacle<Grape_can>({ -26.0f,0.0f,0.0f }, stage);
    SpawnObstacle<Grape_can>({ -14.0f,0.0f,0.0f }, stage);
    SpawnObstacle<Grape_can>({ -2.0f,0.0f,0.0f }, stage);
    SpawnObstacle<Grape_can>({ 10.0f,0.0f,0.0f }, stage);

    SpawnObstacle<Grape_can>({ 12.0f,0.0f,-150.0f }, stage);
    SpawnObstacle<Grape_can>({ 24.0f,0.0f,-150.0f }, stage);
    SpawnObstacle<Cola>({ 36.0f,0.0f,-150.0f }, stage);
    SpawnObstacle<Cola>({ 48.0f,0.0f,-150.0f }, stage);
    SpawnObstacle<Jellybeans_Green>({ 70.0f,3.0f,-150.0f }, stage);
    SpawnObstacle<Jellybeans_Green>({ 28.0f,3.0f,0.0f }, stage);
    SpawnObstacle<Cola>({ 46.0f,0.0f,0.0f }, stage);
    SpawnObstacle<Cola>({ 58.0f,0.0f,0.0f }, stage);
    SpawnObstacle<Cola>({ 70.0f,0.0f,0.0f }, stage);
    SpawnObstacle<Cola>({ 82.0f,0.0f,0.0f }, stage);
    SpawnObstacle<Cola>({ 94.0f,0.0f,0.0f }, stage);
    SpawnObstacle<Cola>({ 106.0f,0.0f,0.0f }, stage);

    SpawnObstacle<Cola>({ 46.0f,18.0f,0.0f }, stage);
    SpawnObstacle<Cola>({ 58.0f,18.0f,0.0f }, stage);
    SpawnObstacle<Cola>({ 70.0f,18.0f,0.0f }, stage);
    SpawnObstacle<Cola>({ 82.0f,18.0f,0.0f }, stage);
    SpawnObstacle<Cola>({ 94.0f,18.0f,0.0f }, stage);
    SpawnObstacle<Cola>({ 106.0f,18.0f,0.0f }, stage);

    SpawnObstacle<Cola>({ 96.0f,0.0f,-150.0f }, stage);
    SpawnObstacle<Cola>({ 106.0f,0.0f,-150.0f }, stage);
    SpawnObstacle<Orange_can>({ 118.0f,0.0f,-150.0f }, stage);
    SpawnObstacle<Orange_can>({ 130.0f,0.0f,-150.0f }, stage);
    SpawnObstacle<Jellybeans_Green>({ 150.0f,3.0f,-150.0f }, stage);
    SpawnObstacle<Jellybeans_Green>({ 126.0f,3.0f,0.0f }, stage);
    SpawnObstacle<Orange_can>({ 142.0f,0.0f,0.0f }, stage);
    SpawnObstacle<Orange_can>({ 154.0f,0.0f,0.0f }, stage);
    SpawnObstacle<Orange_can>({ 166.0f,0.0f,0.0f }, stage);
    SpawnObstacle<Orange_can>({ 178.0f,0.0f,0.0f }, stage);
    SpawnObstacle<Orange_can>({ 190.0f,0.0f,0.0f }, stage);
    SpawnObstacle<Orange_can>({ 202.0f,0.0f,0.0f }, stage);

    SpawnObstacle<Orange_can>({ 142.0f,18.0f,0.0f }, stage);
    SpawnObstacle<Orange_can>({ 154.0f,18.0f,0.0f }, stage);
    SpawnObstacle<Orange_can>({ 166.0f,18.0f,0.0f }, stage);
    SpawnObstacle<Orange_can>({ 178.0f,18.0f,0.0f }, stage);
    SpawnObstacle<Orange_can>({ 190.0f,18.0f,0.0f }, stage);
    SpawnObstacle<Orange_can>({ 202.0f,18.0f,0.0f }, stage);
}
// エリア08
void Stage::AreaInfo08(Stage* stage)
{

    SpawnObstacle<Jellybeans_Green>({ 60.0f,3.0f,240.0f }, stage);
    SpawnObstacle<Jellybeans_Green>({ 160.0f,3.0f,240.0f }, stage);
    SpawnObstacle<Jellybeans_Green>({ 220.0f,3.0f,240.0f }, stage);

    SpawnObstacle<Jellybeans_Green>({ -220.0f,3.0f,240.0f }, stage);
    SpawnObstacle<Jellybeans_Green>({ -160.0f,3.0f,240.0f }, stage);
    SpawnObstacle<Jellybeans_Green>({ -60.0f,3.0f,240.0f }, stage);

    SpawnObstacle<Jellybeans_Orange>({ 215.0f,3.0f,180.0f }, stage);
    SpawnObstacle<Jellybeans_Orange>({ 100.0f,3.0f,180.0f }, stage);
    SpawnObstacle<Jellybeans_Orange>({ 50.0f,3.0f,180.0f }, stage);
    SpawnObstacle<Jellybeans_Orange>({ -50.0f,3.0f,180.0f }, stage);
    SpawnObstacle<Jellybeans_Orange>({ -100.0f,3.0f,180.0f }, stage);
    SpawnObstacle<Jellybeans_Orange>({ -215.0f,3.0f,180.0f }, stage);
    SpawnObstacle<Pokey>({ 200.0f,0.0f,150.0f }, stage);
    SpawnObstacle<Pokey>({ -200.0f,0.0f,150.0f }, stage);
    SpawnObstacle<Pokey>({ 80.0f,0.0f,150.0f }, stage);
    SpawnObstacle<Pokey>({ -80.0f,0.0f,150.0f }, stage);
    SpawnObstacle<Pokey>({ 30.0f,0.0f,150.0f }, stage);
    SpawnObstacle<Pokey>({ -30.0f,0.0f,150.0f }, stage);
    SpawnObstacle<Jellybeans_Green>({ -60.0f,3.0f,70.0f }, stage);
    SpawnObstacle<Jellybeans_Green>({ 60.0f,3.0f,70.0f }, stage);
    SpawnObstacle<Pokey>({ 235.0f,0.0f,20.0f }, stage);
    SpawnObstacle<Pokey>({ -235.0f,0.0f,20.0f }, stage);
    SpawnObstacle<Pokey>({ 130.0f,0.0f,20.0f }, stage);
    SpawnObstacle<Pokey>({ -130.0f,0.0f,20.0f }, stage);
    SpawnObstacle<Pokey>({ 50.0f,0.0f,20.0f }, stage);
    SpawnObstacle<Pokey>({ -50.0f,0.0f,20.0f }, stage);
    SpawnObstacle<Jellybeans_Yellow>({ 0.0f,3.0f,-20.0f }, stage);
    SpawnObstacle<Jellybeans_Yellow>({ 90.0f,3.0f,-20.0f }, stage);
    SpawnObstacle<Jellybeans_Yellow>({ 90.0f,3.0f,-20.0f }, stage);
    SpawnObstacle<Pokey>({ 200.0f,0.0f,-120.0f }, stage);
    SpawnObstacle<Pokey>({ -200.0f,0.0f,120.0f }, stage);
    SpawnObstacle<Pokey>({ 150.0f,0.0f,-120.0f }, stage);
    SpawnObstacle<Pokey>({ -150.0f,0.0f,-120.0f }, stage);
    SpawnObstacle<Pokey>({ 240.0f,0.0f,-235.0f }, stage);
    SpawnObstacle<Pokey>({ -240.0f,0.0f,-235.0f }, stage);
    SpawnObstacle<Pokey>({ 20.0f,0.0f,-235.0f }, stage);
    SpawnObstacle<Pokey>({ -20.0f,0.0f,-235.0f }, stage);
}
// エリア09
void Stage::AreaInfo09(Stage* stage)
{
    SpawnObstacle<Pokey>({ -150.0f,0.0f,-200.0f }, stage);
    SpawnObstacle<Pokey>({ -125.0f,0.0f,-200.0f }, stage);
    SpawnObstacle<Pokey>({ -100.0f,0.0f,-200.0f }, stage);
    SpawnObstacle<Pokey>({ -75.0f,0.0f,-200.0f }, stage);
    SpawnObstacle<Pokey>({ 0.0f,0.0f,-200.0f }, stage);
    SpawnObstacle<Candy_gate>({ -175.0f,0.0f,-200.0f }, stage);
    SpawnObstacle<Candy_gate>({ -200.0f,0.0f,-200.0f }, stage);
    SpawnObstacle<Candy_gate>({ -225.0f,0.0f,-200.0f }, stage);
    SpawnObstacle<Candy_gate>({ -250.0f,0.0f,-200.0f }, stage);
    SpawnObstacle<Marshmallow_Blue>({ -175.0f,3.0f,-150.0f }, stage);
    SpawnObstacle<Marshmallow_Blue>({ -175.0f,3.0f,-100.0f }, stage);
    SpawnObstacle<Marshmallow_Blue>({ -175.0f,3.0f,-50.0f }, stage);
    SpawnObstacle<Marshmallow_Blue>({ -200.0f,3.0f,-150.0f }, stage);
    SpawnObstacle<Marshmallow_Blue>({ -200.0f,3.0f,-100.0f }, stage);
    SpawnObstacle<Marshmallow_Blue>({ -200.0f,3.0f,-50.0f }, stage);
    SpawnObstacle<Marshmallow_Blue>({ -225.0f,3.0f,-150.0f }, stage);
    SpawnObstacle<Marshmallow_Blue>({ -225.0f,3.0f,-100.0f }, stage);
    SpawnObstacle<Marshmallow_Blue>({ -225.0f,3.0f,-50.0f }, stage);
    SpawnObstacle<Marshmallow_Blue>({ -250.0f,3.0f,-150.0f }, stage);
    SpawnObstacle<Marshmallow_Blue>({ -250.0f,3.0f,-100.0f }, stage);
    SpawnObstacle<Marshmallow_Blue>({ -250.0f,3.0f,-50.0f }, stage);

    SpawnObstacle<Pokey>({ 150.0f,0.0f,-200.0f }, stage);
    SpawnObstacle<Pokey>({ 125.0f,0.0f,-200.0f }, stage);
    SpawnObstacle<Pokey>({ 100.0f,0.0f,-200.0f }, stage);
    SpawnObstacle<Pokey>({ 75.0f,0.0f,-200.0f }, stage);
    SpawnObstacle<Candy_gate>({ 175.0f,0.0f,-200.0f }, stage);
    SpawnObstacle<Candy_gate>({ 200.0f,0.0f,-200.0f }, stage);
    SpawnObstacle<Candy_gate>({ 225.0f,0.0f,-200.0f }, stage);
    SpawnObstacle<Candy_gate>({ 250.0f,0.0f,-200.0f }, stage);
    SpawnObstacle<Marshmallow_Blue>({ 175.0f,3.0f,-150.0f }, stage);
    SpawnObstacle<Marshmallow_Blue>({ 175.0f,3.0f,-100.0f }, stage);
    SpawnObstacle<Marshmallow_Blue>({ 175.0f,3.0f,-50.0f }, stage);
    SpawnObstacle<Marshmallow_Blue>({ 200.0f,3.0f,-150.0f }, stage);
    SpawnObstacle<Marshmallow_Blue>({ 200.0f,3.0f,-100.0f }, stage);
    SpawnObstacle<Marshmallow_Blue>({ 200.0f,3.0f,-50.0f }, stage);
    SpawnObstacle<Marshmallow_Blue>({ 225.0f,3.0f,-150.0f }, stage);
    SpawnObstacle<Marshmallow_Blue>({ 225.0f,3.0f,-100.0f }, stage);
    SpawnObstacle<Marshmallow_Blue>({ 225.0f,3.0f,-50.0f }, stage);
    SpawnObstacle<Marshmallow_Blue>({ 250.0f,3.0f,-150.0f }, stage);
    SpawnObstacle<Marshmallow_Blue>({ 250.0f,3.0f,-100.0f }, stage);
    SpawnObstacle<Marshmallow_Blue>({ 250.0f,3.0f,-50.0f }, stage);


    SpawnObstacle<Marshmallow_Blue>({ -25.0f,3.0f,-150.0f }, stage);
    SpawnObstacle<Marshmallow_Blue>({ -25.0f,3.0f,-100.0f }, stage);
    SpawnObstacle<Marshmallow_Blue>({ -25.0f,3.0f,-50.0f }, stage);
    SpawnObstacle<Marshmallow_Blue>({ -50.0f,3.0f,-150.0f }, stage);
    SpawnObstacle<Marshmallow_Blue>({ -50.0f,3.0f,-100.0f }, stage);
    SpawnObstacle<Marshmallow_Blue>({ -50.0f,3.0f,-50.0f }, stage);
    SpawnObstacle<Marshmallow_Blue>({ 25.0f,3.0f,-150.0f }, stage);
    SpawnObstacle<Marshmallow_Blue>({ 25.0f,3.0f,-100.0f }, stage);
    SpawnObstacle<Marshmallow_Blue>({ 25.0f,3.0f,-50.0f }, stage);
    SpawnObstacle<Marshmallow_Blue>({ 50.0f,3.0f,-150.0f }, stage);
    SpawnObstacle<Marshmallow_Blue>({ 50.0f,3.0f,-100.0f }, stage);
    SpawnObstacle<Marshmallow_Blue>({ 50.0f,3.0f,-50.0f }, stage);

    SpawnObstacle<Candy_gate>({ 25.0f,0.0f,-200.0f }, stage);
    SpawnObstacle<Candy_gate>({ 50.0f,0.0f,-200.0f }, stage);
    SpawnObstacle<Candy_gate>({ -25.0f,0.0f,-200.0f }, stage);
    SpawnObstacle<Candy_gate>({ -50.0f,0.0f,-200.0f }, stage);
}
// エリア10
void Stage::AreaInfo10(Stage* stage)
{
    SpawnObstacle<Pokey>({ 0.0f,0.0f,-100.0f }, stage);
    SpawnObstacle<Prits>({ 0.0f,0.0f,0.0f }, stage);
    SpawnObstacle<Chocolate_ball>({ 0.0f,0.0f,100.0f }, stage);
    SpawnObstacle<Pokey>({ 100.0f,0.0f,100.0f }, stage);
    SpawnObstacle<Prits>({ 100.0f,0.0f,0.0f }, stage);
    SpawnObstacle<Chocolate_ball>({ 70.0f,0.0f,100.0f }, stage);
    SpawnObstacle<Pokey>({ 30.0f,0.0f,-30.0f }, stage);
    SpawnObstacle<Prits>({ 50.0f,0.0f,-220.0f }, stage);
    SpawnObstacle<Chocolate_ball>({ 10.0f,0.0f,-150.0f }, stage);
    SpawnObstacle<Pokey>({ 90.0f,0.0f,190.0f }, stage);
    SpawnObstacle<Prits>({ 220.0f,0.0f,230.0f }, stage);
    SpawnObstacle<Chocolate_ball>({ -230.0f,0.0f,230.0f }, stage);
    SpawnObstacle<Pokey>({ -100.0f,0.0f,40.0f }, stage);
    SpawnObstacle<Prits>({ -150.0f,0.0f,60.0f }, stage);
    SpawnObstacle<Chocolate_ball>({ -130.0f,0.0f,60.0f }, stage);
    SpawnObstacle<Pokey>({ -100.0f,0.0f,-10.0f }, stage);
    SpawnObstacle<Prits>({ -150.0f,0.0f,-60.0f }, stage);
    SpawnObstacle<Chocolate_ball>({ -130.0f,0.0f,-120.0f }, stage);
    SpawnObstacle<Pokey>({ -50.0f,0.0f,80.0f }, stage);
    SpawnObstacle<Prits>({ -230.0f,0.0f,-230.0f }, stage);
    SpawnObstacle<Chocolate_ball>({ -220.0f,0.0f,-190.0f }, stage);
    SpawnObstacle<Pokey>({ 200.0f,0.0f,80.0f }, stage);
    SpawnObstacle<Prits>({ 240.0f,0.0f,-70.0f }, stage);
    SpawnObstacle<Chocolate_ball>({ 40.0f,0.0f,90.0f }, stage);
    SpawnObstacle<Pokey>({ 235.0f,0.0f,180.0f }, stage);
    SpawnObstacle<Prits>({ 140.0f,0.0f,130.0f }, stage);
    SpawnObstacle<Chocolate_ball>({ 150.0f,0.0f,90.0f }, stage);
    SpawnObstacle<Chocolate_ball>({ -10.0f,0.0f,-130.0f }, stage);
    SpawnObstacle<Jellybeans_Yellow>({ 25.0f,3.0f,-240.0f }, stage);
    SpawnObstacle<Jellybeans_Yellow>({ 240.0f,3.0f,-240.0f }, stage);
    SpawnObstacle<Jellybeans_Pink>({ 40.0f,3.0f,130.0f }, stage);
    SpawnObstacle<Jellybeans_Pink>({ 195.0f,3.0f,230.0f }, stage);
    SpawnObstacle<Jellybeans_Green>({ 75.0f,3.0f,120.0f }, stage);
    SpawnObstacle<Jellybeans_Green>({ -150.0f,3.0f,-190.0f }, stage);
    SpawnObstacle<Jellybeans_Yellow>({ 240.0f,3.0f,-160.0f }, stage);

}
// エリア11
void Stage::AreaInfo11(Stage* stage)
{
    SpawnObstacle<Pokey>({ 0.0f,0.0f,-100.0f }, stage);
    SpawnObstacle<Prits>({ 0.0f,0.0f,0.0f }, stage);
    SpawnObstacle<Chocolate_ball>({ 0.0f,0.0f,100.0f }, stage);
    SpawnObstacle<Pokey>({ 100.0f,0.0f,100.0f }, stage);
    SpawnObstacle<Prits>({ 100.0f,0.0f,0.0f }, stage);
    SpawnObstacle<Chocolate_ball>({ 70.0f,0.0f,100.0f }, stage);
    SpawnObstacle<Pokey>({ 30.0f,0.0f,-30.0f }, stage);
    SpawnObstacle<Prits>({ 50.0f,0.0f,-220.0f }, stage);
    SpawnObstacle<Chocolate_ball>({ 10.0f,0.0f,-150.0f }, stage);
    SpawnObstacle<Pokey>({ 90.0f,0.0f,190.0f }, stage);
    SpawnObstacle<Prits>({ 220.0f,0.0f,230.0f }, stage);
    SpawnObstacle<Chocolate_ball>({ -230.0f,0.0f,230.0f }, stage);
    SpawnObstacle<Pokey>({ -100.0f,0.0f,40.0f }, stage);
    SpawnObstacle<Prits>({ -150.0f,0.0f,60.0f }, stage);
    SpawnObstacle<Chocolate_ball>({ -130.0f,0.0f,60.0f }, stage);
    SpawnObstacle<Pokey>({ -100.0f,0.0f,-10.0f }, stage);
    SpawnObstacle<Prits>({ -150.0f,0.0f,-60.0f }, stage);
    SpawnObstacle<Chocolate_ball>({ -130.0f,0.0f,-120.0f }, stage);
    SpawnObstacle<Pokey>({ -50.0f,0.0f,80.0f }, stage);
    SpawnObstacle<Prits>({ -230.0f,0.0f,-230.0f }, stage);
    SpawnObstacle<Chocolate_ball>({ -220.0f,0.0f,-190.0f }, stage);
    SpawnObstacle<Pokey>({ 200.0f,0.0f,80.0f }, stage);
    SpawnObstacle<Prits>({ 240.0f,0.0f,-70.0f }, stage);
    SpawnObstacle<Chocolate_ball>({ 40.0f,0.0f,90.0f }, stage);
    SpawnObstacle<Pokey>({ 235.0f,0.0f,180.0f }, stage);
    SpawnObstacle<Prits>({ 140.0f,0.0f,130.0f }, stage);
    SpawnObstacle<Chocolate_ball>({ 150.0f,0.0f,90.0f }, stage);
    SpawnObstacle<Chocolate_ball>({ -10.0f,0.0f,-130.0f }, stage);
    SpawnObstacle<Jellybeans_Yellow>({ 25.0f,3.0f,-240.0f }, stage);
    SpawnObstacle<Jellybeans_Yellow>({ 240.0f,3.0f,-240.0f }, stage);
    SpawnObstacle<Jellybeans_Pink>({ 40.0f,3.0f,130.0f }, stage);
    SpawnObstacle<Jellybeans_Pink>({ 195.0f,3.0f,230.0f }, stage);
    SpawnObstacle<Jellybeans_Green>({ 75.0f,3.0f,120.0f }, stage);
    SpawnObstacle<Jellybeans_Green>({ -150.0f,3.0f,-190.0f }, stage);
    SpawnObstacle<Jellybeans_Yellow>({ 240.0f,3.0f,-160.0f }, stage);
}
// エリア12
void Stage::AreaInfo12(Stage* stage)
{
    SpawnObstacle<Cola>({ 20.0f,0.0f,100.0f }, stage);
    SpawnObstacle<Cola>({ 40.0f,0.0f,-170.0f }, stage);
    SpawnObstacle<Cola>({ 190.0f,0.0f,110.0f }, stage);
    SpawnObstacle<Cola>({ -125.0f,0.0f,240.0f }, stage);
    SpawnObstacle<Pokey>({ -20.0f,0.0f,25.0f }, stage);
    SpawnObstacle<Pokey>({ 120.0f,0.0f,125.0f }, stage);
    SpawnObstacle<Pokey>({ 230.0f,0.0f,-125.0f }, stage);
    SpawnObstacle<Pokey>({ 170.0f,0.0f,180.0f }, stage);
    SpawnObstacle<Prits>({ 40.0f,0.0f,-25.0f }, stage);
    SpawnObstacle<Prits>({ 90.0f,0.0f,-80.0f }, stage);
    SpawnObstacle<Prits>({ 160.0f,0.0f,80.0f }, stage);
    SpawnObstacle<Prits>({ 210.0f,0.0f,190.0f }, stage);
    SpawnObstacle<Grape_can>({ 150.0f,0.0f,0.0f }, stage);
    SpawnObstacle<Grape_can>({ -10.0f,0.0f,90.0f }, stage);
    SpawnObstacle<Grape_can>({ -100.0f,0.0f,200.0f }, stage);
    SpawnObstacle<Grape_can>({ 50.0f,0.0f,-180.0f }, stage);
    SpawnObstacle<Grape_can>({ 10.0f,0.0f,-160.0f }, stage);
    SpawnObstacle<Orange_gum>({ -80.0f,0.0f,-150.0f }, stage);
    SpawnObstacle<Orange_gum>({ -20.0f,0.0f,180.0f }, stage);
    SpawnObstacle<Orange_gum>({ -200.0f,0.0f,60.0f }, stage);
    SpawnObstacle<Orange_gum>({ -120.0f,0.0f,45.0f }, stage);
    SpawnObstacle<Orange_can>({ 140.0f,0.0f,240.0f }, stage);
    SpawnObstacle<Orange_can>({ 100.0f,0.0f,-180.0f }, stage);
    SpawnObstacle<Orange_can>({ 240.0f,0.0f,-240.0f }, stage);
    SpawnObstacle<Orange_can>({ -180.0f,0.0f,-190.0f }, stage);
    SpawnObstacle<Marshmallow_Blue>({ -240.0f,3.0f,0.0f }, stage);
    SpawnObstacle<Marshmallow_Blue>({ 245.0f,3.0f,245.0f }, stage);
    SpawnObstacle<Marshmallow_Pink>({ 150.0f,3.0f,130.0f }, stage);
    SpawnObstacle<Marshmallow_Pink>({ -150.0f,3.0f,-130.0f }, stage);
    SpawnObstacle<Marshmallow_Blue>({ 120.0f,3.0f,-240.0f }, stage);
}
// エリア13
void Stage::AreaInfo13(Stage* stage)
{
    SpawnObstacle<Prits>({ 0.0f,0.0f,-240.0f }, stage);
    SpawnObstacle<Prits>({ 50.0f,0.0f,-240.0f }, stage);
    SpawnObstacle<Prits>({ 100.0f,0.0f,-240.0f }, stage);
    SpawnObstacle<Prits>({ 150.0f,0.0f,-240.0f }, stage);
    SpawnObstacle<Prits>({ 200.0f,0.0f,-240.0f }, stage);
    SpawnObstacle<Prits>({ 230.0f,0.0f,-240.0f }, stage);
    SpawnObstacle<Prits>({ -50.0f,0.0f,-240.0f }, stage);
    SpawnObstacle<Prits>({ -100.0f,0.0f,-240.0f }, stage);
    SpawnObstacle<Prits>({ -150.0f,0.0f,-240.0f }, stage);
    SpawnObstacle<Prits>({ -200.0f,0.0f,-240.0f }, stage);
    SpawnObstacle<Prits>({ -230.0f,0.0f,-240.0f }, stage);

    SpawnObstacle<Chocolate_ball>({ 25.0f,0.0f,-120.0f }, stage);
    SpawnObstacle<Chocolate_ball>({ 75.0f,0.0f,-120.0f }, stage);
    SpawnObstacle<Chocolate_ball>({ 125.0f,0.0f,-120.0f }, stage);
    SpawnObstacle<Chocolate_ball>({ 175.0f,0.0f,-120.0f }, stage);
    SpawnObstacle<Chocolate_ball>({ 225.0f,0.0f,-120.0f }, stage);
    SpawnObstacle<Chocolate_ball>({ -25.0f,0.0f,-120.0f }, stage);
    SpawnObstacle<Chocolate_ball>({ -75.0f,0.0f,-120.0f }, stage);
    SpawnObstacle<Chocolate_ball>({ -125.0f,0.0f,-120.0f }, stage);
    SpawnObstacle<Chocolate_ball>({ -175.0f,0.0f,-120.0f }, stage);
    SpawnObstacle<Chocolate_ball>({ -225.0f,0.0f,-120.0f }, stage);

    SpawnObstacle<Macaron_Pink>({ 0.0f,3.0f,0.0f }, stage);
    SpawnObstacle<Macaron_Pink>({ -50.0f,3.0f,0.0f }, stage);
    SpawnObstacle<Macaron_Pink>({ -100.0f,3.0f,0.0f }, stage);
    SpawnObstacle<Macaron_Pink>({ -150.0f,3.0f,0.0f }, stage);
    SpawnObstacle<Macaron_Pink>({ -200.0f,3.0f,0.0f }, stage);
    SpawnObstacle<Macaron_Pink>({ 50.0f,3.0f,0.0f }, stage);
    SpawnObstacle<Macaron_Pink>({ 100.0f,3.0f,0.0f }, stage);
    SpawnObstacle<Macaron_Pink>({ 150.0f,3.0f,0.0f }, stage);
    SpawnObstacle<Macaron_Pink>({ 200.0f,3.0f,0.0f }, stage);



    SpawnObstacle<Chocolate_ball>({ 25.0f,0.0f,120.0f }, stage);
    SpawnObstacle<Chocolate_ball>({ 75.0f,0.0f,120.0f }, stage);
    SpawnObstacle<Chocolate_ball>({ 125.0f,0.0f,120.0f }, stage);
    SpawnObstacle<Chocolate_ball>({ 175.0f,0.0f,120.0f }, stage);
    SpawnObstacle<Chocolate_ball>({ 225.0f,0.0f,120.0f }, stage);
    SpawnObstacle<Chocolate_ball>({ -25.0f,0.0f,120.0f }, stage);
    SpawnObstacle<Chocolate_ball>({ -75.0f,0.0f,120.0f }, stage);
    SpawnObstacle<Chocolate_ball>({ -125.0f,0.0f,120.0f }, stage);
    SpawnObstacle<Chocolate_ball>({ -175.0f,0.0f,120.0f }, stage);
    SpawnObstacle<Chocolate_ball>({ -225.0f,0.0f,120.0f }, stage);

    SpawnObstacle<Pokey>({ 0.0f,0.0f,240.0f }, stage);
    SpawnObstacle<Pokey>({ 50.0f,0.0f,240.0f }, stage);
    SpawnObstacle<Pokey>({ 100.0f,0.0f,240.0f }, stage);
    SpawnObstacle<Pokey>({ 150.0f,0.0f,240.0f }, stage);
    SpawnObstacle<Pokey>({ 200.0f,0.0f,240.0f }, stage);
    SpawnObstacle<Pokey>({ 230.0f,0.0f,240.0f }, stage);
    SpawnObstacle<Pokey>({ -50.0f,0.0f,240.0f }, stage);
    SpawnObstacle<Pokey>({ -100.0f,0.0f,240.0f }, stage);
    SpawnObstacle<Pokey>({ -150.0f,0.0f,240.0f }, stage);
    SpawnObstacle<Pokey>({ -200.0f,0.0f,240.0f }, stage);
    SpawnObstacle<Pokey>({ -230.0f,0.0f,240.0f }, stage);
}
// エリア14
void Stage::AreaInfo14(Stage* stage)
{
    SpawnObstacle<Cola>({ 220.0f,0.0f,-100.0f }, stage);
    SpawnObstacle<Orange_can>({ 200.0f,0.0f,100.0f }, stage);
    SpawnObstacle<Grape_can>({ -230.0f,0.0f,0.0f }, stage);
    SpawnObstacle<Cola>({ 120.0f,0.0f,-50.0f }, stage);
    SpawnObstacle<Orange_can>({ 190.0f,0.0f,50.0f }, stage);
    SpawnObstacle<Grape_can>({ -230.0f,0.0f,0.0f }, stage);
    SpawnObstacle<Cola>({ 180.0f,0.0f,-100.0f }, stage);
    SpawnObstacle<Orange_can>({ -120.0f,0.0f,90.0f }, stage);
    SpawnObstacle<Grape_can>({ -230.0f,0.0f,100.0f }, stage);
    SpawnObstacle<Cola>({ -180.0f,0.0f,-40.0f }, stage);
    SpawnObstacle<Orange_can>({ -20.0f,0.0f,-90.0f }, stage);
    SpawnObstacle<Grape_can>({ -10.0f,0.0f,10.0f }, stage);
    SpawnObstacle<Cola>({ -80.0f,0.0f,170.0f }, stage);
    SpawnObstacle<Orange_can>({ -20.0f,0.0f,220.0f }, stage);
    SpawnObstacle<Grape_can>({ 220.0f,0.0f,210.0f }, stage);
    SpawnObstacle<Cola>({ -10.0f,0.0f,170.0f }, stage);
    SpawnObstacle<Orange_can>({ -20.0f,0.0f,-150.0f }, stage);
    SpawnObstacle<Grape_can>({ 70.0f,0.0f,120.0f }, stage);
    SpawnObstacle<Cola>({ -70.0f,0.0f,-50.0f }, stage);
    SpawnObstacle<Orange_can>({ -100.0f,0.0f,-80.0f }, stage);
    SpawnObstacle<Grape_can>({ -20.0f,0.0f,120.0f }, stage);
    SpawnObstacle<Cola>({ -120.0f,0.0f,-50.0f }, stage);
    SpawnObstacle<Orange_can>({ -90.0f,0.0f,-40.0f }, stage);
    SpawnObstacle<Grape_can>({ -170.0f,0.0f,-120.0f }, stage);
    SpawnObstacle<Cola>({ -220.0f,0.0f,-100.0f }, stage);
    SpawnObstacle<Orange_can>({ -230.0f,0.0f,-70.0f }, stage);
    SpawnObstacle<Grape_can>({ -210.0f,0.0f,230.0f }, stage);
    SpawnObstacle<Cola>({ 240.0f,0.0f,230.0f }, stage);
    SpawnObstacle<Orange_can>({ 40.0f,0.0f,-90.0f }, stage);
    SpawnObstacle<Grape_can>({ 20.0f,0.0f,-50.0f }, stage);
    SpawnObstacle<Grape_can>({ 150.0f,0.0f,-200.0f }, stage);
    SpawnObstacle<Grape_can>({ 120.0f,0.0f,-180.0f }, stage);
    SpawnObstacle<Orange_can>({ 130.0f,0.0f,120.0f }, stage);
    SpawnObstacle<Cola>({ 110.0f,0.0f,80.0f }, stage);
    SpawnObstacle<Cola>({ 40.0f,0.0f,80.0f }, stage);
    SpawnObstacle<Cola>({ -40.0f,0.0f,180.0f }, stage);
    SpawnObstacle<Cola>({ 240.0f,0.0f,-20.0f }, stage);
    SpawnObstacle<Cola>({ 245.0f,0.0f,-90.0f }, stage);
    SpawnObstacle<Cola>({ -140.0f,0.0f,180.0f }, stage);
    SpawnObstacle<Orange_can>({ -180.0f,0.0f,210.0f }, stage);
    SpawnObstacle<Orange_can>({ -160.0f,0.0f,150.0f }, stage);
    SpawnObstacle<Orange_can>({ -190.0f,0.0f,100.0f }, stage);
    SpawnObstacle<Orange_can>({ -200.0f,0.0f,10.0f }, stage);
    SpawnObstacle<Jellybeans_Yellow>({ -90.0f,3.0f,-220.0f }, stage);
    SpawnObstacle<Jellybeans_Pink>({ 240.0f,3.0f,-80.0f }, stage);
    SpawnObstacle<Jellybeans_Green>({ 100.0f,3.0f,0.0f }, stage);
    SpawnObstacle<Jellybeans_Yellow>({ 20.0f,3.0f,40.0f }, stage);
    SpawnObstacle<Jellybeans_Pink>({ -110.0f,3.0f,0.0f }, stage);
    SpawnObstacle<Jellybeans_Green>({ -240.0f,3.0f,200.0f }, stage);
    SpawnObstacle<Jellybeans_Yellow>({ 150.0f,3.0f,90.0f }, stage);
    SpawnObstacle<Jellybeans_Pink>({ 170.0f,3.0f,170.0f }, stage);
    SpawnObstacle<Jellybeans_Green>({ 120.0f,3.0f,240.0f }, stage);
    SpawnObstacle<Jellybeans_Orange>({ 110.0f,3.0f,-200.0f }, stage);

}
// エリア15
void Stage::AreaInfo15(Stage* stage)
{
    SpawnObstacle<Cola>({ 240.0f,0.0f,-200.0f }, stage);
    SpawnObstacle<Cola>({ 230.0f,0.0f,-200.0f }, stage);
    SpawnObstacle<Cola>({ 220.0f,0.0f,-200.0f }, stage);
    SpawnObstacle<Cola>({ 210.0f,0.0f,-200.0f }, stage);
    SpawnObstacle<Cola>({ 200.0f,0.0f,-200.0f }, stage);
    SpawnObstacle<Cola>({ 190.0f,0.0f,-200.0f }, stage);
    SpawnObstacle<Cola>({ 180.0f,0.0f,-200.0f }, stage);
    SpawnObstacle<Cola>({ 170.0f,0.0f,-200.0f }, stage);
    SpawnObstacle<Cola>({ 160.0f,0.0f,-200.0f }, stage);
    SpawnObstacle<Cola>({ 150.0f,0.0f,-200.0f }, stage);

    SpawnObstacle<Candy_gate>({ 125.0f,0.0f,-200.0f }, stage);
    SpawnObstacle<Candy_gate>({ 100.0f,0.0f,-200.0f }, stage);
    SpawnObstacle<Candy_gate>({ 75.0f,0.0f,-200.0f }, stage);

    SpawnObstacle<Grape_can>({ 50.0f,0.0f,-200.0f }, stage);
    SpawnObstacle<Grape_can>({ 40.0f,0.0f,-200.0f }, stage);
    SpawnObstacle<Grape_can>({ 30.0f,0.0f,-200.0f }, stage);
    SpawnObstacle<Grape_can>({ 20.0f,0.0f,-200.0f }, stage);
    SpawnObstacle<Grape_can>({ 10.0f,0.0f,-200.0f }, stage);
    SpawnObstacle<Grape_can>({ 0.0f,0.0f,-200.0f }, stage);
    SpawnObstacle<Grape_can>({ -50.0f,0.0f,-200.0f }, stage);
    SpawnObstacle<Grape_can>({ -40.0f,0.0f,-200.0f }, stage);
    SpawnObstacle<Grape_can>({ -30.0f,0.0f,-200.0f }, stage);
    SpawnObstacle<Grape_can>({ -20.0f,0.0f,-200.0f }, stage);
    SpawnObstacle<Grape_can>({ -10.0f,0.0f,-200.0f }, stage);

    SpawnObstacle<Candy_gate>({ -125.0f,0.0f,-200.0f }, stage);
    SpawnObstacle<Candy_gate>({ -100.0f,0.0f,-200.0f }, stage);
    SpawnObstacle<Candy_gate>({ -75.0f,0.0f,-200.0f }, stage);
    SpawnObstacle<Prits>({ 125.0f,0.0f,200.0f }, stage);
    SpawnObstacle<Prits>({ 100.0f,0.0f,200.0f }, stage);
    SpawnObstacle<Prits>({ 75.0f,0.0f,200.0f }, stage);

    SpawnObstacle<Jellybeans_Yellow>({ 125.0f,3.0f,-150.0f }, stage);
    SpawnObstacle<Jellybeans_Yellow>({ 100.0f,3.0f,-150.0f }, stage);
    SpawnObstacle<Jellybeans_Yellow>({ 75.0f,3.0f,-150.0f }, stage);

    SpawnObstacle<Jellybeans_Yellow>({ -125.0f,3.0f,-150.0f }, stage);
    SpawnObstacle<Jellybeans_Yellow>({ -100.0f,3.0f,-150.0f }, stage);
    SpawnObstacle<Jellybeans_Yellow>({ -75.0f,3.0f,-150.0f }, stage);


    SpawnObstacle<Prits>({ -125.0f,0.0f,200.0f }, stage);
    SpawnObstacle<Prits>({ -100.0f,0.0f,200.0f }, stage);
    SpawnObstacle<Prits>({ -75.0f,0.0f,200.0f }, stage);

    SpawnObstacle<Jellybeans_Green>({ -50.0f,3.0f,200.0f }, stage);
    SpawnObstacle<Jellybeans_Green>({ -40.0f,3.0f,200.0f }, stage);
    SpawnObstacle<Jellybeans_Green>({ -30.0f,3.0f,200.0f }, stage);
    SpawnObstacle<Jellybeans_Green>({ -20.0f,3.0f,200.0f }, stage);
    SpawnObstacle<Jellybeans_Green>({ -10.0f,3.0f,200.0f }, stage);
    SpawnObstacle<Jellybeans_Green>({ 50.0f,3.0f,200.0f }, stage);
    SpawnObstacle<Jellybeans_Green>({ 40.0f,3.0f,200.0f }, stage);
    SpawnObstacle<Jellybeans_Green>({ 30.0f,3.0f,200.0f }, stage);
    SpawnObstacle<Jellybeans_Green>({ 20.0f,3.0f,200.0f }, stage);
    SpawnObstacle<Jellybeans_Green>({ 10.0f,3.0f,200.0f }, stage);
    SpawnObstacle<Jellybeans_Green>({ 0.0f,3.0f,200.0f }, stage);

    SpawnObstacle<Orange_can>({ -240.0f,0.0f,-200.0f }, stage);
    SpawnObstacle<Orange_can>({ -230.0f,0.0f,-200.0f }, stage);
    SpawnObstacle<Orange_can>({ -220.0f,0.0f,-200.0f }, stage);
    SpawnObstacle<Orange_can>({ -210.0f,0.0f,-200.0f }, stage);
    SpawnObstacle<Orange_can>({ -200.0f,0.0f,-200.0f }, stage);
    SpawnObstacle<Orange_can>({ -190.0f,0.0f,-200.0f }, stage);
    SpawnObstacle<Orange_can>({ -180.0f,0.0f,-200.0f }, stage);
    SpawnObstacle<Orange_can>({ -170.0f,0.0f,-200.0f }, stage);
    SpawnObstacle<Orange_can>({ -160.0f,0.0f,-200.0f }, stage);
    SpawnObstacle<Orange_can>({ -150.0f,0.0f,-200.0f }, stage);


}
// エリア16
void Stage::AreaInfo16(Stage* stage)
{
    SpawnObstacle<Chocolate_ball>({ -150.0f,0.0f,-230.0f }, stage);
    SpawnObstacle<Chocolate_ball>({ -210.0f,0.0f,-240.0f }, stage);
    SpawnObstacle<Chocolate_ball>({ -240.0f,0.0f,120.0f }, stage);

    SpawnObstacle<Chocolate_ball>({ -180.0f,0.0f,140.0f }, stage);

    SpawnObstacle<Candy_gate>({ -125.0f,0.0f,-200.0f }, stage);
    SpawnObstacle<Jellybeans_Orange>({ -125.0f,3.0f,-180.0f }, stage);
    SpawnObstacle<Candy_gate>({ -230.0f,0.0f,-150.0f }, stage);
    SpawnObstacle<Jellybeans_Orange>({ -230.0f,3.0f,-120.0f }, stage);

    SpawnObstacle<Candy_gate>({ -50.0f,0.0f,200.0f }, stage);
    SpawnObstacle<Jellybeans_Orange>({ -50.0f,3.0f,220.0f }, stage);
    SpawnObstacle<Candy_gate>({ 95.0f,0.0f,70.0f }, stage);
    SpawnObstacle<Jellybeans_Orange>({ 95.0f,3.0f,90.0f }, stage);
    SpawnObstacle<Candy_gate>({ 200.0f,0.0f,10.0f }, stage);
    SpawnObstacle<Jellybeans_Orange>({ 200.0f,3.0f,30.0f }, stage);
    SpawnObstacle<Chocolate_ball>({ 0.0f,0.0f,0.0f }, stage);
    SpawnObstacle<Chocolate_ball>({ 0.0f,0.0f,-200.0f }, stage);
    SpawnObstacle<Chocolate_ball>({ 50.0f,0.0f,10.0f }, stage);
    SpawnObstacle<Chocolate_ball>({ 200.0f,0.0f,200.0f }, stage);
}
void Stage::AreaInfo17(Stage* stage)
{
    //SpawnObstacle<Cola>({ 0.0f,0.0f,250.0f }, stage);
//SpawnObstacle<Cola>({ 0.0f,0.0f,230.0f }, stage);
//SpawnObstacle<Cola>({ 0.0f,0.0f,210.0f }, stage);
    SpawnObstacle<Cola>({ 0.0f,0.0f,190.0f }, stage);
    SpawnObstacle<Cola>({ 0.0f,0.0f,170.0f }, stage);
    SpawnObstacle<Cola>({ 0.0f,0.0f,150.0f }, stage);
    SpawnObstacle<Cola>({ 0.0f,0.0f,130.0f }, stage);
    SpawnObstacle<Cola>({ 0.0f,0.0f,110.0f }, stage);
    SpawnObstacle<Cola>({ 0.0f,0.0f,90.0f }, stage);
    SpawnObstacle<Cola>({ 0.0f,0.0f,70.0f }, stage);
    SpawnObstacle<Cola>({ 0.0f,0.0f,50.0f }, stage);
    SpawnObstacle<Cola>({ 0.0f,0.0f,30.0f }, stage);
    SpawnObstacle<Cola>({ 0.0f,0.0f,10.0f }, stage);
    SpawnObstacle<Cola>({ 0.0f,0.0f,-10.0f }, stage);
    SpawnObstacle<Cola>({ 0.0f,0.0f,-30.0f }, stage);
    SpawnObstacle<Cola>({ 0.0f,0.0f,-50.0f }, stage);
    SpawnObstacle<Cola>({ 0.0f,0.0f,-70.0f }, stage);
    SpawnObstacle<Cola>({ 0.0f,0.0f,-90.0f }, stage);
    SpawnObstacle<Cola>({ 0.0f,0.0f,-110.0f }, stage);
    SpawnObstacle<Cola>({ 0.0f,0.0f,-130.0f }, stage);
    SpawnObstacle<Cola>({ 0.0f,0.0f,-150.0f }, stage);
    SpawnObstacle<Cola>({ 0.0f,0.0f,-170.0f }, stage);
    SpawnObstacle<Cola>({ 0.0f,0.0f,-190.0f }, stage);
    SpawnObstacle<Cola>({ 0.0f,0.0f,-210.0f }, stage);
    SpawnObstacle<Cola>({ 0.0f,0.0f,-230.0f }, stage);


    SpawnObstacle<Cola>({ 110.0f,0.0f,-150.0f }, stage);
    SpawnObstacle<Cola>({ 95.0f,0.0f,-150.0f }, stage);
    SpawnObstacle<Cola>({ 80.0f,0.0f,-150.0f }, stage);
    SpawnObstacle<Cola>({ 65.0f,0.0f,-150.0f }, stage);
    SpawnObstacle<Cola>({ 50.0f,0.0f,-150.0f }, stage);
    SpawnObstacle< Marshmallow_Blue >({ 20.0f,3.0f,-150.0f }, stage);

    SpawnObstacle<Marshmallow_Pink>({ 90.0f,3.0f,150.0f }, stage);
    SpawnObstacle<Cola>({ 75.0f,0.0f,150.0f }, stage);
    SpawnObstacle<Cola>({ 60.0f,0.0f,150.0f }, stage);
    SpawnObstacle<Cola>({ 45.0f,0.0f,150.0f }, stage);
    SpawnObstacle<Cola>({ 30.0f,0.0f,150.0f }, stage);
    SpawnObstacle<Cola>({ 15.0f,0.0f,150.0f }, stage);


    SpawnObstacle<Cola>({ 125.0f,0.0f,190.0f }, stage);
    SpawnObstacle<Cola>({ 125.0f,0.0f,170.0f }, stage);
    SpawnObstacle<Cola>({ 125.0f,0.0f,150.0f }, stage);
    SpawnObstacle<Cola>({ 125.0f,0.0f,130.0f }, stage);
    SpawnObstacle<Cola>({ 125.0f,0.0f,110.0f }, stage);
    SpawnObstacle<Cola>({ 125.0f,0.0f,90.0f }, stage);
    SpawnObstacle<Cola>({ 125.0f,0.0f,70.0f }, stage);
    SpawnObstacle<Cola>({ 125.0f,0.0f,50.0f }, stage);
    SpawnObstacle<Cola>({ 125.0f,0.0f,30.0f }, stage);
    SpawnObstacle<Cola>({ 125.0f,0.0f,10.0f }, stage);
    SpawnObstacle<Cola>({ 125.0f,0.0f,-10.0f }, stage);
    SpawnObstacle<Cola>({ 125.0f,0.0f,-30.0f }, stage);
    SpawnObstacle<Cola>({ 125.0f,0.0f,-50.0f }, stage);
    SpawnObstacle<Cola>({ 125.0f,0.0f,-70.0f }, stage);
    SpawnObstacle<Cola>({ 125.0f,0.0f,-90.0f }, stage);
    SpawnObstacle<Cola>({ 125.0f,0.0f,-110.0f }, stage);
    SpawnObstacle<Cola>({ 125.0f,0.0f,-130.0f }, stage);
    SpawnObstacle<Cola>({ 125.0f,0.0f,-150.0f }, stage);
    SpawnObstacle<Cola>({ 125.0f,0.0f,-170.0f }, stage);
    SpawnObstacle<Cola>({ 140.0f,0.0f,-190.0f }, stage);
    SpawnObstacle<Cola>({ 155.0f,0.0f,-210.0f }, stage);
    SpawnObstacle<Cola>({ 170.0f,0.0f,-230.0f }, stage);

    SpawnObstacle<Cola>({ -110.0f,0.0f,-150.0f }, stage);
    SpawnObstacle<Cola>({ -95.0f,0.0f,-150.0f }, stage);
    SpawnObstacle<Cola>({ -80.0f,0.0f,-150.0f }, stage);
    SpawnObstacle<Cola>({ -65.0f,0.0f,-150.0f }, stage);
    SpawnObstacle<Cola>({ -50.0f,0.0f,-150.0f }, stage);

    SpawnObstacle<Cola>({ -75.0f,0.0f,0.0f }, stage);
    SpawnObstacle<Cola>({ -60.0f,0.0f,0.0f }, stage);
    SpawnObstacle<Cola>({ -45.0f,0.0f,0.0f }, stage);
    SpawnObstacle<Cola>({ -30.0f,0.0f,0.0f }, stage);
    SpawnObstacle<Cola>({ -15.0f,0.0f,0.0f }, stage);

    SpawnObstacle<Cola>({ -110.0f,0.0f,200.0f }, stage);
    SpawnObstacle<Cola>({ -95.0f,0.0f,200.0f }, stage);
    SpawnObstacle<Cola>({ -80.0f,0.0f,200.0f }, stage);
    SpawnObstacle<Cola>({ -65.0f,0.0f,200.0f }, stage);
    SpawnObstacle<Cola>({ -50.0f,0.0f,200.0f }, stage);

    SpawnObstacle<Cupcake_Pink>({ -20.0f,3.0f,200.0f }, stage);


    SpawnObstacle<Cola>({ -125.0f,0.0f,190.0f }, stage);
    SpawnObstacle<Cola>({ -125.0f,0.0f,170.0f }, stage);
    SpawnObstacle<Cola>({ -125.0f,0.0f,150.0f }, stage);
    SpawnObstacle<Cola>({ -125.0f,0.0f,130.0f }, stage);
    SpawnObstacle<Cola>({ -125.0f,0.0f,110.0f }, stage);
    SpawnObstacle<Cola>({ -125.0f,0.0f,90.0f }, stage);
    SpawnObstacle<Cola>({ -125.0f,0.0f,70.0f }, stage);
    SpawnObstacle<Cola>({ -125.0f,0.0f,50.0f }, stage);
    SpawnObstacle<Cola>({ -125.0f,0.0f,30.0f }, stage);
    SpawnObstacle<Cola>({ -125.0f,0.0f,10.0f }, stage);
    SpawnObstacle<Cola>({ -125.0f,0.0f,-10.0f }, stage);
    SpawnObstacle<Cola>({ -125.0f,0.0f,-30.0f }, stage);
    SpawnObstacle<Cola>({ -125.0f,0.0f,-50.0f }, stage);
    SpawnObstacle<Cola>({ -125.0f,0.0f,-70.0f }, stage);
    SpawnObstacle<Cola>({ -125.0f,0.0f,-90.0f }, stage);
    SpawnObstacle<Cola>({ -125.0f,0.0f,-110.0f }, stage);
    SpawnObstacle<Cola>({ -125.0f,0.0f,-130.0f }, stage);
    SpawnObstacle<Cola>({ -125.0f,0.0f,-150.0f }, stage);
    SpawnObstacle<Cola>({ -125.0f,0.0f,-170.0f }, stage);
    SpawnObstacle<Cola>({ -140.0f,0.0f,-190.0f }, stage);
    SpawnObstacle<Cola>({ -155.0f,0.0f,-210.0f }, stage);
    SpawnObstacle<Cola>({ -170.0f,0.0f,-230.0f }, stage);

}

void Stage::AreaInfo18(Stage* stage)
{
    SpawnObstacle<Orange_can>({ 0.0f,0.0f,15.0f }, stage);
    SpawnObstacle<Orange_can>({ 15.0f,0.0f,15.0f }, stage);
    SpawnObstacle<Orange_can>({ 7.0f,18.0f,15.0f }, stage);
    SpawnObstacle<Orange_can>({ 50.0f,0.0f,15.0f }, stage);
    SpawnObstacle<Orange_can>({ 65.0f,0.0f,15.0f }, stage);
    SpawnObstacle<Orange_can>({ 57.0f,18.0f,15.0f }, stage);
    SpawnObstacle<Orange_can>({ 150.0f,0.0f,-100.0f }, stage);
    SpawnObstacle<Orange_can>({ -100.0f,0.0f,-120.0f }, stage);
    SpawnObstacle<Orange_can>({ 230.0f,0.0f,80.0f }, stage);
    SpawnObstacle<Orange_can>({ -230.0f,0.0f,80.0f }, stage);
    SpawnObstacle<Orange_can>({ 60.0f,0.0f,170.0f }, stage);
    SpawnObstacle<Orange_can>({ -60.0f,0.0f,200.0f }, stage);
    SpawnObstacle<Orange_can>({ 100.0f,0.0f,-230.0f }, stage);
    SpawnObstacle<Orange_can>({ 75.0f,0.0f,230.0f }, stage);
    SpawnObstacle<Orange_can>({ 150.0f,0.0f,-200.0f }, stage);
    SpawnObstacle<Orange_can>({ 110.0f,0.0f,60.0f }, stage);
    SpawnObstacle<Orange_can>({ -150.0f,0.0f,-200.0f }, stage);
    SpawnObstacle<Orange_can>({ -110.0f,0.0f,60.0f }, stage);
    SpawnObstacle<Orange_can>({ -180.0f,0.0f,-50.0f }, stage);
    SpawnObstacle<Orange_can>({ -20.0f,0.0f,90.0f }, stage);
    SpawnObstacle<Orange_can>({ -80.0f,0.0f,-90.0f }, stage);
    SpawnObstacle<Orange_can>({ -50.0f,0.0f,140.0f }, stage);
    SpawnObstacle<Orange_can>({ 50.0f,0.0f,90.0f }, stage);
    SpawnObstacle<Orange_can>({ 220.0f,0.0f,190.0f }, stage);
    SpawnObstacle<Orange_can>({ 230.0f,0.0f,-230.0f }, stage);
    SpawnObstacle<Orange_can>({ -20.0f,0.0f,230.0f }, stage);
    SpawnObstacle<Orange_can>({ -240.0f,0.0f,100.0f }, stage);
    SpawnObstacle<Orange_can>({ -120.0f,0.0f,-100.0f }, stage);
    SpawnObstacle<Orange_can>({ 120.0f,0.0f,-100.0f }, stage);
    SpawnObstacle<Orange_can>({ -150.0f,0.0f,-100.0f }, stage);
    SpawnObstacle<Orange_can>({ -240.0f,0.0f,100.0f }, stage);
    SpawnObstacle<Macaron_Maccha>({ 35.0f,3.0f,0.0f }, stage);
    SpawnObstacle<Orange_can>({ -220.0f,0.0f,-100.0f }, stage);

    SpawnObstacle<Jellybeans_Orange>({ 100.0f,3.0f,190.0f }, stage);
    SpawnObstacle<Jellybeans_Orange>({ 240.0f,3.0f,240.0f }, stage);
    SpawnObstacle<Jellybeans_Orange>({ -220.0f,3.0f,100.0f }, stage);
    SpawnObstacle<Jellybeans_Orange>({ -50.0f,3.0f,-200.0f }, stage);
    SpawnObstacle<Jellybeans_Orange>({ -0.0f,3.0f,240.0f }, stage);
}

void Stage::AreaInfo19(Stage* stage)
{
    SpawnObstacle<Orange_gum>({ 90.0f,0.0f,-240.0f }, stage);
    SpawnObstacle<Orange_gum>({ 240.0f,0.0f,-240.0f }, stage);
    SpawnObstacle<Orange_gum>({ 200.0f,0.0f,-240.0 }, stage);
    SpawnObstacle<Orange_gum>({ -20.0f,0.0f,-240.0f }, stage);
    SpawnObstacle<Orange_gum>({ -150.0f,0.0f,-240.0f }, stage);
    SpawnObstacle<Orange_gum>({ -210.0f,0.0f,-240.0f }, stage);
    SpawnObstacle<Jellybeans_Orange>({ 100.0f,3.0f,-215.0f }, stage);
    SpawnObstacle<Jellybeans_Orange>({ -200.0f,3.0f,-215.0f }, stage);
    SpawnObstacle<Jellybeans_Orange>({ -100.0f,3.0f,-215.0f }, stage);
    SpawnObstacle<Orange_gum>({ 50.0f,0.0f,-190.0f }, stage);
    SpawnObstacle<Orange_gum>({ 150.0f,0.0f,-190.0f }, stage);
    SpawnObstacle<Orange_gum>({ 200.0f,0.0f,-190.0f }, stage);
    SpawnObstacle<Orange_gum>({ 0.0f,0.0f,-190.0f }, stage);
    SpawnObstacle<Orange_gum>({ -30.0f,0.0f,-190.0f }, stage);
    SpawnObstacle<Orange_gum>({ -95.0f,0.0f,-190.0f }, stage);
    SpawnObstacle<Orange_gum>({ -190.0f,0.0f,-190.0f }, stage);
    SpawnObstacle<Jellybeans_Orange>({ 0.0f,3.0f,-160.0f }, stage);
    SpawnObstacle<Jellybeans_Orange>({ -100.0f,3.0f,-160.0f }, stage);
    SpawnObstacle<Jellybeans_Orange>({ 150.0f,3.0f,-160.0f }, stage);
    SpawnObstacle<Orange_gum>({ 130.0f,0.0f,-120.0f }, stage);
    SpawnObstacle<Orange_gum>({ 60.0f,0.0f,-120.0f }, stage);
    SpawnObstacle<Orange_gum>({ 10.0f,0.0f,-120.0f }, stage);
    SpawnObstacle<Orange_gum>({ 210.0f,0.0f,-120.0f }, stage);
    SpawnObstacle<Orange_gum>({ -50.0f,0.0f,-120.0f }, stage);
    SpawnObstacle<Orange_gum>({ -140.0f,0.0f,-120.0f }, stage);
    SpawnObstacle<Orange_gum>({ -230.0f,0.0f,-120.0f }, stage);

    SpawnObstacle<Jellybeans_Orange>({ 100.0f,3.0f,-40.0f }, stage);
    SpawnObstacle<Jellybeans_Orange>({ -120.0f,3.0f,-40.0f }, stage);
    SpawnObstacle<Jellybeans_Orange>({ -30.0f,3.0f,-40.0f }, stage);
    SpawnObstacle<Orange_gum>({ 240.0f,0.0f,0.0f }, stage);
    SpawnObstacle<Orange_gum>({ 175.0f,0.0f,0.0f }, stage);
    SpawnObstacle<Orange_gum>({ 125.0f,0.0f,0.0f }, stage);
    SpawnObstacle<Orange_gum>({ 55.0f,0.0f,0.0f }, stage);
    SpawnObstacle<Orange_gum>({ 10.0f,0.0f,0.0f }, stage);
    SpawnObstacle<Orange_gum>({ -20.0f,0.0f,0.0f }, stage);
    SpawnObstacle<Orange_gum>({ -150.0f,0.0f,0.0f }, stage);
    SpawnObstacle<Orange_gum>({ -190.0f,0.0f,0.0f }, stage);
    SpawnObstacle<Jellybeans_Orange>({ 190.0f,3.0f,90.0f }, stage);
    SpawnObstacle<Jellybeans_Orange>({ -200.0f,3.0f,90.0f }, stage);
    SpawnObstacle<Jellybeans_Orange>({ -30.0f,3.0f,90.0f }, stage);
    SpawnObstacle<Orange_gum>({ 220.0f,0.0f,150.0f }, stage);
    SpawnObstacle<Orange_gum>({ 135.0f,0.0f,150.0f }, stage);
    SpawnObstacle<Orange_gum>({ 55.0f,0.0f,150.0f }, stage);
    SpawnObstacle<Orange_gum>({ -30.0f,0.0f,150.0f }, stage);
    SpawnObstacle<Orange_gum>({ -120.0f,0.0f,150.0f }, stage);
    SpawnObstacle<Orange_gum>({ -230.0f,0.0f,150.0f }, stage);
    SpawnObstacle<Jellybeans_Orange>({ -30.0f,3.0f,180.0f }, stage);
    SpawnObstacle<Jellybeans_Orange>({ -160.0f,3.0f,180.0f }, stage);
    SpawnObstacle<Orange_gum>({ 235.0f,0.0f,235.0f }, stage);
    SpawnObstacle<Orange_gum>({ 110.0f,0.0f,235.0f }, stage);
    SpawnObstacle<Orange_gum>({ -80.0f,0.0f,235.0f }, stage);
    SpawnObstacle<Orange_gum>({ -160.0f,0.0f,235.0f }, stage);
    SpawnObstacle<Orange_gum>({ -220.0f,0.0f,235.0f }, stage);
}

void Stage::AreaInfo20(Stage* stage)
{
    SpawnObstacle<Pokey>({ 75.0f,0.0f,-100.0f }, stage);
    SpawnObstacle<Pokey>({ -75.0f,0.0f,-100.0f }, stage);
    SpawnObstacle<Pokey>({ 180.0f,0.0f,-200.0f }, stage);
    SpawnObstacle<Pokey>({ -180.0f,0.0f,-200.0f }, stage);
    SpawnObstacle<Pokey>({ 20.0f,0.0f,-240.0f }, stage);
    SpawnObstacle<Pokey>({ -20.0f,0.0f,-240.0f }, stage);
    SpawnObstacle<Pokey>({ 15.0f,0.0f,180.0f }, stage);
    SpawnObstacle<Pokey>({ -15.0f,0.0f,180.0f }, stage);

    SpawnObstacle<Pokey>({ -25.0f,0.0f,0.0f }, stage);
    SpawnObstacle<Pokey>({ 25.0f,0.0f,0.0f }, stage);
    SpawnObstacle<Pokey>({ -25.0f,35.5f,0.0f }, stage);
    SpawnObstacle<Pokey>({ 25.0f,35.5f,0.0f }, stage);
    SpawnObstacle<Pokey>({ -15.0f,71.0f,0.0f }, stage);
    SpawnObstacle<Pokey>({ 15.0f,71.0f,0.0f }, stage);
    SpawnObstacle<Pokey>({ 0.0f,106.5f,0.0f }, stage);

    SpawnObstacle<Pokey>({ 35.0f,35.0f,50.0f }, stage);
    SpawnObstacle<Pokey>({ 50.0f,0.0f,50.0f }, stage);
    SpawnObstacle<Pokey>({ 65.0f,35.0f,50.0f }, stage);
    SpawnObstacle<Pokey>({ 85.0f,35.0f,100.0f }, stage);
    SpawnObstacle<Pokey>({ 100.0f,0.0f,100.0f }, stage);
    SpawnObstacle<Pokey>({ 115.0f,35.0f,100.0f }, stage);
    SpawnObstacle<Pokey>({ -35.0f,35.0f,50.0f }, stage);
    SpawnObstacle<Pokey>({ -50.0f,0.0f,50.0f }, stage);
    SpawnObstacle<Pokey>({ -65.0f,35.0f,50.0f }, stage);
    SpawnObstacle<Pokey>({ -115.0f,35.0f,100.0f }, stage);
    SpawnObstacle<Pokey>({ -100.0f,0.0f,100.0f }, stage);
    SpawnObstacle<Pokey>({ -85.0f,35.0f,100.0f }, stage);
    SpawnObstacle<Pokey>({ -135.0f,35.0f,200.0f }, stage);
    SpawnObstacle<Pokey>({ -150.0f,0.0f,200.0f }, stage);
    SpawnObstacle<Pokey>({ -165.0f,35.0f,200.0f }, stage);
    SpawnObstacle<Pokey>({ 150.0f,0.0f,200.0f }, stage);
    SpawnObstacle<Pokey>({ -230.0f,0.0f,230.0f }, stage);
    SpawnObstacle<Pokey>({ 230.0f,0.0f,230.0f }, stage);
    SpawnObstacle<Cupcake_Choco>({ 0.0f,3.0f,0.0f }, stage);
}

void Stage::AreaInfo21(Stage* stage)
{

    SpawnObstacle<Orange_gum>({ 0.0f,0.0f,-230.0f }, stage);
    SpawnObstacle<Orange_gum>({ 50.0f,0.0f,-230.0f }, stage);
    SpawnObstacle<Orange_gum>({ 100.0f,0.0f,-230.0f }, stage);
    SpawnObstacle<Orange_gum>({ 150.0f,0.0f,-230.0f }, stage);
    SpawnObstacle<Orange_gum>({ 200.0f,0.0f,-230.0f }, stage);

    SpawnObstacle<Orange_gum>({ -50.0f,0.0f,-230.0f }, stage);
    SpawnObstacle<Orange_gum>({ -100.0f,0.0f,-230.0f }, stage);
    SpawnObstacle<Orange_gum>({ -150.0f,0.0f,-230.0f }, stage);
    SpawnObstacle<Orange_gum>({ -200.0f,0.0f,-230.0f }, stage);

    SpawnObstacle<Husen_gum>({ 25.0f,0.0f,-180.0f }, stage);
    SpawnObstacle<Husen_gum>({ 75.0f,0.0f,-180.0f }, stage);
    SpawnObstacle<Husen_gum>({ 125.0f,0.0f,-180.0f }, stage);
    SpawnObstacle<Husen_gum>({ 175.0f,0.0f,-180.0f }, stage);
    SpawnObstacle<Husen_gum>({ 225.0f,0.0f,-180.0f }, stage);

    SpawnObstacle<Husen_gum>({ -25.0f,0.0f,-180.0f }, stage);
    SpawnObstacle<Husen_gum>({ -75.0f,0.0f,-180.0f }, stage);
    SpawnObstacle<Husen_gum>({ -125.0f,0.0f,-180.0f }, stage);
    SpawnObstacle<Husen_gum>({ -175.0f,0.0f,-180.0f }, stage);
    SpawnObstacle<Husen_gum>({ -225.0f,0.0f,-180.0f }, stage);


    SpawnObstacle<Husen_gum>({ 25.0f,0.0f,-50.0f }, stage);
    SpawnObstacle<Husen_gum>({ 75.0f,0.0f,-50.0f }, stage);
    SpawnObstacle<Husen_gum>({ 125.0f,0.0f,-50.0f }, stage);
    SpawnObstacle<Husen_gum>({ 175.0f,0.0f,-50.0f }, stage);
    SpawnObstacle<Husen_gum>({ 225.0f,0.0f,-50.0f }, stage);

    SpawnObstacle<Husen_gum>({ -25.0f,0.0f,-50.0f }, stage);
    SpawnObstacle<Husen_gum>({ -75.0f,0.0f,-50.0f }, stage);
    SpawnObstacle<Husen_gum>({ -125.0f,0.0f,-50.0f }, stage);
    SpawnObstacle<Husen_gum>({ -175.0f,0.0f,-50.0f }, stage);
    SpawnObstacle<Husen_gum>({ -225.0f,0.0f,-50.0f }, stage);

    SpawnObstacle<Orange_gum>({ 0.0f,0.0f,60.0f }, stage);
    SpawnObstacle<Orange_gum>({ 50.0f,0.0f,60.0f }, stage);
    SpawnObstacle<Orange_gum>({ 100.0f,0.0f,60.0f }, stage);
    SpawnObstacle<Orange_gum>({ 150.0f,0.0f,60.0f }, stage);
    SpawnObstacle<Orange_gum>({ 200.0f,0.0f,60.0f }, stage);

    SpawnObstacle<Orange_gum>({ -50.0f,0.0f,60.0f }, stage);
    SpawnObstacle<Orange_gum>({ -100.0f,0.0f,60.0f }, stage);
    SpawnObstacle<Orange_gum>({ -150.0f,0.0f,60.0f }, stage);
    SpawnObstacle<Orange_gum>({ -200.0f,0.0f,60.0f }, stage);


    SpawnObstacle<Jellybeans_Pink>({ 25.0f,3.0f,-190.0f }, stage);
    SpawnObstacle<Jellybeans_Pink>({ 75.0f,3.0f,-190.0f }, stage);
    SpawnObstacle<Jellybeans_Pink>({ 125.0f,3.0f,-190.0f }, stage);
    SpawnObstacle<Jellybeans_Pink>({ 175.0f,3.0f,-190.0f }, stage);
    SpawnObstacle<Jellybeans_Pink>({ 225.0f,3.0f,-190.0f }, stage);

    SpawnObstacle<Jellybeans_Pink>({ -25.0f,3.0f,-190.0f }, stage);
    SpawnObstacle<Jellybeans_Pink>({ -75.0f,3.0f,-190.0f }, stage);
    SpawnObstacle<Jellybeans_Pink>({ -125.0f,3.0f,-190.0f }, stage);
    SpawnObstacle<Jellybeans_Pink>({ -175.0f,3.0f,-190.0f }, stage);
    SpawnObstacle<Jellybeans_Pink>({ -225.0f,3.0f,-190.0f }, stage);

    SpawnObstacle<Jellybeans_Orange>({ 0.0f,3.0f,130.0f }, stage);
    SpawnObstacle<Jellybeans_Orange>({ 50.0f,3.0f,130.0f }, stage);
    SpawnObstacle<Jellybeans_Orange>({ 100.0f,3.0f,130.0f }, stage);
    SpawnObstacle<Jellybeans_Orange>({ 150.0f,3.0f,130.0f }, stage);
    SpawnObstacle<Jellybeans_Orange>({ 200.0f,3.0f,130.0f }, stage);
    SpawnObstacle<Jellybeans_Orange>({ -50.0f,3.0f,130.0f }, stage);
    SpawnObstacle<Jellybeans_Orange>({ -100.0f,3.0f,130.0f }, stage);
    SpawnObstacle<Jellybeans_Orange>({ -150.0f,3.0f,130.0f }, stage);
    SpawnObstacle<Jellybeans_Orange>({ -200.0f,3.0f,130.0f }, stage);


}

void Stage::AreaInfo22(Stage* stage)
{
    SpawnObstacle<Marshmallow_Blue>({ 50.0f,3.0f,20.0f }, stage);
    SpawnObstacle<Marshmallow_Blue>({ -50.0f,3.0f,20.0f }, stage);
    SpawnObstacle<Marble_chocolate>({ -100.0f,0.0f,0.0f }, stage);
    SpawnObstacle<Grape_can>({ 70.0f,0.0f,0.0f }, stage);
    SpawnObstacle<Grape_can>({ -70.0f,0.0f,0.0f }, stage);
    SpawnObstacle<Grape_can>({ 85.0f,0.0f,0.0f }, stage);
    SpawnObstacle<Grape_can>({ -85.0f,0.0f,0.0f }, stage);
    SpawnObstacle<Grape_can>({ 100.0f,0.0f,0.0f }, stage);
    SpawnObstacle<Grape_can>({ -100.0f,0.0f,0.0f }, stage);
    SpawnObstacle<Grape_can>({ 20.0f,0.0f,-200.0f }, stage);
    SpawnObstacle<Grape_can>({ -20.0f,0.0f,-200.0f }, stage);
    SpawnObstacle<Grape_can>({ 40.0f,0.0f,-180.0f }, stage);
    SpawnObstacle<Grape_can>({ -40.0f,0.0f,-180.0f }, stage);
    SpawnObstacle<Husen_gum>({ -0.0f,0.0f,-160.0f }, stage);
    SpawnObstacle<Husen_gum>({ -130.0f,0.0f,40.0f }, stage);
    SpawnObstacle<Husen_gum>({ 130.0f,0.0f,40.0f }, stage);
    SpawnObstacle<Marshmallow_Blue>({ 0.0f,3.0f,-200.0f }, stage);
    SpawnObstacle<Orange_can>({ -120.0f,0.0f,120.0f }, stage);
    SpawnObstacle<Orange_can>({ 120.0f,0.0f,120.0f }, stage);
    SpawnObstacle<Orange_can>({ -160.0f,0.0f,170.0f }, stage);
    SpawnObstacle<Orange_can>({ 160.0f,0.0f,170.0f }, stage);
    SpawnObstacle<Orange_can>({ -190.0f,0.0f,200.0f }, stage);
    SpawnObstacle<Orange_can>({ 190.0f,0.0f,200.0f }, stage);

    SpawnObstacle<Orange_can>({ -230.0f,0.0f,200.0f }, stage);
    SpawnObstacle<Orange_can>({ 230.0f,0.0f,200.0f }, stage);
    SpawnObstacle<Orange_can>({ -240.0f,0.0f,150.0f }, stage);
    SpawnObstacle<Orange_can>({ 240.0f,0.0f,150.0f }, stage);
    SpawnObstacle<Orange_can>({ -220.0f,0.0f,0.0f }, stage);
    SpawnObstacle<Orange_can>({ 220.0f,0.0f,0.0f }, stage);
    SpawnObstacle<Orange_can>({ -70.0f,0.0f,230.0f }, stage);
    SpawnObstacle<Orange_can>({ 70.0f,0.0f,230.0f }, stage);
    SpawnObstacle<Orange_can>({ -220.0f,0.0f,230.0f }, stage);
    SpawnObstacle<Orange_can>({ 220.0f,0.0f,230.0f }, stage);
    SpawnObstacle<Orange_can>({ -210.0f,0.0f,50.0f }, stage);
    SpawnObstacle<Orange_can>({ 210.0f,0.0f,50.0f }, stage);

    SpawnObstacle<Cola>({ 60.0f,0.0f,-60.0f }, stage);
    SpawnObstacle<Cola>({ -60.0f,0.0f,-60.0f }, stage);
    SpawnObstacle<Cola>({ 160.0f,0.0f,-120.0f }, stage);
    SpawnObstacle<Cola>({ 160.0f,0.0f,-120.0f }, stage);
    SpawnObstacle<Cola>({ 60.0f,18.0f,-60.0f }, stage);
    SpawnObstacle<Cola>({ -60.0f,18.0f,-60.0f }, stage);
    SpawnObstacle<Cola>({ 160.0f,18.0f,-120.0f }, stage);
    SpawnObstacle<Cola>({ 160.0f,18.0f,-120.0f }, stage);
    SpawnObstacle<Cupcake_Pink>({ -130.0f,3.0f,20.0f }, stage);
    SpawnObstacle<Cupcake_Pink>({ 130.0f,3.0f,20.0f }, stage);


    SpawnObstacle<Candy_gate>({ 0.0f,0.0f,-230.0f }, stage);
    SpawnObstacle<Candy_gate>({ 140.0f,0.0f,-240.0f }, stage);
    SpawnObstacle<Candy_gate>({ -140.0f,0.0f,-240.0f }, stage);
}

void Stage::AreaInfo23(Stage* stage)
{
    SpawnObstacle<Jellybeans_Green>({ 30.0f,3.0f,245.0f }, stage);
    SpawnObstacle<Jellybeans_Green>({ -30.0f,3.0f,245.0f }, stage);

    SpawnObstacle<Chocolate_ball>({ 0.0f,0.0f,230.0f }, stage);
    SpawnObstacle<Marble_chocolate>({ 0.0f,0.0f,200.0f }, stage);
    SpawnObstacle<Chocolate_ball>({ 50.0f,0.0f,180.0f }, stage);
    SpawnObstacle<Chocolate_ball>({ -50.0f,0.0f,180.0f }, stage);
    SpawnObstacle<Chocolate_ball>({ 100.0f,0.0f,180.0f }, stage);
    SpawnObstacle<Chocolate_ball>({ -100.0f,0.0f,180.0f }, stage);
    SpawnObstacle<Chocolate_ball>({ 30.0f,0.0f,130.0f }, stage);
    SpawnObstacle<Chocolate_ball>({ -30.0f,0.0f,130.0f }, stage);

    SpawnObstacle<Chocolate_ball>({ 230.0f,0.0f,240.0f }, stage);
    SpawnObstacle<Chocolate_ball>({ -230.0f,0.0f,240.0f }, stage);


    SpawnObstacle<Chocolate_ball>({ 150.0f,0.0f,10.0f }, stage);
    SpawnObstacle<Chocolate_ball>({ -150.0f,0.0f,10.0f }, stage);
    SpawnObstacle<Chocolate_ball>({ 110.0f,0.0f,10.0f }, stage);
    SpawnObstacle<Chocolate_ball>({ -110.0f,0.0f,10.0f }, stage);
    SpawnObstacle<Husen_gum>({ 130.0f,0.0f,40.0f }, stage);
    SpawnObstacle<Husen_gum>({ -130.0f,0.0f,40.0f }, stage);
    SpawnObstacle<Macaron_Maccha>({ 130.0f,3.0f,20.0f }, stage);
    SpawnObstacle<Macaron_Maccha>({ -130.0f,3.0f,20.0f }, stage);


    SpawnObstacle<Chocolate_ball>({ 20.0f,0.0f,-70.0f }, stage);
    SpawnObstacle<Chocolate_ball>({ -20.0f,0.0f,-70.0f }, stage);
    SpawnObstacle<Chocolate_ball>({ 55.0f,0.0f,-70.0f }, stage);
    SpawnObstacle<Chocolate_ball>({ -55.0f,0.0f,-70.0f }, stage);
    SpawnObstacle<Chocolate_ball>({ 155.0f,0.0f,-70.0f }, stage);
    SpawnObstacle<Chocolate_ball>({ -155.0f,0.0f,-70.0f }, stage);
    SpawnObstacle<Chocolate_ball>({ 225.0f,0.0f,-70.0f }, stage);
    SpawnObstacle<Chocolate_ball>({ -225.0f,0.0f,-70.0f }, stage);
    SpawnObstacle<Chocolate_ball>({ 235.0f,0.0f,70.0f }, stage);
    SpawnObstacle<Chocolate_ball>({ -235.0f,0.0f,70.0f }, stage);


    SpawnObstacle<Husen_gum>({ 70.0f,0.0f,-120.0f }, stage);
    SpawnObstacle<Husen_gum>({ -70.0f,0.0f,-120.0f }, stage);

    SpawnObstacle<Husen_gum>({ 170.0f,0.0f,-200.0f }, stage);
    SpawnObstacle<Husen_gum>({ -170.0f,0.0f,-200.0f }, stage);

    SpawnObstacle<Chocolate_ball>({ 35.0f,0.0f,-220.0f }, stage);
    SpawnObstacle<Chocolate_ball>({ -35.0f,0.0f,-220.0f }, stage);
}

void Stage::AreaInfo24(Stage* stage)
{
    SpawnObstacle<Orange_gum>({ 210.0f,0.0f,-80.0f }, stage);
    SpawnObstacle<Orange_gum>({ 170.0f,0.0f,-80.0f }, stage);

    SpawnObstacle<Orange_gum>({ -210.0f,0.0f,-80.0f }, stage);
    SpawnObstacle<Orange_gum>({ -170.0f,0.0f,-80.0f }, stage);

    SpawnObstacle<Orange_gum>({ -20.0f,0.0f,-80.0f }, stage);
    SpawnObstacle<Orange_gum>({ 20.0f,0.0f,-80.0f }, stage);

    SpawnObstacle<Orange_gum>({ -20.0f,0.0f,170.0f }, stage);
    SpawnObstacle<Orange_gum>({ 20.0f,0.0f,170.0f }, stage);

    SpawnObstacle<Orange_gum>({ 170.0f,0.0f,170.0f }, stage);
    SpawnObstacle<Orange_gum>({ 210.0f,0.0f,170.0f }, stage);
    SpawnObstacle<Orange_gum>({ -170.0f,0.0f,170.0f }, stage);
    SpawnObstacle<Orange_gum>({ -210.0f,0.0f,170.0f }, stage);

    SpawnObstacle<Orange_gum>({ -120.0f,0.0f,-170.0f }, stage);
    SpawnObstacle<Orange_gum>({ -80.0f,0.0f,-170.0f }, stage);
    SpawnObstacle<Orange_gum>({ 120.0f,0.0f,-170.0f }, stage);
    SpawnObstacle<Orange_gum>({ 80.0f,0.0f,-170.0f }, stage);

    SpawnObstacle<Orange_gum>({ -120.0f,0.0f,120.0f }, stage);
    SpawnObstacle<Orange_gum>({ -80.0f,0.0f,120.0f }, stage);
    SpawnObstacle<Orange_gum>({ 120.0f,0.0f,120.0f }, stage);
    SpawnObstacle<Orange_gum>({ 80.0f,0.0f,120.0f }, stage);


    SpawnObstacle<Jellybeans_Green>({ -100.0f,3.0f,-130.0f }, stage);
    SpawnObstacle<Jellybeans_Green>({ 100.0f,3.0f,-130.0f }, stage);
    SpawnObstacle<Husen_gum>({ -60.0f,0.0f,-150.0f }, stage);
    SpawnObstacle<Husen_gum>({ -80.0f,0.0f,-150.0f }, stage);
    SpawnObstacle<Husen_gum>({ -100.0f,0.0f,-150.0f }, stage);
    SpawnObstacle<Husen_gum>({ -120.0f,0.0f,-150.0f }, stage);
    SpawnObstacle<Husen_gum>({ -140.0f,0.0f,-150.0f }, stage);
    SpawnObstacle<Candy_gate>({ 100.0f,0.0f,-170.0f }, stage);
    SpawnObstacle<Candy_gate>({ -100.0f,0.0f,-170.0f }, stage);
    SpawnObstacle<Husen_gum>({ 60.0f,0.0f,-150.0f }, stage);
    SpawnObstacle<Husen_gum>({ 80.0f,0.0f,-150.0f }, stage);
    SpawnObstacle<Husen_gum>({ 100.0f,0.0f,-150.0f }, stage);
    SpawnObstacle<Husen_gum>({ 120.0f,0.0f,-150.0f }, stage);
    SpawnObstacle<Husen_gum>({ 140.0f,0.0f,-150.0f }, stage);
    SpawnObstacle<Jellybeans_Green>({ 0.0f,3.0f,-30.0f }, stage);
    SpawnObstacle<Candy_gate>({ 0.0f,0.0f,-70.0f }, stage);
    SpawnObstacle<Husen_gum>({ 40.0f,0.0f,-50.0f }, stage);
    SpawnObstacle<Husen_gum>({ 20.0f,0.0f,-50.0f }, stage);
    SpawnObstacle<Husen_gum>({ -40.0f,0.0f,-50.0f }, stage);
    SpawnObstacle<Husen_gum>({ -20.0f,0.0f,-50.0f }, stage);
    SpawnObstacle<Husen_gum>({ 0.0f,0.0f,-50.0f }, stage);
    SpawnObstacle<Jellybeans_Green>({ 190.0f,3.0f,-30.0f }, stage);
    SpawnObstacle<Jellybeans_Green>({ -190.0f,3.0f,-30.0f }, stage);
    SpawnObstacle<Candy_gate>({ 190.0f,0.0f,-70.0f }, stage);
    SpawnObstacle<Candy_gate>({ -190.0f,0.0f,-70.0f }, stage);
    SpawnObstacle<Husen_gum>({ 160.0f,0.0f,-50.0f }, stage);
    SpawnObstacle<Husen_gum>({ 180.0f,0.0f,-50.0f }, stage);
    SpawnObstacle<Husen_gum>({ -160.0f,0.0f,-50.0f }, stage);
    SpawnObstacle<Husen_gum>({ -180.0f,0.0f,-50.0f }, stage);
    SpawnObstacle<Husen_gum>({ 200.0f,0.0f,-50.0f }, stage);
    SpawnObstacle<Husen_gum>({ -200.0f,0.0f,-50.0f }, stage);
    SpawnObstacle<Husen_gum>({ 220.0f,0.0f,-50.0f }, stage);
    SpawnObstacle<Husen_gum>({ -220.0f,0.0f,-50.0f }, stage);

    SpawnObstacle<Jellybeans_Green>({ -100.0f,3.0f,80.0f }, stage);
    SpawnObstacle<Candy_gate>({ 100.0f,0.0f,120.0f }, stage);
    SpawnObstacle<Candy_gate>({ -100.0f,0.0f,120.0f }, stage);
    SpawnObstacle<Husen_gum>({ -60.0f,0.0f,100.0f }, stage);
    SpawnObstacle<Husen_gum>({ -80.0f,0.0f,100.0f }, stage);
    SpawnObstacle<Husen_gum>({ -100.0f,0.0f,100.0f }, stage);
    SpawnObstacle<Husen_gum>({ -120.0f,0.0f,100.0f }, stage);
    SpawnObstacle<Husen_gum>({ -140.0f,0.0f,100.0f }, stage);
    SpawnObstacle<Jellybeans_Green>({ 100.0f,3.0f,80.0f }, stage);
    SpawnObstacle<Husen_gum>({ 60.0f,0.0f,100.0f }, stage);
    SpawnObstacle<Husen_gum>({ 80.0f,0.0f,100.0f }, stage);
    SpawnObstacle<Husen_gum>({ 100.0f,0.0f,100.0f }, stage);
    SpawnObstacle<Husen_gum>({ 120.0f,0.0f,100.0f }, stage);
    SpawnObstacle<Husen_gum>({ 140.0f,0.0f,100.0f }, stage);

    SpawnObstacle<Candy_gate>({ 0.0f,0.0f,180.0f }, stage);
    SpawnObstacle<Husen_gum>({ 40.0f,0.0f,200.0f }, stage);
    SpawnObstacle<Husen_gum>({ 20.0f,0.0f,200.0f }, stage);
    SpawnObstacle<Husen_gum>({ -40.0f,0.0f,200.0f }, stage);
    SpawnObstacle<Husen_gum>({ -20.0f,0.0f,200.0f }, stage);
    SpawnObstacle<Husen_gum>({ 0.0f,0.0f,200.0f }, stage);
    SpawnObstacle<Jellybeans_Green>({ 0.0f,3.0f,220.0f }, stage);
    SpawnObstacle<Jellybeans_Green>({ 190.0f,3.0f,220.0f }, stage);
    SpawnObstacle<Jellybeans_Green>({ -190.0f,3.0f,220.0f }, stage);
    SpawnObstacle<Candy_gate>({ 190.0f,0.0f,180.0f }, stage);
    SpawnObstacle<Candy_gate>({ -190.0f,0.0f,180.0f }, stage);
    SpawnObstacle<Husen_gum>({ 160.0f,0.0f,200.0f }, stage);
    SpawnObstacle<Husen_gum>({ 180.0f,0.0f,200.0f }, stage);
    SpawnObstacle<Husen_gum>({ -160.0f,0.0f,200.0f }, stage);
    SpawnObstacle<Husen_gum>({ -180.0f,0.0f,200.0f }, stage);
    SpawnObstacle<Husen_gum>({ 200.0f,0.0f,200.0f }, stage);
    SpawnObstacle<Husen_gum>({ -200.0f,0.0f,200.0f }, stage);
    SpawnObstacle<Husen_gum>({ 220.0f,0.0f,200.0f }, stage);
    SpawnObstacle<Husen_gum>({ -220.0f,0.0f,200.0f }, stage);
}

void Stage::AreaInfo25(Stage* stage)
{
    SpawnObstacle<Pokey>({ -10.0f,0.0f,-240.0f }, stage);
    SpawnObstacle<Pokey>({ -240.0f,0.0f,-240.0f }, stage);
    SpawnObstacle<Pokey>({ -150.0f,0.0f,-240.0f }, stage);
    SpawnObstacle<Pokey>({ -90.0f,0.0f,-240.0f }, stage);

    SpawnObstacle<Pokey>({ -40.0f,0.0f,-200.0f }, stage);
    SpawnObstacle<Pokey>({ -120.0f,0.0f,-200.0f }, stage);
    SpawnObstacle<Pokey>({ -180.0f,0.0f,-200.0f }, stage);
    SpawnObstacle<Pokey>({ -230.0f,0.0f,-200.0f }, stage);

    SpawnObstacle<Pokey>({ -10.0f,0.0f,-150.0f }, stage);
    SpawnObstacle<Pokey>({ -80.0f,0.0f,-150.0f }, stage);
    SpawnObstacle<Pokey>({ -150.0f,0.0f,-150.0f }, stage);
    SpawnObstacle<Pokey>({ -210.0f,0.0f,-150.0f }, stage);

    SpawnObstacle<Pokey>({ -20.0f,0.0f,-50.0f }, stage);
    SpawnObstacle<Pokey>({ -50.0f,0.0f,-50.0f }, stage);
    SpawnObstacle<Pokey>({ -100.0f,0.0f,-50.0f }, stage);
    SpawnObstacle<Pokey>({ -160.0f,0.0f,-50.0f }, stage);
    SpawnObstacle<Macaron_Maccha>({ 0.0f,3.0f,0.0f }, stage);
    SpawnObstacle<Pokey>({ -15.0f,0.0f,100.0f }, stage);
    SpawnObstacle<Pokey>({ -90.0f,0.0f,100.0f }, stage);
    SpawnObstacle<Pokey>({ -180.0f,0.0f,100.0f }, stage);
    SpawnObstacle<Pokey>({ -220.0f,0.0f,100.0f }, stage);
    SpawnObstacle<Pokey>({ -50.0f,0.0f,230.0f }, stage);
    SpawnObstacle<Pokey>({ -120.0f,0.0f,230.0f }, stage);
    SpawnObstacle<Pokey>({ -190.0f,0.0f,230.0f }, stage);
    SpawnObstacle<Pokey>({ -230.0f,0.0f,230.0f }, stage);

    SpawnObstacle<Prits>({ 240.0f,0.0f,-240.0f }, stage);
    SpawnObstacle<Prits>({ 120.0f,0.0f,-240.0f }, stage);
    SpawnObstacle<Prits>({ 20.0f,0.0f,-240.0f }, stage);

    SpawnObstacle<Prits>({ 180.0f,0.0f,-180.0f }, stage);
    SpawnObstacle<Prits>({ 90.0f,0.0f,-180.0f }, stage);
    SpawnObstacle<Prits>({ 40.0f,0.0f,-180.0f }, stage);

    SpawnObstacle<Prits>({ 210.0f,0.0f,-90.0f }, stage);
    SpawnObstacle<Prits>({ 100.0f,0.0f,-90.0f }, stage);
    SpawnObstacle<Prits>({ 40.0f,0.0f,-90.0f }, stage);

    SpawnObstacle<Prits>({ 230.0f,0.0f,-10.0f }, stage);
    SpawnObstacle<Prits>({ 150.0f,0.0f,-10.0f }, stage);
    SpawnObstacle<Prits>({ 90.0f,0.0f,-10.0f }, stage);

    SpawnObstacle<Prits>({ 15.0f,0.0f,100.0f }, stage);
    SpawnObstacle<Prits>({ 70.0f,0.0f,100.0f }, stage);
    SpawnObstacle<Prits>({ 150.0f,0.0f,100.0f }, stage);
    SpawnObstacle<Prits>({ 210.0f,0.0f,100.0f }, stage);

    SpawnObstacle<Prits>({ 50.0f,0.0f,190.0f }, stage);
    SpawnObstacle<Prits>({ 100.0f,0.0f,190.0f }, stage);
    SpawnObstacle<Prits>({ 170.0f,0.0f,190.0f }, stage);
    SpawnObstacle<Prits>({ 240.0f,0.0f,190.0f }, stage);
}

void Stage::AreaInfo26(Stage* stage)
{
    SpawnObstacle<Cupcake_Choco>({ 0.0f,3.0f,-240.0f }, stage);
    SpawnObstacle<Pokey>({ 0.0f,0.0f,-150 }, stage);
    SpawnObstacle<Pokey>({ 25.0f,0.0f,-200.0f }, stage);
    SpawnObstacle<Pokey>({ 50.0f,0.0f,-200.0f }, stage);
    SpawnObstacle<Pokey>({ 75.0f,0.0f,-200.0f }, stage);
    SpawnObstacle<Pokey>({ -25.0f,0.0f,-200.0f }, stage);
    SpawnObstacle<Pokey>({ -50.0f,0.0f,-200.0f }, stage);
    SpawnObstacle<Pokey>({ -75.0f,0.0f,-200.0f }, stage);
    SpawnObstacle<Pokey>({ 125.0f,0.0f,-200.0f }, stage);
    SpawnObstacle<Pokey>({ 150.0f,0.0f,-200.0f }, stage);
    SpawnObstacle<Pokey>({ 175.0f,0.0f,-200.0f }, stage);
    SpawnObstacle<Pokey>({ -125.0f,0.0f,-200.0f }, stage);
    SpawnObstacle<Pokey>({ -150.0f,0.0f,-200.0f }, stage);
    SpawnObstacle<Pokey>({ -175.0f,0.0f,-200.0f }, stage);
    SpawnObstacle<Pokey>({ 200.0f,0.0f,-200.0f }, stage);
    SpawnObstacle<Pokey>({ 225.0f,0.0f,-200.0f }, stage);
    SpawnObstacle<Pokey>({ -200.0f,0.0f,-200.0f }, stage);
    SpawnObstacle<Pokey>({ -225.0f,0.0f,-200.0f }, stage);

    SpawnObstacle<Pokey>({ -230.0f,0.0f,-100.0f }, stage);
    SpawnObstacle<Pokey>({ 230.0f,0.0f,-100.0f }, stage);
    SpawnObstacle<Pokey>({ -180.0f,0.0f,-100.0f }, stage);
    SpawnObstacle<Pokey>({ 180.0f,0.0f,-100.0f }, stage);
    SpawnObstacle<Pokey>({ -120.0f,0.0f,-100.0f }, stage);
    SpawnObstacle<Pokey>({ 120.0f,0.0f,-100.0f }, stage);
    SpawnObstacle<Pokey>({ -50.0f,0.0f,-100.0f }, stage);
    SpawnObstacle<Pokey>({ 50.0f,0.0f,-100.0f }, stage);
    SpawnObstacle<Pokey>({ -40.0f,0.0f,0.0f }, stage);
    SpawnObstacle<Pokey>({ 40.0f,0.0f,-0.0f }, stage);
    SpawnObstacle<Pokey>({ -100.0f,0.0f,0.0f }, stage);
    SpawnObstacle<Pokey>({ 100.0f,0.0f,-0.0f }, stage);
    SpawnObstacle<Pokey>({ -180.0f,0.0f,0.0f }, stage);
    SpawnObstacle<Pokey>({ 180.0f,0.0f,-0.0f }, stage);
    SpawnObstacle<Pokey>({ -225.0f,0.0f,0.0f }, stage);
    SpawnObstacle<Pokey>({ 225.0f,0.0f,-0.0f }, stage);
    SpawnObstacle<Pokey>({ 0.0f,0.0f,0.0f }, stage);

    SpawnObstacle<Pokey>({ -55.0f,0.0f,100.0f }, stage);
    SpawnObstacle<Pokey>({ 55.0f,0.0f,100.0f }, stage);
    SpawnObstacle<Pokey>({ -105.0f,0.0f,100.0f }, stage);
    SpawnObstacle<Pokey>({ 105.0f,0.0f,100.0f }, stage);
    SpawnObstacle<Pokey>({ -155.0f,0.0f,100.0f }, stage);
    SpawnObstacle<Pokey>({ 155.0f,0.0f,100.0f }, stage);

    SpawnObstacle<Pokey>({ -25.0f,0.0f,200.0f }, stage);
    SpawnObstacle<Pokey>({ 25.0f,0.0f,200.0f }, stage);
    SpawnObstacle<Pokey>({ -130.0f,0.0f,200.0f }, stage);
    SpawnObstacle<Pokey>({ 130.0f,0.0f,200.0f }, stage);
    SpawnObstacle<Pokey>({ -195.0f,0.0f,200.0f }, stage);
    SpawnObstacle<Pokey>({ 195.0f,0.0f,200.0f }, stage);

}

void Stage::AreaInfo27(Stage* stage)
{
    SpawnObstacle<Pokey>({ -10.0f,0.0f,-240.0f }, stage);
    SpawnObstacle<Pokey>({ -240.0f,0.0f,-240.0f }, stage);
    SpawnObstacle<Pokey>({ -150.0f,0.0f,-240.0f }, stage);
    SpawnObstacle<Pokey>({ -90.0f,0.0f,-240.0f }, stage);

    SpawnObstacle<Pokey>({ -40.0f,0.0f,-200.0f }, stage);
    SpawnObstacle<Pokey>({ -120.0f,0.0f,-200.0f }, stage);
    SpawnObstacle<Pokey>({ -180.0f,0.0f,-200.0f }, stage);
    SpawnObstacle<Pokey>({ -230.0f,0.0f,-200.0f }, stage);

    SpawnObstacle<Pokey>({ -10.0f,0.0f,-150.0f }, stage);
    SpawnObstacle<Pokey>({ -80.0f,0.0f,-150.0f }, stage);
    SpawnObstacle<Pokey>({ -150.0f,0.0f,-150.0f }, stage);
    SpawnObstacle<Pokey>({ -210.0f,0.0f,-150.0f }, stage);

    SpawnObstacle<Pokey>({ -20.0f,0.0f,-50.0f }, stage);
    SpawnObstacle<Pokey>({ -50.0f,0.0f,-50.0f }, stage);
    SpawnObstacle<Pokey>({ -100.0f,0.0f,-50.0f }, stage);
    SpawnObstacle<Pokey>({ -160.0f,0.0f,-50.0f }, stage);
    SpawnObstacle<Macaron_Maccha>({ 200.0f,3.0f,-240.0f }, stage);
    SpawnObstacle<Pokey>({ -15.0f,0.0f,100.0f }, stage);
    SpawnObstacle<Pokey>({ -90.0f,0.0f,100.0f }, stage);
    SpawnObstacle<Pokey>({ -180.0f,0.0f,100.0f }, stage);
    SpawnObstacle<Pokey>({ -220.0f,0.0f,100.0f }, stage);
    SpawnObstacle<Pokey>({ -50.0f,0.0f,230.0f }, stage);
    SpawnObstacle<Pokey>({ -120.0f,0.0f,230.0f }, stage);
    SpawnObstacle<Pokey>({ -190.0f,0.0f,230.0f }, stage);
    SpawnObstacle<Pokey>({ -230.0f,0.0f,230.0f }, stage);

    SpawnObstacle<Prits>({ 240.0f,0.0f,-240.0f }, stage);
    SpawnObstacle<Prits>({ 120.0f,0.0f,-240.0f }, stage);
    SpawnObstacle<Prits>({ 20.0f,0.0f,-240.0f }, stage);

    SpawnObstacle<Prits>({ 180.0f,0.0f,-180.0f }, stage);
    SpawnObstacle<Prits>({ 90.0f,0.0f,-180.0f }, stage);
    SpawnObstacle<Prits>({ 40.0f,0.0f,-180.0f }, stage);

    SpawnObstacle<Prits>({ 210.0f,0.0f,-90.0f }, stage);
    SpawnObstacle<Prits>({ 100.0f,0.0f,-90.0f }, stage);
    SpawnObstacle<Prits>({ 40.0f,0.0f,-90.0f }, stage);

    SpawnObstacle<Prits>({ 230.0f,0.0f,-10.0f }, stage);
    SpawnObstacle<Prits>({ 150.0f,0.0f,-10.0f }, stage);
    SpawnObstacle<Prits>({ 90.0f,0.0f,-10.0f }, stage);

    SpawnObstacle<Prits>({ 15.0f,0.0f,100.0f }, stage);
    SpawnObstacle<Prits>({ 70.0f,0.0f,100.0f }, stage);
    SpawnObstacle<Prits>({ 150.0f,0.0f,100.0f }, stage);
    SpawnObstacle<Prits>({ 210.0f,0.0f,100.0f }, stage);

    SpawnObstacle<Prits>({ 50.0f,0.0f,190.0f }, stage);
    SpawnObstacle<Prits>({ 100.0f,0.0f,190.0f }, stage);
    SpawnObstacle<Prits>({ 170.0f,0.0f,190.0f }, stage);
    SpawnObstacle<Prits>({ 240.0f,0.0f,190.0f }, stage);
}

void Stage::AreaInfo28(Stage* stage)
{
    SpawnObstacle<Pokey>({ -10.0f,0.0f,-240.0f }, stage);
    SpawnObstacle<Pokey>({ -240.0f,0.0f,-240.0f }, stage);
    SpawnObstacle<Pokey>({ -150.0f,0.0f,-240.0f }, stage);
    SpawnObstacle<Pokey>({ -90.0f,0.0f,-240.0f }, stage);

    SpawnObstacle<Pokey>({ -40.0f,0.0f,-200.0f }, stage);
    SpawnObstacle<Pokey>({ -120.0f,0.0f,-200.0f }, stage);
    SpawnObstacle<Pokey>({ -180.0f,0.0f,-200.0f }, stage);
    SpawnObstacle<Pokey>({ -230.0f,0.0f,-200.0f }, stage);

    SpawnObstacle<Pokey>({ -10.0f,0.0f,-150.0f }, stage);
    SpawnObstacle<Pokey>({ -80.0f,0.0f,-150.0f }, stage);
    SpawnObstacle<Pokey>({ -150.0f,0.0f,-150.0f }, stage);
    SpawnObstacle<Pokey>({ -210.0f,0.0f,-150.0f }, stage);

    SpawnObstacle<Pokey>({ -20.0f,0.0f,-50.0f }, stage);
    SpawnObstacle<Pokey>({ -50.0f,0.0f,-50.0f }, stage);
    SpawnObstacle<Pokey>({ -100.0f,0.0f,-50.0f }, stage);
    SpawnObstacle<Pokey>({ -160.0f,0.0f,-50.0f }, stage);
    SpawnObstacle<Macaron_Maccha>({ -150.0f,3.0f,0.0f }, stage);
    SpawnObstacle<Pokey>({ -15.0f,0.0f,100.0f }, stage);
    SpawnObstacle<Pokey>({ -90.0f,0.0f,100.0f }, stage);
    SpawnObstacle<Pokey>({ -180.0f,0.0f,100.0f }, stage);
    SpawnObstacle<Pokey>({ -220.0f,0.0f,100.0f }, stage);
    SpawnObstacle<Pokey>({ -50.0f,0.0f,230.0f }, stage);
    SpawnObstacle<Pokey>({ -120.0f,0.0f,230.0f }, stage);
    SpawnObstacle<Pokey>({ -190.0f,0.0f,230.0f }, stage);
    SpawnObstacle<Pokey>({ -230.0f,0.0f,230.0f }, stage);

    SpawnObstacle<Prits>({ 240.0f,0.0f,-240.0f }, stage);
    SpawnObstacle<Prits>({ 120.0f,0.0f,-240.0f }, stage);
    SpawnObstacle<Prits>({ 20.0f,0.0f,-240.0f }, stage);

    SpawnObstacle<Prits>({ 180.0f,0.0f,-180.0f }, stage);
    SpawnObstacle<Prits>({ 90.0f,0.0f,-180.0f }, stage);
    SpawnObstacle<Prits>({ 40.0f,0.0f,-180.0f }, stage);

    SpawnObstacle<Prits>({ 210.0f,0.0f,-90.0f }, stage);
    SpawnObstacle<Prits>({ 100.0f,0.0f,-90.0f }, stage);
    SpawnObstacle<Prits>({ 40.0f,0.0f,-90.0f }, stage);

    SpawnObstacle<Prits>({ 230.0f,0.0f,-10.0f }, stage);
    SpawnObstacle<Prits>({ 150.0f,0.0f,-10.0f }, stage);
    SpawnObstacle<Prits>({ 90.0f,0.0f,-10.0f }, stage);

    SpawnObstacle<Prits>({ 15.0f,0.0f,100.0f }, stage);
    SpawnObstacle<Prits>({ 70.0f,0.0f,100.0f }, stage);
    SpawnObstacle<Prits>({ 150.0f,0.0f,100.0f }, stage);
    SpawnObstacle<Prits>({ 210.0f,0.0f,100.0f }, stage);

    SpawnObstacle<Prits>({ 50.0f,0.0f,190.0f }, stage);
    SpawnObstacle<Prits>({ 100.0f,0.0f,190.0f }, stage);
    SpawnObstacle<Prits>({ 170.0f,0.0f,190.0f }, stage);
    SpawnObstacle<Prits>({ 240.0f,0.0f,190.0f }, stage);
}

void Stage::AreaInfo29(Stage* stage)
{
    SpawnObstacle<Cupcake_Choco>({ 120.0f,3.0f,-120.0f }, stage);
    SpawnObstacle<Pokey>({ 0.0f,0.0f,-150 }, stage);
    SpawnObstacle<Pokey>({ 25.0f,0.0f,-200.0f }, stage);
    SpawnObstacle<Pokey>({ 50.0f,0.0f,-200.0f }, stage);
    SpawnObstacle<Pokey>({ 75.0f,0.0f,-200.0f }, stage);
    SpawnObstacle<Pokey>({ -25.0f,0.0f,-200.0f }, stage);
    SpawnObstacle<Pokey>({ -50.0f,0.0f,-200.0f }, stage);
    SpawnObstacle<Pokey>({ -75.0f,0.0f,-200.0f }, stage);
    SpawnObstacle<Pokey>({ 125.0f,0.0f,-200.0f }, stage);
    SpawnObstacle<Pokey>({ 150.0f,0.0f,-200.0f }, stage);
    SpawnObstacle<Pokey>({ 175.0f,0.0f,-200.0f }, stage);
    SpawnObstacle<Pokey>({ -125.0f,0.0f,-200.0f }, stage);
    SpawnObstacle<Pokey>({ -150.0f,0.0f,-200.0f }, stage);
    SpawnObstacle<Pokey>({ -175.0f,0.0f,-200.0f }, stage);
    SpawnObstacle<Pokey>({ 200.0f,0.0f,-200.0f }, stage);
    SpawnObstacle<Pokey>({ 225.0f,0.0f,-200.0f }, stage);
    SpawnObstacle<Pokey>({ -200.0f,0.0f,-200.0f }, stage);
    SpawnObstacle<Pokey>({ -225.0f,0.0f,-200.0f }, stage);

    SpawnObstacle<Pokey>({ -100.0f,0.0f,-150.0f }, stage);
    SpawnObstacle<Pokey>({ 100.0f,0.0f,-150.0f }, stage);
    SpawnObstacle<Pokey>({ -155.0f,0.0f,-150.0f }, stage);
    SpawnObstacle<Pokey>({ 155.0f,0.0f,-150.0f }, stage);

    SpawnObstacle<Pokey>({ -40.0f,0.0f,-150.0f }, stage);
    SpawnObstacle<Pokey>({ 40.0f,0.0f,-150.0f }, stage);
    SpawnObstacle<Pokey>({ -185.0f,0.0f,-150.0f }, stage);
    SpawnObstacle<Pokey>({ 185.0f,0.0f,-150.0f }, stage);
    SpawnObstacle<Pokey>({ -215.0f,0.0f,-150.0f }, stage);
    SpawnObstacle<Pokey>({ 215.0f,0.0f,-150.0f }, stage);
    SpawnObstacle<Pokey>({ -235.0f,0.0f,-50.0f }, stage);
    SpawnObstacle<Pokey>({ 235.0f,0.0f,-50.0f }, stage);
    SpawnObstacle<Pokey>({ -75.0f,0.0f,-50.0f }, stage);
    SpawnObstacle<Pokey>({ 75.0f,0.0f,-50.0f }, stage);
    SpawnObstacle<Pokey>({ -45.0f,0.0f,-50.0f }, stage);
    SpawnObstacle<Pokey>({ 45.0f,0.0f,-50.0f }, stage);
    SpawnObstacle<Pokey>({ 124.0f,0.0f,-50.0f }, stage);
    SpawnObstacle<Pokey>({ -124.0f,0.0f,-50.0f }, stage);

    SpawnObstacle<Pokey>({ -70.0f,0.0f,50.0f }, stage);
    SpawnObstacle<Pokey>({ 70.0f,0.0f,50.0f }, stage);
    SpawnObstacle<Pokey>({ -25.0f,0.0f,50.0f }, stage);
    SpawnObstacle<Pokey>({ 25.0f,0.0f,50.0f }, stage);
    SpawnObstacle<Pokey>({ 120.0f,0.0f,50.0f }, stage);
    SpawnObstacle<Pokey>({ -120.0f,0.0f,50.0f }, stage);
    SpawnObstacle<Pokey>({ 195.0f,0.0f,50.0f }, stage);
    SpawnObstacle<Pokey>({ -195.0f,0.0f,50.0f }, stage);


    SpawnObstacle<Pokey>({ 0.0f,0.0f,150.0f }, stage);
    SpawnObstacle<Pokey>({ -50.0f,0.0f,150.0f }, stage);
    SpawnObstacle<Pokey>({ 50.0f,0.0f,150.0f }, stage);
    SpawnObstacle<Pokey>({ -100.0f,0.0f,150.0f }, stage);
    SpawnObstacle<Pokey>({ 100.0f,0.0f,150.0f }, stage);
    SpawnObstacle<Pokey>({ 150.0f,0.0f,150.0f }, stage);
    SpawnObstacle<Pokey>({ -150.0f,0.0f,150.0f }, stage);
    SpawnObstacle<Pokey>({ 200.0f,0.0f,150.0f }, stage);
    SpawnObstacle<Pokey>({ -200.0f,0.0f,150.0f }, stage);
    SpawnObstacle<Pokey>({ 233.0f,0.0f,150.0f }, stage);
    SpawnObstacle<Pokey>({ -233.0f,0.0f,150.0f }, stage);

}

void Stage::AreaInfo30(Stage* stage)
{
    SpawnObstacle<Pokey>({ 0.0f,0.0f,-100.0f }, stage);
    SpawnObstacle<Pokey>({ 75.0f,0.0f,-100.0f }, stage);
    SpawnObstacle<Pokey>({ -75.0f,0.0f,-100.0f }, stage);
    SpawnObstacle<Pokey>({ 125.0f,0.0f,-60.0f }, stage);
    SpawnObstacle<Pokey>({ -125.0f,0.0f,-60.0f }, stage);
    SpawnObstacle<Pokey>({ 225.0f,0.0f,-30.0f }, stage);
    SpawnObstacle<Pokey>({ -225.0f,0.0f,-30.0f }, stage);
    SpawnObstacle<Pokey>({ 110.0f,0.0f,90.0f }, stage);
    SpawnObstacle<Pokey>({ -110.0f,0.0f,-90.0f }, stage);
    SpawnObstacle<Pokey>({ 25.0f,0.0f,-60.0f }, stage);
    SpawnObstacle<Pokey>({ -25.0f,0.0f,-60.0f }, stage);
    SpawnObstacle<Pokey>({ 25.0f,0.0f,-160.0f }, stage);
    SpawnObstacle<Pokey>({ -25.0f,0.0f,-160.0f }, stage);
    SpawnObstacle<Pokey>({ 180.0f,0.0f,-200.0f }, stage);
    SpawnObstacle<Pokey>({ -180.0f,0.0f,-200.0f }, stage);
    SpawnObstacle<Pokey>({ 20.0f,0.0f,-240.0f }, stage);
    SpawnObstacle<Pokey>({ -20.0f,0.0f,-240.0f }, stage);
    SpawnObstacle<Pokey>({ 15.0f,0.0f,180.0f }, stage);
    SpawnObstacle<Pokey>({ -15.0f,0.0f,180.0f }, stage);

    SpawnObstacle<Pokey>({ -50.0f,0.0f,0.0f }, stage);
    SpawnObstacle<Pokey>({ 50.0f,0.0f,0.0f }, stage);
    SpawnObstacle<Pokey>({ -25.0f,0.0f,0.0f }, stage);
    SpawnObstacle<Pokey>({ 25.0f,0.0f,0.0f }, stage);
    SpawnObstacle<Pokey>({ -25.0f,35.5f,0.0f }, stage);
    SpawnObstacle<Pokey>({ 25.0f,35.5f,0.0f }, stage);
    SpawnObstacle<Pokey>({ -15.0f,71.0f,0.0f }, stage);
    SpawnObstacle<Pokey>({ 15.0f,71.0f,0.0f }, stage);
    SpawnObstacle<Pokey>({ 0.0f,106.5f,0.0f }, stage);

    SpawnObstacle<Pokey>({ 35.0f,35.0f,50.0f }, stage);
    SpawnObstacle<Pokey>({ 50.0f,0.0f,50.0f }, stage);
    SpawnObstacle<Pokey>({ 65.0f,35.0f,50.0f }, stage);
    SpawnObstacle<Pokey>({ 85.0f,35.0f,100.0f }, stage);
    SpawnObstacle<Pokey>({ 100.0f,0.0f,100.0f }, stage);
    SpawnObstacle<Pokey>({ 115.0f,35.0f,100.0f }, stage);
    SpawnObstacle<Pokey>({ -35.0f,35.0f,50.0f }, stage);
    SpawnObstacle<Pokey>({ -50.0f,0.0f,50.0f }, stage);
    SpawnObstacle<Pokey>({ -65.0f,35.0f,50.0f }, stage);
    SpawnObstacle<Pokey>({ -115.0f,35.0f,100.0f }, stage);
    SpawnObstacle<Pokey>({ -100.0f,0.0f,100.0f }, stage);
    SpawnObstacle<Pokey>({ -85.0f,35.0f,100.0f }, stage);
    SpawnObstacle<Pokey>({ -135.0f,35.0f,200.0f }, stage);
    SpawnObstacle<Pokey>({ -150.0f,0.0f,200.0f }, stage);
    SpawnObstacle<Pokey>({ -165.0f,35.0f,200.0f }, stage);
    SpawnObstacle<Pokey>({ 150.0f,0.0f,200.0f }, stage);
    SpawnObstacle<Pokey>({ -230.0f,0.0f,230.0f }, stage);
    SpawnObstacle<Pokey>({ 230.0f,0.0f,230.0f }, stage);
    SpawnObstacle<Cupcake_Choco>({ 0.0f,3.0f,0.0f }, stage);
    SpawnObstacle<Pokey>({ 240.0f,0.0f,-140.0f }, stage);
    SpawnObstacle<Pokey>({ -240.0f,0.0f,-140.0f }, stage);

    SpawnObstacle<Pokey>({ -95.0f,0.0f,120.0f }, stage);
    SpawnObstacle<Pokey>({ 95.0f,0.0f,120.0f }, stage);

    SpawnObstacle<Pokey>({ -195.0f,0.0f,170.0f }, stage);
    SpawnObstacle<Pokey>({ 195.0f,0.0f,170.0f }, stage);

    SpawnObstacle<Pokey>({ -225.0f,0.0f,200.0f }, stage);
    SpawnObstacle<Pokey>({ 225.0f,0.0f,200.0f }, stage);
}

void Stage::AreaInfo31(Stage* stage)
{
    SpawnObstacle<Pokey>({ 0.0f,0.0f,-150 }, stage);
    SpawnObstacle<Pokey>({ 25.0f,0.0f,-200.0f }, stage);
    SpawnObstacle<Pokey>({ 50.0f,0.0f,-200.0f }, stage);
    SpawnObstacle<Pokey>({ 75.0f,0.0f,-200.0f }, stage);
    SpawnObstacle<Pokey>({ -25.0f,0.0f,-200.0f }, stage);
    SpawnObstacle<Pokey>({ -50.0f,0.0f,-200.0f }, stage);
    SpawnObstacle<Pokey>({ -75.0f,0.0f,-200.0f }, stage);
    SpawnObstacle<Pokey>({ 125.0f,0.0f,-200.0f }, stage);
    SpawnObstacle<Pokey>({ 150.0f,0.0f,-200.0f }, stage);
    SpawnObstacle<Pokey>({ 175.0f,0.0f,-200.0f }, stage);
    SpawnObstacle<Pokey>({ -125.0f,0.0f,-200.0f }, stage);
    SpawnObstacle<Pokey>({ -150.0f,0.0f,-200.0f }, stage);
    SpawnObstacle<Pokey>({ -175.0f,0.0f,-200.0f }, stage);
    SpawnObstacle<Pokey>({ 200.0f,0.0f,-200.0f }, stage);
    SpawnObstacle<Pokey>({ 225.0f,0.0f,-200.0f }, stage);
    SpawnObstacle<Pokey>({ -200.0f,0.0f,-200.0f }, stage);
    SpawnObstacle<Pokey>({ -225.0f,0.0f,-200.0f }, stage);

    SpawnObstacle<Pokey>({ -230.0f,0.0f,-100.0f }, stage);
    SpawnObstacle<Pokey>({ 230.0f,0.0f,-100.0f }, stage);
    SpawnObstacle<Pokey>({ -180.0f,0.0f,-100.0f }, stage);
    SpawnObstacle<Pokey>({ 180.0f,0.0f,-100.0f }, stage);
    SpawnObstacle<Pokey>({ -120.0f,0.0f,-100.0f }, stage);
    SpawnObstacle<Pokey>({ 120.0f,0.0f,-100.0f }, stage);
    SpawnObstacle<Pokey>({ -50.0f,0.0f,-100.0f }, stage);
    SpawnObstacle<Pokey>({ 50.0f,0.0f,-100.0f }, stage);
    SpawnObstacle<Pokey>({ -40.0f,0.0f,0.0f }, stage);
    SpawnObstacle<Pokey>({ 40.0f,0.0f,-0.0f }, stage);
    SpawnObstacle<Pokey>({ -100.0f,0.0f,0.0f }, stage);
    SpawnObstacle<Pokey>({ 100.0f,0.0f,-0.0f }, stage);
    SpawnObstacle<Pokey>({ -180.0f,0.0f,0.0f }, stage);
    SpawnObstacle<Pokey>({ 180.0f,0.0f,-0.0f }, stage);
    SpawnObstacle<Pokey>({ -225.0f,0.0f,0.0f }, stage);
    SpawnObstacle<Pokey>({ 225.0f,0.0f,-0.0f }, stage);
    SpawnObstacle<Pokey>({ 0.0f,0.0f,0.0f }, stage);

    SpawnObstacle<Pokey>({ -55.0f,0.0f,100.0f }, stage);
    SpawnObstacle<Pokey>({ 55.0f,0.0f,100.0f }, stage);
    SpawnObstacle<Pokey>({ -105.0f,0.0f,100.0f }, stage);
    SpawnObstacle<Pokey>({ 105.0f,0.0f,100.0f }, stage);
    SpawnObstacle<Pokey>({ -155.0f,0.0f,100.0f }, stage);
    SpawnObstacle<Pokey>({ 155.0f,0.0f,100.0f }, stage);

    SpawnObstacle<Pokey>({ -25.0f,0.0f,200.0f }, stage);
    SpawnObstacle<Pokey>({ 25.0f,0.0f,200.0f }, stage);
    SpawnObstacle<Pokey>({ -130.0f,0.0f,200.0f }, stage);
    SpawnObstacle<Pokey>({ 130.0f,0.0f,200.0f }, stage);
    SpawnObstacle<Pokey>({ -195.0f,0.0f,200.0f }, stage);
    SpawnObstacle<Pokey>({ 195.0f,0.0f,200.0f }, stage);
}

void Stage::AreaInfo32(Stage* stage)
{
    SpawnObstacle<Prits>({ -235.0f,0.0f,-230.0f }, stage);
    SpawnObstacle<Prits>({ 235.0f,0.0f,-230.0f }, stage);
    SpawnObstacle<Prits>({ 210.0f,0.0f,-230.0f }, stage);
    SpawnObstacle<Prits>({ -210.0f,0.0f,-230.0f }, stage);
    SpawnObstacle<Prits>({ 190.0f,8.0f,-230.0f }, stage);
    SpawnObstacle<Prits>({ -190.0f,8.0f,-230.0f }, stage);
    SpawnObstacle<Prits>({ 170.0f,0.0f,-230.0f }, stage);
    SpawnObstacle<Prits>({ -170.0f,0.0f,-230.0f }, stage);
    SpawnObstacle<Prits>({ 145.0f,0.0f,-230.0f }, stage);
    SpawnObstacle<Prits>({ -145.0f,0.0f,-230.0f }, stage);
    SpawnObstacle<Prits>({ 0.0f,8.0f,0.0f }, stage);
    SpawnObstacle<Prits>({ 20.0f,0.0f,0.0f }, stage);
    SpawnObstacle<Prits>({ -20.0f,0.0f,0.0f }, stage);
    SpawnObstacle<Prits>({ 20.0f,0.0f,50.0f }, stage);
    SpawnObstacle<Prits>({ -20.0f,0.0f,50.0f }, stage);
    SpawnObstacle<Prits>({ 25.0f,0.0f,100.0f }, stage);
    SpawnObstacle<Prits>({ -25.0f,0.0f,100.0f }, stage);
    SpawnObstacle<Prits>({ 50.0f,0.0f,100.0f }, stage);
    SpawnObstacle<Prits>({ -50.0f,0.0f,100.0f }, stage);
    SpawnObstacle<Prits>({ 75.0f,0.0f,100.0f }, stage);
    SpawnObstacle<Prits>({ -75.0f,0.0f,100.0f }, stage);
    SpawnObstacle<Prits>({ 100.0f,0.0f,100.0f }, stage);
    SpawnObstacle<Prits>({ -100.0f,0.0f,100.0f }, stage);
    SpawnObstacle<Prits>({ 50.0f,0.0f,-150.0f }, stage);
    SpawnObstacle<Prits>({ -50.0f,0.0f,-150.0f }, stage);
    SpawnObstacle<Prits>({ 150.0f,0.0f,-150.0f }, stage);
    SpawnObstacle<Prits>({ -150.0f,0.0f,-150.0f }, stage);

    SpawnObstacle<Prits>({ 100.0f,0.0f,-50.0f }, stage);
    SpawnObstacle<Prits>({ -100.0f,0.0f,-50.0f }, stage);
    SpawnObstacle<Prits>({ 60.0f,0.0f,-230.0f }, stage);
    SpawnObstacle<Prits>({ -60.0f,0.0f,-230.0f }, stage);

    SpawnObstacle<Prits>({ -160.0f,0.0f,-180.0f }, stage);
    SpawnObstacle<Prits>({ 160.0f,0.0f,-180.0f }, stage);
    SpawnObstacle<Prits>({ -170.0f,0.0f,-150.0f }, stage);
    SpawnObstacle<Prits>({ 170.0f,0.0f,-150.0f }, stage);
    SpawnObstacle<Prits>({ -180.0f,0.0f,-130.0f }, stage);
    SpawnObstacle<Prits>({ 180.0f,0.0f,-130.0f }, stage);
    SpawnObstacle<Prits>({ -190.0f,0.0f,-110.0f }, stage);
    SpawnObstacle<Prits>({ 190.0f,0.0f,-110.0f }, stage);
    SpawnObstacle<Prits>({ -210.0f,0.0f,-90.0f }, stage);
    SpawnObstacle<Prits>({ 210.0f,0.0f,-90.0f }, stage);
    SpawnObstacle<Marshmallow_Blue>({ 190.0f,3.0f,-230.0f }, stage);
    SpawnObstacle<Marshmallow_Blue>({ -190.0f,3.0f,-230.0f }, stage);
    SpawnObstacle<Marshmallow_Blue>({ 0.0f,3.0f,0.0f }, stage);
}

void Stage::AreaInfo33(Stage* stage)
{

}

void Stage::AreaInfo34(Stage* stage)
{

}

void Stage::AreaInfo35(Stage* stage)
{

}

void Stage::AreaInfo36(Stage* stage)
{

}

void Stage::AreaInfo37(Stage* stage)
{

}

void Stage::AreaInfo38(Stage* stage)
{

}

void Stage::AreaInfo39(Stage* stage)
{

}

void Stage::AreaInfo40(Stage* stage)
{
    SpawnObstacle<Grape_can>({ 30.0f,0.0f,-90.0f }, stage);
    SpawnObstacle<Grape_can>({ 30.0f,0.0f,90.0f }, stage);
    SpawnObstacle<Grape_can>({ 30.0f,0.0f,-70.0f }, stage);
    SpawnObstacle<Grape_can>({ 30.0f,0.0f,70.0f }, stage);
    SpawnObstacle<Grape_can>({ 30.0f,0.0f,-50.0f }, stage);
    SpawnObstacle<Grape_can>({ 30.0f,0.0f,50.0f }, stage);
    SpawnObstacle<Grape_can>({ 30.0f,0.0f,-30.0f }, stage);
    SpawnObstacle<Grape_can>({ 30.0f,0.0f,30.0f }, stage);
    SpawnObstacle<Grape_can>({ 30.0f,0.0f,-10.0f }, stage);
    SpawnObstacle<Grape_can>({ 30.0f,0.0f,10.0f }, stage);

    SpawnObstacle<Grape_can>({ 20.0f,0.0f,10.0f }, stage);
    SpawnObstacle<Grape_can>({ 10.0f,0.0f,10.0f }, stage);
    SpawnObstacle<Grape_can>({ 0.0f,0.0f,10.0f }, stage);
    SpawnObstacle<Grape_can>({ -20.0f,0.0f,-90.0f }, stage);
    SpawnObstacle<Grape_can>({ -10.0f,0.0f,-90.0f }, stage);
    SpawnObstacle<Grape_can>({ 0.0f,0.0f,-90.0f }, stage);

    SpawnObstacle<Grape_can>({ -20.0f,0.0f,90.0f }, stage);
    SpawnObstacle<Grape_can>({ -10.0f,0.0f,90.0f }, stage);
    SpawnObstacle<Grape_can>({ 0.0f,0.0f,90.0f }, stage);
    SpawnObstacle<Grape_can>({ -42.0f,0.0f,-90.0f }, stage);
    SpawnObstacle<Grape_can>({ -54.0f,0.0f,-90.0f }, stage);
    SpawnObstacle<Grape_can>({ -66.0f,0.0f,-90.0f }, stage);
    SpawnObstacle<Grape_can>({ -78.0f,0.0f,-90.0f }, stage);
    SpawnObstacle<Grape_can>({ -90.0f,0.0f,-90.0f }, stage);
    SpawnObstacle<Grape_can>({ -102.0f,0.0f,-90.0f }, stage);
    SpawnObstacle<Grape_can>({ -114.0f,0.0f,-90.0f }, stage);
    SpawnObstacle<Grape_can>({ -126.0f,0.0f,-90.0f }, stage);

    SpawnObstacle<Grape_can>({ -174.0f,0.0f,-90.0f }, stage);
    SpawnObstacle<Grape_can>({ -174.0f,0.0f,-70.0f }, stage);
    SpawnObstacle<Grape_can>({ -174.0f,0.0f,-50.0f }, stage);
    SpawnObstacle<Grape_can>({ -174.0f,0.0f,-30.0f }, stage);
    SpawnObstacle<Grape_can>({ -174.0f,0.0f,-10.0f }, stage);
    SpawnObstacle<Grape_can>({ -174.0f,0.0f,10.0f }, stage);
    SpawnObstacle<Grape_can>({ -174.0f,0.0f,30.0f }, stage);
    SpawnObstacle<Grape_can>({ -174.0f,0.0f,50.0f }, stage);
    SpawnObstacle<Grape_can>({ -174.0f,0.0f,70.0f }, stage);
    SpawnObstacle<Grape_can>({ -174.0f,0.0f,90.0f }, stage);
    SpawnObstacle<Grape_can>({ -162.0f,0.0f,-10.0f }, stage);
    SpawnObstacle<Grape_can>({ -150.0f,0.0f,-10.0f }, stage);
    SpawnObstacle<Grape_can>({ -138.0f,0.0f,-10.0f }, stage);
    SpawnObstacle<Grape_can>({ -126.0f,0.0f,-10.0f }, stage);
    SpawnObstacle<Grape_can>({ -114.0f,0.0f,-10.0f }, stage);
    SpawnObstacle<Grape_can>({ -86.0f,0.0f,-10.0f }, stage);

    SpawnObstacle<Grape_can>({ -42.0f,0.0f,90.0f }, stage);
    SpawnObstacle<Grape_can>({ -54.0f,0.0f,90.0f }, stage);
    SpawnObstacle<Grape_can>({ -66.0f,0.0f,90.0f }, stage);
    SpawnObstacle<Grape_can>({ -78.0f,0.0f,90.0f }, stage);
    SpawnObstacle<Grape_can>({ -90.0f,0.0f,90.0f }, stage);
    SpawnObstacle<Grape_can>({ -102.0f,0.0f,90.0f }, stage);
    SpawnObstacle<Grape_can>({ -174.0f,0.0f,90.0f }, stage);
    SpawnObstacle<Grape_can>({ -162.0f,0.0f,90.0f }, stage);
    SpawnObstacle<Grape_can>({ -150.0f,0.0f,90.0f }, stage);
    SpawnObstacle<Marshmallow_Pink>({ -126.0f,3.0f,110.0f }, stage);
    SpawnObstacle<Candy_gate>({ -126.0f,0.0f,90.0f }, stage);
    SpawnObstacle<Grape_can>({ 42.0f,0.0f,-50.0f }, stage);
    SpawnObstacle<Grape_can>({ 54.0f,0.0f,-20.0f }, stage);
    SpawnObstacle<Grape_can>({ 66.0f,0.0f,40.0f }, stage);
    SpawnObstacle<Grape_can>({ 78.0f,0.0f,90.0f }, stage);
    SpawnObstacle<Grape_can>({ 90.0f,0.0f,140.0f }, stage);
    SpawnObstacle<Grape_can>({ 102.0f,0.0f,190.0f }, stage);
    SpawnObstacle<Grape_can>({ 114.0f,0.0f,240.0f }, stage);


    SpawnObstacle<Grape_can>({ -30.0f,0.0f,-90.0f }, stage);
    SpawnObstacle<Grape_can>({ -30.0f,0.0f,90.0f }, stage);
    SpawnObstacle<Grape_can>({ -30.0f,0.0f,-70.0f }, stage);
    SpawnObstacle<Grape_can>({ -30.0f,0.0f,70.0f }, stage);
    SpawnObstacle<Grape_can>({ -30.0f,0.0f,-50.0f }, stage);
    SpawnObstacle<Grape_can>({ -30.0f,0.0f,50.0f }, stage);
    SpawnObstacle<Grape_can>({ -30.0f,0.0f,-30.0f }, stage);
    SpawnObstacle<Grape_can>({ -30.0f,0.0f,30.0f }, stage);
    SpawnObstacle<Grape_can>({ -30.0f,0.0f,-10.0f }, stage);
    SpawnObstacle<Grape_can>({ -30.0f,0.0f,10.0f }, stage);
    SpawnObstacle<Grape_can>({ -30.0f,0.0f,100.0f }, stage);
    SpawnObstacle<Grape_can>({ -30.0f,0.0f,110.0f }, stage);
    SpawnObstacle<Grape_can>({ -30.0f,0.0f,120.0f }, stage);
    SpawnObstacle<Grape_can>({ -30.0f,0.0f,130.0f }, stage);
    SpawnObstacle<Grape_can>({ -30.0f,0.0f,140.0f }, stage);
    SpawnObstacle<Grape_can>({ -30.0f,0.0f,150.0f }, stage);
    SpawnObstacle<Grape_can>({ -30.0f,0.0f,160.0f }, stage);
    SpawnObstacle<Grape_can>({ -20.0f,0.0f,160.0f }, stage);
    SpawnObstacle<Candy_gate>({ 0.0f,0.0f,160.0f }, stage);
    SpawnObstacle<Grape_can>({ 30.0f,0.0f,100.0f }, stage);
    SpawnObstacle<Grape_can>({ 30.0f,0.0f,110.0f }, stage);
    SpawnObstacle<Grape_can>({ 30.0f,0.0f,120.0f }, stage);
    SpawnObstacle<Grape_can>({ 30.0f,0.0f,130.0f }, stage);
    SpawnObstacle<Grape_can>({ 30.0f,0.0f,140.0f }, stage);
    SpawnObstacle<Grape_can>({ 30.0f,0.0f,150.0f }, stage);
    SpawnObstacle<Grape_can>({ 30.0f,0.0f,160.0f }, stage);
    SpawnObstacle<Grape_can>({ 20.0f,0.0f,160.0f }, stage);
    SpawnObstacle<Marshmallow_Pink>({ 0.0f,3.0f,180.0f }, stage);
}

// デバッグ用エリア
void Stage::AreaInfoDebug(Stage* stage)
{
    //SpawnObstacle<Marshmallow_Blue>({ 0.0f,0.0f,0.0f }, stage);
    //SpawnObstacle<Marshmallow_Blue>({ 20.0f,0.0f,0.0f }, stage);
    //SpawnObstacle<Marshmallow_Blue>({ 40.0f,0.0f,0.0f }, stage);
    //SpawnObstacle<Marshmallow_Blue>({ 60.0f,0.0f,0.0f }, stage);

    SpawnObstacle<Macaron_Maccha>({ 0.0f,0.0f,0.0f }, stage);
    SpawnObstacle<Macaron_Maccha>({ 100.0f,0.0f,0.0f }, stage);

    SpawnObstacle<Macaron_Maccha>({ 0.0f,3.0f,20.0f }, stage);
}


// === 以下デバッグ用関数 ===
int Stage::ObstacleNumber = husen_gum;
void Stage::StageInfoDebug(Stage* stage,int n)
{
    switch (n)
    {
    case cola:
        SpawnObstacle<Cola>({ 0.0f,0.0f,0.0f }, stage);
        break;
    case pokey:
        SpawnObstacle<Pokey>({ 0.0f,0.0f,0.0f }, stage);
        break;
    case prits:
        SpawnObstacle<Prits>({ 0.0f,0.0f,0.0f }, stage);
        break;
    case marshmallow_Blue:
        SpawnObstacle<Marshmallow_Blue>({ 0.0f,0.0f,0.0f }, stage);
        break;
    case marshmallow_Pink:
        SpawnObstacle<Marshmallow_Pink>({ 0.0f,0.0f,0.0f }, stage);
        break;
    case jellybeans_Yellow:
        SpawnObstacle<Jellybeans_Yellow>({ 0.0f,0.0f,0.0f }, stage);
        break;
    case jellybeans_Pink:
        SpawnObstacle<Jellybeans_Pink>({ 0.0f,0.0f,0.0f }, stage);
        break;
    case jellybeans_Green:
        SpawnObstacle<Jellybeans_Green>({ 0.0f,0.0f,0.0f }, stage);
        break;
    case jellybeans_Orange:
        SpawnObstacle<Jellybeans_Orange>({ 0.0f,5.0f,0.0f }, stage);
        break;
    case chocolate_ball:
        SpawnObstacle<Chocolate_ball>({ 0.0f,0.0f,0.0f }, stage);
        break;
    case grape_can:
        SpawnObstacle<Grape_can>({ 0.0f,0.0f,0.0f }, stage);
        break;
    case orange_gum:
        SpawnObstacle<Orange_gum>({ 0.0f,0.0f,0.0f }, stage);
        break;
    case husen_gum:
        SpawnObstacle<Husen_gum>({ 0.0f,0.0f,0.0f }, stage);
        break;
    case candy_gate:
        SpawnObstacle<Candy_gate>({ 0.0f,0.0f,0.0f }, stage);
        break;
    case orange_can:
        SpawnObstacle<Orange_can>({ 0.0f,0.0f,0.0f }, stage);
        break;
    case marble_chocolate:
        SpawnObstacle<Marble_chocolate>({ 0.0f,0.0f,0.0f }, stage);
        break;
    case cupcake_Choco:
        SpawnObstacle<Cupcake_Choco>({ 0.0f,0.0f,0.0f }, stage);
        break;
    case cupcake_Pink:
        SpawnObstacle<Cupcake_Pink>({ 0.0f,0.0f,0.0f }, stage);
        break;
    case pudding:
        SpawnObstacle<Pudding>({ 0.0f,0.0f,0.0f }, stage);
        break;
    case macaron_Maccha:
        SpawnObstacle<Macaron_Maccha>({ 0.0f,0.0f,0.0f }, stage);
        break;
    case macaron_Ping:
        SpawnObstacle<Macaron_Pink>({ 0.0f,0.0f,0.0f }, stage);
        break;
    }
}


// 深度ステンシル
namespace
{
    const char* obstacle_name[] =
    {
        "cola",
        "pokey",
        "prits",
        "marshmallow_Blue",
        "marshmallow_Pink",
        "jellybeans_Yellow",
        "jellybeans_Pink",
        "jellybeans_Green",
        "jellybeans_Orange",
        "chocolate_ball",
        "grape_can",
        "orange_gum",
        "husen_gum",
        "candy_gate",
        "orange_can",
        "marble_chocolate",
        "cupcake_Choco",
        "cupcake_Pink",
        "pudding",
        "macaron_Maccha",
        "macaron_Pink",
    };  
    const char* OBSTACLE_NAME = obstacle_name[0];
}

//デバッグGUI描画
void Stage::DrawDebugGUI_()
{
    ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(ImVec2(300, 300), ImGuiCond_FirstUseEver);

    if (ImGui::Begin("Stage", nullptr, ImGuiWindowFlags_None))
    {
        // 生成オブジェクトの設定
        if (ImGui::BeginCombo("SpawnItem", OBSTACLE_NAME, ImGuiComboFlags_NoArrowButton))
        {
            for (int n = 0; n < IM_ARRAYSIZE(obstacle_name); n++)
            {
                bool is_selected = (OBSTACLE_NAME == obstacle_name[n]);
                if (ImGui::Selectable(obstacle_name[n]))
                {
                    ObstacleNumber = n;
                    OBSTACLE_NAME = obstacle_name[n];
                }
                if (is_selected) ImGui::SetItemDefaultFocus();
            }
            ImGui::EndCombo();
        }
    }
    ImGui::End();
}