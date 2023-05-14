#define CIN_USE_DEFAULT_INSTRUCTION_SET
//#define CIN_USE_SSE
//#define CIN_USE_AVX
#include "CinMath/CinMath.h"

#define TEST_PRINTING 0

constinit static size_t s_PassedTests{ 0U };
constinit static size_t s_FailedTests{ 0U };

#ifdef __LINE__
#define FILE_LINE __LINE__
#else
#define FILE_LINE "Unknown"
#endif

#define TEST_ASSERT(condition) if((condition)) ++s_PassedTests; else { ++s_FailedTests; fprintf(stderr, "Failed test: %s on line %d\n", #condition, (int)FILE_LINE); }

template<typename ValueType> 
static void TestVector2() noexcept;

template<typename ValueType>
static void TestVector3() noexcept;

template<typename ValueType>
static void TestVector4() noexcept;

template<typename ValueType>
static void TestSwizzling() noexcept;

template<typename ValueType>
static void TestMatrix2x2() noexcept;

template<typename ValueType>
static void TestMatrix3x3() noexcept;

template<typename ValueType>
static void TestMatrix4x4() noexcept;

template<typename ValueType> 
static void TestRadians() noexcept;

template<typename ValueType>
static void TestDegrees() noexcept;

template<typename ValueType>
static void TestAngle() noexcept;

template<typename ValueType>
static void TestAngularComparison() noexcept;

template<typename ValueType>
static void TestQuaternion() noexcept;

#if TEST_PRINTING
template<typename ValueType>
static void TestPrinting() noexcept;
#endif
template<typename ValueType>
static void TestOther() noexcept;

template<typename ValueType>
static void TestProjection() noexcept;

#define TEST(TestName) Test##TestName<float>(); Test##TestName<double>()

template<typename ValueType>
bool Approximate(const ValueType lhs, const ValueType rhs) noexcept
{
	if constexpr (std::is_same_v<float, ValueType>)
		return (std::fabs(lhs - rhs) < static_cast<ValueType>(0.001));
	else
		return (std::abs(lhs - rhs) < static_cast<ValueType>(0.001));
}

template<size_t rows, size_t columns, typename ValueType>
bool ApproximateMatrix(const CinMath::Matrix<rows, columns, ValueType>& lhs, const CinMath::Matrix<rows, columns, ValueType>& rhs) noexcept
{
	for (size_t i{ 0U }; i < rows * columns; ++i)
		if (std::abs(lhs[i] - rhs[i]) > static_cast<ValueType>(0.001))
			return false;

	return true;
}

int main([[maybe_unused]] const int argc, [[maybe_unused]] const char** argv) noexcept
{
	std::cout << "Tested instruction set:\n";
#if defined CIN_USE_DEFAULT_INSTRUCTION_SET
	std::cout << "Default";
#elif defined CIN_USE_SSE
	std::cout << "SSE";
#elif defined CIN_USE_AVX
	std::cout << "AVX";
#else
	std::cout << "UNKNOWN\n";
#endif
	/* Vector types */
	TEST(Vector2);
	TEST(Vector3);
	TEST(Vector4);

	/* Matrices */
	TEST(Matrix2x2);
	TEST(Matrix3x3);
	TEST(Matrix4x4);

	/* Radians, degrees, angle */
	TEST(Radians);
	TEST(Degrees);
	TEST(Angle);
	TEST(AngularComparison);
	
	/* Swizzling */
	TEST(Swizzling);
	
	/* Quaternions */
	TEST(Quaternion);
	
	/* Other */
	TEST(Other);
	TEST(Projection);
#if TEST_PRINTING
	TEST(Printing);
#endif
	std::cout <<
	"\n\n"
	"=================================\n"
	"             SUMMARY             \n"
	"=================================\n";
		
#ifdef NDEBUG
	std::cout << "TESTED IN RELEASE MODE\n";
#endif
	std::cout << "Tests passed: " << s_PassedTests << '\n';
	std::cout << "Tests failed: " << s_FailedTests << '\n';

	return s_FailedTests != 0U;
}

template<typename ValueType>
static void TestVector2() noexcept
{
	using namespace CinMath;
	using VectorType = Vector<2, ValueType>;
	
	/* consteval constructor */
	{
		constexpr VectorType vector;
		TEST_ASSERT(vector.x == static_cast<ValueType>(0))
		TEST_ASSERT(vector.y == static_cast<ValueType>(0))
	}
	/* constexpr single value constructor */
	{
		constexpr VectorType vector{ static_cast<ValueType>(42.0) };
		TEST_ASSERT(vector.x == static_cast<ValueType>(42.0))
		TEST_ASSERT(vector.y == static_cast<ValueType>(42.0))
		/* union */
		TEST_ASSERT(vector.u == static_cast<ValueType>(42.0))
		TEST_ASSERT(vector.v == static_cast<ValueType>(42.0))
	}
	/* constexpr constructor */
	{
		constexpr VectorType vector{ static_cast<ValueType>(13.0), static_cast<ValueType>(31.0) };
		TEST_ASSERT(vector.x == static_cast<ValueType>(13.0))
		TEST_ASSERT(vector.y == static_cast<ValueType>(31))
		/* union */
		TEST_ASSERT(vector.u == static_cast<ValueType>(13.0))
		TEST_ASSERT(vector.v == static_cast<ValueType>(31))
	}
	/* raw storage */
	{
		VectorType vector;
		TEST_ASSERT(reinterpret_cast<ValueType*>(std::addressof(vector)) == vector.operator ValueType * ());
		TEST_ASSERT(reinterpret_cast<ValueType*>(std::addressof(vector)) == vector.operator const ValueType * ());
	}
	/* array operator */
	{
		constexpr VectorType vector{ static_cast<ValueType>(13.0), static_cast<ValueType>(31.0) };
		TEST_ASSERT(vector[0U] == static_cast<ValueType>(13.0))
		TEST_ASSERT(vector[1U] == static_cast<ValueType>(31))
	}
	/* comparison operators */
	{
		constexpr VectorType vector1{ static_cast<ValueType>(13.0), static_cast<ValueType>(31.0) };
		constexpr VectorType vector1Copy{ static_cast<ValueType>(13.0), static_cast<ValueType>(31.0) };

		TEST_ASSERT(vector1 == vector1Copy);
	}
	/* comparison operators */
	{
		constexpr VectorType vector1{ static_cast<ValueType>(13.0), static_cast<ValueType>(31.0) };
		constexpr VectorType vector1Modified{ static_cast<ValueType>(13.0 + 1.0), static_cast<ValueType>(31.0 + 1.0) };

		TEST_ASSERT(vector1 != vector1Modified);
	}
	/* plus operator (does nothing really) */
	{
		constexpr VectorType vector1{ static_cast<ValueType>(13.0), static_cast<ValueType>(31.0) };
		TEST_ASSERT(vector1 == (+vector1));
	}
	/* negate operator */
	{
		constexpr VectorType vector1{ static_cast<ValueType>(13.0), static_cast<ValueType>(31.0) };
		VectorType vector2{ -vector1.x, -vector1.y };

		TEST_ASSERT(vector1 == (-vector2));
	}
	/* += operator */
	{
		VectorType vector1{ static_cast<ValueType>(13.0), static_cast<ValueType>(31.0) };
		vector1 += VectorType{ static_cast<ValueType>(1.0), static_cast<ValueType>(1.0) };

		TEST_ASSERT(vector1 == VectorType(static_cast<ValueType>(13.0 + 1.0), static_cast<ValueType>(31.0 + 1.0)));
	}
	/* -= operator */
	{
		VectorType vector1{ static_cast<ValueType>(13.0), static_cast<ValueType>(31.0) };
		vector1 -= VectorType{ static_cast<ValueType>(1.0), static_cast<ValueType>(1.0) };

		TEST_ASSERT(vector1 == VectorType(static_cast<ValueType>(13.0 - 1.0), static_cast<ValueType>(31.0 - 1.0)));
	}
	/* *= operator */
	{
		VectorType vector1{ static_cast<ValueType>(13.0), static_cast<ValueType>(31.0) };
		vector1 *= VectorType{ static_cast<ValueType>(3.0), static_cast<ValueType>(3.0) };

		TEST_ASSERT(vector1 == VectorType(static_cast<ValueType>(13.0 * 3.0), static_cast<ValueType>(31.0 * 3.0)));
	}
	/* /= operator */
	{
		VectorType vector1{ static_cast<ValueType>(13.0), static_cast<ValueType>(31.0) };
		vector1 /= VectorType{ static_cast<ValueType>(3.0), static_cast<ValueType>(3.0) };

		TEST_ASSERT(vector1 == VectorType(static_cast<ValueType>(13.0 / 3.0), static_cast<ValueType>(31.0 / 3.0)));
	}
	/* += operator (scalar) */
	{
		VectorType vector1{ static_cast<ValueType>(13.0), static_cast<ValueType>(31.0) };
		constexpr ValueType scalar{ static_cast<ValueType>(2.0) };
		vector1 += { scalar };

		TEST_ASSERT(vector1 == VectorType(static_cast<ValueType>(13.0 + scalar), static_cast<ValueType>(31.0 + scalar)));
	}
	/* -= operator (scalar) */
	{
		VectorType vector1{ static_cast<ValueType>(13.0), static_cast<ValueType>(31.0) };
		constexpr ValueType scalar{ static_cast<ValueType>(2.0) };
		vector1 -= { scalar };

		TEST_ASSERT(vector1 == VectorType(static_cast<ValueType>(13.0 - scalar), static_cast<ValueType>(31.0 - scalar)));
	}
	/* *= operator (scalar) */
	{
		VectorType vector1{ static_cast<ValueType>(13.0), static_cast<ValueType>(31.0) };
		constexpr ValueType scalar{ static_cast<ValueType>(2.0) };
		vector1 *= { scalar };

		TEST_ASSERT(vector1 == VectorType(static_cast<ValueType>(13.0 * scalar), static_cast<ValueType>(31.0 * scalar)));
	}
	/* /= operator (scalar) */
	{
		VectorType vector1{ static_cast<ValueType>(13.0), static_cast<ValueType>(31.0) };
		constexpr ValueType scalar{ static_cast<ValueType>(2.0) };
		vector1 /= { scalar };

		TEST_ASSERT(vector1 == VectorType(static_cast<ValueType>(13.0 / scalar), static_cast<ValueType>(31.0 / scalar)));
	}
	/* operator+ */
	{
		constexpr ValueType scalar1{ static_cast<ValueType>(2.0) };
		constexpr ValueType scalar2{ static_cast<ValueType>(3.0) };

		constexpr VectorType vector{ static_cast<ValueType>(13.0), static_cast<ValueType>(31.0) };
		VectorType operation{ vector + VectorType{ scalar1, scalar2 } };

		TEST_ASSERT(operation == VectorType(vector.x + scalar1, vector.y + scalar2));
	}
	/* operator- */
	{
		constexpr ValueType scalar1{ static_cast<ValueType>(2.0) };
		constexpr ValueType scalar2{ static_cast<ValueType>(3.0) };

		constexpr VectorType vector{ static_cast<ValueType>(13.0), static_cast<ValueType>(31.0) };
		VectorType operation{ vector - VectorType{ scalar1, scalar2 } };

		TEST_ASSERT(operation == VectorType(vector.x - scalar1, vector.y - scalar2));
	}
	/* operator* */
	{
		constexpr ValueType scalar1{ static_cast<ValueType>(2.0) };
		constexpr ValueType scalar2{ static_cast<ValueType>(3.0) };

		constexpr VectorType vector{ static_cast<ValueType>(13.0), static_cast<ValueType>(31.0) };
		VectorType operation{ vector * VectorType{ scalar1, scalar2 } };

		TEST_ASSERT(operation == VectorType(vector.x * scalar1, vector.y * scalar2));
	}
	/* operator/ */
	{
		constexpr ValueType scalar1{ static_cast<ValueType>(2.0) };
		constexpr ValueType scalar2{ static_cast<ValueType>(3.0) };

		constexpr VectorType vector{ static_cast<ValueType>(13.0), static_cast<ValueType>(31.0) };
		VectorType operation{ vector / VectorType{ scalar1, scalar2 } };

		TEST_ASSERT(operation == VectorType(vector.x / scalar1, vector.y / scalar2));
	}
	/* operator+ (scalar) */
	{
		constexpr ValueType scalar{ static_cast<ValueType>(2.0) };
		constexpr VectorType vector{ static_cast<ValueType>(13.0), static_cast<ValueType>(31.0) };
		VectorType operation{ vector + VectorType{ scalar, scalar } };

		TEST_ASSERT(operation == VectorType(vector.x + scalar, vector.y + scalar));
	}
	/* operator- (scalar) */
	{
		constexpr ValueType scalar{ static_cast<ValueType>(2.0) };
		constexpr VectorType vector{ static_cast<ValueType>(13.0), static_cast<ValueType>(31.0) };
		VectorType operation{ vector - VectorType{ scalar, scalar } };

		TEST_ASSERT(operation == VectorType(vector.x - scalar, vector.y - scalar));
	}
	/* operator* (scalar) */
	{
		constexpr ValueType scalar{ static_cast<ValueType>(2.0) };
		constexpr VectorType vector{ static_cast<ValueType>(13.0), static_cast<ValueType>(31.0) };
		VectorType operation{ vector * VectorType{ scalar, scalar } };

		TEST_ASSERT(operation == VectorType(vector.x * scalar, vector.y * scalar));
	}
	/* operator/ (scalar) */
	{
		constexpr ValueType scalar{ static_cast<ValueType>(2.0) };
		constexpr VectorType vector{ static_cast<ValueType>(13.0), static_cast<ValueType>(31.0) };
		VectorType operation{ vector / VectorType{ scalar, scalar } };

		TEST_ASSERT(operation == VectorType(vector.x / scalar, vector.y / scalar));
	}
	/* Conversion */
	{
		/* float -> double, double -> float */
		using OtherType = std::conditional<std::is_same_v<ValueType, float>, double, float>::type;
		static_assert(!std::is_same_v<OtherType, ValueType>);

		constexpr VectorType lhs{ static_cast<ValueType>(2), static_cast<ValueType>(4) };
		constexpr Vector<2, OtherType> rhs{ static_cast<OtherType>(2), static_cast<OtherType>(4) };
		const VectorType casted{ static_cast<VectorType>(rhs) };
		
		const bool result{ casted == lhs };
		TEST_ASSERT(result);
	}
}

