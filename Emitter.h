#pragma once
#include"Vector2.h"
class Emitter
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Emitter();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Emitter();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// 位置受け渡し
	/// </summary>
	/// <returns>位置</returns>
	Vector2 GetPosition()const { return this->position_; };

	/// <summary>
	/// サイズ受け渡し
	/// </summary>
	/// <returns>大きさ</returns>
	Vector2 GetSize()const { return this->size_; };

private:
	Vector2 position_;	//位置
	Vector2 size_;		//大きさ
};

