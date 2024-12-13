#include "GameScene.h"


GameScene::GameScene() {}

// デストラクタ
GameScene::~GameScene() {
	
	delete player_;
	delete enemy_;
	
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	textureHandle_ = TextureManager::Load("mario.jpg");
	sprite_ = Sprite::Create(textureHandle_, {100, 50});

	model_ = Model::Create();
	// ViewProjectionの初期化
	viewProjection_.Initialize();

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
	//判定対象AとBの座標
	    Vector3 posA, posB;
		//自弾リストの取得
	    const std::list<PlayerBullet*>& PlayerBullets = player_->GetBullets();
	    // 敵弾リストの取得
	    const std::list<EnemyBullet*>& EnemyBullets = enemy_->GetBullets();




	}

