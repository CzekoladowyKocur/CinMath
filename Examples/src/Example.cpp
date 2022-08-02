#include "CinMath/CinMath.h"

template<typename T> 
void TestFunc()
{
	T lhs;
	T rhs;

	float scalar{ 1.0f };

	rhs += lhs;
	rhs -= lhs;
	rhs *= lhs;
	rhs /= lhs;

	auto res1 = lhs * rhs;
	auto res2 = lhs / rhs;
	auto res3 = lhs + rhs;
	auto res4 = lhs - rhs;

	rhs += scalar;
	rhs -= scalar;
	rhs *= scalar;
	rhs /= scalar;

	auto res1_scalar = lhs * scalar;
	auto res2_scalar = lhs / scalar;
	auto res3_scalar = lhs + scalar;
	auto res4_scalar = lhs - scalar;
}

template<typename T> 
void TestFuncMat()
{
	T lhs;
	T rhs;

	float scalar{ 1.0f };

	rhs += lhs;
	rhs -= lhs;
	rhs *= lhs;

	auto res1 = lhs * rhs;
	auto res3 = lhs + rhs;
	auto res4 = lhs - rhs;

	rhs += scalar;
	rhs -= scalar;
	rhs *= scalar;
	rhs /= scalar;

	auto res1_scalar = lhs * scalar;
	auto res2_scalar = lhs / scalar;
	auto res3_scalar = lhs + scalar;
	auto res4_scalar = lhs - scalar;
}

int main()
{
	using namespace CinMath;
	TestFunc<Vector2>();
	TestFunc<Vector3>();
	TestFunc<Vector4>();

	TestFuncMat<Matrix2>();
	TestFuncMat<Matrix3>();
	TestFuncMat<Matrix4>();

	Matrix4 ma1, mat2, mat3;
	auto result =  ma1 * mat2 * mat3;


	operator+(operator+(ma1, mat2), ma1);

	return 0;
}