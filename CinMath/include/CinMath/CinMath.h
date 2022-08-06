#pragma once
#define CIN_INSTRUCTION_SET_DEFAULT_BIT		(0U)
#define CIN_INSTRUCTION_SET_X86_BIT			(0x40000000U)
#define CIN_INSTRUCTION_SET_ARM_BIT			(0x80000000U)
#define CIN_INSTRUCTION_SET_NEON_BIT		(0x00000001U)
#define CIN_INSTRUCTION_SET_SSE_BIT			(0x00000002U)
#define CIN_INSTRUCTION_SET_SSE2_BIT		(0x00000004U)
#define CIN_INSTRUCTION_SET_SSE3_BIT		(0x00000008U)
#define CIN_INSTRUCTION_SET_SSSE3_BIT		(0x00000010U)
#define CIN_INSTRUCTION_SET_SSE41_BIT		(0x00000020U)
#define CIN_INSTRUCTION_SET_SSE42_BIT		(0x00000040U)
#define CIN_INSTRUCTION_SET_AVX_BIT			(0x00000080U)
#define CIN_INSTRUCTION_SET_AVX2_BIT		(0x00000100U)

#define CIN_INSTRUCTION_SET_AVX2			CIN_INSTRUCTION_SET_AVX2_BIT	| CIN_INSTRUCTION_SET_AVX
#define CIN_INSTRUCTION_SET_AVX				CIN_INSTRUCTION_SET_AVX_BIT		| CIN_INSTRUCTION_SET_SSE42
#define CIN_INSTRUCTION_SET_SSE42			CIN_INSTRUCTION_SET_SSE42_BIT	| CIN_INSTRUCTION_SET_SSE41
#define CIN_INSTRUCTION_SET_SSE41			CIN_INSTRUCTION_SET_SSE41_BIT	| CIN_INSTRUCTION_SET_SSSE3
#define CIN_INSTRUCTION_SET_SSSE3			CIN_INSTRUCTION_SET_SSSE3_BIT	| CIN_INSTRUCTION_SET_SSE3
#define CIN_INSTRUCTION_SET_SSE3			CIN_INSTRUCTION_SET_SSE3_BIT	| CIN_INSTRUCTION_SET_SSE2
#define CIN_INSTRUCTION_SET_SSE2			CIN_INSTRUCTION_SET_SSE2_BIT	| CIN_INSTRUCTION_SET_SSE
#define CIN_INSTRUCTION_SET_SSE				CIN_INSTRUCTION_SET_SSE_BIT		| CIN_INSTRUCTION_SET_X86
#define CIN_INSTRUCTION_SET_NEON			CIN_INSTRUCTION_SET_NEON_BIT	| CIN_INSTRUCTION_SET_ARM
#define CIN_INSTRUCTION_SET_ARM				CIN_INSTRUCTION_SET_ARM_BIT
#define CIN_INSTRUCTION_SET_X86				CIN_INSTRUCTION_SET_X86_BIT
#define CIN_INSTRUCTION_SET_DEFAULT			CIN_INSTRUCTION_SET_DEFAULT_BIT

