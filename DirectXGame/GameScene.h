#pragma once
#include "Effect.h"
#include "KamataEngine.h"

using namespace KamataEngine;

class GameScene {

public:
	// デストラクタ
	~GameScene();

	// 初期化
	void Initialize();
	// 更新
	void Update();
	// 描画
	void Draw();

private:
	KamataEngine::DirectXCommon* dxCommon_ = nullptr;
	KamataEngine::Input* input_ = nullptr;
	KamataEngine::Audio* audio_ = nullptr;

	// エフェクトの3Dモデルデータ
	Model* modelEffect_ = nullptr;
	// エフェクト
	Effect* effect_ = nullptr;
	// カメラ
	Camera camera_;
};