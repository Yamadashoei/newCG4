#include "Effect.h"
#include <cassert>

using namespace KamataEngine;
using namespace MathUtility;

void Effect::Initialize(Model* model, Vector3 scale, Vector3 rotation) {
	assert(model);
	model_ = model;

	worldTransform_.Initialize();
	worldTransform_.scale_ = scale;
	worldTransform_.rotation_ = rotation;

	objectColor_.Initialize();
	color_ = {1, 1, 1, 1}; // 白
}

void Effect::Update() {
	worldTransform_.UpdateMatrix();
	objectColor_.SetColor(color_);
}

void Effect::Draw(Camera& camera) {
	if (model_) {
		model_->Draw(worldTransform_, camera, &objectColor_);
	}
}
