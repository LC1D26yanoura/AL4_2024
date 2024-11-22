#include "Enemy.h"
#include "cassert"

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
	velocity_ = {0, 0, 0.3f};

}

void Enemy::Update() {
	worldTransform_.UpdateMatrix();
	// 座標を移動させる
	worldTransform_.translation_ -= velocity_;
}

void Enemy::Draw(const ViewProjection& viewProjection) { 
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}