template<typename ValueType>
static void TestVector3() noexcept
{
	using namespace CinMath;
	using VectorType = Vector<3, ValueType>;

	/* consteval constructor */
	{
		constexpr VectorType vector;
		TEST_ASSERT(vector.x == static_cast<ValueType>(0))
		TEST_ASSERT(vector.y == static_cast<ValueType>(0))
		TEST_ASSERT(vector.z == static_cast<ValueType>(0))
	}
	/* constexpr single value constructor */
	{
		constexpr VectorType vector{ static_cast<ValueType>(42.0) };
		TEST_ASSERT(vector.x == static_cast<ValueType>(42.0))
		TEST_ASSERT(vector.y == static_cast<ValueType>(42.0))
		TEST_ASSERT(vector.z == static_cast<ValueType>(42.0))
		/* union */
		TEST_ASSERT(vector.r == static_cast<ValueType>(42.0))
		TEST_ASSERT(vector.g == static_cast<ValueType>(42.0))
		TEST_ASSERT(vector.b == static_cast<ValueType>(42.0))
	}
	/* constexpr constructor */
	{
		constexpr VectorType vector{ static_cast<ValueType>(13.0), static_cast<ValueType>(31.0), static_cast<ValueType>(15.0) };
		TEST_ASSERT(vector.x == static_cast<ValueType>(13.0))
		TEST_ASSERT(vector.y == static_cast<ValueType>(31.0))
		TEST_ASSERT(vector.z == static_cast<ValueType>(15.0))
		/* union */
		TEST_ASSERT(vector.r == static_cast<ValueType>(13.0))
		TEST_ASSERT(vector.g == static_cast<ValueType>(31.0))
		TEST_ASSERT(vector.b == static_cast<ValueType>(15.0))
	}
	/* raw storage */
	{
		VectorType vector;
		TEST_ASSERT(reinterpret_cast<ValueType*>(std::addressof(vector)) == vector.operator ValueType * ());
		TEST_ASSERT(reinterpret_cast<ValueType*>(std::addressof(vector)) == vector.operator const ValueType * ());
	}
	/* array operator */
	{
		constexpr VectorType vector{ static_cast<ValueType>(13.0), static_cast<ValueType>(31.0), static_cast<ValueType>(15.0) };
		TEST_ASSERT(vector[0U] == static_cast<ValueType>(13.0))
		TEST_ASSERT(vector[1U] == static_cast<ValueType>(31.0))
		TEST_ASSERT(vector[2U] == static_cast<ValueType>(15.0))
	}
	/* comparison operators */
	{
		constexpr VectorType vector1{ static_cast<ValueType>(13.0), static_cast<ValueType>(31.0), static_cast<ValueType>(15.0) };
		constexpr VectorType vector1Copy{ static_cast<ValueType>(13.0), static_cast<ValueType>(31.0), static_cast<ValueType>(15.0) };

		TEST_ASSERT(vector1 == vector1Copy);
	}
	/* comparison operators */
	{
		constexpr VectorType vector1{ static_cast<ValueType>(13.0), static_cast<ValueType>(31.0), static_cast<ValueType>(15.0) };
		constexpr VectorType vector1Modified{ static_cast<ValueType>(13.0 + 1.0), static_cast<ValueType>(31.0), static_cast<ValueType>(15.0) };

		TEST_ASSERT(vector1 != vector1Modified);
	}
	/* plus operator (does nothing really) */
	{
		constexpr VectorType vector{ static_cast<ValueType>(13.0), static_cast<ValueType>(31.0), static_cast<ValueType>(15.0) };
		TEST_ASSERT(vector == (+vector));
	}
	/* negate operator */
	{
		constexpr VectorType vector1{ static_cast<ValueType>(13.0), static_cast<ValueType>(31.0), static_cast<ValueType>(15.0) };
		VectorType vector2{ -vector1.x, -vector1.y, -vector1.z };

		TEST_ASSERT(vector1 == (-vector2));
	}
	/* += operator */
	{
		VectorType vector1{ static_cast<ValueType>(13.0), static_cast<ValueType>(31.0), static_cast<ValueType>(15.0) };
		vector1 += VectorType{ static_cast<ValueType>(1.0), static_cast<ValueType>(1.0), static_cast<ValueType>(1.0) };

		TEST_ASSERT(vector1 == VectorType(static_cast<ValueType>(13.0 + 1.0), static_cast<ValueType>(31.0 + 1.0), static_cast<ValueType>(15.0 + 1.0)));
	}
	/* -= operator */
	{
		VectorType vector1{ static_cast<ValueType>(13.0), static_cast<ValueType>(31.0), static_cast<ValueType>(15.0) };
		vector1 -= VectorType{ static_cast<ValueType>(1.0), static_cast<ValueType>(1.0), static_cast<ValueType>(1.0) };

		TEST_ASSERT(vector1 == VectorType(static_cast<ValueType>(13.0 - 1.0), static_cast<ValueType>(31.0 - 1.0), static_cast<ValueType>(15.0 - 1.0)));
	}
	/* *= operator */
	{
		VectorType vector1{ static_cast<ValueType>(13.0), static_cast<ValueType>(31.0), static_cast<ValueType>(15.0) };
		vector1 *= VectorType{static_cast<ValueType>(3.0), static_cast<ValueType>(3.0), static_cast<ValueType>(3.0) };

		TEST_ASSERT(vector1 == VectorType(static_cast<ValueType>(13.0 * 3.0), static_cast<ValueType>(31.0 * 3.0), static_cast<ValueType>(15.0 * 3.0)));
	}
	/* /= operator */
	{
		VectorType vector1{ static_cast<ValueType>(13.0), static_cast<ValueType>(31.0), static_cast<ValueType>(15.0) };
		vector1 /= VectorType{static_cast<ValueType>(3.0), static_cast<ValueType>(3.0), static_cast<ValueType>(3.0) };

		TEST_ASSERT(vector1 == VectorType(static_cast<ValueType>(13.0 / 3.0), static_cast<ValueType>(31.0 / 3.0), static_cast<ValueType>(15.0 / 3.0)));
	}
	/* += operator (scalar) */
	{
		VectorType vector1{ static_cast<ValueType>(13.0), static_cast<ValueType>(31.0), static_cast<ValueType>(15.0) };
		constexpr ValueType scalar{ static_cast<ValueType>(2.0) };
		vector1 += { scalar };

		TEST_ASSERT(vector1 == VectorType(static_cast<ValueType>(13.0 + scalar), static_cast<ValueType>(31.0 + scalar), static_cast<ValueType>(15.0 + scalar)));
	}
	/* -= operator (scalar) */
	{
		VectorType vector1{ static_cast<ValueType>(13.0), static_cast<ValueType>(31.0), static_cast<ValueType>(15.0) };
		constexpr ValueType scalar{ static_cast<ValueType>(2.0) };
		vector1 -= { scalar };

		TEST_ASSERT(vector1 == VectorType(static_cast<ValueType>(13.0 - scalar), static_cast<ValueType>(31.0 - scalar), static_cast<ValueType>(15.0 - scalar)));
	}
	/* *= operator (scalar) */
	{
		VectorType vector1{ static_cast<ValueType>(13.0), static_cast<ValueType>(31.0), static_cast<ValueType>(15.0) };
		constexpr ValueType scalar{ static_cast<ValueType>(2.0) };
		vector1 *= { scalar };

		TEST_ASSERT(vector1 == VectorType(static_cast<ValueType>(13.0 * scalar), static_cast<ValueType>(31.0 * scalar), static_cast<ValueType>(15.0 * scalar)));
	}
	/* /= operator (scalar) */
	{
		VectorType vector1{ static_cast<ValueType>(13.0), static_cast<ValueType>(31.0), static_cast<ValueType>(15.0) };
		constexpr ValueType scalar{ static_cast<ValueType>(2.0) };
		vector1 /= { scalar };

		TEST_ASSERT(vector1 == VectorType(static_cast<ValueType>(13.0 / scalar), static_cast<ValueType>(31.0 / scalar), static_cast<ValueType>(15.0 / scalar)));
	}
	/* operator+ */
	{
		constexpr ValueType scalar1{ static_cast<ValueType>(2.0) };
		constexpr ValueType scalar2{ static_cast<ValueType>(3.0) };
		constexpr ValueType scalar3{ static_cast<ValueType>(4.0) };

		constexpr VectorType vector{ static_cast<ValueType>(13.0), static_cast<ValueType>(31.0), static_cast<ValueType>(15.0) };
		VectorType operation{ vector + VectorType{ scalar1, scalar2, scalar3 } };

		TEST_ASSERT(operation == VectorType(vector.x + scalar1, vector.y + scalar2, vector.z + scalar3));
	}
	/* operator- */
	{
		constexpr ValueType scalar1{ static_cast<ValueType>(2.0) };
		constexpr ValueType scalar2{ static_cast<ValueType>(3.0) };
		constexpr ValueType scalar3{ static_cast<ValueType>(4.0) };

		constexpr VectorType vector{ static_cast<ValueType>(13.0), static_cast<ValueType>(31.0), static_cast<ValueType>(15.0) };
		VectorType operation{ vector - VectorType{ scalar1, scalar2, scalar3 } };

		TEST_ASSERT(operation == VectorType(vector.x - scalar1, vector.y - scalar2, vector.z - scalar3));
	}
	/* operator* */
	{
		constexpr ValueType scalar1{ static_cast<ValueType>(2.0) };
		constexpr ValueType scalar2{ static_cast<ValueType>(3.0) };
		constexpr ValueType scalar3{ static_cast<ValueType>(4.0) };

		constexpr VectorType vector{ static_cast<ValueType>(13.0), static_cast<ValueType>(31.0), static_cast<ValueType>(15.0) };
		VectorType operation{ vector * VectorType{ scalar1, scalar2, scalar3 } };

		TEST_ASSERT(operation == VectorType(vector.x * scalar1, vector.y * scalar2, vector.z * scalar3));
	}
	/* operator/ */
	{
		constexpr ValueType scalar1{ static_cast<ValueType>(2.0) };
		constexpr ValueType scalar2{ static_cast<ValueType>(3.0) };
		constexpr ValueType scalar3{ static_cast<ValueType>(4.0) };

		constexpr VectorType vector{ static_cast<ValueType>(13.0), static_cast<ValueType>(31.0), static_cast<ValueType>(15.0) };
		VectorType operation{ vector / VectorType{ scalar1, scalar2, scalar3 } };

		TEST_ASSERT(operation == VectorType(vector.x / scalar1, vector.y / scalar2, vector.z / scalar3));
	}
	/* operator+ (scalar) */
	{
		constexpr ValueType scalar{ static_cast<ValueType>(2.0) };
		constexpr VectorType vector{ static_cast<ValueType>(13.0), static_cast<ValueType>(31.0), static_cast<ValueType>(15.0) };
		VectorType operation{ vector + VectorType{ scalar, scalar, scalar } };

		TEST_ASSERT(operation == VectorType(vector.x + scalar, vector.y + scalar, vector.z + scalar));
	}
	/* operator- (scalar) */
	{
		constexpr ValueType scalar{ static_cast<ValueType>(2.0) };
		constexpr VectorType vector{ static_cast<ValueType>(13.0), static_cast<ValueType>(31.0), static_cast<ValueType>(15.0) };
		VectorType operation{ vector - VectorType{ scalar, scalar, scalar } };

		TEST_ASSERT(operation == VectorType(vector.x - scalar, vector.y - scalar, vector.z - scalar));
	}
	/* operator* (scalar) */
	{
		constexpr ValueType scalar{ static_cast<ValueType>(2.0) };
		constexpr VectorType vector{ static_cast<ValueType>(13.0), static_cast<ValueType>(31.0), static_cast<ValueType>(15.0) };
		VectorType operation{ vector * VectorType{ scalar, scalar, scalar } };

		TEST_ASSERT(operation == VectorType(vector.x * scalar, vector.y * scalar, vector.z * scalar));
	}
	/* operator/ (scalar) */
	{
		constexpr ValueType scalar{ static_cast<ValueType>(2.0) };
		constexpr VectorType vector{ static_cast<ValueType>(13.0), static_cast<ValueType>(31.0), static_cast<ValueType>(15.0) };
		VectorType operation{ vector / VectorType{ scalar, scalar, scalar } };

		TEST_ASSERT(operation == VectorType(vector.x / scalar, vector.y / scalar, vector.z / scalar));
	}
	/* Conversion */
	{
		/* float -> double, double -> float */
		using OtherType = std::conditional<std::is_same_v<ValueType, float>, double, float>::type;
		static_assert(!std::is_same_v<OtherType, ValueType>);

		constexpr VectorType lhs{ static_cast<ValueType>(2), static_cast<ValueType>(4), static_cast<ValueType>(6) };
		constexpr Vector<3, OtherType> rhs{ static_cast<OtherType>(2), static_cast<OtherType>(4),  static_cast<OtherType>(6) };
		const VectorType casted{ static_cast<VectorType>(rhs) };
		
		const bool result{ casted == lhs };
		TEST_ASSERT(result);
	}
}

template<typename ValueType>
static void TestVector4() noexcept
{
	using namespace CinMath;
	using VectorType = Vector<4, ValueType>;

	/* consteval constructor */
	{
		constexpr VectorType vector;
		TEST_ASSERT(vector.x == static_cast<ValueType>(0))
		TEST_ASSERT(vector.y == static_cast<ValueType>(0))
		TEST_ASSERT(vector.z == static_cast<ValueType>(0))
		TEST_ASSERT(vector.w == static_cast<ValueType>(0))
	}
	/* constexpr single value constructor */
	{
		constexpr VectorType vector{ static_cast<ValueType>(42.0) };
		TEST_ASSERT(vector.x == static_cast<ValueType>(42.0))
		TEST_ASSERT(vector.y == static_cast<ValueType>(42.0))
		TEST_ASSERT(vector.z == static_cast<ValueType>(42.0))
		TEST_ASSERT(vector.w == static_cast<ValueType>(42.0))
		/* union */
		TEST_ASSERT(vector.r == static_cast<ValueType>(42.0))
		TEST_ASSERT(vector.g == static_cast<ValueType>(42.0))
		TEST_ASSERT(vector.b == static_cast<ValueType>(42.0))
		TEST_ASSERT(vector.a == static_cast<ValueType>(42.0))
	}
	/* constexpr constructor */
	{
		constexpr VectorType vector{ static_cast<ValueType>(13.0), static_cast<ValueType>(31.0), static_cast<ValueType>(15.0),  static_cast<ValueType>(51.0) };
		TEST_ASSERT(vector.x == static_cast<ValueType>(13.0))
		TEST_ASSERT(vector.y == static_cast<ValueType>(31.0))
		TEST_ASSERT(vector.z == static_cast<ValueType>(15.0))
		TEST_ASSERT(vector.w == static_cast<ValueType>(51.0))
		/* union */
		TEST_ASSERT(vector.r == static_cast<ValueType>(13.0))
		TEST_ASSERT(vector.g == static_cast<ValueType>(31.0))
		TEST_ASSERT(vector.b == static_cast<ValueType>(15.0))
		TEST_ASSERT(vector.a == static_cast<ValueType>(51.0))
	}
	/* raw storage */
	{
		VectorType vector;
		TEST_ASSERT(reinterpret_cast<ValueType*>(std::addressof(vector)) == vector.operator ValueType * ());
		TEST_ASSERT(reinterpret_cast<ValueType*>(std::addressof(vector)) == vector.operator const ValueType * ());
	}
	/* array operator */
	{
		constexpr VectorType vector{ static_cast<ValueType>(13.0), static_cast<ValueType>(31.0), static_cast<ValueType>(15.0), static_cast<ValueType>(51.0) };
		TEST_ASSERT(vector[0U] == static_cast<ValueType>(13.0))
		TEST_ASSERT(vector[1U] == static_cast<ValueType>(31.0))
		TEST_ASSERT(vector[2U] == static_cast<ValueType>(15.0))
		TEST_ASSERT(vector[3U] == static_cast<ValueType>(51.0))
	}
	/* comparison operators */
	{
		constexpr VectorType vector1{ static_cast<ValueType>(13.0), static_cast<ValueType>(31.0), static_cast<ValueType>(15.0), static_cast<ValueType>(51.0) };
		constexpr VectorType vector1Copy{ static_cast<ValueType>(13.0), static_cast<ValueType>(31.0), static_cast<ValueType>(15.0), static_cast<ValueType>(51.0) };

		TEST_ASSERT(vector1 == vector1Copy);
	}
	/* comparison operators */
	{
		constexpr VectorType vector1{ static_cast<ValueType>(13.0), static_cast<ValueType>(31.0), static_cast<ValueType>(15.0), static_cast<ValueType>(51.0) };
		constexpr VectorType vector1Modified{ static_cast<ValueType>(13.0 + 1.0), static_cast<ValueType>(31.0), static_cast<ValueType>(15.0), static_cast<ValueType>(51.0) };

		TEST_ASSERT(vector1 != vector1Modified);
	}
	/* plus operator (does nothing really) */
	{
		constexpr VectorType vector{ static_cast<ValueType>(13.0), static_cast<ValueType>(31.0), static_cast<ValueType>(15.0), static_cast<ValueType>(51.0) };
		TEST_ASSERT(vector == (+vector));
	}
	/* negate operator */
	{
		constexpr VectorType vector1{ static_cast<ValueType>(13.0), static_cast<ValueType>(31.0), static_cast<ValueType>(15.0), static_cast<ValueType>(51.0) };
		VectorType vector2{ -vector1.x, -vector1.y, -vector1.z, -vector1.w };

		TEST_ASSERT(vector1 == (-vector2));
	}
	/* += operator */
	{
		VectorType vector1{ static_cast<ValueType>(13.0), static_cast<ValueType>(31.0), static_cast<ValueType>(15.0), static_cast<ValueType>(51.0) };
		vector1 += VectorType{ static_cast<ValueType>(1.0), static_cast<ValueType>(1.0), static_cast<ValueType>(1.0), static_cast<ValueType>(1.0) };

		TEST_ASSERT(vector1 == VectorType(static_cast<ValueType>(13.0 + 1.0), static_cast<ValueType>(31.0 + 1.0), static_cast<ValueType>(15.0 + 1.0), static_cast<ValueType>(51.0 + 1.0)));
	}
	/* -= operator */
	{
		VectorType vector1{ static_cast<ValueType>(13.0), static_cast<ValueType>(31.0), static_cast<ValueType>(15.0), static_cast<ValueType>(51.0) };
		vector1 -= VectorType{ static_cast<ValueType>(1.0), static_cast<ValueType>(1.0), static_cast<ValueType>(1.0), static_cast<ValueType>(1.0) };

		TEST_ASSERT(vector1 == VectorType(static_cast<ValueType>(13.0 - 1.0), static_cast<ValueType>(31.0 - 1.0), static_cast<ValueType>(15.0 - 1.0), static_cast<ValueType>(51.0 - 1.0)));
	}
	/* *= operator */
	{
		VectorType vector1{ static_cast<ValueType>(13.0), static_cast<ValueType>(31.0), static_cast<ValueType>(15.0), static_cast<ValueType>(51.0) };
		vector1 *= VectorType{ static_cast<ValueType>(3.0), static_cast<ValueType>(3.0), static_cast<ValueType>(3.0), static_cast<ValueType>(3.0) };

		TEST_ASSERT(vector1 == VectorType(static_cast<ValueType>(13.0 * 3.0), static_cast<ValueType>(31.0 * 3.0), static_cast<ValueType>(15.0 * 3.0), static_cast<ValueType>(51.0 * 3.0)));
	}
	/* /= operator */
	{
		VectorType vector1{ static_cast<ValueType>(13.0), static_cast<ValueType>(31.0), static_cast<ValueType>(15.0), static_cast<ValueType>(51.0) };
		vector1 /= VectorType{ static_cast<ValueType>(3.0), static_cast<ValueType>(3.0), static_cast<ValueType>(3.0), static_cast<ValueType>(3.0) };

		TEST_ASSERT(vector1 == VectorType(static_cast<ValueType>(13.0 / 3.0), static_cast<ValueType>(31.0 / 3.0), static_cast<ValueType>(15.0 / 3.0), static_cast<ValueType>(51 / 3.0)));
	}
	/* += operator (scalar) */
	{
		VectorType vector1{ static_cast<ValueType>(13.0), static_cast<ValueType>(31.0), static_cast<ValueType>(15.0), static_cast<ValueType>(51.0) };
		constexpr ValueType scalar{ static_cast<ValueType>(2.0) };
		vector1 += { scalar };

		TEST_ASSERT(vector1 == VectorType(static_cast<ValueType>(13.0 + scalar), static_cast<ValueType>(31.0 + scalar), static_cast<ValueType>(15.0 + scalar), static_cast<ValueType>(51.0 + scalar)));
	}
	/* -= operator (scalar) */
	{
		VectorType vector1{ static_cast<ValueType>(13.0), static_cast<ValueType>(31.0), static_cast<ValueType>(15.0), static_cast<ValueType>(51.0) };
		constexpr ValueType scalar{ static_cast<ValueType>(2.0) };
		vector1 -= { scalar };

		TEST_ASSERT(vector1 == VectorType(static_cast<ValueType>(13.0 - scalar), static_cast<ValueType>(31.0 - scalar), static_cast<ValueType>(15.0 - scalar), static_cast<ValueType>(51.0 - scalar)));
	}
	/* *= operator (scalar) */
	{
		VectorType vector1{ static_cast<ValueType>(13.0), static_cast<ValueType>(31.0), static_cast<ValueType>(15.0), static_cast<ValueType>(51.0) };
		constexpr ValueType scalar{ static_cast<ValueType>(2.0) };
		vector1 *= { scalar };

		TEST_ASSERT(vector1 == VectorType(static_cast<ValueType>(13.0 * scalar), static_cast<ValueType>(31.0 * scalar), static_cast<ValueType>(15.0 * scalar), static_cast<ValueType>(51.0 * scalar)));
	}
	/* /= operator (scalar) */
	{
		VectorType vector1{ static_cast<ValueType>(13.0), static_cast<ValueType>(31.0), static_cast<ValueType>(15.0), static_cast<ValueType>(51.0) };
		constexpr ValueType scalar{ static_cast<ValueType>(2.0) };
		vector1 /= { scalar };

		TEST_ASSERT(vector1 == VectorType(static_cast<ValueType>(13.0 / scalar), static_cast<ValueType>(31.0 / scalar), static_cast<ValueType>(15.0 / scalar), static_cast<ValueType>(51.0 / scalar)));
	}
	/* operator+ */
	{
		constexpr ValueType scalar1{ static_cast<ValueType>(2.0) };
		constexpr ValueType scalar2{ static_cast<ValueType>(3.0) };
		constexpr ValueType scalar3{ static_cast<ValueType>(4.0) };
		constexpr ValueType scalar4{ static_cast<ValueType>(5.0) };

		constexpr VectorType vector{ static_cast<ValueType>(13.0), static_cast<ValueType>(31.0), static_cast<ValueType>(15.0), static_cast<ValueType>(51.0) };
		VectorType operation{ vector + VectorType{ scalar1, scalar2, scalar3, scalar4 } };

		TEST_ASSERT(operation == VectorType(vector.x + scalar1, vector.y + scalar2, vector.z + scalar3, vector.w + scalar4));
	}
	/* operator- */
	{
		constexpr ValueType scalar1{ static_cast<ValueType>(2.0) };
		constexpr ValueType scalar2{ static_cast<ValueType>(3.0) };
		constexpr ValueType scalar3{ static_cast<ValueType>(4.0) };
		constexpr ValueType scalar4{ static_cast<ValueType>(5.0) };

		constexpr VectorType vector{ static_cast<ValueType>(13.0), static_cast<ValueType>(31.0), static_cast<ValueType>(15.0), static_cast<ValueType>(51.0) };
		VectorType operation{ vector - VectorType{ scalar1, scalar2, scalar3, scalar4 } };

		TEST_ASSERT(operation == VectorType(vector.x - scalar1, vector.y - scalar2, vector.z - scalar3, vector.w - scalar4));
	}
	/* operator* */
	{
		constexpr ValueType scalar1{ static_cast<ValueType>(2.0) };
		constexpr ValueType scalar2{ static_cast<ValueType>(3.0) };
		constexpr ValueType scalar3{ static_cast<ValueType>(4.0) };
		constexpr ValueType scalar4{ static_cast<ValueType>(5.0) };

		constexpr VectorType vector{ static_cast<ValueType>(13.0), static_cast<ValueType>(31.0), static_cast<ValueType>(15.0), static_cast<ValueType>(51.0) };
		VectorType operation{ vector * VectorType{ scalar1, scalar2, scalar3, scalar4 } };

		TEST_ASSERT(operation == VectorType(vector.x * scalar1, vector.y * scalar2, vector.z * scalar3, vector.w * scalar4));
	}
	/* operator/ */
	{
		constexpr ValueType scalar1{ static_cast<ValueType>(2.0) };
		constexpr ValueType scalar2{ static_cast<ValueType>(3.0) };
		constexpr ValueType scalar3{ static_cast<ValueType>(4.0) };
		constexpr ValueType scalar4{ static_cast<ValueType>(5.0) };

		constexpr VectorType vector{ static_cast<ValueType>(13.0), static_cast<ValueType>(31.0), static_cast<ValueType>(15.0), static_cast<ValueType>(51.0) };
		VectorType operation{ vector / VectorType{ scalar1, scalar2, scalar3, scalar4 } };

		TEST_ASSERT(operation == VectorType(vector.x / scalar1, vector.y / scalar2, vector.z / scalar3, vector.w / scalar4));
	}
	/* operator+ (scalar) */
	{
		constexpr ValueType scalar{ static_cast<ValueType>(2.0) };
		constexpr VectorType vector{ static_cast<ValueType>(13.0), static_cast<ValueType>(31.0), static_cast<ValueType>(15.0), static_cast<ValueType>(51.0) };
		VectorType operation{ vector + VectorType{ scalar, scalar, scalar, scalar } };

		TEST_ASSERT(operation == VectorType(vector.x + scalar, vector.y + scalar, vector.z + scalar, vector.w + scalar));
	}
	/* operator- (scalar) */
	{
		constexpr ValueType scalar{ static_cast<ValueType>(2.0) };
		constexpr VectorType vector{ static_cast<ValueType>(13.0), static_cast<ValueType>(31.0), static_cast<ValueType>(15.0), static_cast<ValueType>(51.0) };
		VectorType operation{ vector - VectorType{ scalar, scalar, scalar, scalar } };

		TEST_ASSERT(operation == VectorType(vector.x - scalar, vector.y - scalar, vector.z - scalar, vector.w - scalar));
	}
	/* operator* (scalar) */
	{
		constexpr ValueType scalar{ static_cast<ValueType>(2.0) };
		constexpr VectorType vector{ static_cast<ValueType>(13.0), static_cast<ValueType>(31.0), static_cast<ValueType>(15.0), static_cast<ValueType>(51.0) };
		VectorType operation{ vector * VectorType{ scalar, scalar, scalar, scalar } };

		TEST_ASSERT(operation == VectorType(vector.x * scalar, vector.y * scalar, vector.z * scalar, vector.w * scalar));
	}
	/* operator/ (scalar) */
	{
		constexpr ValueType scalar{ static_cast<ValueType>(2.0) };
		constexpr VectorType vector{ static_cast<ValueType>(13.0), static_cast<ValueType>(31.0), static_cast<ValueType>(15.0), static_cast<ValueType>(51.0) };
		VectorType operation{ vector / VectorType{ scalar, scalar, scalar, scalar } };

		TEST_ASSERT(operation == VectorType(vector.x / scalar, vector.y / scalar, vector.z / scalar, vector.w / scalar));
	}
	/* Conversion */
	{
		/* float -> double, double -> float */
		using OtherType = std::conditional<std::is_same_v<ValueType, float>, double, float>::type;
		static_assert(!std::is_same_v<OtherType, ValueType>);

		constexpr VectorType lhs{ static_cast<ValueType>(2), static_cast<ValueType>(4), static_cast<ValueType>(6), static_cast<ValueType>(8) };
		constexpr Vector<4, OtherType> rhs{ static_cast<OtherType>(2), static_cast<OtherType>(4),  static_cast<OtherType>(6), static_cast<ValueType>(8) };
		const VectorType casted{ static_cast<VectorType>(rhs) };
		
		const bool result{ casted == lhs };
		TEST_ASSERT(result);
	}
}

