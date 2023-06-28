#include "Graphics/Graphics.h"
#include "SceneGame.h"
#include "Camera.h"
#include "LightManager.h"
#include "EffectManager.h"
#include "Input/Input.h"
#include "Stage.h"

//-------------------------------------------------------------------------------------------------------
// 
//		 �Q�[���V�[��
// 
//-------------------------------------------------------------------------------------------------------

// ������
void SceneGame::Initialize()
{
	//�v���C���[�����ݒ�
	player = new Player();

	// �󏉊��ݒ�
	sky = new Sky();

	// �X�e�[�W�}�l�[�W���[�����ݒ�
	stageManager = new StageManager;

	BaseStage::clear();

	// �X�e�[�W����
	for (int z = 0; z < Stage::StageDepthMax; ++z)
	{
		for (int x = 0; x < Stage::StageSideMax; ++x)
		{
			float X = (-((Stage::StageSideMax - 1) * 0.5f) + x) * Stage::StageSize;
			float Z = (z * Stage::StageSize);

			stageManager->StageSpawn({ X,0.0f,Z });
		}
	}

	// �n�`����
	for (int z = 0; z < Terrain::StageDepthMax; ++z)
	{
		for (int x = 0; x < Terrain::StageSideMax; ++x)
		{
			float X = (-((Terrain::StageSideMax - 1) * 0.5f) + x) * Terrain::StageSize;
			float Z = (z * Terrain::StageSize);

			stageManager->TerrainSpawn({ X,0.0f,Z });
		}
	}

	//�J���������ݒ�
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

	// �J�����R���g���[���[�̏�����
	cameraController = new CameraController();


	//-------------------------------------------------------------------------------------------------------
	// ���@���̉��̓V�F�[�_�[�֘A
	//-------------------------------------------------------------------------------------------------------
	// �e�N�X�`����ǂݍ���
	texture = std::make_unique<Texture>("Data/Texture/1920px-Equirectangular-projection.jpg");

	// �X�v���C�g
	sprite = std::make_unique<Sprite>();
	sprite->SetShaderResourceView(texture->GetShaderResourceView(), texture->GetWidth(), texture->GetHeight());

	// �}�X�N�e�N�X�`���̓ǂݍ���
	maskTexture = std::make_unique<Texture>("Data/Texture/dissolve_animation.png");
	dissolveThreshold = 0.0f;
	edgeThreshold = 0.2f; // ����臒l
	edgeColor = { 1, 0, 0, 1 }; // ���̐F

	LightManager::Instane().Register(new Light(LightType::Directional));

}

// �I����
void SceneGame::Finalize()
{
	// �X�e�[�W�I��
	stageManager->Clear();
	// �v���C���[�I��
	if (player != nullptr)
	{
		delete player;
		player = nullptr;
	}
	// ��I��
	if (sky != nullptr)
	{
		delete sky;
		sky = nullptr;
	}
}

// �X�V����
void SceneGame::Update(float elapsedTime)
{
	// �J�����R���g���[���[�X�V������
	DirectX::XMFLOAT3 target = player->GetPosition();
	target.y += 0.5f;
	cameraController->setTarget(target);
	cameraController->Update(elapsedTime);

	// �|�[�Y����
	GamePad& gamePad = Input::Instance().GetGamePad();
	if (gamePad.GetButtonDown() & GamePad::BTN_X)
		isPaused = !isPaused;       // 0�R���̃X�^�[�g�{�^���������ꂽ��|�[�Y��Ԃ����]
	if (isPaused) return;           // ���̎��_�Ń|�[�Y���Ȃ烊�^�[��

	//�v���C���[�X�V����
	player->Update(elapsedTime);

	//�X�e�[�W�X�V����
	stageManager->Update(player, elapsedTime);

	//��X�V����
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

	// �G�t�F�N�g�̍X�V����
	EffectManager::Instance().Update(elapsedTime);
}

// �`�揈��
void SceneGame::Render()
{
	// 3D��Ԃ̕`���ʂ̃o�b�t�@�ɑ΂��čs��
	Render3DScene();
	// 2D�X�v���C�g�`��
	{
		// ���͉����`�悵�Ȃ�
	}

	// �f�o�b�O���̕\��
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
	// 2D�f�o�b�OGUI�`��
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

// �O���b�h�`��
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

	// X��
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

	// Y��
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

	// Z��
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

// 3D��Ԃ̕`��
void SceneGame::Render3DScene()
{
	Graphics& graphics = Graphics::Instance();
	ID3D11DeviceContext* dc = graphics.GetDeviceContext();
	ID3D11RenderTargetView* rtv = graphics.GetRenderTargetView();
	ID3D11DepthStencilView* dsv = graphics.GetDepthStencilView();

	// ��ʃN���A�������_�[�^�[�Q�b�g�ݒ�
	FLOAT color[] = { 0.0f, 0.0f, 0.5f, 1.0f }; // RGBA(0.0�`1.0)
	dc->ClearRenderTargetView(rtv, color);
	dc->ClearDepthStencilView(dsv, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	dc->OMSetRenderTargets(1, &rtv, dsv);
	// �`�揈��
	RenderContext rc;
	rc.deviceContext = dc;
	// ���C�g�̏����l�ߍ���
	LightManager::Instane().PushRenderContext(rc);
	// �J�����p�����[�^�ݒ�
	Camera& camera = Camera::Instance();
	rc.viewPosition.x = camera.GetEye().x;
	rc.viewPosition.y = camera.GetEye().y;
	rc.viewPosition.z = camera.GetEye().z;
	rc.viewPosition.w = 1;
	rc.view = camera.GetView();
	rc.projection = camera.GetProjection();
	// 3D���f���`��
	{
		ModelShader* shader = graphics.GetShader(ModelShaderId::Toon);
		shader->Begin(rc);
		//shader->Draw(rc, stage->model.get());
		sky->Draw(rc, shader);
		stageManager->Draw(rc, shader);
		player->Draw(rc, shader);
		shader->End(rc);
	}
	// 3D�G�t�F�N�g�`��
	{
		EffectManager::Instance().Render(rc.view, rc.projection);
	}
	// �f�o�b�O�v���~�e�B�u�̕\��
	{
		// ���C�g�̃f�o�b�O�v���~�e�B�u�̕`��
		LightManager::Instane().DrawDebugPrimitive();
		// ���C�������_���`����s
		graphics.GetLineRenderer()->Render(dc, camera.GetView(), camera.GetProjection());
		// �f�o�b�O�����_���`����s
		graphics.GetDebugRenderer()->Render(dc, camera.GetView(), camera.GetProjection());
	}
}