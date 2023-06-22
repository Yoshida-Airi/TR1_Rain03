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



private:
	Vector2 position_;		//位置
	Vector2 velocity_;		//速度
	Vector2 acceleration_;	//加速度
	float size_;			//大きさ(直径)
	float mass_;			//質量
	
	Vector2 endPos_;
	Vector2 endvel_;
	Vector2 endAcc_;


	bool isActive_;			//生成されているか　true:生成されている
	bool isSplash_;

	float rainDensity_;	//雨粒の密度
	float airDensity_;	//空気の密度
	float k_;			//空気抵抗係数
	float kGravity_;	//重力加速度

	Vector2 terminalVelocity_;	//終端速度

	Vector2 ground_;	//地面の位置
	float restitution_; // 跳ね返り係数

	Vector2 wind_;		//風力

	Vector2 airResistance_;	//空気抵抗
	Vector2 airResistanceAcceleration_;	//空気抵抗による加速度
	Vector2 gravityAcceleration_;		//重力による加速度
	Vector2 windAcceleration_;

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

	
	float random;

};

