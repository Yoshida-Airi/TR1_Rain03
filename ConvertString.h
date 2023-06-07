#pragma once
#define _USE_MATH_DEFINES
#include<math.h>
#include<assert.h>
#include"Vector2.h"

struct Matrix3x3
{
	float m[3][3];
};

//3x3行列の積
Matrix3x3 Multiply(Matrix3x3 matrix1, Matrix3x3 matrix2);

//3x3逆行列を求める
Matrix3x3 Inverse(Matrix3x3 matrix);

Matrix3x3 MakeAffinMatrix(Vector2 scale, float rotate, Vector2 translate);

//正射影行列
Matrix3x3 MakeOrthographicMatrix(float left, float top, float right, float bottom);

//ビューポート
Matrix3x3 MakeViewMatrix(float left, float top, float width, float height);

//2次元ベクトルを同次座標として変換する
Vector2 Transform(Vector2 vector, Matrix3x3 matrix);