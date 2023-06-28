#include "Graphics/Graphics.h"
#include "SceneGame.h"
#include "Camera.h"
#include "LightManager.h"
#include "EffectManager.h"
#include "Input/Input.h"
#include "Stage.h"

//-------------------------------------------------------------------------------------------------------
// 
//		 ゲームシーン
// 
//-------------------------------------------------------------------------------------------------------

// 初期化
void SceneGame::Initialize()
{
	//プレイヤー初期設定
	player = new Player();

	// 空初期設定
	sky = new Sky();

	// ステージマネージャー初期設定
	stageManager = new StageManager;

	BaseStage::clear();

	// ステージ生成
	for (int z = 0; z < Stage::StageDepthMax; ++z)
	{
		for (int x = 0; x < Stage::StageSideMax; ++x)
		{
			float X = (-((Stage::StageSideMax - 1) * 0.5f) + x) * Stage::StageSize;
			float Z = (z * Stage::StageSize);

			stageManager->StageSpawn({ X,0.0f,Z });
		}
	}

	// 地形生成
	for (int z = 0; z < Terrain::StageDepthMax; ++z)
	{
		for (int x = 0; x < Terrain::StageSideMax; ++x)
		{
			float X = (-((Terrain::StageSideMax - 1) * 0.5f) + x) * Terrain::StageSize;
			float Z = (z * Terrain::StageSize);

			stageManager->TerrainSpawn({ X,0.0f,Z });
		}
	}

	//カメラ初期設定
	Graphics& graphics = Graphics::Instance();
	Camera& camera = Camera::Instance();
	camera.SetLookAt(
		DirectX::XMFLOAT3(0, 10, -10),
		DirectX::XMFLOAT3(0, 0, 0),
		DirectX::XMFLOAT3(0, 1, 0)
	);
	camera.SetPerspectiveFov(
		DirectX::XMConvertToRadians(45),
		graphics.GetScreenWidth() / graphics.GetScreenHeight(),
		0.1f,
		1000.0f
	);

	// カメラコントローラーの初期化
	cameraController = new CameraController();


	//-------------------------------------------------------------------------------------------------------
	// ↓　この下はシェーダー関連
	//-------------------------------------------------------------------------------------------------------
	// テクスチャを読み込む
	texture = std::make_unique<Texture>("Data/Texture/1920px-Equirectangular-projection.jpg");

	// スプライト
	sprite = std::make_unique<Sprite>();
	sprite->SetShaderResourceView(texture->GetShaderResourceView(), texture->GetWidth(), texture->GetHeight());

	// マスクテクスチャの読み込み
	maskTexture = std::make_unique<Texture>("Data/Texture/dissolve_animation.png");
	dissolveThreshold = 0.0f;
	edgeThreshold = 0.2f; // 縁の閾値
	edgeColor = { 1, 0, 0, 1 }; // 縁の色

	LightManager::Instane().Register(new Light(LightType::Directional));

}

// 終了化
void SceneGame::Finalize()
{
	// ステージ終了
	stageManager->Clear();
	// プレイヤー終了
	if (player != nullptr)
	{
		delete player;
		player = nullptr;
	}
	// 空終了
	if (sky != nullptr)
	{
		delete sky;
		sky = nullptr;
	}
}

// 更新処理
void SceneGame::Update(float elapsedTime)
{
	// カメラコントローラー更新処理化
	DirectX::XMFLOAT3 target = player->GetPosition();
	target.y += 0.5f;
	cameraController->setTarget(target);
	cameraController->Update(elapsedTime);

	// ポーズ処理
	GamePad& gamePad = Input::Instance().GetGamePad();
	if (gamePad.GetButtonDown() & GamePad::BTN_X)
		isPaused = !isPaused;       // 0コンのスタートボタンが押されたらポーズ状態が反転
	if (isPaused) return;           // この時点でポーズ中ならリターン

	//プレイヤー更新処理
	player->Update(elapsedTime);

	//ステージ更新処理
	stageManager->Update(player, elapsedTime);

	//空更新処理
	sky->Update(elapsedTime);
	sky->SetPosition({ player->GetPosition().x,player->GetPosition().y,player->GetPosition().z + 510 });

	sprite->Update(0.0f, 0.0f,
		100.0f, 100.0f,
		0.0f, 0.0f,
		static_cast<float>(texture->GetWidth()), static_cast<float>(texture->GetHeight()),
		0.0f,
		1.0f, 1.0f, 1.0f, 1.0f);

	sprite->Update(0.0f, 0.0f,
		Graphics::Instance().GetScreenWidth(), Graphics::Instance().GetScreenHeight(),
		0.0f, 0.0f,
		static_cast<float>(texture->GetWidth()), static_cast<float>(texture->GetHeight()),
		0.0f,
		1.0f, 1.0f, 1.0f, 1.0f);

	// エフェクトの更新処理
	EffectManager::Instance().Update(elapsedTime);
}

