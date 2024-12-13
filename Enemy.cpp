#include "Enemy.h"
#include "EnemyBullet.h"
#include "cassert"

Enemy::~Enemy() {
	for (EnemyBullet* bullet : bullets_) {
		delete bullet;
	}
	bullets_.clear();
}

void Enemy::fire() {
	Attack(); }

void Enemy::Approachphase() {
//発射タイマーを初期化
	fireTimer_ = kFireInterval;
}

void Enemy::Initialize(Model* model, uint32_t textureHandle, const Vector3& Position) {
	assert(model);

	worldTransform_.Initialize();

	textureHandle_ = textureHandle;
	model_ = model;
	// テクスチャ読み込み
	textureHandle_ = TextureManager::Load("cube/cube.jpg");
	// 引数で受け取った初期座標をセット
	worldTransform_.translation_ = Position;

	// 引数で受け取った速度をメンバ変数に代入
	velocity_ = {0, 0, 0.1f};

	//fire();

	//接近フェーズ初期化
	Approachphase();
}

void Enemy::Update() {
	worldTransform_.UpdateMatrix();

	switch (phase_) { case Phase::Approach:
	default:
		//移動
		worldTransform_.translation_ -= velocity_;
		//発射タイマーをデクリメント
		fireTimer_--;
		//指定時間に達した
		if (fireTimer_ == 0) {
		//弾を発射
			fire();
			//発射タイマーを初期化
			fireTimer_ = kFireInterval;
		}
		//既定の位置に到達したら離脱
		if (worldTransform_.translation_.z < 0.0f) {
			phase_ = Phase::Leave;
		}
		break;
	case Phase::Leave:
		//移動
		worldTransform_.translation_ += velocity_;
		break; 
	}
	// 弾更新
	for (EnemyBullet* bullet : bullets_) {
		bullet->Update();
	}
	// デスフラグの立った球を削除
	bullets_.remove_if([](EnemyBullet* bullets_) {
		if (bullets_->IsDead()) {
			delete bullets_;
			return true;
		}
		return false;
	});
}

void Enemy::Draw(const ViewProjection& viewProjection) { 
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
	for (EnemyBullet* bullet : bullets_) {
		bullet->Draw(viewProjection);
	}
}

void Enemy::Attack() {
	
		// 弾の速度
		const float kBulletSpeed = 1.0f;
		Vector3 velocity(0, 0, kBulletSpeed);
		// 速度ベクトルを時期に向きに合わせて回転させる
		velocity = TransformNormal(velocity, worldTransform_.matWorld_);

		// 弾を生成し初期化
		EnemyBullet* newBullet = new EnemyBullet();
		newBullet->Initialize(model_, worldTransform_.translation_, velocity);
		// 弾を登録する
		bullets_.push_back(newBullet);
	
}

