#pragma once

namespace CinMath {
	CIN_MATH_INLINE Matrix<4, 4, float> CIN_CALL operator+(const Matrix<4, 4, float>& matrix) noexcept
	{
		return matrix;
	}

	CIN_MATH_INLINE Matrix<4, 4, float> CIN_CALL operator-(const Matrix<4, 4, float>& matrix) noexcept
	{
		Matrix<4, 4, float> result;
#if (CIN_INSTRUCTION_SET) & (CIN_INSTRUCTION_SET_AVX_BIT)
		result.data[0] = _mm256_mul_ps(matrix.data[0], AtCompileTime(__m256{ -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f}));
		result.data[1] = _mm256_mul_ps(matrix.data[1], AtCompileTime(__m256{ -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f}));
#elif (CIN_INSTRUCTION_SET) & (CIN_INSTRUCTION_SET_SSE_BIT)
		result.data[0] = _mm_mul_ps(matrix.data[0], AtCompileTime(__m128{ -1.0f, -1.0f, -1.0f, -1.0f}));
		result.data[1] = _mm_mul_ps(matrix.data[1], AtCompileTime(__m128{ -1.0f, -1.0f, -1.0f, -1.0f}));
		result.data[2] = _mm_mul_ps(matrix.data[2], AtCompileTime(__m128{ -1.0f, -1.0f, -1.0f, -1.0f}));
		result.data[3] = _mm_mul_ps(matrix.data[3], AtCompileTime(__m128{ -1.0f, -1.0f, -1.0f, -1.0f}));
#else
		result.raw[0] = -matrix.raw[0];
		result.raw[1] = -matrix.raw[1];
		result.raw[2] = -matrix.raw[2];
		result.raw[3] = -matrix.raw[3];

		result.raw[4] = -matrix.raw[4];
		result.raw[5] = -matrix.raw[5];
		result.raw[6] = -matrix.raw[6];
		result.raw[7] = -matrix.raw[7];

		result.raw[8] = -matrix.raw[8];
		result.raw[9] = -matrix.raw[9];
		result.raw[10] = -matrix.raw[10];
		result.raw[11] = -matrix.raw[11];

		result.raw[12] = -matrix.raw[12];
		result.raw[13] = -matrix.raw[13];
		result.raw[14] = -matrix.raw[14];
		result.raw[15] = -matrix.raw[15];
#endif
		return result;
	}

	CIN_MATH_INLINE void CIN_CALL operator+=(Matrix<4, 4, float>& lhs, const Matrix<4, 4, float>& rhs) noexcept
	{
#if (CIN_INSTRUCTION_SET) & (CIN_INSTRUCTION_SET_AVX_BIT)
		lhs.data[0] = _mm256_add_ps(lhs.data[0], rhs.data[0]);
		lhs.data[1] = _mm256_add_ps(lhs.data[1], rhs.data[1]);
#elif (CIN_INSTRUCTION_SET) & (CIN_INSTRUCTION_SET_SSE_BIT)
		lhs.data[0] = _mm_add_ps(lhs.data[0], rhs.data[0]);
		lhs.data[1] = _mm_add_ps(lhs.data[1], rhs.data[1]);
		lhs.data[2] = _mm_add_ps(lhs.data[2], rhs.data[2]);
		lhs.data[3] = _mm_add_ps(lhs.data[3], rhs.data[3]);
#else
		lhs.raw[0] += rhs.raw[0];
		lhs.raw[1] += rhs.raw[1];
		lhs.raw[2] += rhs.raw[2];
		lhs.raw[3] += rhs.raw[3];
		lhs.raw[4] += rhs.raw[4];
		lhs.raw[5] += rhs.raw[5];
		lhs.raw[6] += rhs.raw[6];
		lhs.raw[7] += rhs.raw[7];
		lhs.raw[8] += rhs.raw[8];
		lhs.raw[9] += rhs.raw[9];
		lhs.raw[10] += rhs.raw[10];
		lhs.raw[11] += rhs.raw[11];
		lhs.raw[12] += rhs.raw[12];
		lhs.raw[13] += rhs.raw[13];
		lhs.raw[14] += rhs.raw[14];
		lhs.raw[15] += rhs.raw[15];
#endif
	}

	CIN_MATH_INLINE void CIN_CALL operator-=(Matrix<4, 4, float>& lhs, const Matrix<4, 4, float>& rhs) noexcept
	{
#if (CIN_INSTRUCTION_SET) & (CIN_INSTRUCTION_SET_AVX_BIT)
		lhs.data[0] = _mm256_sub_ps(lhs.data[0], rhs.data[0]);
		lhs.data[1] = _mm256_sub_ps(lhs.data[1], rhs.data[1]);
#elif (CIN_INSTRUCTION_SET) & (CIN_INSTRUCTION_SET_SSE_BIT)
		lhs.data[0] = _mm_sub_ps(lhs.data[0], rhs.data[0]);
		lhs.data[1] = _mm_sub_ps(lhs.data[1], rhs.data[1]);
		lhs.data[2] = _mm_sub_ps(lhs.data[2], rhs.data[2]);
		lhs.data[3] = _mm_sub_ps(lhs.data[3], rhs.data[3]);
#else
		lhs.raw[0] -= rhs.raw[0];
		lhs.raw[1] -= rhs.raw[1];
		lhs.raw[2] -= rhs.raw[2];
		lhs.raw[3] -= rhs.raw[3];
		lhs.raw[4] -= rhs.raw[4];
		lhs.raw[5] -= rhs.raw[5];
		lhs.raw[6] -= rhs.raw[6];
		lhs.raw[7] -= rhs.raw[7];
		lhs.raw[8] -= rhs.raw[8];
		lhs.raw[9] -= rhs.raw[9];
		lhs.raw[10] -= rhs.raw[10];
		lhs.raw[11] -= rhs.raw[11];
		lhs.raw[12] -= rhs.raw[12];
		lhs.raw[13] -= rhs.raw[13];
		lhs.raw[14] -= rhs.raw[14];
		lhs.raw[15] -= rhs.raw[15];
#endif
	}

