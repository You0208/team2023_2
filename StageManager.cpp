#include "StageManager.h"
#include<imgui.h>
#include <Input/Input.h>

// コンストラクタ
StageManager::StageManager()
{
    // 初期速度設定
    stageScrollVelocity.z = MaxStageScrollVelocity[1];
    terrainScrollVelocity.z = MaxTerrainScrollVelocity[1];
}

// デストラクタ
StageManager::~StageManager()
{
    Clear();
}

void StageManager::DrawDebugGUI()
{
    Stage::DrawDebugGUI_();

    ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(ImVec2(300, 300), ImGuiCond_FirstUseEver);

    if (ImGui::Begin("StageManager", nullptr, ImGuiWindowFlags_None))
    {
        ImGui::SliderFloat("scrollVelocityZ", &stageScrollVelocity.z, 0.0f, -300.0f);
        ImGui::SliderFloat("terrainScrollVelocityZ", &terrainScrollVelocity.z, 0.0f, -300.0f);
    }

    ImGui::Text("SpawnStageCount:%ld", GetSpawnStageCount());
    ImGui::Text("stageNo:%ld", stageNo);

    ImGui::Text("[I][J][K][L] : camera");
    ImGui::Text("[A][D] : player");
    ImGui::Text("[X] : HitAnime");
    ImGui::Text("[C] : pause");

    ImGui::End();
}

// 更新処理
void StageManager::Update(Player* player, float elapsedTIme)
{
    // プレイヤーのダメージアニメ再生は以下の処理を行わない
    if(player->GetIsDamageAnim()) return;

    // ステージ切り替え
    ChangeStage();

    // 移動入力処理
    InputMove(elapsedTIme);

    // 速度処理更新
    UpdateVelocity(elapsedTIme, player);

    // ステージの更新
    StageUpdate(elapsedTIme);

    // 地形更新
    TerrainUpdate(elapsedTIme);
}

// 描画処理
void StageManager::Draw(RenderContext rc, ModelShader* shader)
{
    // ステージ描画
    for (BaseStage* stage : stages)
    {
        stage->Draw(rc, shader);
    }

    // 地形描画
    for (BaseStage* terrain : terrains)
    {
        terrain->Draw(rc, shader);
    }
}

void StageManager::ObsDraw(RenderContext rc, ModelShader* shader)
{   // ステージ描画
    for (BaseStage* stage : stages)
    {
        for (auto& it : stage->obstacles)
        {
            it->Draw(rc, shader);
        }
    }
}

// ステージ登録
void StageManager::Register(Stage* stage)
{
    stages.emplace_back(stage);
}

// ステージ全削除
void StageManager::Clear()
{
    // <ステージ>
    // リスト削除
    for (BaseStage* stage : stages)
    {
        delete stage;
        stage = nullptr;
    }
    stages.clear();
    // 削除リスト削除
    for (BaseStage* remove : stageRemoves)
    {
        delete remove;
        remove = nullptr;
    }
    stageRemoves.clear();
    // スポーンデータ削除
    stagesSpawns.clear();


    // <地形>
    // リスト削除
    for (BaseStage* stage : terrains)
    {
        delete stage;
        stage = nullptr;
    }
    terrains.clear();
    // 削除リスト削除
    for (BaseStage* remove : terrainRemoves)
    {
        delete remove;
        remove = nullptr;
    }
    terrainRemoves.clear();
    // スポーンデータ削除
    terrainSpawns.clear();
}

// ステージ生成
void StageManager::StageSpawn(DirectX::XMFLOAT3 position)
{
    Stage* s = new Stage(stageNo);                  //ステージを生成
    s->SetPosition(position);                       // ここでステージのポジションを決める
    s->SetScrollVelocity(&stageScrollVelocity);     // 共通のスクロール速度を設定
    s->Initialize();                                // 障害物生成
    stages.emplace_back(s);                         // コンテナ追加
}

// ステージの更新
void StageManager::StageUpdate(float elapsedTIme)
{
    // ステージの生成
    for (DirectX::XMFLOAT3 data : stagesSpawns)
    {
        StageSpawn(data);
    }
    stagesSpawns.clear();

    // ステージの更新処理
    for (BaseStage* stage : stages)
    {
        stage->Update(elapsedTIme);

        // 削除リスト追加
        if (stage->GetIsDestroy())
        {
            stageRemoves.insert(stage);
        }

        // 生成リスト追加
        if (stage->GetIsSpawn())
        {
            stagesSpawns.emplace_back(stage->GetSpawnPosition());
        }
    }

    // ステージの削除
    for (BaseStage* remove : stageRemoves)
    {
        std::vector<BaseStage*>::iterator it
            = std::find(stages.begin(), stages.end(), remove);

        // removeのデータがstagesにあれば
        if (it != stages.end())
        {
            stages.erase(it);
        }
        delete remove;
    }
    // 破棄リストをクリア
    stageRemoves.clear();
}