#ifdef CIN_USE_DEFAULT_INSTRUCTION_SET
#define CIN_INSTRUCTION_SET CIN_INSTRUCTION_SET_DEFAULT
#elif defined(CIN_USE_NEON)
#define CIN_INSTRUCTION_SET (CIN_INSTRUCTION_SET_NEON)
#define CIN_FORCE_INTRINSICS
#elif defined(CIN_USE_AVX2)
#define CIN_INSTRUCTION_SET (CIN_INSTRUCTION_SET_AVX2)
#define CIN_FORCE_INTRINSICS
#elif defined(CIN_USE_AVX)
#define CIN_INSTRUCTION_SET (CIN_INSTRUCTION_SET_AVX)
#define CIN_FORCE_INTRINSICS
#elif defined(CIN_USE_SSE42)
#define CIN_INSTRUCTION_SET (CIN_INSTRUCTION_SET_SSE42)
#define CIN_FORCE_INTRINSICS
#elif defined(CIN_USE_SSE41)
#define CIN_INSTRUCTION_SET (CIN_INSTRUCTION_SET_SSE41)
#define CIN_FORCE_INTRINSICS
#elif defined(CIN_USE_SSSE3)
#define CIN_INSTRUCTION_SET (CIN_INSTRUCTION_SET_SSSE3)
#define CIN_FORCE_INTRINSICS
#elif defined(CIN_USE_SSE3)
#define CIN_INSTRUCTION_SET (CIN_INSTRUCTION_SET_SSE3)
#define CIN_FORCE_INTRINSICS
#elif defined(CIN_USE_SSE2)
#define CIN_INSTRUCTION_SET (CIN_INSTRUCTION_SET_SSE2)
#define CIN_FORCE_INTRINSICS
#elif defined(CIN_USE_SSE)
#define CIN_INSTRUCTION_SET (CIN_INSTRUCTION_SET_SSE)
#define CIN_USE_INTRINSICS
#elif defined(CIN_USE_INTRINSICS)
#if defined(__AVX2__)
#define CIN_INSTRUCTION_SET (CIN_INSTRUCTION_SET_AVX2)
#elif defined(__AVX__)
#define CIN_INSTRUCTION_SET (CIN_INSTRUCTION_SET_AVX)
#elif defined(__SSE4_2__)
#define CIN_INSTRUCTION_SET (CIN_INSTRUCTION_SET_SSE42)
#elif defined(__SSE4_1__)
#define CIN_INSTRUCTION_SET (CIN_INSTRUCTION_SET_SSE41)
#elif defined(__SSSE3__)
#define CIN_INSTRUCTION_SET (CIN_INSTRUCTION_SET_SSSE3)
#elif defined(__SSE3__)
#define CIN_INSTRUCTION_SET (CIN_INSTRUCTION_SET_SSE3)
#elif defined(__SSE2__) || defined(__x86_64__) || defined(_M_X64) || defined(_M_IX86_FP)
#define CIN_INSTRUCTION_SET (CIN_INSTRUCTION_SET_SSE2)
#elif defined(__i386__)
#define CIN_INSTRUCTION_SET (CIN_INSTRUCTION_SET_X86)
#elif defined(__ARM_NEON)
#define CIN_INSTRUCTION_SET (CIN_INSTRUCTION_SET_ARM | CIN_INSTRUCTION_SET_NEON)
#elif defined(__arm__ ) || defined(_M_ARM)
#define CIN_INSTRUCTION_SET (CIN_INSTRUCTION_SET_ARM)
#else
#define CIN_INSTRUCTION_SET (CIN_INSTRUCTION_SET_DEFAULT)
#endif
#endif

/* https://stackoverflow.com/questions/11228855/header-files-for-x86-simd-intrinsics */
#if (CIN_INSTRUCTION_SET) & (CIN_INSTRUCTION_SET_AVX2_BIT)
#include <immintrin.h>
#elif (CIN_INSTRUCTION_SET) & (CIN_INSTRUCTION_SET_AVX_BIT)
#include <immintrin.h>
#elif (CIN_INSTRUCTION_SET)  & (CIN_INSTRUCTION_SET_SSE42_BIT)
#include <nmmintrin.h>
#elif (CIN_INSTRUCTION_SET) & (CIN_INSTRUCTION_SET_SSE41_BIT)
#include <smmintrin.h>
#elif (CIN_INSTRUCTION_SET) & (CIN_INSTRUCTION_SET_SSSE3_BIT)
#include <tmmintrin.h>
#elif (CIN_INSTRUCTION_SET)  & (CIN_INSTRUCTION_SET_SSE3_BIT)
#include <pmmintrin.h>
#elif (CIN_INSTRUCTION_SET) & (CIN_INSTRUCTION_SET_SSE2_BIT)
#include <emmintrin.h>
#elif (CIN_INSTRUCTION_SET) & (CIN_INSTRUCTION_SET_SSE_BIT)
#include <xmmintrin.h>
#endif

#ifdef _MSC_VER
#define CIN_CALL __vectorcall
#else
#define CIN_CALL
#endif

#if defined(__clang__) || defined(__GNUC__)
#include <cmath>
#endif

#if defined(__clang__) || defined(__GNUC__)
#define CIN_MATH_INLINE		inline __attribute__((always_inline))
#else
#define CIN_MATH_INLINE  	__forceinline
#endif
#define CIN_MATH_FUNCTION_QUALIFIER CIN_FORCE_INLINE

#if defined(__clang__) || defined(__GNUC__)
#define CIN_MATH_PREFETCH(address) __builtin_prefetch(address)
#define CIN_MATH_RESTRICT
#elif defined(_MSC_VER)
#define CIN_MATH_PREFETCH(address) __prefetch(address)
#define CIN_MATH_RESTRICT __restrict
#else
#define CIN_MATH_PREFETCH(address)
#define CIN_MATH_RESTRICT
#endif

