#pragma once

namespace CinMath {
	CIN_MATH_INLINE TQuaternion<float> CIN_MATH_CALL operator+(const TQuaternion<float>& quaternion) noexcept
	{
		return quaternion;
	}

	CIN_MATH_INLINE TQuaternion<float> CIN_MATH_CALL operator-(const TQuaternion<float>& quaternion) noexcept
	{
		TQuaternion<float> result;
#if (CIN_INSTRUCTION_SET) & (CIN_INSTRUCTION_SET_SSE_BIT)
		result.data = _mm_mul_ps(quaternion.data, AtCompileTime(__m128{ -1.0f, -1.0f, -1.0f, -1.0f }));
#else
		result.raw[0] = -quaternion.raw[0];
		result.raw[1] = -quaternion.raw[1];
		result.raw[2] = -quaternion.raw[2];
		result.raw[3] = -quaternion.raw[3];
#endif
		return result;
	}
	
	CIN_MATH_INLINE TQuaternion<float> CIN_MATH_CALL operator+(const TQuaternion<float>& lhs, const TQuaternion<float>& rhs) noexcept
	{
		TQuaternion<float> result;
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

	CIN_MATH_INLINE TQuaternion<float> CIN_MATH_CALL operator-(const TQuaternion<float>& lhs, const TQuaternion<float>& rhs) noexcept
	{
		TQuaternion<float> result;
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

	CIN_MATH_INLINE TQuaternion<float> CIN_MATH_CALL operator*(const TQuaternion<float>& lhs, const TQuaternion<float>& rhs) noexcept
	{
		TQuaternion<float> result;
		/* Compute s1s2 - dot(v1v2) */
		result.scalar = (lhs.raw[0] * rhs.raw[0]) - (lhs.raw[1] * rhs.raw[1] + lhs.raw[2] * rhs.raw[2] + lhs.raw[3] * rhs.raw[3]);
		/* Compute s1v2 + s2v1 + cross(v1, v2) */
		const Vector<3, float> s1v2 = rhs.vector * lhs.scalar;
		const Vector<3, float> s2v1 = lhs.vector * rhs.scalar;

		Vector<3, float> cross;
		cross.raw[0] = lhs.vector.raw[1] * rhs.vector.raw[2] - lhs.vector.raw[2] * rhs.vector.raw[1];
		cross.raw[1] = lhs.vector.raw[2] * rhs.vector.raw[0] - lhs.vector.raw[0] * rhs.vector.raw[2];
		cross.raw[2] = lhs.vector.raw[0] * rhs.vector.raw[1] - lhs.vector.raw[1] * rhs.vector.raw[0];

		result.vector = s1v2 + s2v1 + cross;

		return result;
	}

	CIN_MATH_INLINE TQuaternion<float> CIN_MATH_CALL operator/(const TQuaternion<float>& lhs, const TQuaternion<float>& rhs) noexcept
	{
		TQuaternion<float> result;

		const float norm
		{ 
			std::sqrt
			(
				+ lhs.raw[0] * lhs.raw[0]
				+ lhs.raw[1] * lhs.raw[1]
				+ lhs.raw[2] * lhs.raw[2]
				+ lhs.raw[3] * lhs.raw[3]
			)
		};

		result.raw[1] = (lhs.raw[0] * rhs.raw[1] - lhs.raw[1] * rhs.raw[0] - lhs.raw[2] * rhs.raw[3] + lhs.raw[3] * rhs.raw[2]) / norm;
		result.raw[0] = (lhs.raw[0] * rhs.raw[0] + lhs.raw[1] * rhs.raw[1] + lhs.raw[2] * rhs.raw[2] + lhs.raw[3] * rhs.raw[3]) / norm;
		result.raw[2] = (lhs.raw[0] * rhs.raw[2] + lhs.raw[1] * rhs.raw[3] - lhs.raw[2] * rhs.raw[0] - lhs.raw[3] * rhs.raw[1]) / norm;
		result.raw[3] = (lhs.raw[0] * rhs.raw[3] - lhs.raw[1] * rhs.raw[2] + lhs.raw[2] * rhs.raw[1] - lhs.raw[3] * rhs.raw[0]) / norm;

		return result;
	}

	CIN_MATH_INLINE TQuaternion<float> CIN_MATH_CALL operator*(const TQuaternion<float>& quaternion, const float _scalar) noexcept
	{
		TQuaternion<float> result;
#if (CIN_INSTRUCTION_SET) & (CIN_INSTRUCTION_SET_SSE_BIT)
		result.data = _mm_mul_ps(quaternion.data, __m128{ _scalar, _scalar, _scalar, _scalar });
#else
		result.raw[0] = quaternion.raw[0] * _scalar;
		result.raw[1] = quaternion.raw[1] * _scalar;
		result.raw[2] = quaternion.raw[2] * _scalar;
		result.raw[3] = quaternion.raw[3] * _scalar;
#endif
		return result;
	}

	CIN_MATH_INLINE TQuaternion<float> CIN_MATH_CALL operator/(const TQuaternion<float>& quaternion, const float _scalar) noexcept 
	{
		TQuaternion<float> result;
#if (CIN_INSTRUCTION_SET) & (CIN_INSTRUCTION_SET_SSE_BIT)
		result.data = _mm_div_ps(quaternion.data, __m128{ _scalar, _scalar, _scalar, _scalar });
#else
		result.raw[0] = quaternion.raw[0] / _scalar;
		result.raw[1] = quaternion.raw[1] / _scalar;
		result.raw[2] = quaternion.raw[2] / _scalar;
		result.raw[3] = quaternion.raw[3] / _scalar;
#endif
		return result;
	}

	CIN_MATH_INLINE TQuaternion<double> CIN_MATH_CALL operator+(const TQuaternion<double>& quaternion) noexcept
	{
		return quaternion;
	}

	CIN_MATH_INLINE TQuaternion<double> CIN_MATH_CALL operator-(const TQuaternion<double>& quaternion) noexcept
	{
		TQuaternion<double> result;
		
		result.raw[0] = -quaternion.raw[0];
		result.raw[1] = -quaternion.raw[1];
		result.raw[2] = -quaternion.raw[2];
		result.raw[3] = -quaternion.raw[3];
		
		return result;
	}

	CIN_MATH_INLINE TQuaternion<double> CIN_MATH_CALL operator+(const TQuaternion<double>& lhs, const TQuaternion<double>& rhs) noexcept
	{
		TQuaternion<double> result;

		result.raw[0] = lhs.raw[0] + rhs.raw[0];
		result.raw[1] = lhs.raw[1] + rhs.raw[1];
		result.raw[2] = lhs.raw[2] + rhs.raw[2];
		result.raw[3] = lhs.raw[3] + rhs.raw[3];

		return result;
	}

	CIN_MATH_INLINE TQuaternion<double> CIN_MATH_CALL operator-(const TQuaternion<double>& lhs, const TQuaternion<double>& rhs) noexcept
	{
		TQuaternion<double> result;

		result.raw[0] = lhs.raw[0] - rhs.raw[0];
		result.raw[1] = lhs.raw[1] - rhs.raw[1];
		result.raw[2] = lhs.raw[2] - rhs.raw[2];
		result.raw[3] = lhs.raw[3] - rhs.raw[3];

		return result;
	}

	CIN_MATH_INLINE TQuaternion<double> CIN_MATH_CALL operator*(const TQuaternion<double>& lhs, const TQuaternion<double>& rhs) noexcept
	{
		TQuaternion<double> result;
		/* Compute s1s2 - dot(v1v2) */
		result.scalar = (lhs.raw[0] * rhs.raw[0]) - (lhs.raw[1] * rhs.raw[1] + lhs.raw[2] * rhs.raw[2] + lhs.raw[3] * rhs.raw[3]);
		/* Compute s1v2 + s2v1 + cross(v1, v2) */
		const Vector<3, double> s1v2 = rhs.vector * lhs.scalar;
		const Vector<3, double> s2v1 = lhs.vector * rhs.scalar;

		Vector<3, double> cross;
		cross.raw[0] = lhs.vector.raw[1] * rhs.vector.raw[2] - lhs.vector.raw[2] * rhs.vector.raw[1];
		cross.raw[1] = lhs.vector.raw[2] * rhs.vector.raw[0] - lhs.vector.raw[0] * rhs.vector.raw[2];
		cross.raw[2] = lhs.vector.raw[0] * rhs.vector.raw[1] - lhs.vector.raw[1] * rhs.vector.raw[0];

		result.vector = s1v2 + s2v1 + cross;

		return result;
	}

	CIN_MATH_INLINE TQuaternion<double> CIN_MATH_CALL operator/(const TQuaternion<double>& lhs, const TQuaternion<double>& rhs) noexcept
	{
		TQuaternion<double> result;

		const double norm
		{ 
			std::sqrt
			(
				+ lhs.raw[0] * lhs.raw[0]
				+ lhs.raw[1] * lhs.raw[1]
				+ lhs.raw[2] * lhs.raw[2]
				+ lhs.raw[3] * lhs.raw[3]
			)
		};

		result.raw[1] = (lhs.raw[0] * rhs.raw[1] - lhs.raw[1] * rhs.raw[0] - lhs.raw[2] * rhs.raw[3] + lhs.raw[3] * rhs.raw[2]) / norm;
		result.raw[0] = (lhs.raw[0] * rhs.raw[0] + lhs.raw[1] * rhs.raw[1] + lhs.raw[2] * rhs.raw[2] + lhs.raw[3] * rhs.raw[3]) / norm;
		result.raw[2] = (lhs.raw[0] * rhs.raw[2] + lhs.raw[1] * rhs.raw[3] - lhs.raw[2] * rhs.raw[0] - lhs.raw[3] * rhs.raw[1]) / norm;
		result.raw[3] = (lhs.raw[0] * rhs.raw[3] - lhs.raw[1] * rhs.raw[2] + lhs.raw[2] * rhs.raw[1] - lhs.raw[3] * rhs.raw[0]) / norm;

		return result;
	}

	CIN_MATH_INLINE TQuaternion<double> CIN_MATH_CALL operator*(const TQuaternion<double>& quaternion, const double _scalar) noexcept
	{
		TQuaternion<double> result;

		result.raw[0] = quaternion.raw[0] * _scalar;
		result.raw[1] = quaternion.raw[1] * _scalar;
		result.raw[2] = quaternion.raw[2] * _scalar;
		result.raw[3] = quaternion.raw[3] * _scalar;

		return result;
	}

	CIN_MATH_INLINE TQuaternion<double> CIN_MATH_CALL operator/(const TQuaternion<double>& quaternion, const double _scalar) noexcept
	{
		TQuaternion<double> result;

		result.raw[0] = quaternion.raw[0] / _scalar;
		result.raw[1] = quaternion.raw[1] / _scalar;
		result.raw[2] = quaternion.raw[2] / _scalar;
		result.raw[3] = quaternion.raw[3] / _scalar;

		return result;
	}
}