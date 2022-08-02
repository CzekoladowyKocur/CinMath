#pragma once

namespace CinMath {
	CIN_MATH_INLINE Matrix<2, 2, float> CIN_CALL operator+(const Matrix<2, 2, float>& matrix) noexcept
	{
		return matrix;
	}

	CIN_MATH_INLINE Matrix<2, 2, float> CIN_CALL operator-(const Matrix<2, 2, float>& matrix) noexcept
	{
		Matrix<2, 2, float> result;
#if (CIN_INSTRUCTION_SET) & (CIN_INSTRUCTION_SET_SSE_BIT)
		result.data = _mm_mul_ps(matrix.data, AtCompileTime(__m128{ -1.0f, -1.0f, -1.0f, -1.0f}));
#else
		result.raw[0] = -matrix.raw[0];
		result.raw[1] = -matrix.raw[1];
		result.raw[2] = -matrix.raw[2];
		result.raw[3] = -matrix.raw[3];
#endif
		return result;
	}

	CIN_MATH_INLINE void CIN_CALL operator+=(Matrix<2, 2, float>& lhs, const Matrix<2, 2, float>& rhs) noexcept
	{
#if (CIN_INSTRUCTION_SET) & (CIN_INSTRUCTION_SET_SSE_BIT)
		lhs.data = _mm_add_ps(lhs.data, rhs.data);
#else
		lhs.raw[0] += rhs.raw[0];
		lhs.raw[1] += rhs.raw[1];
		lhs.raw[2] += rhs.raw[2];
		lhs.raw[3] += rhs.raw[3];
#endif
	}

	CIN_MATH_INLINE void CIN_CALL operator-=(Matrix<2, 2, float>& lhs, const Matrix<2, 2, float>& rhs) noexcept
	{
#if (CIN_INSTRUCTION_SET) & (CIN_INSTRUCTION_SET_SSE_BIT)
		lhs.data = _mm_sub_ps(lhs.data, rhs.data);
#else
		lhs.raw[0] -= rhs.raw[0];
		lhs.raw[1] -= rhs.raw[1];
		lhs.raw[2] -= rhs.raw[2];
		lhs.raw[3] -= rhs.raw[3];
#endif
	}

