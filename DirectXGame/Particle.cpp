#include "Particle.h"
#include <cassert>
using namespace KamataEngine;
using namespace MathUtility;

void Particle::Initialize(Model* model, Vector3 position, Vector3 velocity) {
	// Nullチェック
	assert(model);
	// 引数として受け取ったデータをメンバ変数に記録する
	modelParticle_ = model; // モデルの初期化
	velocity_ = velocity;   // 速度の初期化

	worldTransform_.Initialize();                // ワールド変換の初期化
	worldTransform_.translation_ = position;     // ワールド変換のスケールを設定
	worldTransform_.scale_ = {0.2f, 0.2f, 0.2f}; // ワールド変換のスケールを設定

	objectColor_.Initialize(); // 色の設定
	color_ = {1, 1, 0, 1};     // 色の初期値を設定
}

void Particle::Update() {

	// 移動
	worldTransform_.translation_ += velocity_;
	// 行列を更新
	worldTransform_.UpdateMatrix();

	// 色変更オブジェクトに色の数値を設定
	objectColor_.SetColor(color_);
}

void Particle::Draw(Camera& camera) {
	// 3Dモデルの描画
	modelParticle_->Draw(worldTransform_, camera, &objectColor_);
}