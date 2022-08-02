#pragma once

namespace CinMath {
	CIN_MATH_INLINE Vector<4, float> CIN_CALL operator+(const Vector<4, float>& vector) noexcept
	{
		return vector;
	}

	CIN_MATH_INLINE Vector<4, float> CIN_CALL operator-(const Vector<4, float>& vector) noexcept
	{
		Vector<4, float> result;
#if (CIN_INSTRUCTION_SET) & (CIN_INSTRUCTION_SET_SSE_BIT)
		result.data = _mm_mul_ps(vector.data, AtCompileTime(__m128{ -1.0f, -1.0f, -1.0f, -1.0f}));
#else
		result.raw[0] = -vector.raw[0];
		result.raw[1] = -vector.raw[1];
		result.raw[2] = -vector.raw[2];
		result.raw[3] = -vector.raw[3];
#endif
		return result;
	}

	CIN_MATH_INLINE void CIN_CALL operator+=(Vector<4, float>& lhs, const Vector<4, float>& rhs) noexcept
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

	CIN_MATH_INLINE void CIN_CALL operator-=(Vector<4, float>& lhs, const Vector<4, float>& rhs) noexcept
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

	CIN_MATH_INLINE void CIN_CALL operator*=(Vector<4, float>& lhs, const Vector<4, float>& rhs) noexcept
	{
#if (CIN_INSTRUCTION_SET) & (CIN_INSTRUCTION_SET_SSE_BIT)
		lhs.data = _mm_mul_ps(lhs.data, rhs.data);
#else
		lhs.raw[0] *= rhs.raw[0];
		lhs.raw[1] *= rhs.raw[1];
		lhs.raw[2] *= rhs.raw[2];
		lhs.raw[3] *= rhs.raw[3];
#endif
	}

	CIN_MATH_INLINE void CIN_CALL operator/=(Vector<4, float>& lhs, const Vector<4, float>& rhs) noexcept
	{
#if (CIN_INSTRUCTION_SET) & (CIN_INSTRUCTION_SET_SSE_BIT)
		lhs.data = _mm_div_ps(lhs.data, rhs.data);
#else
		lhs.raw[0] /= rhs.raw[0];
		lhs.raw[1] /= rhs.raw[1];
		lhs.raw[2] /= rhs.raw[2];
		lhs.raw[3] /= rhs.raw[3];
#endif
	}

	CIN_MATH_INLINE void CIN_CALL operator+=(Vector<4, float>& lhs, const float rhs) noexcept
	{
#if (CIN_INSTRUCTION_SET) & (CIN_INSTRUCTION_SET_SSE_BIT)
		lhs.data = _mm_add_ps(lhs.data, __m128{ rhs, rhs, rhs, rhs});
#else
		lhs.raw[0] += rhs;
		lhs.raw[1] += rhs;
		lhs.raw[2] += rhs;
		lhs.raw[3] += rhs;
#endif
	}

	CIN_MATH_INLINE void CIN_CALL operator-=(Vector<4, float>& lhs, const float rhs) noexcept
	{
#if (CIN_INSTRUCTION_SET) & (CIN_INSTRUCTION_SET_SSE_BIT)
		lhs.data = _mm_sub_ps(lhs.data, __m128{ rhs, rhs, rhs, rhs});
#else
		lhs.raw[0] -= rhs;
		lhs.raw[1] -= rhs;
		lhs.raw[2] -= rhs;
		lhs.raw[3] -= rhs;
#endif
	}

	CIN_MATH_INLINE void CIN_CALL operator*=(Vector<4, float>& lhs, const float rhs) noexcept
	{
#if (CIN_INSTRUCTION_SET) & (CIN_INSTRUCTION_SET_SSE_BIT)
		lhs.data = _mm_mul_ps(lhs.data, __m128{ rhs, rhs, rhs, rhs});
#else
		lhs.raw[0] *= rhs;
		lhs.raw[1] *= rhs;
		lhs.raw[2] *= rhs;
		lhs.raw[3] *= rhs;
#endif
	}

