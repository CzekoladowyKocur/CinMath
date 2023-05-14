#pragma once

namespace CinMath {
	/**
	 * Converts an angle in degrees to radians
	 * 
	 * @param input degrees
	 * @return angle in radians
	 */
	template<typename ValueType>
	constexpr CIN_MATH_INLINE ValueType ToRadians(const ValueType degrees) noexcept
	{
		static_assert(std::is_floating_point_v<ValueType>, "Floating point conversion only is supported");
		return degrees * AtCompileTime(Constants::PI<ValueType> / static_cast<ValueType>(180U));
	}

	/**
	 * Converts an angle in radians to degrees
	 * 
	 * @param input radians
	 * @return angle in degrees
	 */
	template<typename ValueType>
	constexpr CIN_MATH_INLINE ValueType ToDegrees(const ValueType radians) noexcept
	{
		static_assert(std::is_floating_point_v<ValueType>, "Floating point conversion only is supported");
		return radians * AtCompileTime(static_cast<ValueType>(180U) / Constants::PI<ValueType>);
	}

	/**
	 * Calculates the length of a given vector
	 * 
	 * @param input vector
	 * @return length of the input vector
	 */
	template<Length_t length, typename ValueType>
	CIN_MATH_INLINE ValueType Length(const Vector<length, ValueType>& vector) noexcept;

	/**
	 * Normalizes a given vector
	 * 
	 * @param input vector
	 * @return normalized input vector
	 */
	template<Length_t length, typename ValueType>
	CIN_MATH_INLINE Vector<length, ValueType> Normalize(const Vector<length, ValueType>& vector) noexcept;

	/**
	 * Calculates the dot product of two vectors
	 * 
	 * @param lhs 
	 * @param rhs
	 * @return dot product of input vectors
	 */
	template<Length_t length, typename ValueType>
	CIN_MATH_INLINE ValueType Dot(const Vector<length, ValueType>& lhs, const Vector<length, ValueType>& rhs) noexcept;

	/**
	 * Calculates the cross product of two vectors
	 * 
	 * @param lhs
	 * @param rhs
	 * @return cross product of input vectors
	 */
	template<Length_t length, typename ValueType>
	CIN_MATH_INLINE Vector<length, ValueType> Cross(const Vector<length, ValueType>& lhs, const Vector<length, ValueType>& rhs) noexcept;

	/**
	 * Transposes a given matrix. In linear algebra, the transpose of a matrix is an operator which flips a matrix over its diagonal;
	 * that is, it switches the row and column indices of the matrix A by producing another matrix, often denoted by A^T
	 * https://en.wikipedia.org/wiki/Transpose
	 * 
	 * @param input matrix
	 * @return transposed input matrix
	 */
	template<Length_t rows, Length_t columns, typename ValueType>
	CIN_MATH_INLINE Matrix<rows, columns, ValueType> Transpose(const Matrix<rows, columns, ValueType>& matrix) noexcept;

	/**
	 * Calculates the determinant of a given matrix
	 * 
	 * @param input matrix
	 * @return determinant value of input matrix
	 */
	template<Length_t rows, Length_t columns, typename ValueType>
	CIN_MATH_INLINE ValueType Determinant(const Matrix<rows, columns, ValueType>& matrix) noexcept;

	/**
	 * Calculates the inverse of a given matrix
	 * 
	 * @param input matrix
	 * @return inverse of input matrix
	 */
	template<Length_t rows, Length_t columns, typename ValueType>
	CIN_MATH_INLINE Matrix<rows, columns, ValueType> Inverse(const Matrix<rows, columns, ValueType>& matrix) noexcept;

	/**
	 * Calculates the conjugate of a given quaternion
	 * 
	 * @param input quaternion
	 * @return conjugate of input quaternion
	 */
	template<typename ValueType>
	CIN_MATH_INLINE TQuaternion<ValueType> Conjugate(const TQuaternion<ValueType>& quaternion) noexcept;

	/**
	 * Calculates the norm (length) of a given quaternion
	 * 
	 * @param input quaternion
	 * @return norm of input quaternion
	 */
	template<typename ValueType>
	CIN_MATH_INLINE ValueType Norm(const TQuaternion<ValueType>& quaternion) noexcept;

	/**
	 * Calculates the squared norm (length) of a given quaternion
	 * 
	 * @param input quaternion
	 * @return squared norm of input quaternion
	 */
	template<typename ValueType>
	CIN_MATH_INLINE ValueType NormSquared(const TQuaternion<ValueType>& quaternion) noexcept;

	/**
	 * Normalizes a given quaternion
	 * 
	 * @param input quaternion
	 * @return Normalized input quaternion
	 */
	template<typename ValueType>
	CIN_MATH_INLINE TQuaternion<ValueType> Normalize(const TQuaternion<ValueType>& quaternion) noexcept;

	/**
	 * Calculates the inverse of a given quaternion
	 * 
	 * @param input quaternion
	 * @return inverse of input quaternion
	 */
	template<typename ValueType>
	CIN_MATH_INLINE TQuaternion<ValueType> Inverse(const TQuaternion<ValueType>& quaternion) noexcept;

	/**
	 * Rotates the vector by a given quaternion (in unit form)
	 * 
	 * @param input vector to be rotated
	 * @param input quaternion
	 * @return rotated input vector by input quaternion
	 */
	template<typename ValueType>
	CIN_MATH_INLINE Vector<3, ValueType> Rotate(const Vector<3, ValueType>& vector, const TQuaternion<ValueType>& rotation) noexcept;

	/**
	 * Calculates quaternion in unit form based off an axis and angle specified in radians.
	 * 
	 * @param input vector, an arbitrary axis of rotation
	 * @param input angle, the angle of rotation
	 * @return quaternion of rotation in unit form
	 */
	template<typename ValueType>
	CIN_MATH_INLINE TQuaternion<ValueType> AxisAngleToQuaternion(const Angle angle, const Vector<3, ValueType>& vector) noexcept;

	/**
	 * Calculates quaternion in unit form based off an axis angle. The function reads the x element of the vector as the rotation angle (in radians)
	 * and the y, z, w components as the arbitrary axis.
	 *
	 * @param input vector, vector.x -> angle in radians, vector.yzw -> an arbitrary axis of rotation
	 * @return quaternion of rotation in unit form
	 */
	template<typename ValueType>
	CIN_MATH_INLINE TQuaternion<ValueType> AxisAngleToQuaternion(const Vector<4, ValueType>& vector) noexcept;

	/**
	 * Converts a given unit form quaternion to an axis angle
	 * 
	 * @param input quaternion
	 * @return axis angle vector, vector.x -> angle in radians, vector.yzw -> an arbitrary axis of rotation
	 */
	template<typename ValueType>
	CIN_MATH_INLINE Vector<4, ValueType> QuaternionToAxisAngle(const TQuaternion<ValueType>& quaternion) noexcept;

	/**
	 * Translates a given matrix by a vector
	 * 
	 * @param input matrix
	 * @param input vector (translation)
	 * @return Translated input matrix by the given input vector
	 */
	template<Length_t rows, Length_t columns, typename ValueType>
	CIN_MATH_INLINE Matrix<rows, columns, ValueType> Translate(const Matrix<rows, columns, ValueType>& matrix, const Vector<3, ValueType>& translation) noexcept;

	/**
	 * Translates a given matrix by a vector
	 *
	 * @param input matrix
	 * @param input vector (translation)
	 * @return Translated input matrix by the given input vector
	 * @note The w component of translation component should be equal to 0
	 */
	template<Length_t rows, Length_t columns, typename ValueType>
	CIN_MATH_INLINE Matrix<rows, columns, ValueType> Translate(const Matrix<rows, columns, ValueType>& matrix, const Vector<4, ValueType>& translation) noexcept;

	/**
	 * Translates an identity matrix by a vector
	 *
	 * @param input vector (translation)
	 * @return Translated identity matrix by the given input vector
	 */
	template<Length_t rows, Length_t columns, typename ValueType>
	CIN_MATH_INLINE Matrix<rows, columns, ValueType> TranslateIdentity(const Vector<3, ValueType>& translation) noexcept;

	/**
	 * Translates an identity matrix by a vector
	 *
	 * @param input vector (translation)
	 * @return Translated identity matrix by the given input vector
	 * @note The w component of translation component should be equal to 0
	 */
	template<Length_t rows, Length_t columns, typename ValueType>
	CIN_MATH_INLINE Matrix<rows, columns, ValueType> TranslateIdentity(const Vector<4, ValueType>& translation) noexcept;

