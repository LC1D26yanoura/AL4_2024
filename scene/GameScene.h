#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "Player.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "TextureManager.h"
#include <cassert>
#include "Enemy.h"
#include "Vector3.h"
#include "MathUtilityForText.h"

class GameScene {
public:
	Sprite* sprite_ = nullptr;
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	//衝突判定と応答
	void CheckAllCollisions();
	
private:
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;
	uint32_t textureHandle_ = 0;
	// 自キャラ
	Player* player_ = nullptr;
	// プレイヤーのモデル
	Model* model_ = nullptr;
	//敵
	Enemy* enemy_ = nullptr;

	ViewProjection viewProjection_;
	
};