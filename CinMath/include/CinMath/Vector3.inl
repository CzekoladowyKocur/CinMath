#pragma once

namespace CinMath {
	CIN_MATH_INLINE Vector<3, float> CIN_CALL operator+(const Vector<3, float>& vector) noexcept
	{
		return vector;
	}

	CIN_MATH_INLINE Vector<3, float> CIN_CALL operator-(const Vector<3, float>& vector) noexcept
	{
		Vector<3, float> result;

		result.raw[0] = -vector.raw[0];
		result.raw[1] = -vector.raw[1];
		result.raw[2] = -vector.raw[2];

		return result;
	}

	CIN_MATH_INLINE void CIN_CALL operator+=(Vector<3, float>& lhs, const Vector<3, float>& rhs) noexcept
	{
		lhs.raw[0] += rhs.raw[0];
		lhs.raw[1] += rhs.raw[1];
		lhs.raw[2] += rhs.raw[2];
	}

	CIN_MATH_INLINE void CIN_CALL operator-=(Vector<3, float>& lhs, const Vector<3, float>& rhs) noexcept
	{
		lhs.raw[0] -= rhs.raw[0];
		lhs.raw[1] -= rhs.raw[1];
		lhs.raw[2] -= rhs.raw[2];
	}

	CIN_MATH_INLINE void CIN_CALL operator*=(Vector<3, float>& lhs, const Vector<3, float>& rhs) noexcept
	{
		lhs.raw[0] *= rhs.raw[0];
		lhs.raw[1] *= rhs.raw[1];
		lhs.raw[2] *= rhs.raw[2];
	}

	CIN_MATH_INLINE void CIN_CALL operator/=(Vector<3, float>& lhs, const Vector<3, float>& rhs) noexcept
	{
		lhs.raw[0] /= rhs.raw[0];
		lhs.raw[1] /= rhs.raw[1];
		lhs.raw[2] /= rhs.raw[2];
	}

	CIN_MATH_INLINE void CIN_CALL operator+=(Vector<3, float>& lhs, const float rhs) noexcept
	{
		lhs.raw[0] += rhs;
		lhs.raw[1] += rhs;
		lhs.raw[2] += rhs;
	}

	CIN_MATH_INLINE void CIN_CALL operator-=(Vector<3, float>& lhs, const float rhs) noexcept
	{
		lhs.raw[0] -= rhs;
		lhs.raw[1] -= rhs;
		lhs.raw[2] -= rhs;
	}

	CIN_MATH_INLINE void CIN_CALL operator*=(Vector<3, float>& lhs, const float rhs) noexcept
	{
		lhs.raw[0] *= rhs;
		lhs.raw[1] *= rhs;
		lhs.raw[2] *= rhs;
	}

	CIN_MATH_INLINE void CIN_CALL operator/=(Vector<3, float>& lhs, const float rhs) noexcept
	{
		lhs.raw[0] /= rhs;
		lhs.raw[1] /= rhs;
		lhs.raw[2] /= rhs;
	}

	CIN_MATH_INLINE Vector<3, float> CIN_CALL operator+(const Vector<3, float>& lhs, const Vector<3, float>& rhs) noexcept
	{
		Vector<3, float> result;

		result.raw[0] = lhs.raw[0] + rhs.raw[0];
		result.raw[1] = lhs.raw[1] + rhs.raw[1];
		result.raw[2] = lhs.raw[2] + rhs.raw[2];

		return result;
	}

	CIN_MATH_INLINE Vector<3, float> CIN_CALL operator-(const Vector<3, float>& lhs, const Vector<3, float>& rhs) noexcept
	{
		Vector<3, float> result;

		result.raw[0] = lhs.raw[0] - rhs.raw[0];
		result.raw[1] = lhs.raw[1] - rhs.raw[1];
		result.raw[2] = lhs.raw[2] - rhs.raw[2];

		return result;
	}

	CIN_MATH_INLINE Vector<3, float> CIN_CALL operator*(const Vector<3, float>& lhs, const Vector<3, float>& rhs) noexcept
	{
		Vector<3, float> result;

		result.raw[0] = lhs.raw[0] * rhs.raw[0];
		result.raw[1] = lhs.raw[1] * rhs.raw[1];
		result.raw[2] = lhs.raw[2] * rhs.raw[2];

		return result;
	}

	CIN_MATH_INLINE Vector<3, float> CIN_CALL operator/(const Vector<3, float>& lhs, const Vector<3, float>& rhs) noexcept
	{
		Vector<3, float> result;

		result.raw[0] = lhs.raw[0] / rhs.raw[0];
		result.raw[1] = lhs.raw[1] / rhs.raw[1];
		result.raw[2] = lhs.raw[2] / rhs.raw[2];

		return result;
	}

	CIN_MATH_INLINE Vector<3, float> CIN_CALL operator+(const Vector<3, float>& lhs, const float rhs) noexcept
	{
		Vector<3, float> result;

		result.raw[0] = lhs.raw[0] + rhs;
		result.raw[1] = lhs.raw[1] + rhs;
		result.raw[2] = lhs.raw[2] + rhs;

		return result;
	}

	CIN_MATH_INLINE Vector<3, float> CIN_CALL operator-(const Vector<3, float>& lhs, const float rhs) noexcept
	{
		Vector<3, float> result;

		result.raw[0] = lhs.raw[0] - rhs;
		result.raw[1] = lhs.raw[1] - rhs;
		result.raw[2] = lhs.raw[2] - rhs;

		return result;
	}

	CIN_MATH_INLINE Vector<3, float> CIN_CALL operator*(const Vector<3, float>& lhs, const float rhs) noexcept
	{
		Vector<3, float> result;

		result.raw[0] = lhs.raw[0] * rhs;
		result.raw[1] = lhs.raw[1] * rhs;
		result.raw[2] = lhs.raw[2] * rhs;
		
		return result;
	}

	CIN_MATH_INLINE Vector<3, float> CIN_CALL operator/(const Vector<3, float>& lhs, const float rhs) noexcept
	{
		Vector<3, float> result;

		result.raw[0] = lhs.raw[0] / rhs;
		result.raw[1] = lhs.raw[1] / rhs;
		result.raw[2] = lhs.raw[2] / rhs;
		
		return result;
	}
}