#pragma once
#include"ConvertString.h"
#include<stdlib.h>
#include"Emitter.h"


class SplashParticle
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	SplashParticle(Vector2 pos,Vector2 size);

	/// <summary>
	/// デストラクタ
	/// </summary>
	~SplashParticle();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw();



private:
	Vector2 position_;		//位置
	Vector2 velocity_;		//速度
	Vector2 acceleration_;	//加速度
	Vector2 size_;			//大きさ
	float mass_;			//質量
	const float k_ = -0.6f;		//空気抵抗係数
	const float kGravity_ = 9.8f;	//重力加速度
	bool isActive_;			//生成されているか　true:生成されている

	Vector2 ground_;	//地面の位置
	float restitution_; // 跳ね返り係数
	Vector2 angle_;		//角度
	const float kDegToRad = static_cast<float>(M_PI) / 180.0f;

	Vector2 height_;	//円錐の高さ


	Vector2 airResistance_;	//空気抵抗
	Vector2 airResistanceAcceleration_;	//空気抵抗による加速度

	Emitter* emitter_;	//エミッター


};

