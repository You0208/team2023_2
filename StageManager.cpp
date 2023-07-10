#include "StageManager.h"
#include "Tool.h"
#include<imgui.h>
#include <Input/Input.h>

int StageManager::stageNo = 0;

// コンストラクタ
StageManager::StageManager()
{
    // 初期速度設定
    stageScrollVelocity.z = MaxStageScrollVelocity[1];
    terrainScrollVelocity.z = MaxTerrainScrollVelocity[1];

    scrollVelocityRate = ScrollVelocityRate;
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

    ImGui::Text("DoneStageNu:%ld", doneStageNum);
    ImGui::Text("stageNo:%ld", stageNo);
    ImGui::Text("accelerationTimer:%d", static_cast<int>(accelerationTimer));

    ImGui::Text("IsBreakTime:%d", static_cast<int>(IsBreakTime));
    ImGui::Text("IsSpawnNone:%d", static_cast<int>(IsSpawnNone_Side));

    // 残り休憩時間
    ImGui::Text("IsBreakTime:%lf", breakTimer);

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

    // スコアの更新(常時加算)
    UpdateScore(player, elapsedTIme);

    // ステージ切り替え
    SetBreakTime_State();

    // 移動入力処理
    InputMove(elapsedTIme);

    // 速度処理更新
    UpdateVelocity(elapsedTIme, player);

    // doneStageNumの加算
    AddDoneStageNum(elapsedTIme);

    // ステージの更新
    StageUpdate(elapsedTIme);

    // 地形更新
    TerrainUpdate(elapsedTIme);

    // 休憩時間更新
    UpdateBreakTime(elapsedTIme, player);
    player->IsBreakTime = IsBreakTime;
}

// セレクト更新
void StageManager::StageSelectUpdate(float elapsedTIme)
{
    stageScrollVelocity = { 0,0,0 };
    terrainScrollVelocity = { 0,0,0 };
    // ステージの更新
    StageUpdate(elapsedTIme);

    // 地形更新
    TerrainUpdate(elapsedTIme);
}