/* Anonymous struct warning */
#if _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4201)  
#elif __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic"
#elif __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wgnu-anonymous-struct"
#pragma clang diagnostic ignored "-Wnested-anon-types"
#endif

#include <stdint.h>
#include <cstdint>
#include <array>
#include <sstream>
#include <iostream>
#include <assert.h>

namespace CinMath {
	namespace Constants {
		template<typename T>
		constexpr T PI = T(3.1415926535897932384626433832795L);

		template<auto N>
		concept FactorialComputable = N > 0 and std::is_arithmetic<decltype(N)>::value and std::is_integral<decltype(N)>::value;

		template<auto N> requires FactorialComputable<N>
		consteval std::size_t Factorial()
		{
			if constexpr (N > 1)
				return N * Factorial<N - 1>();
			else
				return N;
		}
	}

	/* Force the argument to be evaluated at compile-time */
	consteval auto AtCompileTime(auto arg)
	{
		return arg;
	}

	/* Template type parameters */
	typedef float DefaultPrecision;
	typedef double DoublePrecision;

	typedef std::uint64_t Rows_t;
	typedef std::uint64_t Columns_t;
	typedef std::uint64_t Length_t;

	/* SIMD and basic types */
#if (CIN_INSTRUCTION_SET) == (CIN_INSTRUCTION_SET_DEFAULT_BIT)
	/* Vectors */
	typedef float CinnamonFloat32Vector1_t;
	typedef float CinnamonFloat32Vector2_t[2];
	typedef float CinnamonFloat32Vector3_t[3];
	typedef float CinnamonFloat32Vector4_t[4];
	/* Matrices */
	typedef float CinnamonFloat32Matrix1x1_t;
	typedef float CinnamonFloat32Matrix2x2_t[2 * 2];
	typedef float CinnamonFloat32Matrix3x3_t[3 * 3];
	typedef float CinnamonFloat32Matrix4x4_t[4 * 4];
	/* Quaternions */
	typedef CinnamonFloat32Vector4_t CinnamonFloat32Quaternion_t;
#elif ((CIN_INSTRUCTION_SET) & (CIN_INSTRUCTION_SET_AVX2_BIT)) || ((CIN_INSTRUCTION_SET) & (CIN_INSTRUCTION_SET_AVX_BIT))
	/* Vectors */
	typedef float CinnamonFloat32Vector1_t;
	typedef float CinnamonFloat32Vector2_t[2];
	typedef float CinnamonFloat32Vector3_t[3];
	typedef __m128 CinnamonFloat32Vector4_t;
	/* Matrices */
	typedef float CinnamonFloat32Matrix1x1_t;
	typedef __m128 CinnamonFloat32Matrix2x2_t;
	typedef float CinnamonFloat32Matrix3x3_t[3 * 3];
	typedef __m256 CinnamonFloat32Matrix4x4_t[2];
	/* Quaternions */
	typedef CinnamonFloat32Vector4_t CinnamonFloat32Quaternion_t;
#elif (CIN_INSTRUCTION_SET) & (CIN_INSTRUCTION_SET_SSE2_BIT)
	/* Vectors */
	typedef float CinnamonFloat32Vector1_t;
	typedef float CinnamonFloat32Vector2_t[2];
	typedef float CinnamonFloat32Vector3_t[3];
	typedef __m128 CinnamonFloat32Vector4_t;
	/* Matrices */
	typedef float CinnamonFloat32Matrix1x1_t;
	typedef __m128 CinnamonFloat32Matrix2x2_t;
	typedef float CinnamonFloat32Matrix3x3_t[3 * 3];
	typedef __m128 CinnamonFloat32Matrix4x4_t[4];
	/* Quaternions */
	typedef CinnamonFloat32Vector4_t CinnamonFloat32Quaternion_t;
#elif (CIN_INSTRUCTION_SET) & (CIN_INSTRUCTION_SET_SSE_BIT) /* 128 bit wide float registers only */
	/* Vectors */
	typedef float CinnamonFloat32Vector1_t;
	typedef float CinnamonFloat32Vector2_t[2];
	typedef float CinnamonFloat32Vector3_t[3];
	typedef __m128 CinnamonFloat32Vector4_t;
	/* Matrices */
	typedef float CinnamonFloat32Matrix1x1_t;
	typedef __m128  CinnamonFloat32Matrix2x2_t;
	typedef float CinnamonFloat32Matrix3x3_t[3 * 3];
	typedef __m128 CinnamonFloat32Matrix4x4_t[4];
	/* Quaternions */
	typedef CinnamonFloat32Vector4_t CinnamonFloat32Quaternion_t;
#endif
	/* Linear vector containers */
	template<Length_t length, typename ValueType>
	struct Storage final
	{
		typedef struct {
			ValueType data[length];
		} Container;
	};