template<typename ValueType>
static void TestSwizzling() noexcept
{
	using namespace CinMath;
	using Vector2Type = Vector<2, ValueType>;
	using Vector3Type = Vector<3, ValueType>;
	using Vector4Type = Vector<4, ValueType>;
	/* Vector2 */
	{
		Vector2Type vector{ static_cast<ValueType>(1.0), static_cast<ValueType>(2.0) };
		TEST_ASSERT(vector.xy == Vector2Type(vector.x, vector.y))
	}

	/* Vector3 */
	{
		Vector3Type vector{ static_cast<ValueType>(1.0), static_cast<ValueType>(2.0), static_cast<ValueType>(3.0) };
		TEST_ASSERT(vector.xy == Vector2Type(vector.x, vector.y))
		TEST_ASSERT(vector.xz == Vector2Type(vector.x, vector.z))

		TEST_ASSERT(vector.yz == Vector2Type(vector.y, vector.z))

		TEST_ASSERT(vector.xyz == Vector3Type(vector.x, vector.y, vector.z))
	}
	/* Vector4 */
	{
		Vector4Type vector{ static_cast<ValueType>(1.0), static_cast<ValueType>(2.0), static_cast<ValueType>(3.0), static_cast<ValueType>(4.0) };
		TEST_ASSERT(vector.xy == Vector2Type(vector.x, vector.y))
		TEST_ASSERT(vector.xz == Vector2Type(vector.x, vector.z))
		TEST_ASSERT(vector.xw == Vector2Type(vector.x, vector.w))

		TEST_ASSERT(vector.yz == Vector2Type(vector.y, vector.z))
		TEST_ASSERT(vector.yw == Vector2Type(vector.y, vector.w))

		TEST_ASSERT(vector.zw == Vector2Type(vector.z, vector.w))

		TEST_ASSERT(vector.xyz == Vector3Type(vector.x, vector.y, vector.z))
		TEST_ASSERT(vector.yzw == Vector3Type(vector.y, vector.z, vector.w))

		TEST_ASSERT(vector.xyzw == Vector4Type(vector.x, vector.y, vector.z, vector.w))
	}
}

template<typename ValueType>
static void TestMatrix2x2() noexcept
{
	using namespace CinMath;
	using MatrixType = Matrix<2, 2, ValueType>;
	/* consteval constructors */
	{
		{
			constexpr MatrixType matrix;
			constexpr MatrixType expected { static_cast<ValueType>(0), static_cast<ValueType>(0), static_cast<ValueType>(0), static_cast<ValueType>(0) };
			TEST_ASSERT(matrix == expected);
		}
		/* Identity constructor */
		{
			constexpr MatrixType matrix(1.0f);
			constexpr MatrixType expected{ MatrixType::Identity() };
			TEST_ASSERT(matrix == expected);
		}
	}
	/* raw */
	{
		MatrixType matrix;
		TEST_ASSERT(reinterpret_cast<ValueType*>(std::addressof(matrix)) == matrix.operator ValueType * ());
		TEST_ASSERT(reinterpret_cast<ValueType*>(std::addressof(matrix)) == matrix.operator const ValueType * ());
	}
	/* [] operator */
	{
		/* const */
		{
			const MatrixType matrix{ static_cast<ValueType>(1), static_cast<ValueType>(2), static_cast<ValueType>(3), static_cast<ValueType>(4) };
			const ValueType value1{ matrix[0] }; TEST_ASSERT(value1 == static_cast<ValueType>(1));
			const ValueType value2{ matrix[1] }; TEST_ASSERT(value2 == static_cast<ValueType>(2));
			const ValueType value3{ matrix[2] }; TEST_ASSERT(value3 == static_cast<ValueType>(3));
			const ValueType value4{ matrix[3] }; TEST_ASSERT(value4 == static_cast<ValueType>(4));
		}
		/* non-const */
		{
			MatrixType matrix{ static_cast<ValueType>(1), static_cast<ValueType>(2), static_cast<ValueType>(3), static_cast<ValueType>(4) };
			ValueType& value1{ matrix[0] }; TEST_ASSERT(value1 == static_cast<ValueType>(1));
			ValueType& value2{ matrix[1] }; TEST_ASSERT(value2 == static_cast<ValueType>(2));
			ValueType& value3{ matrix[2] }; TEST_ASSERT(value3 == static_cast<ValueType>(3));
			ValueType& value4{ matrix[3] }; TEST_ASSERT(value4 == static_cast<ValueType>(4));
		}
	}
	/* == operator */
	{
		constexpr MatrixType lhs{ static_cast<ValueType>(1), static_cast<ValueType>(2), static_cast<ValueType>(3), static_cast<ValueType>(4) };
		constexpr MatrixType rhs{ static_cast<ValueType>(1), static_cast<ValueType>(2), static_cast<ValueType>(3), static_cast<ValueType>(4) };
		TEST_ASSERT(lhs == rhs);
	}
	/* != operator */
	{
		constexpr MatrixType lhs{ static_cast<ValueType>(1), static_cast<ValueType>(2), static_cast<ValueType>(3), static_cast<ValueType>(4) };
		
		for(size_t i{ 0U }; i < 4U; ++i)
		{
			MatrixType rhs{ lhs };
			rhs[i] = 999;

			TEST_ASSERT(lhs != rhs);
		}
	}
	/* conversion */
	{
		using OtherType = std::conditional<std::is_same_v<ValueType, float>, double, float>::type;
		static_assert(!std::is_same_v<OtherType, ValueType>);

		constexpr MatrixType matrix{ static_cast<ValueType>(1), static_cast<ValueType>(2), static_cast<ValueType>(3), static_cast<ValueType>(4) };
		constexpr Matrix<2, 2, OtherType> otherMatrix{ static_cast<OtherType>(1), static_cast<OtherType>(2), static_cast<OtherType>(3), static_cast<OtherType>(4) };

		const bool result{ matrix == static_cast<MatrixType>(otherMatrix) };
		TEST_ASSERT(result);
	}
	/* + operator */
	{
		constexpr MatrixType matrix{ static_cast<ValueType>(1), static_cast<ValueType>(2), static_cast<ValueType>(3), static_cast<ValueType>(4) };

		const bool result{ matrix == (+matrix) };
		TEST_ASSERT(result);
	}
	/* - operator */
	{
		constexpr MatrixType matrix{ static_cast<ValueType>(1), static_cast<ValueType>(2), static_cast<ValueType>(3), static_cast<ValueType>(4) };
		const bool result{ -matrix == MatrixType(static_cast<ValueType>(-1), static_cast<ValueType>(-2), static_cast<ValueType>(-3), static_cast<ValueType>(-4)) };

		TEST_ASSERT(result);
	}
	/* += operator */
	{
		 MatrixType matrix{ static_cast<ValueType>(1), static_cast<ValueType>(2), static_cast<ValueType>(3), static_cast<ValueType>(4) };
		 matrix += MatrixType{ static_cast<ValueType>(1), static_cast<ValueType>(2), static_cast<ValueType>(3), static_cast<ValueType>(4) };

		 const bool result{ matrix == MatrixType{ static_cast<ValueType>(1 + 1), static_cast<ValueType>(2 + 2), static_cast<ValueType>(3 + 3), static_cast<ValueType>(4 + 4) } };
		 TEST_ASSERT(result);
	}
	/* -= operator */
	{
		 MatrixType matrix{ static_cast<ValueType>(1), static_cast<ValueType>(2), static_cast<ValueType>(3), static_cast<ValueType>(4) };
		 matrix -= MatrixType{ static_cast<ValueType>(1), static_cast<ValueType>(2), static_cast<ValueType>(3), static_cast<ValueType>(4) };

		 const bool result{ matrix == MatrixType{ static_cast<ValueType>(1 - 1), static_cast<ValueType>(2 - 2), static_cast<ValueType>(3 - 3), static_cast<ValueType>(4 - 4) } };
		 TEST_ASSERT(result);
	}
	/* *= operator */
	{
		MatrixType matrix
		{ 
			static_cast<ValueType>(1), static_cast<ValueType>(2), 
			static_cast<ValueType>(3), static_cast<ValueType>(4) 
		};

		matrix *= MatrixType
		{ 
			static_cast<ValueType>(1), static_cast<ValueType>(2), 
			static_cast<ValueType>(3), static_cast<ValueType>(4) 
		};

		const bool result
		{ 
			matrix == MatrixType
			{ 
				static_cast<ValueType>(1 * 1 + 2 * 3), static_cast<ValueType>(1 * 2 + 2 * 4), 
				static_cast<ValueType>(3 * 1 + 4 * 3), static_cast<ValueType>(3 * 2 + 4 * 4) 
			} 
		};

		TEST_ASSERT(result);
	}
	/* += operator (scalar) */
	{
		MatrixType matrix
		{ 
			static_cast<ValueType>(1), static_cast<ValueType>(2), 
			static_cast<ValueType>(3), static_cast<ValueType>(4) 
		};

		matrix += static_cast<ValueType>(2);

		const bool result
		{
			matrix == MatrixType
			{
				static_cast<ValueType>(1 + 2), static_cast<ValueType>(2 + 2), 
				static_cast<ValueType>(3 + 2), static_cast<ValueType>(4 + 2) 
			}
		};

		TEST_ASSERT(result);
	}
	/* -= operator (scalar) */
	{
		MatrixType matrix
		{ 
			static_cast<ValueType>(1), static_cast<ValueType>(2), 
			static_cast<ValueType>(3), static_cast<ValueType>(4) 
		};

		matrix -= static_cast<ValueType>(2);

		const bool result
		{
			matrix == MatrixType
			{
				static_cast<ValueType>(1 - 2), static_cast<ValueType>(2 - 2), 
				static_cast<ValueType>(3 - 2), static_cast<ValueType>(4 - 2) 
			}
		};

		TEST_ASSERT(result);
	}
	/* *= operator (scalar) */
	{
		MatrixType matrix
		{ 
			static_cast<ValueType>(1), static_cast<ValueType>(2), 
			static_cast<ValueType>(3), static_cast<ValueType>(4) 
		};

		matrix *= static_cast<ValueType>(2);

		const bool result
		{
			matrix == MatrixType
			{
				static_cast<ValueType>(1 * 2), static_cast<ValueType>(2 * 2), 
				static_cast<ValueType>(3 * 2), static_cast<ValueType>(4 * 2) 
			}
		};

		TEST_ASSERT(result);
	}
	/* /= operator (scalar) */
	{
		MatrixType matrix
		{ 
			static_cast<ValueType>(1), static_cast<ValueType>(2), 
			static_cast<ValueType>(3), static_cast<ValueType>(4) 
		};

		matrix /= static_cast<ValueType>(2);

		const bool result
		{
			matrix == MatrixType
			{
				static_cast<ValueType>(1) / static_cast<ValueType>(2), static_cast<ValueType>(2) / static_cast<ValueType>(2), 
				static_cast<ValueType>(3) / static_cast<ValueType>(2), static_cast<ValueType>(4) / static_cast<ValueType>(2) 
			}
		};

		TEST_ASSERT(result);
	}
	/* + operator */
	{
		 MatrixType matrix{ static_cast<ValueType>(1), static_cast<ValueType>(2), static_cast<ValueType>(3), static_cast<ValueType>(4) };
		 const auto operation{ matrix + MatrixType{ static_cast<ValueType>(1), static_cast<ValueType>(2), static_cast<ValueType>(3), static_cast<ValueType>(4) } };

		 const auto result{ operation == MatrixType{ static_cast<ValueType>(1 + 1), static_cast<ValueType>(2 + 2), static_cast<ValueType>(3 + 3), static_cast<ValueType>(4 + 4) } };
		 TEST_ASSERT(result);
	}
	/* - operator */
	{
		 MatrixType matrix{ static_cast<ValueType>(1), static_cast<ValueType>(2), static_cast<ValueType>(3), static_cast<ValueType>(4) };
		 const auto operation{ matrix - MatrixType{ static_cast<ValueType>(1), static_cast<ValueType>(2), static_cast<ValueType>(3), static_cast<ValueType>(4) } };

		 const bool result{ operation == MatrixType{ static_cast<ValueType>(1 - 1), static_cast<ValueType>(2 - 2), static_cast<ValueType>(3 - 3), static_cast<ValueType>(4 - 4) } };
		 TEST_ASSERT(result);
	}
	/* *= operator */
	{
		MatrixType matrix
		{ 
			static_cast<ValueType>(1), static_cast<ValueType>(2), 
			static_cast<ValueType>(3), static_cast<ValueType>(4) 
		};

		const auto operation 
		{
			matrix * MatrixType
			{ 
				static_cast<ValueType>(1), static_cast<ValueType>(2), 
				static_cast<ValueType>(3), static_cast<ValueType>(4) 
			}
		};

		const bool result
		{ 
			operation == MatrixType
			{ 
				static_cast<ValueType>(1 * 1 + 2 * 3), static_cast<ValueType>(1 * 2 + 2 * 4), 
				static_cast<ValueType>(3 * 1 + 4 * 3), static_cast<ValueType>(3 * 2 + 4 * 4) 
			} 
		};

		TEST_ASSERT(result);
	}
	/* += operator (scalar) */
	{
		MatrixType matrix
		{ 
			static_cast<ValueType>(1), static_cast<ValueType>(2), 
			static_cast<ValueType>(3), static_cast<ValueType>(4) 
		};

		const auto operation 
		{
			matrix + static_cast<ValueType>(2)
		};

		const bool result
		{
			operation == MatrixType
			{
				static_cast<ValueType>(1 + 2), static_cast<ValueType>(2 + 2), 
				static_cast<ValueType>(3 + 2), static_cast<ValueType>(4 + 2) 
			}
		};

		TEST_ASSERT(result);
	}
	/* -= operator (scalar) */
	{
		MatrixType matrix
		{ 
			static_cast<ValueType>(1), static_cast<ValueType>(2), 
			static_cast<ValueType>(3), static_cast<ValueType>(4) 
		};

		const auto operation
		{
			matrix - static_cast<ValueType>(2)
		};

		const bool result
		{
			operation == MatrixType
			{
				static_cast<ValueType>(1 - 2), static_cast<ValueType>(2 - 2), 
				static_cast<ValueType>(3 - 2), static_cast<ValueType>(4 - 2) 
			}
		};

		TEST_ASSERT(result);
	}
	/* *= operator (scalar) */
	{
		MatrixType matrix
		{ 
			static_cast<ValueType>(1), static_cast<ValueType>(2), 
			static_cast<ValueType>(3), static_cast<ValueType>(4) 
		};

		const auto operation
		{ 
			matrix * static_cast<ValueType>(2)
		};

		const bool result
		{
			operation == MatrixType
			{
				static_cast<ValueType>(1 * 2), static_cast<ValueType>(2 * 2), 
				static_cast<ValueType>(3 * 2), static_cast<ValueType>(4 * 2) 
			}
		};

		TEST_ASSERT(result);
	}
	/* /= operator (scalar) */
	{
		MatrixType matrix
		{ 
			static_cast<ValueType>(1), static_cast<ValueType>(2), 
			static_cast<ValueType>(3), static_cast<ValueType>(4) 
		};

		const auto operation 
		{
			matrix / static_cast<ValueType>(2)
		};

		const bool result
		{
			operation == MatrixType
			{
				static_cast<ValueType>(1) / static_cast<ValueType>(2), static_cast<ValueType>(2) / static_cast<ValueType>(2), 
				static_cast<ValueType>(3) / static_cast<ValueType>(2), static_cast<ValueType>(4) / static_cast<ValueType>(2) 
			}
		};

		TEST_ASSERT(result);
	}
}

