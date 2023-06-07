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

	/// <summary>
	///	位置の変更
	/// </summary>
	/// <param name="pos">位置</param>
	void SetPosition(Vector2 pos);

	/// <summary>
	/// サイズの変更
	/// </summary>
	/// <param name="size"></param>
	void SetSize(Vector2 size);

private:
	Vector2 position_;	//位置
	Vector2 size_;		//大きさ
};

