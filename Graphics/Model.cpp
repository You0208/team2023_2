#include "Graphics/Graphics.h"
#include "Graphics/Model.h"
#include "ResourceManager.h"

// �R���X�g���N�^
Model::Model(const char* filename)
{
	// ���\�[�X�ǂݍ���
	resource = ResourceManager::Instance().LoadModelResource(filename);

	// �m�[�h
	const std::vector<ModelResource::Node>& resNodes = resource->GetNodes();

	nodes.resize(resNodes.size());
	for (size_t nodeIndex = 0; nodeIndex < nodes.size(); ++nodeIndex)
	{
		auto&& src = resNodes.at(nodeIndex);
		auto&& dst = nodes.at(nodeIndex);

		dst.name = src.name.c_str();
		dst.parent = src.parentIndex >= 0 ? &nodes.at(src.parentIndex) : nullptr;
		dst.scale = src.scale;
		dst.rotate = src.rotate;
		dst.translate = src.translate;

		if (dst.parent != nullptr)
		{
			dst.parent->children.emplace_back(&dst);
		}
	}

	// �s��v�Z
	const DirectX::XMFLOAT4X4 transform = { 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 };
	UpdateTransform(transform);
}

// �ϊ��s��v�Z
void Model::UpdateTransform(const DirectX::XMFLOAT4X4& transform)
{
	DirectX::XMMATRIX Transform = DirectX::XMLoadFloat4x4(&transform);

	for (Node& node : nodes)
	{
		// ���[�J���s��Z�o
		DirectX::XMMATRIX S = DirectX::XMMatrixScaling(node.scale.x, node.scale.y, node.scale.z);
		DirectX::XMMATRIX R = DirectX::XMMatrixRotationQuaternion(DirectX::XMLoadFloat4(&node.rotate));
		DirectX::XMMATRIX T = DirectX::XMMatrixTranslation(node.translate.x, node.translate.y, node.translate.z);
		DirectX::XMMATRIX LocalTransform = S * R * T;

		// ���[���h�s��Z�o
		DirectX::XMMATRIX ParentTransform;
		if (node.parent != nullptr)
		{
			ParentTransform = DirectX::XMLoadFloat4x4(&node.parent->worldTransform);
		}
		else
		{
			ParentTransform = Transform;
		}
		DirectX::XMMATRIX WorldTransform = LocalTransform * ParentTransform;

		// �v�Z���ʂ��i�[
		DirectX::XMStoreFloat4x4(&node.localTransform, LocalTransform);
		DirectX::XMStoreFloat4x4(&node.worldTransform, WorldTransform);
	}
}


