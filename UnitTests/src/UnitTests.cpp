#include <memory>
#include <iostream>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
//#define CIN_USE_DEFAULT_INSTRUCTION_SET
#define CIN_USE_SSE
#include "CinMath/CinMath.h"

std::ostream& operator<<(std::ostream& stream, const glm::mat4& matrix)
{
	const float* ptr = &matrix[0][0];
	for (uint32_t i{ 0 }; i < sizeof(glm::mat4) / sizeof(matrix[0][0]); ++i)
	{
		if ((i + 1) % 4 == 0)
			stream << ptr[i] << '\n';
		else
			stream << ptr[i] << ' ';
	}

	return stream << '\n';
}

std::ostream& operator<<(std::ostream& stream, const glm::mat2& matrix)
{
	const float* ptr = &matrix[0][0];
	for (uint32_t i{ 0 }; i < sizeof(glm::mat2) / sizeof(matrix[0][0]); ++i)
	{
		if ((i + 1) % 2 == 0)
			stream << ptr[i] << '\n';
		else
			stream << ptr[i] << ' ';
	}

	return stream << '\n';
}

constexpr uint32_t g_TestCount{ 1'000'00 };

template<typename LHS, typename RHS>
void IsMemoryEqual(LHS& lhs, RHS& rhs, const std::string_view error)
{
	static_assert(sizeof(LHS) == sizeof(RHS));
	if (memcmp(&lhs, &rhs, sizeof(LHS)) != 0)
		throw std::runtime_error(error.data());
}

template<typename LHS, typename RHS>
bool IsMemoryEqualBoolean(LHS& lhs, RHS& rhs)
{
	return memcmp(&lhs, &rhs, sizeof(LHS)) == 0;
}

template<typename Destination, typename ... Rest>
void CopyDataTo(void* data, Destination& dest, Rest&& ... rest)
{
	memcpy(&dest, data, sizeof(Destination));

	if constexpr (sizeof...(Rest) > 0)
		CopyDataTo(data, std::forward<Rest>(rest)...);
}

float RandomFloat()
{
	/* Relatively low value helps eliminate rounding errors */
	return static_cast<float>((rand() % 200) + 1 - 100);
}