// 地形の更新
void StageManager::TerrainUpdate(float elapsedTIme)
{
    // ステージの生成
    for (DirectX::XMFLOAT3 data : terrainSpawns)
    {
        TerrainSpawn(data);
    }
    terrainSpawns.clear();

    // ステージの更新処理
    for (BaseStage* stage : terrains)
    {
        stage->Update(elapsedTIme);

        // 削除リスト追加
        if (stage->GetIsDestroy())
        {
            terrainRemoves.insert(stage);
        }

        // 生成リスト追加
        if (stage->GetIsSpawn())
        {
            terrainSpawns.emplace_back(stage->GetSpawnPosition());
        }
    }

    // ステージの削除
    for (BaseStage* remove : terrainRemoves)
    {
        std::vector<BaseStage*>::iterator it
            = std::find(terrains.begin(), terrains.end(), remove);

        // removeのデータがstagesにあれば
        if (it != terrains.end())
        {
            terrains.erase(it);
        }
        delete remove;
    }
    // 破棄リストをクリア
    terrainRemoves.clear();
}

// 地形生成
void StageManager::TerrainSpawn(DirectX::XMFLOAT3 position)
{
    Terrain* s = new Terrain;           //地形を生成
    s->SetPosition(position);// ここでステージのポジションを決める
    s->SetScrollVelocity(&terrainScrollVelocity);  // 共通のスクロール速度を設定
    s->Initialize();
    terrains.emplace_back(s);
}

void StageManager::AddVelocity()
{
    stageScrollVelocity = { stageScrollVelocity.x * 1.5f,stageScrollVelocity.y * 1.5f ,stageScrollVelocity.z * 1.5f };
}

// スティック入力値から移動ベクトルを取得
DirectX::XMFLOAT3 StageManager::GetMoveVec()
{
    // 入力情報を取得
    GamePad& gamePad = Input::Instance().GetGamePad();
    float ax = gamePad.GetAxisLX();
    DirectX::XMFLOAT3 vec = { ax ,0.0f,0.0f };

    return vec;
}

// 移動入力処理
void StageManager::InputMove(float elapsedTime)
{
    // 進行ベクトル取得
    DirectX::XMFLOAT3 moveVec = GetMoveVec();

    // 移動方向ベクトルを設定
    // (反転させる)
    moveVecX = moveVec.x * -1;
}

// 速度処理更新
void StageManager::UpdateVelocity(float elapsedTime, Player* player)
{
    // 経過フレーム
    float elapsedFrame = 60.0f * elapsedTime;

    // プレイヤーの最大速度更新
    maxPlayerVelocity = MaxPlayerVelocity[player->GetHungerLevel()];

    // 水平速力更新処理
    UpdataHorizontalVelocity(elapsedFrame);

    player->SetVelocity({ -stageScrollVelocity.x,0.0f,0.0f });

    // ステージのスクロール速度更新
    UpdateScrollVelocity(stageScrollVelocity, MaxStageScrollVelocity[player->GetHungerLevel()], ScrollVelocityRate);
    
    // 地形のスクロール速度更新
    UpdateScrollVelocity(terrainScrollVelocity, MaxTerrainScrollVelocity[player->GetHungerLevel()], ScrollVelocityRate);
}

// 水平速力更新処理
void StageManager::UpdataHorizontalVelocity(float elapsedFrame)
{
    // XZ平面の速力を減速する
    float length = sqrtf(stageScrollVelocity.x * stageScrollVelocity.x);

    // キーを離すとすぐ止まってほしので減速処理なし

    // XZ平面の速力を加速する
    if (length <= maxPlayerVelocity)
    {
        // 移動ベクトルがゼロベクトル出ないなら加速する
        float moveVecLength = sqrtf(moveVecX * moveVecX);
        if (moveVecLength > 0.0f)
        {
            // 加速力
            float acceleration = this->acceleration * elapsedFrame;

            // 移動ベクトルによる加速処理
            stageScrollVelocity.x += moveVecX * acceleration;

            // 最大速度制限
            float length = sqrtf(stageScrollVelocity.x * stageScrollVelocity.x);
            if (length > maxPlayerVelocity)
            {
                float vx = stageScrollVelocity.x / length;

                stageScrollVelocity.x = vx * maxPlayerVelocity;
            }
        }
    }

    // moveVecXが0ならVelocityを0にする
    if ((moveVecX < FLT_EPSILON) && (moveVecX > -FLT_EPSILON))
    {
        stageScrollVelocity.x = 0.0f;
    }

    // 地形データの速力に代入
    terrainScrollVelocity.x = stageScrollVelocity.x;

    // 移動ベクトルをリセット
    moveVecX = 0.0f;
}

// ステージの切り替え
void StageManager::ChangeStage()
{
    for (int i = stageNo ;i < 3;++i)
    {
        if (GetSpawnStageCount() >= StageChangeLine[i])
        {
            stageNo++;      // 次のステージに切り替え
            return;
        }
    }
}

// スクロール速度更新
void StageManager::UpdateScrollVelocity(DirectX::XMFLOAT3& ScrollVelocity, float maxVelocity, float rate)
{
    float length = ScrollVelocity.z - maxVelocity;
    // 値が微小な場合は処理しない
    if (fabs(length) > 1e-8f)
    {
        //return a + t * (b - a);
        ScrollVelocity.z = ScrollVelocity.z + rate * (maxVelocity - ScrollVelocity.z);
    }
}