// �A�j���[�V�����X�V����
void Model::UpdateAnimation(float elapsedTIme)
{
	// �Đ����łȂ��Ȃ珈�����Ȃ�
	if (!IsPlayAnimation()) return;

	// �u�����h���̌v�Z
	float blendRate = 1.0f;

	// TODO: �搶�ɕ���
	if (animationBlendTIme >= -animationBlendSeconds
		&& animationBlendTIme < animationBlendSeconds)
	{
		animationBlendTIme = currentAnimationSeconds;
	}

	//�@�u�����h���v�Z
	blendRate = (currentAnimationSeconds - animationBlendTIme) / animationBlendSeconds;


	// �w��̃A�j���[�V�����f�[�^���擾
	const std::vector<ModelResource::Animation>& animations = resource->GetAnimations();		// ���\�[�X�̃A�j���[�V�����擾(resource->GetAnimations()���ȗ����邽�߂̋L�q���Ă���)
	const ModelResource::Animation& animation = animations.at(currentAnimationIndex);			// �w��̃A�j���[�V�����f�[�^���擾

	// �A�j���[�V�����f�[�^����L�[�t���[���f�[�^���X�g���擾
	const std::vector<ModelResource::Keyframe>& keyframes = animation.keyframes;
	int keyCount = static_cast<int>(keyframes.size());
	for (int keyIndex = 0; keyIndex < keyCount - 1; ++keyIndex)
	{
		// ���݂̎��Ԃ��ǂ̃L�[�t���[���̊Ԃɂ���̂����肷��
		const ModelResource::Keyframe& keyframe0 = keyframes.at(keyIndex);
		const ModelResource::Keyframe& keyframe1 = keyframes.at(keyIndex + 1);

		// �o�ߎ��Ԃ��Đ����ԓ��Ȃ�
		if (currentAnimationSeconds >= keyframe0.seconds &&
			currentAnimationSeconds < keyframe1.seconds)
		{
			// �Đ����ԂƃL�[�t���[���̎��Ԃ�����ԗ����Z�o����
			float rate = (currentAnimationSeconds - keyframe0.seconds)
				/ (keyframe1.seconds - keyframe0.seconds);

			int nodeCount = static_cast<int>(nodes.size());

			// �Đ����ԂƃL�[�t���[���̎��Ԃ����ԗ����v�Z����
			for (int nodeIndex = 0; nodeIndex < nodeCount; ++nodeIndex)
			{
				// 2�̃L�[�t���[���Ԃ̕�Ԍv�Z
				const ModelResource::NodeKeyData& key0 = keyframe0.nodeKeys.at(nodeIndex);
				const ModelResource::NodeKeyData& key1 = keyframe1.nodeKeys.at(nodeIndex);

				Node& node = nodes[nodeIndex];

				// �u�����h��ԏ���
				// ���݂͋@�\���Ă��Ȃ�
				if (blendRate < 1.0f)
				{
					// ���݂̎p���Ǝ��̃L�[�t���[���Ƃ̎p���̕��
					
					// �p�x�̐��`���
					DirectX::XMVECTOR Now_Rotate = DirectX::XMLoadFloat4(&node.rotate);		// ���̎p��
					DirectX::XMVECTOR Key0_Rotate = DirectX::XMLoadFloat4(&key1.rotate);	// ���̃L�[�t���[���̎p��
					DirectX::XMVECTOR rotate =
						DirectX::XMQuaternionSlerp(Now_Rotate, Key0_Rotate, blendRate);

					// ���W�̐��`���
					DirectX::XMVECTOR Now_Translate = DirectX::XMLoadFloat3(&node.translate);
					DirectX::XMVECTOR Key0_Translate = DirectX::XMLoadFloat3(&key1.translate);
					DirectX::XMVECTOR translate =
						DirectX::XMVectorLerp(Now_Translate, Key0_Translate, blendRate);

					// ��Ԍ��ʂ�ݒ�
					node.scale = key1.scale;
					DirectX::XMStoreFloat4(&node.rotate, rotate);
					DirectX::XMStoreFloat3(&node.translate, translate);
				}
				// �ʏ�̌v�Z
				else {

					// �O�̃L�[�t���[���Ǝ��̃L�[�t���[���̎p������

					// �p�x�̐��`���
					DirectX::XMVECTOR Key0_Rotate = DirectX::XMLoadFloat4(&key0.rotate);
					DirectX::XMVECTOR Key1_rotate = DirectX::XMLoadFloat4(&key1.rotate);
					DirectX::XMVECTOR rotate =
						DirectX::XMQuaternionSlerp(Key0_Rotate, Key1_rotate, rate);

					// ���W�̐��`���
					DirectX::XMVECTOR Key0_Translate = DirectX::XMLoadFloat3(&key0.translate);
					DirectX::XMVECTOR Key1_Translate = DirectX::XMLoadFloat3(&key1.translate);
					DirectX::XMVECTOR translate =
						DirectX::XMVectorLerp(Key0_Translate, Key1_Translate, rate);

					// ��Ԍ��ʂ�ݒ�
					node.scale = key0.scale;
					DirectX::XMStoreFloat4(&node.rotate, rotate);
					DirectX::XMStoreFloat3(&node.translate, translate);
				}
			}
			break;
		}
	}

	// �ŏI�t���[��
	if (animationEndFlag)
	{
		animationEndFlag = false;
		currentAnimationIndex = -1;
		return;
	}

	// ���Ԍo��
	currentAnimationSeconds += elapsedTIme;

	// �Đ����Ԃ��I�[���Ԃ𒴂�����
	if (currentAnimationSeconds >= animation.secondsLength)
	{
		// ���[�v�Đ�����ꍇ
		if (animationLoopFlag)
		{
			// �Đ����Ԃ�҂��߂�
			currentAnimationSeconds -= animation.secondsLength;
			return;
		}
		// ���[�v�Đ����Ȃ��ꍇ
		else
		{
			animationEndFlag = true;
		}
	}
}

// �A�j���[�V�����Đ�[17]
void Model::PlayAnimation(int index, bool loop, float blendSeconds)
{
	currentAnimationIndex = index;
	currentAnimationSeconds = 0.0f;

	animationLoopFlag = loop;
	animationEndFlag = false;

	animationBlendTIme = 0.0f;
	animationBlendSeconds = blendSeconds;
}

// �A�j���[�V�����Đ�����[17]
bool Model::IsPlayAnimation() const
{
	// �A�j���[�V�����ԍ���0�ȉ��Ȃ�
	if (currentAnimationIndex < 0)return false;
	// �A�j���[�V�����ԍ����ۑ�����Ă���A�j���[�V�����̐��ȏ�Ȃ�
	if (currentAnimationIndex >= resource->GetAnimations().size()) return false;

	return true;
}