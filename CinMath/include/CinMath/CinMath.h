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
#define CIN_MATH_CALL __vectorcall
#else
#define CIN_MATH_CALL
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

	/* Used to signal constant evaluation constructors */
	struct ConstevalConstructorProxy {};
	/* Buffer out of warning (swizzles are unions) */
#if _MSC_VER
#pragma warning(push)
#pragma warning(disable: 6201)
#pragma warning(disable: 6385)
#elif __GNUC__
#elif __clang__
#endif
	/* Swizzling */
	template<typename Type, std::size_t Index>
	struct ScalarSwizzle final
	{
		Type View[1];

		constexpr CIN_MATH_INLINE Type& operator=(const Type x) noexcept
		{
			View[Index] = x;
			return View[Index];
		}

		constexpr CIN_MATH_INLINE operator Type() const noexcept
		{
			return View[Index];
		}

		constexpr CIN_MATH_INLINE Type operator++(const int) noexcept
		{
			return View[Index]++;
		}

		constexpr CIN_MATH_INLINE Type operator++() noexcept
		{
			return ++View[Index];
		}

		constexpr CIN_MATH_INLINE Type operator--(const int) noexcept
		{
			return View[Index]--;
		}

		constexpr CIN_MATH_INLINE Type operator--() noexcept
		{
			return --View[Index];
		}
	};

	template<typename Type, typename VectorType, std::size_t SwizzleFirst, std::size_t SwizzleSecond>
	struct Vector2Swizzle final
	{
		Type View[2];

		constexpr CIN_MATH_INLINE VectorType operator=(const Type scalar) const noexcept
		{
			return VectorType(View[SwizzleFirst] = scalar, View[SwizzleSecond] = scalar);
		}

		constexpr CIN_MATH_INLINE VectorType operator+(const Type scalar) const noexcept
		{
			return VectorType(View[SwizzleFirst] + scalar, View[SwizzleSecond] + scalar);
		}

		constexpr CIN_MATH_INLINE VectorType operator-(const Type scalar) const noexcept
		{
			return VectorType(View[SwizzleFirst] - scalar, View[SwizzleSecond] - scalar);
		}

		constexpr CIN_MATH_INLINE VectorType operator*(const Type scalar) const noexcept
		{
			return VectorType(View[SwizzleFirst] * scalar, View[SwizzleSecond] * scalar);
		}

		constexpr CIN_MATH_INLINE VectorType operator+=(const Type scalar) noexcept
		{
			return VectorType(View[SwizzleFirst] += scalar, View[SwizzleSecond] += scalar);
		}

		constexpr CIN_MATH_INLINE VectorType operator-=(const Type scalar) noexcept
		{
			return VectorType(View[SwizzleFirst] -= scalar, View[SwizzleSecond] -= scalar);
		}

		constexpr CIN_MATH_INLINE VectorType operator*=(const Type scalar) noexcept
		{
			return VectorType(View[SwizzleFirst] *= scalar, View[SwizzleSecond] *= scalar);
		}

		constexpr CIN_MATH_INLINE VectorType operator=(const VectorType& vector) noexcept
		{
			return VectorType(View[SwizzleFirst] = vector.x, View[SwizzleSecond] = vector.y);
		}

		constexpr CIN_MATH_INLINE VectorType operator+=(const VectorType& vector) noexcept
		{
			return VectorType(View[SwizzleFirst] += vector.x, View[SwizzleSecond] += vector.y);
		}

		constexpr CIN_MATH_INLINE VectorType operator-=(const VectorType& vector) noexcept
		{
			return VectorType(View[SwizzleFirst] -= vector.x, View[SwizzleSecond] -= vector.y);
		}

		constexpr CIN_MATH_INLINE VectorType operator*=(const VectorType& vector) noexcept
		{
			return VectorType(View[SwizzleFirst] *= vector.x, View[SwizzleSecond] *= vector.y);
		}

		constexpr CIN_MATH_INLINE operator VectorType() const noexcept
		{
			return VectorType(View[SwizzleFirst], View[SwizzleSecond]);
		}
	};

	template<typename Type, typename VectorType, std::size_t SwizzleFirst, std::size_t SwizzleSecond, std::size_t SwizzleThird>
	struct Vector3Swizzle final
	{
		Type View[3];

		constexpr CIN_MATH_INLINE VectorType operator=(const Type scalar) noexcept
		{
			return VectorType(View[SwizzleFirst] = scalar, View[SwizzleSecond] = scalar, View[SwizzleThird] = scalar);
		}

		constexpr CIN_MATH_INLINE VectorType operator+(const Type scalar) noexcept
		{
			return VectorType(View[SwizzleFirst] + scalar, View[SwizzleSecond] + scalar, View[SwizzleThird] + scalar);
		}

		constexpr CIN_MATH_INLINE VectorType operator-(const Type scalar) noexcept
		{
			return VectorType(View[SwizzleFirst] - scalar, View[SwizzleSecond] - scalar, View[SwizzleThird] - scalar);
		}

		constexpr CIN_MATH_INLINE VectorType operator*(const Type scalar) noexcept
		{
			return VectorType(View[SwizzleFirst] * scalar, View[SwizzleSecond] * scalar, View[SwizzleThird] * scalar);
		}

		constexpr CIN_MATH_INLINE VectorType operator+=(const Type scalar) noexcept
		{
			return VectorType(View[SwizzleFirst] += scalar, View[SwizzleSecond] += scalar, View[SwizzleThird] += scalar);
		}

		constexpr CIN_MATH_INLINE VectorType operator-=(const Type scalar) noexcept
		{
			return VectorType(View[SwizzleFirst] -= scalar, View[SwizzleSecond] -= scalar, View[SwizzleThird] -= scalar);
		}

		constexpr CIN_MATH_INLINE VectorType operator*=(const Type scalar) noexcept
		{
			return VectorType(View[SwizzleFirst] *= scalar, View[SwizzleSecond] *= scalar, View[SwizzleThird] *= scalar);
		}

		constexpr CIN_MATH_INLINE VectorType operator=(const VectorType& vector) noexcept
		{
			return VectorType(View[SwizzleFirst] = vector.x, View[SwizzleSecond] = vector.y, View[SwizzleThird] = vector.z);
		}

		constexpr CIN_MATH_INLINE VectorType operator+=(const VectorType& vector) noexcept
		{
			return VectorType(View[SwizzleFirst] += vector.x, View[SwizzleSecond] += vector.y, View[SwizzleThird] += vector.z);
		}

		constexpr CIN_MATH_INLINE VectorType operator-=(const VectorType& vector) noexcept
		{
			return VectorType(View[SwizzleFirst] -= vector.x, View[SwizzleSecond] -= vector.y), View[SwizzleThird] -= vector.z;
		}

		constexpr CIN_MATH_INLINE VectorType operator*=(const VectorType& vector) noexcept
		{
			return VectorType(View[SwizzleFirst] *= vector.x, View[SwizzleSecond] *= vector.y, View[SwizzleThird] *= vector.z);
		}

		constexpr CIN_MATH_INLINE operator VectorType() const noexcept
		{
			return VectorType(View[SwizzleFirst], View[SwizzleSecond], View[SwizzleThird]);
		}
	};

	template<typename Type, typename VectorType, std::size_t SwizzleFirst, std::size_t SwizzleSecond, std::size_t SwizzleThird, std::size_t SwizzleFourth>
	struct Vector4Swizzle final
	{
		Type View[4];
	
		constexpr CIN_MATH_INLINE VectorType operator=(const Type scalar) const noexcept
		{
			return VectorType(View[SwizzleFirst] = scalar, View[SwizzleSecond] = scalar, View[SwizzleThird] = scalar, View[SwizzleFourth] = scalar);
		}
		
		constexpr CIN_MATH_INLINE VectorType operator+(const Type scalar) const noexcept
		{
			return VectorType(View[SwizzleFirst] + scalar, View[SwizzleSecond] + scalar, View[SwizzleThird] + scalar, View[SwizzleFourth] + scalar);
		}
		
		constexpr CIN_MATH_INLINE VectorType operator-(const Type scalar) const noexcept
		{
			return VectorType(View[SwizzleFirst] - scalar, View[SwizzleSecond] - scalar, View[SwizzleThird] - scalar, View[SwizzleFourth] - scalar);
		}
		
		constexpr CIN_MATH_INLINE VectorType operator*(const Type scalar) const noexcept
		{
			return VectorType(View[SwizzleFirst] * scalar, View[SwizzleSecond] * scalar, View[SwizzleThird] * scalar, View[SwizzleFourth] * scalar);
		}
		
		constexpr CIN_MATH_INLINE VectorType operator+=(const Type scalar) noexcept
		{
			return VectorType(View[SwizzleFirst] += scalar, View[SwizzleSecond] += scalar, View[SwizzleThird] += scalar, View[SwizzleFourth] += scalar);
		}
		
		constexpr CIN_MATH_INLINE VectorType operator-=(const Type scalar) noexcept
		{
			return VectorType(View[SwizzleFirst] -= scalar, View[SwizzleSecond] -= scalar, View[SwizzleThird] -= scalar, View[SwizzleFourth] -= scalar);
		}
		
		constexpr CIN_MATH_INLINE VectorType operator*=(const Type scalar) noexcept
		{
			return VectorType(View[SwizzleFirst] *= scalar, View[SwizzleSecond] *= scalar, View[SwizzleThird] *= scalar, View[SwizzleFourth] *= scalar);
		}
		
		constexpr CIN_MATH_INLINE VectorType operator=(const VectorType& vector) noexcept
		{
			return VectorType(View[SwizzleFirst] = vector.x, View[SwizzleSecond] = vector.y, View[SwizzleThird] = vector.z, View[SwizzleFourth] = vector.w);
		}
		
		constexpr CIN_MATH_INLINE VectorType operator+=(const VectorType& vector) noexcept
		{
			return VectorType(View[SwizzleFirst] += vector.x, View[SwizzleSecond] += vector.y, View[SwizzleThird] += vector.z, View[SwizzleFourth] += vector.w);
		}
		
		constexpr CIN_MATH_INLINE VectorType operator-=(const VectorType& vector) noexcept
		{
			return VectorType(View[SwizzleFirst] -= vector.x, View[SwizzleSecond] -= vector.y, View[SwizzleThird] -= vector.z, View[SwizzleFourth] -= vector.w);
		}
		
		constexpr CIN_MATH_INLINE VectorType operator*=(const VectorType& vector) noexcept
		{
			return VectorType(View[SwizzleFirst] *= vector.x, View[SwizzleSecond] *= vector.y, View[SwizzleThird] *= vector.z, View[SwizzleFourth] *= vector.w);
		}
		
		constexpr CIN_MATH_INLINE operator VectorType() const noexcept
		{
			return VectorType(View[SwizzleFirst], View[SwizzleSecond], View[SwizzleThird], View[SwizzleFourth]);
		}
	};