// 描画処理
void SceneGame::Render()
{
	// 3D空間の描画を別のバッファに対して行う
	Render3DScene();
	// 2Dスプライト描画
	{
		// 今は何も描画しない
	}

	// デバッグ情報の表示
	{
		ImGui::Separator();
		if (ImGui::TreeNode("Mask"))
		{
			ImGui::SliderFloat("Dissolve Threshold", &dissolveThreshold, 0.0f, 1.0f);
			ImGui::TreePop();
		}
		ImGui::Separator();
		LightManager::Instane().DrawDebugGUI();
	}
	// 2DデバッグGUI描画
	{
		// stageManager
		player->DrawDebugGUI();
		stageManager->DrawDebugGUI();
	}
}

void SceneGame::DrawDebugParameter(DirectX::XMFLOAT4X4& transform, const char* label)
{
	ImGui::PushID(label);
	if (ImGui::TreeNode(label))
	{
		DirectX::XMVECTOR Scale, Rotation, Position;
		DirectX::XMMatrixDecompose(&Scale, &Rotation, &Position, DirectX::XMLoadFloat4x4(&transform));
		DirectX::XMFLOAT3 scale, rotation, position;
		DirectX::XMStoreFloat3(&scale, Scale);
		DirectX::XMStoreFloat3(&rotation, Rotation);
		DirectX::XMStoreFloat3(&position, Position);
		ImGui::SliderFloat3("scale", &scale.x, 0.0f, 10.0f);
		ImGui::SliderFloat3("rotation", &rotation.x, -DirectX::XM_PI, DirectX::XM_PI);
		ImGui::SliderFloat3("position", &position.x, -300.0f, 1000.0f);
		DirectX::XMMATRIX Transform;
		Transform	= DirectX::XMMatrixScaling(scale.x, scale.y, scale.z)
					* DirectX::XMMatrixRotationRollPitchYaw(rotation.x, rotation.y, rotation.z)
					* DirectX::XMMatrixTranslation(position.x, position.y, position.z);
		DirectX::XMStoreFloat4x4(&transform, Transform);
		ImGui::TreePop();
	}
	ImGui::PopID();
}

