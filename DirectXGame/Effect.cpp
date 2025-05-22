#include "Effect.h"
#include <cassert>

using namespace KamataEngine;
using namespace MathUtility;

void Effect::Initialize(Model* model, Vector3 scale, Vector3 rotation) {
	assert(model);
	model_ = model;

	// ワールド変換の初期化
	worldTransform_.Initialize();
	worldTransform_.scale_ = scale;
	worldTransform_.rotation_ = rotation;
	worldTransform_.translation_ = {0.0f, 0.0f, 0.0f}; // 原点固定（安全のため明示）

	// 色の設定
	objectColor_.Initialize();
	color_ = {1, 1, 0, 1};
}

void Effect::Update() {
	// 行列を定数バッファに転送
	worldTransform_.UpdateMatrix();
	// 色変更オブジェクトに色の数値を設定する
	objectColor_.SetColor(color_);
}

void Effect::Draw(Camera& camera) {
	// 3Dモデルを描画
	model_->Draw(worldTransform_, camera);
}