template<typename ValueType>
static void TestMatrix3x3() noexcept
{
	using namespace CinMath;
	using MatrixType = Matrix<3, 3, ValueType>;
	/* consteval constructors */
	{
		{
			constexpr MatrixType matrix;
			constexpr MatrixType expected
			{ 
				static_cast<ValueType>(0), static_cast<ValueType>(0), static_cast<ValueType>(0),
				static_cast<ValueType>(0), static_cast<ValueType>(0), static_cast<ValueType>(0),
				static_cast<ValueType>(0), static_cast<ValueType>(0), static_cast<ValueType>(0)
			};

			TEST_ASSERT(matrix == expected);
		}
		/* Identity constructor */
		{
			constexpr MatrixType matrix(1.0f);
			constexpr MatrixType expected{ MatrixType::Identity() };
			TEST_ASSERT(matrix == expected);
		}
	}
	/* raw */
	{
		MatrixType matrix;
		TEST_ASSERT(reinterpret_cast<ValueType*>(std::addressof(matrix)) == matrix.operator ValueType * ());
		TEST_ASSERT(reinterpret_cast<ValueType*>(std::addressof(matrix)) == matrix.operator const ValueType * ());
	}
	/* [] operator */
	{
		/* const */
		{
			const MatrixType matrix
			{ 
				static_cast<ValueType>(1), static_cast<ValueType>(2), static_cast<ValueType>(3), 
				static_cast<ValueType>(4), static_cast<ValueType>(5), static_cast<ValueType>(6),
				static_cast<ValueType>(7), static_cast<ValueType>(8),static_cast<ValueType>(9)
			};

			const ValueType value1{ matrix[0] }; TEST_ASSERT(value1 == static_cast<ValueType>(1));
			const ValueType value2{ matrix[1] }; TEST_ASSERT(value2 == static_cast<ValueType>(2));
			const ValueType value3{ matrix[2] }; TEST_ASSERT(value3 == static_cast<ValueType>(3));
			const ValueType value4{ matrix[3] }; TEST_ASSERT(value4 == static_cast<ValueType>(4));
			const ValueType value5{ matrix[4] }; TEST_ASSERT(value5 == static_cast<ValueType>(5));
			const ValueType value6{ matrix[5] }; TEST_ASSERT(value6 == static_cast<ValueType>(6));
			const ValueType value7{ matrix[6] }; TEST_ASSERT(value7 == static_cast<ValueType>(7));
			const ValueType value8{ matrix[7] }; TEST_ASSERT(value8 == static_cast<ValueType>(8));
			const ValueType value9{ matrix[8] }; TEST_ASSERT(value9 == static_cast<ValueType>(9));
		}
		/* non-const */
		{
			MatrixType matrix
			{ 
				static_cast<ValueType>(1), static_cast<ValueType>(2), static_cast<ValueType>(3), 
				static_cast<ValueType>(4), static_cast<ValueType>(5), static_cast<ValueType>(6),
				static_cast<ValueType>(7), static_cast<ValueType>(8),static_cast<ValueType>(9)
			};

			ValueType& value1{ matrix[0] }; TEST_ASSERT(value1 == static_cast<ValueType>(1));
			ValueType& value2{ matrix[1] }; TEST_ASSERT(value2 == static_cast<ValueType>(2));
			ValueType& value3{ matrix[2] }; TEST_ASSERT(value3 == static_cast<ValueType>(3));
			ValueType& value4{ matrix[3] }; TEST_ASSERT(value4 == static_cast<ValueType>(4));
			ValueType& value5{ matrix[4] }; TEST_ASSERT(value5 == static_cast<ValueType>(5));
			ValueType& value6{ matrix[5] }; TEST_ASSERT(value6 == static_cast<ValueType>(6));
			ValueType& value7{ matrix[6] }; TEST_ASSERT(value7 == static_cast<ValueType>(7));
			ValueType& value8{ matrix[7] }; TEST_ASSERT(value8 == static_cast<ValueType>(8));
			ValueType& value9{ matrix[8] }; TEST_ASSERT(value9 == static_cast<ValueType>(9));
		}
	}
	/* == operator */
	{
		constexpr MatrixType lhs
		{ 
			static_cast<ValueType>(1), static_cast<ValueType>(2), static_cast<ValueType>(3), 
			static_cast<ValueType>(4), static_cast<ValueType>(5), static_cast<ValueType>(6),
			static_cast<ValueType>(7), static_cast<ValueType>(8),static_cast<ValueType>(9)
		};

		constexpr MatrixType rhs
		{ 
			static_cast<ValueType>(1), static_cast<ValueType>(2), static_cast<ValueType>(3), 
			static_cast<ValueType>(4), static_cast<ValueType>(5), static_cast<ValueType>(6),
			static_cast<ValueType>(7), static_cast<ValueType>(8),static_cast<ValueType>(9)
		};

		TEST_ASSERT(lhs == rhs);
	}
	/* != operator */
	{
		constexpr MatrixType lhs
		{ 
			static_cast<ValueType>(1), static_cast<ValueType>(2), static_cast<ValueType>(3), 
			static_cast<ValueType>(4), static_cast<ValueType>(5), static_cast<ValueType>(6),
			static_cast<ValueType>(7), static_cast<ValueType>(8),static_cast<ValueType>(9)
		};

		for(size_t i{ 0U }; i < 9U; ++i)
		{
			MatrixType rhs{ lhs };
			rhs[i] = 999;
			
			TEST_ASSERT(lhs != rhs);
		}
	}
	/* conversion */
	{
		using OtherType = std::conditional<std::is_same_v<ValueType, float>, double, float>::type;
		static_assert(!std::is_same_v<OtherType, ValueType>);

		constexpr MatrixType matrix
		{ 
			static_cast<ValueType>(1), static_cast<ValueType>(2), static_cast<ValueType>(3), 
			static_cast<ValueType>(4), static_cast<ValueType>(5), static_cast<ValueType>(6),
			static_cast<ValueType>(7), static_cast<ValueType>(8),static_cast<ValueType>(9)
		};

		constexpr Matrix<3, 3, OtherType> otherMatrix
		{
			static_cast<OtherType>(1), static_cast<OtherType>(2), static_cast<OtherType>(3), 
			static_cast<OtherType>(4), static_cast<OtherType>(5), static_cast<OtherType>(6),
			static_cast<OtherType>(7), static_cast<OtherType>(8),static_cast<OtherType>(9)
		};

		const bool result{ matrix == static_cast<MatrixType>(otherMatrix) };
		TEST_ASSERT(result);
	}
	/* + operator */
	{
		constexpr MatrixType matrix
		{ 
			static_cast<ValueType>(1), static_cast<ValueType>(2), static_cast<ValueType>(3), 
			static_cast<ValueType>(4), static_cast<ValueType>(5), static_cast<ValueType>(6),
			static_cast<ValueType>(7), static_cast<ValueType>(8),static_cast<ValueType>(9)
		};

		const bool result{ matrix == (+matrix) };
		TEST_ASSERT(result);
	}
	/* - operator */
	{
		constexpr MatrixType matrix
		{ 
			static_cast<ValueType>(1), static_cast<ValueType>(2), static_cast<ValueType>(3), 
			static_cast<ValueType>(4), static_cast<ValueType>(5), static_cast<ValueType>(6),
			static_cast<ValueType>(7), static_cast<ValueType>(8),static_cast<ValueType>(9)
		};

		const bool result
		{ 
			-matrix == MatrixType
			{ 
				static_cast<ValueType>(-1), static_cast<ValueType>(-2), static_cast<ValueType>(-3), 
				static_cast<ValueType>(-4), static_cast<ValueType>(-5), static_cast<ValueType>(-6),
				static_cast<ValueType>(-7), static_cast<ValueType>(-8),static_cast<ValueType>(-9)
			} 
		};

		TEST_ASSERT(result);
	}
	/* += operator */
	{
		MatrixType matrix
		{ 
			static_cast<ValueType>(1), static_cast<ValueType>(2), static_cast<ValueType>(3), 
			static_cast<ValueType>(4), static_cast<ValueType>(5), static_cast<ValueType>(6),
			static_cast<ValueType>(7), static_cast<ValueType>(8),static_cast<ValueType>(9)
		};

		matrix += MatrixType
		{ 
			static_cast<ValueType>(1), static_cast<ValueType>(2), static_cast<ValueType>(3), 
			static_cast<ValueType>(4), static_cast<ValueType>(5), static_cast<ValueType>(6),
			static_cast<ValueType>(7), static_cast<ValueType>(8),static_cast<ValueType>(9)
		};

		const bool result
		{ 
			matrix == MatrixType
			{ 
				static_cast<ValueType>(1 + 1), static_cast<ValueType>(2 + 2), static_cast<ValueType>(3 + 3), 
				static_cast<ValueType>(4 + 4), static_cast<ValueType>(5 + 5), static_cast<ValueType>(6 + 6),
				static_cast<ValueType>(7 + 7), static_cast<ValueType>(8 + 8), static_cast<ValueType>(9 + 9)     
			} 
		};

		TEST_ASSERT(result);
	}
	/* -= operator */
	{
		MatrixType matrix
		{ 
			static_cast<ValueType>(1), static_cast<ValueType>(2), static_cast<ValueType>(3), 
			static_cast<ValueType>(4), static_cast<ValueType>(5), static_cast<ValueType>(6),
			static_cast<ValueType>(7), static_cast<ValueType>(8),static_cast<ValueType>(9)
		};

		matrix -= MatrixType
		{ 
			static_cast<ValueType>(1), static_cast<ValueType>(2), static_cast<ValueType>(3), 
			static_cast<ValueType>(4), static_cast<ValueType>(5), static_cast<ValueType>(6),
			static_cast<ValueType>(7), static_cast<ValueType>(8),static_cast<ValueType>(9)
		};

		const bool result
		{ 
			matrix == MatrixType
			{ 
				static_cast<ValueType>(1 - 1), static_cast<ValueType>(2 - 2), static_cast<ValueType>(3 - 3), 
				static_cast<ValueType>(4 - 4), static_cast<ValueType>(5 - 5), static_cast<ValueType>(6 - 6),
				static_cast<ValueType>(7 - 7), static_cast<ValueType>(8 - 8), static_cast<ValueType>(9 - 9)     
			} 
		};
		
		TEST_ASSERT(result);
	}
	/* *= operator */
	{
		MatrixType matrix
		{ 
			static_cast<ValueType>(1), static_cast<ValueType>(2), static_cast<ValueType>(3), 
			static_cast<ValueType>(4), static_cast<ValueType>(5), static_cast<ValueType>(6),
			static_cast<ValueType>(7), static_cast<ValueType>(8),static_cast<ValueType>(9)
		};

		matrix *= MatrixType
		{ 
			static_cast<ValueType>(1), static_cast<ValueType>(2), static_cast<ValueType>(3), 
			static_cast<ValueType>(4), static_cast<ValueType>(5), static_cast<ValueType>(6),
			static_cast<ValueType>(7), static_cast<ValueType>(8),static_cast<ValueType>(9)
		};

		const bool result
		{ 
			matrix == MatrixType
			{ 
				static_cast<ValueType>(1 * 1 + 2 * 4 + 3 * 7), static_cast<ValueType>(1 * 2 + 2 * 5 + 3 * 8), static_cast<ValueType>(1 * 3 + 2 * 6 + 3 * 9), 
				static_cast<ValueType>(4 * 1 + 5 * 4 + 6 * 7), static_cast<ValueType>(4 * 2 + 5 * 5 + 6 * 8), static_cast<ValueType>(4 * 3 + 5 * 6 + 6 * 9),
				static_cast<ValueType>(7 * 1 + 8 * 4 + 9 * 7), static_cast<ValueType>(7 * 2 + 8 * 5 + 9 * 8),static_cast<ValueType>(7 * 3 + 8 * 6 + 9 * 9)
			} 
		};

		TEST_ASSERT(result);
	}
	/* += operator (scalar) */
	{
		MatrixType matrix
		{ 
			static_cast<ValueType>(1), static_cast<ValueType>(2), static_cast<ValueType>(3), 
			static_cast<ValueType>(4), static_cast<ValueType>(5), static_cast<ValueType>(6),
			static_cast<ValueType>(7), static_cast<ValueType>(8),static_cast<ValueType>(9)
		};

		matrix += static_cast<ValueType>(2);

		const bool result
		{
			matrix == MatrixType
			{
				static_cast<ValueType>(1 + 2), static_cast<ValueType>(2 + 2), static_cast<ValueType>(3 + 2), 
				static_cast<ValueType>(4 + 2), static_cast<ValueType>(5 + 2), static_cast<ValueType>(6 + 2),
				static_cast<ValueType>(7 + 2), static_cast<ValueType>(8 + 2),static_cast<ValueType>(9 + 2)
			}
		};

		TEST_ASSERT(result);
	}
	/* -= operator (scalar) */
	{
		MatrixType matrix
		{ 
			static_cast<ValueType>(1), static_cast<ValueType>(2), static_cast<ValueType>(3), 
			static_cast<ValueType>(4), static_cast<ValueType>(5), static_cast<ValueType>(6),
			static_cast<ValueType>(7), static_cast<ValueType>(8),static_cast<ValueType>(9)
		};

		matrix -= static_cast<ValueType>(2);

		const bool result
		{
			matrix == MatrixType
			{
				static_cast<ValueType>(1 - 2), static_cast<ValueType>(2 - 2), static_cast<ValueType>(3 - 2), 
				static_cast<ValueType>(4 - 2), static_cast<ValueType>(5 - 2), static_cast<ValueType>(6 - 2),
				static_cast<ValueType>(7 - 2), static_cast<ValueType>(8 - 2),static_cast<ValueType>(9 - 2)
			}
		};

		TEST_ASSERT(result);
	}
	/* *= operator (scalar) */
	{
		MatrixType matrix
		{ 
			static_cast<ValueType>(1), static_cast<ValueType>(2), static_cast<ValueType>(3), 
			static_cast<ValueType>(4), static_cast<ValueType>(5), static_cast<ValueType>(6),
			static_cast<ValueType>(7), static_cast<ValueType>(8),static_cast<ValueType>(9)
		};

		matrix *= static_cast<ValueType>(2);

		const bool result
		{
			matrix == MatrixType
			{
				static_cast<ValueType>(1 * 2), static_cast<ValueType>(2 * 2), static_cast<ValueType>(3 * 2), 
				static_cast<ValueType>(4 * 2), static_cast<ValueType>(5 * 2), static_cast<ValueType>(6 * 2),
				static_cast<ValueType>(7 * 2), static_cast<ValueType>(8 * 2),static_cast<ValueType>(9 * 2)
			}
		};

		TEST_ASSERT(result);
	}
	/* /= operator (scalar) */
	{
		MatrixType matrix
		{ 
			static_cast<ValueType>(1), static_cast<ValueType>(2), static_cast<ValueType>(3), 
			static_cast<ValueType>(4), static_cast<ValueType>(5), static_cast<ValueType>(6),
			static_cast<ValueType>(7), static_cast<ValueType>(8),static_cast<ValueType>(9)
		};

		matrix /= static_cast<ValueType>(2);

		const bool result
		{
			matrix == MatrixType
			{
				static_cast<ValueType>(1) / static_cast<ValueType>(2), static_cast<ValueType>(2) / static_cast<ValueType>(2), static_cast<ValueType>(3) / static_cast<ValueType>(2), 
				static_cast<ValueType>(4) / static_cast<ValueType>(2), static_cast<ValueType>(5) / static_cast<ValueType>(2), static_cast<ValueType>(6) / static_cast<ValueType>(2),
				static_cast<ValueType>(7) / static_cast<ValueType>(2), static_cast<ValueType>(8) / static_cast<ValueType>(2), static_cast<ValueType>(9) / static_cast<ValueType>(2)
			}
		};

		TEST_ASSERT(result);
	}
	/* + operator */
	{
		MatrixType matrix
		{ 
			static_cast<ValueType>(1), static_cast<ValueType>(2), static_cast<ValueType>(3), 
			static_cast<ValueType>(4), static_cast<ValueType>(5), static_cast<ValueType>(6),
			static_cast<ValueType>(7), static_cast<ValueType>(8),static_cast<ValueType>(9)
		};

		const auto operation
		{ 
			matrix + MatrixType
			{
				static_cast<ValueType>(1), static_cast<ValueType>(2), static_cast<ValueType>(3), 
				static_cast<ValueType>(4), static_cast<ValueType>(5), static_cast<ValueType>(6),
				static_cast<ValueType>(7), static_cast<ValueType>(8),static_cast<ValueType>(9)
			} 
		};

		const bool result
		{ 
			operation == MatrixType
			{ 
				static_cast<ValueType>(1 + 1), static_cast<ValueType>(2 + 2), static_cast<ValueType>(3 + 3), 
				static_cast<ValueType>(4 + 4), static_cast<ValueType>(5 + 5), static_cast<ValueType>(6 + 6),
				static_cast<ValueType>(7 + 7), static_cast<ValueType>(8 + 8),static_cast<ValueType>(9 + 9)
			} 
		};

		TEST_ASSERT(result);
	}
	/* - operator */
	{
		MatrixType matrix
		{ 
			static_cast<ValueType>(1), static_cast<ValueType>(2), static_cast<ValueType>(3), 
			static_cast<ValueType>(4), static_cast<ValueType>(5), static_cast<ValueType>(6),
			static_cast<ValueType>(7), static_cast<ValueType>(8),static_cast<ValueType>(9)
		};

		const auto operation
		{ 
			matrix - MatrixType
			{
				static_cast<ValueType>(1), static_cast<ValueType>(2), static_cast<ValueType>(3), 
				static_cast<ValueType>(4), static_cast<ValueType>(5), static_cast<ValueType>(6),
				static_cast<ValueType>(7), static_cast<ValueType>(8),static_cast<ValueType>(9)
			} 
		};

		const bool result
		{ 
			operation == MatrixType
			{ 
				static_cast<ValueType>(1 - 1), static_cast<ValueType>(2 - 2), static_cast<ValueType>(3 - 3), 
				static_cast<ValueType>(4 - 4), static_cast<ValueType>(5 - 5), static_cast<ValueType>(6 - 6),
				static_cast<ValueType>(7 - 7), static_cast<ValueType>(8 - 8),static_cast<ValueType>(9 - 9)
			} 
		};

		TEST_ASSERT(result);
	}
	/* *= operator */
	{
		MatrixType matrix
		{ 
			static_cast<ValueType>(1), static_cast<ValueType>(2), static_cast<ValueType>(3), 
			static_cast<ValueType>(4), static_cast<ValueType>(5), static_cast<ValueType>(6),
			static_cast<ValueType>(7), static_cast<ValueType>(8),static_cast<ValueType>(9)
		};

		const auto operation
		{ 
			matrix * MatrixType
			{
				static_cast<ValueType>(1), static_cast<ValueType>(2), static_cast<ValueType>(3), 
				static_cast<ValueType>(4), static_cast<ValueType>(5), static_cast<ValueType>(6),
				static_cast<ValueType>(7), static_cast<ValueType>(8),static_cast<ValueType>(9)
			} 
		};

		const bool result
		{ 
			operation == MatrixType
			{ 
				static_cast<ValueType>(1 * 1 + 2 * 4 + 3 * 7), static_cast<ValueType>(1 * 2 + 2 * 5 + 3 * 8), static_cast<ValueType>(1 * 3 + 2 * 6 + 3 * 9), 
				static_cast<ValueType>(4 * 1 + 5 * 4 + 6 * 7), static_cast<ValueType>(4 * 2 + 5 * 5 + 6 * 8), static_cast<ValueType>(4 * 3 + 5 * 6 + 6 * 9),
				static_cast<ValueType>(7 * 1 + 8 * 4 + 9 * 7), static_cast<ValueType>(7 * 2 + 8 * 5 + 9 * 8),static_cast<ValueType>(7 * 3 + 8 * 6 + 9 * 9)
			} 
		};

		TEST_ASSERT(result);
	}
	/* += operator (scalar) */
	{
		MatrixType matrix
		{ 
			static_cast<ValueType>(1), static_cast<ValueType>(2), static_cast<ValueType>(3), 
			static_cast<ValueType>(4), static_cast<ValueType>(5), static_cast<ValueType>(6),
			static_cast<ValueType>(7), static_cast<ValueType>(8),static_cast<ValueType>(9)
		};

		matrix += static_cast<ValueType>(2);
		const bool result
		{
			matrix == MatrixType
			{
				static_cast<ValueType>(1 + 2), static_cast<ValueType>(2 + 2), static_cast<ValueType>(3 + 2), 
				static_cast<ValueType>(4 + 2), static_cast<ValueType>(5 + 2), static_cast<ValueType>(6 + 2),
				static_cast<ValueType>(7 + 2), static_cast<ValueType>(8 + 2),static_cast<ValueType>(9 + 2)
			}
		};

		TEST_ASSERT(result);
	}
	/* -= operator (scalar) */
	{
		MatrixType matrix
		{ 
			static_cast<ValueType>(1), static_cast<ValueType>(2), static_cast<ValueType>(3), 
			static_cast<ValueType>(4), static_cast<ValueType>(5), static_cast<ValueType>(6),
			static_cast<ValueType>(7), static_cast<ValueType>(8),static_cast<ValueType>(9)
		};

		matrix -= static_cast<ValueType>(2);
		const bool result
		{
			matrix == MatrixType
			{
				static_cast<ValueType>(1 - 2), static_cast<ValueType>(2 - 2), static_cast<ValueType>(3 - 2), 
				static_cast<ValueType>(4 - 2), static_cast<ValueType>(5 - 2), static_cast<ValueType>(6 - 2),
				static_cast<ValueType>(7 - 2), static_cast<ValueType>(8 - 2),static_cast<ValueType>(9 - 2)
			}
		};

		TEST_ASSERT(result);
	}
	/* *= operator (scalar) */
	{
		MatrixType matrix
		{ 
			static_cast<ValueType>(1), static_cast<ValueType>(2), static_cast<ValueType>(3), 
			static_cast<ValueType>(4), static_cast<ValueType>(5), static_cast<ValueType>(6),
			static_cast<ValueType>(7), static_cast<ValueType>(8),static_cast<ValueType>(9)
		};

		matrix *= static_cast<ValueType>(2);
		const bool result
		{
			matrix == MatrixType
			{
				static_cast<ValueType>(1 * 2), static_cast<ValueType>(2 * 2), static_cast<ValueType>(3 * 2), 
				static_cast<ValueType>(4 * 2), static_cast<ValueType>(5 * 2), static_cast<ValueType>(6 * 2),
				static_cast<ValueType>(7 * 2), static_cast<ValueType>(8 * 2),static_cast<ValueType>(9 * 2)
			}
		};

		TEST_ASSERT(result);
	}
	/* /= operator (scalar) */
	{
		MatrixType matrix
		{ 
			static_cast<ValueType>(1), static_cast<ValueType>(2), static_cast<ValueType>(3), 
			static_cast<ValueType>(4), static_cast<ValueType>(5), static_cast<ValueType>(6),
			static_cast<ValueType>(7), static_cast<ValueType>(8),static_cast<ValueType>(9)
		};

		matrix /= static_cast<ValueType>(2);
		const bool result
		{
			matrix == MatrixType
			{
				static_cast<ValueType>(1) / static_cast<ValueType>(2), static_cast<ValueType>(2) / static_cast<ValueType>(2), static_cast<ValueType>(3) / static_cast<ValueType>(2), 
				static_cast<ValueType>(4) / static_cast<ValueType>(2), static_cast<ValueType>(5) / static_cast<ValueType>(2), static_cast<ValueType>(6) / static_cast<ValueType>(2),
				static_cast<ValueType>(7) / static_cast<ValueType>(2), static_cast<ValueType>(8) / static_cast<ValueType>(2),static_cast<ValueType>(9) / static_cast<ValueType>(2)
			}
		};

		TEST_ASSERT(result);
	}
}