// グリッド描画
void SceneGame::DrawGrid(ID3D11DeviceContext* context, int subdivisions, float scale)
{
	int numLines = (subdivisions + 1) * 2;
	int vertexCount = numLines * 2;

	float corner = 0.5f;
	float step = 1.0f / static_cast<float>(subdivisions);

	int index = 0;
	float s = -corner;

	const DirectX::XMFLOAT4 white = DirectX::XMFLOAT4(1, 1, 1, 1);

	LineRenderer* lineRenderer = Graphics::Instance().GetLineRenderer();
	// Create vertical lines
	float scaling = static_cast<float>(subdivisions) * scale;
	DirectX::XMMATRIX M = DirectX::XMMatrixScaling(scaling, scaling, scaling);
	DirectX::XMVECTOR V, P;
	DirectX::XMFLOAT3 position;
	for (int i = 0; i <= subdivisions; i++)
	{
		V = DirectX::XMVectorSet(s, 0, corner, 0);
		P = DirectX::XMVector3TransformCoord(V, M);
		DirectX::XMStoreFloat3(&position, P);
		lineRenderer->AddVertex(position, white);

		V = DirectX::XMVectorSet(s, 0, -corner, 0);
		P = DirectX::XMVector3TransformCoord(V, M);
		DirectX::XMStoreFloat3(&position, P);
		lineRenderer->AddVertex(position, white);

		s += step;
	}

	// Create horizontal lines
	s = -corner;
	for (int i = 0; i <= subdivisions; i++)
	{
		V = DirectX::XMVectorSet(corner, 0, s, 0);
		P = DirectX::XMVector3TransformCoord(V, M);
		DirectX::XMStoreFloat3(&position, P);
		lineRenderer->AddVertex(position, white);

		V = DirectX::XMVectorSet(-corner, 0, s, 0);
		P = DirectX::XMVector3TransformCoord(V, M);
		DirectX::XMStoreFloat3(&position, P);
		lineRenderer->AddVertex(position, white);

		s += step;
	}

	// X軸
	{
		const DirectX::XMFLOAT4 red = DirectX::XMFLOAT4(1, 0, 0, 1);
		V = DirectX::XMVectorSet(0, 0, 0, 0);
		P = DirectX::XMVector3TransformCoord(V, M);
		DirectX::XMStoreFloat3(&position, P);
		lineRenderer->AddVertex(position, red);

		V = DirectX::XMVectorSet(corner, 0, 0, 0);
		P = DirectX::XMVector3TransformCoord(V, M);
		DirectX::XMStoreFloat3(&position, P);
		lineRenderer->AddVertex(position, red);
	}

	// Y軸
	{
		const DirectX::XMFLOAT4 green = DirectX::XMFLOAT4(0, 1, 0, 1);
		V = DirectX::XMVectorSet(0, 0, 0, 0);
		P = DirectX::XMVector3TransformCoord(V, M);
		DirectX::XMStoreFloat3(&position, P);
		lineRenderer->AddVertex(position, green);

		V = DirectX::XMVectorSet(0, corner, 0, 0);
		P = DirectX::XMVector3TransformCoord(V, M);
		DirectX::XMStoreFloat3(&position, P);
		lineRenderer->AddVertex(position, green);
	}

	// Z軸
	{
		const DirectX::XMFLOAT4 blue = DirectX::XMFLOAT4(0, 0, 1, 1);
		V = DirectX::XMVectorSet(0, 0, 0, 0);
		P = DirectX::XMVector3TransformCoord(V, M);
		DirectX::XMStoreFloat3(&position, P);
		lineRenderer->AddVertex(position, blue);

		V = DirectX::XMVectorSet(0, 0, corner, 0);
		P = DirectX::XMVector3TransformCoord(V, M);
		DirectX::XMStoreFloat3(&position, P);
		lineRenderer->AddVertex(position, blue);
	}
}

// 3D空間の描画
void SceneGame::Render3DScene()
{
	Graphics& graphics = Graphics::Instance();
	ID3D11DeviceContext* dc = graphics.GetDeviceContext();
	ID3D11RenderTargetView* rtv = graphics.GetRenderTargetView();
	ID3D11DepthStencilView* dsv = graphics.GetDepthStencilView();

	// 画面クリア＆レンダーターゲット設定
	FLOAT color[] = { 0.0f, 0.0f, 0.5f, 1.0f }; // RGBA(0.0～1.0)
	dc->ClearRenderTargetView(rtv, color);
	dc->ClearDepthStencilView(dsv, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	dc->OMSetRenderTargets(1, &rtv, dsv);
	// 描画処理
	RenderContext rc;
	rc.deviceContext = dc;
	// ライトの情報を詰め込む
	LightManager::Instane().PushRenderContext(rc);
	// カメラパラメータ設定
	Camera& camera = Camera::Instance();
	rc.viewPosition.x = camera.GetEye().x;
	rc.viewPosition.y = camera.GetEye().y;
	rc.viewPosition.z = camera.GetEye().z;
	rc.viewPosition.w = 1;
	rc.view = camera.GetView();
	rc.projection = camera.GetProjection();
	// 3Dモデル描画
	{
		ModelShader* shader = graphics.GetShader(ModelShaderId::Toon);
		shader->Begin(rc);
		//shader->Draw(rc, stage->model.get());
		sky->Draw(rc, shader);
		stageManager->Draw(rc, shader);
		player->Draw(rc, shader);
		shader->End(rc);
	}
	// 3Dエフェクト描画
	{
		EffectManager::Instance().Render(rc.view, rc.projection);
	}
	// デバッグプリミティブの表示
	{
		// ライトのデバッグプリミティブの描画
		LightManager::Instane().DrawDebugPrimitive();
		// ラインレンダラ描画実行
		graphics.GetLineRenderer()->Render(dc, camera.GetView(), camera.GetProjection());
		// デバッグレンダラ描画実行
		graphics.GetDebugRenderer()->Render(dc, camera.GetView(), camera.GetProjection());
	}
}