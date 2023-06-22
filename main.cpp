#include <Novice.h>
#include"Particle.h"
#include "ImGuiManager.h"


const char kWindowTitle[] = "LE2B_28_ヨシダアイリ_タイトル";


// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {



	// ライブラリの初期化
	const int kWindowWidth = 1280;
	const int kWindowHeight = 720;
	Novice::Initialize(kWindowTitle, kWindowWidth, kWindowHeight);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	const int kNumParticles = 100; // パーティクルの数
	Particle* particle[kNumParticles];

	for (int i = 0; i < kNumParticles; i++)
	{
		particle[i] = new Particle;
	}
	
	

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///


		//パーティクルの更新
		for (int i = 0; i < kNumParticles; i++)
		{
			
			particle[i]->Update();
	
		}




		///
		/// ↑更新処理ここまで
		///

		

		///
		/// ↓描画処理ここから
		///

		////背景
		//Novice::DrawBox(0, 0, 1280, 720, 0.0f, BLACK, kFillModeSolid);

		for (int i = 0; i < kNumParticles; i++)
		{
			particle[i]->Draw();
		}


		Novice::ScreenPrintf(0, 0, "%d", particle[1]);



		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// パーティクルのメモリ解放
	for (int i = 0; i < kNumParticles; i++)
	{
		delete particle[i];
		particle[i] = nullptr; // ヌルポインタに設定しておく
	}



	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