	/**
	 * Rotates a given matrix by an angle (in radians) around an arbitrary axis
	 * 
	 * @param input matrix
	 * @param input axis
	 * @param input angle (in radians)
	 * @return Rotated input matrix by the input angle around the input axis
	 */
	template<Length_t rows, Length_t columns, typename ValueType>
	CIN_MATH_INLINE Matrix<rows, columns, ValueType> Rotate(const Matrix<rows, columns, ValueType>& matrix, const Vector<3, ValueType>& axis, const TAngle<ValueType> rotation) noexcept;

	/**
	 * Rotates an identity matrix by an angle (in radians) around an arbitrary axis
	 *
	 * @param input axis
	 * @param input angle (in radians)
	 * @return Rotated identity matrix by the input angle around the input axis
	 */
	template<Length_t rows, Length_t columns, typename ValueType>
	CIN_MATH_INLINE Matrix<rows, columns, ValueType> RotateIdentity(const Vector<3, ValueType>& axis, const TAngle<ValueType> rotation) noexcept;

	/**
	 * Rotates a given matrix by an angle (in radians) around the x axis
	 *
	 * @param input matrix
	 * @param input angle (in radians)
	 * @return Rotated input matrix by the input angle around the x axis
	 */
	template<Length_t rows, Length_t columns, typename ValueType>
	CIN_MATH_INLINE Matrix<rows, columns, ValueType> RotateX(const Matrix<rows, columns, ValueType>& matrix, const TAngle<ValueType> rotation) noexcept;

	/**
	 * Rotates an identity matrix by an angle (in radians) around the x axis
	 *
	 * @param input angle (in radians)
	 * @return Rotated identity matrix by the input angle around the x axis
	 */
	template<Length_t rows, Length_t columns, typename ValueType>
	CIN_MATH_INLINE Matrix<rows, columns, ValueType> RotateXIdentity(const TAngle<ValueType> rotation) noexcept;

	/**
	 * Rotates a given matrix by an angle (in radians) around the y axis
	 *
	 * @param input matrix
	 * @param input angle (in radians)
	 * @return Rotated input matrix by the input angle around the y axis
	 */
	template<Length_t rows, Length_t columns, typename ValueType>
	CIN_MATH_INLINE Matrix<rows, columns, ValueType> RotateY(const Matrix<rows, columns, ValueType>& matrix, const TAngle<ValueType> rotation) noexcept;

	/**
	 * Rotates an identity matrix by an angle (in radians) around the y axis
	 *
	 * @param input angle (in radians)
	 * @return Rotated identity matrix by the input angle around the y axis
	 */
	template<Length_t rows, Length_t columns, typename ValueType>
	CIN_MATH_INLINE Matrix<rows, columns, ValueType> RotateYIdentity(const TAngle<ValueType> rotation) noexcept;

	/**
	 * Rotates a given matrix by an angle (in radians) around the z axis
	 *
	 * @param input matrix
	 * @param input angle (in radians)
	 * @return Rotated input matrix by the input angle around the z axis
	 */
	template<Length_t rows, Length_t columns, typename ValueType>
	CIN_MATH_INLINE Matrix<rows, columns, ValueType> RotateZ(const Matrix<rows, columns, ValueType>& matrix, const TAngle<ValueType> rotation) noexcept;

	/**
	 * Rotates an identity matrix by an angle (in radians) around the z axis
	 *
	 * @param input angle (in radians)
	 * @return Rotated identity matrix by the input angle around the z axis
	 */
	template<Length_t rows, Length_t columns, typename ValueType>
	CIN_MATH_INLINE Matrix<rows, columns, ValueType> RotateZIdentity(const TAngle<ValueType> rotation) noexcept;

	/**
	 * Calculates the perspective projection
	 *
	 * @param orthoLeft orthographic left
	 * @param orthoRight orthographic right
	 * @param orthoBottom orthographic bottom
	 * @param orthoTop orthographic top
	 */
	template<typename ValueType>
	CIN_MATH_INLINE Matrix<4, 4, ValueType> OrthographicProjection(const ValueType orthoLeft, const ValueType orthoRight, const ValueType orthoBottom, const ValueType orthoTop) noexcept;

	/**
	 * Calculates the perspective projection
	 * 
	 * @param FOV Field of view
	 * @param aspectRatio Aspect ratio
	 * @param nearClip The near clip space
	 * @param farClip The far clip space
	 */
	template<typename ValueType>
	CIN_MATH_INLINE Matrix<4, 4, ValueType> PerspectiveProjection(const ValueType FOV, const ValueType aspectRatio, const ValueType nearClip, const ValueType farClip) noexcept;

	namespace Implementation {
		/* Vectors */
		template<Length_t length, typename ValueType>
		struct VectorLength;

		template<Length_t length, typename ValueType>
		struct VectorNormalize;

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
		struct MatrixRotate;

		template<Length_t rows, Length_t columns, typename ValueType>
		struct MatrixRotateIdentity;

		template<Length_t rows, Length_t columns, typename ValueType>
		struct MatrixRotateX;

		template<Length_t rows, Length_t columns, typename ValueType>
		struct MatrixRotateXIdentity;

		template<Length_t rows, Length_t columns, typename ValueType>
		struct MatrixRotateY;

		template<Length_t rows, Length_t columns, typename ValueType>
		struct MatrixRotateYIdentity;

		template<Length_t rows, Length_t columns, typename ValueType>
		struct MatrixRotateZ;

		template<Length_t rows, Length_t columns, typename ValueType>
		struct MatrixRotateZIdentity;

		template<Length_t rows, Length_t columns, typename ValueType>
		struct MatrixScale;

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
		struct QuaternionQuaternionToAxisAngle;

		template<typename ValueType>
		struct OrthographicProjection;

		template<typename ValueType>
		struct PerspectiveProjection;

		/* Vector length */
		template<typename ValueType>
		struct VectorLength<2, ValueType> final
		{
			CIN_MATH_INLINE static ValueType implementation(const Vector<2, ValueType>& vector) noexcept
			{
				return std::sqrt(vector.raw[0] * vector.raw[0] + vector.raw[1] * vector.raw[1]);
			}
		};

		template<typename ValueType>
		struct VectorLength<3, ValueType> final
		{
			CIN_MATH_INLINE static ValueType implementation(const Vector<3, ValueType>& vector) noexcept
			{
				return std::sqrt(vector.raw[0] * vector.raw[0] + vector.raw[1] * vector.raw[1] + vector.raw[2] * vector.raw[2]);
			}
		};

		template<typename ValueType>
		struct VectorLength<4, ValueType> final
		{
			CIN_MATH_INLINE static ValueType implementation(const Vector<4, ValueType>& vector) noexcept
			{
				return std::sqrt(vector.raw[0] * vector.raw[0] + vector.raw[1] * vector.raw[1] + vector.raw[2] * vector.raw[2] + vector.raw[3] * vector.raw[3]);
			}
		};

		/* Vector normalize */
		template<typename ValueType>
		struct VectorNormalize<2, ValueType> final
		{
			CIN_MATH_INLINE static Vector<2, ValueType> implementation(const Vector<2, ValueType>& vector) noexcept
			{
				return vector / Length(vector);
			}
		};

		template<typename ValueType>
		struct VectorNormalize<3, ValueType> final
		{
			CIN_MATH_INLINE static Vector<3, ValueType> implementation(const Vector<3, ValueType>& vector) noexcept
			{
				return vector / Length(vector);
			}
		};

		template<typename ValueType>
		struct VectorNormalize<4, ValueType> final
		{
			CIN_MATH_INLINE static Vector<4, ValueType> implementation(const Vector<4, ValueType>& vector) noexcept
			{
				return vector / Length(vector);
			}
		};

		/* Dot product */
		template<typename ValueType>
		struct VectorDot<2, ValueType> final
		{
			CIN_MATH_INLINE static ValueType implementation(const Vector<2, ValueType>& lhs, const Vector<2, ValueType>& rhs) noexcept
			{
				return lhs.raw[0] * rhs.raw[0] + lhs.raw[1] * rhs.raw[1];
			}
		};

