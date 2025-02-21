#include "GameScene.h"


GameScene::GameScene() {}

// デストラクタ
GameScene::~GameScene() {
	
	delete player_;
	delete enemy_;
	delete modelSkydome_;
}

void GameScene::Initialize() {
	// ゲームプレイフェーズから開始
	phase_ = Phase::kPlay;
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	textureHandle_ = TextureManager::Load("mario.jpg");
	sprite_ = Sprite::Create(textureHandle_, {100, 50});

	// スカイドームの生成
	skydome_ = new Skydome();

	model_ = Model::Create();
	// ViewProjectionの初期化
	viewProjection_.Initialize();

		// 3Dモデルの生成(skydome)
	modelSkydome_ = Model::CreateFromOBJ("skydome", true);

	// スカイドームの初期化
	skydome_->Initialize(modelSkydome_, &viewProjection_);


	player_ = new Player();
	player_->Initialize(model_, textureHandle_, &viewProjection_);

	enemy_ = new Enemy();
	Vector3 Position = {0, 0, 50};
	enemy_->Initialize(model_, textureHandle_, Position);
	//敵キャラに自キャラのアドレスを渡す
	enemy_->SetPlayer(player_);

}

void GameScene::Update() { 
		player_->Update();
		if (enemy_) {
			enemy_->Update();
		}
	    // スカイドームの更新
	    skydome_->Update();

		CheckAllCollisions();
	    finished_ = player_->Isdead();
}
    

	void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	// スカイドームの描画
	skydome_->Draw();

	player_->Draw();
	if (enemy_) {
		enemy_->Draw(viewProjection_);
	}


	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
    }

    void GameScene::CheckAllCollisions() {
	    // 判定対象AとBの座標
	    Vector3 posA, posB;
	    // 自弾リストの取得
	    const std::list<PlayerBullet*>& PlayerBullets = player_->GetBullets();
	    // 敵弾リストの取得
	    const std::list<EnemyBullet*>& EnemyBullets = enemy_->GetBullets();

#pragma region 自キャラと敵弾の当たり判定
	    {
		    // 自キャラの座標
		    posA = player_->GetWorldPosition();
		    // 自キャラと敵弾全ての当たり判定
		    for (EnemyBullet* bullet : EnemyBullets) {
			    // 敵弾の座標
			    posB = bullet->GetWorldPosition();
			    // 座標の差分ベクトル
			    Vector3 subtract = posB - posA;
			    // 座標AとBの距離を求める
			    float distance = Length(subtract);
			    // 球と球の交差判定
			    if (distance < 1.5f + 1.5f) {
				    // 自キャラの衝突時コールバックを呼び出す
				    player_->OnCollision();
				    // 敵弾の衝突時コールバックを呼び出す
				    bullet->OnCollision();
			    }
		    }
	    }
#pragma endregion

#pragma region 自弾と敵キャラの当たり判定
	    {
		    // 敵キャラの座標
		    posA = enemy_->GetWorldPosition();
		    // 敵キャラと自弾全ての当たり判定
		    for (PlayerBullet* bullet : PlayerBullets) {
			    // 敵弾の座標
			    posB = bullet->GetWorldPosition();
			    // 座標の差分ベクトル
			    Vector3 subtract = posB - posA;
			    // 座標AとBの距離を求める
			    float distance = Length(subtract);
			    // 球と球の交差判定
			    if (distance < 1.5f + 1.5f) {
				    // 自弾の衝突時コールバックを呼び出す
				    enemy_->OnCollision();
				    // 敵弾の衝突時コールバックを呼び出す
				    bullet->OnCollision();
			    }
		    }
	    }
#pragma endregion
#pragma region 自弾と敵弾の当たり判定
	    {
		    // 自弾全てについて
		    for (PlayerBullet* playerBullet : PlayerBullets) {
			    // 自弾の座標
			    posA = playerBullet->GetWorldPosition();
			    // 敵弾全てについて
			    for (EnemyBullet* enemyBullet : EnemyBullets) {
				    // 敵弾の座標
				    posB = enemyBullet->GetWorldPosition();
				    // 座標の差分ベクトル
				    Vector3 subtract = posB - posA;
				    // 座標AとBの距離を求める
				    float distance = Length(subtract);
				    // 球と球の交差判定
				    if (distance < 1.5f + 1.5f) {
					    // 自弾の衝突時コールバックを呼び出す
 					    playerBullet->OnCollision();
					    // 敵弾の衝突時コールバックを呼び出す
					    enemyBullet->OnCollision();
				    }
			    }
		    }
	    }
#pragma endregion
    }
