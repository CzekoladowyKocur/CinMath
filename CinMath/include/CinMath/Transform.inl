#pragma once

namespace CinMath {
	template<typename ValueType>
	CIN_MATH_INLINE ValueType ToRadians(const ValueType degrees) noexcept
	{
		return degrees * AtCompileTime(Constants::PI<ValueType> / static_cast<ValueType>(180U));
	}
	
	template<typename ValueType>
	CIN_MATH_INLINE ValueType ToDegrees(const ValueType radians) noexcept
	{
		return radians * AtCompileTime(static_cast<ValueType>(180U) / Constants::PI<ValueType>);
	}

	namespace Implementation {
		/* Vectors */
		template<Length_t length, typename ValueType>
		struct VectorLength;

		template<Length_t length, typename ValueType>
		struct VectorDot;

		template<Length_t length, typename ValueType>
		struct VectorCross;

		/* Matrices */
		template<Length_t rows, Length_t columns, typename ValueType>
		struct MatrixTranslate;

		template<Length_t rows, Length_t columns, typename ValueType>
		struct MatrixTranslateIdentity;

		template<Length_t rows, Length_t columns, typename ValueType>
		struct MatrixTranspose;

		template<Length_t rows, Length_t columns, typename ValueType>
		struct MatrixDeterminant;

		template<Length_t rows, Length_t columns, typename ValueType>
		struct MatrixInverse;

		/* Quaternions */
		template<typename ValueType>
		struct QuaternionConugate;

		template<typename ValueType>
		struct QuaternionNorm;

		template<typename ValueType>
		struct QuaternionNormSquared;

		template<typename ValueType>
		struct QuaternionNormalize;

		template<typename ValueType>
		struct QuaternionInverse;

		template<typename ValueType>
		struct QuaternionRotate;

		template<typename ValueType>
		struct QuaternionAxisAngleToQuaternion;

		template<typename ValueType>
		struct PerspectiveProjection;

		/* Vector length */
		template<typename ValueType>
		struct VectorLength<2, ValueType>
		{
			CIN_MATH_INLINE static ValueType implementation(const Vector<2, ValueType>& vector) noexcept
			{
				return std::sqrt(vector.raw[0] * vector.raw[0] + vector.raw[1] * vector.raw[1]);
			}
		};

		template<typename ValueType>
		struct VectorLength<3, ValueType>
		{
			CIN_MATH_INLINE static ValueType implementation(const Vector<3, ValueType>& vector) noexcept
			{
				return std::sqrt(vector.raw[0] * vector.raw[0] + vector.raw[1] * vector.raw[1] + vector.raw[2] * vector.raw[2]);
			}
		};

		template<typename ValueType>
		struct VectorLength<4, ValueType>
		{
			CIN_MATH_INLINE static ValueType implementation(const Vector<4, ValueType>& vector) noexcept
			{
				return std::sqrt(vector.raw[0] * vector.raw[0] + vector.raw[1] * vector.raw[1] + vector.raw[2] * vector.raw[2] + vector.raw[3] * vector.raw[3]);
			}
		};

		/* Dot product */
		template<typename ValueType>
		struct VectorDot<2, ValueType>
		{
			CIN_MATH_INLINE static ValueType implementation(const Vector<2, ValueType>& lhs, const Vector<2, ValueType>& rhs) noexcept
			{
				return lhs.raw[0] * rhs.raw[0] + lhs.raw[1] * rhs.raw[1];
			}
		};

		template<typename ValueType>
		struct VectorDot<3, ValueType>
		{
			CIN_MATH_INLINE static ValueType implementation(const Vector<3, ValueType>& lhs, const Vector<3, ValueType>& rhs) noexcept
			{
				return lhs.raw[0] * rhs.raw[0] + lhs.raw[1] * rhs.raw[1] + lhs.raw[2] * rhs.raw[2];
			}
		};

