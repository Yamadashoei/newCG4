#pragma once
#include "KamataEngine.h"
#include "Particle.h"

#include <3d/Camera.h>
#include <3d/Model.h>
#include <3d/WorldTransform.h>
#include <base\DirectXCommon.h>

class GameScene {

public:
	// コンストラクタ
	GameScene();
	// デストラクタ
	~GameScene();

	// 初期化
	void Initialize();
	// 更新
	void Update();
	// 描画
	void Draw();

	// パーティクル発生
	void ParticleBorn(KamataEngine::Vector3 position);

private:
	KamataEngine::DirectXCommon* dxCommon_ = nullptr;
	KamataEngine::Input* input_ = nullptr;
	KamataEngine::Audio* audio_ = nullptr;

	// パーティクルモデル
	KamataEngine::Model* modelParticle_ = nullptr;
	// カメラ
	KamataEngine::Camera camera_;

	// パーティクル
	std::list<Particle*> particles_; // Particle* particle_ = nullptr;
};