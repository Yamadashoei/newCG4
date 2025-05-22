#include "GameScene.h"
#include <random>

using namespace KamataEngine;
using namespace MathUtility;

GameScene::~GameScene() {
	delete modelEffect_;
	for (Effect* e : effects_)
		delete e;
	effects_.clear();
}

void GameScene::Initialize() {
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	modelEffect_ = Model::CreateFromOBJ("effect", true);

	// カメラ設定
	camera_.Initialize();
	camera_.translation_.z = -10.0f;
	camera_.UpdateMatrix();

	// ランダム初期化
	std::random_device seedGen;
	std::mt19937 engine(seedGen());
	std::uniform_real_distribution<float> scaleXDist(0.03f, 0.1f);     // 太さ（横）
	std::uniform_real_distribution<float> scaleYDist(0.5f, 1.0f);     // 長さ（縦）
	std::uniform_real_distribution<float> rotOffsetDist(0.0f, 3.14f); // 少しだけブレさせる


	for (int i = 0; i < 12; ++i) {

		Vector3 scale = {
		    scaleXDist(engine), // 太さもランダム
		    scaleYDist(engine), // 長さもランダム
		    1.0f};
		Vector3 rotation = {0.0f, 0.0f, rotOffsetDist(engine)};

		Effect* effect = new Effect();
		effect->Initialize(modelEffect_, scale, rotation);
		effects_.push_back(effect);
	}
}

void GameScene::Update() {
	for (Effect* e : effects_)
		e->Update();
}

void GameScene::Draw() {
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	///

	
	for (Effect* e : effects_) {
		e->Draw(camera_);
	}
	/// </summary>

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}
