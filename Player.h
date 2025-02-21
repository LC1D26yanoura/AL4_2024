#pragma once
#include "Model.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "input.h"
#include "MathUtilityForText.h"
#include "imgui.h"
#include "PlayerBullet.h"
#include <list>

class Player {
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(Model* model, uint32_t textureHandle, ViewProjection* viewProjection);

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

/// <summary>
/// 旋回
/// </summary>
	void Rotate();
	
/// <summary>
/// 攻撃
/// </summary>
	void Attack();

/// <summary>
/// デストラクタ
/// </summary>
	~Player();

	//ワールド座標を取得
	Vector3 GetWorldPosition();

	// 衝突を検出したら呼び出されるコールバック関数
	void OnCollision();

	//弾リストを取得
	const std::list<PlayerBullet*>& GetBullets() const { return bullets_; }

	bool Isdead() const { return isdead; }

private:
	//ワールド変換データ
	WorldTransform worldTransform_;
	//モデル
	Model* model_ = nullptr;
	//テクスチャハンドル
	uint32_t textureHandle_ = 0u;
	//
	ViewProjection* viewProjection_ = nullptr;
	//キーボード入力
	Input* input_ = nullptr;
	//弾
	std::list<PlayerBullet*> bullets_;
	//デスフラグ
	bool isdead = false;
};