		template<typename ValueType>
		struct VectorDot<3, ValueType> final
		{
			CIN_MATH_INLINE static ValueType implementation(const Vector<3, ValueType>& lhs, const Vector<3, ValueType>& rhs) noexcept
			{
				return lhs.raw[0] * rhs.raw[0] + lhs.raw[1] * rhs.raw[1] + lhs.raw[2] * rhs.raw[2];
			}
		};

		template<typename ValueType>
		struct VectorDot<4, ValueType> final
		{
			CIN_MATH_INLINE static ValueType implementation(const Vector<4, ValueType>& lhs, const Vector<4, ValueType>& rhs) noexcept
			{
				return lhs.raw[0] * rhs.raw[0] + lhs.raw[1] * rhs.raw[1] + lhs.raw[2] * rhs.raw[2] + lhs.raw[3] * rhs.raw[3];
			}
		};

		/* Cross product */
		template<typename ValueType>
		struct VectorCross<3, ValueType> final
		{
			CIN_MATH_INLINE static Vector<3, float> implementation(const Vector<3, float>& lhs, const Vector<3, float>& rhs) noexcept
			{
				Vector<3, float> result;

				result.raw[0] = lhs[1] * rhs[2] - lhs[2] * rhs[1];
				result.raw[1] = lhs[2] * rhs[0] - lhs[0] * rhs[2];
				result.raw[2] = lhs[0] * rhs[1] - lhs[1] * rhs[0];

				return result;
			}

			CIN_MATH_INLINE static Vector<3, double> implementation(const Vector<3, double>& lhs, const Vector<3, double>& rhs) noexcept
			{
				Vector<3, double> result;

				result.raw[0] = lhs[1] * rhs[2] - lhs[2] * rhs[1];
				result.raw[1] = lhs[2] * rhs[0] - lhs[0] * rhs[2];
				result.raw[2] = lhs[0] * rhs[1] - lhs[1] * rhs[0];

				return result;
			}
		};

		template<typename ValueType>
		struct VectorCross<4, ValueType> final
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

			CIN_MATH_INLINE static Vector<4, double> implementation(const Vector<4, double>& lhs, const Vector<4, double>& rhs) noexcept
			{
				Vector<4, double> result;
				
				result.raw[0] = lhs[1] * rhs[2] - lhs[2] * rhs[1];
				result.raw[1] = lhs[2] * rhs[0] - lhs[0] * rhs[2];
				result.raw[2] = lhs[0] * rhs[1] - lhs[1] * rhs[0];

				return result;
			}
		};

