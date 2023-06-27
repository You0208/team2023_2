#include "Terrain.h"

// �R���X�g���N�^
Terrain::Terrain()
{
    //�X�e�[�W���f����ǂݍ���
    model = std::make_unique<Model>("Data/Model/Debug/cube.mdl");
    scale = { StageSize,0.5f ,StageSize };
    stageSideMax = StageSideMax;
    stageDepthMax = StageDepthMax;
}

// ������
void Terrain::Initialize()
{
}

// �X�V����
void Terrain::Update(float elapsedTime)
{
    // �X�N���[��
    UpdateVelocity(elapsedTime);

    //�s��X�V
    UpdateTransform();

    //���f���s��X�V
    if (model != nullptr)
        model->UpdateTransform(transform);

    // �X�e�[�W����
    StageSpawn();

    // �X�e�[�W�폜
    StageDelete();
}

// �`�揈��
void Terrain::Draw(RenderContext rc, ModelShader* shader)
{
    //�X�e�[�W�`��
    if (model != nullptr)
        shader->Draw(rc, model.get());
}