template<typename ValueType>
static void TestMatrix4x4() noexcept
{
	using namespace CinMath;
	using MatrixType = Matrix<4, 4, ValueType>;
	/* consteval constructors */
	{
		{
			constexpr MatrixType matrix;
			constexpr MatrixType expected
			{ 
				static_cast<ValueType>(0), static_cast<ValueType>(0), static_cast<ValueType>(0), static_cast<ValueType>(0), 
				static_cast<ValueType>(0), static_cast<ValueType>(0), static_cast<ValueType>(0), static_cast<ValueType>(0), 
				static_cast<ValueType>(0), static_cast<ValueType>(0), static_cast<ValueType>(0), static_cast<ValueType>(0), 
				static_cast<ValueType>(0), static_cast<ValueType>(0), static_cast<ValueType>(0), static_cast<ValueType>(0) 
			};

			TEST_ASSERT(matrix == expected);
		}
		/* Identity constructor */
		{
			constexpr MatrixType matrix(1.0f);
			constexpr MatrixType expected{ MatrixType::Identity() };
			TEST_ASSERT(matrix == expected);
		}
	}
	/* raw */
	{
		MatrixType matrix;
		TEST_ASSERT(reinterpret_cast<ValueType*>(std::addressof(matrix)) == matrix.operator ValueType * ());
		TEST_ASSERT(reinterpret_cast<ValueType*>(std::addressof(matrix)) == matrix.operator const ValueType * ());
	}
	/* [] operator */
	{
		/* const */
		{
			const MatrixType matrix
			{ 
				static_cast<ValueType>(1), static_cast<ValueType>(2), static_cast<ValueType>(3), static_cast<ValueType>(4), 
				static_cast<ValueType>(5), static_cast<ValueType>(6), static_cast<ValueType>(7), static_cast<ValueType>(8), 
				static_cast<ValueType>(9), static_cast<ValueType>(10), static_cast<ValueType>(11), static_cast<ValueType>(12), 
				static_cast<ValueType>(13), static_cast<ValueType>(14), static_cast<ValueType>(15), static_cast<ValueType>(16), 
			};

			const ValueType value1{ matrix[0] }; TEST_ASSERT(value1 == static_cast<ValueType>(1));
			const ValueType value2{ matrix[1] }; TEST_ASSERT(value2 == static_cast<ValueType>(2));
			const ValueType value3{ matrix[2] }; TEST_ASSERT(value3 == static_cast<ValueType>(3));
			const ValueType value4{ matrix[3] }; TEST_ASSERT(value4 == static_cast<ValueType>(4));
			const ValueType value5{ matrix[4] }; TEST_ASSERT(value5 == static_cast<ValueType>(5));
			const ValueType value6{ matrix[5] }; TEST_ASSERT(value6 == static_cast<ValueType>(6));
			const ValueType value7{ matrix[6] }; TEST_ASSERT(value7 == static_cast<ValueType>(7));
			const ValueType value8{ matrix[7] }; TEST_ASSERT(value8 == static_cast<ValueType>(8));
			const ValueType value9{ matrix[8] }; TEST_ASSERT(value9 == static_cast<ValueType>(9));
			const ValueType value10{ matrix[9] }; TEST_ASSERT(value10 == static_cast<ValueType>(10));
			const ValueType value11{ matrix[10] }; TEST_ASSERT(value11 == static_cast<ValueType>(11));
			const ValueType value12{ matrix[11] }; TEST_ASSERT(value12 == static_cast<ValueType>(12));
			const ValueType value13{ matrix[12] }; TEST_ASSERT(value13 == static_cast<ValueType>(13));
			const ValueType value14{ matrix[13] }; TEST_ASSERT(value14 == static_cast<ValueType>(14));
			const ValueType value15{ matrix[14] }; TEST_ASSERT(value15 == static_cast<ValueType>(15));
			const ValueType value16{ matrix[15] }; TEST_ASSERT(value16 == static_cast<ValueType>(16));
		}
		/* non-const */
		{
			MatrixType matrix
			{ 
				static_cast<ValueType>(1), static_cast<ValueType>(2), static_cast<ValueType>(3), static_cast<ValueType>(4), 
				static_cast<ValueType>(5), static_cast<ValueType>(6), static_cast<ValueType>(7), static_cast<ValueType>(8), 
				static_cast<ValueType>(9), static_cast<ValueType>(10), static_cast<ValueType>(11), static_cast<ValueType>(12), 
				static_cast<ValueType>(13), static_cast<ValueType>(14), static_cast<ValueType>(15), static_cast<ValueType>(16), 
			};

			ValueType& value1{ matrix[0] }; TEST_ASSERT(value1 == static_cast<ValueType>(1));
			ValueType& value2{ matrix[1] }; TEST_ASSERT(value2 == static_cast<ValueType>(2));
			ValueType& value3{ matrix[2] }; TEST_ASSERT(value3 == static_cast<ValueType>(3));
			ValueType& value4{ matrix[3] }; TEST_ASSERT(value4 == static_cast<ValueType>(4));
			ValueType& value5{ matrix[4] }; TEST_ASSERT(value5 == static_cast<ValueType>(5));
			ValueType& value6{ matrix[5] }; TEST_ASSERT(value6 == static_cast<ValueType>(6));
			ValueType& value7{ matrix[6] }; TEST_ASSERT(value7 == static_cast<ValueType>(7));
			ValueType& value8{ matrix[7] }; TEST_ASSERT(value8 == static_cast<ValueType>(8));
			ValueType& value9{ matrix[8] }; TEST_ASSERT(value9 == static_cast<ValueType>(9));
			ValueType& value10{ matrix[9] }; TEST_ASSERT(value10 == static_cast<ValueType>(10));
			ValueType& value11{ matrix[10] }; TEST_ASSERT(value11 == static_cast<ValueType>(11));
			ValueType& value12{ matrix[11] }; TEST_ASSERT(value12 == static_cast<ValueType>(12));
			ValueType& value13{ matrix[12] }; TEST_ASSERT(value13 == static_cast<ValueType>(13));
			ValueType& value14{ matrix[13] }; TEST_ASSERT(value14 == static_cast<ValueType>(14));
			ValueType& value15{ matrix[14] }; TEST_ASSERT(value15 == static_cast<ValueType>(15));
			ValueType& value16{ matrix[15] }; TEST_ASSERT(value16 == static_cast<ValueType>(16));
		}
	}
	/* == operator */
	{
		const MatrixType lhs
		{ 
			static_cast<ValueType>(1), static_cast<ValueType>(2), static_cast<ValueType>(3), static_cast<ValueType>(4), 
			static_cast<ValueType>(5), static_cast<ValueType>(6), static_cast<ValueType>(7), static_cast<ValueType>(8), 
			static_cast<ValueType>(9), static_cast<ValueType>(10), static_cast<ValueType>(11), static_cast<ValueType>(12), 
			static_cast<ValueType>(13), static_cast<ValueType>(14), static_cast<ValueType>(15), static_cast<ValueType>(16), 
		};

		const MatrixType rhs
		{ 
			static_cast<ValueType>(1), static_cast<ValueType>(2), static_cast<ValueType>(3), static_cast<ValueType>(4), 
			static_cast<ValueType>(5), static_cast<ValueType>(6), static_cast<ValueType>(7), static_cast<ValueType>(8), 
			static_cast<ValueType>(9), static_cast<ValueType>(10), static_cast<ValueType>(11), static_cast<ValueType>(12), 
			static_cast<ValueType>(13), static_cast<ValueType>(14), static_cast<ValueType>(15), static_cast<ValueType>(16), 
		};

		TEST_ASSERT(lhs == rhs);
	}
	/* != operator */
	{
		const MatrixType lhs
		{ 
			static_cast<ValueType>(1), static_cast<ValueType>(2), static_cast<ValueType>(3), static_cast<ValueType>(4), 
			static_cast<ValueType>(5), static_cast<ValueType>(6), static_cast<ValueType>(7), static_cast<ValueType>(8), 
			static_cast<ValueType>(9), static_cast<ValueType>(10), static_cast<ValueType>(11), static_cast<ValueType>(12), 
			static_cast<ValueType>(13), static_cast<ValueType>(14), static_cast<ValueType>(15), static_cast<ValueType>(16), 
		};

		for(size_t i{ 0U }; i < 16U; ++i)
		{
			MatrixType rhs{ lhs };
			rhs[i] = 999;
			
			TEST_ASSERT(lhs != rhs);
		}
	}
	/* conversion */
	{
		using OtherType = std::conditional<std::is_same_v<ValueType, float>, double, float>::type;
		static_assert(!std::is_same_v<OtherType, ValueType>);

		const MatrixType matrix
		{ 
			static_cast<ValueType>(1), static_cast<ValueType>(2), static_cast<ValueType>(3), static_cast<ValueType>(4), 
			static_cast<ValueType>(5), static_cast<ValueType>(6), static_cast<ValueType>(7), static_cast<ValueType>(8), 
			static_cast<ValueType>(9), static_cast<ValueType>(10), static_cast<ValueType>(11), static_cast<ValueType>(12), 
			static_cast<ValueType>(13), static_cast<ValueType>(14), static_cast<ValueType>(15), static_cast<ValueType>(16)
		};

		constexpr Matrix<4, 4, OtherType> otherMatrix
		{
			static_cast<ValueType>(1), static_cast<ValueType>(2), static_cast<ValueType>(3), static_cast<ValueType>(4), 
			static_cast<ValueType>(5), static_cast<ValueType>(6), static_cast<ValueType>(7), static_cast<ValueType>(8), 
			static_cast<ValueType>(9), static_cast<ValueType>(10), static_cast<ValueType>(11), static_cast<ValueType>(12), 
			static_cast<ValueType>(13), static_cast<ValueType>(14), static_cast<ValueType>(15), static_cast<ValueType>(16) 
		};

		const bool result{ matrix == static_cast<MatrixType>(otherMatrix) };
		TEST_ASSERT(result);
	}
	/* + operator */
	{
		constexpr MatrixType matrix
		{ 
			static_cast<ValueType>(1), static_cast<ValueType>(2), static_cast<ValueType>(3), static_cast<ValueType>(4), 
			static_cast<ValueType>(5), static_cast<ValueType>(6), static_cast<ValueType>(7), static_cast<ValueType>(8), 
			static_cast<ValueType>(9), static_cast<ValueType>(10), static_cast<ValueType>(11), static_cast<ValueType>(12), 
			static_cast<ValueType>(13), static_cast<ValueType>(14), static_cast<ValueType>(15), static_cast<ValueType>(16)
		};

		const bool result{ matrix == (+matrix) };
		TEST_ASSERT(result);
	}
	/* - operator */
	{
		constexpr MatrixType matrix
		{ 
			static_cast<ValueType>(1), static_cast<ValueType>(2), static_cast<ValueType>(3), static_cast<ValueType>(4), 
			static_cast<ValueType>(5), static_cast<ValueType>(6), static_cast<ValueType>(7), static_cast<ValueType>(8), 
			static_cast<ValueType>(9), static_cast<ValueType>(10), static_cast<ValueType>(11), static_cast<ValueType>(12), 
			static_cast<ValueType>(13), static_cast<ValueType>(14), static_cast<ValueType>(15), static_cast<ValueType>(16) 
		};

		const bool result
		{ 
			-matrix == MatrixType
			{ 
				static_cast<ValueType>(-1), static_cast<ValueType>(-2), static_cast<ValueType>(-3), static_cast<ValueType>(-4), 
				static_cast<ValueType>(-5), static_cast<ValueType>(-6), static_cast<ValueType>(-7), static_cast<ValueType>(-8), 
				static_cast<ValueType>(-9), static_cast<ValueType>(-10), static_cast<ValueType>(-11), static_cast<ValueType>(-12), 
				static_cast<ValueType>(-13), static_cast<ValueType>(-14), static_cast<ValueType>(-15), static_cast<ValueType>(-16)
			} 
		};

		TEST_ASSERT(result);
	}
	/* += operator */
	{
		MatrixType matrix
		{ 
			static_cast<ValueType>(1), static_cast<ValueType>(2), static_cast<ValueType>(3), static_cast<ValueType>(4), 
			static_cast<ValueType>(5), static_cast<ValueType>(6), static_cast<ValueType>(7), static_cast<ValueType>(8), 
			static_cast<ValueType>(9), static_cast<ValueType>(10), static_cast<ValueType>(11), static_cast<ValueType>(12), 
			static_cast<ValueType>(13), static_cast<ValueType>(14), static_cast<ValueType>(15), static_cast<ValueType>(16) 
		};

		matrix += MatrixType
		{ 
			static_cast<ValueType>(1), static_cast<ValueType>(2), static_cast<ValueType>(3), static_cast<ValueType>(4), 
			static_cast<ValueType>(5), static_cast<ValueType>(6), static_cast<ValueType>(7), static_cast<ValueType>(8), 
			static_cast<ValueType>(9), static_cast<ValueType>(10), static_cast<ValueType>(11), static_cast<ValueType>(12), 
			static_cast<ValueType>(13), static_cast<ValueType>(14), static_cast<ValueType>(15), static_cast<ValueType>(16)
		};

		const bool result
		{ 
			matrix == MatrixType
			{ 
				static_cast<ValueType>(1 + 1), static_cast<ValueType>(2 + 2), static_cast<ValueType>(3 + 3), static_cast<ValueType>(4 + 4), 
				static_cast<ValueType>(5 + 5), static_cast<ValueType>(6 + 6), static_cast<ValueType>(7 + 7), static_cast<ValueType>(8 + 8), 
				static_cast<ValueType>(9 + 9), static_cast<ValueType>(10 + 10), static_cast<ValueType>(11 + 11), static_cast<ValueType>(12 + 12), 
				static_cast<ValueType>(13 + 13), static_cast<ValueType>(14 + 14), static_cast<ValueType>(15 + 15), static_cast<ValueType>(16 + 16), 
			} 
		};

		TEST_ASSERT(result);
	}
	/* -= operator */
	{
		MatrixType matrix
		{ 
			static_cast<ValueType>(1), static_cast<ValueType>(2), static_cast<ValueType>(3), static_cast<ValueType>(4), 
			static_cast<ValueType>(5), static_cast<ValueType>(6), static_cast<ValueType>(7), static_cast<ValueType>(8), 
			static_cast<ValueType>(9), static_cast<ValueType>(10), static_cast<ValueType>(11), static_cast<ValueType>(12), 
			static_cast<ValueType>(13), static_cast<ValueType>(14), static_cast<ValueType>(15), static_cast<ValueType>(16)
		};

		matrix -= MatrixType
		{ 
			static_cast<ValueType>(1), static_cast<ValueType>(2), static_cast<ValueType>(3), static_cast<ValueType>(4), 
			static_cast<ValueType>(5), static_cast<ValueType>(6), static_cast<ValueType>(7), static_cast<ValueType>(8), 
			static_cast<ValueType>(9), static_cast<ValueType>(10), static_cast<ValueType>(11), static_cast<ValueType>(12), 
			static_cast<ValueType>(13), static_cast<ValueType>(14), static_cast<ValueType>(15), static_cast<ValueType>(16)
		};

		const bool result
		{ 
			matrix == MatrixType
			{ 
				static_cast<ValueType>(1 - 1), static_cast<ValueType>(2 - 2), static_cast<ValueType>(3 - 3), static_cast<ValueType>(4 - 4), 
				static_cast<ValueType>(5 - 5), static_cast<ValueType>(6 - 6), static_cast<ValueType>(7 - 7), static_cast<ValueType>(8 - 8), 
				static_cast<ValueType>(9 - 9), static_cast<ValueType>(10 - 10), static_cast<ValueType>(11 - 11), static_cast<ValueType>(12 - 12), 
				static_cast<ValueType>(13 - 13), static_cast<ValueType>(14 - 14), static_cast<ValueType>(15 - 15), static_cast<ValueType>(16 - 16)
			} 
		};
		
		TEST_ASSERT(result);
	}
	/* *= operator */
	{
		MatrixType matrix
		{ 
			static_cast<ValueType>(1), static_cast<ValueType>(2), static_cast<ValueType>(3), static_cast<ValueType>(4), 
			static_cast<ValueType>(5), static_cast<ValueType>(6), static_cast<ValueType>(7), static_cast<ValueType>(8), 
			static_cast<ValueType>(9), static_cast<ValueType>(10), static_cast<ValueType>(11), static_cast<ValueType>(12), 
			static_cast<ValueType>(13), static_cast<ValueType>(14), static_cast<ValueType>(15), static_cast<ValueType>(16)
		};

		matrix *= MatrixType
		{ 
			static_cast<ValueType>(1), static_cast<ValueType>(2), static_cast<ValueType>(3), static_cast<ValueType>(4), 
			static_cast<ValueType>(5), static_cast<ValueType>(6), static_cast<ValueType>(7), static_cast<ValueType>(8), 
			static_cast<ValueType>(9), static_cast<ValueType>(10), static_cast<ValueType>(11), static_cast<ValueType>(12), 
			static_cast<ValueType>(13), static_cast<ValueType>(14), static_cast<ValueType>(15), static_cast<ValueType>(16)
		};

		const bool result
		{ 
			matrix == MatrixType
			{ 
				static_cast<ValueType>(1 * 1 + 2 * 5 + 3 * 9 + 4 * 13), static_cast<ValueType>(1 * 2 + 2 * 6 + 3 * 10 + 4 * 14), static_cast<ValueType>(1 * 3 + 2 * 7 + 3 * 11 + 4 * 15), static_cast<ValueType>(1 * 4 + 2 * 8 + 3 * 12 + 4 * 16),
				static_cast<ValueType>(5 * 1 + 6 * 5 + 7 * 9 + 8 * 13), static_cast<ValueType>(5 * 2 + 6 * 6 + 7 * 10 + 8 * 14), static_cast<ValueType>(5 * 3 + 6 * 7 + 7 * 11 + 8 * 15), static_cast<ValueType>(5 * 4 + 6 * 8 + 7 * 12 + 8 * 16),
				static_cast<ValueType>(9 * 1 + 10 * 5 + 11 * 9 + 12 * 13), static_cast<ValueType>(9 * 2 + 10 * 6 + 11 * 10 + 12 * 14), static_cast<ValueType>(9 * 3 + 10 * 7 + 11 * 11 + 12 * 15), static_cast<ValueType>(9 * 4 + 10 * 8 + 11 * 12 + 12 * 16),
				static_cast<ValueType>(13 * 1 + 14 * 5 + 15 * 9 + 16 * 13), static_cast<ValueType>(13 * 2 + 14 * 6 + 15 * 10 + 16 * 14), static_cast<ValueType>(13 * 3 + 14 * 7 + 15 * 11 + 16 * 15), static_cast<ValueType>(13 * 4 + 14 * 8 + 15 * 12 + 16 * 16)
			} 
		};

		TEST_ASSERT(result);
	}
	/* += operator (scalar) */
	{
		MatrixType matrix
		{ 
			static_cast<ValueType>(1), static_cast<ValueType>(2), static_cast<ValueType>(3), static_cast<ValueType>(4), 
			static_cast<ValueType>(5), static_cast<ValueType>(6), static_cast<ValueType>(7), static_cast<ValueType>(8), 
			static_cast<ValueType>(9), static_cast<ValueType>(10), static_cast<ValueType>(11), static_cast<ValueType>(12), 
			static_cast<ValueType>(13), static_cast<ValueType>(14), static_cast<ValueType>(15), static_cast<ValueType>(16)
		};

		matrix += static_cast<ValueType>(2);

		const bool result
		{
			matrix == MatrixType
			{
				static_cast<ValueType>(1 + 2), static_cast<ValueType>(2 + 2), static_cast<ValueType>(3 + 2), static_cast<ValueType>(4 + 2), 
				static_cast<ValueType>(5 + 2), static_cast<ValueType>(6 + 2), static_cast<ValueType>(7 + 2), static_cast<ValueType>(8 + 2), 
				static_cast<ValueType>(9 + 2), static_cast<ValueType>(10 + 2), static_cast<ValueType>(11 + 2), static_cast<ValueType>(12 + 2), 
				static_cast<ValueType>(13 + 2), static_cast<ValueType>(14 + 2), static_cast<ValueType>(15 + 2), static_cast<ValueType>(16 + 2)
			}
		};

		TEST_ASSERT(result);
	}
	/* -= operator (scalar) */
	{
		MatrixType matrix
		{ 
			static_cast<ValueType>(1), static_cast<ValueType>(2), static_cast<ValueType>(3), static_cast<ValueType>(4), 
			static_cast<ValueType>(5), static_cast<ValueType>(6), static_cast<ValueType>(7), static_cast<ValueType>(8), 
			static_cast<ValueType>(9), static_cast<ValueType>(10), static_cast<ValueType>(11), static_cast<ValueType>(12), 
			static_cast<ValueType>(13), static_cast<ValueType>(14), static_cast<ValueType>(15), static_cast<ValueType>(16)
		};

		matrix -= static_cast<ValueType>(2);

		const bool result
		{
			matrix == MatrixType
			{
				static_cast<ValueType>(1 - 2), static_cast<ValueType>(2 - 2), static_cast<ValueType>(3 - 2), static_cast<ValueType>(4 - 2), 
				static_cast<ValueType>(5 - 2), static_cast<ValueType>(6 - 2), static_cast<ValueType>(7 - 2), static_cast<ValueType>(8 - 2), 
				static_cast<ValueType>(9 - 2), static_cast<ValueType>(10 - 2), static_cast<ValueType>(11 - 2), static_cast<ValueType>(12 - 2), 
				static_cast<ValueType>(13 - 2), static_cast<ValueType>(14 - 2), static_cast<ValueType>(15 - 2), static_cast<ValueType>(16 - 2)
			}
		};

		TEST_ASSERT(result);
	}
	/* *= operator (scalar) */
	{
		MatrixType matrix
		{ 
			static_cast<ValueType>(1), static_cast<ValueType>(2), static_cast<ValueType>(3), static_cast<ValueType>(4), 
			static_cast<ValueType>(5), static_cast<ValueType>(6), static_cast<ValueType>(7), static_cast<ValueType>(8), 
			static_cast<ValueType>(9), static_cast<ValueType>(10), static_cast<ValueType>(11), static_cast<ValueType>(12), 
			static_cast<ValueType>(13), static_cast<ValueType>(14), static_cast<ValueType>(15), static_cast<ValueType>(16)
		};

		matrix *= static_cast<ValueType>(2);

		const bool result
		{
			matrix == MatrixType
			{
				static_cast<ValueType>(1 * 2), static_cast<ValueType>(2 * 2), static_cast<ValueType>(3 * 2), static_cast<ValueType>(4 * 2), 
				static_cast<ValueType>(5 * 2), static_cast<ValueType>(6 * 2), static_cast<ValueType>(7 * 2), static_cast<ValueType>(8 * 2), 
				static_cast<ValueType>(9 * 2), static_cast<ValueType>(10 * 2), static_cast<ValueType>(11 * 2), static_cast<ValueType>(12 * 2), 
				static_cast<ValueType>(13 * 2), static_cast<ValueType>(14 * 2), static_cast<ValueType>(15 * 2), static_cast<ValueType>(16 * 2)
			}
		};

		TEST_ASSERT(result);
	}
	/* /= operator (scalar) */
	{
		MatrixType matrix
		{ 
			static_cast<ValueType>(1), static_cast<ValueType>(2), static_cast<ValueType>(3), static_cast<ValueType>(4), 
			static_cast<ValueType>(5), static_cast<ValueType>(6), static_cast<ValueType>(7), static_cast<ValueType>(8), 
			static_cast<ValueType>(9), static_cast<ValueType>(10), static_cast<ValueType>(11), static_cast<ValueType>(12), 
			static_cast<ValueType>(13), static_cast<ValueType>(14), static_cast<ValueType>(15), static_cast<ValueType>(16)
		};

		matrix *= static_cast<ValueType>(2);

		const bool result
		{
			matrix == MatrixType
			{
				static_cast<ValueType>(1 * 2), static_cast<ValueType>(2 * 2), static_cast<ValueType>(3 * 2), static_cast<ValueType>(4 * 2), 
				static_cast<ValueType>(5 * 2), static_cast<ValueType>(6 * 2), static_cast<ValueType>(7 * 2), static_cast<ValueType>(8 * 2), 
				static_cast<ValueType>(9 * 2), static_cast<ValueType>(10 * 2), static_cast<ValueType>(11 * 2), static_cast<ValueType>(12 * 2), 
				static_cast<ValueType>(13 * 2), static_cast<ValueType>(14 * 2), static_cast<ValueType>(15 * 2), static_cast<ValueType>(16 * 2)
			}
		};

		TEST_ASSERT(result);
	}
	/* + operator */
	{
		MatrixType matrix
		{ 
			static_cast<ValueType>(1), static_cast<ValueType>(2), static_cast<ValueType>(3), static_cast<ValueType>(4), 
			static_cast<ValueType>(5), static_cast<ValueType>(6), static_cast<ValueType>(7), static_cast<ValueType>(8), 
			static_cast<ValueType>(9), static_cast<ValueType>(10), static_cast<ValueType>(11), static_cast<ValueType>(12), 
			static_cast<ValueType>(13), static_cast<ValueType>(14), static_cast<ValueType>(15), static_cast<ValueType>(16)
		};

		const auto operation
		{ 
			matrix + MatrixType
			{
				static_cast<ValueType>(1), static_cast<ValueType>(2), static_cast<ValueType>(3), static_cast<ValueType>(4), 
				static_cast<ValueType>(5), static_cast<ValueType>(6), static_cast<ValueType>(7), static_cast<ValueType>(8), 
				static_cast<ValueType>(9), static_cast<ValueType>(10), static_cast<ValueType>(11), static_cast<ValueType>(12), 
				static_cast<ValueType>(13), static_cast<ValueType>(14), static_cast<ValueType>(15), static_cast<ValueType>(16)
			} 
		};

		const bool result
		{ 
			operation == MatrixType
			{ 
				static_cast<ValueType>(1 + 1), static_cast<ValueType>(2 + 2), static_cast<ValueType>(3 + 3), static_cast<ValueType>(4 + 4), 
				static_cast<ValueType>(5 + 5), static_cast<ValueType>(6 + 6), static_cast<ValueType>(7 + 7), static_cast<ValueType>(8 + 8), 
				static_cast<ValueType>(9 + 9), static_cast<ValueType>(10 + 10), static_cast<ValueType>(11 + 11), static_cast<ValueType>(12 + 12), 
				static_cast<ValueType>(13 + 13), static_cast<ValueType>(14 + 14), static_cast<ValueType>(15 + 15), static_cast<ValueType>(16 + 16)
			} 
		};

		TEST_ASSERT(result);
	}
	/* - operator */
	{
		MatrixType matrix
		{ 
			static_cast<ValueType>(1), static_cast<ValueType>(2), static_cast<ValueType>(3), static_cast<ValueType>(4), 
			static_cast<ValueType>(5), static_cast<ValueType>(6), static_cast<ValueType>(7), static_cast<ValueType>(8), 
			static_cast<ValueType>(9), static_cast<ValueType>(10), static_cast<ValueType>(11), static_cast<ValueType>(12), 
			static_cast<ValueType>(13), static_cast<ValueType>(14), static_cast<ValueType>(15), static_cast<ValueType>(16)
		};

		const auto operation
		{ 
			matrix - MatrixType
			{
				static_cast<ValueType>(1), static_cast<ValueType>(2), static_cast<ValueType>(3), static_cast<ValueType>(4), 
				static_cast<ValueType>(5), static_cast<ValueType>(6), static_cast<ValueType>(7), static_cast<ValueType>(8), 
				static_cast<ValueType>(9), static_cast<ValueType>(10), static_cast<ValueType>(11), static_cast<ValueType>(12), 
				static_cast<ValueType>(13), static_cast<ValueType>(14), static_cast<ValueType>(15), static_cast<ValueType>(16)
			} 
		};

		const bool result
		{ 
			operation == MatrixType
			{ 
				static_cast<ValueType>(1 - 1), static_cast<ValueType>(2 - 2), static_cast<ValueType>(3 - 3), static_cast<ValueType>(4 - 4), 
				static_cast<ValueType>(5 - 5), static_cast<ValueType>(6 - 6), static_cast<ValueType>(7 - 7), static_cast<ValueType>(8 - 8), 
				static_cast<ValueType>(9 - 9), static_cast<ValueType>(10 - 10), static_cast<ValueType>(11 - 11), static_cast<ValueType>(12 - 12), 
				static_cast<ValueType>(13 - 13), static_cast<ValueType>(14 - 14), static_cast<ValueType>(15 - 15), static_cast<ValueType>(16 - 16)
			} 
		};

		TEST_ASSERT(result);
	}
	/* *= operator */
	{
		MatrixType matrix
		{ 
			static_cast<ValueType>(1), static_cast<ValueType>(2), static_cast<ValueType>(3), static_cast<ValueType>(4), 
			static_cast<ValueType>(5), static_cast<ValueType>(6), static_cast<ValueType>(7), static_cast<ValueType>(8), 
			static_cast<ValueType>(9), static_cast<ValueType>(10), static_cast<ValueType>(11), static_cast<ValueType>(12), 
			static_cast<ValueType>(13), static_cast<ValueType>(14), static_cast<ValueType>(15), static_cast<ValueType>(16)
		};

		matrix *= MatrixType
		{
			static_cast<ValueType>(1), static_cast<ValueType>(2), static_cast<ValueType>(3), static_cast<ValueType>(4), 
			static_cast<ValueType>(5), static_cast<ValueType>(6), static_cast<ValueType>(7), static_cast<ValueType>(8), 
			static_cast<ValueType>(9), static_cast<ValueType>(10), static_cast<ValueType>(11), static_cast<ValueType>(12), 
			static_cast<ValueType>(13), static_cast<ValueType>(14), static_cast<ValueType>(15), static_cast<ValueType>(16)
		};

		const bool result
		{ 
			matrix == MatrixType
			{ 
				static_cast<ValueType>(1 * 1 + 2 * 5 + 3 * 9 + 4 * 13), static_cast<ValueType>(1 * 2 + 2 * 6 + 3 * 10 + 4 * 14), static_cast<ValueType>(1 * 3 + 2 * 7 + 3 * 11 + 4 * 15), static_cast<ValueType>(1 * 4 + 2 * 8 + 3 * 12 + 4 * 16),
				static_cast<ValueType>(5 * 1 + 6 * 5 + 7 * 9 + 8 * 13), static_cast<ValueType>(5 * 2 + 6 * 6 + 7 * 10 + 8 * 14), static_cast<ValueType>(5 * 3 + 6 * 7 + 7 * 11 + 8 * 15), static_cast<ValueType>(5 * 4 + 6 * 8 + 7 * 12 + 8 * 16),
				static_cast<ValueType>(9 * 1 + 10 * 5 + 11 * 9 + 12 * 13), static_cast<ValueType>(9 * 2 + 10 * 6 + 11 * 10 + 12 * 14), static_cast<ValueType>(9 * 3 + 10 * 7 + 11 * 11 + 12 * 15), static_cast<ValueType>(9 * 4 + 10 * 8 + 11 * 12 + 12 * 16),
				static_cast<ValueType>(13 * 1 + 14 * 5 + 15 * 9 + 16 * 13), static_cast<ValueType>(13 * 2 + 14 * 6 + 15 * 10 + 16 * 14), static_cast<ValueType>(13 * 3 + 14 * 7 + 15 * 11 + 16 * 15), static_cast<ValueType>(13 * 4 + 14 * 8 + 15 * 12 + 16 * 16)
			} 
		};

		TEST_ASSERT(result);
	}
	/* += operator (scalar) */
	{
		MatrixType matrix
		{ 
			static_cast<ValueType>(1), static_cast<ValueType>(2), static_cast<ValueType>(3), static_cast<ValueType>(4), 
			static_cast<ValueType>(5), static_cast<ValueType>(6), static_cast<ValueType>(7), static_cast<ValueType>(8), 
			static_cast<ValueType>(9), static_cast<ValueType>(10), static_cast<ValueType>(11), static_cast<ValueType>(12), 
			static_cast<ValueType>(13), static_cast<ValueType>(14), static_cast<ValueType>(15), static_cast<ValueType>(16)
		};

		matrix += static_cast<ValueType>(2);

		const bool result
		{ 
			matrix == MatrixType
			{ 
				static_cast<ValueType>(1 + 2), static_cast<ValueType>(2 + 2), static_cast<ValueType>(3 + 2), static_cast<ValueType>(4 + 2),
				static_cast<ValueType>(5 + 2), static_cast<ValueType>(6 + 2), static_cast<ValueType>(7 + 2), static_cast<ValueType>(8 + 2),
				static_cast<ValueType>(9 + 2), static_cast<ValueType>(10 + 2), static_cast<ValueType>(11 + 2), static_cast<ValueType>(12 + 2),
				static_cast<ValueType>(13 + 2), static_cast<ValueType>(14 + 2), static_cast<ValueType>(15 + 2), static_cast<ValueType>(16 + 2)
			} 
		};

		TEST_ASSERT(result);
	}
	/* -= operator (scalar) */
	{
		MatrixType matrix
		{ 
			static_cast<ValueType>(1), static_cast<ValueType>(2), static_cast<ValueType>(3), static_cast<ValueType>(4), 
			static_cast<ValueType>(5), static_cast<ValueType>(6), static_cast<ValueType>(7), static_cast<ValueType>(8), 
			static_cast<ValueType>(9), static_cast<ValueType>(10), static_cast<ValueType>(11), static_cast<ValueType>(12), 
			static_cast<ValueType>(13), static_cast<ValueType>(14), static_cast<ValueType>(15), static_cast<ValueType>(16)
		};

		matrix -= static_cast<ValueType>(2);

		const bool result
		{ 
			matrix == MatrixType
			{ 
				static_cast<ValueType>(1 - 2), static_cast<ValueType>(2 - 2), static_cast<ValueType>(3 - 2), static_cast<ValueType>(4 - 2),
				static_cast<ValueType>(5 - 2), static_cast<ValueType>(6 - 2), static_cast<ValueType>(7 - 2), static_cast<ValueType>(8 - 2),
				static_cast<ValueType>(9 - 2), static_cast<ValueType>(10 - 2), static_cast<ValueType>(11 - 2), static_cast<ValueType>(12 - 2),
				static_cast<ValueType>(13 - 2), static_cast<ValueType>(14 - 2), static_cast<ValueType>(15 - 2), static_cast<ValueType>(16 - 2)
			} 
		};

		TEST_ASSERT(result);
	}
	/* *= operator (scalar) */
	{
		MatrixType matrix
		{ 
			static_cast<ValueType>(1), static_cast<ValueType>(2), static_cast<ValueType>(3), static_cast<ValueType>(4), 
			static_cast<ValueType>(5), static_cast<ValueType>(6), static_cast<ValueType>(7), static_cast<ValueType>(8), 
			static_cast<ValueType>(9), static_cast<ValueType>(10), static_cast<ValueType>(11), static_cast<ValueType>(12), 
			static_cast<ValueType>(13), static_cast<ValueType>(14), static_cast<ValueType>(15), static_cast<ValueType>(16)
		};

		matrix *= static_cast<ValueType>(2);
		const bool result
		{ 
			matrix == MatrixType
			{ 
				static_cast<ValueType>(1 * 2), static_cast<ValueType>(2 * 2), static_cast<ValueType>(3 * 2), static_cast<ValueType>(4 * 2),
				static_cast<ValueType>(5 * 2), static_cast<ValueType>(6 * 2), static_cast<ValueType>(7 * 2), static_cast<ValueType>(8 * 2),
				static_cast<ValueType>(9 * 2), static_cast<ValueType>(10 * 2), static_cast<ValueType>(11 * 2), static_cast<ValueType>(12 * 2),
				static_cast<ValueType>(13 * 2), static_cast<ValueType>(14 * 2), static_cast<ValueType>(15 * 2), static_cast<ValueType>(16 * 2)
			} 
		};

		TEST_ASSERT(result);
	}
	/* /= operator (scalar) */
	{
		MatrixType matrix
		{ 
			static_cast<ValueType>(1), static_cast<ValueType>(2), static_cast<ValueType>(3), static_cast<ValueType>(4), 
			static_cast<ValueType>(5), static_cast<ValueType>(6), static_cast<ValueType>(7), static_cast<ValueType>(8), 
			static_cast<ValueType>(9), static_cast<ValueType>(10), static_cast<ValueType>(11), static_cast<ValueType>(12), 
			static_cast<ValueType>(13), static_cast<ValueType>(14), static_cast<ValueType>(15), static_cast<ValueType>(16)
		};

		matrix /= static_cast<ValueType>(2);
		const bool result
		{ 
			matrix == MatrixType
			{ 
				static_cast<ValueType>(1) / static_cast<ValueType>(2), static_cast<ValueType>(2) / static_cast<ValueType>(2), static_cast<ValueType>(3) / static_cast<ValueType>(2), static_cast<ValueType>(4) /  static_cast<ValueType>(2),
				static_cast<ValueType>(5) / static_cast<ValueType>(2), static_cast<ValueType>(6) / static_cast<ValueType>(2), static_cast<ValueType>(7) / static_cast<ValueType>(2), static_cast<ValueType>(8) /  static_cast<ValueType>(2),
				static_cast<ValueType>(9) / static_cast<ValueType>(2), static_cast<ValueType>(10) / static_cast<ValueType>(2), static_cast<ValueType>(11) / static_cast<ValueType>(2), static_cast<ValueType>(12) / static_cast<ValueType>(2),
				static_cast<ValueType>(13) / static_cast<ValueType>(2), static_cast<ValueType>(14) / static_cast<ValueType>(2), static_cast<ValueType>(15) / static_cast<ValueType>(2), static_cast<ValueType>(16) / static_cast<ValueType>(2)
			} 
		};

		TEST_ASSERT(result);
	}
}

