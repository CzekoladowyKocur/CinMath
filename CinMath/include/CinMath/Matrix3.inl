#pragma once

namespace CinMath {
	CIN_MATH_INLINE Matrix<3, 3, float> CIN_CALL operator+(const Matrix<3, 3, float>& matrix) noexcept
	{
		return matrix;
	}

	CIN_MATH_INLINE Matrix<3, 3, float> CIN_CALL operator-(const Matrix<3, 3, float>& matrix) noexcept
	{
		Matrix<3, 3, float> result;

		result.raw[0] = -matrix.raw[0];
		result.raw[1] = -matrix.raw[1];
		result.raw[2] = -matrix.raw[2];

		result.raw[3] = -matrix.raw[3];
		result.raw[4] = -matrix.raw[4];
		result.raw[5] = -matrix.raw[5];

		result.raw[6] = -matrix.raw[6];
		result.raw[7] = -matrix.raw[7];
		result.raw[8] = -matrix.raw[8];

		return result;
	}

	CIN_MATH_INLINE void CIN_CALL operator+=(Matrix<3, 3, float>& lhs, const Matrix<3, 3, float>& rhs) noexcept
	{
		lhs.raw[0] += rhs.raw[0];
		lhs.raw[1] += rhs.raw[1];
		lhs.raw[2] += rhs.raw[2];

		lhs.raw[3] += rhs.raw[3];
		lhs.raw[4] += rhs.raw[4];
		lhs.raw[5] += rhs.raw[5];

		lhs.raw[6] += rhs.raw[6];
		lhs.raw[7] += rhs.raw[7];
		lhs.raw[8] += rhs.raw[8];
	}

	CIN_MATH_INLINE void CIN_CALL operator-=(Matrix<3, 3, float>& lhs, const Matrix<3, 3, float>& rhs) noexcept
	{
		lhs.raw[0] -= rhs.raw[0];
		lhs.raw[1] -= rhs.raw[1];
		lhs.raw[2] -= rhs.raw[2];
		lhs.raw[3] -= rhs.raw[3];
		lhs.raw[4] -= rhs.raw[4];
		lhs.raw[5] -= rhs.raw[5];
		lhs.raw[6] -= rhs.raw[6];
		lhs.raw[7] -= rhs.raw[7];
		lhs.raw[8] -= rhs.raw[8];
	}

	CIN_MATH_INLINE void CIN_CALL operator*=(Matrix<3, 3, float>& lhs, const Matrix<3, 3, float>& rhs) noexcept
	{
		Matrix<3, 3, float> result;

		result.raw[0] = lhs.raw[0 + 0] * rhs.raw[0 + 0] + lhs.raw[3 + 0] * rhs.raw[1 + 0] + lhs.raw[6 + 0] * rhs.raw[2 + 0];
		result.raw[1] = lhs.raw[0 + 1] * rhs.raw[0 + 0] + lhs.raw[3 + 1] * rhs.raw[1 + 0] + lhs.raw[6 + 1] * rhs.raw[2 + 0];
		result.raw[2] = lhs.raw[0 + 2] * rhs.raw[0 + 0] + lhs.raw[3 + 2] * rhs.raw[1 + 0] + lhs.raw[6 + 2] * rhs.raw[2 + 0];
		result.raw[3] = lhs.raw[0 + 0] * rhs.raw[0 + 3] + lhs.raw[3 + 0] * rhs.raw[1 + 3] + lhs.raw[6 + 0] * rhs.raw[2 + 3];
		result.raw[4] = lhs.raw[0 + 1] * rhs.raw[0 + 3] + lhs.raw[3 + 1] * rhs.raw[1 + 3] + lhs.raw[6 + 1] * rhs.raw[2 + 3];
		result.raw[5] = lhs.raw[0 + 2] * rhs.raw[0 + 3] + lhs.raw[3 + 2] * rhs.raw[1 + 3] + lhs.raw[6 + 2] * rhs.raw[2 + 3];
		result.raw[6] = lhs.raw[0 + 0] * rhs.raw[0 + 6] + lhs.raw[3 + 0] * rhs.raw[1 + 6] + lhs.raw[6 + 0] * rhs.raw[2 + 6];
		result.raw[7] = lhs.raw[0 + 1] * rhs.raw[0 + 6] + lhs.raw[3 + 1] * rhs.raw[1 + 6] + lhs.raw[6 + 1] * rhs.raw[2 + 6];
		result.raw[8] = lhs.raw[0 + 2] * rhs.raw[0 + 6] + lhs.raw[3 + 2] * rhs.raw[1 + 6] + lhs.raw[6 + 2] * rhs.raw[2 + 6];

		lhs = result;
	}

