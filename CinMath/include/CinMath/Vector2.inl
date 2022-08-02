#pragma once

namespace CinMath {
	CIN_MATH_INLINE Vector<2, float> CIN_CALL operator+(const Vector<2, float>& vector) noexcept
	{
		return vector;
	}

	CIN_MATH_INLINE Vector<2, float> CIN_CALL operator-(const Vector<2, float>& vector) noexcept
	{
		Vector<2, float> result;

		result.raw[0] = -vector.raw[0];
		result.raw[1] = -vector.raw[1];

		return result;
	}

	CIN_MATH_INLINE void CIN_CALL operator+=(Vector<2, float>& lhs, const Vector<2, float>& rhs) noexcept
	{
		lhs.raw[0] += rhs.raw[0];
		lhs.raw[1] += rhs.raw[1];
	}

	CIN_MATH_INLINE void CIN_CALL operator-=(Vector<2, float>& lhs, const Vector<2, float>& rhs) noexcept
	{
		lhs.raw[0] -= rhs.raw[0];
		lhs.raw[1] -= rhs.raw[1];
	}

	CIN_MATH_INLINE void CIN_CALL operator*=(Vector<2, float>& lhs, const Vector<2, float>& rhs) noexcept
	{
		lhs.raw[0] *= rhs.raw[0];
		lhs.raw[1] *= rhs.raw[1];
	}

	CIN_MATH_INLINE void CIN_CALL operator/=(Vector<2, float>& lhs, const Vector<2, float>& rhs) noexcept
	{
		lhs.raw[0] /= rhs.raw[0];
		lhs.raw[1] /= rhs.raw[1];
	}

	CIN_MATH_INLINE void CIN_CALL operator+=(Vector<2, float>& lhs, const float rhs) noexcept
	{
		lhs.raw[0] += rhs;
		lhs.raw[1] += rhs;
	}

	CIN_MATH_INLINE void CIN_CALL operator-=(Vector<2, float>& lhs, const float rhs) noexcept
	{
		lhs.raw[0] -= rhs;
		lhs.raw[1] -= rhs;
	}

	CIN_MATH_INLINE void CIN_CALL operator*=(Vector<2, float>& lhs, const float rhs) noexcept
	{
		lhs.raw[0] *= rhs;
		lhs.raw[1] *= rhs;
	}

	CIN_MATH_INLINE void CIN_CALL operator/=(Vector<2, float>& lhs, const float rhs) noexcept
	{
		lhs.raw[0] /= rhs;
		lhs.raw[1] /= rhs;
	}

	CIN_MATH_INLINE Vector<2, float> CIN_CALL operator+(const Vector<2, float>& lhs, const Vector<2, float>& rhs) noexcept
	{
		Vector<2, float> result;

		result.raw[0] = lhs.raw[0] + rhs.raw[0];
		result.raw[1] = lhs.raw[1] + rhs.raw[1];

		return result;
	}

	CIN_MATH_INLINE Vector<2, float> CIN_CALL operator-(const Vector<2, float>& lhs, const Vector<2, float>& rhs) noexcept
	{
		Vector<2, float> result;

		result.raw[0] = lhs.raw[0] - rhs.raw[0];
		result.raw[1] = lhs.raw[1] - rhs.raw[1];

		return result;
	}

	CIN_MATH_INLINE Vector<2, float> CIN_CALL operator*(const Vector<2, float>& lhs, const Vector<2, float>& rhs) noexcept
	{
		Vector<2, float> result;

		result.raw[0] = lhs.raw[0] * rhs.raw[0];
		result.raw[1] = lhs.raw[1] * rhs.raw[1];

		return result;
	}

	CIN_MATH_INLINE Vector<2, float> CIN_CALL operator/(const Vector<2, float>& lhs, const Vector<2, float>& rhs) noexcept
	{
		Vector<2, float> result;

		result.raw[0] = lhs.raw[0] / rhs.raw[0];
		result.raw[1] = lhs.raw[1] / rhs.raw[1];

		return result;
	}

	CIN_MATH_INLINE Vector<2, float> CIN_CALL operator+(const Vector<2, float>& lhs, const float rhs) noexcept
	{
		Vector<2, float> result;

		result.raw[0] = lhs.raw[0] + rhs;
		result.raw[1] = lhs.raw[1] + rhs;

		return result;
	}

	CIN_MATH_INLINE Vector<2, float> CIN_CALL operator-(const Vector<2, float>& lhs, const float rhs) noexcept
	{
		Vector<2, float> result;

		result.raw[0] = lhs.raw[0] - rhs;
		result.raw[1] = lhs.raw[1] - rhs;

		return result;
	}

	CIN_MATH_INLINE Vector<2, float> CIN_CALL operator*(const Vector<2, float>& lhs, const float rhs) noexcept
	{
		Vector<2, float> result;

		result.raw[0] = lhs.raw[0] * rhs;
		result.raw[1] = lhs.raw[1] * rhs;

		return result;
	}

	CIN_MATH_INLINE Vector<2, float> CIN_CALL operator/(const Vector<2, float>& lhs, const float rhs) noexcept
	{
		Vector<2, float> result;

		result.raw[0] = lhs.raw[0] / rhs;
		result.raw[1] = lhs.raw[1] / rhs;

		return result;
	}
}