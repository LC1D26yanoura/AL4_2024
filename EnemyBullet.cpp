#include "EnemyBullet.h"
#include "cassert"

void EnemyBullet::Initialize(Model* model, const Vector3& Position, const Vector3& velocity) {
	assert(model);

	model_ = model;

	// テクスチャ読み込み
	textureHandle_ = TextureManager::Load("white1x1.png");
	worldTransform_.Initialize();

	// 引数で受け取った初期座標をセット
	worldTransform_.translation_ = Position;
	// 引数で受け取った速度をメンバ変数に代入
	velocity_ = velocity;

}

void EnemyBullet::Update() {
	worldTransform_.UpdateMatrix();
	// 座標を移動させる
	worldTransform_.translation_ -= velocity_;
	// 時間経過でデス
	if (--deathTimer_ <= 0) {
		isDead_ = true;
	}
}

void EnemyBullet::Draw(const ViewProjection& viewProjection) { 
	model_->Draw(worldTransform_, viewProjection, textureHandle_); }

void EnemyBullet::OnCollision() { isDead_ = true; }