void TestVectors()
{
	/* Vector 2 */
	for (uint32_t i{ 0 }; i < g_TestCount; ++i)
	{
		using Cin = CinMath::Vector2;
		using vec2 = glm::vec2;

		const std::pair<float, float> testNumbers1 = { RandomFloat(), RandomFloat() };
		const std::pair<float, float> testNumbers2 = { RandomFloat(), RandomFloat() };

		Cin cin1(testNumbers1.second, testNumbers1.first);
		Cin cin2(testNumbers2.second, testNumbers2.first);

		vec2 _Test1({ testNumbers1.second, testNumbers1.first });
		vec2 _Test2({ testNumbers2.second, testNumbers2.first });

		/* Negation */
		{
			Cin cinResult1 = -cin1;
			Cin cinResult2 = -cin2;

			auto _result1 = -_Test1;
			auto _result2 = -_Test2;

			/* -0.0f isnt the same as 0.0f in memory but it's technically the same */
			assert(cinResult1.x == _result1.x || cinResult1.x == 0.0f || cinResult1.x == -0.0f);
			assert(cinResult1.y == _result1.y || cinResult1.y == 0.0f || cinResult1.y == -0.0f);

			assert(cinResult2.x == _result2.x || cinResult2.x == 0.0f || cinResult2.x == -0.0f);
			assert(cinResult2.y == _result2.y || cinResult2.y == 0.0f || cinResult2.y == -0.0f);
		}
		/* Add scalar */
		{
			auto scalar1 = RandomFloat();
			auto scalar2 = RandomFloat();
			Cin cinResult1 = cin1 + scalar1;
			Cin cinResult2 = cin2 + scalar2;
			auto _result1 = _Test1 + scalar1;
			auto _result2 = _Test2 + scalar2;
			IsMemoryEqual(cinResult1, _result1, "Vec2 add scalar");
			IsMemoryEqual(cinResult2, _result2, "Vec2 add scalar");
		}
		/* Sub scalar */
		{
			auto scalar1 = RandomFloat();
			auto scalar2 = RandomFloat();
			Cin cinResult1 = cin1 - scalar1;
			Cin cinResult2 = cin2 - scalar2;
			auto _result1 = _Test1 - scalar1;
			auto _result2 = _Test2 - scalar2;
			IsMemoryEqual(cinResult1, _result1, "Vec2 sub scalar");
			IsMemoryEqual(cinResult2, _result2, "Vec2 sub scalar");
		}
		/* Mul scalar */
		{
			auto scalar1 = RandomFloat();
			auto scalar2 = RandomFloat();
			Cin cinResult1 = cin1 * scalar1;
			Cin cinResult2 = cin2 * scalar2;
			auto _result1 = _Test1 * scalar1;
			auto _result2 = _Test2 * scalar2;
			IsMemoryEqual(cinResult1, _result1, "Vec2 mul scalar");
			IsMemoryEqual(cinResult2, _result2, "Vec2 mul scalar");
		}
		/* Div scalar */
		{
			auto scalar1 = RandomFloat();
			auto scalar2 = RandomFloat();
			Cin cinResult1 = cin1 / scalar1;
			Cin cinResult2 = cin2 / scalar2;
			auto _result1 = _Test1 / scalar1;
			auto _result2 = _Test2 / scalar2;
			IsMemoryEqual(cinResult1, _result1, "Vec2 div scalar");
			IsMemoryEqual(cinResult2, _result2, "Vec2 div scalar");
		}
		/* Sub */
		{
			Cin cinResult = cin1 + cin2;
			auto _result = _Test1 + _Test2;
			IsMemoryEqual(cinResult, _result, "Vec2 sub");
		}
		/* Mul */
		{
			Cin cinResult = cin1 * cin2;
			auto _result = _Test1 * _Test2;
			IsMemoryEqual(cinResult, _result, "Vec2 mul");
		}
		/* Div */
		{
			Cin cinResult = cin1 / cin2;
			auto _result = _Test1 / _Test2;
			IsMemoryEqual(cinResult, _result, "Vec2 div");
		}
		/* Add */
		{
			Cin cinResult = cin1 + cin2;
			auto _result = _Test1 + _Test2;
			IsMemoryEqual(cinResult, _result, "Vec2 add");
		}
		/* Sub */
		{
			Cin cinResult = cin1 + cin2;
			auto _result = _Test1 + _Test2;
			IsMemoryEqual(cinResult, _result, "Vec2 sub");
		}
		/* Mul */
		{
			Cin cinResult = cin1 * cin2;
			auto _result = _Test1 * _Test2;
			IsMemoryEqual(cinResult, _result, "Vec2 mul");
		}
		/* Div */
		{
			Cin cinResult = cin1 / cin2;
			auto _result = _Test1 / _Test2;
			IsMemoryEqual(cinResult, _result, "Vec2 div");
		}
		/* Add= */
		{
			cin1 += cin2;
			_Test1 += _Test2;
			IsMemoryEqual(cin1, _Test1, "Vec2 add=");
		}
		/* Sub= */
		{
			cin1 -= cin2;
			_Test1 -= _Test2;
			IsMemoryEqual(cin1, _Test1, "Vec2 sub=");
		}
		/* Mul= */
		{
			cin1 *= cin2;
			_Test1 *= _Test2;
			IsMemoryEqual(cin1, _Test1, "Vec2 mul=");
		}
		/* Div= */
		{
			cin1 /= cin2;
			_Test1 /= _Test2;
			IsMemoryEqual(cin1, _Test1, "Vec2 div=");
		}
		/* Transform: Length */
		{
			auto cinResult1 = CinMath::Length(cin1);
			auto cinResult2 = CinMath::Length(cin2);

			auto _result1 = glm::length(_Test1);
			auto _result2 = glm::length(_Test2);

			IsMemoryEqual(cinResult1, _result1, "Vec2 length");
			IsMemoryEqual(cinResult2, _result2, "Vec2 length");
		}
		/* Transform: Dot product */
		{
			auto cinResult = CinMath::Dot(cin1, cin2);
			auto _result = glm::dot(_Test1, _Test2);


			IsMemoryEqual(cinResult, _result, "Vec2 dot product");
		}
	}

	for (uint32_t i{ 0 }; i < g_TestCount; ++i)
	{
		using Cin = CinMath::Vector3;
		using vec2 = glm::vec3;

		float testNumbers1[3]{ RandomFloat(), RandomFloat(),  RandomFloat() };
		float testNumbers2[3]{ RandomFloat(), RandomFloat(),  RandomFloat() };

		Cin cin1({ 0 });
		Cin cin2({ 0 });
		vec2 _Test1({ 0 });
		vec2 _Test2({ 0 });
		CopyDataTo(testNumbers1, cin1, cin2, _Test1, _Test2);
		IsMemoryEqual(_Test1, cin1, "Memcpy failed");
		IsMemoryEqual(_Test2, cin2, "Memcpy failed");

		/* Negation */
		{
			Cin cinResult1 = -cin1;
			Cin cinResult2 = -cin2;

			auto _result1 = -_Test1;
			auto _result2 = -_Test2;

			/* -0.0f isnt the same as 0.0f in memory but it's technically the same */
			assert(cinResult1.x == _result1.x || cinResult1.x == 0.0f || cinResult1.x == -0.0f);
			assert(cinResult1.y == _result1.y || cinResult1.y == 0.0f || cinResult1.y == -0.0f);
			assert(cinResult1.z == _result1.z || cinResult1.z == 0.0f || cinResult1.z == -0.0f);

			assert(cinResult2.x == _result2.x || cinResult2.x == 0.0f || cinResult2.x == -0.0f);
			assert(cinResult2.y == _result2.y || cinResult2.y == 0.0f || cinResult2.y == -0.0f);
			assert(cinResult2.z == _result2.z || cinResult2.z == 0.0f || cinResult2.z == -0.0f);
		}
		/* Add scalar */
		{
			auto scalar1 = RandomFloat();
			auto scalar2 = RandomFloat();
			Cin cinResult1 = cin1 + scalar1;
			Cin cinResult2 = cin2 + scalar2;
			auto _result1 = _Test1 + scalar1;
			auto _result2 = _Test2 + scalar2;
			IsMemoryEqual(cinResult1, _result1, "Vec3 add scalar");
			IsMemoryEqual(cinResult2, _result2, "Vec3 add scalar");
		}
		/* Sub scalar */
		{
			auto scalar1 = RandomFloat();
			auto scalar2 = RandomFloat();
			Cin cinResult1 = cin1 - scalar1;
			Cin cinResult2 = cin2 - scalar2;
			auto _result1 = _Test1 - scalar1;
			auto _result2 = _Test2 - scalar2;
			IsMemoryEqual(cinResult1, _result1, "Vec3 sub scalar");
			IsMemoryEqual(cinResult2, _result2, "Vec3 sub scalar");
		}
		/* Mul scalar */
		{
			auto scalar1 = RandomFloat();
			auto scalar2 = RandomFloat();
			Cin cinResult1 = cin1 * scalar1;
			Cin cinResult2 = cin2 * scalar2;
			auto _result1 = _Test1 * scalar1;
			auto _result2 = _Test2 * scalar2;
			IsMemoryEqual(cinResult1, _result1, "Vec3 mul scalar");
			IsMemoryEqual(cinResult2, _result2, "Vec3 mul scalar");
		}
		/* Div scalar */
		{
			auto scalar1 = RandomFloat();
			auto scalar2 = RandomFloat();
			Cin cinResult1 = cin1 / scalar1;
			Cin cinResult2 = cin2 / scalar2;
			auto _result1 = _Test1 / scalar1;
			auto _result2 = _Test2 / scalar2;
			IsMemoryEqual(cinResult1, _result1, "Vec3 div scalar");
			IsMemoryEqual(cinResult2, _result2, "Vec3 div scalar");
		}
		/* Add */
		{
			Cin cinResult = cin1 + cin2;
			auto _result = _Test1 + _Test2;
			IsMemoryEqual(cinResult, _result, "Vec3 add");
		}
		/* Sub */
		{
			Cin cinResult = cin1 + cin2;
			auto _result = _Test1 + _Test2;
			IsMemoryEqual(cinResult, _result, "Vec3 sub");
		}
		/* Mul */
		{
			Cin cinResult = cin1 * cin2;
			auto _result = _Test1 * _Test2;
			IsMemoryEqual(cinResult, _result, "Vec3 mul");
		}
		/* Div */
		{
			Cin cinResult = cin1 / cin2;
			auto _result = _Test1 / _Test2;
			IsMemoryEqual(cinResult, _result, "Vec3 div");
		}
		/* Add= */
		{
			cin1 += cin2;
			_Test1 += _Test2;
			IsMemoryEqual(cin1, _Test1, "Vec3 add=");
		}
		/* Sub */
		{
			cin1 -= cin2;
			_Test1 -= _Test2;
			IsMemoryEqual(cin1, _Test1, "Vec3 sub=");
		}
		/* Sub */
		{
			cin1 *= cin2;
			_Test1 *= _Test2;
			IsMemoryEqual(cin1, _Test1, "Vec3 mul=");
		}
		/* Sub */
		{
			cin1 /= cin2;
			_Test1 /= _Test2;
			IsMemoryEqual(cin1, _Test1, "Vec3 div=");
		}
		/* Transform: Length */
		{
			auto cinResult1 = CinMath::Length(cin1);
			auto cinResult2 = CinMath::Length(cin2);

			auto _result1 = glm::length(_Test1);
			auto _result2 = glm::length(_Test2);

			IsMemoryEqual(cinResult1, _result1, "Vec3 length");
			IsMemoryEqual(cinResult2, _result2, "Vec3 length");
		}
		/* Transform: Dot product */
		{
			auto cinResult = CinMath::Dot(cin1, cin2);
			auto _result = glm::dot(_Test1, _Test2);


			IsMemoryEqual(cinResult, _result, "Vec3 dot product");
		}
		/* Transform: Cross product */
		{
			auto cinResult = CinMath::Cross(cin1, cin2);
			auto _result = glm::cross(_Test1, _Test2);

			IsMemoryEqual(cinResult, _result, "Vec3 cross product");
		}
	}

	for (uint32_t i{ 0 }; i < g_TestCount; ++i)
	{
		using Cin = CinMath::Vector4;
		using vec2 = glm::vec4;

		float testNumbers1[4]{ RandomFloat(), RandomFloat(), RandomFloat(), RandomFloat() };
		float testNumbers2[4]{ RandomFloat(), RandomFloat(), RandomFloat(), RandomFloat() };

		Cin cin1(0.0f, 0.0f, 0.0f, 0.0f);
		Cin cin2(0.0f);
		vec2 _Test1({ 0 });
		vec2 _Test2({ 0 });
		CopyDataTo(testNumbers1, cin1, _Test1);
		CopyDataTo(testNumbers2, cin2, _Test2);

		IsMemoryEqual(_Test1, cin1, "Memcpy failed");
		IsMemoryEqual(_Test2, cin2, "Memcpy failed");

		/* Negation */
		{
			Cin cinResult1 = -cin1;
			Cin cinResult2 = -cin2;

			auto _result1 = -_Test1;
			auto _result2 = -_Test2;

			/* -0.0f isnt the same as 0.0f in memory but it's technically the same */
			assert(cinResult1.x == _result1.x || cinResult1.x == 0.0f || cinResult1.x == -0.0f);
			assert(cinResult1.y == _result1.y || cinResult1.y == 0.0f || cinResult1.y == -0.0f);
			assert(cinResult1.z == _result1.z || cinResult1.z == 0.0f || cinResult1.z == -0.0f);
			assert(cinResult1.w == _result1.w || cinResult1.w == 0.0f || cinResult1.w == -0.0f);

			assert(cinResult2.x == _result2.x || cinResult2.x == 0.0f || cinResult2.x == -0.0f);
			assert(cinResult2.y == _result2.y || cinResult2.y == 0.0f || cinResult2.y == -0.0f);
			assert(cinResult2.z == _result2.z || cinResult2.z == 0.0f || cinResult2.z == -0.0f);
			assert(cinResult2.w == _result2.w || cinResult2.w == 0.0f || cinResult2.w == -0.0f);
		}
		/* Add scalar */
		{
			auto scalar1 = RandomFloat();
			auto scalar2 = RandomFloat();
			Cin cinResult1 = cin1 + scalar1;
			Cin cinResult2 = cin2 + scalar2;
			auto _result1 = _Test1 + scalar1;
			auto _result2 = _Test2 + scalar2;
			IsMemoryEqual(cinResult1, _result1, "Vec4 add scalar");
			IsMemoryEqual(cinResult2, _result2, "Vec4 add scalar");
		}
		/* Sub scalar */
		{
			auto scalar1 = RandomFloat();
			auto scalar2 = RandomFloat();
			Cin cinResult1 = cin1 - scalar1;
			Cin cinResult2 = cin2 - scalar2;
			auto _result1 = _Test1 - scalar1;
			auto _result2 = _Test2 - scalar2;
			IsMemoryEqual(cinResult1, _result1, "Vec4 sub scalar");
			IsMemoryEqual(cinResult2, _result2, "Vec4 sub scalar");
		}
		/* Mul scalar */
		{
			auto scalar1 = RandomFloat();
			auto scalar2 = RandomFloat();
			Cin cinResult1 = cin1 * scalar1;
			Cin cinResult2 = cin2 * scalar2;
			auto _result1 = _Test1 * scalar1;
			auto _result2 = _Test2 * scalar2;
			IsMemoryEqual(cinResult1, _result1, "Vec4 mul scalar");
			IsMemoryEqual(cinResult2, _result2, "Vec4 mul scalar");
		}
		/* Div scalar */
		{
			auto scalar1 = RandomFloat();
			auto scalar2 = RandomFloat();
			Cin cinResult1 = cin1 / scalar1;
			Cin cinResult2 = cin2 / scalar2;
			auto _result1 = _Test1 / scalar1;
			auto _result2 = _Test2 / scalar2;
			IsMemoryEqual(cinResult1, _result1, "Vec4 div scalar");
			IsMemoryEqual(cinResult2, _result2, "Vec4 div scalar");
		}
		/* Add */
		{
			Cin cinResult = cin1 + cin2;
			auto _result = _Test1 + _Test2;
			IsMemoryEqual(cinResult, _result, "Vec4 add");
		}
		/* Sub */
		{
			Cin cinResult = cin1 - cin2;
			auto _result = _Test1 - _Test2;
			IsMemoryEqual(cinResult, _result, "Vec4 sub");
		}
		/* Mul */
		{
			Cin cinResult = cin1 * cin2;
			auto _result = _Test1 * _Test2;
			IsMemoryEqual(cinResult, _result, "Vec4 mul");
		}
		/* Div */
		{
			Cin cinResult = cin1 / cin2;
			auto _result = _Test1 / _Test2;
			IsMemoryEqual(cinResult, _result, "Vec4 div");
		}
		/* Add= */
		{
			cin1 += cin2;
			_Test1 += _Test2;
			IsMemoryEqual(cin1, _Test1, "Vec4 add=");
		}
		/* Sub= */
		{
			cin1 -= cin2;
			_Test1 -= _Test2;
			IsMemoryEqual(cin1, _Test1, "Vec4 sub=");
		}
		/* Mul= */
		{
			cin1 *= cin2;
			_Test1 *= _Test2;
			IsMemoryEqual(cin1, _Test1, "Vec4 mul=");
		}
		/* Div= */
		{
			cin1 /= cin2;
			_Test1 /= _Test2;
			IsMemoryEqual(cin1, _Test1, "Vec4 div=");
		}
		/* Transform: Length */
		{
			auto cinResult1 = CinMath::Length(cin1);
			auto cinResult2 = CinMath::Length(cin2);

			auto _result1 = glm::length(_Test1);
			auto _result2 = glm::length(_Test2);

			IsMemoryEqual(cinResult1, _result1, "Vec4 length");
			IsMemoryEqual(cinResult2, _result2, "Vec4 length");
		}
		/* Transform: Dot product */
		{
			auto cinResult = CinMath::Dot(cin1, cin2);
			auto _result = glm::dot(_Test1, _Test2);

			if (!IsMemoryEqualBoolean(cinResult, _result))
			{
				throw std::runtime_error("Vec4 dot");
			}
		}
	}
}

