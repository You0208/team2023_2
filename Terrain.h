#pragma once
#include <vector>
#include "Graphics/Shader.h"
#include "Graphics/Model.h"
#include "BaseStage.h"

// �n��
class Terrain : public BaseStage
{
public:
    static const int StageSideMax       = 2;        // �X�e�[�W�̍ő吔(���E)
    static const int StageDepthMax      = 3;        // �X�e�[�W�̍ő吔(���s)
    static constexpr float StageSize    = 500.0f;    // �X�e�[�W�̃T�C�Y
public:
    Terrain();

    void DrawDebugGUI() {};

    // ������
    void Initialize();

    // �X�V����
    void Update(float elapsedTime);

    // �`�揈��
    void Draw(RenderContext rc, ModelShader* shader);
};