	CIN_MATH_INLINE void CIN_CALL operator*=(Matrix<2, 2, float>& lhs, const Matrix<2, 2, float>& rhs) noexcept
	{
#if (CIN_INSTRUCTION_SET) & (CIN_INSTRUCTION_SET_SSE_BIT)
		const __m128 e0{ _mm_shuffle_ps(rhs.data, rhs.data, 0b11'11'00'00) };
		const __m128 e1{ _mm_shuffle_ps(rhs.data, rhs.data, 0b01'01'10'10) };

		const __m128 m0{ _mm_mul_ps(lhs.data, e0) };
		const __m128 m1{ _mm_mul_ps(lhs.data, e1) };

		lhs.data = _mm_add_ps(m0, _mm_shuffle_ps(m1, m1, 0b01'00'11'10));;
#else
		Matrix<2, 2, float> result;
		
		result.raw[0] = lhs.raw[0] * rhs.raw[0] + lhs.raw[2] * rhs.raw[1];
		result.raw[1] = lhs.raw[1] * rhs.raw[0] + lhs.raw[3] * rhs.raw[1];
		result.raw[2] = lhs.raw[0] * rhs.raw[2] + lhs.raw[2] * rhs.raw[3];
		result.raw[3] = lhs.raw[1] * rhs.raw[2] + lhs.raw[3] * rhs.raw[3];
		
		lhs = result;
#endif
	}

	CIN_MATH_INLINE void CIN_CALL operator+=(Matrix<2, 2, float>& lhs, const float rhs) noexcept
	{
#if (CIN_INSTRUCTION_SET) & (CIN_INSTRUCTION_SET_SSE_BIT)
		lhs.data = _mm_add_ps(lhs.data, _mm_set_ps(rhs, rhs, rhs, rhs));
#else
		lhs.raw[0] += rhs;
		lhs.raw[1] += rhs;
		lhs.raw[2] += rhs;
		lhs.raw[3] += rhs;
#endif
	}

	CIN_MATH_INLINE void CIN_CALL operator-=(Matrix<2, 2, float>& lhs, const float rhs) noexcept
	{
#if (CIN_INSTRUCTION_SET) & (CIN_INSTRUCTION_SET_SSE_BIT)
		lhs.data = _mm_sub_ps(lhs.data, _mm_set_ps(rhs, rhs, rhs, rhs));
#else
		lhs.raw[0] -= rhs;
		lhs.raw[1] -= rhs;
		lhs.raw[2] -= rhs;
		lhs.raw[3] -= rhs;
#endif
	}

	CIN_MATH_INLINE void CIN_CALL operator*=(Matrix<2, 2, float>& lhs, const float rhs) noexcept
	{
#if (CIN_INSTRUCTION_SET) & (CIN_INSTRUCTION_SET_SSE_BIT)
		lhs.data = _mm_mul_ps(lhs.data, _mm_set_ps(rhs, rhs, rhs, rhs));
#else
		lhs.raw[0] *= rhs;
		lhs.raw[1] *= rhs;
		lhs.raw[2] *= rhs;
		lhs.raw[3] *= rhs;
#endif
	}

	CIN_MATH_INLINE void CIN_CALL operator/=(Matrix<2, 2, float>& lhs, const float rhs) noexcept
	{
#if (CIN_INSTRUCTION_SET) & (CIN_INSTRUCTION_SET_SSE_BIT)
		lhs.data = _mm_div_ps(lhs.data, _mm_set_ps(rhs, rhs, rhs, rhs));
#else
		lhs.raw[0] /= rhs;
		lhs.raw[1] /= rhs;
		lhs.raw[2] /= rhs;
		lhs.raw[3] /= rhs;
#endif
	}

	CIN_MATH_INLINE Matrix<2, 2, float> CIN_CALL operator+(const Matrix<2, 2, float>& lhs, const Matrix<2, 2, float>& rhs) noexcept
	{
		Matrix<2, 2, float> result;
#if (CIN_INSTRUCTION_SET) & (CIN_INSTRUCTION_SET_SSE_BIT)
		result.data = _mm_add_ps(lhs.data, rhs.data);
#else
		result.raw[0] = lhs.raw[0] + rhs.raw[0];
		result.raw[1] = lhs.raw[1] + rhs.raw[1];
		result.raw[2] = lhs.raw[2] + rhs.raw[2];
		result.raw[3] = lhs.raw[3] + rhs.raw[3];
#endif
		return result;
	}

	CIN_MATH_INLINE Matrix<2, 2, float> CIN_CALL operator-(const Matrix<2, 2, float>& lhs, const Matrix<2, 2, float>& rhs) noexcept
	{
		Matrix<2, 2, float> result;
#if (CIN_INSTRUCTION_SET) & (CIN_INSTRUCTION_SET_SSE_BIT)
		result.data = _mm_sub_ps(lhs.data, rhs.data);
#else
		result.raw[0] = lhs.raw[0] - rhs.raw[0];
		result.raw[1] = lhs.raw[1] - rhs.raw[1];
		result.raw[2] = lhs.raw[2] - rhs.raw[2];
		result.raw[3] = lhs.raw[3] - rhs.raw[3];
#endif
		return result;
	}

	CIN_MATH_INLINE Matrix<2, 2, float> CIN_CALL operator*(const Matrix<2, 2, float>& lhs, const Matrix<2, 2, float>& rhs) noexcept
	{
		Matrix<2, 2, float> result;
#if (CIN_INSTRUCTION_SET) & (CIN_INSTRUCTION_SET_SSE_BIT)
		const __m128 e0{ _mm_shuffle_ps(rhs.data, rhs.data, 0b11'11'00'00) };
		const __m128 e1{ _mm_shuffle_ps(rhs.data, rhs.data, 0b01'01'10'10) };

		const __m128 m0{ _mm_mul_ps(lhs.data, e0) };
		const __m128 m1{ _mm_mul_ps(lhs.data, e1) };

		result.data = _mm_add_ps(m0, _mm_shuffle_ps(m1, m1, 0b01'00'11'10));;
#else
		result.raw[0] = lhs.raw[0] * rhs.raw[0] + lhs.raw[2] * rhs.raw[1];
		result.raw[1] = lhs.raw[1] * rhs.raw[0] + lhs.raw[3] * rhs.raw[1];
		result.raw[2] = lhs.raw[0] * rhs.raw[2] + lhs.raw[2] * rhs.raw[3];
		result.raw[3] = lhs.raw[1] * rhs.raw[2] + lhs.raw[3] * rhs.raw[3];
#endif
		return result;
	}

	CIN_MATH_INLINE Matrix<2, 2, float> CIN_CALL operator+(const Matrix<2, 2, float>& lhs, const float rhs) noexcept
	{
		Matrix<2, 2, float> result;
#if (CIN_INSTRUCTION_SET) & (CIN_INSTRUCTION_SET_SSE_BIT)
		result.data = _mm_add_ps(lhs.data, __m128{ rhs, rhs, rhs, rhs });
#else
		result.raw[0] = lhs.raw[0] + rhs;
		result.raw[1] = lhs.raw[1] + rhs;
		result.raw[2] = lhs.raw[2] + rhs;
		result.raw[3] = lhs.raw[3] + rhs;
#endif
		return result;
	}

	CIN_MATH_INLINE Matrix<2, 2, float> CIN_CALL operator-(const Matrix<2, 2, float>& lhs, const float rhs) noexcept
	{
		Matrix<2, 2, float> result;
#if (CIN_INSTRUCTION_SET) & (CIN_INSTRUCTION_SET_SSE_BIT)
		result.data = _mm_sub_ps(lhs.data, __m128{ rhs, rhs, rhs, rhs });
#else
		result.raw[0] = lhs.raw[0] - rhs;
		result.raw[1] = lhs.raw[1] - rhs;
		result.raw[2] = lhs.raw[2] - rhs;
		result.raw[3] = lhs.raw[3] - rhs;
#endif
		return result;
	}

	CIN_MATH_INLINE Matrix<2, 2, float> CIN_CALL operator*(const Matrix<2, 2, float>& lhs, const float rhs) noexcept
	{
		Matrix<2, 2, float> result;
#if (CIN_INSTRUCTION_SET) & (CIN_INSTRUCTION_SET_SSE_BIT)
		result.data = _mm_mul_ps(lhs.data, __m128{ rhs, rhs, rhs, rhs });
#else
		result.raw[0] = lhs.raw[0] * rhs;
		result.raw[1] = lhs.raw[1] * rhs;
		result.raw[2] = lhs.raw[2] * rhs;
		result.raw[3] = lhs.raw[3] * rhs;
#endif
		return result;
	}

	CIN_MATH_INLINE Matrix<2, 2, float> CIN_CALL operator/(const Matrix<2, 2, float>& lhs, const float rhs) noexcept
	{
		Matrix<2, 2, float> result;
#if (CIN_INSTRUCTION_SET) & (CIN_INSTRUCTION_SET_SSE_BIT)
		result.data = _mm_div_ps(lhs.data, __m128{ rhs, rhs, rhs, rhs });
#else
		result.raw[0] = lhs.raw[0] / rhs;
		result.raw[1] = lhs.raw[1] / rhs;
		result.raw[2] = lhs.raw[2] / rhs;
		result.raw[3] = lhs.raw[3] / rhs;
#endif
		return result;
	}
}