	/* Vector 2 */
	template<>
	struct Storage<2, float> final
	{
		typedef CinnamonFloat32Vector2_t Container;
	};

	/* Vector 3 */
	template<>
	struct Storage<3, float> final
	{
		typedef CinnamonFloat32Vector3_t Container;
	};

	/* Vector 4 */
	template<>
	struct Storage<4, float> final
	{
		typedef CinnamonFloat32Vector4_t Container;
	};

	/* Matrix containers */
	template<Rows_t rows, Columns_t columns, typename ValueType>
	struct MatrixStorage;

	/* Matrix 2x2 */
	template<>
	struct MatrixStorage<2, 2, float> final
	{
		typedef CinnamonFloat32Matrix2x2_t Container;
	};

	/* Matrix 3x3 */
	template<>
	struct MatrixStorage<3, 3, float> final
	{
		typedef CinnamonFloat32Matrix3x3_t Container;
	};

	/* Matrix 4x4 */
	template<>
	struct MatrixStorage<4, 4, float> final
	{
		typedef CinnamonFloat32Matrix4x4_t Container;
	};
}

namespace CinMath {
	/* Generic vector type */
	template<Length_t length, typename ValueType>
	class Vector;

	/* Generic matrix type */
	template<Rows_t N, Columns_t M, typename ValueType>
	class Matrix;
}

/* Includes */
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"

#include "Matrix2.h"
#include "Matrix3.h"
#include "Matrix4.h"

#include "Quaternion.h"

#include "Transform.h"

/* Inline headers */
#include "Vector2.inl"
#include "Vector3.inl"
#include "Vector4.inl"

#include "Matrix2.inl"
#include "Matrix3.inl"
#include "Matrix4.inl"

#include "Quaternion.inl"

#include "Transform.inl"

#if _MSC_VER
#pragma warning(pop)
#elif __GNUC__
#pragma GCC diagnostic pop
#elif __clang__
#pragma clang diagnostic pop
#endif

#include <iostream>
CIN_MATH_INLINE std::ostream& operator<<(std::ostream& stream, const CinMath::Vector2& vector) noexcept
{
	stream << vector.x << ' ' << vector.y;
	return stream;
}

CIN_MATH_INLINE std::ostream& operator<<(std::ostream& stream, const CinMath::Vector3& vector) noexcept
{
	stream << vector.x << ' ' << vector.y << ' ' << vector.z;
	return stream;
}

CIN_MATH_INLINE std::ostream& operator<<(std::ostream& stream, const CinMath::Vector4& vector) noexcept
{
	stream << vector.x << ' ' << vector.y << ' ' << vector.z << ' ' << vector.w;
	return stream;
}

CIN_MATH_INLINE std::ostream& operator<<(std::ostream& stream, const CinMath::Matrix2& matrix) noexcept
{
	stream
		<< matrix[0] << ' ' << matrix[1] << '\n'
		<< matrix[2] << ' ' << matrix[3];
	return stream;
}

CIN_MATH_INLINE std::ostream& operator<<(std::ostream& stream, const CinMath::Matrix3& matrix) noexcept
{
	stream
		<< matrix[0] << ' ' << matrix[1] << ' ' << matrix[2] << '\n'
		<< matrix[3] << ' ' << matrix[4] << ' ' << matrix[5] << '\n'
		<< matrix[6] << ' ' << matrix[7] << ' ' << matrix[8];
	return stream;
}

CIN_MATH_INLINE std::ostream& operator<<(std::ostream& stream, const CinMath::Matrix4& matrix) noexcept
{
	stream
		<< matrix[0] << ' ' << matrix[1] << ' ' << matrix[2] << ' ' << matrix[3] << '\n'
		<< matrix[4] << ' ' << matrix[5] << ' ' << matrix[6] << ' ' << matrix[7] << '\n'
		<< matrix[8] << ' ' << matrix[9] << ' ' << matrix[10] << ' ' << matrix[11] << '\n'
		<< matrix[12] << ' ' << matrix[13] << ' ' << matrix[14] << ' ' << matrix[15];
	return stream;
}

CIN_MATH_INLINE std::ostream& operator<<(std::ostream& stream, const CinMath::Quaternion& quaternion) noexcept
{
	stream << quaternion.a << ' ' << quaternion.b << ' ' << quaternion.c << ' ' << quaternion.d;
	return stream;
}