#if _MSC_VER
#pragma warning(pop)
#elif __GNUC__
#pragma GCC diagnostic pop
#elif __clang__
#pragma clang diagnostic pop
#endif
	/* Template type parameters */
	typedef float DefaultPrecision;
	typedef double DoublePrecision;

	typedef std::size_t Rows_t;
	typedef std::size_t Columns_t;
	typedef std::size_t Length_t;

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

	typedef double CinnamonFloat64Matrix2x2_t[2 * 2];
	typedef double CinnamonFloat64Matrix3x3_t[3 * 3];
	typedef double CinnamonFloat64Matrix4x4_t[4 * 4];
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

	typedef double CinnamonFloat64Matrix2x2_t[2 * 2];
	typedef double CinnamonFloat64Matrix3x3_t[3 * 3];
	typedef double CinnamonFloat64Matrix4x4_t[4 * 4];
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

	typedef double CinnamonFloat64Matrix2x2_t[2 * 2];
	typedef double CinnamonFloat64Matrix3x3_t[3 * 3];
	typedef double CinnamonFloat64Matrix4x4_t[4 * 4];
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

	typedef double CinnamonFloat64Matrix2x2_t[2 * 2];
	typedef double CinnamonFloat64Matrix3x3_t[3 * 3];
	typedef double CinnamonFloat64Matrix4x4_t[4 * 4];
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

	/* Matrix 2x2 */
	template<>
	struct MatrixStorage<2, 2, double> final
	{
		typedef CinnamonFloat64Matrix2x2_t Container;
	};

	/* Matrix 3x3 */
	template<>
	struct MatrixStorage<3, 3, double> final
	{
		typedef CinnamonFloat64Matrix3x3_t Container;
	};

	/* Matrix 4x4 */
	template<>
	struct MatrixStorage<4, 4, double> final
	{
		typedef CinnamonFloat64Matrix4x4_t Container;
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

#include "Angle.h"
#include "Quaternion.h"

#include "Transform.h"

/* Inline headers */
#include "Vector2.inl"
#include "Vector3.inl"
#include "Vector4.inl"

#include "Matrix2.inl"
#include "Matrix3.inl"
#include "Matrix4.inl"

#include "Angle.inl"
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
#include <iomanip> 		/* for std::setw */
#include <string_view>	

namespace CinMath
{
	namespace Printing
	{
		struct DefaultVectorPrintSpecificer
		{
			static constexpr char Opening()	noexcept { return static_cast<char>('['); }
			static constexpr char Closing()	noexcept { return static_cast<char>(']'); }
		};

		struct RoundVectorPrintSpecificer
		{
			static constexpr char Opening()	noexcept { return static_cast<char>('('); }
			static constexpr char Closing()	noexcept { return static_cast<char>(')'); }
		};

		struct CurlyVectorPrintSpecificer
		{
			static constexpr char Opening()	noexcept { return static_cast<char>('{'); }
			static constexpr char Closing()	noexcept { return static_cast<char>('}'); }
		};

		template<typename VectorType, typename VectorPrintSpecificer = DefaultVectorPrintSpecificer>
		struct VectorPrinter
		{
			constexpr VectorPrinter(const VectorType& reference, [[maybe_unused]] const VectorPrintSpecificer) noexcept
				:
				Reference(reference),
				Opening(VectorPrintSpecificer::Opening()),
				Closing(VectorPrintSpecificer::Closing())
			{}

			const VectorType& Reference;
			const char Opening;
			const char Closing;
		};

		struct DefaultMatrixPrintSpecificer
		{
#ifdef _MSC_VER
			static constexpr char UpwardsColumnFacingLeft()		noexcept { return static_cast<char>(0xDA); }
			static constexpr char DownwardsColumnFacingLeft()	noexcept { return static_cast<char>(0xC0); }
			static constexpr char UpwardsColumnFacingRight()	noexcept { return static_cast<char>(0xBF); }
			static constexpr char DownwardsColumnFacingRight()	noexcept { return static_cast<char>(0xD9); }
			static constexpr char Row()							noexcept { return static_cast<char>(0xB3); }
#else
			static constexpr char UpwardsColumnFacingLeft()		noexcept { return static_cast<char>(' '); }
			static constexpr char DownwardsColumnFacingLeft()	noexcept { return static_cast<char>(' '); }
			static constexpr char UpwardsColumnFacingRight()	noexcept { return static_cast<char>(' '); }
			static constexpr char DownwardsColumnFacingRight()	noexcept { return static_cast<char>(' '); }
			static constexpr char Row()							noexcept { return static_cast<char>('|'); }
#endif
		};

		struct ThickMatrixPrintSpecificer
		{
			static constexpr char UpwardsColumnFacingLeft()		noexcept { return static_cast<char>(0xC9); }
			static constexpr char DownwardsColumnFacingLeft()	noexcept { return static_cast<char>(0xC8); }
			static constexpr char UpwardsColumnFacingRight()	noexcept { return static_cast<char>(0xBB); }
			static constexpr char DownwardsColumnFacingRight()	noexcept { return static_cast<char>(0xBC); }
			static constexpr char Row()							noexcept { return static_cast<char>(0xBA); }
		};

		struct NakedMatrixPrintSpecificer
		{
			static constexpr char UpwardsColumnFacingLeft()		noexcept { return static_cast<char>(' '); }
			static constexpr char DownwardsColumnFacingLeft()	noexcept { return static_cast<char>(' '); }
			static constexpr char UpwardsColumnFacingRight()	noexcept { return static_cast<char>(' '); }
			static constexpr char DownwardsColumnFacingRight()	noexcept { return static_cast<char>(' '); }
			static constexpr char Row()							noexcept { return static_cast<char>(' '); }
		};

		template<typename MatrixType, typename MatrixPrintSpecificer = DefaultMatrixPrintSpecificer>
		struct MatrixPrinter
		{
			constexpr MatrixPrinter(const MatrixType& reference, [[maybe_unused]] const MatrixPrintSpecificer) noexcept
				:
				Reference(reference),
				UpwardsColumnFacingLeft(MatrixPrintSpecificer::UpwardsColumnFacingLeft()),
				DownwardsColumnFacingLeft(MatrixPrintSpecificer::DownwardsColumnFacingLeft()),
				UpwardsColumnFacingRight(MatrixPrintSpecificer::UpwardsColumnFacingRight()),
				DownwardsColumnFacingRight(MatrixPrintSpecificer::DownwardsColumnFacingRight())
			{}

			const MatrixType& Reference;
			const char UpwardsColumnFacingLeft;
			const char DownwardsColumnFacingLeft;
			const char UpwardsColumnFacingRight;
			const char DownwardsColumnFacingRight;
		};

		inline void SimplifyRealNumber(std::string& outNumber) noexcept
		{
			outNumber.erase(outNumber.find_last_not_of('0') + 1, std::string::npos);

			if(outNumber.back() == '.')
				outNumber.pop_back();
		}

		struct FloatingPointNumberRepresantationSize
		{
			size_t WholeNumberPartLength;
			/* Separator (.) included */
			size_t FractionNumberPartLength;
		
			static inline FloatingPointNumberRepresantationSize Calculate(const std::string_view number) noexcept
			{
				const std::string_view wholeNumberPart{ number.substr(0, number.find_first_of('.')) };
				const std::string_view fractionPart{ number.substr(wholeNumberPart.size()) };
		
				return FloatingPointNumberRepresantationSize{ wholeNumberPart.size(), fractionPart.size() };
			}
		};

		template<typename ValueType>
		FloatingPointNumberRepresantationSize FindMaxWholeAndFractionPartSizes(const ValueType* begin, const ValueType* end)
		{
			FloatingPointNumberRepresantationSize max{ 0, 0 };
			while(begin != end)
			{
				std::string number{ std::to_string(*begin) };
				SimplifyRealNumber(number);

				FloatingPointNumberRepresantationSize current{ FloatingPointNumberRepresantationSize::Calculate(number) };
				if(current.WholeNumberPartLength > max.WholeNumberPartLength)
					max.WholeNumberPartLength = current.WholeNumberPartLength;

				if(current.FractionNumberPartLength > max.FractionNumberPartLength)
					max.FractionNumberPartLength = current.FractionNumberPartLength;

				++begin;
			}

			return max;
		}
	}
}

template<typename ValueType, typename PrintSpecifier = CinMath::Printing::DefaultVectorPrintSpecificer>
CIN_MATH_INLINE std::ostream& operator<<(std::ostream& stream, const CinMath::Printing::VectorPrinter<CinMath::Vector<4, ValueType>, PrintSpecifier>& printer) noexcept
{
	const CinMath::Vector<4, ValueType>& vector{ printer.Reference };
	stream << PrintSpecifier::Opening() << vector.raw[0] << ", " << vector.raw[1] << ", " << vector.raw[2] << ", " << vector.raw[3]  << PrintSpecifier::Closing() << '\n';
	return stream;
}

template<typename ValueType, typename PrintSpecifier = CinMath::Printing::DefaultVectorPrintSpecificer>
CIN_MATH_INLINE std::ostream& operator<<(std::ostream& stream, const CinMath::Printing::VectorPrinter<CinMath::Vector<3, ValueType>, PrintSpecifier>& printer) noexcept
{
	const CinMath::Vector<3, ValueType>& vector{ printer.Reference };
	stream << PrintSpecifier::Opening() << vector.raw[0] << ", " << vector.raw[1] << ", " << vector.raw[2] << PrintSpecifier::Closing() << '\n';
	return stream;
}

template<typename ValueType, typename PrintSpecifier = CinMath::Printing::DefaultVectorPrintSpecificer>
CIN_MATH_INLINE std::ostream& operator<<(std::ostream& stream, const CinMath::Printing::VectorPrinter<CinMath::Vector<2, ValueType>, PrintSpecifier>& printer) noexcept
{
	const CinMath::Vector<2, ValueType>& vector{ printer.Reference };
	stream << PrintSpecifier::Opening() << vector.raw[0] << ", " << vector.raw[1] << PrintSpecifier::Closing() << '\n';
	return stream;
}

template<typename ValueType, typename PrintSpecifier = CinMath::Printing::DefaultMatrixPrintSpecificer>
CIN_MATH_INLINE std::ostream& operator<<(std::ostream& stream, const CinMath::Printing::MatrixPrinter<CinMath::Matrix<2, 2, ValueType>, PrintSpecifier>& printer) noexcept
{
	const CinMath::Matrix<2, 2, ValueType>& matrix{ printer.Reference };
	const auto max{ CinMath::Printing::FindMaxWholeAndFractionPartSizes(&matrix.m11, &matrix.m22) };
	const size_t width{ (max.WholeNumberPartLength + 1) + (max.FractionNumberPartLength ? max.FractionNumberPartLength + 1 : 0) };

	std::stringstream output;
	output << '\n' << std::fixed << std::setprecision(max.FractionNumberPartLength) 
		<< PrintSpecifier::UpwardsColumnFacingLeft() << std::setw(width * 2 + 1) << ' ' << PrintSpecifier::UpwardsColumnFacingRight() 	   << '\n'
		<< PrintSpecifier::Row() << std::setw(width) << matrix[0]  << std::setw(width) << matrix[1] << ' ' << PrintSpecifier::Row() 	   << '\n'
		<< PrintSpecifier::Row() << std::setw(width) << matrix[2]  << std::setw(width) << matrix[3] << ' ' << PrintSpecifier::Row() 	   << '\n'
		<< PrintSpecifier::DownwardsColumnFacingLeft() << std::setw(width * 2 + 1) << ' ' << PrintSpecifier::DownwardsColumnFacingRight()  << '\n';

	return stream << output.str();
}

template<typename ValueType, typename PrintSpecifier = CinMath::Printing::DefaultMatrixPrintSpecificer>
CIN_MATH_INLINE std::ostream& operator<<(std::ostream& stream, const CinMath::Printing::MatrixPrinter<CinMath::Matrix<3, 3, ValueType>, PrintSpecifier>& printer) noexcept
{
	const CinMath::Matrix<3, 3, ValueType>& matrix{ printer.Reference };
	const auto max{ CinMath::Printing::FindMaxWholeAndFractionPartSizes(&matrix.m11, &matrix.m33) };
	const size_t width{ (max.WholeNumberPartLength + 1) + (max.FractionNumberPartLength ? max.FractionNumberPartLength + 1 : 0) };

	std::stringstream output;
	output << '\n' << std::fixed << std::setprecision(max.FractionNumberPartLength) 
		<< PrintSpecifier::UpwardsColumnFacingLeft() << std::setw(width * 3 + 1) << ' ' << PrintSpecifier::UpwardsColumnFacingRight() << '\n'
		<< PrintSpecifier::Row() << std::setw(width) << matrix[0]  << std::setw(width) << matrix[1]  << std::setw(width) << matrix[2] << ' ' << PrintSpecifier::Row() << '\n'
		<< PrintSpecifier::Row() << std::setw(width) << matrix[3]  << std::setw(width) << matrix[4]  << std::setw(width) << matrix[5] << ' ' << PrintSpecifier::Row() << '\n'
		<< PrintSpecifier::Row() << std::setw(width) << matrix[6]  << std::setw(width) << matrix[7]  << std::setw(width) << matrix[8] << ' ' << PrintSpecifier::Row() << '\n'
		<< PrintSpecifier::DownwardsColumnFacingLeft() << std::setw(width * 3 + 1) << ' ' << PrintSpecifier::DownwardsColumnFacingRight() << '\n';

	return stream << output.str();
}

template<typename ValueType, typename PrintSpecifier = CinMath::Printing::DefaultMatrixPrintSpecificer>
CIN_MATH_INLINE std::ostream& operator<<(std::ostream& stream, const CinMath::Printing::MatrixPrinter<CinMath::Matrix<4, 4, ValueType>, PrintSpecifier>& printer) noexcept
{
	const CinMath::Matrix<4, 4, ValueType>& matrix{ printer.Reference };
	const auto max{ CinMath::Printing::FindMaxWholeAndFractionPartSizes(&matrix.m11, &matrix.m44) };
	const size_t width{ (max.WholeNumberPartLength + 1) + (max.FractionNumberPartLength ? max.FractionNumberPartLength + 1 : 0) };

	std::stringstream output;
	output << '\n' << std::fixed << std::setprecision(max.FractionNumberPartLength) 
		<< PrintSpecifier::UpwardsColumnFacingLeft() << std::setw(width * 4 + 1) << ' ' << PrintSpecifier::UpwardsColumnFacingRight() << '\n'
		<< PrintSpecifier::Row() << std::setw(width) << matrix[0]  << std::setw(width) << matrix[1]  << std::setw(width) << matrix[2]  << std::setw(width) << matrix[3]  << ' ' << PrintSpecifier::Row() << '\n'
		<< PrintSpecifier::Row() << std::setw(width) << matrix[4]  << std::setw(width) << matrix[5]  << std::setw(width) << matrix[6]  << std::setw(width) << matrix[7]  << ' ' << PrintSpecifier::Row() << '\n'
		<< PrintSpecifier::Row() << std::setw(width) << matrix[8]  << std::setw(width) << matrix[9]  << std::setw(width) << matrix[10] << std::setw(width) << matrix[11] << ' ' << PrintSpecifier::Row() << '\n'
		<< PrintSpecifier::Row() << std::setw(width) << matrix[12] << std::setw(width) << matrix[13] << std::setw(width) << matrix[14] << std::setw(width) << matrix[15] << ' ' << PrintSpecifier::Row() << '\n'
		<< PrintSpecifier::DownwardsColumnFacingLeft() << std::setw(width * 4 + 1) << ' ' << PrintSpecifier::DownwardsColumnFacingRight() << '\n';

	return stream << output.str();
}

template<CinMath::Length_t length, typename ValueType>
CIN_MATH_INLINE std::ostream& operator<<(std::ostream& stream, const CinMath::Vector<length, ValueType>& vector) noexcept
{
	stream << CinMath::Printing::VectorPrinter(vector, CinMath::Printing::DefaultVectorPrintSpecificer());
	return stream;
}

template<typename ValueType, typename VectorType, std::size_t SwizzleFirst, std::size_t SwizzleSecond>
CIN_MATH_INLINE std::ostream& operator<<(std::ostream& stream, const CinMath::Vector2Swizzle<ValueType, VectorType, SwizzleFirst, SwizzleSecond>& swizzle) noexcept
{
	stream << '[' << swizzle.View[0] << ", " << swizzle.View[1] << ']' << '\n';
	return stream;
}

template<typename ValueType, typename VectorType, std::size_t SwizzleFirst, std::size_t SwizzleSecond, std::size_t SwizzleThird>
CIN_MATH_INLINE std::ostream& operator<<(std::ostream& stream, const CinMath::Vector3Swizzle<ValueType, VectorType, SwizzleFirst, SwizzleSecond, SwizzleThird>& swizzle) noexcept
{
	stream << '[' << swizzle.View[0] << ", " << swizzle.View[1] << ", " << swizzle.View[2] << ']' << '\n';
	return stream;
}

template<typename ValueType, typename VectorType, std::size_t SwizzleFirst, std::size_t SwizzleSecond, std::size_t SwizzleThird, std::size_t SwizzleFourth>
CIN_MATH_INLINE std::ostream& operator<<(std::ostream& stream, const CinMath::Vector4Swizzle<ValueType, VectorType, SwizzleFirst, SwizzleSecond, SwizzleThird, SwizzleFourth>& swizzle) noexcept
{
	stream << '[' << swizzle.View[0] << ", " << swizzle.View[1] << ", " << swizzle.View[2] << ", " << swizzle.View[3] << ']' << '\n';
	return stream;
}

template<CinMath::Length_t rows, CinMath::Length_t columns, typename ValueType>
CIN_MATH_INLINE std::ostream& operator<<(std::ostream& stream, const CinMath::Matrix<rows, columns, ValueType>& matrix) noexcept
{
	stream << CinMath::Printing::MatrixPrinter(matrix, CinMath::Printing::DefaultMatrixPrintSpecificer());
	return stream;
}

template<typename ValueType>
CIN_MATH_INLINE std::ostream& operator<<(std::ostream& stream, const CinMath::TQuaternion<ValueType>& quaternion)
{
	stream << "[" << quaternion.raw[0] << ", (" << quaternion.raw[1] << "i, " << quaternion.raw[2] << "j, " << quaternion.raw[3] << "k)]\n";
	return stream;
}