template<typename ValueType>
static void TestRadians() noexcept
{
	using namespace CinMath;
	using RadianType = TRadians<ValueType>;
	/* consteval constructor */
	{
		constexpr RadianType radians;
		TEST_ASSERT(radians == static_cast<ValueType>(0));
	}
	/* typesafe constructors */
	{
		/* literal const long double */
		{
			constexpr RadianType radians(45.0_rad);
			TEST_ASSERT(radians == static_cast<ValueType>(45.0));
		}

		/* literal const unsigned long long int */
		{
			constexpr RadianType radians(45_rad);
			TEST_ASSERT(radians == static_cast<ValueType>(45));
		}
	}
	/* Value type operator */
	{
		const RadianType radians(30.0_rad);
		const ValueType asIntegral{ radians.operator ValueType() };

		TEST_ASSERT(asIntegral == 30.0f)
	}
	/* comparison operator */
	{
		constexpr RadianType radians1(45_rad);
		constexpr RadianType radians2(45_rad);

		TEST_ASSERT(radians1 == radians2);
	}
	/* comparison operator */
	{
		constexpr RadianType radians1(45_rad);
		constexpr RadianType radians2(90_rad);

		TEST_ASSERT(radians1 != radians2);
	}
	/* operator+ */
	{
		constexpr RadianType radrees = 45_rad + 3_rad;
		TEST_ASSERT(radrees == static_cast<ValueType>(45 + 3))
	}
	/* operator- */
	{
		constexpr RadianType radrees = 45_rad - 3_rad;
		TEST_ASSERT(radrees == static_cast<ValueType>(45 - 3))
	}
	/* operator* */
	{
		constexpr RadianType radrees = 45_rad * 3;
		TEST_ASSERT(radrees == static_cast<ValueType>(45 * 3))
	}
	/* operator/ */
	{
		constexpr RadianType radrees = 45_rad / 3;
		TEST_ASSERT(radrees == static_cast<ValueType>(45 / 3))
	}
	/* operator + */
	{
		constexpr RadianType radrees1{ 45_rad };
		constexpr RadianType radrees2{ 3_rad };
		RadianType operation;
		operation = radrees1 + radrees2;

		TEST_ASSERT(operation == static_cast<ValueType>(45 + 3));
	}
	/* operator - */
	{
		constexpr RadianType radrees1{ 45_rad };
		constexpr RadianType radrees2{ 3_rad };
		RadianType operation;
		operation = radrees1 - radrees2;

		TEST_ASSERT(operation == static_cast<ValueType>(45 - 3));
	}
	/* operator * */
	{
		constexpr RadianType radrees1{ 45_rad };
		constexpr RadianType radrees2{ 3_rad };
		RadianType operation;
		operation = radrees1 * radrees2;

		TEST_ASSERT(operation == static_cast<ValueType>(45 * 3));
	}
	/* operator / */
	{
		constexpr RadianType radrees1{ 45_rad };
		constexpr RadianType radrees2{ 3_rad };
		RadianType operation;
		operation = radrees1 / radrees2;

		TEST_ASSERT(operation == static_cast<ValueType>(45 / 3));
	}
	/* operator += */
	{
		RadianType radrees1{ 45_rad };
		constexpr RadianType radrees2{ 3_rad };

		radrees1 += radrees2;
		TEST_ASSERT(radrees1 == static_cast<ValueType>(45 + 3));
	}
	/* operator -= */
	{
		RadianType radrees1{ 45_rad };
		constexpr RadianType radrees2{ 3_rad };

		radrees1 -= radrees2;
		TEST_ASSERT(radrees1 == static_cast<ValueType>(45 - 3));
	}
	/* operator *= */
	{
		RadianType radrees1{ 45_rad };
		constexpr RadianType radrees2{ 3_rad };

		radrees1 *= radrees2;
		TEST_ASSERT(radrees1 == static_cast<ValueType>(45 * 3));
	}
	/* operator /= */
	{
		RadianType radrees1{ 45_rad };
		constexpr RadianType radrees2{ 3_rad };

		radrees1 /= radrees2;
		TEST_ASSERT(radrees1 == static_cast<ValueType>(45 / 3));
	}
	/* operator += */
	{
		RadianType radrees{ 45_rad };
		radrees += 3_rad;
		TEST_ASSERT(radrees == static_cast<ValueType>(45 + 3));
	}
	/* operator -= */
	{
		RadianType radrees{ 45_rad };
		radrees -= 3_rad;
		TEST_ASSERT(radrees == static_cast<ValueType>(45 - 3));
	}
	/* operator *= */
	{
		RadianType radrees{ 45_rad };
		radrees *= 3_rad;
		TEST_ASSERT(radrees == static_cast<ValueType>(45 * 3));
	}
	/* operator /= */
	{
		RadianType radrees{ 45_rad };
		radrees /= 3_rad;
		TEST_ASSERT(radrees == static_cast<ValueType>(45 / 3));
	}
}