	CIN_MATH_INLINE void CIN_CALL operator*=(Matrix<4, 4, float>& lhs, const Matrix<4, 4, float>& rhs) noexcept
	{
		Matrix<4, 4, float> result;
#if (CIN_INSTRUCTION_SET) & (CIN_INSTRUCTION_SET_AVX_BIT)
		__m256 e0{ _mm256_permute_ps(rhs.data[0], 0b00'00'00'00) };
		__m256 e1{ _mm256_permute_ps(rhs.data[1], 0b00'00'00'00) };
		// a_11, a_12, a_13, a_14 | a_11, a_12, a_13, a_14
		const __m256 firstRowLHS{ _mm256_permute2f128_ps(lhs.data[0], lhs.data[0], 0x00) };

		// b_11(a_11, a_12, a_13, a_14 ) | b_21(a_11, a_12, a_13, a_14)
		__m256 m0{ _mm256_mul_ps(e0, firstRowLHS) };

		// b_31(a_11, a_12, a_13, a_14 ) | b_41(a_11, a_12, a_13, a_14)
		__m256 m1{ _mm256_mul_ps(e1, firstRowLHS) };

		// b_12, b_12, b_12, b_12 | b_22, b_22, b_22, b_22
		e0 = { _mm256_permute_ps(rhs.data[0], 0b01'01'01'01) };
		// b_32, b_32, b_32, b_32 | b_42, b_42, b_42, b_42
		e1 = { _mm256_permute_ps(rhs.data[1], 0b01'01'01'01) };

		// a_21, a_22, a_23, a_24 | a_21, a_22, a_23, a_24
		const __m256 secondRowLHS{ _mm256_permute2f128_ps(lhs.data[0], lhs.data[0], 0x11) };

		// b_12(a_21, a_22, a_23, a_24 ) | b_22(a_21, a_22, a_23, a_24)
		__m256 m2{ _mm256_mul_ps(e0, secondRowLHS) };

		// b_32(a_21, a_22, a_23, a_24 ) | b_42(a_21, a_22, a_23, a_24)
		__m256 m3{ _mm256_mul_ps(e1, secondRowLHS) };

		// b_13, b_13, b_13, b_13 | b_23, b_23, b_23, b_23
		e0 = { _mm256_permute_ps(rhs.data[0], 0b10'10'10'10) };
		// b_33, b_33, b_33, b_33 | b_43, b_43, b_43, b_43
		e1 = { _mm256_permute_ps(rhs.data[1], 0b10'10'10'10) };

		// a_31, a_32, a_33, a_34 | a_31, a_32, a_33, a_34
		const __m256 thirdRowLHS{ _mm256_permute2f128_ps(lhs.data[1], lhs.data[1], 0x00) };

		// b_13(a_31, a_32, a_33, a_34) | b_23(a_31, a_32, a_33, a_34)
		__m256 m4{ _mm256_mul_ps(e0, thirdRowLHS) };

		// b_33(a_31, a_32, a_33, a_34) | b_43(a_31, a_32, a_33, a_34)
		__m256 m5{ _mm256_mul_ps(e1, thirdRowLHS) };

		// b_14, b_14, b_14, b_14 | b_24, b_24, b_24, b_24
		e0 = { _mm256_permute_ps(rhs.data[0], 0b11'11'11'11) };
		// b_34, b_34, b_34, b_34 | b_44, b_44, b_44, b_44
		e1 = { _mm256_permute_ps(rhs.data[1], 0b11'11'11'11) };

		// a_41, a_42, a_43, a_44 | a_41, a_42, a_43, a_44
		__m256 fourthRowLHS{ _mm256_permute2f128_ps(lhs.data[1], lhs.data[1], 0x11) };

		// b_14(a_41, a_42, a_43, a_44) | b_24(a_41, a_42, a_43, a_44)
		__m256 m6{ _mm256_mul_ps(e0, fourthRowLHS) };

		// b_34(a_41, a_42, a_43, a_44) | b_44(a_41, a_42, a_43, a_44)
		__m256 m7{ _mm256_mul_ps(e1, fourthRowLHS) };

		result.data[0] = _mm256_add_ps(_mm256_add_ps(m0, m2), _mm256_add_ps(m4, m6));
		result.data[1] = _mm256_add_ps(_mm256_add_ps(m1, m3), _mm256_add_ps(m5, m7));
#elif (CIN_INSTRUCTION_SET) & (CIN_INSTRUCTION_SET_SSE_BIT)
		{
			// b_11, b_11, b_11, b_11
			__m128 e0{ _mm_shuffle_ps(rhs.data[0], rhs.data[0], 0b00'00'00'00) };
			// b_12, b_12, b_12, b_12
			__m128 e1{ _mm_shuffle_ps(rhs.data[0], rhs.data[0], 0b01'01'01'01) };
			// b_13, b_13, b_13, b_13
			__m128 e2{ _mm_shuffle_ps(rhs.data[0], rhs.data[0], 0b10'10'10'10) };
			// b_14, b_14, b_14, b_14
			__m128 e3{ _mm_shuffle_ps(rhs.data[0], rhs.data[0], 0b11'11'11'11) };

			// b_11 * (a_11 | a_12 | a_13 | a_14) 
			__m128 m0{ _mm_mul_ps(lhs.data[0], e0) };
			// b_12 * (a_21 | a_22 | a_23 | a_24)
			__m128 m1{ _mm_mul_ps(lhs.data[1], e1) };
			// b_13 * (a_31 | a_32 | a_33 | a_34)
			__m128 m2{ _mm_mul_ps(lhs.data[2], e2) };
			// b_14 * (a_41 | a_42 | a_43 | a_44)
			__m128 m3{ _mm_mul_ps(lhs.data[3], e3) };

			__m128 a0{ _mm_add_ps(m0, m1) };
			__m128 a1{ _mm_add_ps(m2, m3) };
			__m128 a2{ _mm_add_ps(a0, a1) };

			result.data[0] = a2;
		}

		{
			// b_21, b_21, b_21, b_21
			__m128 e0{ _mm_shuffle_ps(rhs.data[1], rhs.data[1], 0b00'00'00'00) };
			// b_22, b_22, b_22, b_22
			__m128 e1{ _mm_shuffle_ps(rhs.data[1], rhs.data[1], 0b01'01'01'01) };
			// b_23, b_23, b_23, b_23
			__m128 e2{ _mm_shuffle_ps(rhs.data[1], rhs.data[1], 0b10'10'10'10) };
			// b_24, b_24, b_24, b_24
			__m128 e3{ _mm_shuffle_ps(rhs.data[1], rhs.data[1], 0b11'11'11'11) };

			// b_21 * (a_11 | a_12 | a_13 | a_14);
			__m128 m0{ _mm_mul_ps(lhs.data[0], e0) };
			// b_22 * (a_21 | a_22 | a_23 | a_24)
			__m128 m1{ _mm_mul_ps(lhs.data[1], e1) };
			// b_23 * (a_31 | a_32 | a_33 | a_34)
			__m128 m2{ _mm_mul_ps(lhs.data[2], e2) };
			// b_24 * (a_41 | a_42 | a_43 | a_44)
			__m128 m3{ _mm_mul_ps(lhs.data[3], e3) };

			__m128 a0{ _mm_add_ps(m0, m1) };
			__m128 a1{ _mm_add_ps(m2, m3) };
			__m128 a2{ _mm_add_ps(a0, a1) };

			result.data[1] = a2;
		}

		{
			// b_31, b_31, b_31, b_31
			__m128 e0{ _mm_shuffle_ps(rhs.data[2], rhs.data[2], 0b00'00'00'00) };
			// b_32, b_32, b_32, b_32
			__m128 e1{ _mm_shuffle_ps(rhs.data[2], rhs.data[2], 0b01'01'01'01) };
			// b_33, b_33, b_33, b_33
			__m128 e2{ _mm_shuffle_ps(rhs.data[2], rhs.data[2], 0b10'10'10'10) };
			// b_34, b_34, b_34, b_34
			__m128 e3{ _mm_shuffle_ps(rhs.data[2], rhs.data[2], 0b11'11'11'11) };

			// b_31 * (a_11 | a_12 | a_13 | a_14);
			__m128 m0{ _mm_mul_ps(lhs.data[0], e0) };
			// b_32 * (a_21 | a_22 | a_23 | a_24)
			__m128 m1{ _mm_mul_ps(lhs.data[1], e1) };
			// b_33 * (a_31 | a_32 | a_33 | a_34)
			__m128 m2{ _mm_mul_ps(lhs.data[2], e2) };
			// b_34 * (a_41 | a_42 | a_43 | a_44)
			__m128 m3{ _mm_mul_ps(lhs.data[3], e3) };

			__m128 a0{ _mm_add_ps(m0, m1) };
			__m128 a1{ _mm_add_ps(m2, m3) };
			__m128 a2{ _mm_add_ps(a0, a1) };

			result.data[2] = a2;
		}

		{
			// b_41, b_41, b_41, b_41
			__m128 e0{ _mm_shuffle_ps(rhs.data[3], rhs.data[3], 0b00'00'00'00) };
			// b_42, b_42, b_42, b_42
			__m128 e1{ _mm_shuffle_ps(rhs.data[3], rhs.data[3], 0b01'01'01'01) };
			// b_43, b_43, b_43, b_43
			__m128 e2{ _mm_shuffle_ps(rhs.data[3], rhs.data[3], 0b10'10'10'10) };
			// b_44, b_44, b_44, b_44
			__m128 e3{ _mm_shuffle_ps(rhs.data[3], rhs.data[3], 0b11'11'11'11) };

			// b_41 * (a_11 | a_12 | a_13 | a_14);
			__m128 m0{ _mm_mul_ps(lhs.data[0], e0) };
			// b_42 * (a_21 | a_22 | a_23 | a_24)
			__m128 m1{ _mm_mul_ps(lhs.data[1], e1) };
			// b_43 * (a_31 | a_32 | a_33 | a_34)
			__m128 m2{ _mm_mul_ps(lhs.data[2], e2) };
			// b_44 * (a_41 | a_42 | a_43 | a_44)
			__m128 m3{ _mm_mul_ps(lhs.data[3], e3) };

			__m128 a0{ _mm_add_ps(m0, m1) };
			__m128 a1{ _mm_add_ps(m2, m3) };
			__m128 a2{ _mm_add_ps(a0, a1) };

			result.data[3] = a2;
		}
#else
		result.raw[0] = rhs.raw[0 + 0] * lhs.raw[0 + 0] + rhs.raw[0 + 1] * lhs.raw[4 + 0] + rhs.raw[0 + 2] * lhs.raw[8 + 0] + rhs.raw[0 + 3] * lhs.raw[12 + 0];
		result.raw[1] = rhs.raw[0 + 0] * lhs.raw[0 + 1] + rhs.raw[0 + 1] * lhs.raw[4 + 1] + rhs.raw[0 + 2] * lhs.raw[8 + 1] + rhs.raw[0 + 3] * lhs.raw[12 + 1];
		result.raw[2] = rhs.raw[0 + 0] * lhs.raw[0 + 2] + rhs.raw[0 + 1] * lhs.raw[4 + 2] + rhs.raw[0 + 2] * lhs.raw[8 + 2] + rhs.raw[0 + 3] * lhs.raw[12 + 2];
		result.raw[3] = rhs.raw[0 + 0] * lhs.raw[0 + 3] + rhs.raw[0 + 1] * lhs.raw[4 + 3] + rhs.raw[0 + 2] * lhs.raw[8 + 3] + rhs.raw[0 + 3] * lhs.raw[12 + 3];

		result.raw[4] = rhs.raw[4 + 0] * lhs.raw[0 + 0] + rhs.raw[4 + 1] * lhs.raw[4 + 0] + rhs.raw[4 + 2] * lhs.raw[8 + 0] + rhs.raw[4 + 3] * lhs.raw[12 + 0];
		result.raw[5] = rhs.raw[4 + 0] * lhs.raw[0 + 1] + rhs.raw[4 + 1] * lhs.raw[4 + 1] + rhs.raw[4 + 2] * lhs.raw[8 + 1] + rhs.raw[4 + 3] * lhs.raw[12 + 1];
		result.raw[6] = rhs.raw[4 + 0] * lhs.raw[0 + 2] + rhs.raw[4 + 1] * lhs.raw[4 + 2] + rhs.raw[4 + 2] * lhs.raw[8 + 2] + rhs.raw[4 + 3] * lhs.raw[12 + 2];
		result.raw[7] = rhs.raw[4 + 0] * lhs.raw[0 + 3] + rhs.raw[4 + 1] * lhs.raw[4 + 3] + rhs.raw[4 + 2] * lhs.raw[8 + 3] + rhs.raw[4 + 3] * lhs.raw[12 + 3];

		result.raw[8] = rhs.raw[8 + 0] * lhs.raw[0 + 0] + rhs.raw[8 + 1] * lhs.raw[4 + 0] + rhs.raw[8 + 2] * lhs.raw[8 + 0] + rhs.raw[8 + 3] * lhs.raw[12 + 0];
		result.raw[9] = rhs.raw[8 + 0] * lhs.raw[0 + 1] + rhs.raw[8 + 1] * lhs.raw[4 + 1] + rhs.raw[8 + 2] * lhs.raw[8 + 1] + rhs.raw[8 + 3] * lhs.raw[12 + 1];
		result.raw[10] = rhs.raw[8 + 0] * lhs.raw[0 + 2] + rhs.raw[8 + 1] * lhs.raw[4 + 2] + rhs.raw[8 + 2] * lhs.raw[8 + 2] + rhs.raw[8 + 3] * lhs.raw[12 + 2];
		result.raw[11] = rhs.raw[8 + 0] * lhs.raw[0 + 3] + rhs.raw[8 + 1] * lhs.raw[4 + 3] + rhs.raw[8 + 2] * lhs.raw[8 + 3] + rhs.raw[8 + 3] * lhs.raw[12 + 3];

		result.raw[12] = rhs.raw[12 + 0] * lhs.raw[0 + 0] + rhs.raw[12 + 1] * lhs.raw[4 + 0] + rhs.raw[12 + 2] * lhs.raw[8 + 0] + rhs.raw[12 + 3] * lhs.raw[12 + 0];
		result.raw[13] = rhs.raw[12 + 0] * lhs.raw[0 + 1] + rhs.raw[12 + 1] * lhs.raw[4 + 1] + rhs.raw[12 + 2] * lhs.raw[8 + 1] + rhs.raw[12 + 3] * lhs.raw[12 + 1];
		result.raw[14] = rhs.raw[12 + 0] * lhs.raw[0 + 2] + rhs.raw[12 + 1] * lhs.raw[4 + 2] + rhs.raw[12 + 2] * lhs.raw[8 + 2] + rhs.raw[12 + 3] * lhs.raw[12 + 2];
		result.raw[15] = rhs.raw[12 + 0] * lhs.raw[0 + 3] + rhs.raw[12 + 1] * lhs.raw[4 + 3] + rhs.raw[12 + 2] * lhs.raw[8 + 3] + rhs.raw[12 + 3] * lhs.raw[12 + 3];
#endif
		lhs = result;
	}

	CIN_MATH_INLINE void CIN_CALL operator+=(Matrix<4, 4, float>& lhs, const float rhs) noexcept
	{
#if (CIN_INSTRUCTION_SET) & (CIN_INSTRUCTION_SET_AVX_BIT)
		lhs.data[0] = _mm256_add_ps(lhs.data[0], __m256{rhs, rhs, rhs, rhs, rhs, rhs, rhs, rhs});
		lhs.data[1] = _mm256_add_ps(lhs.data[1], __m256{rhs, rhs, rhs, rhs, rhs, rhs, rhs, rhs});
#elif (CIN_INSTRUCTION_SET) & (CIN_INSTRUCTION_SET_SSE_BIT)
		lhs.data[0] = _mm_add_ps(lhs.data[0], __m128{rhs, rhs, rhs, rhs });
		lhs.data[1] = _mm_add_ps(lhs.data[1], __m128{rhs, rhs, rhs, rhs });
		lhs.data[2] = _mm_add_ps(lhs.data[2], __m128{rhs, rhs, rhs, rhs });
		lhs.data[3] = _mm_add_ps(lhs.data[3], __m128{rhs, rhs, rhs, rhs });
#else
		lhs.raw[0] += rhs;
		lhs.raw[1] += rhs;
		lhs.raw[2] += rhs;
		lhs.raw[3] += rhs;
		lhs.raw[4] += rhs;
		lhs.raw[5] += rhs;
		lhs.raw[6] += rhs;
		lhs.raw[7] += rhs;
		lhs.raw[8] += rhs;
		lhs.raw[9] += rhs;
		lhs.raw[10] += rhs;
		lhs.raw[11] += rhs;
		lhs.raw[12] += rhs;
		lhs.raw[13] += rhs;
		lhs.raw[14] += rhs;
		lhs.raw[15] += rhs;
#endif
	}

	CIN_MATH_INLINE void CIN_CALL operator-=(Matrix<4, 4, float>& lhs, const float rhs) noexcept
	{
#if (CIN_INSTRUCTION_SET) & (CIN_INSTRUCTION_SET_AVX_BIT)
		lhs.data[0] = _mm256_sub_ps(lhs.data[0], __m256{rhs, rhs, rhs, rhs, rhs, rhs, rhs, rhs});
		lhs.data[1] = _mm256_sub_ps(lhs.data[1], __m256{rhs, rhs, rhs, rhs, rhs, rhs, rhs, rhs});
#elif (CIN_INSTRUCTION_SET) & (CIN_INSTRUCTION_SET_SSE_BIT)
		lhs.data[0] = _mm_sub_ps(lhs.data[0], __m128{rhs, rhs, rhs, rhs});
		lhs.data[1] = _mm_sub_ps(lhs.data[1], __m128{rhs, rhs, rhs, rhs});
		lhs.data[2] = _mm_sub_ps(lhs.data[2], __m128{rhs, rhs, rhs, rhs});
		lhs.data[3] = _mm_sub_ps(lhs.data[3], __m128{rhs, rhs, rhs, rhs});
#else
		lhs.raw[0] -= rhs;
		lhs.raw[1] -= rhs;
		lhs.raw[2] -= rhs;
		lhs.raw[3] -= rhs;
		lhs.raw[4] -= rhs;
		lhs.raw[5] -= rhs;
		lhs.raw[6] -= rhs;
		lhs.raw[7] -= rhs;
		lhs.raw[8] -= rhs;
		lhs.raw[9] -= rhs;
		lhs.raw[10] -= rhs;
		lhs.raw[11] -= rhs;
		lhs.raw[12] -= rhs;
		lhs.raw[13] -= rhs;
		lhs.raw[14] -= rhs;
		lhs.raw[15] -= rhs;
#endif
	}

	CIN_MATH_INLINE void CIN_CALL operator*=(Matrix<4, 4, float>& lhs, const float rhs) noexcept
	{
#if (CIN_INSTRUCTION_SET) & (CIN_INSTRUCTION_SET_AVX_BIT)
		lhs.data[0] = _mm256_mul_ps(lhs.data[0], __m256{rhs, rhs, rhs, rhs, rhs, rhs, rhs, rhs});
		lhs.data[1] = _mm256_mul_ps(lhs.data[1], __m256{rhs, rhs, rhs, rhs, rhs, rhs, rhs, rhs});
#elif (CIN_INSTRUCTION_SET) & (CIN_INSTRUCTION_SET_SSE_BIT)
		lhs.data[0] = _mm_mul_ps(lhs.data[0], __m128{rhs, rhs, rhs, rhs});
		lhs.data[1] = _mm_mul_ps(lhs.data[1], __m128{rhs, rhs, rhs, rhs});
		lhs.data[2] = _mm_mul_ps(lhs.data[2], __m128{rhs, rhs, rhs, rhs});
		lhs.data[3] = _mm_mul_ps(lhs.data[3], __m128{rhs, rhs, rhs, rhs});
#else
		lhs.raw[0] *= rhs;
		lhs.raw[1] *= rhs;
		lhs.raw[2] *= rhs;
		lhs.raw[3] *= rhs;
		lhs.raw[4] *= rhs;
		lhs.raw[5] *= rhs;
		lhs.raw[6] *= rhs;
		lhs.raw[7] *= rhs;
		lhs.raw[8] *= rhs;
		lhs.raw[9] *= rhs;
		lhs.raw[10] *= rhs;
		lhs.raw[11] *= rhs;
		lhs.raw[12] *= rhs;
		lhs.raw[13] *= rhs;
		lhs.raw[14] *= rhs;
		lhs.raw[15] *= rhs;
#endif
	}

	CIN_MATH_INLINE void CIN_CALL operator/=(Matrix<4, 4, float>& lhs, const float rhs) noexcept
	{
#if (CIN_INSTRUCTION_SET) & (CIN_INSTRUCTION_SET_AVX_BIT)
		lhs.data[0] = _mm256_div_ps(lhs.data[0], __m256{rhs, rhs, rhs, rhs, rhs, rhs, rhs, rhs});
		lhs.data[1] = _mm256_div_ps(lhs.data[1], __m256{rhs, rhs, rhs, rhs, rhs, rhs, rhs, rhs});
#elif (CIN_INSTRUCTION_SET) & (CIN_INSTRUCTION_SET_SSE_BIT)
		lhs.data[0] = _mm_div_ps(lhs.data[0], __m128{rhs, rhs, rhs, rhs});
		lhs.data[1] = _mm_div_ps(lhs.data[1], __m128{rhs, rhs, rhs, rhs});
		lhs.data[2] = _mm_div_ps(lhs.data[2], __m128{rhs, rhs, rhs, rhs});
		lhs.data[3] = _mm_div_ps(lhs.data[3], __m128{rhs, rhs, rhs, rhs});
#else
		lhs.raw[0] /= rhs;
		lhs.raw[1] /= rhs;
		lhs.raw[2] /= rhs;
		lhs.raw[3] /= rhs;
		lhs.raw[4] /= rhs;
		lhs.raw[5] /= rhs;
		lhs.raw[6] /= rhs;
		lhs.raw[7] /= rhs;
		lhs.raw[8] /= rhs;
		lhs.raw[9] /= rhs;
		lhs.raw[10] /= rhs;
		lhs.raw[11] /= rhs;
		lhs.raw[12] /= rhs;
		lhs.raw[13] /= rhs;
		lhs.raw[14] /= rhs;
		lhs.raw[15] /= rhs;
#endif
	}

	CIN_MATH_INLINE Matrix<4, 4, float> CIN_CALL operator+(const Matrix<4, 4, float>& lhs, const Matrix<4, 4, float>& rhs) noexcept
	{
		Matrix<4, 4, float> result;
#if (CIN_INSTRUCTION_SET) & (CIN_INSTRUCTION_SET_AVX_BIT)
		result.data[0] = _mm256_add_ps(lhs.data[0], rhs.data[0]);
		result.data[1] = _mm256_add_ps(lhs.data[1], rhs.data[1]);
#elif (CIN_INSTRUCTION_SET) & (CIN_INSTRUCTION_SET_SSE_BIT)
		result.data[0] = _mm_add_ps(lhs.data[0], rhs.data[0]);
		result.data[1] = _mm_add_ps(lhs.data[1], rhs.data[1]);
		result.data[2] = _mm_add_ps(lhs.data[2], rhs.data[2]);
		result.data[3] = _mm_add_ps(lhs.data[3], rhs.data[3]);
#else
		result.raw[0] = lhs.raw[0] + rhs.raw[0];
		result.raw[1] = lhs.raw[1] + rhs.raw[1];
		result.raw[2] = lhs.raw[2] + rhs.raw[2];
		result.raw[3] = lhs.raw[3] + rhs.raw[3];
		result.raw[4] = lhs.raw[4] + rhs.raw[4];
		result.raw[5] = lhs.raw[5] + rhs.raw[5];
		result.raw[6] = lhs.raw[6] + rhs.raw[6];
		result.raw[7] = lhs.raw[7] + rhs.raw[7];
		result.raw[8] = lhs.raw[8] + rhs.raw[8];
		result.raw[9] = lhs.raw[9] + rhs.raw[9];
		result.raw[10] = lhs.raw[10] + rhs.raw[10];
		result.raw[11] = lhs.raw[11] + rhs.raw[11];
		result.raw[12] = lhs.raw[12] + rhs.raw[12];
		result.raw[13] = lhs.raw[13] + rhs.raw[13];
		result.raw[14] = lhs.raw[14] + rhs.raw[14];
		result.raw[15] = lhs.raw[15] + rhs.raw[15];
#endif
		return result;
	}

	CIN_MATH_INLINE Matrix<4, 4, float> CIN_CALL operator-(const Matrix<4, 4, float>& lhs, const Matrix<4, 4, float>& rhs) noexcept
	{
		Matrix<4, 4, float> result;
#if (CIN_INSTRUCTION_SET) & (CIN_INSTRUCTION_SET_AVX_BIT)
		result.data[0] = _mm256_sub_ps(lhs.data[0], rhs.data[0]);
		result.data[1] = _mm256_sub_ps(lhs.data[1], rhs.data[1]);
#elif (CIN_INSTRUCTION_SET) & (CIN_INSTRUCTION_SET_SSE_BIT)
		result.data[0] = _mm_sub_ps(lhs.data[0], rhs.data[0]);
		result.data[1] = _mm_sub_ps(lhs.data[1], rhs.data[1]);
		result.data[2] = _mm_sub_ps(lhs.data[2], rhs.data[2]);
		result.data[3] = _mm_sub_ps(lhs.data[3], rhs.data[3]);
#else
		result.raw[0] = lhs.raw[0] - rhs.raw[0];
		result.raw[1] = lhs.raw[1] - rhs.raw[1];
		result.raw[2] = lhs.raw[2] - rhs.raw[2];
		result.raw[3] = lhs.raw[3] - rhs.raw[3];
		result.raw[4] = lhs.raw[4] - rhs.raw[4];
		result.raw[5] = lhs.raw[5] - rhs.raw[5];
		result.raw[6] = lhs.raw[6] - rhs.raw[6];
		result.raw[7] = lhs.raw[7] - rhs.raw[7];
		result.raw[8] = lhs.raw[8] - rhs.raw[8];
		result.raw[9] = lhs.raw[9] - rhs.raw[9];
		result.raw[10] = lhs.raw[10] - rhs.raw[10];
		result.raw[11] = lhs.raw[11] - rhs.raw[11];
		result.raw[12] = lhs.raw[12] - rhs.raw[12];
		result.raw[13] = lhs.raw[13] - rhs.raw[13];
		result.raw[14] = lhs.raw[14] - rhs.raw[14];
		result.raw[15] = lhs.raw[15] - rhs.raw[15];
#endif
		return result;
	}

	CIN_MATH_INLINE Matrix<4, 4, float> CIN_CALL operator*(const Matrix<4, 4, float>& lhs, const Matrix<4, 4, float>& rhs) noexcept
	{
		Matrix<4, 4, float> result;
#if (CIN_INSTRUCTION_SET) & (CIN_INSTRUCTION_SET_AVX_BIT)
		__m256 e0{ _mm256_permute_ps(rhs.data[0], 0b00'00'00'00) };
		__m256 e1{ _mm256_permute_ps(rhs.data[1], 0b00'00'00'00) };
		// a_11, a_12, a_13, a_14 | a_11, a_12, a_13, a_14
		const __m256 firstRowLHS{ _mm256_permute2f128_ps(lhs.data[0], lhs.data[0], 0x00) };

		// b_11(a_11, a_12, a_13, a_14 ) | b_21(a_11, a_12, a_13, a_14)
		__m256 m0{ _mm256_mul_ps(e0, firstRowLHS) };

		// b_31(a_11, a_12, a_13, a_14 ) | b_41(a_11, a_12, a_13, a_14)
		__m256 m1{ _mm256_mul_ps(e1, firstRowLHS) };

		// b_12, b_12, b_12, b_12 | b_22, b_22, b_22, b_22
		e0 = { _mm256_permute_ps(rhs.data[0], 0b01'01'01'01) };
		// b_32, b_32, b_32, b_32 | b_42, b_42, b_42, b_42
		e1 = { _mm256_permute_ps(rhs.data[1], 0b01'01'01'01) };

		// a_21, a_22, a_23, a_24 | a_21, a_22, a_23, a_24
		const __m256 secondRowLHS{ _mm256_permute2f128_ps(lhs.data[0], lhs.data[0], 0x11) };

		// b_12(a_21, a_22, a_23, a_24 ) | b_22(a_21, a_22, a_23, a_24)
		__m256 m2{ _mm256_mul_ps(e0, secondRowLHS) };

		// b_32(a_21, a_22, a_23, a_24 ) | b_42(a_21, a_22, a_23, a_24)
		__m256 m3{ _mm256_mul_ps(e1, secondRowLHS) };

		// b_13, b_13, b_13, b_13 | b_23, b_23, b_23, b_23
		e0 = { _mm256_permute_ps(rhs.data[0], 0b10'10'10'10) };
		// b_33, b_33, b_33, b_33 | b_43, b_43, b_43, b_43
		e1 = { _mm256_permute_ps(rhs.data[1], 0b10'10'10'10) };

		// a_31, a_32, a_33, a_34 | a_31, a_32, a_33, a_34
		const __m256 thirdRowLHS{ _mm256_permute2f128_ps(lhs.data[1], lhs.data[1], 0x00) };

		// b_13(a_31, a_32, a_33, a_34) | b_23(a_31, a_32, a_33, a_34)
		__m256 m4{ _mm256_mul_ps(e0, thirdRowLHS) };

		// b_33(a_31, a_32, a_33, a_34) | b_43(a_31, a_32, a_33, a_34)
		__m256 m5{ _mm256_mul_ps(e1, thirdRowLHS) };

		// b_14, b_14, b_14, b_14 | b_24, b_24, b_24, b_24
		e0 = { _mm256_permute_ps(rhs.data[0], 0b11'11'11'11) };
		// b_34, b_34, b_34, b_34 | b_44, b_44, b_44, b_44
		e1 = { _mm256_permute_ps(rhs.data[1], 0b11'11'11'11) };

		// a_41, a_42, a_43, a_44 | a_41, a_42, a_43, a_44
		__m256 fourthRowLHS{ _mm256_permute2f128_ps(lhs.data[1], lhs.data[1], 0x11) };

		// b_14(a_41, a_42, a_43, a_44) | b_24(a_41, a_42, a_43, a_44)
		__m256 m6{ _mm256_mul_ps(e0, fourthRowLHS) };

		// b_34(a_41, a_42, a_43, a_44) | b_44(a_41, a_42, a_43, a_44)
		__m256 m7{ _mm256_mul_ps(e1, fourthRowLHS) };

		result.data[0] = _mm256_add_ps(_mm256_add_ps(m0, m2), _mm256_add_ps(m4, m6));
		result.data[1] = _mm256_add_ps(_mm256_add_ps(m1, m3), _mm256_add_ps(m5, m7));
#elif (CIN_INSTRUCTION_SET) & (CIN_INSTRUCTION_SET_SSE_BIT)
		{
			// b_11, b_11, b_11, b_11
			__m128 e0{ _mm_shuffle_ps(rhs.data[0], rhs.data[0], 0b00'00'00'00) };
			// b_12, b_12, b_12, b_12
			__m128 e1{ _mm_shuffle_ps(rhs.data[0], rhs.data[0], 0b01'01'01'01) };
			// b_13, b_13, b_13, b_13
			__m128 e2{ _mm_shuffle_ps(rhs.data[0], rhs.data[0], 0b10'10'10'10) };
			// b_14, b_14, b_14, b_14
			__m128 e3{ _mm_shuffle_ps(rhs.data[0], rhs.data[0], 0b11'11'11'11) };

			// b_11 * (a_11 | a_12 | a_13 | a_14) 
			__m128 m0{ _mm_mul_ps(lhs.data[0], e0) };
			// b_12 * (a_21 | a_22 | a_23 | a_24)
			__m128 m1{ _mm_mul_ps(lhs.data[1], e1) };
			// b_13 * (a_31 | a_32 | a_33 | a_34)
			__m128 m2{ _mm_mul_ps(lhs.data[2], e2) };
			// b_14 * (a_41 | a_42 | a_43 | a_44)
			__m128 m3{ _mm_mul_ps(lhs.data[3], e3) };

			__m128 a0{ _mm_add_ps(m0, m1) };
			__m128 a1{ _mm_add_ps(m2, m3) };
			__m128 a2{ _mm_add_ps(a0, a1) };

			result.data[0] = a2;
		}

		{
			// b_21, b_21, b_21, b_21
			__m128 e0{ _mm_shuffle_ps(rhs.data[1], rhs.data[1], 0b00'00'00'00) };
			// b_22, b_22, b_22, b_22
			__m128 e1{ _mm_shuffle_ps(rhs.data[1], rhs.data[1], 0b01'01'01'01) };
			// b_23, b_23, b_23, b_23
			__m128 e2{ _mm_shuffle_ps(rhs.data[1], rhs.data[1], 0b10'10'10'10) };
			// b_24, b_24, b_24, b_24
			__m128 e3{ _mm_shuffle_ps(rhs.data[1], rhs.data[1], 0b11'11'11'11) };

			// b_21 * (a_11 | a_12 | a_13 | a_14);
			__m128 m0{ _mm_mul_ps(lhs.data[0], e0) };
			// b_22 * (a_21 | a_22 | a_23 | a_24)
			__m128 m1{ _mm_mul_ps(lhs.data[1], e1) };
			// b_23 * (a_31 | a_32 | a_33 | a_34)
			__m128 m2{ _mm_mul_ps(lhs.data[2], e2) };
			// b_24 * (a_41 | a_42 | a_43 | a_44)
			__m128 m3{ _mm_mul_ps(lhs.data[3], e3) };

			__m128 a0{ _mm_add_ps(m0, m1) };
			__m128 a1{ _mm_add_ps(m2, m3) };
			__m128 a2{ _mm_add_ps(a0, a1) };

			result.data[1] = a2;
		}

		{
			// b_31, b_31, b_31, b_31
			__m128 e0{ _mm_shuffle_ps(rhs.data[2], rhs.data[2], 0b00'00'00'00) };
			// b_32, b_32, b_32, b_32
			__m128 e1{ _mm_shuffle_ps(rhs.data[2], rhs.data[2], 0b01'01'01'01) };
			// b_33, b_33, b_33, b_33
			__m128 e2{ _mm_shuffle_ps(rhs.data[2], rhs.data[2], 0b10'10'10'10) };
			// b_34, b_34, b_34, b_34
			__m128 e3{ _mm_shuffle_ps(rhs.data[2], rhs.data[2], 0b11'11'11'11) };

			// b_31 * (a_11 | a_12 | a_13 | a_14);
			__m128 m0{ _mm_mul_ps(lhs.data[0], e0) };
			// b_32 * (a_21 | a_22 | a_23 | a_24)
			__m128 m1{ _mm_mul_ps(lhs.data[1], e1) };
			// b_33 * (a_31 | a_32 | a_33 | a_34)
			__m128 m2{ _mm_mul_ps(lhs.data[2], e2) };
			// b_34 * (a_41 | a_42 | a_43 | a_44)
			__m128 m3{ _mm_mul_ps(lhs.data[3], e3) };

			__m128 a0{ _mm_add_ps(m0, m1) };
			__m128 a1{ _mm_add_ps(m2, m3) };
			__m128 a2{ _mm_add_ps(a0, a1) };

			result.data[2] = a2;
		}

		{
			// b_41, b_41, b_41, b_41
			__m128 e0{ _mm_shuffle_ps(rhs.data[3], rhs.data[3], 0b00'00'00'00) };
			// b_42, b_42, b_42, b_42
			__m128 e1{ _mm_shuffle_ps(rhs.data[3], rhs.data[3], 0b01'01'01'01) };
			// b_43, b_43, b_43, b_43
			__m128 e2{ _mm_shuffle_ps(rhs.data[3], rhs.data[3], 0b10'10'10'10) };
			// b_44, b_44, b_44, b_44
			__m128 e3{ _mm_shuffle_ps(rhs.data[3], rhs.data[3], 0b11'11'11'11) };

			// b_41 * (a_11 | a_12 | a_13 | a_14);
			__m128 m0{ _mm_mul_ps(lhs.data[0], e0) };
			// b_42 * (a_21 | a_22 | a_23 | a_24)
			__m128 m1{ _mm_mul_ps(lhs.data[1], e1) };
			// b_43 * (a_31 | a_32 | a_33 | a_34)
			__m128 m2{ _mm_mul_ps(lhs.data[2], e2) };
			// b_44 * (a_41 | a_42 | a_43 | a_44)
			__m128 m3{ _mm_mul_ps(lhs.data[3], e3) };

			__m128 a0{ _mm_add_ps(m0, m1) };
			__m128 a1{ _mm_add_ps(m2, m3) };
			__m128 a2{ _mm_add_ps(a0, a1) };

			result.data[3] = a2;
		}
#else
		result.raw[0] = rhs.raw[0 + 0] * lhs.raw[0 + 0] + rhs.raw[0 + 1] * lhs.raw[4 + 0] + rhs.raw[0 + 2] * lhs.raw[8 + 0] + rhs.raw[0 + 3] * lhs.raw[12 + 0];
		result.raw[1] = rhs.raw[0 + 0] * lhs.raw[0 + 1] + rhs.raw[0 + 1] * lhs.raw[4 + 1] + rhs.raw[0 + 2] * lhs.raw[8 + 1] + rhs.raw[0 + 3] * lhs.raw[12 + 1];
		result.raw[2] = rhs.raw[0 + 0] * lhs.raw[0 + 2] + rhs.raw[0 + 1] * lhs.raw[4 + 2] + rhs.raw[0 + 2] * lhs.raw[8 + 2] + rhs.raw[0 + 3] * lhs.raw[12 + 2];
		result.raw[3] = rhs.raw[0 + 0] * lhs.raw[0 + 3] + rhs.raw[0 + 1] * lhs.raw[4 + 3] + rhs.raw[0 + 2] * lhs.raw[8 + 3] + rhs.raw[0 + 3] * lhs.raw[12 + 3];

		result.raw[4] = rhs.raw[4 + 0] * lhs.raw[0 + 0] + rhs.raw[4 + 1] * lhs.raw[4 + 0] + rhs.raw[4 + 2] * lhs.raw[8 + 0] + rhs.raw[4 + 3] * lhs.raw[12 + 0];
		result.raw[5] = rhs.raw[4 + 0] * lhs.raw[0 + 1] + rhs.raw[4 + 1] * lhs.raw[4 + 1] + rhs.raw[4 + 2] * lhs.raw[8 + 1] + rhs.raw[4 + 3] * lhs.raw[12 + 1];
		result.raw[6] = rhs.raw[4 + 0] * lhs.raw[0 + 2] + rhs.raw[4 + 1] * lhs.raw[4 + 2] + rhs.raw[4 + 2] * lhs.raw[8 + 2] + rhs.raw[4 + 3] * lhs.raw[12 + 2];
		result.raw[7] = rhs.raw[4 + 0] * lhs.raw[0 + 3] + rhs.raw[4 + 1] * lhs.raw[4 + 3] + rhs.raw[4 + 2] * lhs.raw[8 + 3] + rhs.raw[4 + 3] * lhs.raw[12 + 3];

		result.raw[8] = rhs.raw[8 + 0] * lhs.raw[0 + 0] + rhs.raw[8 + 1] * lhs.raw[4 + 0] + rhs.raw[8 + 2] * lhs.raw[8 + 0] + rhs.raw[8 + 3] * lhs.raw[12 + 0];
		result.raw[9] = rhs.raw[8 + 0] * lhs.raw[0 + 1] + rhs.raw[8 + 1] * lhs.raw[4 + 1] + rhs.raw[8 + 2] * lhs.raw[8 + 1] + rhs.raw[8 + 3] * lhs.raw[12 + 1];
		result.raw[10] = rhs.raw[8 + 0] * lhs.raw[0 + 2] + rhs.raw[8 + 1] * lhs.raw[4 + 2] + rhs.raw[8 + 2] * lhs.raw[8 + 2] + rhs.raw[8 + 3] * lhs.raw[12 + 2];
		result.raw[11] = rhs.raw[8 + 0] * lhs.raw[0 + 3] + rhs.raw[8 + 1] * lhs.raw[4 + 3] + rhs.raw[8 + 2] * lhs.raw[8 + 3] + rhs.raw[8 + 3] * lhs.raw[12 + 3];

		result.raw[12] = rhs.raw[12 + 0] * lhs.raw[0 + 0] + rhs.raw[12 + 1] * lhs.raw[4 + 0] + rhs.raw[12 + 2] * lhs.raw[8 + 0] + rhs.raw[12 + 3] * lhs.raw[12 + 0];
		result.raw[13] = rhs.raw[12 + 0] * lhs.raw[0 + 1] + rhs.raw[12 + 1] * lhs.raw[4 + 1] + rhs.raw[12 + 2] * lhs.raw[8 + 1] + rhs.raw[12 + 3] * lhs.raw[12 + 1];
		result.raw[14] = rhs.raw[12 + 0] * lhs.raw[0 + 2] + rhs.raw[12 + 1] * lhs.raw[4 + 2] + rhs.raw[12 + 2] * lhs.raw[8 + 2] + rhs.raw[12 + 3] * lhs.raw[12 + 2];
		result.raw[15] = rhs.raw[12 + 0] * lhs.raw[0 + 3] + rhs.raw[12 + 1] * lhs.raw[4 + 3] + rhs.raw[12 + 2] * lhs.raw[8 + 3] + rhs.raw[12 + 3] * lhs.raw[12 + 3];
#endif
		return result;
	}

	CIN_MATH_INLINE Matrix<4, 4, float> CIN_CALL operator+(const Matrix<4, 4, float>& lhs, const float rhs) noexcept
	{
		Matrix<4, 4, float> result;
#if (CIN_INSTRUCTION_SET) & (CIN_INSTRUCTION_SET_AVX_BIT)
		result.data[0] = _mm256_add_ps(lhs.data[0], __m256{ rhs, rhs, rhs, rhs, rhs, rhs, rhs, rhs});
		result.data[1] = _mm256_add_ps(lhs.data[1], __m256{ rhs, rhs, rhs, rhs, rhs, rhs, rhs, rhs});
#elif (CIN_INSTRUCTION_SET) & (CIN_INSTRUCTION_SET_SSE_BIT)
		result.data[0] = _mm_add_ps(lhs.data[0], __m128{ rhs, rhs, rhs, rhs});
		result.data[1] = _mm_add_ps(lhs.data[1], __m128{ rhs, rhs, rhs, rhs});
		result.data[2] = _mm_add_ps(lhs.data[2], __m128{ rhs, rhs, rhs, rhs});
		result.data[3] = _mm_add_ps(lhs.data[3], __m128{ rhs, rhs, rhs, rhs});
#else
		result.raw[0] = lhs.raw[0] + rhs;
		result.raw[1] = lhs.raw[1] + rhs;
		result.raw[2] = lhs.raw[2] + rhs;
		result.raw[3] = lhs.raw[3] + rhs;
		result.raw[4] = lhs.raw[4] + rhs;
		result.raw[5] = lhs.raw[5] + rhs;
		result.raw[6] = lhs.raw[6] + rhs;
		result.raw[7] = lhs.raw[7] + rhs;
		result.raw[8] = lhs.raw[8] + rhs;
		result.raw[9] = lhs.raw[9] + rhs;
		result.raw[10] = lhs.raw[10] + rhs;
		result.raw[11] = lhs.raw[11] + rhs;
		result.raw[12] = lhs.raw[12] + rhs;
		result.raw[13] = lhs.raw[13] + rhs;
		result.raw[14] = lhs.raw[14] + rhs;
		result.raw[15] = lhs.raw[15] + rhs;
#endif
		return result;
	}

	CIN_MATH_INLINE Matrix<4, 4, float> CIN_CALL operator-(const Matrix<4, 4, float>& lhs, const float rhs) noexcept
	{
		Matrix<4, 4, float> result;
#if (CIN_INSTRUCTION_SET) & (CIN_INSTRUCTION_SET_AVX_BIT)
		result.data[0] = _mm256_sub_ps(lhs.data[0], __m256{ rhs, rhs, rhs, rhs, rhs, rhs, rhs, rhs});
		result.data[1] = _mm256_sub_ps(lhs.data[1], __m256{ rhs, rhs, rhs, rhs, rhs, rhs, rhs, rhs});
#elif (CIN_INSTRUCTION_SET) & (CIN_INSTRUCTION_SET_SSE_BIT)
		result.data[0] = _mm_sub_ps(lhs.data[0], __m128{ rhs, rhs, rhs, rhs});
		result.data[1] = _mm_sub_ps(lhs.data[1], __m128{ rhs, rhs, rhs, rhs});
		result.data[2] = _mm_sub_ps(lhs.data[2], __m128{ rhs, rhs, rhs, rhs});
		result.data[3] = _mm_sub_ps(lhs.data[3], __m128{ rhs, rhs, rhs, rhs});
#else
		result.raw[0] = lhs.raw[0] - rhs;
		result.raw[1] = lhs.raw[1] - rhs;
		result.raw[2] = lhs.raw[2] - rhs;
		result.raw[3] = lhs.raw[3] - rhs;
		result.raw[4] = lhs.raw[4] - rhs;
		result.raw[5] = lhs.raw[5] - rhs;
		result.raw[6] = lhs.raw[6] - rhs;
		result.raw[7] = lhs.raw[7] - rhs;
		result.raw[8] = lhs.raw[8] - rhs;
		result.raw[9] = lhs.raw[9] - rhs;
		result.raw[10] = lhs.raw[10] - rhs;
		result.raw[11] = lhs.raw[11] - rhs;
		result.raw[12] = lhs.raw[12] - rhs;
		result.raw[13] = lhs.raw[13] - rhs;
		result.raw[14] = lhs.raw[14] - rhs;
		result.raw[15] = lhs.raw[15] - rhs;
#endif
		return result;
	}

	CIN_MATH_INLINE Matrix<4, 4, float> CIN_CALL operator*(const Matrix<4, 4, float>& lhs, const float rhs) noexcept
	{
		Matrix<4, 4, float> result;
#if (CIN_INSTRUCTION_SET) & (CIN_INSTRUCTION_SET_AVX_BIT)
		result.data[0] = _mm256_mul_ps(lhs.data[0], __m256{ rhs, rhs, rhs, rhs, rhs, rhs, rhs, rhs});
		result.data[1] = _mm256_mul_ps(lhs.data[1], __m256{ rhs, rhs, rhs, rhs, rhs, rhs, rhs, rhs});
#elif (CIN_INSTRUCTION_SET) & (CIN_INSTRUCTION_SET_SSE_BIT)
		result.data[0] = _mm_mul_ps(lhs.data[0], __m128{ rhs, rhs, rhs, rhs});
		result.data[1] = _mm_mul_ps(lhs.data[1], __m128{ rhs, rhs, rhs, rhs});
		result.data[2] = _mm_mul_ps(lhs.data[2], __m128{ rhs, rhs, rhs, rhs});
		result.data[3] = _mm_mul_ps(lhs.data[3], __m128{ rhs, rhs, rhs, rhs});
#else
		result.raw[0] = lhs.raw[0] * rhs;
		result.raw[1] = lhs.raw[1] * rhs;
		result.raw[2] = lhs.raw[2] * rhs;
		result.raw[3] = lhs.raw[3] * rhs;
		result.raw[4] = lhs.raw[4] * rhs;
		result.raw[5] = lhs.raw[5] * rhs;
		result.raw[6] = lhs.raw[6] * rhs;
		result.raw[7] = lhs.raw[7] * rhs;
		result.raw[8] = lhs.raw[8] * rhs;
		result.raw[9] = lhs.raw[9] * rhs;
		result.raw[10] = lhs.raw[10] * rhs;
		result.raw[11] = lhs.raw[11] * rhs;
		result.raw[12] = lhs.raw[12] * rhs;
		result.raw[13] = lhs.raw[13] * rhs;
		result.raw[14] = lhs.raw[14] * rhs;
		result.raw[15] = lhs.raw[15] * rhs;
#endif
		return result;
	}

	CIN_MATH_INLINE Matrix<4, 4, float> CIN_CALL operator/(const Matrix<4, 4, float>& lhs, const float rhs) noexcept
	{
		Matrix<4, 4, float> result;
#if (CIN_INSTRUCTION_SET) & (CIN_INSTRUCTION_SET_AVX_BIT)
		result.data[0] = _mm256_div_ps(lhs.data[0], __m256{ rhs, rhs, rhs, rhs, rhs, rhs, rhs, rhs});
		result.data[1] = _mm256_div_ps(lhs.data[1], __m256{ rhs, rhs, rhs, rhs, rhs, rhs, rhs, rhs});
#elif (CIN_INSTRUCTION_SET) & (CIN_INSTRUCTION_SET_SSE_BIT)
		result.data[0] = _mm_div_ps(lhs.data[0], __m128{ rhs, rhs, rhs, rhs});
		result.data[1] = _mm_div_ps(lhs.data[1], __m128{ rhs, rhs, rhs, rhs});
		result.data[2] = _mm_div_ps(lhs.data[2], __m128{ rhs, rhs, rhs, rhs});
		result.data[3] = _mm_div_ps(lhs.data[3], __m128{ rhs, rhs, rhs, rhs});
#else
		result.raw[0] = lhs.raw[0] / rhs;
		result.raw[1] = lhs.raw[1] / rhs;
		result.raw[2] = lhs.raw[2] / rhs;
		result.raw[3] = lhs.raw[3] / rhs;
		result.raw[4] = lhs.raw[4] / rhs;
		result.raw[5] = lhs.raw[5] / rhs;
		result.raw[6] = lhs.raw[6] / rhs;
		result.raw[7] = lhs.raw[7] / rhs;
		result.raw[8] = lhs.raw[8] / rhs;
		result.raw[9] = lhs.raw[9] / rhs;
		result.raw[10] = lhs.raw[10] / rhs;
		result.raw[11] = lhs.raw[11] / rhs;
		result.raw[12] = lhs.raw[12] / rhs;
		result.raw[13] = lhs.raw[13] / rhs;
		result.raw[14] = lhs.raw[14] / rhs;
		result.raw[15] = lhs.raw[15] / rhs;
#endif
		return result;
	}

	CIN_MATH_INLINE Vector<4, float> CIN_CALL operator*(const Matrix<4, 4, float>& lhs, const Vector<4, float>& rhs) noexcept
	{
		Vector<4, float> result;
#if (CIN_INSTRUCTION_SET) & (CIN_INSTRUCTION_SET_AVX_BIT)
		/* 10 instructions more than sse.. */
		const __m256 e0{ _mm256_set_m128(_mm_shuffle_ps(rhs.data, rhs.data, 0b01'01'01'01), _mm_shuffle_ps(rhs.data, rhs.data, 0b00'00'00'00)) };
		const __m256 m0{ _mm256_mul_ps(e0, lhs.data[0]) };
			
		result.data = _mm_add_ps(result.data, _mm256_extractf128_ps(m0, 0b00'00'00'00));
		result.data = _mm_add_ps(result.data, _mm256_extractf128_ps(m0, 0b01'01'01'01));
		
		const __m256 e1{ _mm256_set_m128(_mm_shuffle_ps(rhs.data, rhs.data, 0b11'11'11'11), _mm_shuffle_ps(rhs.data, rhs.data, 0b10'10'10'10)) };
		const __m256 m1{ _mm256_mul_ps(e1, lhs.data[1]) };

		result.data = _mm_add_ps(result.data, _mm256_extractf128_ps(m1, 0b00'00'00'00));
		result.data = _mm_add_ps(result.data, _mm256_extractf128_ps(m1, 0b01'01'01'01));
#elif (CIN_INSTRUCTION_SET) & (CIN_INSTRUCTION_SET_SSE_BIT)
		const __m128 e0{ _mm_shuffle_ps(rhs.data, rhs.data, 0b00'00'00'00) };
		result.data = _mm_mul_ps(e0, lhs.data[0]);

		const __m128 e1{ _mm_mul_ps(_mm_shuffle_ps(rhs.data, rhs.data, 0b01'01'01'01), lhs.data[1]) };
		result.data = _mm_add_ps(result.data, e1);
		
		const __m128 e2{ _mm_mul_ps(_mm_shuffle_ps(rhs.data, rhs.data, 0b10'10'10'10), lhs.data[2]) };
		result.data = _mm_add_ps(result.data, e2);

		const __m128 e3{ _mm_mul_ps(_mm_shuffle_ps(rhs.data, rhs.data, 0b11'11'11'11), lhs.data[3]) };
		result.data = _mm_add_ps(result.data, e3);
#else
		result[0] = rhs[0] * lhs[0] + rhs[1] * lhs[4] + rhs[2] * lhs[8] + rhs[3] * lhs[12];
		result[1] = rhs[0] * lhs[1] + rhs[1] * lhs[5] + rhs[2] * lhs[9] + rhs[3] * lhs[13];
		result[2] = rhs[0] * lhs[2] + rhs[1] * lhs[6] + rhs[2] * lhs[10] + rhs[3] * lhs[14];
		result[3] = rhs[0] * lhs[3] + rhs[1] * lhs[7] + rhs[2] * lhs[11] + rhs[3] * lhs[15];
#endif
		return result;
	}
}