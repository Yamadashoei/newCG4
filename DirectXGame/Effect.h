#pragma once
#include <KamataEngine.h>

using namespace KamataEngine;
using namespace MathUtility;

// エフェクト
class Effect {
public:
	// 初期化
	void Initialize(KamataEngine::Model* model, Vector3 position);

	// 更新
	void Update();

	// 描画
	void Draw(KamataEngine::Camera& camera);

private:
	// ワールド変換データ
	KamataEngine::WorldTransform worldTransform_;
	// モデル
	KamataEngine::Model* model_ = nullptr;
	// 色変更オブジェクト
	KamataEngine::ObjectColor objectColor_;
	// 色の数値
	KamataEngine::Vector4 color_;
};