template<typename ValueType>
void TestDegrees() noexcept
{
	using namespace CinMath;
	using DegreesType = TDegrees<ValueType>;
	/* consteval constructor */
	{
		constexpr DegreesType degrees;
		TEST_ASSERT(degrees == static_cast<ValueType>(0));
	}
	/* typesafe constructor */
	{
		/* literal const long double */
		{
			constexpr DegreesType degrees(45.0_deg);
			TEST_ASSERT(degrees == static_cast<ValueType>(45.0));
		}

		/* literal const unsigned long long int */
		{
			constexpr DegreesType degrees(45_deg);
			TEST_ASSERT(degrees == static_cast<ValueType>(45));
		}
	}
	/* Value type operator */
	{
		const DegreesType degrees(30.0_deg);
		const ValueType asIntegral{degrees.operator ValueType() };

		TEST_ASSERT(asIntegral == 30.0f)
	}
	/* comparison operator */
	{
		constexpr DegreesType degrees1(45_deg);
		constexpr DegreesType degrees2(45_deg);

		TEST_ASSERT(degrees1 == degrees2);
	}
	/* comparison operator */
	{
		constexpr DegreesType degrees1(45_deg);
		constexpr DegreesType degrees2(90_deg);

		TEST_ASSERT(degrees1 != degrees2);
	}
	/* operator+ */
	{
		constexpr DegreesType degrees = 45_deg + 3_deg;
		TEST_ASSERT(degrees == static_cast<ValueType>(45 + 3))
	}
	/* operator- */
	{
		constexpr DegreesType degrees = 45_deg - 3_deg;
		TEST_ASSERT(degrees == static_cast<ValueType>(45 - 3))
	}
	/* operator* */
	{
		constexpr DegreesType degrees = 45_deg * 3;
		TEST_ASSERT(degrees == static_cast<ValueType>(45 * 3))
	}
	/* operator/ */
	{
		constexpr DegreesType degrees = 45_deg / 3;
		TEST_ASSERT(degrees == static_cast<ValueType>(45 / 3))
	}
	/* operator + */
	{
		constexpr DegreesType degrees1{ 45_deg };
		constexpr DegreesType degrees2{ 3_deg };
		DegreesType operation;
		operation = degrees1 + degrees2;

		TEST_ASSERT(operation == static_cast<ValueType>(45 + 3));
	}
	/* operator - */
	{
		constexpr DegreesType degrees1{ 45_deg };
		constexpr DegreesType degrees2{ 3_deg };
		DegreesType operation;
		operation = degrees1 - degrees2;

		TEST_ASSERT(operation == static_cast<ValueType>(45 - 3));
	}
	/* operator * */
	{
		constexpr DegreesType degrees1{ 45_deg };
		constexpr DegreesType degrees2{ 3_deg };
		DegreesType operation;
		operation = degrees1 * degrees2;

		TEST_ASSERT(operation == static_cast<ValueType>(45 * 3));
	}
	/* operator / */
	{
		constexpr DegreesType degrees1{ 45_deg };
		constexpr DegreesType degrees2{ 3_deg };
		DegreesType operation;
		operation = degrees1 / degrees2;

		TEST_ASSERT(operation == static_cast<ValueType>(45 / 3));
	}
	/* operator += */
	{
		DegreesType degrees1{ 45_deg };
		constexpr DegreesType degrees2{ 3_deg };

		degrees1 += degrees2;
		TEST_ASSERT(degrees1 == static_cast<ValueType>(45 + 3));
	}
	/* operator -= */
	{
		DegreesType degrees1{ 45_deg };
		constexpr DegreesType degrees2{ 3_deg };

		degrees1 -= degrees2;
		TEST_ASSERT(degrees1 == static_cast<ValueType>(45 - 3));
	}
	/* operator *= */
	{
		DegreesType degrees1{ 45_deg };
		constexpr DegreesType degrees2{ 3_deg };

		degrees1 *= degrees2;
		TEST_ASSERT(degrees1 == static_cast<ValueType>(45 * 3));
	}
	/* operator /= */
	{
		DegreesType degrees1{ 45_deg };
		constexpr DegreesType degrees2{ 3_deg };

		degrees1 /= degrees2;
		TEST_ASSERT(degrees1 == static_cast<ValueType>(45 / 3));
	}
	/* operator += */
	{
		DegreesType degrees{ 45_deg };
		degrees += 3_deg;
		TEST_ASSERT(degrees == static_cast<ValueType>(45 + 3));
	}
	/* operator -= */
	{
		DegreesType degrees{ 45_deg };
		degrees -= 3_deg;
		TEST_ASSERT(degrees == static_cast<ValueType>(45 - 3));
	}
	/* operator *= */
	{
		DegreesType degrees{ 45_deg };
		degrees *= 3_deg;
		TEST_ASSERT(degrees == static_cast<ValueType>(45 * 3));
	}
	/* operator /= */
	{
		DegreesType degrees{ 45_deg };
		degrees /= 3_deg;
		TEST_ASSERT(degrees == static_cast<ValueType>(45 / 3));
	}
}

template<typename ValueType>
static void TestAngle() noexcept
{
	using namespace CinMath;
	using AngleType = TAngle<ValueType>;
	/* consteval constructor */
	{
		constexpr AngleType angle;
		TEST_ASSERT(angle.ToRadians() == static_cast<ValueType>(0));
		TEST_ASSERT(angle.ToDegrees() == static_cast<ValueType>(0));
	}
	/* radians constructor */
	{
		/* literal const long double */
		{
			constexpr AngleType angle(45.0_rad);
			TEST_ASSERT(angle.ToRadians() == static_cast<ValueType>(45.0));
		}
		/* literal const unsigned long long int */
		{
			constexpr AngleType angle(45_rad);
			TEST_ASSERT(angle.ToRadians() == static_cast<ValueType>(45));
		}
	}
	/* degrees constructor */
	{
		/* literal const long double */
		{
			constexpr AngleType angle(45.0_deg);
			TEST_ASSERT(angle.ToDegrees() == static_cast<ValueType>(45.0));
		}
		/* literal const unsigned long long int */
		{
			constexpr AngleType angle(45_deg);
			TEST_ASSERT(angle.ToDegrees() == static_cast<ValueType>(45));
		}
	}
	/* comparison operator */
	{
		constexpr AngleType angle1(45_deg);
		constexpr AngleType angle2(45_deg);
		TEST_ASSERT(angle1 == angle2);
	}
	/* comparison operator */
	{
		constexpr AngleType angle1(45_deg);
		constexpr AngleType angle2(90_deg);
		TEST_ASSERT(angle1 != angle2);
	}
}

template<typename ValueType>
static void TestAngularComparison() noexcept
{
	using namespace CinMath;
	using RadiansType = TRadians<ValueType>;
	using DegreesType = TDegrees<ValueType>;

	/* Radians -> Degrees */
	{
		constexpr RadiansType radians(45_rad);
		TEST_ASSERT(Approximate<ValueType>(radians.ToDegrees(), static_cast<ValueType>(2578.3100781)));

		constexpr RadiansType radians2(1.0_rad);
		TEST_ASSERT(Approximate<ValueType>(radians2.ToDegrees(), static_cast<ValueType>(57.2957795131)));
	}
	/* Degrees -> Radians */
	{
		constexpr DegreesType degrees(90.32_deg);
		TEST_ASSERT(Approximate<ValueType>(degrees.ToRadians(), static_cast<ValueType>(1.5763813804)));

		constexpr DegreesType degrees2(360_deg);
		TEST_ASSERT(Approximate<ValueType>(degrees2.ToRadians(), static_cast<ValueType>(6.2831853072)));
	}
}

template<typename ValueType>
void TestQuaternion() noexcept
{
	using QuaternionType = CinMath::TQuaternion<ValueType>;
	using namespace CinMath;
	/* consteval constructor */
	{
		constexpr QuaternionType quat;
		TEST_ASSERT(quat[0U] == static_cast<ValueType>(0));
		TEST_ASSERT(quat[1U] == static_cast<ValueType>(0));
		TEST_ASSERT(quat[2U] == static_cast<ValueType>(0));
		TEST_ASSERT(quat[3U] == static_cast<ValueType>(0));
	}
	/* 4-value constructor */
	{
		constexpr QuaternionType quat(
			static_cast<ValueType>(1),
			static_cast<ValueType>(2),
			static_cast<ValueType>(3),
			static_cast<ValueType>(4));

		TEST_ASSERT(quat[0U] == static_cast<ValueType>(1));
		TEST_ASSERT(quat[1U] == static_cast<ValueType>(2));
		TEST_ASSERT(quat[2U] == static_cast<ValueType>(3));
		TEST_ASSERT(quat[3U] == static_cast<ValueType>(4));
	}
	/* scalar-vector constructor */
	{
		using VectorType = CinMath::Vector<3U, ValueType>;

		constexpr QuaternionType quat
		(
			static_cast<ValueType>(1), 
			VectorType
			{
				static_cast<ValueType>(2),
				static_cast<ValueType>(3),
				static_cast<ValueType>(4)
			}
		);
		TEST_ASSERT(quat[0U] == static_cast<ValueType>(1));
		TEST_ASSERT(quat[1U] == static_cast<ValueType>(2));
		TEST_ASSERT(quat[2U] == static_cast<ValueType>(3));
		TEST_ASSERT(quat[3U] == static_cast<ValueType>(4));
	}
	/* raw */
	{
		QuaternionType quat;
		TEST_ASSERT(reinterpret_cast<ValueType*>(std::addressof(quat)) == quat.operator ValueType * ());
		TEST_ASSERT(reinterpret_cast<ValueType*>(std::addressof(quat)) == quat.operator const ValueType * ());
	}
	/* index operators */
	{
		constexpr QuaternionType quaternion{ static_cast<ValueType>(0), static_cast<ValueType>(1), static_cast<ValueType>(2), static_cast<ValueType>(3) };
		{
			ValueType nonConst0{ quaternion[0] };
			ValueType nonConst1{ quaternion[1] };
			ValueType nonConst2{ quaternion[2] };
			ValueType nonConst3{ quaternion[3] };

			TEST_ASSERT(nonConst0 == 0 && nonConst1 == 1 && nonConst2 == 2 && nonConst3 == 3);
		}
		{
			const ValueType const0{ quaternion[0] };
			const ValueType const1{ quaternion[1] };
			const ValueType const2{ quaternion[2] };
			const ValueType const3{ quaternion[3] };

			TEST_ASSERT(const0 == 0 && const1 == 1 && const2 == 2 && const3 == 3);
		}
	}
	/* Vector4 conversion */
	{
		constexpr QuaternionType quaternion{ static_cast<ValueType>(0), static_cast<ValueType>(1), static_cast<ValueType>(2), static_cast<ValueType>(3) };
		const auto vec{ CinMath::Vector<4, ValueType>{ static_cast<ValueType>(0), static_cast<ValueType>(1), static_cast<ValueType>(2), static_cast<ValueType>(3) } };
		TEST_ASSERT((quaternion.operator CinMath::Vector<4, ValueType>() == vec));
	}
	/* operator == */
	{
		constexpr QuaternionType lhs{ static_cast<ValueType>(0), static_cast<ValueType>(1), static_cast<ValueType>(2), static_cast<ValueType>(3) };
		constexpr QuaternionType rhs{ static_cast<ValueType>(0), static_cast<ValueType>(1), static_cast<ValueType>(2), static_cast<ValueType>(3) };

		TEST_ASSERT(lhs == rhs);
	}
	/* operator != */
	{
		constexpr QuaternionType lhs{ static_cast<ValueType>(0), static_cast<ValueType>(1), static_cast<ValueType>(2), static_cast<ValueType>(3) };
		for(size_t i{ 0U }; i < 4U; ++i)
		{
			QuaternionType rhs{ static_cast<ValueType>(0), static_cast<ValueType>(1), static_cast<ValueType>(2), static_cast<ValueType>(3) };
			rhs[i] = 999;

			TEST_ASSERT(lhs != rhs);
		}
	}
	/* + operator */
	{
		constexpr QuaternionType lhs{ static_cast<ValueType>(1),  static_cast<ValueType>(2),  static_cast<ValueType>(3),  static_cast<ValueType>(4) };
		TEST_ASSERT(+lhs == lhs);
	}
	/* - operator */
	{
		constexpr QuaternionType lhs{ static_cast<ValueType>(1),  static_cast<ValueType>(2),  static_cast<ValueType>(3),  static_cast<ValueType>(4) };
		constexpr QuaternionType expected{ static_cast<ValueType>(-1), static_cast<ValueType>(-2),  static_cast<ValueType>(-3),  static_cast<ValueType>(-4) };
		TEST_ASSERT(-lhs == expected);
	}
	/* operator + */
	{
		constexpr QuaternionType lhs{ static_cast<ValueType>(1),  static_cast<ValueType>(2),  static_cast<ValueType>(3),  static_cast<ValueType>(4) };
		constexpr QuaternionType rhs{ static_cast<ValueType>(1),  static_cast<ValueType>(2),  static_cast<ValueType>(3),  static_cast<ValueType>(4) };

		const auto operation{ lhs + rhs };

		const bool result
		{
			operation == QuaternionType
			{
				static_cast<ValueType>(1 + 1),  static_cast<ValueType>(2 + 2),  static_cast<ValueType>(3 + 3),  static_cast<ValueType>(4 + 4)
			}
		};

		TEST_ASSERT(result);
	}
	/* operator - */
	{
		constexpr QuaternionType lhs{ static_cast<ValueType>(1),  static_cast<ValueType>(2),  static_cast<ValueType>(3),  static_cast<ValueType>(4) };
		constexpr QuaternionType rhs{ static_cast<ValueType>(1),  static_cast<ValueType>(2),  static_cast<ValueType>(3),  static_cast<ValueType>(4) };

		const auto operation{ lhs - rhs };

		const bool result
		{
			operation == QuaternionType
			{
				static_cast<ValueType>(1 - 1),  static_cast<ValueType>(2 - 2),  static_cast<ValueType>(3 - 3),  static_cast<ValueType>(4 - 4)
			}
		};

		TEST_ASSERT(result);
	}
	/* operator * */
	{
		constexpr QuaternionType lhs{ static_cast<ValueType>(1),  static_cast<ValueType>(2),  static_cast<ValueType>(3),  static_cast<ValueType>(4) };
		constexpr QuaternionType rhs{ static_cast<ValueType>(5),  static_cast<ValueType>(6),  static_cast<ValueType>(7),  static_cast<ValueType>(8) };

		const auto operation{ lhs * rhs };

		const bool result
		{
			operation == QuaternionType
			{
				static_cast<ValueType>(-60), static_cast<ValueType>(12), static_cast<ValueType>(30), static_cast<ValueType>(24)
			}
		};

		TEST_ASSERT(result);
	}
	/* operator / */
	{
#if 0
		constexpr QuaternionType lhs{ static_cast<ValueType>(1),  static_cast<ValueType>(2),  static_cast<ValueType>(3),  static_cast<ValueType>(4) };
		constexpr QuaternionType rhs{ static_cast<ValueType>(5),  static_cast<ValueType>(6),  static_cast<ValueType>(7),  static_cast<ValueType>(8) };

		const auto operation{ lhs / rhs };

		const bool result
		{
			operation == QuaternionType
			{
				static_cast<ValueType>(), static_cast<ValueType>(), static_cast<ValueType>(), static_cast<ValueType>()
			}
		};

		TEST_ASSERT(result);
#endif
	}
	/* operator * (scalar) */
	{
		constexpr QuaternionType lhs{ static_cast<ValueType>(1),  static_cast<ValueType>(2),  static_cast<ValueType>(3),  static_cast<ValueType>(4) };
				
		const auto operation{ lhs / static_cast<ValueType>(2) };

		const bool result
		{
			operation == QuaternionType
			{
				static_cast<ValueType>(1) / static_cast<ValueType>(2), static_cast<ValueType>(2) / static_cast<ValueType>(2), 
				static_cast<ValueType>(3) / static_cast<ValueType>(2), static_cast<ValueType>(4) / static_cast<ValueType>(2)
			}
		};

		TEST_ASSERT(result);
	}
}