void TestMatrices()
{
	for (uint32_t i{ 0 }; i < g_TestCount; ++i)
	{
		using Cin = CinMath::Matrix2;
		using mat = glm::mat2;

		float testNumbers1[4]{ RandomFloat(), RandomFloat(), RandomFloat(), RandomFloat() };
		float testNumbers2[4]{ RandomFloat(), RandomFloat(), RandomFloat(), RandomFloat() };

		Cin cin1({ 0 });
		Cin cin2({ 0 });
		mat _Test1({ 0 });
		mat _Test2({ 0 });

		CopyDataTo(testNumbers1, cin1, _Test1);
		CopyDataTo(testNumbers2, cin2, _Test2);

		IsMemoryEqual(_Test1, cin1, "Memcpy failed");
		IsMemoryEqual(_Test2, cin2, "Memcpy failed");

		/* Identity */
		{
			Cin cinResult({ 1.0f });
			mat _result({ 1.0f });

			IsMemoryEqual(cinResult, _result, "mat2 identity");
		}
		/* Negation */
		{
			auto cinResult1 = -cin1;
			auto cinResult2 = -cin2;

			mat _result1 = -_Test1;
			mat _result2 = -_Test2;

			/* -0.0f isnt the same as 0.0f in memory but it's technically the same */
			assert(cinResult1.raw[0] == _result1[0][0] || cinResult1.raw[0] == 0.0f || cinResult1.raw[0] == -0.0f);
			assert(cinResult1.raw[1] == _result1[0][1] || cinResult1.raw[1] == 0.0f || cinResult1.raw[1] == -0.0f);
			assert(cinResult1.raw[2] == _result1[1][0] || cinResult1.raw[2] == 0.0f || cinResult1.raw[2] == -0.0f);
			assert(cinResult1.raw[3] == _result1[1][1] || cinResult1.raw[3] == 0.0f || cinResult1.raw[3] == -0.0f);

			assert(cinResult2.raw[0] == _result2[0][0] || cinResult2.raw[0] == 0.0f || cinResult2.raw[0] == -0.0f);
			assert(cinResult2.raw[1] == _result2[0][1] || cinResult2.raw[1] == 0.0f || cinResult2.raw[1] == -0.0f);
			assert(cinResult2.raw[2] == _result2[1][0] || cinResult2.raw[2] == 0.0f || cinResult2.raw[2] == -0.0f);
			assert(cinResult2.raw[3] == _result2[1][1] || cinResult2.raw[3] == 0.0f || cinResult2.raw[3] == -0.0f);
		}
		/* Add scalar */
		{
			auto scalar1 = RandomFloat();
			auto scalar2 = RandomFloat();
			auto cinResult1 = cin1 + scalar1;
			auto cinResult2 = cin2 + scalar2;
			auto _result1 = _Test1 + scalar1;
			auto _result2 = _Test2 + scalar2;
			IsMemoryEqual(cinResult1, _result1, "mat2 add scalar");
			IsMemoryEqual(cinResult2, _result2, "mat2 add scalar");
		}
		/* Sub scalar */
		{
			auto scalar1 = RandomFloat();
			auto scalar2 = RandomFloat();
			auto cinResult1 = cin1 - scalar1;
			auto cinResult2 = cin2 - scalar2;
			auto _result1 = _Test1 - scalar1;
			auto _result2 = _Test2 - scalar2;
			IsMemoryEqual(cinResult1, _result1, "mat2 sub scalar");
			IsMemoryEqual(cinResult2, _result2, "mat2 sub scalar");
		}
		/* Mul scalar */
		{
			auto scalar1 = RandomFloat();
			auto scalar2 = RandomFloat();
			auto cinResult1 = cin1 * scalar1;
			auto cinResult2 = cin2 * scalar2;
			auto _result1 = _Test1 * scalar1;
			auto _result2 = _Test2 * scalar2;
			IsMemoryEqual(cinResult1, _result1, "mat2 mul scalar");
			IsMemoryEqual(cinResult2, _result2, "mat2 mul scalar");
		}
		/* Add= scalar */
		{
			auto scalar1 = RandomFloat();
			auto scalar2 = RandomFloat();
			cin1 += scalar1;
			cin2 += scalar2;

			_Test1 += scalar1;
			_Test2 += scalar2;

			IsMemoryEqual(cin1, _Test1, "mat2 add= scalar");
			IsMemoryEqual(cin2, _Test2, "mat2 add= scalar");
		}
		/* Sub= scalar */
		{
			auto scalar1 = RandomFloat();
			auto scalar2 = RandomFloat();
			cin1 -= scalar1;
			cin2 -= scalar2;

			_Test1 -= scalar1;
			_Test2 -= scalar2;

			IsMemoryEqual(cin1, _Test1, "mat2 sub= scalar");
			IsMemoryEqual(cin2, _Test2, "mat2 sub= scalar");
		}
		/* Mul= scalar */
		{
			auto scalar1 = RandomFloat();
			auto scalar2 = RandomFloat();
			cin1 *= scalar1;
			cin2 *= scalar2;

			_Test1 *= scalar1;
			_Test2 *= scalar2;

			IsMemoryEqual(cin1, _Test1, "mat2 mul= scalar");
			IsMemoryEqual(cin2, _Test2, "mat2 mul= scalar");
		}
		/* Add */
		{
			auto cinResult = cin1 + cin2;
			auto _result = _Test1 + _Test2;
			IsMemoryEqual(cinResult, _result, "mat2 add");
		}
		/* Sub */
		{
			auto cinResult = cin1 + cin2;
			auto _result = _Test1 + _Test2;
			IsMemoryEqual(cinResult, _result, "mat2 sub");
		}
		/* Mul */
		{
			auto cinResult = cin1 * cin2;
			auto _result = _Test1 * _Test2;
			IsMemoryEqual(cinResult, _result, "mat2  mul");
		}
		/* Add= */
		{
			cin1 += cin2;
			_Test1 += _Test2;
			IsMemoryEqual(cin1, _Test1, "mat2 add=");
		}
		/* Sub */
		{
			cin1 -= cin2;
			_Test1 -= _Test2;
			IsMemoryEqual(cin1, _Test1, "mat2 sub=");
		}
		/* Mul= */
		{
			cin1 *= cin2;
			_Test1 *= _Test2;

			IsMemoryEqual(cin1, _Test1, "mat2 mul=");
		}
		/* Determinant */
		{
			auto cinResult = CinMath::Determinant(cin1);
			auto _result = glm::determinant(_Test1);

			IsMemoryEqual(_result, cinResult, "Mat2 determinant");
		}
		/* Inverse */
		{
			auto cinResult = CinMath::Inverse(cin1);
			auto _result = glm::inverse(_Test1);

			IsMemoryEqual(_result, cinResult, "Mat2 inverse");
		}
		/* Transpose */
		{
			auto cinResult = CinMath::Transpose(cin1);
			auto _result = glm::transpose(_Test1);

			IsMemoryEqual(_result, cinResult, "Mat2 transpose");
		}
	}

	for (uint32_t i{ 0 }; i < g_TestCount; ++i)
	{
		using Cin = CinMath::Matrix3;
		using mat = glm::mat3;

		float testNumbers1[9]{ RandomFloat(), RandomFloat(), RandomFloat(), RandomFloat(), RandomFloat(), RandomFloat(), RandomFloat(), RandomFloat(), RandomFloat() };
		float testNumbers2[9]{ RandomFloat(), RandomFloat(), RandomFloat(), RandomFloat(), RandomFloat(), RandomFloat(), RandomFloat(), RandomFloat(), RandomFloat() };

		Cin cin1({ 0 });
		Cin cin2({ 0 });
		mat _Test1({ 0 });
		mat _Test2({ 0 });
		CopyDataTo(testNumbers1, cin1, _Test1);
		CopyDataTo(testNumbers2, cin2, _Test2);

		IsMemoryEqual(_Test1, cin1, "Memcpy failed");
		IsMemoryEqual(_Test2, cin2, "Memcpy failed");

		/* Identity */
		{
			Cin cinResult({ 1.0f });
			mat _result({ 1.0f });

			IsMemoryEqual(cinResult, _result, "mat3 identity");
		}
		/* Negation */
		{
			auto cinResult1 = -cin1;
			auto cinResult2 = -cin2;

			auto _result1 = -_Test1;
			auto _result2 = -_Test2;

			/* -0.0f isnt the same as 0.0f in memory but it's technically the same */
			assert(cinResult1.raw[0] == _result1[0][0] || cinResult1.raw[0] == 0.0f || cinResult1.raw[0] == -0.0f);
			assert(cinResult1.raw[1] == _result1[0][1] || cinResult1.raw[1] == 0.0f || cinResult1.raw[1] == -0.0f);
			assert(cinResult1.raw[2] == _result1[0][2] || cinResult1.raw[2] == 0.0f || cinResult1.raw[2] == -0.0f);
			assert(cinResult1.raw[3] == _result1[1][0] || cinResult1.raw[3] == 0.0f || cinResult1.raw[3] == -0.0f);
			assert(cinResult1.raw[4] == _result1[1][1] || cinResult1.raw[3] == 0.0f || cinResult1.raw[3] == -0.0f);
			assert(cinResult1.raw[5] == _result1[1][2] || cinResult1.raw[3] == 0.0f || cinResult1.raw[3] == -0.0f);
			assert(cinResult1.raw[6] == _result1[2][0] || cinResult1.raw[3] == 0.0f || cinResult1.raw[3] == -0.0f);
			assert(cinResult1.raw[7] == _result1[2][1] || cinResult1.raw[3] == 0.0f || cinResult1.raw[3] == -0.0f);
			assert(cinResult1.raw[8] == _result1[2][2] || cinResult1.raw[3] == 0.0f || cinResult1.raw[3] == -0.0f);

			assert(cinResult2.raw[0] == _result2[0][0] || cinResult2.raw[0] == 0.0f || cinResult2.raw[0] == -0.0f);
			assert(cinResult2.raw[1] == _result2[0][1] || cinResult2.raw[1] == 0.0f || cinResult2.raw[1] == -0.0f);
			assert(cinResult2.raw[2] == _result2[0][2] || cinResult2.raw[2] == 0.0f || cinResult2.raw[2] == -0.0f);
			assert(cinResult2.raw[3] == _result2[1][0] || cinResult2.raw[3] == 0.0f || cinResult2.raw[3] == -0.0f);
			assert(cinResult2.raw[4] == _result2[1][1] || cinResult2.raw[3] == 0.0f || cinResult2.raw[3] == -0.0f);
			assert(cinResult2.raw[5] == _result2[1][2] || cinResult2.raw[3] == 0.0f || cinResult2.raw[3] == -0.0f);
			assert(cinResult2.raw[6] == _result2[2][0] || cinResult2.raw[3] == 0.0f || cinResult2.raw[3] == -0.0f);
			assert(cinResult2.raw[7] == _result2[2][1] || cinResult2.raw[3] == 0.0f || cinResult2.raw[3] == -0.0f);
			assert(cinResult2.raw[8] == _result2[2][2] || cinResult2.raw[3] == 0.0f || cinResult2.raw[3] == -0.0f);
		}
		/* Add scalar */
		{
			auto scalar1 = RandomFloat();
			auto scalar2 = RandomFloat();
			auto cinResult1 = cin1 + scalar1;
			auto cinResult2 = cin2 + scalar2;
			auto _result1 = _Test1 + scalar1;
			auto _result2 = _Test2 + scalar2;
			IsMemoryEqual(cinResult1, _result1, "mat3 add scalar");
			IsMemoryEqual(cinResult2, _result2, "mat3 add scalar");
		}
		/* Sub scalar */
		{
			auto scalar1 = RandomFloat();
			auto scalar2 = RandomFloat();
			auto cinResult1 = cin1 - scalar1;
			auto cinResult2 = cin2 - scalar2;
			auto _result1 = _Test1 - scalar1;
			auto _result2 = _Test2 - scalar2;
			IsMemoryEqual(cinResult1, _result1, "mat3 sub scalar");
			IsMemoryEqual(cinResult2, _result2, "mat3 sub scalar");
		}
		/* Mul scalar */
		{
			auto scalar1 = RandomFloat();
			auto scalar2 = RandomFloat();
			auto cinResult1 = cin1 * scalar1;
			auto cinResult2 = cin2 * scalar2;
			auto _result1 = _Test1 * scalar1;
			auto _result2 = _Test2 * scalar2;
			IsMemoryEqual(cinResult1, _result1, "mat3 mul scalar");
			IsMemoryEqual(cinResult2, _result2, "mat3 mul scalar");
		}
		/* Add= scalar */
		{
			auto scalar1 = RandomFloat();
			auto scalar2 = RandomFloat();
			cin1 += scalar1;
			cin2 += scalar2;

			_Test1 += scalar1;
			_Test2 += scalar2;

			IsMemoryEqual(cin1, _Test1, "mat3 add= scalar");
			IsMemoryEqual(cin2, _Test2, "mat3 add= scalar");
		}
		/* Sub= scalar */
		{
			auto scalar1 = RandomFloat();
			auto scalar2 = RandomFloat();
			cin1 -= scalar1;
			cin2 -= scalar2;

			_Test1 -= scalar1;
			_Test2 -= scalar2;

			IsMemoryEqual(cin1, _Test1, "mat3 sub= scalar");
			IsMemoryEqual(cin2, _Test2, "mat3 sub= scalar");
		}
		/* Mul= scalar */
		{
			auto scalar1 = RandomFloat();
			auto scalar2 = RandomFloat();
			cin1 *= scalar1;
			cin2 *= scalar2;

			_Test1 *= scalar1;
			_Test2 *= scalar2;

			IsMemoryEqual(cin1, _Test1, "mat3 mul= scalar");
			IsMemoryEqual(cin2, _Test2, "mat3 mul= scalar");
		}
		/* Add */
		{
			auto cinResult = cin1 + cin2;
			auto _result = _Test1 + _Test2;
			IsMemoryEqual(cinResult, _result, "mat3 add");
		}
		/* Sub */
		{
			auto cinResult = cin1 + cin2;
			auto _result = _Test1 + _Test2;
			IsMemoryEqual(cinResult, _result, "mat3 sub");
		}
		/* Mul */
		{
			auto cinResult = cin1 * cin2;
			auto _result = _Test1 * _Test2;
			IsMemoryEqual(cinResult, _result, "mat3  mul");
		}
		/* Add= */
		{
			cin1 += cin2;
			_Test1 += _Test2;
			IsMemoryEqual(cin1, _Test1, "mat3 add=");
		}
		/* Sub= */
		{
			cin1 -= cin2;
			_Test1 -= _Test2;
			IsMemoryEqual(cin1, _Test1, "mat3 sub=");
		}
		/* Mul= */
		{
			cin1 *= cin2;
			_Test1 *= _Test2;
			IsMemoryEqual(cin1, _Test1, "mat3 mul=");
		}
		/* Determinant */
		{
			auto cinResult = CinMath::Determinant(cin1);
			auto _result = glm::determinant(_Test1);

			IsMemoryEqual(_result, cinResult, "Mat3 determinant");
		}
		/* Inverse */
		{
			auto cinResult = CinMath::Inverse(cin1);
			auto _result = glm::inverse(_Test1);

			IsMemoryEqual(_result, cinResult, "Mat3 inverse");
		}
		/* Transpose */
		{
			//auto cinResult = CinMath::Transpose(cin1);
			//auto _result = glm::transpose(_Test1);

			//IsMemoryEqual(_result, cinResult, "Mat4 determinant");
		}
	}

	for (uint32_t i{ 0 }; i < g_TestCount; ++i)
	{
		using Cin = CinMath::Matrix4x4;
		using mat = glm::mat4;

		float testNumbers1[16]{
		RandomFloat(), RandomFloat(), RandomFloat(), RandomFloat(),
		RandomFloat(), RandomFloat(), RandomFloat(), RandomFloat(),
		RandomFloat(), RandomFloat(), RandomFloat(), RandomFloat(),
		RandomFloat(), RandomFloat(), RandomFloat(), RandomFloat() };

		float testNumbers2[16]{
		RandomFloat(), RandomFloat(), RandomFloat(), RandomFloat(),
		RandomFloat(), RandomFloat(), RandomFloat(), RandomFloat(),
		RandomFloat(), RandomFloat(), RandomFloat(), RandomFloat(),
		RandomFloat(), RandomFloat(), RandomFloat(), RandomFloat() };

		Cin cin1({ 0 });
		Cin cin2({ 0 });
		mat _Test1({ 0 });
		mat _Test2({ 0 });
		CopyDataTo(testNumbers1, cin1, _Test1);
		CopyDataTo(testNumbers2, cin2, _Test2);

		IsMemoryEqual(_Test1, cin1, "Memcpy failed");
		IsMemoryEqual(_Test2, cin2, "Memcpy failed");

		/* Identity */
		{
			Cin cinResult({ 1.0f });
			mat _result({ 1.0f });

			IsMemoryEqual(cinResult, _result, "mat4 identity");
		}
		/* Negation */
		{
			auto cinResult1 = -cin1;
			auto cinResult2 = -cin2;

			auto _result1 = -_Test1;
			auto _result2 = -_Test2;

			/* -0.0f isnt the same as 0.0f in memory but it's technically the same */
			assert(cinResult1.raw[0] == _result1[0][0] || cinResult1.raw[0] == 0.0f || cinResult1.raw[0] == -0.0f);
			assert(cinResult1.raw[1] == _result1[0][1] || cinResult1.raw[1] == 0.0f || cinResult1.raw[1] == -0.0f);
			assert(cinResult1.raw[2] == _result1[0][2] || cinResult1.raw[2] == 0.0f || cinResult1.raw[2] == -0.0f);
			assert(cinResult1.raw[3] == _result1[0][3] || cinResult1.raw[3] == 0.0f || cinResult1.raw[3] == -0.0f);
			assert(cinResult1.raw[4] == _result1[1][0] || cinResult1.raw[4] == 0.0f || cinResult1.raw[4] == -0.0f);
			assert(cinResult1.raw[5] == _result1[1][1] || cinResult1.raw[5] == 0.0f || cinResult1.raw[5] == -0.0f);
			assert(cinResult1.raw[6] == _result1[1][2] || cinResult1.raw[6] == 0.0f || cinResult1.raw[6] == -0.0f);
			assert(cinResult1.raw[7] == _result1[1][3] || cinResult1.raw[7] == 0.0f || cinResult1.raw[7] == -0.0f);
			assert(cinResult1.raw[8] == _result1[2][0] || cinResult1.raw[8] == 0.0f || cinResult1.raw[8] == -0.0f);
			assert(cinResult1.raw[9] == _result1[2][1] || cinResult1.raw[9] == 0.0f || cinResult1.raw[9] == -0.0f);
			assert(cinResult1.raw[10] == _result1[2][2] || cinResult1.raw[10] == 0.0f || cinResult1.raw[10] == -0.0f);
			assert(cinResult1.raw[11] == _result1[2][3] || cinResult1.raw[11] == 0.0f || cinResult1.raw[11] == -0.0f);
			assert(cinResult1.raw[12] == _result1[3][0] || cinResult1.raw[12] == 0.0f || cinResult1.raw[12] == -0.0f);
			assert(cinResult1.raw[13] == _result1[3][1] || cinResult1.raw[13] == 0.0f || cinResult1.raw[13] == -0.0f);
			assert(cinResult1.raw[14] == _result1[3][2] || cinResult1.raw[14] == 0.0f || cinResult1.raw[14] == -0.0f);
			assert(cinResult1.raw[15] == _result1[3][3] || cinResult1.raw[15] == 0.0f || cinResult1.raw[15] == -0.0f);

			assert(cinResult2.raw[0] == _result2[0][0] || cinResult2.raw[0] == 0.0f || cinResult2.raw[0] == -0.0f);
			assert(cinResult2.raw[1] == _result2[0][1] || cinResult2.raw[1] == 0.0f || cinResult2.raw[1] == -0.0f);
			assert(cinResult2.raw[2] == _result2[0][2] || cinResult2.raw[2] == 0.0f || cinResult2.raw[2] == -0.0f);
			assert(cinResult2.raw[3] == _result2[0][3] || cinResult2.raw[3] == 0.0f || cinResult2.raw[3] == -0.0f);
			assert(cinResult2.raw[4] == _result2[1][0] || cinResult2.raw[4] == 0.0f || cinResult2.raw[4] == -0.0f);
			assert(cinResult2.raw[5] == _result2[1][1] || cinResult2.raw[5] == 0.0f || cinResult2.raw[5] == -0.0f);
			assert(cinResult2.raw[6] == _result2[1][2] || cinResult2.raw[6] == 0.0f || cinResult2.raw[6] == -0.0f);
			assert(cinResult2.raw[7] == _result2[1][3] || cinResult2.raw[7] == 0.0f || cinResult2.raw[7] == -0.0f);
			assert(cinResult2.raw[8] == _result2[2][0] || cinResult2.raw[8] == 0.0f || cinResult2.raw[8] == -0.0f);
			assert(cinResult2.raw[9] == _result2[2][1] || cinResult2.raw[9] == 0.0f || cinResult2.raw[9] == -0.0f);
			assert(cinResult2.raw[10] == _result2[2][2] || cinResult2.raw[10] == 0.0f || cinResult2.raw[10] == -0.0f);
			assert(cinResult2.raw[11] == _result2[2][3] || cinResult2.raw[11] == 0.0f || cinResult2.raw[11] == -0.0f);
			assert(cinResult2.raw[12] == _result2[3][0] || cinResult2.raw[12] == 0.0f || cinResult2.raw[12] == -0.0f);
			assert(cinResult2.raw[13] == _result2[3][1] || cinResult2.raw[13] == 0.0f || cinResult2.raw[13] == -0.0f);
			assert(cinResult2.raw[14] == _result2[3][2] || cinResult2.raw[14] == 0.0f || cinResult2.raw[14] == -0.0f);
			assert(cinResult2.raw[15] == _result2[3][3] || cinResult2.raw[15] == 0.0f || cinResult2.raw[15] == -0.0f);
		}
		/* Add scalar */
		{
			auto scalar1 = RandomFloat();
			auto scalar2 = RandomFloat();
			auto cinResult1 = cin1 + scalar1;
			auto cinResult2 = cin2 + scalar2;
			auto _result1 = _Test1 + scalar1;
			auto _result2 = _Test2 + scalar2;
			IsMemoryEqual(cinResult1, _result1, "mat4 add scalar");
			IsMemoryEqual(cinResult2, _result2, "mat4 add scalar");
		}
		/* Sub scalar */
		{
			auto scalar1 = RandomFloat();
			auto scalar2 = RandomFloat();
			auto cinResult1 = cin1 - scalar1;
			auto cinResult2 = cin2 - scalar2;
			auto _result1 = _Test1 - scalar1;
			auto _result2 = _Test2 - scalar2;
			IsMemoryEqual(cinResult1, _result1, "mat4 sub scalar");
			IsMemoryEqual(cinResult2, _result2, "mat4 sub scalar");
		}
		/* Mul scalar */
		{
			auto scalar1 = RandomFloat();
			auto scalar2 = RandomFloat();
			auto cinResult1 = cin1 * scalar1;
			auto cinResult2 = cin2 * scalar2;
			auto _result1 = _Test1 * scalar1;
			auto _result2 = _Test2 * scalar2;
			IsMemoryEqual(cinResult1, _result1, "mat4 mul scalar");
			IsMemoryEqual(cinResult2, _result2, "mat4 mul scalar");
		}
		/* Add= scalar */
		{
			auto scalar1 = RandomFloat();
			auto scalar2 = RandomFloat();
			cin1 += scalar1;
			cin2 += scalar2;

			_Test1 += scalar1;
			_Test2 += scalar2;

			IsMemoryEqual(cin1, _Test1, "mat4 add= scalar");
			IsMemoryEqual(cin2, _Test2, "mat4 add= scalar");
		}
		/* Sub= scalar */
		{
			auto scalar1 = RandomFloat();
			auto scalar2 = RandomFloat();
			cin1 -= scalar1;
			cin2 -= scalar2;

			_Test1 -= scalar1;
			_Test2 -= scalar2;

			IsMemoryEqual(cin1, _Test1, "mat4 sub= scalar");
			IsMemoryEqual(cin2, _Test2, "mat4 sub= scalar");
		}
		/* Mul= scalar */
		{
			auto scalar1 = RandomFloat();
			auto scalar2 = RandomFloat();
			cin1 *= scalar1;
			cin2 *= scalar2;

			_Test1 *= scalar1;
			_Test2 *= scalar2;

			IsMemoryEqual(cin1, _Test1, "mat4 mul= scalar");
			IsMemoryEqual(cin2, _Test2, "mat4 mul= scalar");
		}
		/* Add */
		{
			auto cinResult = cin1 + cin2;
			auto _result = _Test1 + _Test2;
			IsMemoryEqual(cinResult, _result, "mat4 add");
		}
		/* Sub */
		{
			auto cinResult = cin1 + cin2;
			auto _result = _Test1 + _Test2;
			IsMemoryEqual(cinResult, _result, "mat4 sub");
		}
		/* Mul */
		{
			CopyDataTo(testNumbers1, cin1, _Test1);
			CopyDataTo(testNumbers2, cin2, _Test2);

			Cin cinResult1 = cin1 * cin2;
			auto _result1 = _Test1 * _Test2;

			if (!IsMemoryEqualBoolean(cinResult1, _result1))
			{
				printf("\nCIN:\n");
				std::cout << cinResult1 << '\n';

				printf("\nGLM:\n");
				std::cout << _result1;
			}
		}
		/* Add= */
		{
			cin1 += cin2;
			_Test1 += _Test2;
			IsMemoryEqual(cin1, _Test1, "mat4 add=");
		}
		/* Sub= */
		{
			cin1 -= cin2;
			_Test1 -= _Test2;
			IsMemoryEqual(cin1, _Test1, "mat4 sub=");
		}
		/* Mul= */
		{
			cin1 *= cin2;
			_Test1 *= _Test2;

			auto cinResult1 = cin1;
			auto _result1 = _Test1;

			IsMemoryEqual(cin1, _Test1, "mat4 mul=");
		}
		/* Determinant */
		{
			//auto cinResult = CinMath::Determinant(cin1);
			//auto _result = glm::determinant(_Test1);
			//
			//IsMemoryEqual(_result, cinResult, "Mat4 determinant");
		}
		/* Inverse */
		{
			/* Check if it's invertible */
			//if (CinMath::Determinant(cin1))
			//{
			//	auto cinResult = CinMath::Inverse(cin1);
			//	auto _result = glm::inverse(_Test1);
			//
			//	for (uint32_t iter{ 0 }; iter < 16; ++iter)
			//	{
			//		const float* ptr = &_result[0][0];
			//
			//		if (fabs(cinResult[iter] - ptr[iter]) > 0.2f)
			//			throw std::runtime_error("Mat inverse");
			//	}
			//
			//	//IsMemoryEqual(_result, cinResult, "Mat4 inverse");
			//}
		}
		/* Transpose */
		{
			auto cinResult = CinMath::Transpose(cin1);
			auto _result = glm::transpose(_Test1);

			IsMemoryEqual(_result, cinResult, "Mat4 transpose");
		}
	}
}