	CIN_MATH_INLINE void CIN_CALL operator/=(Vector<4, float>& lhs, const float rhs) noexcept
	{
#if (CIN_INSTRUCTION_SET) & (CIN_INSTRUCTION_SET_SSE_BIT)
		lhs.data = _mm_div_ps(lhs.data, __m128{ rhs, rhs, rhs, rhs});
#else
		lhs.raw[0] /= rhs;
		lhs.raw[1] /= rhs;
		lhs.raw[2] /= rhs;
		lhs.raw[3] /= rhs;
#endif
	}

	CIN_MATH_INLINE Vector<4, float> CIN_CALL operator+(const Vector<4, float>& lhs, const Vector<4, float>& rhs) noexcept
	{
		Vector<4, float> result;
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

	CIN_MATH_INLINE Vector<4, float> CIN_CALL operator-(const Vector<4, float>& lhs, const Vector<4, float>& rhs) noexcept
	{
		Vector<4, float> result;
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

	CIN_MATH_INLINE Vector<4, float> CIN_CALL operator*(const Vector<4, float>& lhs, const Vector<4, float>& rhs) noexcept
	{
		Vector<4, float> result;
#if (CIN_INSTRUCTION_SET) & (CIN_INSTRUCTION_SET_SSE_BIT)
		result.data = _mm_mul_ps(lhs.data, rhs.data);
#else
		result.raw[0] = lhs.raw[0] * rhs.raw[0];
		result.raw[1] = lhs.raw[1] * rhs.raw[1];
		result.raw[2] = lhs.raw[2] * rhs.raw[2];
		result.raw[3] = lhs.raw[3] * rhs.raw[3];
#endif
		return result;
	}

	CIN_MATH_INLINE Vector<4, float> CIN_CALL operator/(const Vector<4, float>& lhs, const Vector<4, float>& rhs) noexcept
	{
		Vector<4, float> result;
#if (CIN_INSTRUCTION_SET) & (CIN_INSTRUCTION_SET_SSE_BIT)
		result.data = _mm_div_ps(lhs.data, rhs.data);
#else
		result.raw[0] = lhs.raw[0] / rhs.raw[0];
		result.raw[1] = lhs.raw[1] / rhs.raw[1];
		result.raw[2] = lhs.raw[2] / rhs.raw[2];
		result.raw[3] = lhs.raw[3] / rhs.raw[3];
#endif
		return result;
	}

	CIN_MATH_INLINE Vector<4, float> CIN_CALL operator+(const Vector<4, float>& lhs, const float rhs) noexcept
	{
		Vector<4, float> result;
#if (CIN_INSTRUCTION_SET) & (CIN_INSTRUCTION_SET_SSE_BIT)
		result.data = _mm_add_ps(lhs.data, __m128{ rhs, rhs, rhs, rhs});
#else
		result.raw[0] = lhs.raw[0] + rhs;
		result.raw[1] = lhs.raw[1] + rhs;
		result.raw[2] = lhs.raw[2] + rhs;
		result.raw[3] = lhs.raw[3] + rhs;
#endif
		return result;
	}

	CIN_MATH_INLINE Vector<4, float> CIN_CALL operator-(const Vector<4, float>& lhs, const float rhs) noexcept
	{
		Vector<4, float> result;
#if (CIN_INSTRUCTION_SET) & (CIN_INSTRUCTION_SET_SSE_BIT)
		result.data = _mm_sub_ps(lhs.data, __m128{ rhs, rhs, rhs, rhs});
#else
		result.raw[0] = lhs.raw[0] - rhs;
		result.raw[1] = lhs.raw[1] - rhs;
		result.raw[2] = lhs.raw[2] - rhs;
		result.raw[3] = lhs.raw[3] - rhs;
#endif
		return result;
	}

	CIN_MATH_INLINE Vector<4, float> CIN_CALL operator*(const Vector<4, float>& lhs, const float rhs) noexcept
	{
		Vector<4, float> result;
#if (CIN_INSTRUCTION_SET) & (CIN_INSTRUCTION_SET_SSE_BIT)
		result.data = _mm_mul_ps(lhs.data, __m128{ rhs, rhs, rhs, rhs});
#else
		result.raw[0] = lhs.raw[0] * rhs;
		result.raw[1] = lhs.raw[1] * rhs;
		result.raw[2] = lhs.raw[2] * rhs;
		result.raw[3] = lhs.raw[3] * rhs;
#endif
		return result;
	}

	CIN_MATH_INLINE Vector<4, float> CIN_CALL operator/(const Vector<4, float>& lhs, const float rhs) noexcept
	{
		Vector<4, float> result;
#if (CIN_INSTRUCTION_SET) & (CIN_INSTRUCTION_SET_SSE_BIT)
		result.data = _mm_div_ps(lhs.data, __m128{ rhs, rhs, rhs, rhs});
#else
		result.raw[0] = lhs.raw[0] / rhs;
		result.raw[1] = lhs.raw[1] / rhs;
		result.raw[2] = lhs.raw[2] / rhs;
		result.raw[3] = lhs.raw[3] / rhs;
#endif
		return result;
	}

	CIN_MATH_INLINE Vector<4, float> CIN_CALL operator*(const Vector<4, float>& lhs, const Matrix<4, 4, float>& rhs) noexcept
	{
		Vector<4, float> result;
#if (CIN_INSTRUCTION_SET) & (CIN_INSTRUCTION_SET_AVX_BIT)
		const __m256 vectorData{ _mm256_set_m128(lhs.data, lhs.data) };

		const __m256 xy_m256{ _mm256_mul_ps(rhs.data[0], vectorData) };
		const __m256 zw_m256{ _mm256_mul_ps(rhs.data[1], vectorData) };

		__m256 ha0{ _mm256_hadd_ps(xy_m256, zw_m256) };
		__m256 ha1{ _mm256_hadd_ps(zw_m256, xy_m256) };
		ha1 = _mm256_permute2f128_ps(ha1, ha1, 0x01);

		const __m256 ha2{ _mm256_hadd_ps(ha0, ha1) };
		__m128 vec{ _mm256_extractf128_ps(ha2, 0) };
		vec = _mm_shuffle_ps(vec, vec, _MM_SHUFFLE(2, 1, 3, 0));

		result.data = vec;
#elif (CIN_INSTRUCTION_SET) & (CIN_INSTRUCTION_SET_SSE_BIT)
		/* a_11 * b_11, a_12 * b_12, a_13 * b_13, a_14 * b_14 */
		const __m128 m0{ _mm_mul_ps(lhs.data, rhs.data[0]) };
		/* a_11 * b_21, a_12 * b_22, a_13 * b_23, a_14 * b_24 */
		const __m128 m1{ _mm_mul_ps(lhs.data, rhs.data[1]) };
		/* a_11 * b_31, a_12 * b_32, a_13 * b_33, a_14 * b_34 */
		const __m128 m2{ _mm_mul_ps(lhs.data, rhs.data[2]) };
		/* a_11 * b_41, a_12 * b_42, a_13 * b_43, a_14 * b_44 */
		const __m128 m3{ _mm_mul_ps(lhs.data, rhs.data[3]) };

		__m128 a0{ _mm_add_ps(_mm_shuffle_ps(m0, m1, 0b10'00'10'00), _mm_shuffle_ps(m0, m1, 0b11'01'11'01)) };
		__m128 a1{ _mm_add_ps(_mm_shuffle_ps(m2, m3, 0b10'00'10'00), _mm_shuffle_ps(m2, m3, 0b11'01'11'01)) };

		result.data = _mm_add_ps(_mm_shuffle_ps(a0, a1, 0b10'00'10'00), _mm_shuffle_ps(a0, a1, 0b11'01'11'01));
#else
		result.raw[0] = lhs[0] * rhs[0] + lhs[1] * rhs[1] + lhs[2] * rhs[2] + lhs[3] * rhs[3];
		result.raw[1] = lhs[0] * rhs[4] + lhs[1] * rhs[5] + lhs[2] * rhs[6] + lhs[3] * rhs[7];
		result.raw[2] = lhs[0] * rhs[8] + lhs[1] * rhs[9] + lhs[2] * rhs[10] + lhs[3] * rhs[11];
		result.raw[3] = lhs[0] * rhs[12] + lhs[1] * rhs[13] + lhs[2] * rhs[14] + lhs[3] * rhs[15];
#endif
		return result;
	}
}