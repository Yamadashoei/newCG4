#pragma once
#include "KamataEngine.h"
#include <3d/Camera.h>
#include <3d/Model.h>
#include <3d/WorldTransform.h>

class Particle {

public:
	// 初期化
	void Initialize(KamataEngine::Model* model, KamataEngine::Vector3 position);
	// 更新
	void Update();
	// 描画
	void Draw(KamataEngine::Camera& camera);

private:
	// ワールド変換
	KamataEngine::WorldTransform worldTransform_;
	// モデル
	KamataEngine::Model* modelParticle_ = nullptr;

	// 色変更オブジェクト
	KamataEngine::ObjectColor objectColor_;
	// 色の数値
	KamataEngine::Vector4 color_;
};