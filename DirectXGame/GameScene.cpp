#include "GameScene.h"

using namespace KamataEngine;

GameScene::~GameScene() { // 3Dモデルデータの解放
	delete modelEffect_;
	delete effect_;
}

void GameScene::Initialize() {
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	// 3Dモデルデータの生成
	modelEffect_ = Model::CreateFromOBJ("effect", true);

	// カメラの初期化
	camera_.Initialize();

	Vector3 position = {0.0f, 0.0f, 0.0f};

	// パーティクルの生成
	effect_ = new Effect();
	// パーティクルの初期化
	effect_->Initialize(modelEffect_, position);
}

void GameScene::Update() { effect_->Update(); }

void GameScene::Draw() {
	// DirectXCommon インスタンスの取得
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

	// パーティクル描画
	effect_->Draw(camera_);

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