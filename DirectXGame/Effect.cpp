#include "Effect.h"

using namespace KamataEngine;
using namespace MathUtility;

void Effect::Initialize(KamataEngine::Model* model, Vector3 position) {
	assert(model);

	model_ = model;
	// ワールド変換の初期化
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;

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

void Effect::Draw(KamataEngine::Camera& camera) {
	// 3Dモデルを描画
	model_->Draw(worldTransform_, camera, &objectColor_);
}