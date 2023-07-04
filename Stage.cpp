#include "Stage.h"
#include "SceneManager.h"
#include<imgui.h>
//-------------------------------------------------------------------------------------------------------
// 
//		 ステージ
// 
//-------------------------------------------------------------------------------------------------------

Stage::SpawnObstacleInfo Stage::StageNONE[] =
{
    {AreaInfo00,Stage::SpawnLevel::low}
    ,{AreaInfo00,Stage::SpawnLevel::middle}
    ,{AreaInfo00,Stage::SpawnLevel::high}

    ,{nullptr,0} // END
};

Stage::SpawnObstacleInfo Stage::StageInfo01[] =
{
    {AreaInfo02,Stage::SpawnLevel::low}
    ,{AreaInfo02,Stage::SpawnLevel::middle}
    ,{AreaInfo02,Stage::SpawnLevel::high}

    ,{nullptr,0} // END
};
Stage::SpawnObstacleInfo Stage::StageInfo02[] =
{
    {AreaInfo02,Stage::SpawnLevel::high}
    ,{AreaInfo02,Stage::SpawnLevel::middle}
    ,{AreaInfo02,Stage::SpawnLevel::low}

    ,{nullptr,0} // END
};
Stage::SpawnObstacleInfo Stage::StageInfo03[] =
{
    {AreaInfo02,Stage::SpawnLevel::high}
    ,{AreaInfo02,Stage::SpawnLevel::middle}
    ,{AreaInfo02,Stage::SpawnLevel::low}

    ,{nullptr,0} // END
};
Stage::SpawnObstacleInfo Stage::StageInfo04[] =
{
    {AreaInfo02,Stage::SpawnLevel::high}
    ,{AreaInfo02,Stage::SpawnLevel::middle}
    ,{AreaInfo02,Stage::SpawnLevel::low}

    ,{nullptr,0} // END
};
Stage::SpawnObstacleInfo Stage::StageInfo05[] =
{
    {AreaInfo02,Stage::SpawnLevel::high}
    ,{AreaInfo02,Stage::SpawnLevel::middle}
    ,{AreaInfo02,Stage::SpawnLevel::low}

    ,{nullptr,0} // END
};

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
Stage::Stage(int stageNo)
{
    stageNo = (std::min)(stageNo, StageMax);

    //ステージモデルを読み込み
    model = std::make_unique<Model>("Data/Model/Debug/cube.mdl");

    // 初期設定
    scale = { StageSize,0.5f ,StageSize };
    stageSideMax = StageSideMax;
    stageDepthMax = StageDepthMax;

    //if (SceneManager::Instance().IsNoneStage || stageNo < 0)
    //{
    //    AreaInfo infoN = RandSpawn(StageNONE);
    //    infoN(this);
    //}
    //else 
    //{
    //    //AreaInfo info = RandSpawn(stageInfo[stageNo]);
    //    AreaInfo info = RandSpawn(StageDebug[stageNo]);
    //    info(this);
    //}

    StageInfoDebug(this,ObstacleNumber);
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
    if (DepthSpawn()) SpawnStageCount++;    // ステージ生成数増加
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

// ステージ01
void Stage::AreaInfo01(Stage* stage)
{
    SpawnObstacle<Cola>({ -10.0f,0.0f,0.0f }, stage);
    SpawnObstacle<Cola>({ 0.0f,0.0f,0.0f }, stage);
    SpawnObstacle<Candy_gate>({ 10.0f,0.0f,0.0f }, stage);
}

// ステージ02
void Stage::AreaInfo02(Stage* stage)
{
    SpawnObstacle<Pokey>({ 0.0f,0.0f,0.0f }, stage);
    SpawnObstacle<Candy_gate>({ 100.0f,0.0f,0.0f }, stage);
    
    SpawnObstacle<Macaron_Maccha>({ 0.0f,3.0f,20.0f }, stage);
}

// エリア03
void Stage::AreaInfo03(Stage* stage)
{
    SpawnObstacle<Cupcake_Choco>({ 0.0f,0.0f,0.0f }, stage);
}

void Stage::AreaInfoDebug(Stage* stage)
{
    //SpawnObstacle<Marshmallow_Blue>({ 0.0f,0.0f,0.0f }, stage);
    //SpawnObstacle<Marshmallow_Blue>({ 20.0f,0.0f,0.0f }, stage);
    //SpawnObstacle<Marshmallow_Blue>({ 40.0f,0.0f,0.0f }, stage);
    //SpawnObstacle<Marshmallow_Blue>({ 60.0f,0.0f,0.0f }, stage);

    SpawnObstacle<Pokey>({ 0.0f,0.0f,0.0f }, stage);
    SpawnObstacle<Candy_gate>({ 100.0f,0.0f,0.0f }, stage);

    SpawnObstacle<Macaron_Maccha>({ 0.0f,3.0f,20.0f }, stage);
}


// === 以下デバッグ用関数 ===
int Stage::ObstacleNumber = marble_chocolate;
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