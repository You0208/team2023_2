#pragma once

#include <memory>
#include <vector>
#include <DirectXMath.h>
#include "Graphics/ModelResource.h"

// ���f��
class Model
{
public:
	Model(const char* filename);
	~Model() {}

	struct Node
	{
		const char* name;
		Node* parent;
		DirectX::XMFLOAT3	scale;
		DirectX::XMFLOAT4	rotate;
		DirectX::XMFLOAT3	translate;
		DirectX::XMFLOAT4X4	localTransform;
		DirectX::XMFLOAT4X4	worldTransform;

		std::vector<Node*>	children;
	};

	// �s��v�Z
	void UpdateTransform(const DirectX::XMFLOAT4X4& transform);

	// �m�[�h���X�g�擾
	const std::vector<Node>& GetNodes() const { return nodes; }
	std::vector<Node>& GetNodes() { return nodes; }

	// ���\�[�X�擾
	const ModelResource* GetResource() const { return resource.get(); }

	// �A�j���[�V�����X�V����[17]
	void UpdateAnimation(float elapsedTIme);

	// �A�j���[�V�����Đ�[17]
	void PlayAnimation(int index, bool loop, float blendSeconds = 0.2f);

	// �A�j���[�V�����Đ�����[17]
	bool IsPlayAnimation()const;

private:
	std::shared_ptr<ModelResource>	resource;
	std::vector<Node>				nodes;

	// [17]
	// ���݂̃A�j���[�V�����ԍ�
	int currentAnimationIndex = -1;
	float currentAnimationSeconds = 0.0f;	// �o�ߎ���
	bool animationLoopFlag = false;
	bool animationEndFlag = false;
	float animationBlendTIme = 0.0f;
	float animationBlendSeconds = 0.0f;
};