	CIN_MATH_INLINE void CIN_CALL operator+=(Matrix<3, 3, float>& lhs, const float rhs) noexcept
	{
		lhs.raw[0] += rhs;
		lhs.raw[1] += rhs;
		lhs.raw[2] += rhs;
		lhs.raw[3] += rhs;
		lhs.raw[4] += rhs;
		lhs.raw[5] += rhs;
		lhs.raw[6] += rhs;
		lhs.raw[7] += rhs;
		lhs.raw[8] += rhs;
	}

	CIN_MATH_INLINE void CIN_CALL operator-=(Matrix<3, 3, float>& lhs, const float rhs) noexcept
	{
		lhs.raw[0] -= rhs;
		lhs.raw[1] -= rhs;
		lhs.raw[2] -= rhs;
		lhs.raw[3] -= rhs;
		lhs.raw[4] -= rhs;
		lhs.raw[5] -= rhs;
		lhs.raw[6] -= rhs;
		lhs.raw[7] -= rhs;
		lhs.raw[8] -= rhs;
	}

	CIN_MATH_INLINE void CIN_CALL operator*=(Matrix<3, 3, float>& lhs, const float rhs) noexcept
	{
		lhs.raw[0] *= rhs;
		lhs.raw[1] *= rhs;
		lhs.raw[2] *= rhs;
		lhs.raw[3] *= rhs;
		lhs.raw[4] *= rhs;
		lhs.raw[5] *= rhs;
		lhs.raw[6] *= rhs;
		lhs.raw[7] *= rhs;
		lhs.raw[8] *= rhs;
	}

	CIN_MATH_INLINE void CIN_CALL operator/=(Matrix<3, 3, float>& lhs, const float rhs) noexcept
	{
		lhs.raw[0] /= rhs;
		lhs.raw[1] /= rhs;
		lhs.raw[2] /= rhs;
		lhs.raw[3] /= rhs;
		lhs.raw[4] /= rhs;
		lhs.raw[5] /= rhs;
		lhs.raw[6] /= rhs;
		lhs.raw[7] /= rhs;
		lhs.raw[8] /= rhs;
	}

	CIN_MATH_INLINE Matrix<3, 3, float> CIN_CALL operator+(const Matrix<3, 3, float>& lhs, const Matrix<3, 3, float>& rhs) noexcept
	{
		Matrix<3, 3, float> result;

		result.raw[0] = lhs.raw[0] + rhs.raw[0];
		result.raw[1] = lhs.raw[1] + rhs.raw[1];
		result.raw[2] = lhs.raw[2] + rhs.raw[2];
		result.raw[3] = lhs.raw[3] + rhs.raw[3];
		result.raw[4] = lhs.raw[4] + rhs.raw[4];
		result.raw[5] = lhs.raw[5] + rhs.raw[5];
		result.raw[6] = lhs.raw[6] + rhs.raw[6];
		result.raw[7] = lhs.raw[7] + rhs.raw[7];
		result.raw[8] = lhs.raw[8] + rhs.raw[8];

		return result;
	}

	CIN_MATH_INLINE Matrix<3, 3, float> CIN_CALL operator-(const Matrix<3, 3, float>& lhs, const Matrix<3, 3, float>& rhs) noexcept
	{
		Matrix<3, 3, float> result;

		result.raw[0] = lhs.raw[0] - rhs.raw[0];
		result.raw[1] = lhs.raw[1] - rhs.raw[1];
		result.raw[2] = lhs.raw[2] - rhs.raw[2];
		result.raw[3] = lhs.raw[3] - rhs.raw[3];
		result.raw[4] = lhs.raw[4] - rhs.raw[4];
		result.raw[5] = lhs.raw[5] - rhs.raw[5];
		result.raw[6] = lhs.raw[6] - rhs.raw[6];
		result.raw[7] = lhs.raw[7] - rhs.raw[7];
		result.raw[8] = lhs.raw[8] - rhs.raw[8];

		return result;
	}

