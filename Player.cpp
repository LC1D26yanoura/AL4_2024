#include "Player.h"

#include "cassert"

void Player::Initialize(Model* model,  uint32_t textureHandle,ViewProjection*viewProjection) { 
	assert(model);

	worldTransform_.Initialize();
	
	textureHandle_ = textureHandle;
	model_ = model;
	viewProjection_ = viewProjection;
	//シングルトンインスタンスを取得する
	input_ = Input::GetInstance();
}

void Player::Update() { 
	worldTransform_.TransferMatrix();
	//キャラクターの移動ベクトル
	Vector3 move = {0, 0, 0};
	//キャラクター移動速さ
	const float kCharacterSpeed = 0.2f;
	//押した方向でベクトルを変更（左右）
	if (input_->PushKey(DIK_A)) {
		move.x -= kCharacterSpeed;
	}
	if (input_->PushKey(DIK_D)) {
		move.x += kCharacterSpeed;
	}
	//押した方向でベクトルを変更（上下）
	if (input_->PushKey(DIK_W)) {
		move.y += kCharacterSpeed;
	}
	if (input_->PushKey(DIK_S)) {
		move.y -= kCharacterSpeed;
	}
	//座標移動（ベクトルの加算）
	worldTransform_.translation_ += move;
	//移動限界座標
	const float kMoveLimitX = 34;
	const float kMoveLimitY = 19;
	//範囲を超えない処理
	worldTransform_.translation_.x = max(worldTransform_.translation_.x, -kMoveLimitX);
	worldTransform_.translation_.x = min(worldTransform_.translation_.x, +kMoveLimitX);
	worldTransform_.translation_.y = max(worldTransform_.translation_.y, -kMoveLimitY);
	worldTransform_.translation_.y = min(worldTransform_.translation_.y, +kMoveLimitY);
	// 行列更新
	worldTransform_.matWorld_ = MakeAffineMatrix(worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);
	// 行列を定数バッファに転送
	worldTransform_.TransferMatrix();
	//キャラクターの座標を画面表示する処理
	//ImGui::Begin("");
	//
	//ImGui::End();

	
}

void Player::Draw() { 
	model_->Draw(worldTransform_, *viewProjection_, textureHandle_); 
}

void Player::Rotate() {
	const float kRotSpeed = 0.02f;

	if (input_->PushKey(DIK_LEFT)) {
		worldTransform_.rotation_.y -= kRotSpeed;
	}
	if (input_->PushKey(DIK_RIGHT)) {
		worldTransform_.rotation_.y += kRotSpeed;
	}
}
