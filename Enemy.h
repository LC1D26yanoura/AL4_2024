#pragma once
#include "Model.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "MathUtilityForText.h"
#include "TextureManager.h"
#include "Vector3.h"
#include "MathUtilityForText.h"
#include "EnemyBullet.h"
#include <list>
//自機クラスの前方宣言
class Player;

enum class Phase {
	Approach,
	Leave,
};

class Enemy {
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(Model* model, uint32_t textureHandle, const Vector3& Position);

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw(const ViewProjection& viewProjection);

	/// <summary>
	/// 攻撃
	/// </summary>
	void Attack();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Enemy();

/// <summary>
/// 弾発射
/// </summary>
	void fire();

//発射間隔
	static const int kFireInterval = 60;

	//接近フェーズ初期化
	void Approachphase();

	void SetPlayer(Player* player) { player_ = player; }
	
	// ワールド座標を取得
		Vector3 GetWorldPosition();
	

	private:
	// ワールド変換データ
	WorldTransform worldTransform_;
	// モデル
	Model* model_ = nullptr;
	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;
	// 速度
	Vector3 velocity_;
	//フェーズ
	Phase phase_ = Phase::Approach;
	// 弾
	std::list<EnemyBullet*> bullets_;
	//発射タイマー
	int32_t fireTimer_ = 0;
	//自キャラ
	Player* player_ = nullptr;
};

