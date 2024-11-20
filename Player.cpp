#include "Player.h"
#include "cassert"

void Player::Initialize(Model* model,  uint32_t textureHandle,ViewProjection*viewProjection) { 
	assert(model);

	worldTransform_.Initialize();
	
	textureHandle_ = textureHandle;
	model_ = model;
	viewProjection_ = viewProjection;


}

void Player::Update() { 
	worldTransform_.TransferMatrix();
}

void Player::Draw() { 

	model_->Draw(worldTransform_, *viewProjection_, textureHandle_);
}