template<typename ValueType>
void TestOther() noexcept
{
	/* ToRadians */
	{
		constexpr ValueType degrees{ 180.0f };
		TEST_ASSERT(CinMath::ToRadians(degrees) == CinMath::Constants::PI<ValueType>);
	}
	/* To degrees */
	{
		constexpr ValueType radians{ static_cast<ValueType>(2) * CinMath::Constants::PI<ValueType> };
		TEST_ASSERT(CinMath::ToDegrees(radians) == static_cast<ValueType>(360));
	}
	/* Length */
	{
		/* Vector2 */
		{
			using VectorType = CinMath::Vector<2, ValueType>;
			constexpr VectorType vector{ static_cast<ValueType>(3), static_cast<ValueType>(4) };
			TEST_ASSERT(CinMath::Length(vector) == static_cast<ValueType>(5));
		}
		/* Vector3 */
		{
			using VectorType = CinMath::Vector<3, ValueType>;
			constexpr VectorType vector{ static_cast<ValueType>(3), static_cast<ValueType>(4),  static_cast<ValueType>(12) };
			TEST_ASSERT(CinMath::Length(vector) == static_cast<ValueType>(13));
		}
		/* Vector4 */
		{
			using VectorType = CinMath::Vector<4, ValueType>;
			constexpr VectorType vector{ static_cast<ValueType>(4), static_cast<ValueType>(4),  static_cast<ValueType>(2), static_cast<ValueType>(8) };
			TEST_ASSERT(CinMath::Length(vector) == static_cast<ValueType>(10));
		}
	}
	/* Normalize */
	{
		/* Vector2 */
		{
			using VectorType = CinMath::Vector<2, ValueType>;
			constexpr VectorType vector{ static_cast<ValueType>(3), static_cast<ValueType>(4) };
			const VectorType expected{ static_cast<ValueType>(3) / static_cast<ValueType>(5), static_cast<ValueType>(4) / static_cast<ValueType>(5) };
			TEST_ASSERT(CinMath::Normalize(vector) == expected);
		}
		/* Vector3 */
		{
			using VectorType = CinMath::Vector<3, ValueType>;
			constexpr VectorType vector{ static_cast<ValueType>(3), static_cast<ValueType>(4),  static_cast<ValueType>(12) };
			const VectorType expected{ static_cast<ValueType>(3) / static_cast<ValueType>(13), static_cast<ValueType>(4) / static_cast<ValueType>(13), static_cast<ValueType>(12) / static_cast<ValueType>(13) };
			TEST_ASSERT(CinMath::Normalize(vector) == expected);
		}
		/* Vector4 */
		{
			using VectorType = CinMath::Vector<4, ValueType>;
			constexpr VectorType vector{ static_cast<ValueType>(4), static_cast<ValueType>(4),  static_cast<ValueType>(2), static_cast<ValueType>(8) };
			const VectorType expected{ static_cast<ValueType>(4) / static_cast<ValueType>(10), static_cast<ValueType>(4) / static_cast<ValueType>(10), static_cast<ValueType>(2) / static_cast<ValueType>(10), static_cast<ValueType>(8) / static_cast<ValueType>(10) };
			TEST_ASSERT(CinMath::Normalize(vector) == expected);
		}
	}
	/* Dot product */
	{
		/* Vector2 */
		{
			using VectorType = CinMath::Vector<2, ValueType>;
			constexpr VectorType lhs{ static_cast<ValueType>(3), static_cast<ValueType>(4) };
			constexpr VectorType rhs{ static_cast<ValueType>(3), static_cast<ValueType>(4) };
			const ValueType expected{ static_cast<ValueType>(25) };
			TEST_ASSERT(CinMath::Dot(lhs, rhs) == expected);
		}
		/* Vector3 */
		{
			using VectorType = CinMath::Vector<3, ValueType>;
			constexpr VectorType lhs{ static_cast<ValueType>(3), static_cast<ValueType>(4), static_cast<ValueType>(5) };
			constexpr VectorType rhs{ static_cast<ValueType>(3), static_cast<ValueType>(4), static_cast<ValueType>(2) };
			const ValueType expected{ static_cast<ValueType>(35) };
			TEST_ASSERT(CinMath::Dot(lhs, rhs) == expected);
		}
		/* Vector4 */
		{
			using VectorType = CinMath::Vector<4, ValueType>;
			constexpr VectorType lhs{ static_cast<ValueType>(3), static_cast<ValueType>(4), static_cast<ValueType>(5), static_cast<ValueType>(4) };
			constexpr VectorType rhs{ static_cast<ValueType>(3), static_cast<ValueType>(4), static_cast<ValueType>(2), static_cast<ValueType>(20) };
			const ValueType expected{ static_cast<ValueType>(115) };
			TEST_ASSERT(CinMath::Dot(lhs, rhs) == expected);
		}
		/* Cross product */
		{
			using VectorType = CinMath::Vector<3, ValueType>;
			constexpr VectorType lhs{ static_cast<ValueType>(2), static_cast<ValueType>(2), static_cast<ValueType>(1) };
			constexpr VectorType rhs{ static_cast<ValueType>(1), static_cast<ValueType>(-2), static_cast<ValueType>(0) };
			const VectorType expected{ static_cast<ValueType>(2), static_cast<ValueType>(1), static_cast<ValueType>(-6) };
			TEST_ASSERT(CinMath::Cross(lhs, rhs) == expected);
		}
		/* Cross product */
		{
			using VectorType = CinMath::Vector<4, ValueType>;
			constexpr VectorType lhs{ static_cast<ValueType>(2), static_cast<ValueType>(2), static_cast<ValueType>(1), static_cast<ValueType>(0) };
			constexpr VectorType rhs{ static_cast<ValueType>(1), static_cast<ValueType>(-2), static_cast<ValueType>(0), static_cast<ValueType>(0) };
			const VectorType expected{ static_cast<ValueType>(2), static_cast<ValueType>(1), static_cast<ValueType>(-6), static_cast<ValueType>(0) };
			TEST_ASSERT(CinMath::Cross(lhs, rhs) == expected);
		}
		/* Transpose */
		{
			using MatrixType = CinMath::Matrix<2, 2, ValueType>;
			constexpr MatrixType matrix
			{
				static_cast<ValueType>(11), static_cast<ValueType>(12),
				static_cast<ValueType>(21), static_cast<ValueType>(22),
			};

			constexpr MatrixType expected
			{
				static_cast<ValueType>(11), static_cast<ValueType>(21),
				static_cast<ValueType>(12), static_cast<ValueType>(22),
			};

			TEST_ASSERT(CinMath::Transpose(matrix) == expected);
			TEST_ASSERT(matrix == CinMath::Transpose(expected));
			TEST_ASSERT(CinMath::Transpose(CinMath::Transpose(matrix)) == matrix);
		}
		{
			using MatrixType = CinMath::Matrix<3, 3, ValueType>;
			constexpr MatrixType matrix
			{
				static_cast<ValueType>(11), static_cast<ValueType>(12), static_cast<ValueType>(13),
				static_cast<ValueType>(21), static_cast<ValueType>(22), static_cast<ValueType>(23),
				static_cast<ValueType>(31), static_cast<ValueType>(32), static_cast<ValueType>(33),
			};

			constexpr MatrixType expected
			{
				static_cast<ValueType>(11), static_cast<ValueType>(21), static_cast<ValueType>(31),
				static_cast<ValueType>(12), static_cast<ValueType>(22), static_cast<ValueType>(32),
				static_cast<ValueType>(13), static_cast<ValueType>(23), static_cast<ValueType>(33),
			};

			TEST_ASSERT(CinMath::Transpose(matrix) == expected);
			TEST_ASSERT(matrix == CinMath::Transpose(expected));
			TEST_ASSERT(CinMath::Transpose(CinMath::Transpose(matrix)) == matrix);
		}
		{
			using MatrixType = CinMath::Matrix<4, 4, ValueType>;
			constexpr MatrixType matrix
			{
				static_cast<ValueType>(11), static_cast<ValueType>(12), static_cast<ValueType>(13), static_cast<ValueType>(14),
				static_cast<ValueType>(21), static_cast<ValueType>(22), static_cast<ValueType>(23), static_cast<ValueType>(24),
				static_cast<ValueType>(31), static_cast<ValueType>(32), static_cast<ValueType>(33), static_cast<ValueType>(34),
				static_cast<ValueType>(41), static_cast<ValueType>(42), static_cast<ValueType>(43), static_cast<ValueType>(44)
			};

			constexpr MatrixType expected
			{
				static_cast<ValueType>(11), static_cast<ValueType>(21), static_cast<ValueType>(31), static_cast<ValueType>(41),
				static_cast<ValueType>(12), static_cast<ValueType>(22), static_cast<ValueType>(32), static_cast<ValueType>(42),
				static_cast<ValueType>(13), static_cast<ValueType>(23), static_cast<ValueType>(33), static_cast<ValueType>(43),
				static_cast<ValueType>(14), static_cast<ValueType>(24), static_cast<ValueType>(34), static_cast<ValueType>(44)
			};

			TEST_ASSERT(CinMath::Transpose(matrix) == expected);
			TEST_ASSERT(matrix == CinMath::Transpose(expected));
			TEST_ASSERT(CinMath::Transpose(CinMath::Transpose(matrix)) == matrix);
		}
	}
	/* Determinant */
	{
		using MatrixType = CinMath::Matrix<4, 4, ValueType>;
		constexpr MatrixType matrix
		{
			static_cast<ValueType>(1), static_cast<ValueType>(-2), static_cast<ValueType>(0), static_cast<ValueType>(3),
			static_cast<ValueType>(-1), static_cast<ValueType>(4), static_cast<ValueType>(1), static_cast<ValueType>(-2),
			static_cast<ValueType>(2), static_cast<ValueType>(-1), static_cast<ValueType>(0), static_cast<ValueType>(3),
			static_cast<ValueType>(-2), static_cast<ValueType>(1), static_cast<ValueType>(2), static_cast<ValueType>(0)
		};

		TEST_ASSERT(CinMath::Determinant(matrix) == static_cast<ValueType>(9));
	}
	{
		using MatrixType = CinMath::Matrix<3, 3, ValueType>;
		constexpr MatrixType matrix
		{
			static_cast<ValueType>(1), static_cast<ValueType>(-2), static_cast<ValueType>(3),
			static_cast<ValueType>(2), static_cast<ValueType>(-1), static_cast<ValueType>(3),
			static_cast<ValueType>(-2), static_cast<ValueType>(1), static_cast<ValueType>(0)
		};

		TEST_ASSERT(CinMath::Determinant(matrix) == static_cast<ValueType>(9));
	}
	{
		using MatrixType = CinMath::Matrix<2, 2, ValueType>;
		constexpr MatrixType matrix
		{
			static_cast<ValueType>(1), static_cast<ValueType>(-2),
			static_cast<ValueType>(2), static_cast<ValueType>(-1),
		};

		TEST_ASSERT(CinMath::Determinant(matrix) == static_cast<ValueType>(3));
	}
	/* Inverse */
	{
		using MatrixType = CinMath::Matrix<2, 2, ValueType>;
		constexpr MatrixType matrix
		{
			static_cast<ValueType>(1), static_cast<ValueType>(3), 
			static_cast<ValueType>(4), static_cast<ValueType>(2), 
		};

		constexpr MatrixType expected
		{
			static_cast<ValueType>(-2), static_cast<ValueType>(3), 
			static_cast<ValueType>(4), static_cast<ValueType>(-1),
		};

		const auto readableForm{ CinMath::Inverse(matrix) * static_cast<ValueType>(10) };
		const bool success{ ApproximateMatrix<2, 2, ValueType>(readableForm, expected) };
		TEST_ASSERT(success);
	}
	{
		using MatrixType = CinMath::Matrix<3, 3, ValueType>;
		constexpr MatrixType matrix
		{
			static_cast<ValueType>(1), static_cast<ValueType>(3), static_cast<ValueType>(6),
			static_cast<ValueType>(4), static_cast<ValueType>(2), static_cast<ValueType>(1),
			static_cast<ValueType>(4), static_cast<ValueType>(4), static_cast<ValueType>(3),
		};

		constexpr MatrixType expected
		{
			static_cast<ValueType>(2), static_cast<ValueType>(15), static_cast<ValueType>(-9),
			static_cast<ValueType>(-8), static_cast<ValueType>(-21), static_cast<ValueType>(23),
			static_cast<ValueType>(8), static_cast<ValueType>(8), static_cast<ValueType>(-10)
		};

		const auto readableForm{ CinMath::Inverse(matrix) * static_cast<ValueType>(26) };
		const bool success{ ApproximateMatrix<3, 3, ValueType>(readableForm, expected) };
		TEST_ASSERT(success);
	}
	{
		using MatrixType = CinMath::Matrix<4, 4, ValueType>;
		constexpr MatrixType matrix
		{
			static_cast<ValueType>(1), static_cast<ValueType>(3), static_cast<ValueType>(6), static_cast<ValueType>(4),
			static_cast<ValueType>(4), static_cast<ValueType>(2), static_cast<ValueType>(1), static_cast<ValueType>(3),
			static_cast<ValueType>(4), static_cast<ValueType>(4), static_cast<ValueType>(3), static_cast<ValueType>(2),
			static_cast<ValueType>(2), static_cast<ValueType>(2), static_cast<ValueType>(1), static_cast<ValueType>(9)
		};

		constexpr MatrixType expected
		{
			static_cast<ValueType>(12), static_cast<ValueType>(125), static_cast<ValueType>(-54), static_cast<ValueType>(-35),
			static_cast<ValueType>(-62), static_cast<ValueType>(-175), static_cast<ValueType>(166), static_cast<ValueType>(49),
			static_cast<ValueType>(64), static_cast<ValueType>(64), static_cast<ValueType>(-62), static_cast<ValueType>(-36),
			static_cast<ValueType>(4), static_cast<ValueType>(4), static_cast<ValueType>(-18), static_cast<ValueType>(26)
		};

		const auto readableForm{ CinMath::Inverse(matrix) * static_cast<ValueType>(226) };
		const bool success{ ApproximateMatrix<4, 4, ValueType>(readableForm, expected) };
		TEST_ASSERT(success);
	}
}

template<typename ValueType>
static void TestProjection() noexcept
{
	if constexpr (std::is_same_v<ValueType, float>)
	{
		using MatrixType = CinMath::Matrix<4, 4, ValueType>;
		MatrixType result = CinMath::OrthographicProjection(-2.0f, 2.0f, -1.0f, 1.0f);

		constexpr MatrixType expected
		{
			static_cast<ValueType>(0.5),	static_cast<ValueType>(0),		static_cast<ValueType>(0), static_cast<ValueType>(0),
			static_cast<ValueType>(0),		static_cast<ValueType>(1.0),	static_cast<ValueType>(0), static_cast<ValueType>(0),
			static_cast<ValueType>(0),		static_cast<ValueType>(0),		static_cast<ValueType>(-1.0), static_cast<ValueType>(0),
			static_cast<ValueType>(0),		static_cast<ValueType>(0),		static_cast<ValueType>(0), static_cast<ValueType>(1.0)
		};

		TEST_ASSERT(expected == result);
	}
}

#if TEST_PRINTING
template<typename ValueType>
void TestPrinting() noexcept
{
	using namespace CinMath::Printing;

	const auto randomfloat
	{
		[]() -> float
		{
			return static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
		}
	};
	/* Vectors */
	std::cout << "\n--VECTOR PRINT--\n";
	{
		using Vector4Type = CinMath::Vector<4, ValueType>;
		constexpr Vector4Type toPrint{ 1, 2, 3, 4 };

		std::cout << "std-out\n";
		std::cout << toPrint;
		std::cout << "std-out-default\n";
		std::cout << VectorPrinter(toPrint, DefaultVectorPrintSpecificer());
		std::cout << "std-out-round\n";
		std::cout << VectorPrinter(toPrint, RoundVectorPrintSpecificer());
		std::cout << "std-out-curly\n";
		std::cout << VectorPrinter(toPrint, CurlyVectorPrintSpecificer());
	}
	{
		using Vector4Type = CinMath::Vector<3, ValueType>;
		constexpr Vector4Type toPrint{ 1, 2, 3 };

		std::cout << "std-out\n";
		std::cout << toPrint;
		std::cout << "std-out-default\n";
		std::cout << VectorPrinter(toPrint, DefaultVectorPrintSpecificer());
		std::cout << "std-out-round\n";
		std::cout << VectorPrinter(toPrint, RoundVectorPrintSpecificer());
		std::cout << "std-out-curly\n";
		std::cout << VectorPrinter(toPrint, CurlyVectorPrintSpecificer());
	}
	{
		using Vector4Type = CinMath::Vector<2, ValueType>;
		constexpr Vector4Type toPrint{ 1, 2 };

		std::cout << "std-out\n";
		std::cout << toPrint;
		std::cout << "std-out-default\n";
		std::cout << VectorPrinter(toPrint, DefaultVectorPrintSpecificer());
		std::cout << "std-out-round\n";
		std::cout << VectorPrinter(toPrint, RoundVectorPrintSpecificer());
		std::cout << "std-out-curly\n";
		std::cout << VectorPrinter(toPrint, CurlyVectorPrintSpecificer());
	}
	/* Matrices */
	std::cout << "\n--MARIX PRINT--\n";
	{
		using Matrix4x4Type = CinMath::Matrix<4, 4, ValueType>;
		const Matrix4x4Type toPrint
		{
			randomfloat(), randomfloat(), randomfloat(), randomfloat(),
			randomfloat(), randomfloat(), randomfloat(), randomfloat(),
			randomfloat(), randomfloat(), randomfloat(), randomfloat(),
			randomfloat(), randomfloat(), randomfloat(), randomfloat()
		};

		std::cout << "std-out\n";
		std::cout << toPrint;
		std::cout << "std-out-default\n";
		std::cout << MatrixPrinter(toPrint, DefaultMatrixPrintSpecificer());
		std::cout << "std-out-thick\n";
		std::cout << MatrixPrinter(toPrint, ThickMatrixPrintSpecificer());
		std::cout << "std-out-naked\n";
		std::cout << MatrixPrinter(toPrint, NakedMatrixPrintSpecificer());
	}
	{
		using Matrix3x3Type = CinMath::Matrix<3, 3, ValueType>;
		constexpr Matrix3x3Type toPrint
		{
			11, 12, 13,
			21, 22, 23,
			31, 32, 33
		};

		std::cout << "std-out\n";
		std::cout << toPrint;
		std::cout << "std-out-default\n";
		std::cout << MatrixPrinter(toPrint, DefaultMatrixPrintSpecificer());
		std::cout << "std-out-thick\n";
		std::cout << MatrixPrinter(toPrint, ThickMatrixPrintSpecificer());
		std::cout << "std-out-naked\n";
		std::cout << MatrixPrinter(toPrint, NakedMatrixPrintSpecificer());
	}
	{
		using Matrix2x2Type = CinMath::Matrix<2, 2, ValueType>;
		constexpr Matrix2x2Type toPrint
		{
			11, 12,
			21, 22
		};

		std::cout << "std-out\n";
		std::cout << toPrint;
		std::cout << "std-out-default\n";
		std::cout << MatrixPrinter(toPrint, DefaultMatrixPrintSpecificer());
		std::cout << "std-out-thick\n";
		std::cout << MatrixPrinter(toPrint, ThickMatrixPrintSpecificer());
		std::cout << "std-out-naked\n";
		std::cout << MatrixPrinter(toPrint, NakedMatrixPrintSpecificer());
	}
	std::cout << "--PRINT QUATERNION--";
	{
		using QuaternionType = CinMath::TQuaternion<ValueType>;
		constexpr QuaternionType quat{ static_cast<ValueType>(1), static_cast<ValueType>(2), static_cast<ValueType>(3), static_cast<ValueType>(4) };
		std::cout << quat;
	}
}
#endif