#include "Player.h"

#include "cassert"

Player::~Player() { 
	for (PlayerBullet* bullet : bullets_) {
	delete bullet;
	}

}

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
	worldTransform_.UpdateMatrix();
	// 行列を定数バッファに転送
	worldTransform_.TransferMatrix();
	
	//旋回呼び出し
	Rotate();
	
	//攻撃呼び出し
	Attack();
	//弾更新
	for (PlayerBullet * bullet : bullets_) {
		bullet->Update();
	}
}

void Player::Draw() { 
	model_->Draw(worldTransform_, *viewProjection_, textureHandle_); 
	//弾描画
	for (PlayerBullet* bullet : bullets_) {
		bullet->Draw(*viewProjection_);
	}
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

void Player::Attack() {
	if (input_->TriggerKey(DIK_SPACE)) {
		//弾があれば開放する
		
		//弾を生成し初期化
		PlayerBullet* newBullet = new PlayerBullet();
		newBullet->Initialize(model_, worldTransform_.translation_);
		//弾を登録する
		bullets_.push_back(newBullet);
	}
}

