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
	Vector2 size_;			//大きさ
	float mass_;			//質量
	const float k_ = -0.06f;		//空気抵抗係数
	const float kGravity_ = 9.8f*10;	//重力加速度
	bool isActive_;			//生成されているか　true:生成されている
	
	Vector2 ground_;	//地面の位置
	float restitution_; // 跳ね返り係数


	Vector2 airResistance_;	//空気抵抗
	Vector2 airResistanceAcceleration_;	//空気抵抗による加速度

	Emitter* emitter_;	//エミッター
	Emitter* subEmitter_;	//跳ね返りのエミッター


};