	CIN_MATH_INLINE Matrix<3, 3, float> CIN_CALL operator*(const Matrix<3, 3, float>& lhs, const Matrix<3, 3, float>& rhs) noexcept
	{
		Matrix<3, 3, float> result;

		result.raw[0] = lhs.raw[0 + 0] * rhs.raw[0 + 0] + lhs.raw[3 + 0] * rhs.raw[1 + 0] + lhs.raw[6 + 0] * rhs.raw[2 + 0];
		result.raw[1] = lhs.raw[0 + 1] * rhs.raw[0 + 0] + lhs.raw[3 + 1] * rhs.raw[1 + 0] + lhs.raw[6 + 1] * rhs.raw[2 + 0];
		result.raw[2] = lhs.raw[0 + 2] * rhs.raw[0 + 0] + lhs.raw[3 + 2] * rhs.raw[1 + 0] + lhs.raw[6 + 2] * rhs.raw[2 + 0];
		result.raw[3] = lhs.raw[0 + 0] * rhs.raw[0 + 3] + lhs.raw[3 + 0] * rhs.raw[1 + 3] + lhs.raw[6 + 0] * rhs.raw[2 + 3];
		result.raw[4] = lhs.raw[0 + 1] * rhs.raw[0 + 3] + lhs.raw[3 + 1] * rhs.raw[1 + 3] + lhs.raw[6 + 1] * rhs.raw[2 + 3];
		result.raw[5] = lhs.raw[0 + 2] * rhs.raw[0 + 3] + lhs.raw[3 + 2] * rhs.raw[1 + 3] + lhs.raw[6 + 2] * rhs.raw[2 + 3];
		result.raw[6] = lhs.raw[0 + 0] * rhs.raw[0 + 6] + lhs.raw[3 + 0] * rhs.raw[1 + 6] + lhs.raw[6 + 0] * rhs.raw[2 + 6];
		result.raw[7] = lhs.raw[0 + 1] * rhs.raw[0 + 6] + lhs.raw[3 + 1] * rhs.raw[1 + 6] + lhs.raw[6 + 1] * rhs.raw[2 + 6];
		result.raw[8] = lhs.raw[0 + 2] * rhs.raw[0 + 6] + lhs.raw[3 + 2] * rhs.raw[1 + 6] + lhs.raw[6 + 2] * rhs.raw[2 + 6];

		return result;
	}

	CIN_MATH_INLINE Matrix<3, 3, float> CIN_CALL operator+(const Matrix<3, 3, float>& lhs, const float rhs) noexcept
	{
		Matrix<3, 3, float> result;

		result.raw[0] = lhs.raw[0] + rhs;
		result.raw[1] = lhs.raw[1] + rhs;
		result.raw[2] = lhs.raw[2] + rhs;
		result.raw[3] = lhs.raw[3] + rhs;
		result.raw[4] = lhs.raw[4] + rhs;
		result.raw[5] = lhs.raw[5] + rhs;
		result.raw[6] = lhs.raw[6] + rhs;
		result.raw[7] = lhs.raw[7] + rhs;
		result.raw[8] = lhs.raw[8] + rhs;

		return result;
	}

	CIN_MATH_INLINE Matrix<3, 3, float> CIN_CALL operator-(const Matrix<3, 3, float>& lhs, const float rhs) noexcept
	{
		Matrix<3, 3, float> result;

		result.raw[0] = lhs.raw[0] - rhs;
		result.raw[1] = lhs.raw[1] - rhs;
		result.raw[2] = lhs.raw[2] - rhs;
		result.raw[3] = lhs.raw[3] - rhs;
		result.raw[4] = lhs.raw[4] - rhs;
		result.raw[5] = lhs.raw[5] - rhs;
		result.raw[6] = lhs.raw[6] - rhs;
		result.raw[7] = lhs.raw[7] - rhs;
		result.raw[8] = lhs.raw[8] - rhs;

		return result;
	}

	CIN_MATH_INLINE Matrix<3, 3, float> CIN_CALL operator*(const Matrix<3, 3, float>& lhs, const float rhs) noexcept
	{
		Matrix<3, 3, float> result;

		result.raw[0] = lhs.raw[0] * rhs;
		result.raw[1] = lhs.raw[1] * rhs;
		result.raw[2] = lhs.raw[2] * rhs;
		result.raw[3] = lhs.raw[3] * rhs;
		result.raw[4] = lhs.raw[4] * rhs;
		result.raw[5] = lhs.raw[5] * rhs;
		result.raw[6] = lhs.raw[6] * rhs;
		result.raw[7] = lhs.raw[7] * rhs;
		result.raw[8] = lhs.raw[8] * rhs;

		return result;
	}

	CIN_MATH_INLINE Matrix<3, 3, float> CIN_CALL operator/(const Matrix<3, 3, float>& lhs, const float rhs) noexcept
	{
		Matrix<3, 3, float> result;

		result.raw[0] = lhs.raw[0] / rhs;
		result.raw[1] = lhs.raw[1] / rhs;
		result.raw[2] = lhs.raw[2] / rhs;
		result.raw[3] = lhs.raw[3] / rhs;
		result.raw[4] = lhs.raw[4] / rhs;
		result.raw[5] = lhs.raw[5] / rhs;
		result.raw[6] = lhs.raw[6] / rhs;
		result.raw[7] = lhs.raw[7] / rhs;
		result.raw[8] = lhs.raw[8] / rhs;

		return result;
	}
}