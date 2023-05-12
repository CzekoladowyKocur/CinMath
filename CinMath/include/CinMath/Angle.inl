#pragma once

namespace CinMath {
	constexpr CIN_MATH_INLINE void operator+=(TRadians<float>& lhs, const TRadians<float>& rhs) noexcept
	{
		lhs.Value += rhs.Value;
	}

	constexpr CIN_MATH_INLINE void operator-=(TRadians<float>& lhs, const TRadians<float>& rhs) noexcept
	{
		lhs.Value -= rhs.Value;
	}

	constexpr CIN_MATH_INLINE void operator*=(TRadians<float>& lhs, const TRadians<float>& rhs) noexcept
	{
		lhs.Value *= rhs.Value;
	}
	
	constexpr CIN_MATH_INLINE void operator/=(TRadians<float>& lhs, const TRadians<float>& rhs) noexcept
	{
		lhs.Value /= rhs.Value;
	}

	constexpr CIN_MATH_INLINE void operator+=(TRadians<double>& lhs, const TRadians<double>& rhs) noexcept
	{
		lhs.Value += rhs.Value;
	}

	constexpr CIN_MATH_INLINE void operator-=(TRadians<double>& lhs, const TRadians<double>& rhs) noexcept
	{
		lhs.Value -= rhs.Value;
	}

	constexpr CIN_MATH_INLINE void operator*=(TRadians<double>& lhs, const TRadians<double>& rhs) noexcept
	{
		lhs.Value *= rhs.Value;
	}

	constexpr CIN_MATH_INLINE void operator/=(TRadians<double>& lhs, const TRadians<double>& rhs) noexcept
	{
		lhs.Value /= rhs.Value;
	}

	[[nodiscard]] constexpr CIN_MATH_INLINE TRadians<float> operator+(const TRadians<float>& lhs, const TRadians<float>& rhs) noexcept
	{
		return TRadians<float>{ lhs.operator float() + rhs.operator float() };
	}

	[[nodiscard]] constexpr CIN_MATH_INLINE TRadians<float> operator-(const TRadians<float>& lhs, const TRadians<float>& rhs) noexcept
	{
		return TRadians<float>{ lhs.operator float() - rhs.operator float() };
	}

	[[nodiscard]] constexpr CIN_MATH_INLINE TRadians<float> operator*(const TRadians<float>& lhs, const TRadians<float>& rhs) noexcept
	{
		return TRadians<float>{ lhs.operator float() * rhs.operator float() };
	}

	[[nodiscard]] constexpr CIN_MATH_INLINE TRadians<float> operator/(const TRadians<float>& lhs, const TRadians<float>& rhs) noexcept
	{
		return TRadians<float>{ lhs.operator float() / rhs.operator float() };
	}

	[[nodiscard]] constexpr CIN_MATH_INLINE TRadians<double> operator+(const TRadians<double>& lhs, const TRadians<double>& rhs) noexcept
	{
		return TRadians<double>{ lhs.operator double() + rhs.operator double() };
	}

	[[nodiscard]] constexpr CIN_MATH_INLINE TRadians<double> operator-(const TRadians<double>& lhs, const TRadians<double>& rhs) noexcept
	{
		return TRadians<double>{ lhs.operator double() - rhs.operator double() };
	}

	[[nodiscard]] constexpr CIN_MATH_INLINE TRadians<double> operator*(const TRadians<double>& lhs, const TRadians<double>& rhs) noexcept
	{
		return TRadians<double>{ lhs.operator double() * rhs.operator double() };
	}

	[[nodiscard]] constexpr CIN_MATH_INLINE TRadians<double> operator/(const TRadians<double>& lhs, const TRadians<double>& rhs) noexcept
	{
		return TRadians<double>{ lhs.operator double() / rhs.operator double() };
	}

	constexpr CIN_MATH_INLINE void operator+=(TDegrees<float>& lhs, const TDegrees<float>& rhs) noexcept
	{
		lhs.Value += rhs.Value;
	}

	constexpr CIN_MATH_INLINE void operator-=(TDegrees<float>& lhs, const TDegrees<float>& rhs) noexcept
	{
		lhs.Value -= rhs.Value;
	}

	constexpr CIN_MATH_INLINE void operator*=(TDegrees<float>& lhs, const TDegrees<float>& rhs) noexcept
	{
		lhs.Value *= rhs.Value;
	}

	constexpr CIN_MATH_INLINE void operator/=(TDegrees<float>& lhs, const TDegrees<float>& rhs) noexcept
	{
		lhs.Value /= rhs.Value;
	}

	constexpr CIN_MATH_INLINE void operator+=(TDegrees<double>& lhs, const TDegrees<double>& rhs) noexcept
	{
		lhs.Value += rhs.Value;
	}

	constexpr CIN_MATH_INLINE void operator-=(TDegrees<double>& lhs, const TDegrees<double>& rhs) noexcept
	{
		lhs.Value -= rhs.Value;
	}

	constexpr CIN_MATH_INLINE void operator*=(TDegrees<double>& lhs, const TDegrees<double>& rhs) noexcept
	{
		lhs.Value *= rhs.Value;
	}

	constexpr CIN_MATH_INLINE void operator/=(TDegrees<double>& lhs, const TDegrees<double>& rhs) noexcept
	{
		lhs.Value /= rhs.Value;
	}

	[[nodiscard]] constexpr CIN_MATH_INLINE TDegrees<float> operator+(const TDegrees<float>& lhs, const TDegrees<float>& rhs) noexcept
	{
		return TDegrees<float>::FromValue(lhs.operator float() + rhs.operator float());
	}

	[[nodiscard]] constexpr CIN_MATH_INLINE TDegrees<float> operator-(const TDegrees<float>& lhs, const TDegrees<float>& rhs) noexcept
	{
		return TDegrees<float>::FromValue(lhs.operator float() - rhs.operator float());
	}

	[[nodiscard]] constexpr CIN_MATH_INLINE TDegrees<float> operator*(const TDegrees<float>& lhs, const TDegrees<float>& rhs) noexcept
	{
		return TDegrees<float>::FromValue(lhs.operator float() * rhs.operator float());
	}

	[[nodiscard]] constexpr CIN_MATH_INLINE TDegrees<float> operator/(const TDegrees<float>& lhs, const TDegrees<float>& rhs) noexcept
	{
		return TDegrees<float>::FromValue(lhs.operator float() / rhs.operator float());
	}

	[[nodiscard]] constexpr CIN_MATH_INLINE  TDegrees<double> operator+(const TDegrees<double>& lhs, const TDegrees<double>& rhs) noexcept
	{
		return TDegrees<double>::FromValue(lhs.operator double() + rhs.operator double());
	}

	[[nodiscard]] constexpr CIN_MATH_INLINE TDegrees<double> operator-(const TDegrees<double>& lhs, const TDegrees<double>& rhs) noexcept
	{
		return TDegrees<double>::FromValue(lhs.operator double() - rhs.operator double());
	}

	[[nodiscard]] constexpr CIN_MATH_INLINE TDegrees<double> operator*(const TDegrees<double>& lhs, const TDegrees<double>& rhs) noexcept
	{
		return TDegrees<double>::FromValue(lhs.operator double() * rhs.operator double());
	}

	[[nodiscard]] constexpr CIN_MATH_INLINE TDegrees<double> operator/(const TDegrees<double>& lhs, const TDegrees<double>& rhs) noexcept
	{
		return TDegrees<double>::FromValue(lhs.operator double() / rhs.operator double());
	}
}