void StageManager::StageDeathUpdate(float elapsedTIme)
{
    //VZ = lerp(VZ, 100.0f, 0.001f);
    //stageScrollVelocity = { 0,0,VZ };
    //terrainScrollVelocity = { 0,0,VZ };
    stageScrollVelocity = { 0,0,0 };
    terrainScrollVelocity = { 0,0,0 };
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
void StageManager::StageSpawn(SpawnData data)
{
    int No = (SceneManager::Instance().IsNoneStage && !data.IsDepthSpawn) ||
        // 奥行の生成が禁止されているもしくは左右の生成が禁止されていて左右に生成される場合-1を返す
        IsSpawnNone_Depth || (IsSpawnNone_Side && !data.IsDepthSpawn)
        // Stageの引き数が0以下の場合StageNONEが生成される
        ? -1 : stageNo;            

    Stage* s = new Stage(No);                       //ステージを生成
    s->SetPosition(data.position);                       // ここでステージのポジションを決める
    s->SetScrollVelocity(&stageScrollVelocity);     // 共通のスクロール速度を設定
    s->Initialize();                                // 障害物生成
    stages.emplace_back(s);                         // コンテナ追加
}

// ステージの更新
void StageManager::StageUpdate(float elapsedTIme)
{
    // ステージの生成
    for (SpawnData data : stagesSpawns)
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
            SpawnData data = { stage->GetSpawnPosition(), stage->GetisIsDepthSpawn() };
            stagesSpawns.emplace_back(data);
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
    Terrain* s = new Terrain;                       //地形を生成
    s->SetPosition(position);                       // ここでステージのポジションを決める
    s->SetScrollVelocity(&terrainScrollVelocity);   // 共通のスクロール速度を設定
    s->Initialize();
    terrains.emplace_back(s);
}

void StageManager::AddVelocity(float addVelocity, float timer)
{
    accelerationTimer = timer;
    stageScrollVelocity.z -= addVelocity;
    terrainScrollVelocity.z -= addVelocity;
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
    UpdataHorizontalVelocity(elapsedFrame, player);

    player->SetVelocity({ -stageScrollVelocity.x,0.0f,0.0f });

    // 加速状態なら
    if (accelerationTimer >= 0.0f)
    {
        accelerationTimer      -= elapsedTime;
        scrollVelocityRate      = ScrollVelocityRate_ac;
        stageScrollVelocity.z   = (std::max)(stageScrollVelocity.z, MaxVelocity);
        terrainScrollVelocity.z = (std::max)(terrainScrollVelocity.z, MaxVelocity);
    }
    else scrollVelocityRate = ScrollVelocityRate;

    // ステージのスクロール速度更新
    UpdateScrollVelocity(stageScrollVelocity, MaxStageScrollVelocity[player->GetHungerLevel()], scrollVelocityRate);
    
    // 地形のスクロール速度更新
    UpdateScrollVelocity(terrainScrollVelocity, MaxTerrainScrollVelocity[player->GetHungerLevel()], scrollVelocityRate);
}

// 水平速力更新処理
void StageManager::UpdataHorizontalVelocity(float elapsedFrame, Player* player)
{
    float length = sqrtf(stageScrollVelocity.x * stageScrollVelocity.x);

#if 0
    // 空腹状態であるとき
    if (player->GetHungerLevel() == 0)
    {
        // XZ平面の速力を減速する

        // キーを離すとすぐ止まってほしので減速処理なし
        float length = sqrtf((stageScrollVelocity.x * stageScrollVelocity.x));
        if (length > 0.0f)
        {
            // 摩擦力
            float friction = this->friction * elapsedFrame;

            // 摩擦による横方向の減速処理[09]
            if (length > friction)
            {
                float vx = stageScrollVelocity.x / length;
                stageScrollVelocity.x -= vx * friction;
            }
            // 横方向の速力が摩擦力以下になったので速力を無効化[09]
            else
            {
                stageScrollVelocity.x = 0.0f;
            }
        }
    }
    // 空腹状態でないとき
    else
    {
        // moveVecXが0ならVelocityを0にする
        if ((moveVecX < FLT_EPSILON) && (moveVecX > -FLT_EPSILON))
        {
            stageScrollVelocity.x = 0.0f;
        }
    }
#else
    if ((moveVecX < FLT_EPSILON) && (moveVecX > -FLT_EPSILON))
    {
        stageScrollVelocity.x = 0.0f;
    }

#endif

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


    // 地形データの速力に代入
    terrainScrollVelocity.x = stageScrollVelocity.x;

    // 移動ベクトルをリセット
    moveVecX = 0.0f;
}

// BreakTime_Stateをセット
void StageManager::SetBreakTime_State()
{
    //　ブレイクタイムは以下の処理をしない
    if (IsBreakTime) return;

    for (int i = stageNo ;i < Stage::StageMax - 1;++i)
    {
        if (doneStageNum >= StageChangeLine[i] - (Stage::StageDepthMax - 1))    // 1枚は自機の後ろに行くので
        {
            IsSpawnNone_Depth = true;
            IsSpawnNone_Side = true;
            breakTime_State = StageChangeLine[i];
            break;
        }
    }       
}

// 休憩時間更新
void StageManager::UpdateBreakTime(float elapsedFrame, Player* player)
{
    if (IsSpawnNone_Depth)
    {
        // ブレイクタイム開始するステージを超えた　かつ　ブレイクタイムでないとき
        if (!IsBreakTime && breakTime_State <= doneStageNum)
        {
            player->AddScore(StageClearcBonus[stageNo]);    // ステージクリア報酬
            stageNo++;                                      // 次のステージに切り替え
            IsBreakTime = true;
            breakTime_End = doneStageNum + MaxBreakTime;
        }

        // ステージの生成再開
        if (IsBreakTime && breakTime_End - MaxBreakTime <= doneStageNum)
        {
            IsSpawnNone_Depth = false;
        }
    }
    // ブレイクタイムなら
    else if (IsBreakTime && breakTime_End <= doneStageNum)
    {
        IsSpawnNone_Side = false;
        IsBreakTime = false;
        doneStageNum = 0;
    }


}

// doneStageNumの加算
void StageManager::AddDoneStageNum(float elapsedTIme)
{
    // ステージの位置(z)
    static float z = + (Stage::StageSize*0.5f);     // 初期が画面の中心から始まるため
    z -= stageScrollVelocity.z * elapsedTIme;

    // ステージより大きくなると
    if (z >= Stage::StageSize)
    {
        z = 0.0f;
        ++doneStageNum;
    }
}

// スコアの更新(常時加算)
void StageManager::UpdateScore(Player* player, float elapsedTime)
{
    // ブレイクタイム中なら加算しない
    if (IsBreakTime) return;
    // 加算量
    static float s = 0.0f;

    s += MaxAlwaysAddScore[stageNo] * MaxAlwaysAddScoreMagnification[player->GetHungerLevel()] * elapsedTime;
    
    // 加算量が1を超えるとスコアを加算する
    if (s >= 1.0f)
    {
        player->AddScore(1);    // スコア加算
        s -= 1.0f;
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