		template<typename ValueType>
		struct MatrixTranslate<4, 4, ValueType> final
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
		struct MatrixTranslateIdentity<4, 4, ValueType> final
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
				return Matrix<4, 4, float> 
				{
					1.0f, 0.0f, 0.0f, 0.0f,
					0.0f, 1.0f, 0.0f, 0.0f,
					0.0f, 0.0f, 1.0f, 0.0f,
					translation.raw[0], translation.raw[1], translation.raw[2], 1.0f
				};
			}
		};

		template<typename ValueType>
		struct MatrixRotate<4, 4, ValueType> final
		{
			CIN_MATH_INLINE static Matrix<4, 4, float> implementation(const Matrix<4, 4, float>& matrix, const Vector<3, float>& axis, const float rotation) noexcept
			{
				const Vector<3, float> a{ Normalize(axis) };

				const float s{ std::sin(rotation) };
				const float c{ std::cos(rotation) };

				/*
					c + (1 - c)x^2, (1 - c)xy - sz, (1 - c)xz + sy,
					(1 - c)xy + sz, c + (1 - c)y^2, (1 - c)yz - sx,
					(1 - c)xz - sy, (1 - c)yz + sx, c + (1 - c)z^2
				*/
				return Matrix<4, 4, float>
				{
					{					
						c + (1.0f - c) * (a.x * a.x), (1.0f - c) * a.x * a.y - s * a.z, (1.0f - c) * a.x * a.z + s * a.y, 0.0f,
						(1.0f - c) * a.x * a.y + s * a.z, c + (1.0f - c) * (a.y * a.y), (1.0f - c) * a.y * a.z - s * a.x, 0.0f,
						(1.0f - c) * a.x * a.z - s * a.y, (1.0f - c) * a.y * a.z + s * a.x, c + (1.0f - c) * (a.z * a.z), 0.0f,
						0.0f, 0.0f, 0.0f, 1.0f
					}
				} * matrix;
			}

			CIN_MATH_INLINE static Matrix<4, 4, float> implementation(const Matrix<4, 4, float>& matrix, const TQuaternion<float>& quaternion) noexcept
			{
				const auto normalizedQuaternion{ Normalize(quaternion) };

				const float x{ normalizedQuaternion.vector.x };
				const float y{ normalizedQuaternion.vector.y };
				const float z{ normalizedQuaternion.vector.z };
				const float w{ normalizedQuaternion.scalar };

				return Matrix<4, 4, float>
				{
					{
						1.0f - 2.0f * (y * y) - 2.0f * (z * z), 2.0f * x * y - 2.0f * w * z, 2.0f * x * z + 2.0f * w * y, 0.0f,
						2.0f * x * y + 2.0f * w * z, 1.0f - 2.0f * (x * x) - 2.0f* (z * z), 2.0f * y * z - 2.0f * w * x, 0.0f,
						2.0f * x * z - 2.0f * w * y, 2.0f * y * z + 2.0f * w * x, 1.0f - 2.0f * (x * x) - 2.0f * (y * y), 0.0f,
						0.0f, 0.0f, 0.0f, 1.0f
					}
				} * matrix;
			}
		};

		template<typename ValueType>
		struct MatrixRotateIdentity<4, 4, ValueType> final
		{
			CIN_MATH_INLINE static Matrix<4, 4, float> implementation(const Vector<3, ValueType>& axis, const ValueType rotation) noexcept
			{
				const Vector<3, float> a{ Normalize(axis) };
				const float s{ std::sin(rotation) };
				const float c{ std::cos(rotation) };
				/*
					c + (1 - c)x^2, (1 - c)xy - sz, (1 - c)xz + sy,
					(1 - c)xy + sz, c + (1 - c)y^2, (1 - c)yz - sx,
					(1 - c)xz - sy, (1 - c)yz + sx, c + (1 - c)z^2
				*/
				return Matrix<4, 4, float>
				{
					{
						c + (1.0f - c) * (a.x * a.x), (1.0f - c)* a.x* a.y - s * a.z, (1.0f - c)* a.x* a.z + s * a.y, 0.0f,
						(1.0f - c)* a.x* a.y + s * a.z, c + (1.0f - c) * (a.y * a.y), (1.0f - c)* a.y* a.z - s * a.x, 0.0f,
						(1.0f - c)* a.x* a.z - s * a.y, (1.0f - c)* a.y* a.z + s * a.x, c + (1.0f - c) * (a.z * a.z), 0.0f,
						0.0f, 0.0f, 0.0f, 1.0f
					}
				};
			}
		};

		template<Length_t rows, Length_t columns, typename ValueType>
		struct MatrixRotateX final
		{
			CIN_MATH_INLINE static Matrix<4, 4, float> implementation(const Matrix<4, 4, ValueType>& matrix, const ValueType rotation) noexcept
			{
				const float s{ std::sin(rotation) };
				const float c{ std::cos(rotation) };

				return Matrix<4, 4, float>
				{
					{
						1.0f, 0.0f, 0.0f, 0.0f,
						0.0f, c, -s, 0.0f,
						0.0f, s, c, 0.0f,
						0.0f, 0.0f, 0.0f, 1.0f
					}
				} * matrix;
			}
		};

		template<Length_t rows, Length_t columns, typename ValueType>
		struct MatrixRotateXIdentity final
		{
			CIN_MATH_INLINE static Matrix<4, 4, float> implementation(const float rotation) noexcept
			{
				const float s{ std::sin(rotation) };
				const float c{ std::cos(rotation) };

				return Matrix<4, 4, float>
				{
					{
						1.0f, 0.0f, 0.0f, 0.0f,
						0.0f, c,	-s,	  0.0f,
						0.0f, s,	 c,	  0.0f,
						0.0f, 0.0f, 0.0f, 1.0f
					}
				};
			}

			CIN_MATH_INLINE static Matrix<4, 4, double> implementation(const double rotation) noexcept
			{
				const double s{ std::sin(rotation) };
				const double c{ std::cos(rotation) };

				return Matrix<4, 4, double>
				{
					{
						1.0f, 0.0f, 0.0f, 0.0f,
						0.0f, c,	-s,	  0.0f,
						0.0f, s,	 c,	  0.0f,
						0.0f, 0.0f, 0.0f, 1.0f
					}
				};
			}
		};

		template<Length_t rows, Length_t columns, typename ValueType>
		struct MatrixRotateY final
		{
			CIN_MATH_INLINE static Matrix<4, 4, float> implementation(const Matrix<4, 4, ValueType>& matrix, const ValueType rotation) noexcept
			{
				const float s{ std::sin(rotation) };
				const float c{ std::cos(rotation) };

				return Matrix<4, 4, float>
				{
					{
						c, 0.0f, s, 0.0f,
						0.0f, 1.0f, 0.0f, 0.0f,
						-s, 0.0f, c, 0.0f,
						0.0f, 0.0f, 0.0f, 1.0f
					}
				} * matrix;
			}
		};

		template<Length_t rows, Length_t columns, typename ValueType>
		struct MatrixRotateYIdentity final
		{
			CIN_MATH_INLINE static Matrix<4, 4, float> implementation(const ValueType rotation) noexcept
			{
				const float s{ std::sin(rotation) };
				const float c{ std::cos(rotation) };

				return Matrix<4, 4, float>
				{
					{
						c, 0.0f, s, 0.0f,
						0.0f, 1.0f, 0.0f, 0.0f,
						-s, 0.0f, c, 0.0f,
						0.0f, 0.0f, 0.0f, 1.0f
					}
				};
			}
		};

		template<Length_t rows, Length_t columns, typename ValueType>
		struct MatrixRotateZ final
		{
			CIN_MATH_INLINE static Matrix<4, 4, float> implementation(const Matrix<4, 4, ValueType>& matrix, const ValueType rotation) noexcept
			{
				const float s{ std::sin(rotation) };
				const float c{ std::cos(rotation) };

				return Matrix<4, 4, float>
				{
					{
						c, -s, 0.0f, 0.0f,
						s, c, 0.0f, 0.0f,
						0.0f, 0.0f, 1.0f, 0.0f,
						0.0f, 0.0f, 0.0f, 1.0f,
					}
				} * matrix;
			}
		};

		template<Length_t rows, Length_t columns, typename ValueType>
		struct MatrixRotateZIdentity final
		{
			CIN_MATH_INLINE static Matrix<4, 4, float> implementation(const ValueType rotation) noexcept
			{
				const float s{ std::sin(rotation) };
				const float c{ std::cos(rotation) };

				return Matrix<4, 4, float>
				{
					{
						c, -s, 0.0f, 0.0f,
						s, c, 0.0f, 0.0f,
						0.0f, 0.0f, 1.0f, 0.0f,
						0.0f, 0.0f, 0.0f, 1.0f,
					}
				};
			}
		};

		template<Length_t rows, Length_t columns, typename ValueType>
		struct MatrixScale final
		{
			CIN_MATH_INLINE static Matrix<4, 4, float> implementation(const Matrix<4, 4, float>& matrix, const Vector<3, float>& scale) noexcept
			{
				Matrix<4, 4, float> result;
#if (CIN_INSTRUCTION_SET) & (CIN_INSTRUCTION_SET_AVX)
				result.raw[0] = matrix.raw[0] * scale.x;
				result.raw[1] = matrix.raw[1] * scale.x;
				result.raw[2] = matrix.raw[2] * scale.x;
				result.raw[3] = matrix.raw[3] * scale.x;

				result.raw[4] = matrix.raw[4] * scale.y;
				result.raw[5] = matrix.raw[5] * scale.y;
				result.raw[6] = matrix.raw[6] * scale.y;
				result.raw[7] = matrix.raw[7] * scale.y;

				result.raw[8] = matrix.raw[8] * scale.z;
				result.raw[9] = matrix.raw[9] * scale.z;
				result.raw[10] = matrix.raw[10] * scale.z;
				result.raw[11] = matrix.raw[11] * scale.z;

				result.raw[12] = matrix.raw[12];
				result.raw[13] = matrix.raw[13];
				result.raw[14] = matrix.raw[14];
				result.raw[15] = matrix.raw[15];
#elif (CIN_INSTRUCTION_SET) & (CIN_INSTRUCTION_SET_SSE)
				result.data[0] = _mm_mul_ps(matrix.data[0], _mm_set_ps(scale.x, scale.x, scale.x, scale.x));
				result.data[1] = _mm_mul_ps(matrix.data[1], _mm_set_ps(scale.y, scale.y, scale.y, scale.y));
				result.data[2] = _mm_mul_ps(matrix.data[2], _mm_set_ps(scale.z, scale.z, scale.z, scale.z));
				result.data[3] = matrix.data[3];
#else
				result.raw[0] = matrix.raw[0] * scale.x;
				result.raw[1] = matrix.raw[1] * scale.x;
				result.raw[2] = matrix.raw[2] * scale.x;
				result.raw[3] = matrix.raw[3] * scale.x;

				result.raw[4] = matrix.raw[4] * scale.y;
				result.raw[5] = matrix.raw[5] * scale.y;
				result.raw[6] = matrix.raw[6] * scale.y;
				result.raw[7] = matrix.raw[7] * scale.y;

				result.raw[8] = matrix.raw[8] * scale.z;
				result.raw[9] = matrix.raw[9] * scale.z;
				result.raw[10] = matrix.raw[10] * scale.z;
				result.raw[11] = matrix.raw[11] * scale.z;

				result.raw[12] = matrix.raw[12];
				result.raw[13] = matrix.raw[13];
				result.raw[14] = matrix.raw[14];
				result.raw[15] = matrix.raw[15];
#endif
				return result;
			}
		};

		template<typename ValueType>
		struct MatrixTranspose<2, 2, ValueType> final
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

			CIN_MATH_INLINE static Matrix<2, 2, double> implementation(const Matrix<2, 2, double>& matrix) noexcept
			{
				Matrix<2, 2, double> result;

				result.raw[0] = matrix.raw[0];
				result.raw[1] = matrix.raw[2];
				result.raw[2] = matrix.raw[1];
				result.raw[3] = matrix.raw[3];

				return result;
			}
		};

		template<typename ValueType>
		struct MatrixTranspose<3, 3, ValueType> final
		{
			CIN_MATH_INLINE static Matrix<3, 3, float> implementation(const Matrix<3, 3, float>& matrix) noexcept
			{
				Matrix<3, 3, float> result;

				result.raw[0] = matrix[0];
				result.raw[1] = matrix[3];
				result.raw[2] = matrix[6];

				result.raw[3] = matrix[1];
				result.raw[4] = matrix[4];
				result.raw[5] = matrix[7];

				result.raw[6] = matrix[2];
				result.raw[7] = matrix[5];
				result.raw[8] = matrix[8];

				return result;
			}

			CIN_MATH_INLINE static Matrix<3, 3, double> implementation(const Matrix<3, 3, double>& matrix) noexcept
			{
				Matrix<3, 3, double> result;

				result.raw[0] = matrix[0];
				result.raw[1] = matrix[3];
				result.raw[2] = matrix[6];

				result.raw[3] = matrix[1];
				result.raw[4] = matrix[4];
				result.raw[5] = matrix[7];

				result.raw[6] = matrix[2];
				result.raw[7] = matrix[5];
				result.raw[8] = matrix[8];

				return result;
			}
		};

		template<typename ValueType>
		struct MatrixTranspose<4, 4, ValueType> final
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

			CIN_MATH_INLINE static Matrix<4, 4, double> implementation(const Matrix<4, 4, double>& matrix) noexcept
			{
				Matrix<4, 4, double> result;

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

				return result;
			}
		};

		template<typename ValueType>
		struct MatrixDeterminant<2, 2, ValueType> final
		{
			CIN_MATH_INLINE static float implementation(const Matrix<2, 2, float>& matrix) noexcept
			{
				return  matrix[0] * matrix[3] - matrix[2] * matrix[1];
			}

			CIN_MATH_INLINE static double implementation(const Matrix<2, 2, double>& matrix) noexcept
			{
				return  matrix[0] * matrix[3] - matrix[2] * matrix[1];
			}
		};

		template<typename ValueType>
		struct MatrixDeterminant<3, 3, ValueType> final
		{
			CIN_MATH_INLINE static float implementation(const Matrix<3, 3, float>& matrix) noexcept
			{
				return
					+ matrix.raw[0] * (matrix.raw[4] * matrix.raw[8] - matrix.raw[7] * matrix.raw[5])
					- matrix.raw[3] * (matrix.raw[1] * matrix.raw[8] - matrix.raw[7] * matrix.raw[2])
					+ matrix.raw[6] * (matrix.raw[1] * matrix.raw[5] - matrix.raw[4] * matrix.raw[2]);
			}

			CIN_MATH_INLINE static double implementation(const Matrix<3, 3, double>& matrix) noexcept
			{
				return
					+ matrix.raw[0] * (matrix.raw[4] * matrix.raw[8] - matrix.raw[7] * matrix.raw[5])
					- matrix.raw[3] * (matrix.raw[1] * matrix.raw[8] - matrix.raw[7] * matrix.raw[2])
					+ matrix.raw[6] * (matrix.raw[1] * matrix.raw[5] - matrix.raw[4] * matrix.raw[2]);
			}
		};

		template<typename ValueType>
		struct MatrixDeterminant<4, 4, ValueType> final
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

			CIN_MATH_INLINE static double implementation(const Matrix<4, 4, double>& matrix) noexcept
			{
				const double e00{ matrix[10] * matrix[15] - matrix[14] * matrix[11] };
				const double e01{ matrix[9] * matrix[15] - matrix[13] * matrix[11] };
				const double e02{ matrix[9] * matrix[14] - matrix[13] * matrix[10] };

				const double e03{ matrix[8] * matrix[15] - matrix[12] * matrix[11] };
				const double e04{ matrix[8] * matrix[14] - matrix[12] * matrix[10] };
				const double e05{ matrix[8] * matrix[13] - matrix[12] * matrix[9] };

				const double m00{ matrix[5] * e00 - matrix[6] * e01 + matrix[7] * e02 };
				const double m01{ matrix[4] * e00 - matrix[6] * e03 + matrix[7] * e04 };

				const double m02{ matrix[4] * e01 - matrix[5] * e03 + matrix[7] * e05 };
				const double m03{ matrix[4] * e02 - matrix[5] * e04 + matrix[6] * e05 };

				return matrix[0] * m00 - matrix[1] * m01 + matrix[2] * m02 - matrix[3] * m03;
			}
		};

		template<typename ValueType>
		struct MatrixInverse<2, 2, ValueType> final
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

			CIN_MATH_INLINE static Matrix<2, 2, double> implementation(const Matrix<2, 2, double>& matrix) noexcept
			{
				Matrix<2, 2, double> result;
				const double oneOverDeterminant{ 1.0f / (matrix[0] * matrix[3] - matrix[2] * matrix[1]) };

				result.raw[0] = matrix[3] * (+oneOverDeterminant);
				result.raw[1] = matrix[1] * (-oneOverDeterminant);
				result.raw[2] = matrix[2] * (-oneOverDeterminant);
				result.raw[3] = matrix[0] * (+oneOverDeterminant);

				return result;
			}
		};

		template<typename ValueType>
		struct MatrixInverse<3, 3, ValueType> final
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

			CIN_MATH_INLINE static Matrix<3, 3, double> implementation(const Matrix<3, 3, double>& matrix) noexcept
			{
				Matrix<3, 3, double> result;
				const double oneOverDeterminant{ 1.0f / MatrixDeterminant<3, 3, double>::implementation(matrix) };

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
		struct MatrixInverse<4, 4, ValueType> final
		{
			CIN_MATH_INLINE static Matrix<4, 4, float> implementation(const Matrix<4, 4, float>& matrix) noexcept
			{
				/*					   | D11 D12 D13 D14 |
				*			   1	   | D21 D22 D23 D24 |
				* inv(A) = -------- *  | D31 D32 D33 D34 |
				*			det(A)	   | D41 D42 D43 D44 |
				* 
				* Dij = (-1)^i+j * det(Aij)
				*/
				
				/* Verify the inverse exists */
				assert(Determinant(matrix) != 0.0f);
				Matrix<4, 4, float> result;
				const float oneOverDeterminant{ 1.0f / MatrixDeterminant<4, 4, float>::implementation(matrix) };
				
				const float D11
				{
					+ matrix.raw[5] * (matrix.raw[10] * matrix.raw[15] - matrix.raw[14] * matrix.raw[11])
					- matrix.raw[9] * (matrix.raw[6] * matrix.raw[15] - matrix.raw[14] * matrix.raw[7])
					+ matrix.raw[13] * (matrix.raw[6] * matrix.raw[11] - matrix.raw[10] * matrix.raw[7])
				};

				const float D12
				{ -(
					+ matrix.raw[4] * (matrix.raw[10] * matrix.raw[15] - matrix.raw[14] * matrix.raw[11])
					- matrix.raw[8] * (matrix.raw[6] * matrix.raw[15] - matrix.raw[14] * matrix.raw[7])
					+ matrix.raw[12] * (matrix.raw[6] * matrix.raw[11] - matrix.raw[10] * matrix.raw[7])
				) };

				const float D13
				{
					+ matrix.raw[4] * (matrix.raw[9] * matrix.raw[15] - matrix.raw[13] * matrix.raw[11])
					- matrix.raw[8] * (matrix.raw[5] * matrix.raw[15] - matrix.raw[13] * matrix.raw[7])
					+ matrix.raw[12] * (matrix.raw[5] * matrix.raw[11] - matrix.raw[9] * matrix.raw[7])
				};

				const float D14
				{ -(
					+ matrix.raw[4] * (matrix.raw[9] * matrix.raw[14] - matrix.raw[13] * matrix.raw[10])
					- matrix.raw[8] * (matrix.raw[5] * matrix.raw[14] - matrix.raw[13] * matrix.raw[6])
					+ matrix.raw[12] * (matrix.raw[5] * matrix.raw[10] - matrix.raw[9] * matrix.raw[6])
				) };

				const float D21
				{ -(
					+ matrix.raw[1] * (matrix.raw[10] * matrix.raw[15] - matrix.raw[14] * matrix.raw[11])
					- matrix.raw[9] * (matrix.raw[2] * matrix.raw[15] - matrix.raw[14] * matrix.raw[3])
					+ matrix.raw[13] * (matrix.raw[2] * matrix.raw[11] - matrix.raw[10] * matrix.raw[3])
				) };

				const float D22
				{
					+ matrix.raw[0] * (matrix.raw[10] * matrix.raw[15] - matrix.raw[14] * matrix.raw[11])
					- matrix.raw[8] * (matrix.raw[2] * matrix.raw[15] - matrix.raw[14] * matrix.raw[3])
					+ matrix.raw[12] * (matrix.raw[2] * matrix.raw[11] - matrix.raw[10] * matrix.raw[3])
				};

				const float D23
				{ -(
					+ matrix.raw[0] * (matrix.raw[9] * matrix.raw[15] - matrix.raw[13] * matrix.raw[11])
					- matrix.raw[8] * (matrix.raw[1] * matrix.raw[15] - matrix.raw[13] * matrix.raw[3])
					+ matrix.raw[12] * (matrix.raw[1] * matrix.raw[11] - matrix.raw[9] * matrix.raw[3])
				) };

				const float D24
				{
					+ matrix.raw[0] * (matrix.raw[9] * matrix.raw[14] - matrix.raw[13] * matrix.raw[10])
					- matrix.raw[8] * (matrix.raw[1] * matrix.raw[14] - matrix.raw[13] * matrix.raw[2])
					+ matrix.raw[12] * (matrix.raw[1] * matrix.raw[10] - matrix.raw[9] * matrix.raw[2])
				};

				const float D31
				{
						+matrix.raw[1] * (matrix.raw[6] * matrix.raw[15] - matrix.raw[14] * matrix.raw[7])
						- matrix.raw[5] * (matrix.raw[2] * matrix.raw[15] - matrix.raw[14] * matrix.raw[3])
						+ matrix.raw[13] * (matrix.raw[2] * matrix.raw[7] - matrix.raw[6] * matrix.raw[3])
				};

				const float D32
				{ -(
					+ matrix.raw[0] * (matrix.raw[6] * matrix.raw[15] - matrix.raw[14] * matrix.raw[7])
					- matrix.raw[4] * (matrix.raw[2] * matrix.raw[15] - matrix.raw[14] * matrix.raw[3])
					+ matrix.raw[12] * (matrix.raw[2] * matrix.raw[7] - matrix.raw[6] * matrix.raw[3])
				) };

				const float D33
				{
					+ matrix.raw[0] * (matrix.raw[5] * matrix.raw[15] - matrix.raw[13] * matrix.raw[7])
					- matrix.raw[4] * (matrix.raw[1] * matrix.raw[15] - matrix.raw[13] * matrix.raw[3])
					+ matrix.raw[12] * (matrix.raw[1] * matrix.raw[7] - matrix.raw[5] * matrix.raw[3])
				};

				const float D34
				{ -(
					+ matrix.raw[0] * (matrix.raw[5] * matrix.raw[14] - matrix.raw[13] * matrix.raw[6])
					- matrix.raw[4] * (matrix.raw[1] * matrix.raw[14] - matrix.raw[13] * matrix.raw[2])
					+ matrix.raw[12] * (matrix.raw[1] * matrix.raw[6] - matrix.raw[5] * matrix.raw[2])
				) };

				const float D41
				{ -(
					+ matrix.raw[1] * (matrix.raw[6] * matrix.raw[11] - matrix.raw[10] * matrix.raw[7])
					- matrix.raw[5] * (matrix.raw[2] * matrix.raw[11] - matrix.raw[10] * matrix.raw[3])
					+ matrix.raw[9] * (matrix.raw[2] * matrix.raw[7] - matrix.raw[6] * matrix.raw[3])
				) };

				const float D42
				{
					+ matrix.raw[0] * (matrix.raw[6] * matrix.raw[11] - matrix.raw[10] * matrix.raw[7])
					- matrix.raw[4] * (matrix.raw[2] * matrix.raw[11] - matrix.raw[10] * matrix.raw[3])
					+ matrix.raw[8] * (matrix.raw[2] * matrix.raw[7] - matrix.raw[6] * matrix.raw[3])
				};

				const float D43
				{ -(
					+ matrix.raw[0] * (matrix.raw[5] * matrix.raw[11] - matrix.raw[9] * matrix.raw[7])
					- matrix.raw[4] * (matrix.raw[1] * matrix.raw[11] - matrix.raw[9] * matrix.raw[3])
					+ matrix.raw[8] * (matrix.raw[1] * matrix.raw[7] - matrix.raw[5] * matrix.raw[3])
				) };

				const float D44
				{
					+ matrix.raw[0] * (matrix.raw[5] * matrix.raw[10] - matrix.raw[9] * matrix.raw[6])
					- matrix.raw[4] * (matrix.raw[1] * matrix.raw[10] - matrix.raw[9] * matrix.raw[2])
					+ matrix.raw[8] * (matrix.raw[1] * matrix.raw[6] - matrix.raw[5] * matrix.raw[2])
				};

				/* Construct already transposed */
				//const Matrix<4, 4, float> A			const Matrix<4, 4, float> A_transposed
				//{										{
				//	D11, D12, D13, D14,						D11, D21, D31, D41,
				//	D21, D22, D23, D24,		  ==> 			D12, D22, D32, D42,		
				//	D31, D32, D33, D34,						D13, D23, D33, D43,
				//	D41, D42, D43, D44						D14, D24, D34, D44
				//};									};

				const Matrix<4, 4, float> A_transposed
				{
					D11, D21, D31, D41,
					D12, D22, D32, D42,
					D13, D23, D33, D43,
					D14, D24, D34, D44
				};

				return A_transposed * oneOverDeterminant;
			}

			CIN_MATH_INLINE static Matrix<4, 4, double> implementation(const Matrix<4, 4, double>& matrix) noexcept
			{
				/*					   | D11 D12 D13 D14 |
				*			   1	   | D21 D22 D23 D24 |
				* inv(A) = -------- *  | D31 D32 D33 D34 |
				*			det(A)	   | D41 D42 D43 D44 |
				*
				* Dij = (-1)^i+j * det(Aij)
				*/

				/* Verify the inverse exists */
				assert(Determinant(matrix) != 0.0f);
				Matrix<4, 4, double> result;
				const double oneOverDeterminant{ 1.0f / MatrixDeterminant<4, 4, double>::implementation(matrix) };

				const double D11
				{
					+matrix.raw[5] * (matrix.raw[10] * matrix.raw[15] - matrix.raw[14] * matrix.raw[11])
					- matrix.raw[9] * (matrix.raw[6] * matrix.raw[15] - matrix.raw[14] * matrix.raw[7])
					+ matrix.raw[13] * (matrix.raw[6] * matrix.raw[11] - matrix.raw[10] * matrix.raw[7])
				};

				const double D12
				{ -(
					+matrix.raw[4] * (matrix.raw[10] * matrix.raw[15] - matrix.raw[14] * matrix.raw[11])
					- matrix.raw[8] * (matrix.raw[6] * matrix.raw[15] - matrix.raw[14] * matrix.raw[7])
					+ matrix.raw[12] * (matrix.raw[6] * matrix.raw[11] - matrix.raw[10] * matrix.raw[7])
				) };

				const double D13
				{
					+matrix.raw[4] * (matrix.raw[9] * matrix.raw[15] - matrix.raw[13] * matrix.raw[11])
					- matrix.raw[8] * (matrix.raw[5] * matrix.raw[15] - matrix.raw[13] * matrix.raw[7])
					+ matrix.raw[12] * (matrix.raw[5] * matrix.raw[11] - matrix.raw[9] * matrix.raw[7])
				};

				const double D14
				{ -(
					+matrix.raw[4] * (matrix.raw[9] * matrix.raw[14] - matrix.raw[13] * matrix.raw[10])
					- matrix.raw[8] * (matrix.raw[5] * matrix.raw[14] - matrix.raw[13] * matrix.raw[6])
					+ matrix.raw[12] * (matrix.raw[5] * matrix.raw[10] - matrix.raw[9] * matrix.raw[6])
				) };

				const double D21
				{ -(
					+matrix.raw[1] * (matrix.raw[10] * matrix.raw[15] - matrix.raw[14] * matrix.raw[11])
					- matrix.raw[9] * (matrix.raw[2] * matrix.raw[15] - matrix.raw[14] * matrix.raw[3])
					+ matrix.raw[13] * (matrix.raw[2] * matrix.raw[11] - matrix.raw[10] * matrix.raw[3])
				) };

				const double D22
				{
					+matrix.raw[0] * (matrix.raw[10] * matrix.raw[15] - matrix.raw[14] * matrix.raw[11])
					- matrix.raw[8] * (matrix.raw[2] * matrix.raw[15] - matrix.raw[14] * matrix.raw[3])
					+ matrix.raw[12] * (matrix.raw[2] * matrix.raw[11] - matrix.raw[10] * matrix.raw[3])
				};

				const double D23
				{ -(
					+matrix.raw[0] * (matrix.raw[9] * matrix.raw[15] - matrix.raw[13] * matrix.raw[11])
					- matrix.raw[8] * (matrix.raw[1] * matrix.raw[15] - matrix.raw[13] * matrix.raw[3])
					+ matrix.raw[12] * (matrix.raw[1] * matrix.raw[11] - matrix.raw[9] * matrix.raw[3])
				) };

				const double D24
				{
					+matrix.raw[0] * (matrix.raw[9] * matrix.raw[14] - matrix.raw[13] * matrix.raw[10])
					- matrix.raw[8] * (matrix.raw[1] * matrix.raw[14] - matrix.raw[13] * matrix.raw[2])
					+ matrix.raw[12] * (matrix.raw[1] * matrix.raw[10] - matrix.raw[9] * matrix.raw[2])
				};

				const double D31
				{
						+matrix.raw[1] * (matrix.raw[6] * matrix.raw[15] - matrix.raw[14] * matrix.raw[7])
						- matrix.raw[5] * (matrix.raw[2] * matrix.raw[15] - matrix.raw[14] * matrix.raw[3])
						+ matrix.raw[13] * (matrix.raw[2] * matrix.raw[7] - matrix.raw[6] * matrix.raw[3])
				};

				const double D32
				{ -(
					+matrix.raw[0] * (matrix.raw[6] * matrix.raw[15] - matrix.raw[14] * matrix.raw[7])
					- matrix.raw[4] * (matrix.raw[2] * matrix.raw[15] - matrix.raw[14] * matrix.raw[3])
					+ matrix.raw[12] * (matrix.raw[2] * matrix.raw[7] - matrix.raw[6] * matrix.raw[3])
				) };

				const double D33
				{
					+matrix.raw[0] * (matrix.raw[5] * matrix.raw[15] - matrix.raw[13] * matrix.raw[7])
					- matrix.raw[4] * (matrix.raw[1] * matrix.raw[15] - matrix.raw[13] * matrix.raw[3])
					+ matrix.raw[12] * (matrix.raw[1] * matrix.raw[7] - matrix.raw[5] * matrix.raw[3])
				};

				const double D34
				{ -(
					+matrix.raw[0] * (matrix.raw[5] * matrix.raw[14] - matrix.raw[13] * matrix.raw[6])
					- matrix.raw[4] * (matrix.raw[1] * matrix.raw[14] - matrix.raw[13] * matrix.raw[2])
					+ matrix.raw[12] * (matrix.raw[1] * matrix.raw[6] - matrix.raw[5] * matrix.raw[2])
				) };

				const double D41
				{ -(
					+matrix.raw[1] * (matrix.raw[6] * matrix.raw[11] - matrix.raw[10] * matrix.raw[7])
					- matrix.raw[5] * (matrix.raw[2] * matrix.raw[11] - matrix.raw[10] * matrix.raw[3])
					+ matrix.raw[9] * (matrix.raw[2] * matrix.raw[7] - matrix.raw[6] * matrix.raw[3])
				) };

				const double D42
				{
					+matrix.raw[0] * (matrix.raw[6] * matrix.raw[11] - matrix.raw[10] * matrix.raw[7])
					- matrix.raw[4] * (matrix.raw[2] * matrix.raw[11] - matrix.raw[10] * matrix.raw[3])
					+ matrix.raw[8] * (matrix.raw[2] * matrix.raw[7] - matrix.raw[6] * matrix.raw[3])
				};

				const double D43
				{ -(
					+matrix.raw[0] * (matrix.raw[5] * matrix.raw[11] - matrix.raw[9] * matrix.raw[7])
					- matrix.raw[4] * (matrix.raw[1] * matrix.raw[11] - matrix.raw[9] * matrix.raw[3])
					+ matrix.raw[8] * (matrix.raw[1] * matrix.raw[7] - matrix.raw[5] * matrix.raw[3])
				) };

				const double D44
				{
					+matrix.raw[0] * (matrix.raw[5] * matrix.raw[10] - matrix.raw[9] * matrix.raw[6])
					- matrix.raw[4] * (matrix.raw[1] * matrix.raw[10] - matrix.raw[9] * matrix.raw[2])
					+ matrix.raw[8] * (matrix.raw[1] * matrix.raw[6] - matrix.raw[5] * matrix.raw[2])
				};

				/* Construct already transposed */
				//const Matrix<4, 4, double> A			const Matrix<4, 4, double> A_transposed
				//{										{
				//	D11, D12, D13, D14,						D11, D21, D31, D41,
				//	D21, D22, D23, D24,		  ==> 			D12, D22, D32, D42,		
				//	D31, D32, D33, D34,						D13, D23, D33, D43,
				//	D41, D42, D43, D44						D14, D24, D34, D44
				//};									};

				const Matrix<4, 4, double> A_transposed
				{
					D11, D21, D31, D41,
					D12, D22, D32, D42,
					D13, D23, D33, D43,
					D14, D24, D34, D44
				};

				return A_transposed * oneOverDeterminant;
			}
		};

		template<typename ValueType>
		struct QuaternionConugate final
		{
			CIN_MATH_INLINE static TQuaternion<ValueType> implementation(const TQuaternion<ValueType>& quaternion) noexcept
			{
				TQuaternion<ValueType> result;

				result.raw[0] = +quaternion.raw[0];
				result.raw[1] = -quaternion.raw[1];
				result.raw[2] = -quaternion.raw[2];
				result.raw[3] = -quaternion.raw[3];

				return result;
			}
		};

		template<typename ValueType>
		struct QuaternionNorm final
		{
			CIN_MATH_INLINE static ValueType implementation(const TQuaternion<ValueType>& quaternion) noexcept
			{
				return std::sqrt(
					+ quaternion.raw[0] * quaternion.raw[0]
					+ quaternion.raw[1] * quaternion.raw[1]
					+ quaternion.raw[2] * quaternion.raw[2]
					+ quaternion.raw[3] * quaternion.raw[3]);
			}
		};

		template<typename ValueType>
		struct QuaternionNormSquared final
		{
			CIN_MATH_INLINE static ValueType implementation(const TQuaternion<ValueType>& quaternion) noexcept
			{
				return
					+ quaternion.raw[0] * quaternion.raw[0]
					+ quaternion.raw[1] * quaternion.raw[1]
					+ quaternion.raw[2] * quaternion.raw[2]
					+ quaternion.raw[3] * quaternion.raw[3];
			}
		};

		template<typename ValueType>
		struct QuaternionNormalize final
		{
			CIN_MATH_INLINE static TQuaternion<ValueType> implementation(const TQuaternion<ValueType>& quaternion) noexcept
			{
				TQuaternion<ValueType> result;
				const ValueType norm{ Norm(quaternion) };

				result.raw[0] = quaternion.raw[0] / norm;
				result.raw[1] = quaternion.raw[1] / norm;
				result.raw[2] = quaternion.raw[2] / norm;
				result.raw[3] = quaternion.raw[3] / norm;

				return result;
			}
		};

		template<typename ValueType>
		struct QuaternionInverse final
		{
			CIN_MATH_INLINE static TQuaternion<ValueType> implementation(const TQuaternion<ValueType>& quaternion) noexcept
			{
				return Conjugate(quaternion) / NormSquared(quaternion);
			}
		};

		template<typename ValueType>
		struct QuaternionRotate final
		{
			CIN_MATH_INLINE static TQuaternion<float> implementation(const Vector<3, float>& vector, const TQuaternion<float>& rotation) noexcept
			{
				assert(false);
				return TQuaternion<float>{};
			}
		};

		template<typename ValueType>
		struct QuaternionAxisAngleToQuaternion final
		{
			CIN_MATH_INLINE static TQuaternion<float> implementation(const Angle angle, const Vector<3, float>& axisAngle) noexcept
			{
				const float halfRadianAngle{ angle.ToRadians() * 0.5f };

				TQuaternion<float> result;
				result.scalar = std::cos(halfRadianAngle);
				result.vector = Normalize(axisAngle) * std::sin(halfRadianAngle);

				return result;
			}

			CIN_MATH_INLINE static TQuaternion<float> implementation(const Vector<4, float>& axisAngle) noexcept
			{
				const float halfTheta{ axisAngle.x * 0.5f };

				TQuaternion<float> result;
				result.scalar = std::cos(halfTheta);
				result.vector = (Normalize<3, float>(axisAngle.yzw) * std::sin(halfTheta));

				return result;
			}
		};

		template<typename ValueType>
		struct QuaternionQuaternionToAxisAngle final
		{
			CIN_MATH_INLINE static Vector<4, float> implementation(const TQuaternion<float>& quaternion) noexcept
			{
				const float theta{ 2.0f * std::acos(quaternion.scalar) };
				const float halfSinTheta{ std::sin(theta) * 0.5f };

				Vector<4, float> result;
				result.x = theta;
				result.yzw = quaternion.vector.xyz / halfSinTheta;

				return result;
			}
		};

		template<typename ValueType>
		struct QuaternionUnitForm final
		{
			CIN_MATH_INLINE static TQuaternion<float> implementation(const TQuaternion<float>& quaternion) noexcept
			{
				const float halfAngle{ quaternion.scalar * 0.5f };
				const Vector<3, float> normalizedAxis{ Normalize(quaternion.vector) };
				
				TQuaternion<float> result;
				result.scalar = std::cos(halfAngle);
				result.vector = normalizedAxis * std::sin(halfAngle);

				return result;
			}
		};

		template<typename ValueType>
		struct OrthographicProjection final
		{
			CIN_MATH_INLINE static Matrix<4, 4, float> implementation(const ValueType orthoLeft, const ValueType orthoRight, const ValueType orthoBottom, const ValueType orthoTop) noexcept
			{
				return Matrix<4, 4, float>
				{
					2.0f / (orthoRight - orthoLeft), 0.0f, 0.0f, 0.0f,
					0.0f, 2.0f / (orthoTop - orthoBottom), 0.0f, 0.0f,
					0.0f, 0.0f, -1.0f, 0.0f,
					-(orthoRight + orthoLeft) / (orthoRight - orthoLeft), -(orthoTop + orthoBottom) / (orthoTop - orthoBottom), 0.0f, 1.0f
				};
			}
		};

		template<typename ValueType>
		struct PerspectiveProjection final
		{
			CIN_MATH_INLINE static Matrix<4, 4, float> implementation(const ValueType FOV, const ValueType aspectRatio, const ValueType nearClip, const ValueType farClip) noexcept
			{
				Matrix<4, 4, float> result;

				const float tangentHalfFOV{ std::tan(FOV * 0.5f) };
				const float nearClipMinusFarClip{ nearClip - farClip };

				result[0] = 1.0f / (tangentHalfFOV * aspectRatio);
				result[5] = 1.0f / (tangentHalfFOV);
				result[10] = (farClip + nearClip) / nearClipMinusFarClip;
				result[11] = -1.0f;
				result[14] = 2.0f * farClip * nearClip / nearClipMinusFarClip;

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
	CIN_MATH_INLINE Vector<length, ValueType> Normalize(const Vector<length, ValueType>& vector) noexcept
	{
		return Implementation::VectorNormalize<length, ValueType>::implementation(vector);
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
	CIN_MATH_INLINE TQuaternion<ValueType> Conjugate(const TQuaternion<ValueType>& quaternion) noexcept
	{
		return Implementation::QuaternionConugate<ValueType>::implementation(quaternion);
	}

	template<typename ValueType>
	CIN_MATH_INLINE ValueType Norm(const TQuaternion<ValueType>& quaternion) noexcept
	{
		return Implementation::QuaternionNorm<ValueType>::implementation(quaternion);
	}

	template<typename ValueType>
	CIN_MATH_INLINE ValueType NormSquared(const TQuaternion<ValueType>& quaternion) noexcept
	{
		return Implementation::QuaternionNormSquared<ValueType>::implementation(quaternion);
	}

	template<typename ValueType>
	CIN_MATH_INLINE TQuaternion<ValueType> Normalize(const TQuaternion<ValueType>& quaternion) noexcept
	{
		return Implementation::QuaternionNormalize<ValueType>::implementation(quaternion);
	}

	template<typename ValueType>
	CIN_MATH_INLINE TQuaternion<ValueType> Inverse(const TQuaternion<ValueType>& quaternion) noexcept
	{
		return Implementation::QuaternionInverse<ValueType>::implementation(quaternion);
	}

	template<typename ValueType>
	CIN_MATH_INLINE Vector<3, ValueType> Rotate(const Vector<3, ValueType>& vector, const TQuaternion<ValueType>& rotation) noexcept
	{
		return Implementation::QuaternionRotate<ValueType>::implementation(vector, rotation);
	}

	template<typename ValueType>
	CIN_MATH_INLINE TQuaternion<ValueType> AxisAngleToQuaternion(const Angle angle, const Vector<3, ValueType>& vector) noexcept
	{
		return Implementation::QuaternionAxisAngleToQuaternion<ValueType>::implementation(angle, vector);
	}

	template<typename ValueType>
	CIN_MATH_INLINE TQuaternion<ValueType> AxisAngleToQuaternion(const Vector<4, ValueType>& vector) noexcept
	{
		return Implementation::QuaternionAxisAngleToQuaternion<ValueType>::implementation(vector);
	}

	template<typename ValueType>
	CIN_MATH_INLINE Vector<4, ValueType> QuaternionToAxisAngle(const TQuaternion<ValueType>& quaternion) noexcept
	{
		return Implementation::QuaternionQuaternionToAxisAngle<ValueType>::implementation(quaternion);
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

	template<Length_t rows, Length_t columns, typename ValueType>
	CIN_MATH_INLINE Matrix<rows, columns, ValueType> Rotate(const Matrix<rows, columns, ValueType>& matrix, const Vector<3, ValueType>& axis, const ValueType rotation) noexcept
	{
		return Implementation::MatrixRotate<rows, columns, ValueType>::implementation(matrix, axis, rotation);
	}

	template<Length_t rows, Length_t columns, typename ValueType>
	CIN_MATH_INLINE Matrix<rows, columns, ValueType> Rotate(const Matrix<rows, columns, ValueType>& matrix, const TQuaternion<ValueType>& quaternion) noexcept
	{
		return Implementation::MatrixRotate<rows, columns, ValueType>::implementation(matrix, quaternion);
	}

	template<Length_t rows, Length_t columns, typename ValueType>
	CIN_MATH_INLINE Matrix<rows, columns, ValueType> RotateIdentity(const Vector<3, ValueType>& axis, const TAngle<ValueType> rotation) noexcept
	{
		return Implementation::MatrixRotateIdentity<rows, columns, ValueType>::implementation(axis, rotation.ToRadians());
	}

	template<Length_t rows, Length_t columns, typename ValueType>
	CIN_MATH_INLINE Matrix<rows, columns, ValueType> RotateX(const Matrix<rows, columns, ValueType>& matrix, const TAngle<ValueType> rotation) noexcept
	{
		return Implementation::MatrixRotateX<rows, columns, ValueType>::implementation(matrix, rotation.ToRadians());
	}

	template<Length_t rows, Length_t columns, typename ValueType>
	CIN_MATH_INLINE Matrix<rows, columns, ValueType> RotateXIdentity(const TAngle<ValueType> rotation) noexcept
	{
		return Implementation::MatrixRotateXIdentity<rows, columns, ValueType>::implementation(rotation.ToRadians());
	}

	template<Length_t rows, Length_t columns, typename ValueType>
	CIN_MATH_INLINE Matrix<rows, columns, ValueType> RotateY(const Matrix<rows, columns, ValueType>& matrix, const TAngle<ValueType> rotation) noexcept
	{
		return Implementation::MatrixRotateY<rows, columns, ValueType>::implementation(matrix, rotation.ToRadians());
	}

	template<Length_t rows, Length_t columns, typename ValueType>
	CIN_MATH_INLINE Matrix<rows, columns, ValueType> RotateYIdentity(const TAngle<ValueType> rotation) noexcept
	{
		return Implementation::MatrixRotateYIdentity<rows, columns, ValueType>::implementation(rotation.ToRadians());
	}

	template<Length_t rows, Length_t columns, typename ValueType>
	CIN_MATH_INLINE Matrix<rows, columns, ValueType> RotateZ(const Matrix<rows, columns, ValueType>& matrix, const TAngle<ValueType> rotation) noexcept
	{
		return Implementation::MatrixRotateZ<rows, columns, ValueType>::implementation(rotation.ToRadians());
	}

	template<Length_t rows, Length_t columns, typename ValueType>
	CIN_MATH_INLINE Matrix<rows, columns, ValueType> RotateZIdentity(const TAngle<ValueType> rotation) noexcept
	{
		return Implementation::MatrixRotateZIdentity<rows, columns, ValueType>::implementation(rotation.ToRadians());
	}

	template<Length_t rows, Length_t columns, typename ValueType>
	CIN_MATH_INLINE Matrix<rows, columns, ValueType> Scale(const Matrix<rows, columns, ValueType>& matrix, const Vector<3, ValueType>& scale) noexcept
	{
		return Implementation::MatrixScale<rows, columns, ValueType>::implementation(matrix, scale);
	}

	template<typename ValueType>
	CIN_MATH_INLINE Matrix<4, 4, ValueType> OrthographicProjection(const ValueType orthoLeft, const ValueType orthoRight, const ValueType orthoBottom, const ValueType orthoTop) noexcept
	{
		return Implementation::OrthographicProjection<ValueType>::implementation(orthoLeft, orthoRight, orthoBottom, orthoTop);
	}

	template<typename ValueType>
	CIN_MATH_INLINE Matrix<4, 4, ValueType> PerspectiveProjection(const ValueType FOV, const ValueType aspectRatio, const ValueType nearClip, const ValueType farClip) noexcept
	{
		return Implementation::PerspectiveProjection<ValueType>::implementation(FOV, aspectRatio, nearClip, farClip);
	}
}