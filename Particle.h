#pragma once
#include"ConvertString.h"
#include<stdlib.h>
#include"Emitter.h"



class Particle
{
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	Particle();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Particle();

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

	/// <summary>
	/// 水の跳ね返り
	/// </summary>
	void Splash();


private:
	Vector2 position_;		//位置
	Vector2 velocity_;		//速度
	Vector2 acceleration_;	//加速度
	Vector2 size_;			//大きさ
	Vector2 mass_;			//質量
	const float k_ = -0.6f;		//空気抵抗係数
	const float kGravity_ = 9.8f * 100;	//重力加速度
	bool isActive_;			//生成されているか　true:生成されている
	bool isSplash_;

	Vector2 ground_;	//地面の位置
	float restitution_; // 跳ね返り係数

	Vector2 wind_;		//風力

	Vector2 airResistance_;	//空気抵抗
	Vector2 airResistanceAcceleration_;	//空気抵抗による加速度

	Emitter* emitter_;	//エミッター
	Emitter* subEmitter_;

	static const int numParticles = 10; // 跳ね返るパーティクルの数
	Vector2 splashPosition_[numParticles];
	Vector2 splashVelocity_[numParticles];
	Vector2 splashAcceleration_[numParticles];
	Vector2 splashSize_[numParticles];
	// パーティクルの角度と距離を生成
	float angle ;
	float distance ;

	Vector2 lineStart_;
	Vector2 lineEnd_;

};

