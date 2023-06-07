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
	const float k_ = 0.6f;		//空気抵抗係数
	
	const float kGravity_ = 9.8f;	//重力加速度
	bool isActive_;			//生成されているか　true:生成されている
	
	Vector2 airResistance_;	//空気抵抗
	Vector2 airResistanceAcceleration_;	//空気抵抗による加速度

	//Vector2 cameraPos = { 480.0f,200.0f };
	//Vector2 orthoLeftTop = { -640.f,360.f };
	//Vector2	orthoRightBottom = { 640.0f,-360.0f };
	//Vector2	viewportLeftTop = { 0.0f,0.0f };
	//Vector2	viewportSize = { 480.0f,960.0f };

	//Matrix3x3 cameraMatrix;
	//Matrix3x3 viewMatrix;
	//Matrix3x3 orthoMatrix;
	//Matrix3x3 viewportMatrix;
	//Matrix3x3 vpMatrix;
	//Matrix3x3 worldMatrix;
	//Matrix3x3 wvpMatrix;

	Emitter* emitter_;	//エミッター


};

