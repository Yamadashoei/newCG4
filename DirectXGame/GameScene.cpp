#include "GameScene.h"
#include <cassert>
#include <random>
using namespace KamataEngine;
using namespace MathUtility;

std::random_device seedGenerator;
std::mt19937 randomEngine(seedGenerator());
std::uniform_real_distribution<float> distribution(-1.0f, 1.0f);

GameScene::GameScene() {}

GameScene::~GameScene() {
	delete modelParticle_;
	for (Particle* particle_ : particles_) {
		// パーティクル解放
		delete particle_;
	}
	particles_.clear();
}

void GameScene::Initialize() {
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	// モデルの生成
	modelParticle_ = Model ::CreateSphere(4, 4);
	// カメラの初期化
	camera_.Initialize();

	for (int i = 0; i < 150; i++) {
		// パーティクルの生成
		Particle* particle_ = new Particle();
		// 位置
		Vector3 position = {0.0f, 0.0f, 0.0f};
		Vector3 velocity = {distribution(randomEngine), distribution(randomEngine), 0.0f};
		// 速度
		Normalize(velocity);
		velocity *= distribution(randomEngine); // 速度の大きさをランダムにする
		velocity *= 0.1f;                       // 速度の大きさを1.0fにする

		/*初期化*/
		particle_->Initialize(modelParticle_, position, velocity);
		// リストに追加
		particles_.push_back(particle_);
	}
}

void GameScene::Update() {
	/// パーティクルの更新
	for (Particle* particle_ : particles_) {
		particle_->Update();
	}
}

void GameScene::Draw() {
	// DirectXCommon インスタンスの取得
	// DirectXCommon* dxCommon = DirectXCommon::GetInstance();
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	// パーティクルの描画
	for (Particle* particle_ : particles_) {
		particle_->Draw(camera_);
	}

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}