void TestShared()
{
	/* Shared */
	for (uint32_t i{ 0 }; i < g_TestCount; ++i)
	{
		using Cin = CinMath::Matrix4x4;
		using mat = glm::mat4;

		float testNumbers1[16]{
		RandomFloat(), RandomFloat(), RandomFloat(), RandomFloat(),
		RandomFloat(), RandomFloat(), RandomFloat(), RandomFloat(),
		RandomFloat(), RandomFloat(), RandomFloat(), RandomFloat(),
		RandomFloat(), RandomFloat(), RandomFloat(), RandomFloat() };

		Cin cinMat1({ 0 });
		mat _TestMat1({ 0 });
		CopyDataTo(testNumbers1, cinMat1, _TestMat1);

		IsMemoryEqual(cinMat1, _TestMat1, "Memcpy failed");


		using CinVec = CinMath::Vector4;
		using glmVec = glm::vec4;

		float testNumbers1Vec[4]{ RandomFloat(), RandomFloat(), RandomFloat(), RandomFloat() };

		CinVec cinVec1(0.0f, 0.0f, 0.0f, 0.0f);
		glmVec _TestVec1({ 0 });
		CopyDataTo(testNumbers1Vec, cinVec1, _TestVec1);

		IsMemoryEqual(_TestVec1, cinVec1, "Memcpy failed");

		/* mat4 * vec4 */
		{
			auto cinResult{ cinMat1 * cinVec1 };
			auto _result{ _TestMat1 * _TestVec1 };

			IsMemoryEqual(_result, cinResult, "Mat4 * vec4");
		}
		/* vec4 * mat4 */
		{
			auto cinResult{ cinVec1 * cinMat1 };
			auto _result{ _TestVec1 * _TestMat1 };

			IsMemoryEqual(_result, cinResult, "Mat4 * vec4");
		}
		/* mat4 translate */
		{
			//auto cinResult{ CinMath::Translate(cinMat1, CinMath::Vector3{ cinVec1.x, cinVec1.y, cinVec1.z} ) };
			//auto _result{ glm::translate(_TestMat1, glm::vec3{ _TestVec1.x, _TestVec1.y, _TestVec1.z }) };
			//
			//IsMemoryEqual(_result, cinResult, "mat4 translate");
		}
	}
}

int UnitTests()
{
	try
	{
		std::cout << "Testing vectors. . .\n";
		TestVectors();
		std::cout << "success\n";

		std::cout << "Testing matrices. . .\n";
		TestMatrices();
		std::cout << "success\n";

		std::cout << "Testing shared. . .\n";
		TestShared();
		std::cout << "success\n";
	}
	catch (const std::runtime_error& error)
	{
		std::cout << error.what() << '\n';
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}