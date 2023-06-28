#include "Graphics/Graphics.h"
#include "Graphics/Model.h"
#include "ResourceManager.h"

// コンストラクタ
Model::Model(const char* filename)
{
	// リソース読み込み
	resource = ResourceManager::Instance().LoadModelResource(filename);

	// ノード
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

	// 行列計算
	const DirectX::XMFLOAT4X4 transform = { 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 };
	UpdateTransform(transform);
}

// 変換行列計算
void Model::UpdateTransform(const DirectX::XMFLOAT4X4& transform)
{
	DirectX::XMMATRIX Transform = DirectX::XMLoadFloat4x4(&transform);

	for (Node& node : nodes)
	{
		// ローカル行列算出
		DirectX::XMMATRIX S = DirectX::XMMatrixScaling(node.scale.x, node.scale.y, node.scale.z);
		DirectX::XMMATRIX R = DirectX::XMMatrixRotationQuaternion(DirectX::XMLoadFloat4(&node.rotate));
		DirectX::XMMATRIX T = DirectX::XMMatrixTranslation(node.translate.x, node.translate.y, node.translate.z);
		DirectX::XMMATRIX LocalTransform = S * R * T;

		// ワールド行列算出
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

		// 計算結果を格納
		DirectX::XMStoreFloat4x4(&node.localTransform, LocalTransform);
		DirectX::XMStoreFloat4x4(&node.worldTransform, WorldTransform);
	}
}


// アニメーション更新処理
void Model::UpdateAnimation(float elapsedTIme)
{
	// 再生中でないなら処理しない
	if (!IsPlayAnimation()) return;

	// ブレンド率の計算
	float blendRate = 1.0f;

	// TODO: 先生に聞く
	if (animationBlendTIme >= -animationBlendSeconds
		&& animationBlendTIme < animationBlendSeconds)
	{
		animationBlendTIme = currentAnimationSeconds;
	}

	//　ブレンド率計算
	blendRate = (currentAnimationSeconds - animationBlendTIme) / animationBlendSeconds;


	// 指定のアニメーションデータを取得
	const std::vector<ModelResource::Animation>& animations = resource->GetAnimations();		// リソースのアニメーション取得(resource->GetAnimations()を省略するための記述している)
	const ModelResource::Animation& animation = animations.at(currentAnimationIndex);			// 指定のアニメーションデータを取得

	// アニメーションデータからキーフレームデータリストを取得
	const std::vector<ModelResource::Keyframe>& keyframes = animation.keyframes;
	int keyCount = static_cast<int>(keyframes.size());
	for (int keyIndex = 0; keyIndex < keyCount - 1; ++keyIndex)
	{
		// 現在の時間がどのキーフレームの間にいるのか判定する
		const ModelResource::Keyframe& keyframe0 = keyframes.at(keyIndex);
		const ModelResource::Keyframe& keyframe1 = keyframes.at(keyIndex + 1);

		// 経過時間が再生時間内なら
		if (currentAnimationSeconds >= keyframe0.seconds &&
			currentAnimationSeconds < keyframe1.seconds)
		{
			// 再生時間とキーフレームの時間かた補間率を算出する
			float rate = (currentAnimationSeconds - keyframe0.seconds)
				/ (keyframe1.seconds - keyframe0.seconds);

			int nodeCount = static_cast<int>(nodes.size());

			// 再生時間とキーフレームの時間から補間率を計算する
			for (int nodeIndex = 0; nodeIndex < nodeCount; ++nodeIndex)
			{
				// 2つのキーフレーム間の補間計算
				const ModelResource::NodeKeyData& key0 = keyframe0.nodeKeys.at(nodeIndex);
				const ModelResource::NodeKeyData& key1 = keyframe1.nodeKeys.at(nodeIndex);

				Node& node = nodes[nodeIndex];

				// ブレンド補間処理
				// 現在は機能していない
				if (blendRate < 1.0f)
				{
					// 現在の姿勢と次のキーフレームとの姿勢の補間
					
					// 角度の線形補間
					DirectX::XMVECTOR Now_Rotate = DirectX::XMLoadFloat4(&node.rotate);		// 今の姿勢
					DirectX::XMVECTOR Key0_Rotate = DirectX::XMLoadFloat4(&key1.rotate);	// 次のキーフレームの姿勢
					DirectX::XMVECTOR rotate =
						DirectX::XMQuaternionSlerp(Now_Rotate, Key0_Rotate, blendRate);

					// 座標の線形補間
					DirectX::XMVECTOR Now_Translate = DirectX::XMLoadFloat3(&node.translate);
					DirectX::XMVECTOR Key0_Translate = DirectX::XMLoadFloat3(&key1.translate);
					DirectX::XMVECTOR translate =
						DirectX::XMVectorLerp(Now_Translate, Key0_Translate, blendRate);

					// 補間結果を設定
					node.scale = key1.scale;
					DirectX::XMStoreFloat4(&node.rotate, rotate);
					DirectX::XMStoreFloat3(&node.translate, translate);
				}
				// 通常の計算
				else {

					// 前のキーフレームと次のキーフレームの姿勢を補間

					// 角度の線形補間
					DirectX::XMVECTOR Key0_Rotate = DirectX::XMLoadFloat4(&key0.rotate);
					DirectX::XMVECTOR Key1_rotate = DirectX::XMLoadFloat4(&key1.rotate);
					DirectX::XMVECTOR rotate =
						DirectX::XMQuaternionSlerp(Key0_Rotate, Key1_rotate, rate);

					// 座標の線形補間
					DirectX::XMVECTOR Key0_Translate = DirectX::XMLoadFloat3(&key0.translate);
					DirectX::XMVECTOR Key1_Translate = DirectX::XMLoadFloat3(&key1.translate);
					DirectX::XMVECTOR translate =
						DirectX::XMVectorLerp(Key0_Translate, Key1_Translate, rate);

					// 補間結果を設定
					node.scale = key0.scale;
					DirectX::XMStoreFloat4(&node.rotate, rotate);
					DirectX::XMStoreFloat3(&node.translate, translate);
				}
			}
			break;
		}
	}

	// 最終フレーム
	if (animationEndFlag)
	{
		animationEndFlag = false;
		currentAnimationIndex = -1;
		return;
	}

	// 時間経過
	currentAnimationSeconds += elapsedTIme;

	// 再生時間が終端時間を超えたら
	if (currentAnimationSeconds >= animation.secondsLength)
	{
		// ループ再生する場合
		if (animationLoopFlag)
		{
			// 再生時間を待ち戻す
			currentAnimationSeconds -= animation.secondsLength;
			return;
		}
		// ループ再生しない場合
		else
		{
			animationEndFlag = true;
		}
	}
}

// アニメーション再生[17]
void Model::PlayAnimation(int index, bool loop, float blendSeconds)
{
	currentAnimationIndex = index;
	currentAnimationSeconds = 0.0f;

	animationLoopFlag = loop;
	animationEndFlag = false;

	animationBlendTIme = 0.0f;
	animationBlendSeconds = blendSeconds;
}

// アニメーション再生中か[17]
bool Model::IsPlayAnimation() const
{
	// アニメーション番号が0以下なら
	if (currentAnimationIndex < 0)return false;
	// アニメーション番号が保存されているアニメーションの数以上なら
	if (currentAnimationIndex >= resource->GetAnimations().size()) return false;

	return true;
}