		template<typename ValueType>
		struct VectorDot<4, ValueType>
		{
			CIN_MATH_INLINE static ValueType implementation(const Vector<4, ValueType>& lhs, const Vector<4, ValueType>& rhs) noexcept
			{
#if (CIN_INSTRUCTION_SET) & (CIN_INSTRUCTION_SET_SSE_BIT) & 0
				const __m128 m0{ _mm_mul_ps(lhs.data, rhs.data) };
				const __m128 a0{ _mm_add_ps(m0, _mm_shuffle_ps(m0, m0, 0b00'00'01'00)) };

				return 0.0f;


				/*
				r = _mm_shuffle_ps(r, temp, 0b01'00'00'00);
				r = _mm_add_ps(r, temp);
				temp = _mm_shuffle_ps(temp, r, 0b00'11'00'00);
				temp = _mm_add_ps(temp, r);
				r = _mm_shuffle_ps(temp, temp, 0b10'10'10'10);

				return r.m128_f32[0];
				*/
#else
				return lhs.raw[0] * rhs.raw[0] + lhs.raw[1] * rhs.raw[1] + lhs.raw[2] * rhs.raw[2] + lhs.raw[3] * rhs.raw[3];
#endif
			}
		};

		/* Cross product */
		template<typename ValueType>
		struct VectorCross<3, ValueType>
		{
			CIN_MATH_INLINE static Vector<3, float> implementation(const Vector<3, float>& lhs, const Vector<3, float>& rhs) noexcept
			{
				Vector<3, float> result;

				result.raw[0] = lhs[1] * rhs[2] - lhs[2] * rhs[1];
				result.raw[1] = lhs[2] * rhs[0] - lhs[0] * rhs[2];
				result.raw[2] = lhs[0] * rhs[1] - lhs[1] * rhs[0];

				return result;
			}
		};

		template<typename ValueType>
		struct VectorCross<4, ValueType>
		{
			CIN_MATH_INLINE static Vector<4, float> implementation(const Vector<4, float>& lhs, const Vector<4, float>& rhs) noexcept
			{
				Vector<4, float> result;
#if (CIN_INSTRUCTION_SET) & (CIN_INSTRUCTION_SET_SSE_BIT)
				result.data = _mm_sub_ps(
					_mm_mul_ps(_mm_shuffle_ps(lhs.data, lhs.data, 0b00'00'10'01), _mm_shuffle_ps(rhs.data, rhs.data, 0b00'01'00'10)),
					_mm_mul_ps(_mm_shuffle_ps(lhs.data, lhs.data, 0b00'01'00'10), _mm_shuffle_ps(rhs.data, rhs.data, 0b00'00'10'01)));
#else
				result.raw[0] = lhs[1] * rhs[2] - lhs[2] * rhs[1];
				result.raw[1] = lhs[2] * rhs[0] - lhs[0] * rhs[2];
				result.raw[2] = lhs[0] * rhs[1] - lhs[1] * rhs[0];
#endif
				return result;
			}
		};

		template<typename ValueType>
		struct MatrixTranslate<4, 4, ValueType>
		{
			CIN_MATH_INLINE static Matrix<4, 4, float> implementation(const Matrix<4, 4, float>& matrix, const Vector<3, float>& translation)
			{
				Matrix<4, 4, float> result(matrix);

				result.raw[12] += translation.raw[0] * result.raw[0];
				result.raw[13] += translation.raw[1] * result.raw[10];
				result.raw[14] += translation.raw[2] * result.raw[15];

				return result;
			}

			CIN_MATH_INLINE static Matrix<4, 4, float> implementation(const Matrix<4, 4, float>& matrix, const Vector<4, float>& translation)
			{
				Matrix<4, 4, float> result(matrix);
				assert(translation.w == 0.0f);
				result.raw[12] += translation.raw[0] * result.raw[0];
				result.raw[13] += translation.raw[1] * result.raw[10];
				result.raw[14] += translation.raw[2] * result.raw[15];
				
				return result;
			}
		};

		template<typename ValueType>
		struct MatrixTranslateIdentity<4, 4, ValueType>
		{
			CIN_MATH_INLINE static Matrix<4, 4, float> implementation(const Vector<3, float>& translation)
			{
				return Matrix<4, 4, float> {
					1.0f, 0.0f, 0.0f, 0.0f,
					0.0f, 1.0f, 0.0f, 0.0f,
					0.0f, 0.0f, 1.0f, 0.0f,
					translation.raw[0], translation.raw[1], translation.raw[2], 1.0f
				};
			}

			CIN_MATH_INLINE static Matrix<4, 4, float> implementation(const Vector<4, float>& translation)
			{
				assert(translation.w == 0.0f);
				return Matrix<4, 4, float> {
					1.0f, 0.0f, 0.0f, 0.0f,
					0.0f, 1.0f, 0.0f, 0.0f,
					0.0f, 0.0f, 1.0f, 0.0f,
					translation.raw[0], translation.raw[1], translation.raw[2], 1.0f
				};
			}
		};

		template<typename ValueType>
		struct MatrixTranspose<2, 2, ValueType>
		{
			CIN_MATH_INLINE static Matrix<2, 2, float> implementation(const Matrix<2, 2, float>& matrix) noexcept
			{
				Matrix<2, 2, float> result;
#if (CIN_INSTRUCTION_SET) & (CIN_INSTRUCTION_SET_AVX_BIT)
				result.data = _mm_permute_ps(matrix.data, 0b11'01'10'00);
#elif (CIN_INSTRUCTION_SET) & (CIN_INSTRUCTION_SET_SSE_BIT)
				result.data = _mm_shuffle_ps(matrix.data, matrix.data, 0b11'01'10'00);
#else
				result.raw[0] = matrix.raw[0];
				result.raw[1] = matrix.raw[2];
				result.raw[2] = matrix.raw[1];
				result.raw[3] = matrix.raw[3];
#endif
				return result;
			}
		};

		template<typename ValueType>
		struct MatrixTranspose<4, 4, ValueType>
		{
			CIN_MATH_INLINE static Matrix<4, 4, float> implementation(const Matrix<4, 4, float>& matrix) noexcept
			{
				Matrix<4, 4, float> result;
#if (CIN_INSTRUCTION_SET) & (CIN_INSTRUCTION_SET_AVX_BIT)
				/* a_11, a_31 | a_12, a_32 | a_21, a_41 | a_22, a_42 */
				const __m256 e0{ _mm256_unpacklo_ps(matrix.data[0], matrix.data[1]) };
				/* a_13, a_33 | a_14, a_34 | a_23, a_43 | a_24, a_44 */
				const __m256 e1{ _mm256_unpackhi_ps(matrix.data[0], matrix.data[1]) };

				/* a_11, a_31, a_12, a_32 | a_13, a_33, a_14, a_34 */
				const __m256 e2{ _mm256_permute2f128_ps(e0, e1, 0x20) };
				/* a_21, a_41, a_22, a_42 | a_23, a_43, a_24, a_44 */
				const __m256 e3{ _mm256_permute2f128_ps(e0, e1, 0x31) };

				/* a_11, a_21, a_31, a_41 | a_13, a_23, a_33, a_43 */
				const __m256 e4{ _mm256_unpacklo_ps(e2, e3) };
				/* a_12, a_22, a_32, a_42 | a_14, a_24, a_34, a_44 */
				const __m256 e5{ _mm256_unpackhi_ps(e2, e3) };

				/* a_11, a_21, a_31, a_41 | a_12, a_22, a_32, a_42 */
				result.data[0] = _mm256_permute2f128_ps(e4, e5, 0x20);
				/* a_13, a_23, a_33, a_43 | a_14, a_24, a_34, a_44 */
				result.data[1] = _mm256_permute2f128_ps(e4, e5, 0x31);
#elif (CIN_INSTRUCTION_SET) & (CIN_INSTRUCTION_SET_SSE_BIT)
				/* a_11, a_12, a_21, a_22 */
				__m128 e0{ _mm_shuffle_ps(matrix.data[0], matrix.data[1], 0b01'00'01'00) };
				/* a_13, a_14, a_23, a_24 */
				__m128 e1{ _mm_shuffle_ps(matrix.data[0], matrix.data[1], 0b11'10'11'10) };
				/* a_31, a_32, a_41, a_42 */
				__m128 e2{ _mm_shuffle_ps(matrix.data[2], matrix.data[3], 0b01'00'01'00) };
				/* a_33, a_34, a_43, a_44 */
				__m128 e3{ _mm_shuffle_ps(matrix.data[2], matrix.data[3], 0b11'10'11'10) };

				/* a_11, a_21, a_31, a_41  */
				result.data[0] = _mm_shuffle_ps(e0, e2, 0b10'00'10'00);

				/* a_12, a_22, a_32, a_42  */
				result.data[1] = _mm_shuffle_ps(e0, e2, 0b11'01'11'01);

				/* a_13, a_23, a_33, a_43  */
				result.data[2] = _mm_shuffle_ps(e1, e3, 0b10'00'10'00);

				/* a_14, a_24, a_34, a_44  */
				result.data[3] = _mm_shuffle_ps(e1, e3, 0b11'01'11'01);
#else
				result.raw[0] = matrix.raw[0];
				result.raw[1] = matrix.raw[4];
				result.raw[2] = matrix.raw[8];
				result.raw[3] = matrix.raw[12];

				result.raw[4] = matrix.raw[1];
				result.raw[5] = matrix.raw[5];
				result.raw[6] = matrix.raw[9];
				result.raw[7] = matrix.raw[13];

				result.raw[8] = matrix.raw[2];
				result.raw[9] = matrix.raw[6];
				result.raw[10] = matrix.raw[10];
				result.raw[11] = matrix.raw[14];

				result.raw[12] = matrix.raw[3];
				result.raw[13] = matrix.raw[7];
				result.raw[14] = matrix.raw[11];
				result.raw[15] = matrix.raw[15];
#endif
				return result;
			}
		};

		template<typename ValueType>
		struct MatrixDeterminant<2, 2, ValueType>
		{
			CIN_MATH_INLINE static float implementation(const Matrix<2, 2, float>& matrix) noexcept
			{
				return  matrix[0] * matrix[3] - matrix[2] * matrix[1];
			}
		};

		template<typename ValueType>
		struct MatrixDeterminant<3, 3, ValueType>
		{
			CIN_MATH_INLINE static float implementation(const Matrix<3, 3, float>& matrix) noexcept
			{
				return
					+ matrix.raw[0] * (matrix.raw[4] * matrix.raw[8] - matrix.raw[7] * matrix.raw[5])
					- matrix.raw[3] * (matrix.raw[1] * matrix.raw[8] - matrix.raw[7] * matrix.raw[2])
					+ matrix.raw[6] * (matrix.raw[1] * matrix.raw[5] - matrix.raw[4] * matrix.raw[2]);
			}
		};

		template<typename ValueType>
		struct MatrixDeterminant<4, 4, ValueType>
		{
			CIN_MATH_INLINE static float implementation(const Matrix<4, 4, float>& matrix) noexcept
			{
				const float e00{ matrix[10] * matrix[15] - matrix[14] * matrix[11] };
				const float e01{ matrix[9] * matrix[15] - matrix[13] * matrix[11] };
				const float e02{ matrix[9] * matrix[14] - matrix[13] * matrix[10] };

				const float e03{ matrix[8] * matrix[15] - matrix[12] * matrix[11] };
				const float e04{ matrix[8] * matrix[14] - matrix[12] * matrix[10] };
				const float e05{ matrix[8] * matrix[13] - matrix[12] * matrix[9] };

				const float m00{ matrix[5] * e00 - matrix[6] * e01 + matrix[7] * e02 };
				const float m01{ matrix[4] * e00 - matrix[6] * e03 + matrix[7] * e04 };

				const float m02{ matrix[4] * e01 - matrix[5] * e03 + matrix[7] * e05 };
				const float m03{ matrix[4] * e02 - matrix[5] * e04 + matrix[6] * e05 };
				
				return matrix[0] * m00 - matrix[1] * m01 + matrix[2] * m02 - matrix[3] * m03;
			}
		};

		template<typename ValueType>
		struct MatrixInverse<2, 2, ValueType>
		{
			CIN_MATH_INLINE static Matrix<2, 2, float> implementation(const Matrix<2, 2, float>& matrix) noexcept
			{
				Matrix<2, 2, float> result;
				const float oneOverDeterminant{ 1.0f / (matrix[0] * matrix[3] - matrix[2] * matrix[1]) };

				result.raw[0] = matrix[3] * (+oneOverDeterminant);
				result.raw[1] = matrix[1] * (-oneOverDeterminant);
				result.raw[2] = matrix[2] * (-oneOverDeterminant);
				result.raw[3] = matrix[0] * (+oneOverDeterminant);

				return result;
			}
		};

		template<typename ValueType>
		struct MatrixInverse<3, 3, ValueType>
		{
			CIN_MATH_INLINE static Matrix<3, 3, float> implementation(const Matrix<3, 3, float>& matrix) noexcept
			{
				Matrix<3, 3, float> result;
				const float oneOverDeterminant{ 1.0f / MatrixDeterminant<3, 3, float>::implementation(matrix) };

				result.raw[0] = +(matrix.raw[4] * matrix.raw[8] - matrix.raw[7] * matrix.raw[5]) * oneOverDeterminant;
				result.raw[1] = -(matrix.raw[1] * matrix.raw[8] - matrix.raw[7] * matrix.raw[2]) * oneOverDeterminant;
				result.raw[2] = +(matrix.raw[1] * matrix.raw[5] - matrix.raw[4] * matrix.raw[2]) * oneOverDeterminant;

				result.raw[3] = -(matrix.raw[3] * matrix.raw[8] - matrix.raw[6] * matrix.raw[5]) * oneOverDeterminant;
				result.raw[4] = +(matrix.raw[0] * matrix.raw[8] - matrix.raw[6] * matrix.raw[2]) * oneOverDeterminant;
				result.raw[5] = -(matrix.raw[0] * matrix.raw[5] - matrix.raw[3] * matrix.raw[2]) * oneOverDeterminant;

				result.raw[6] = +(matrix.raw[3] * matrix.raw[7] - matrix.raw[6] * matrix.raw[4]) * oneOverDeterminant;
				result.raw[7] = -(matrix.raw[0] * matrix.raw[7] - matrix.raw[6] * matrix.raw[1]) * oneOverDeterminant;
				result.raw[8] = +(matrix.raw[0] * matrix.raw[4] - matrix.raw[3] * matrix.raw[1]) * oneOverDeterminant;

				return result;
			}
		};

		template<typename ValueType>
		struct MatrixInverse<4, 4, ValueType>
		{
			CIN_MATH_INLINE static Matrix<4, 4, float> implementation(const Matrix<4, 4, float>& matrix) noexcept
			{
				/* TODO: Unimplemented */
				Matrix<4, 4, float> result;
				assert(false);
#if 0
				__m128 minor0, minor1, minor2, minor3;
				__m128 row0,
					row1{ 0.0f, 0.0f, 0.0f, 0.0f },
					row2{ 0.0f, 0.0f, 0.0f, 0.0f },
					row3{ 0.0f, 0.0f, 0.0f, 0.0f };

				__m128 det;
				__m128 tmp1{ 0.0f, 0.0f, 0.0f, 0.0f };

				float* src = const_cast<float*>(matrix.operator const float* ());
				float* dst = result.raw;

				tmp1 = _mm_loadh_pi(_mm_loadl_pi(tmp1, (__m64*)(src)), (__m64*)(src + 4));
				row1 = _mm_loadh_pi(_mm_loadl_pi(row1, (__m64*)(src + 8)), (__m64*)(src + 12));

				row0 = _mm_shuffle_ps(tmp1, row1, 0x88);
				row1 = _mm_shuffle_ps(row1, tmp1, 0xDD);

				tmp1 = _mm_loadh_pi(_mm_loadl_pi(tmp1, (__m64*)(src + 2)), (__m64*)(src + 6));
				row3 = _mm_loadh_pi(_mm_loadl_pi(row3, (__m64*)(src + 10)), (__m64*)(src + 14));

				row2 = _mm_shuffle_ps(tmp1, row3, 0x88);
				row3 = _mm_shuffle_ps(row3, tmp1, 0xDD);

				tmp1 = _mm_mul_ps(row2, row3);
				tmp1 = _mm_shuffle_ps(tmp1, tmp1, 0xB1);

				minor0 = _mm_mul_ps(row1, tmp1);
				minor1 = _mm_mul_ps(row0, tmp1);

				tmp1 = _mm_shuffle_ps(tmp1, tmp1, 0x4E);

				minor0 = _mm_sub_ps(_mm_mul_ps(row1, tmp1), minor0);
				minor1 = _mm_sub_ps(_mm_mul_ps(row0, tmp1), minor1);
				minor1 = _mm_shuffle_ps(minor1, minor1, 0x4E);

				tmp1 = _mm_mul_ps(row1, row2);
				tmp1 = _mm_shuffle_ps(tmp1, tmp1, 0xB1);

				minor0 = _mm_add_ps(_mm_mul_ps(row3, tmp1), minor0);
				minor3 = _mm_mul_ps(row0, tmp1);

				tmp1 = _mm_shuffle_ps(tmp1, tmp1, 0x4E);

				minor0 = _mm_sub_ps(minor0, _mm_mul_ps(row3, tmp1));
				minor3 = _mm_sub_ps(_mm_mul_ps(row0, tmp1), minor3);
				minor3 = _mm_shuffle_ps(minor3, minor3, 0x4E);

				tmp1 = _mm_mul_ps(_mm_shuffle_ps(row1, row1, 0x4E), row3);
				tmp1 = _mm_shuffle_ps(tmp1, tmp1, 0xB1);
				row2 = _mm_shuffle_ps(row2, row2, 0x4E);

				minor0 = _mm_add_ps(_mm_mul_ps(row2, tmp1), minor0);
				minor2 = _mm_mul_ps(row0, tmp1);

				tmp1 = _mm_shuffle_ps(tmp1, tmp1, 0x4E);

				minor0 = _mm_sub_ps(minor0, _mm_mul_ps(row2, tmp1));
				minor2 = _mm_sub_ps(_mm_mul_ps(row0, tmp1), minor2);
				minor2 = _mm_shuffle_ps(minor2, minor2, 0x4E);

				tmp1 = _mm_mul_ps(row0, row1);
				tmp1 = _mm_shuffle_ps(tmp1, tmp1, 0xB1);

				minor2 = _mm_add_ps(_mm_mul_ps(row3, tmp1), minor2);
				minor3 = _mm_sub_ps(_mm_mul_ps(row2, tmp1), minor3);

				tmp1 = _mm_shuffle_ps(tmp1, tmp1, 0x4E);

				minor2 = _mm_sub_ps(_mm_mul_ps(row3, tmp1), minor2);
				minor3 = _mm_sub_ps(minor3, _mm_mul_ps(row2, tmp1));

				tmp1 = _mm_mul_ps(row0, row3);
				tmp1 = _mm_shuffle_ps(tmp1, tmp1, 0xB1);

				minor1 = _mm_sub_ps(minor1, _mm_mul_ps(row2, tmp1));
				minor2 = _mm_add_ps(_mm_mul_ps(row1, tmp1), minor2);

				tmp1 = _mm_shuffle_ps(tmp1, tmp1, 0x4E);

				minor1 = _mm_add_ps(_mm_mul_ps(row2, tmp1), minor1);
				minor2 = _mm_sub_ps(minor2, _mm_mul_ps(row1, tmp1));

				tmp1 = _mm_mul_ps(row0, row2);
				tmp1 = _mm_shuffle_ps(tmp1, tmp1, 0xB1);

				minor1 = _mm_add_ps(_mm_mul_ps(row3, tmp1), minor1);
				minor3 = _mm_sub_ps(minor3, _mm_mul_ps(row1, tmp1));

				tmp1 = _mm_shuffle_ps(tmp1, tmp1, 0x4E);

				minor1 = _mm_sub_ps(minor1, _mm_mul_ps(row3, tmp1));
				minor3 = _mm_add_ps(_mm_mul_ps(row1, tmp1), minor3);

				det = _mm_mul_ps(row0, minor0);
				det = _mm_add_ps(_mm_shuffle_ps(det, det, 0x4E), det);
				det = _mm_add_ss(_mm_shuffle_ps(det, det, 0xB1), det);

				tmp1 = _mm_rcp_ss(det);

				det = _mm_sub_ss(_mm_add_ss(tmp1, tmp1), _mm_mul_ss(det, _mm_mul_ss(tmp1, tmp1)));
				det = _mm_shuffle_ps(det, det, 0x00);

				minor0 = _mm_mul_ps(det, minor0);
				_mm_storel_pi((__m64*)(dst), minor0);
				_mm_storeh_pi((__m64*)(dst + 2), minor0);

				minor1 = _mm_mul_ps(det, minor1);
				_mm_storel_pi((__m64*)(dst + 4), minor1);
				_mm_storeh_pi((__m64*)(dst + 6), minor1);

				minor2 = _mm_mul_ps(det, minor2);
				_mm_storel_pi((__m64*)(dst + 8), minor2);
				_mm_storeh_pi((__m64*)(dst + 10), minor2);

				minor3 = _mm_mul_ps(det, minor3);
				_mm_storel_pi((__m64*)(dst + 12), minor3);
				_mm_storeh_pi((__m64*)(dst + 14), minor3);
#endif
				return result;
			}
		};

		template<typename ValueType>
		struct QuaternionConugate
		{
			CIN_MATH_INLINE static QuaternionBase<ValueType> implementation(const QuaternionBase<ValueType>& quaternion) noexcept
			{
				QuaternionBase<ValueType> result;

				result.raw[0] = +quaternion.raw[0];
				result.raw[1] = -quaternion.raw[1];
				result.raw[2] = -quaternion.raw[2];
				result.raw[3] = -quaternion.raw[3];

				return result;
			}
		};

		template<typename ValueType>
		struct QuaternionNorm
		{
			CIN_MATH_INLINE static ValueType implementation(const QuaternionBase<ValueType>& quaternion) noexcept
			{
				return std::sqrt(
					+quaternion.raw[0] * quaternion.raw[0]
					+ quaternion.raw[1] * quaternion.raw[1]
					+ quaternion.raw[2] * quaternion.raw[2]
					+ quaternion.raw[3] * quaternion.raw[3]);
			}
		};

		template<typename ValueType>
		struct QuaternionNormSquared
		{
			CIN_MATH_INLINE static ValueType implementation(const QuaternionBase<ValueType>& quaternion) noexcept
			{
				return
					+ quaternion.raw[0] * quaternion.raw[0]
					+ quaternion.raw[1] * quaternion.raw[1]
					+ quaternion.raw[2] * quaternion.raw[2]
					+ quaternion.raw[3] * quaternion.raw[3];
			}
		};

		template<typename ValueType>
		struct QuaternionNormalize
		{
			CIN_MATH_INLINE static QuaternionBase<ValueType> implementation(const QuaternionBase<ValueType>& quaternion) noexcept
			{
				QuaternionBase<ValueType> result;
				const ValueType norm{ Norm(quaternion) };

				result.raw[0] = quaternion.raw[0] / norm;
				result.raw[1] = quaternion.raw[1] / norm;
				result.raw[2] = quaternion.raw[2] / norm;
				result.raw[3] = quaternion.raw[3] / norm;

				return result;
			}
		};

		template<typename ValueType>
		struct QuaternionInverse
		{
			CIN_MATH_INLINE static QuaternionBase<ValueType> implementation(const QuaternionBase<ValueType>& quaternion) noexcept
			{
				return Conjugate(quaternion) / NormSquared(quaternion);
			}
		};

		template<typename ValueType>
		struct QuaternionRotate
		{
			CIN_MATH_INLINE static QuaternionBase<float> implementation(const Vector<3, float>& vector, const QuaternionBase<float>& rotation) noexcept
			{
				assert(false);
			}
		};

		template<typename ValueType>
		struct QuaternionAxisAngleToQuaternion
		{
			CIN_MATH_INLINE static QuaternionBase<float> implementation(const Vector<3, float>& axisAngle, const float radianAngle) noexcept
			{
				QuaternionBase<float> result;

				result.raw[0] = std::cosf(radianAngle * 0.5f);
				result.raw[1] = axisAngle.raw[0] * std::sinf(radianAngle * 0.5f);
				result.raw[2] = axisAngle.raw[1] * std::sinf(radianAngle * 0.5f);
				result.raw[3] = axisAngle.raw[2] * std::sinf(radianAngle * 0.5f);

				return result;
			}

			CIN_MATH_INLINE static QuaternionBase<float> implementation(const Vector<4, float>& axisAngle) noexcept
			{
				QuaternionBase<float> result;
				const float halfTheta{ axisAngle.w * 0.5f };
				const float sinHalfTheta{ std::sinf(halfTheta) };

				result.raw[0] = std::cosf(halfTheta);
				result.raw[1] = axisAngle.raw[0] * sinHalfTheta;
				result.raw[2] = axisAngle.raw[1] * sinHalfTheta;
				result.raw[3] = axisAngle.raw[2] * sinHalfTheta;

				return result;
			}
		};

		template<typename ValueType>
		struct QuaternionToAxisAngle
		{
			CIN_MATH_INLINE static Vector<4, float> implementation(const QuaternionBase<float>& quaternion) noexcept
			{
				Vector<4, float> result;
				const float theta{ 2.0f * std::acosf(quaternion.raw[0]) };
				const float sinHalfTheta{ std::sinf(theta) * 0.5f };

				result.raw[0] = quaternion.raw[1] / sinHalfTheta;
				result.raw[1] = quaternion.raw[2] / sinHalfTheta;
				result.raw[2] = quaternion.raw[3] / sinHalfTheta;
				result.raw[3] = theta;

				return result;
			}
		};

		template<typename ValueType>
		struct PerspectiveProjection
		{
			CIN_MATH_INLINE static Matrix<4, 4, float> implementation(const ValueType FOV, const ValueType aspectRatio, const ValueType nearClip, const ValueType farClip) noexcept
			{
				Matrix<4, 4, float> result;
				return result;
			}
		};
	}

	template<Length_t length, typename ValueType>
	CIN_MATH_INLINE ValueType Length(const Vector<length, ValueType>& vector) noexcept
	{
		return Implementation::VectorLength<length, ValueType>::implementation(vector);
	}

	template<Length_t length, typename ValueType>
	CIN_MATH_INLINE ValueType Dot(const Vector<length, ValueType>& lhs, const Vector<length, ValueType>& rhs) noexcept
	{
		return Implementation::VectorDot<length, ValueType>::implementation(lhs, rhs);
	}

	template<Length_t length, typename ValueType>
	CIN_MATH_INLINE Vector<length, ValueType> Cross(const Vector<length, ValueType>& lhs, const Vector<length, ValueType>& rhs) noexcept
	{
		return Implementation::VectorCross<length, ValueType>::implementation(lhs, rhs);
	}

	template<Length_t rows, Length_t columns, typename ValueType>
	CIN_MATH_INLINE Matrix<rows, columns, ValueType> Transpose(const Matrix<rows, columns, ValueType>& matrix) noexcept
	{
		return Implementation::MatrixTranspose<rows, columns, ValueType>::implementation(matrix);
	}

	template<Length_t rows, Length_t columns, typename ValueType>
	CIN_MATH_INLINE ValueType Determinant(const Matrix<rows, columns, ValueType>& matrix) noexcept
	{
		return Implementation::MatrixDeterminant<rows, columns, ValueType>::implementation(matrix);
	}

	template<Length_t rows, Length_t columns, typename ValueType>
	CIN_MATH_INLINE Matrix<rows, columns, ValueType> Inverse(const Matrix<rows, columns, ValueType>& matrix) noexcept
	{
		return Implementation::MatrixInverse<rows, columns, ValueType>::implementation(matrix);
	}

	template<typename ValueType>
	CIN_MATH_INLINE QuaternionBase<ValueType> Conjugate(const QuaternionBase<ValueType>& quaternion) noexcept
	{
		return Implementation::QuaternionConugate<ValueType>::implementation(quaternion);
	}

	template<typename ValueType>
	CIN_MATH_INLINE ValueType Norm(const QuaternionBase<ValueType>& quaternion) noexcept
	{
		return Implementation::QuaternionNorm<ValueType>::implementation(quaternion);
	}

	template<typename ValueType>
	CIN_MATH_INLINE ValueType NormSquared(const QuaternionBase<ValueType>& quaternion) noexcept
	{
		return Implementation::QuaternionNormSquared<ValueType>::implementation(quaternion);
	}

	template<typename ValueType>
	CIN_MATH_INLINE QuaternionBase<ValueType> Normalize(const QuaternionBase<ValueType>& quaternion) noexcept
	{
		return Implementation::QuaternionNormalize<ValueType>::implementation(quaternion);
	}

	template<typename ValueType>
	CIN_MATH_INLINE QuaternionBase<ValueType> Inverse(const QuaternionBase<ValueType>& quaternion) noexcept
	{
		return Implementation::QuaternionInverse<ValueType>::implementation(quaternion);
	}

	template<typename ValueType>
	CIN_MATH_INLINE Vector<3, ValueType> Rotate(const Vector<3, ValueType>& vector, const QuaternionBase<ValueType>& rotation) noexcept
	{
		return Implementation::QuaternionRotate<ValueType>::implementation(vector, rotation);
	}

	template<typename ValueType>
	CIN_MATH_INLINE QuaternionBase<ValueType> AxisAngleToQuaternion(const Vector<3, ValueType>& vector, const ValueType angle) noexcept
	{
		return Implementation::QuaternionAxisAngleToQuaternion<ValueType>::implementation(vector, angle);
	}

	template<typename ValueType>
	CIN_MATH_INLINE QuaternionBase<ValueType> AxisAngleToQuaternion(const Vector<4, ValueType>& vector) noexcept
	{
		return Implementation::QuaternionAxisAngleToQuaternion<ValueType>::implementation(vector);
	}

	template<typename ValueType>
	CIN_MATH_INLINE Vector<4, ValueType> QuaternionToAxisAngle(const QuaternionBase<ValueType>& quaternion) noexcept
	{
		return Implementation::QuaternionToAxisAngle<ValueType>::implementation(quaternion);
	}

	template<typename ValueType>
	CIN_MATH_INLINE Matrix<4, 4, ValueType> PerspectiveProjection(const ValueType FOV, const ValueType aspectRatio, const ValueType nearClip, const ValueType farClip) noexcept
	{
		return Implementation::PerspectiveProjection<ValueType>::implementation(FOV, aspectRatio, nearClip, farClip);
	}

	template<Length_t rows, Length_t columns, typename ValueType>
	CIN_MATH_INLINE Matrix<rows, columns, ValueType> Translate(const Matrix<rows, columns, ValueType>& matrix, const Vector<3, ValueType>& translation) noexcept
	{
		return Implementation::MatrixTranslate<rows, columns, ValueType>::implementation(matrix, translation);
	}

	template<Length_t rows, Length_t columns, typename ValueType>
	CIN_MATH_INLINE Matrix<rows, columns, ValueType> Translate(const Matrix<rows, columns, ValueType>& matrix, const Vector<4, ValueType>& translation) noexcept
	{
		return Implementation::MatrixTranslate<rows, columns, ValueType>::implementation(matrix, translation);
	}

	template<Length_t rows, Length_t columns, typename ValueType>
	CIN_MATH_INLINE Matrix<rows, columns, ValueType> TranslateIdentity(const Vector<3, ValueType>& translation) noexcept
	{
		return Implementation::MatrixTranslateIdentity<rows, columns, ValueType>::implementation(translation);
	}

	template<Length_t rows, Length_t columns, typename ValueType>
	CIN_MATH_INLINE Matrix<rows, columns, ValueType> TranslateIdentity(const Vector<4, ValueType>& translation) noexcept
	{
		return Implementation::MatrixTranslateIdentity<rows, columns, ValueType>::implementation(translation);
	}
}