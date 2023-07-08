#include "Graphics/Graphics.h"
#include "SceneGame.h"
#include "Camera.h"
#include "LightManager.h"
#include "EffectManager.h"
#include "Collision.h"
#include "Input/Input.h"
#include "Stage.h"
#include "Tool.h"

//-------------------------------------------------------------------------------------------------------
// 
//		 ゲームシーン
// 
//-------------------------------------------------------------------------------------------------------

// シャドウマップのサイズ
static const UINT SHADOWMAP_SIZE = 2048;

// 初期化
void SceneGame::Initialize()
{
	// オーディオ初期化
	b_game = Audio::Instance().LoadAudioSource("Data/Audio/BGM/BGM.wav");
	b_game->SetVolume(0.2f);
	b_select = Audio::Instance().LoadAudioSource("Data/Audio/BGM/BGM_Select.wav");
	b_select->SetVolume(0.2f);

	s_speed = Audio::Instance().LoadAudioSource("Data/Audio/SE/Speed.wav");
	s_speed->SetVolume(1.0f);
	s_heal = Audio::Instance().LoadAudioSource("Data/Audio/SE/Heal.wav");
	s_heal->SetVolume(1.0f);
	s_clash = Audio::Instance().LoadAudioSource("Data/Audio/SE/Clash.wav");
	s_clash->SetVolume(0.6f);
	s_choice = Audio::Instance().LoadAudioSource("Data/Audio/SE/Choice.wav");
	s_choice->SetVolume(0.3f);
	s_selection = Audio::Instance().LoadAudioSource("Data/Audio/SE/Selection.wav");
	s_selection->SetVolume(1.0f);

	//プレイヤー初期設定
	player = new Player();
	player->ScoreClear();	// スコアのリセット

	// 空初期設定
	sky = new Sky();

	// fonts
	// フォント読み込み
	texture_fonts[0] = std::make_unique<Texture>("Data/fonts/font0.png");
	texture_fonts[1] = std::make_unique<Texture>("Data/fonts/font1.png");
	texture_fonts[2] = std::make_unique<Texture>("Data/fonts/font2.png");
	texture_fonts[3] = std::make_unique<Texture>("Data/fonts/font3.png");
	texture_fonts[4] = std::make_unique<Texture>("Data/fonts/font4.png");
	texture_fonts[5] = std::make_unique<Texture>("Data/fonts/font5.png");
	texture_fonts[6] = std::make_unique<Texture>("Data/fonts/font6.png");
	for (int i = 0; i < 7; ++i)
	{
		text[i] = std::make_unique<Text>();
		text[i]->SetShaderResourceView(texture_fonts[i]->GetShaderResourceView(),
			texture_fonts[i]->GetWidth(), texture_fonts[i]->GetHeight());
	}
	texture_fonts_number = std::make_unique<Texture>("Data/fonts/font7.png");
	text_number = std::make_unique<Text>();
	text_number->SetShaderResourceView(texture_fonts_number->GetShaderResourceView(),
		texture_fonts_number->GetWidth(), texture_fonts_number->GetHeight());


	// 空腹ゲージのフレーム設定
	texture_hungerGageFrame = std::make_unique<Texture>("Data/Texture/UI/GaugeUI.png");
	sprite_hungerGageFrame = std::make_unique<Sprite>();
	sprite_hungerGageFrame->SetShaderResourceView(texture_hungerGageFrame->GetShaderResourceView(),
		texture_hungerGageFrame->GetWidth(), texture_hungerGageFrame->GetHeight());
	// 空腹ゲージ設定
	texture_hungerGage = std::make_unique<Texture>("Data/Texture/UI/white.png");
	sprite_hungerGage = std::make_unique<Sprite>();
	sprite_hungerGage->SetShaderResourceView(texture_hungerGage->GetShaderResourceView(),
		texture_hungerGage->GetWidth(), texture_hungerGage->GetHeight());
	// 空腹ゲージの背景設定
	sprite_hungerGageBack = std::make_unique<Sprite>();
	sprite_hungerGageBack->SetShaderResourceView(texture_hungerGage->GetShaderResourceView(),
		texture_hungerGage->GetWidth(), texture_hungerGage->GetHeight());

	// ステージレベル看板
	texture_StageUI = std::make_unique<Texture>("Data/Texture/UI/StageUI_sheet.png");
	sprite_StageUI = std::make_unique<Sprite>();
	sprite_StageUI->SetShaderResourceView(texture_StageUI->GetShaderResourceView(),
		texture_StageUI->GetWidth(), texture_StageUI->GetHeight());

	// ステージマネージャー初期設定
	stageManager = new StageManager;

	BaseStage::clear();

	// ステージ生成
	for (int z = 0; z < Stage::StageDepthMax; ++z)
	{
		bool IsDepthSpawn = (z == (Stage::StageDepthMax - 1));
		for (int x = 0; x < Stage::StageSideMax; ++x)
		{
			float X = (-((Stage::StageSideMax - 1) * 0.5f) + x) * Stage::StageSize;
			float Z = (z * Stage::StageSize);

			stageManager->StageSpawn({ {X,0.0f,Z},IsDepthSpawn });
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

	//TODO 要改善
	SceneManager::Instance().IsNoneStage = false;

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

	// ヒットエフェクト読み込み
	hitEffect = new Effect("Data/e/b.efk");
	accelEffect = new Effect("Data/e/kasoku_0704_1.efk");


	//-------------------------------------------------------------------------------------------------------
	// ↓　この下はシェーダー関連
	//-------------------------------------------------------------------------------------------------------
	// テクスチャを読み込む
	texture = std::make_unique<Texture>("Data/Texture/titleFrame.png");
	// スプライト
	sprite = std::make_unique<Sprite>();
	sprite->SetShaderResourceView(texture->GetShaderResourceView(), texture->GetWidth(), texture->GetHeight());

	// テクスチャを読み込む
	texture_line = std::make_unique<Texture>("Data/Texture/syuchusen.png");
	// スプライト
	sprite_line = std::make_unique<Sprite>();
	sprite_line->SetShaderResourceView(texture_line->GetShaderResourceView(), texture_line->GetWidth(), texture_line->GetHeight());

	// 終わり
// テクスチャを読み込む
	t_finish = std::make_unique<Texture>("Data/Texture/Select/owaru.png");
	// スプライト
	s_finish = std::make_unique<Sprite>();
	s_finish->SetShaderResourceView(t_finish->GetShaderResourceView(), t_finish->GetWidth(), t_finish->GetHeight());

	// プレイ
	// テクスチャを読み込む
	t_play = std::make_unique<Texture>("Data/Texture/Select/play.png");
	// スプライト
	s_play = std::make_unique<Sprite>();
	s_play->SetShaderResourceView(t_play->GetShaderResourceView(), t_play->GetWidth(), t_play->GetHeight());

	// ルール
	// テクスチャを読み込む
	t_rulu = std::make_unique<Texture>("Data/Texture/Select/rule.png");
	// スプライト
	s_rulu = std::make_unique<Sprite>();
	s_rulu->SetShaderResourceView(t_rulu->GetShaderResourceView(), t_rulu->GetWidth(), t_rulu->GetHeight());

	// セレクト
	// テクスチャを読み込む
	t_select = std::make_unique<Texture>("Data/Texture/Select/select.png");
	// スプライト
	s_select = std::make_unique<Sprite>();
	s_select->SetShaderResourceView(t_select->GetShaderResourceView(), t_select->GetWidth(), t_select->GetHeight());

	// スコア
	// テクスチャを読み込む
	t_score = std::make_unique<Texture>("Data/Texture/Select/highscore_point.png");
	// スプライト
	s_score = std::make_unique<Sprite>();
	s_score->SetShaderResourceView(t_score->GetShaderResourceView(), t_score->GetWidth(), t_score->GetHeight());



	// マスクテクスチャの読み込み
	maskTexture = std::make_unique<Texture>("Data/Texture/dissolve_animation.png");
	dissolveThreshold = 0.0f;
	edgeThreshold = 0.2f; // 縁の閾値
	edgeColor = { 1, 0, 0, 1 }; // 縁の色

	//LightManager::Instane().Register(new Light(LightType::Directional));
	// 平行光源を追加
	{
		mainDirectionalLight = new Light(LightType::Directional);
		mainDirectionalLight->SetDirection({ -0.437, -0.582, 0.686 });
		LightManager::Instane().Register(mainDirectionalLight);
	}

	// 新しい描画ターゲットの生成
	{
		Graphics& graphics = Graphics::Instance();
		renderTarget = std::make_unique<RenderTarget>(static_cast<UINT>(graphics.GetScreenWidth())
			, static_cast<UINT>(graphics.GetScreenHeight())
			, DXGI_FORMAT_R8G8B8A8_UNORM);
	}

	// シャドウマップ用に深度ステンシルの生成
	{
		Graphics& graphics = Graphics::Instance();
		shadowmapDepthStencil = std::make_unique<DepthStencil>(SHADOWMAP_SIZE, SHADOWMAP_SIZE);
	}

	// ポストプロセス描画クラス生成
	{
		postprocessingRenderer = std::make_unique<PostprocessingRenderer>();
		// シーンテクスチャを設定しておく
		ShaderResourceViewData srvData;
		srvData.srv = renderTarget->GetShaderResourceView();
		srvData.width = renderTarget->GetWidth();
		srvData.height = renderTarget->GetHeight();
		postprocessingRenderer->SetSceneData(srvData);
	}


	// スコア読み取り
	InputHighScore();
}

// 終了化
void SceneGame::Finalize()
{
	// ハイスコアの更新
	UpdateHighScore(player->GetScore());
	// ファイル書き込み(テスト)
	OutputHighScore();

	// ステージ終了
	stageManager->Clear();
	// プレイヤー終了
	if (player != nullptr)
	{
		delete player;
		player = nullptr;
	}
	// エフェクト終了
	if (hitEffect != nullptr)
	{
		delete hitEffect;
		hitEffect = nullptr;
	}
	// エフェクト終了
	if (accelEffect != nullptr)
	{
		delete accelEffect;
		accelEffect = nullptr;
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
	if (IsRule)
	{
		RuleUpdate(elapsedTime);
	}
	else if (SceneManager::Instance().IsSelect)
	{
		SelectUpdate(elapsedTime);
	}
	else
	{
		b_game->Play(true);

		// ポーズ処理
		GamePad& gamePad = Input::Instance().GetGamePad();
		if (gamePad.GetButtonDown() & GamePad::BTN_X)
			isPaused = !isPaused;       // 0コンのスタートボタンが押されたらポーズ状態が反転
		cameraController->Update(elapsedTime);
		if (isPaused) return;           // この時点でポーズ中ならリターン

		// デバッグ
		if (gamePad.GetButtonDown() & GamePad::BTN_Y)
		{
			//player->IsDeath = true;
			//player->OnDead();
			//DeathMoment();
			//player->Gashi = true;
			//accel = true;
			// ヒットエフェクト再生
			{
				DirectX::XMFLOAT3 e = player->GetPosition();
				accelEffect->Play(e);
			}
		}

		if (cameraController->flag)
		{
			// カメラコントローラー更新処理化
			cameraController->Shake(120, player->GetPosition().y + 0.5f);
		}
		else
		{
			// カメラコントローラー更新処理化
			target = player->GetPosition();
			target.y += 2.5f;
			cameraController->setTarget(target);
		}
		cameraController->Update(elapsedTime);

		//プレイヤー更新処理
		player->Update(elapsedTime);

		//空更新処理
		sky->Update(elapsedTime);
		sky->SetPosition({ player->GetPosition().x,player->GetPosition().y,player->GetPosition().z + sky->space });

		static bool IsSePlay = false;			// SEを1度だけ流す(飢餓での死亡SE再生に使用中)

		if (accel)// 加速時
		{
			accelUpdate(elapsedTime);
		}

		if (!player->IsDeath&&!player->Gashi)// プレイヤーが死んでいない時
		{
			//ステージ更新処理
			stageManager->Update(player, elapsedTime);
			CollisionPlayerVsObs();
			CollisionObsVsObs();		// 障害物同士の当たり判定
			UpdateHungerGage();			// 空腹ゲージの更新
			UpdateStageUI();			// ステージレベル看板更新
		}
		else if (player->IsDeath)// プレイヤーが死んでいる時
		{
			DeathUpdate(elapsedTime);
		}
		else if (player->Gashi)
		{
			if (!IsSePlay)
			{
				s_clash->Play(false);
				IsSePlay = true;
			}
			DidFromHunger(elapsedTime);
		}

		if (player->IsDeath || player->Gashi)
		{
			DeathTimer++;
			if (DeathTimer >= 800)
			{
				IsSePlay = false;
				SceneManager::Instance().ChangeScene(new SceneOver);
			}
		}
	}
	EffectManager::Instance().Update(elapsedTime);


	//-------------------------------------------------------------------------------------------------------
	// ↓　この下はシェーダー関連
	//-------------------------------------------------------------------------------------------------------

	sprite->Update(0.0f, rulePos,
		static_cast<float>(texture->GetWidth()), static_cast<float>(texture->GetHeight()),
		0.0f, 0.0f,
		static_cast<float>(texture->GetWidth()), static_cast<float>(texture->GetHeight()),
		0.0f,
		1.0f, 1.0f, 1.0f, 1.0f);

	sprite_line->Update(0.0f, 0.0f,
		Graphics::Instance().GetScreenWidth(), Graphics::Instance().GetScreenHeight(),
		p_w, 0.0f,
		static_cast<float>(texture->GetWidth()), static_cast<float>(texture->GetHeight()),
		0.0f,
		1.0f, 1.0f, 1.0f, 1.0f);

	s_finish->Update(iconPosX[SELECT_FIN], 615.0f,
		static_cast<float>(t_finish->GetWidth()), static_cast<float>(t_finish->GetHeight()),
		0.0f, 0.0f,
		static_cast<float>(t_finish->GetWidth()), static_cast<float>(t_finish->GetHeight()),
		0.0f,
		1.0f, 1.0f, 1.0f, 1.0f);

	s_play->Update(iconPosX[SELECT_PLAY], 215.0f,
		static_cast<float>(t_play->GetWidth()), static_cast<float>(t_play->GetHeight()),
		0.0f, 0.0f,
		static_cast<float>(t_play->GetWidth()), static_cast<float>(t_play->GetHeight()),
		0.0f,
		1.0f, 1.0f, 1.0f, 1.0f);

	s_rulu->Update(iconPosX[SELECT_RULE], 420.0f,
		static_cast<float>(t_rulu->GetWidth()), static_cast<float>(t_rulu->GetHeight()),
		0.0f, 0.0f,
		static_cast<float>(t_rulu->GetWidth()), static_cast<float>(t_rulu->GetHeight()),
		0.0f,
		1.0f, 1.0f, 1.0f, 1.0f);

	s_select->Update(660.0f, 30.0f,
		static_cast<float>(t_select->GetWidth()), static_cast<float>(t_select->GetHeight()),
		0.0f, 0.0f,
		static_cast<float>(t_select->GetWidth()), static_cast<float>(t_select->GetHeight()),
		0.0f,
		1.0f, 1.0f, 1.0f, 1.0f);

	s_score->Update(1120.0f, 830.0f,
		static_cast<float>(t_score->GetWidth()), static_cast<float>(t_score->GetHeight()),
		0.0f, 0.0f,
		static_cast<float>(t_score->GetWidth()), static_cast<float>(t_score->GetHeight()),
		0.0f,
		1.0f, 1.0f, 1.0f, 1.0f);
}

// デバッグ用(削除する)
DirectX::XMFLOAT2 HighScoreTextPos	= { 1510.0f, 857.0f };
DirectX::XMFLOAT2 HighScoreTextSize = { 55.0f, 55.0f };

// 描画処理
void SceneGame::Render()
{
	Graphics& graphics = Graphics::Instance();
	ID3D11DeviceContext* dc = graphics.GetDeviceContext();

	// 3D空間の描画を別のバッファに対して行う
	Render3DScene();

	// シャドウマップの描画
	RenderShadowmap();

	// 書き込み先をバックバッファに変えてオフスクリーンレンダリングの結果を描画する
	{
		ID3D11RenderTargetView* rtv = graphics.GetRenderTargetView();
		ID3D11DepthStencilView* dsv = graphics.GetDepthStencilView();

		// 画面クリア＆レンダーターゲット設定
		FLOAT color[] = { 0.89f, 0.75f, 0.94f, 1.0f }; // RGBA(0.0～1.0)
		dc->ClearRenderTargetView(rtv, color);
		dc->ClearDepthStencilView(dsv, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
		dc->OMSetRenderTargets(1, &rtv, dsv);

		// ビューポートの設定
		D3D11_VIEWPORT vp = {};
		vp.Width = graphics.GetScreenWidth();
		vp.Height = graphics.GetScreenHeight();
		vp.MinDepth = 0.0f;
		vp.MaxDepth = 1.0f;
		dc->RSSetViewports(1, &vp);

		// ポストプロセス処理を行う
		postprocessingRenderer->Render(dc);

	}

	// 2Dスプライト描画
	{
		RenderContext rc;
		rc.deviceContext = dc;
		SpriteShader* shader = graphics.GetShader(SpriteShaderId::Default);
		shader->Begin(rc);
		if (accel)
		{
			// 描画処理
			shader->Draw(rc, sprite_line.get());
		}
		
		if (SceneManager::Instance().IsSelect)
		{
			// ステージセレクト
			shader->Draw(rc, s_finish.get());
			shader->Draw(rc, s_play.get());
			shader->Draw(rc, s_rulu.get());
			shader->Draw(rc, s_select.get());
			shader->Draw(rc, s_score.get());

			// ハイスコア表示
			text_number->textOut(rc
				, HighScore
				, HighScoreTextPos.x, HighScoreTextPos.y
				, HighScoreTextSize.x, HighScoreTextSize.y
				, 1.0f, 1.0f, 1.0f, 1.0f
			);
		}
		else	// ゲーム時
		{
			// 空腹ゲージ
			shader->Draw(rc, sprite_hungerGageBack.get());
			shader->Draw(rc, sprite_hungerGage.get());
			shader->Draw(rc, sprite_hungerGageFrame.get());

			// ステージレベル看板
			shader->Draw(rc, sprite_StageUI.get());

			// スコア表示(仮)
			//text[fontNo]->textOut(rc
			//	, "Score:" + std::to_string(player->GetScore())
			//	, text_pos.x, text_pos.y
			//	, text_size.x, text_size.y
			//	, text_color.x, text_color.y, text_color.z, text_color.w
			//);
			text_number->textOut(rc
				, player->GetScore()
				, text_pos.x, text_pos.y
				, text_size.x, text_size.y
				, text_color.x, text_color.y, text_color.z, text_color.w
			);
		}
		if (IsRule)	shader->Draw(rc, sprite.get());

		shader->End(rc);

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
			ImGui::Separator();
			if (ImGui::TreeNode("Shadowmap"))
			{
				ImGui::SliderFloat("DrawRect", &shadowDrawRect, 1.0f, 2048.0f);
				ImGui::ColorEdit3("Color", &shadowColor.x);
				ImGui::SliderFloat("Bias", &shadowBias, 0.0f, 0.1f);
				ImGui::Text("texture");
				ImGui::Image(shadowmapDepthStencil->GetShaderResourceView().Get(), { 256, 256 }, { 0, 0 }, { 1, 1 },
					{ 1, 1, 1, 1 });
				ImGui::TreePop();
			}
			ImGui::Separator();
		}
		// 2DデバッグGUI描画
		{
			// stageManager
			player->DrawDebugGUI();
			stageManager->DrawDebugGUI();
			postprocessingRenderer->DrawDebugGUI();
		}
		// テキスト
		{
			if (ImGui::TreeNode("Text Score"))
			{
				ImGui::SliderInt("fontNo", &fontNo, 0, 6);
				ImGui::SliderFloat("posX", &text_pos.x, 0.0f, 1920.0f);
				ImGui::SliderFloat("posY", &text_pos.y, 0.0f, 1080.0f);
				ImGui::SliderFloat("size", &text_size.x, 0.0f, 500.0f);
				text_size.y = text_size.x;
				ImGui::ColorPicker4("color", &text_color.x);
				ImGui::TreePop();
			}
			if (ImGui::TreeNode("Text HighScore"))
			{
				ImGui::InputFloat2("Pos", &HighScoreTextPos.x);
				ImGui::InputFloat("Size", &HighScoreTextSize.x);
				HighScoreTextSize.y = HighScoreTextSize.x;
				ImGui::TreePop();
			}
		}
		// スコア表示
		{
			ImGui::Separator();
			if (ImGui::TreeNode("SCORE"))
			{
				ImGui::Text("HighScore:%ld", HighScore);
				ImGui::TreePop();
			}
			// ハイスコアの読み取り
			if (ImGui::Button("InputHighScore"))
			{
				InputHighScore();
			}
			// ハイスコアの書き込み
			if (ImGui::Button("OutputHighScore"))
			{
				OutputHighScore();
			}
			//ハイスコアの更新
			if (ImGui::Button("UpdateHighScore"))
			{
				UpdateHighScore(player->GetScore());
			}
			// ハイスコアのリセット(書き込みも行う)
			if (ImGui::Button("ResetHighScore"))
			{
				ResetHighScore();
			}

			ImGui::Separator();
		}

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

// プレイヤー×障害物
void SceneGame::CollisionPlayerVsObs()
{
	for (auto& it : stageManager->stages)
	{
		for (auto& it2 : it->obstacles)
		{
			if (!it2->IsHit)
			{
				switch (it2->Type)
				{
					case TYPE::CYLINDER:// 円柱
						// 衝突判定
						DirectX::XMFLOAT3 outPosition;
						if (Collision::IntersectCylinderVsCylinder
						(player->GetPosition(),
							player->GetRadius(),
							player->GetHeight(),
							it2->GetPosition(),
							it2->GetRadius(),
							it2->GetHeight(),
							outPosition))
						{
							cameraController->flag = true;
							// ヒットエフェクト再生
							{
								DirectX::XMFLOAT3 e = player->GetPosition();
								hitEffect->Play(e);
							}
							player->OnDead();
							DeathMoment();
							it2->IsHit = true;
							s_clash->Stop();			// SE再生
							s_clash->Play(false);		// SE再生
						}
					break;
					case TYPE::CYLINDERS:// 直方体
						for (int n = 0; n < it2->CollisionNum; ++n)
						{
							// 衝突判定
							if (Collision::IntersectCylinderVsCylinder
							(player->GetPosition(),
								player->GetRadius(),
								player->GetHeight(),
								{ (it2->GetPosition().x - (it2->CollisionNum * it2->GetRadius()) + it2->GetRadius()) + (n * it2->GetRadius() * 2.0f) ,it2->GetPosition().y,it2->GetPosition().z },
								it2->GetRadius(),
								it2->GetHeight(),
								outPosition))
							{
								player->OnDead();
								DeathMoment();
								it2->IsHit = true;
								s_clash->Stop();			// SE再生
								s_clash->Play(false);		// SE再生
							}
						}
						break;
					case TYPE::ITEMS:// アイテム
						// 衝突判定
						if (Collision::IntersectSphereVsCylinder
						(it2->GetPosition(),
							it2->GetRadius(),
							player->GetPosition(),
							player->GetRadius(),
							player->GetHeight(),
							outPosition))
						{
							player->AddScore(it2->score);
							player->AddHungerPoint(it2->hungerPoint);
							it2->IsHit = true;
							s_heal->Stop();				// SE再生
							s_heal->Play(false);		// SE再生
						}
						break;
					case TYPE::GATE:// ゲート
						for (int n = 0; n < it2->CollisionNum; ++n)
						{
							// 衝突判定
							if (Collision::IntersectCylinderVsCylinder
							(player->GetPosition(),
								player->GetRadius(),
								player->GetHeight(),
								{ (it2->GetPosition().x - (it2->CollisionNum * it2->GetRadius()) + it2->GetRadius()) + (n * it2->GetRadius() * 2.0f) ,it2->GetPosition().y,it2->GetPosition().z },
								it2->GetRadius(),
								it2->GetHeight(),
								outPosition))
							{
								// 加速
								stageManager->AddVelocity(50.0f,1.0f);
								accel = true;
								// ヒットエフェクト再生
								{
									DirectX::XMFLOAT3 e = player->GetPosition();
									accelEffect->Play(e);
								}
								it2->IsHit = true;
								s_speed->Stop();		// SE再生
								s_speed->Play(false);	// SE再生
							}
						}
						break;
					default:
						break;
				}
			}
			else if(it2->Type==TYPE::ITEMS)
			{
				it2->GetItem();
			}
		}
	}
}

void SceneGame::SelectUpdate(float elapsedTime)
{
	if (!isTrans)
	{
		b_select->Play(true);	// BGM1再生

		// カメラコントローラー更新処理
		target = player->GetPosition();
		target.y += 1.5f;
		target.x += 1.5f;
		cameraController->setTarget(target);
		cameraController->setRange(5.0f);
		player->SetAngle({ 0.0f,  DirectX::XMConvertToRadians(130.0f), 0.0f });

		// アイコン選択処理
		GamePad& gamePad = Input::Instance().GetGamePad();
		if (gamePad.GetButtonDown() & GamePad::BTN_UP)
		{
			selectNum--;
			s_selection->Stop();
			s_selection->Play(false);		// SE再生
		}
		if (gamePad.GetButtonDown() & GamePad::BTN_DOWN)
		{
			selectNum++;
			s_selection->Stop();
			s_selection->Play(false);		// SE再生
		}
		if (selectNum > 2)selectNum = 0;
		if (selectNum < 0)selectNum = 2;
		// selectNumの値に応じてiconPosXの要素を設定
		for (int i = 0; i < 3; i++) 
		{
			if (i == selectNum)
			{
				iconPosX[i] = 1075.0f;
			}
			else 
			{
				iconPosX[i] = 1175.0f;
			}
		}


		if (gamePad.GetButtonDown() & GamePad::BTN_B)
		{
			switch (selectNum)
			{
			case SELECT_PLAY:
				range = cameraController->getRange();
				rotation = player->GetAngle().y;
				isTrans = true;
				break;
			case SELECT_RULE:
				IsRule = true;
				ruleIn = true;
				break;
			case SELECT_FIN:
				SceneManager::Instance().IsFinishAll = true;
				break;
			}
			s_choice->Play(false);
		}
	}

	cameraController->Update(elapsedTime);
	//プレイヤー更新処理
	player->Update(elapsedTime,true);
	//ステージ更新処理
	stageManager->StageSelectUpdate(elapsedTime);

	//空更新処理
	sky->Update(elapsedTime);
	sky->SetPosition({ player->GetPosition().x,player->GetPosition().y,player->GetPosition().z + sky->space });

	if (isTrans) {
		TransUpdate(elapsedTime);
		player->SelectUpdate(elapsedTime);
		if (range >= 9.98f) {
			stageManager->setVelocityZ(-10.0f);
			player->SetAngleY(0.0f);
			SceneManager::Instance().IsSelect = false;
			SceneManager::Instance().IsNoneStage = false;

			b_select->Stop();	// BGM停止
		}
	}
}

void SceneGame::RuleUpdate(float elapsedTime)
{
	if (ruleIn)
	{
		rulePos += 600 * elapsedTime;
		if (rulePos >= 0.0f)
		{
			rulePos = 0.0f;
			ruleIn = false;
		}
	}
	if (ruleOut)
	{
		rulePos -= 600 * elapsedTime;
		if (rulePos <= -1080.0f)
		{
			rulePos = -1080.0f;
			ruleOut = false;
			IsRule = false;
		}
	}

	// カメラ更新処理
	cameraController->Update(elapsedTime);
	// プレイヤー更新処理
	player->Update(elapsedTime);
	if(!ruleIn&&!ruleOut)
	{
		// ポーズ処理
		GamePad& gamePad = Input::Instance().GetGamePad();
		if (gamePad.GetButtonDown() & GamePad::BTN_A)
			ruleOut=true;
	}
}

void SceneGame::TransUpdate(float elapsedTime)
{
	range = lerp(range, 10.0f, 0.01f);
	target.y = lerp(target.y, player->GetPosition().y + 0.5f, 0.01f);
	target.x = lerp(target.x, player->GetPosition().x, 0.01f);

	cameraController->setTarget(target);
	cameraController->setRange(range);
	if (rotation < DirectX::XMConvertToRadians(360.0f))
	{
		rotation += DirectX::XMConvertToRadians(1.0f);
		player->SetAngleY(rotation);
	}
	else
	{
		player->SetAngleY(0.0f);
	}
}

void SceneGame::DeathUpdate(float elapsedTime)
{
	postprocessingRenderer->UpdateShold();
	cameraController->DeathCamera();
	stageManager->StageDeathUpdate(elapsedTime);
}

void SceneGame::DeathMoment()
{

	// ヒットエフェクト再生
	{
		DirectX::XMFLOAT3 e = player->GetPosition();
		hitEffect->Play(e);
	}
	postprocessingRenderer->setThreshold(0.0f);
	cameraController->flag = true;
	cameraController->setRange(cameraController->getRange() * 1.5f);
}

void SceneGame::DidFromHunger(float elapsedTime)
{
	cameraController->DidFromHungerCamera();
	//s_clash->Play(false);		// SE再生
}

// 障害物と障害物の当たり判定
void SceneGame::CollisionObsVsObs()
{
	for (auto& it : stageManager->stages)
	{
		for (auto& Obs : it->obstacles)
		{
			// 積極的に当たり判定を取らないと飛ばす
			if (Obs->HitCheckTYpe != HIT_CHECK_TYPE::ACTIVE) continue;

			DirectX::XMFLOAT3 obs1_position = Obs->GetPosition();
			float obs1_radius = Obs->GetRadius();
			float obs1_height = Obs->GetHeight();

			for (auto& Obs2 : it->obstacles)
			{
				// 当たり判定を取らない場合は飛ばす
				if (Obs2->IsHitVsObs == HIT_CHECK_TYPE::NOT) continue;

				// 同じ場合は飛ばす
				if (Obs == Obs2)continue;

				// 同じステージでなければ飛ばす
				if (Obs->GetOriginPosition() != Obs->GetOriginPosition()) continue;

				DirectX::XMFLOAT3 obs2_position = Obs2->GetPosition();
				float obs2_radius = Obs2->GetRadius();
				float obs2_height = Obs2->GetHeight();
				DirectX::XMFLOAT3 outPosition;

				// どちらもアイテム(球)タイプの場合
				if (Obs->Type == ITEMS && Obs2->Type == ITEMS)
				{
					if (Collision::IntersectSphereVsSphere(
						obs2_position,
						obs2_radius,
						obs1_position,
						obs1_radius,
						outPosition
					))
					{
						Obs->IsHitVsObs = true;
						Obs->SetPosition(outPosition);
					}
				}
				// Obs2がアイテム(球)の場合
				else if (Obs2->Type == ITEMS)
				{
					for (int n = 0; n < Obs->CollisionNum; ++n)
					{
						// 衝突判定
						if (Collision::IntersectSphereVsCylinder
						(
							obs2_position,
							obs2_radius,
							{ (Obs->GetPosition().x - (Obs->CollisionNum * Obs->GetRadius()) + Obs->GetRadius()) + (n * Obs->GetRadius() * 2.0f) ,Obs->GetPosition().y,Obs->GetPosition().z },
							obs1_radius,
							obs1_height,
							outPosition))
						{
							Obs->IsHitVsObs = true;
							Obs->SetPosition(outPosition);
						}
					}
				}
				// Obsがアイテム(球)の場合
				else if (Obs->Type == ITEMS)
				{
					for (int n2 = 0; n2 < Obs2->CollisionNum; ++n2)
					{
						// 衝突判定
						if (Collision::IntersectCylinderVsSphere
						(
							{ (Obs2->GetPosition().x - (Obs2->CollisionNum * Obs->GetRadius()) + Obs2->GetRadius()) + (n2 * Obs2->GetRadius() * 2.0f) ,Obs2->GetPosition().y,Obs2->GetPosition().z },
							obs2_radius,
							obs2_height,
							obs1_position,
							obs1_radius,
							outPosition)
							)
						{
							Obs->IsHitVsObs = true;
							Obs->SetPosition(outPosition);
						}
					}
				}
				// その他
				else
				{
					for (int n1 = 0; n1 < Obs->CollisionNum; ++n1)
					{
						for (int n2 = 0; n2 < Obs2->CollisionNum; ++n2)
						{

							// 衝突判定
							if (Collision::IntersectCylinderVsCylinder
							(
								{ (Obs2->GetPosition().x - (Obs2->CollisionNum * Obs->GetRadius()) + Obs2->GetRadius()) + (n2 * Obs2->GetRadius() * 2.0f) ,Obs2->GetPosition().y,Obs2->GetPosition().z },
								Obs2->GetRadius(),
								Obs2->GetHeight(),
								{ (Obs->GetPosition().x - (Obs->CollisionNum * Obs->GetRadius()) + Obs->GetRadius()) + (n1 * Obs->GetRadius() * 2.0f) ,Obs->GetPosition().y,Obs->GetPosition().z },
								Obs->GetRadius(),
								Obs->GetHeight(),
								outPosition)
								)
							{
								Obs->IsHitVsObs = true;
								Obs->SetPosition(outPosition);
							}
						}
					}

				}
			}
		}
	}
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

// シャドウマップの描画
void SceneGame::RenderShadowmap()
{
	Graphics& graphics = Graphics::Instance();
	ID3D11DeviceContext* dc = graphics.GetDeviceContext();
	ID3D11RenderTargetView* rtv = nullptr;
	ID3D11DepthStencilView* dsv = shadowmapDepthStencil->GetDepthStencilView().Get();
	// 画面クリア
	dc->ClearDepthStencilView(dsv, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	if (!mainDirectionalLight)
		return;
	// レンダーターゲット設定
	dc->OMSetRenderTargets(0, &rtv, dsv);
	// ビューポートの設定
	D3D11_VIEWPORT vp = {};
	vp.Width = static_cast<float>(shadowmapDepthStencil->GetWidth());
	vp.Height = static_cast<float>(shadowmapDepthStencil->GetHeight());
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	dc->RSSetViewports(1, &vp);
	// 描画処理
	RenderContext rc;
	rc.deviceContext = dc;
	// カメラパラメータ設定
	{
		// 平行光源からカメラ位置を作成し、そこから原点の位置を見るように視線行列を生成
		DirectX::XMVECTOR LightPosition = DirectX::XMLoadFloat3(&mainDirectionalLight->GetDirection());
		LightPosition = DirectX::XMVectorScale(LightPosition, -250.0f);
		DirectX::XMMATRIX V = DirectX::XMMatrixLookAtLH(LightPosition,
			DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f),
			DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f));
		// シャドウマップに描画したい範囲の射影行列を生成
		DirectX::XMMATRIX P = DirectX::XMMatrixOrthographicLH(shadowDrawRect, shadowDrawRect, 0.1f,
			1200.0f);
		DirectX::XMStoreFloat4x4(&rc.view, V);
		DirectX::XMStoreFloat4x4(&rc.projection, P);
		DirectX::XMStoreFloat4x4(&lightViewProjection, V * P);
	}
	// 3Dモデル描画
	{
		ModelShader* shader = graphics.GetShader(ModelShaderId::ShadowmapCaster);
		shader->Begin(rc);
		stageManager->ObsDraw(rc, shader);
		shader->End(rc);
	}
}

// 加速更新
void SceneGame::accelUpdate(float elapsedTime)
{
	accelFrame -= 1.0f;
	if (int(accelFrame) % 2 == 0)
	{
		p_w += 1920.0f;
		if (p_w > 5760)
		{
			p_w = 0.0f;
		}
	}

	if (accelFrame <= 0.0f)
	{
		accelFrame = 120.0f;
		accel = false;
	}
}

// 空腹ゲージの更新
void SceneGame::UpdateHungerGage()
{
	float margin = 0.0f;

	float magnification = 19.0f;								// 倍率

	float dh = 9.0f * magnification;							// 枠の描画サイズ(y)
	float dw_f = 35 * magnification;							// 枠の描画サイズ(x)
	// ゲージの描画サイズ(x)
	float dw_g = (dw_f - 9.15 * magnification) * (player->GetHungerPoint() / Player::MaxHungerPoint);
	float x_g = 9.15 * magnification + margin;							// ゲージの描画位置(x)
	float x_f = margin;											// ゲージの描画位置(x)	// ゲージの描画位置(x)
	float y = 1080.0f - dh - margin;		// 描画位置(y)

	// ゲージの色
	DirectX::XMFLOAT3 c[3] =
	{
		{0.65f,0.68f,1.0f},
		{0.489f,1.0f,0.541f},
		{1.0f,0.611f,0.56f}
	};

	// ゲージ
	sprite_hungerGage->Update(
		x_g, y,
		dw_g, dh,
		0.0f, 0.0f,
		100.0f, 100.0f,
		0.0f,
		c[player->GetHungerLevel()].x, c[player->GetHungerLevel()].y, c[player->GetHungerLevel()].z, 1.0f);
	// フレーム
	sprite_hungerGageFrame->Update(
		x_f, y,
		dw_f, dh,
		0.0f, static_cast<float>(texture_hungerGageFrame->GetHeight() / 3) * player->GetHungerLevel(),
		static_cast<float>(texture_hungerGageFrame->GetWidth()), static_cast<float>(texture_hungerGageFrame->GetHeight() / 3),
		0.0f,
		1.0f, 1.0f, 1.0f, 1.0f);
	// 背景
	sprite_hungerGageBack->Update(
		x_f, y,
		dw_f, dh,
		0.0f, static_cast<float>(texture_hungerGageFrame->GetHeight() / 3) * player->GetHungerLevel(),
		static_cast<float>(texture_hungerGageFrame->GetWidth()), static_cast<float>(texture_hungerGageFrame->GetHeight() / 3),
		0.0f,
		1.0f, 1.0f, 1.0f, 1.0f);
}

void SceneGame::UpdateStageUI()
{
	float screen_width = 1920.0f;

	const int MaxFrame = 20;		// 1枚当たりの表示フレーム数
	const int SpriteMax = 4;		// アニメのスプライトの最大数
	static int frame = 0;			// 現在のフレーム
	frame += 1;

	// 最後のスプライトの表示が終わったら
	if (MaxFrame * (SpriteMax + 1) <= frame)
	{
		frame = 0;
	}

	// アニメ番号
	float anime = static_cast<float>(frame / MaxFrame);

	// 切り抜きサイズ
	float sw = 500.0f;
	float sh = 300.0f;
	// 描画位置
	float dx_end = screen_width - sw; // 描画位置の終点
	float dx = 1920.0f - sw;
	float dy = 0.0f;
	// 描画サイズ
	float dw = sw;
	float dh = sh;
	// 切り抜き位置
	float sx = anime * sw;
	float sy = sh * (stageManager->GetStageNo() - 1);

	// 速度
	float speed = 10.0f;

	// 休憩フラグが立っているとき
	if (stageManager->IsBreakTime)
	{
		StageUI_Position.x = lerp<float>(StageUI_Position.x,dx_end,0.05f);

		// アニメーションしたい
	}
	if (!stageManager->IsBreakTime)
	{
		StageUI_Position.x = lerp<float>(StageUI_Position.x, screen_width, 0.05f);
	}

	// 背景
	sprite_StageUI->Update(
		StageUI_Position.x, StageUI_Position.y,
		dw, dh,
		sx, sy,
		sw, sh,
		0.0f,
		1.0f, 1.0f, 1.0f, 1.0f);
}

// 3D空間の描画
void SceneGame::Render3DScene()
{
	Graphics& graphics = Graphics::Instance();
	ID3D11DeviceContext* dc = graphics.GetDeviceContext();
	ID3D11RenderTargetView* rtv = renderTarget->GetRenderTargetView().Get();
	ID3D11DepthStencilView* dsv = graphics.GetDepthStencilView();
	// 画面クリア＆レンダーターゲット設定
	FLOAT color[] = { 0.89f, 0.75f, 0.94f, 1.0f }; // RGBA(0.0～1.0)
	dc->ClearRenderTargetView(rtv, color);
	dc->ClearDepthStencilView(dsv, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	dc->OMSetRenderTargets(1, &rtv, dsv);
	// ビューポートの設定
	D3D11_VIEWPORT vp = {};
	vp.Width = graphics.GetScreenWidth();
	vp.Height = graphics.GetScreenHeight();
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	dc->RSSetViewports(1, &vp);
	// 描画処理
	RenderContext rc;
	rc.deviceContext = dc;

	// ライトの情報を詰め込む
	LightManager::Instane().PushRenderContext(rc);

	// シャドウマップの設定
	rc.shadowMapData.shadowMap = shadowmapDepthStencil->GetShaderResourceView().Get();
	rc.shadowMapData.lightViewProjection = lightViewProjection;
	rc.shadowMapData.shadowColor = shadowColor;
	rc.shadowMapData.shadowBias = shadowBias;

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