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
	velocity_ = {0, 0, 0.1f};

}

void Enemy::Update() {
	worldTransform_.UpdateMatrix();

	switch (phase_) { case Phase::Approach:
	default:
		//移動
		worldTransform_.translation_ -= velocity_;
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

}

void Enemy::Draw(const ViewProjection& viewProjection) { 
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}
