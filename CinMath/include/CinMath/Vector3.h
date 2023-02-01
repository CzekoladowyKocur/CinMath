#pragma once

namespace CinMath {
	template<typename ValueType>
	class Vector<3, ValueType> final
	{
	public:
		using UnderlyingType = ValueType;
	public:
		consteval explicit Vector<3, ValueType>() noexcept
			:
			x(static_cast<ValueType>(0)),
			y(static_cast<ValueType>(0)),
			z(static_cast<ValueType>(0))
		{}

		constexpr explicit Vector<3, ValueType>(
			const ValueType value) noexcept
			:
			x(value),
			y(value),
			z(value)
		{}

		constexpr explicit Vector<3, ValueType>(
			const ValueType x,
			const ValueType y,
			const ValueType z) noexcept
			:
			x(x),
			y(y),
			z(z)
		{}

		constexpr operator ValueType* () noexcept
		{
			return raw;
		}

		constexpr operator const ValueType* () const noexcept
		{
			return raw;
		}

		constexpr ValueType& operator[](const Length_t index) noexcept
		{
			return raw[index];
		}

		constexpr const ValueType operator[](const Length_t index) const noexcept
		{
			return raw[index];
		}

		constexpr bool operator==(const Vector<3, ValueType>& other) const noexcept
		{
			return x == other.x && y == other.y && z == other.z;
		}

		constexpr bool operator!=(const Vector<3, ValueType>& other) const noexcept
		{
			return x != other.x || y != other.y || z != other.z;
		}

		constexpr operator Vector<3, float>() const noexcept
		{
			return Vector<3, float>{ static_cast<float>(x), static_cast<float>(y), static_cast<float>(z) };
		}

		constexpr operator Vector<3, double>() const noexcept
		{
			return Vector<3, double>{ static_cast<double>(x), static_cast<double>(y), static_cast<double>(z) };
		}

		[[nodiscard]] friend Vector<3, ValueType> CIN_MATH_CALL operator+(const Vector<3, ValueType>& vector) noexcept;
		[[nodiscard]] friend Vector<3, ValueType> CIN_MATH_CALL operator-(const Vector<3, ValueType>& vector) noexcept;

		friend void CIN_MATH_CALL operator+=(Vector<3, ValueType>& lhs, const Vector<4, ValueType>& rhs) noexcept;
		friend void CIN_MATH_CALL operator-=(Vector<3, ValueType>& lhs, const Vector<4, ValueType>& rhs) noexcept;
		friend void CIN_MATH_CALL operator*=(Vector<3, ValueType>& lhs, const Vector<4, ValueType>& rhs) noexcept;
		friend void CIN_MATH_CALL operator/=(Vector<3, ValueType>& lhs, const Vector<4, ValueType>& rhs) noexcept;

		friend void CIN_MATH_CALL operator+=(Vector<3, ValueType>& lhs, const ValueType scalar) noexcept;
		friend void CIN_MATH_CALL operator-=(Vector<3, ValueType>& lhs, const ValueType scalar) noexcept;
		friend void CIN_MATH_CALL operator*=(Vector<3, ValueType>& lhs, const ValueType scalar) noexcept;
		friend void CIN_MATH_CALL operator/=(Vector<3, ValueType>& lhs, const ValueType scalar) noexcept;

		[[nodiscard]] friend Vector<3, ValueType> CIN_MATH_CALL operator+(const Vector<3, ValueType>& lhs, const Vector<3, ValueType>& rhs) noexcept;
		[[nodiscard]] friend Vector<3, ValueType> CIN_MATH_CALL operator-(const Vector<3, ValueType>& lhs, const Vector<3, ValueType>& rhs) noexcept;
		[[nodiscard]] friend Vector<3, ValueType> CIN_MATH_CALL operator*(const Vector<3, ValueType>& lhs, const Vector<3, ValueType>& rhs) noexcept;
		[[nodiscard]] friend Vector<3, ValueType> CIN_MATH_CALL operator/(const Vector<3, ValueType>& lhs, const Vector<3, ValueType>& rhs) noexcept;

		[[nodiscard]] friend Vector<3, ValueType> CIN_MATH_CALL operator+(const Vector<3, ValueType>& lhs, const ValueType scalar) noexcept;
		[[nodiscard]] friend Vector<3, ValueType> CIN_MATH_CALL operator-(const Vector<3, ValueType>& lhs, const ValueType scalar) noexcept;
		[[nodiscard]] friend Vector<3, ValueType> CIN_MATH_CALL operator*(const Vector<3, ValueType>& lhs, const ValueType scalar) noexcept;
		[[nodiscard]] friend Vector<3, ValueType> CIN_MATH_CALL operator/(const Vector<3, ValueType>& lhs, const ValueType scalar) noexcept;
	public:
		union
		{
			struct
			{
				Storage<3, ValueType>::Container data;
			};

			struct
			{
				ValueType raw[3];
			};

			struct
			{
				ValueType x, y, z;
			};

			struct
			{
				ValueType r, g, b;
			};

			/* 2-Element swizzle */
			Vector2Swizzle<ValueType, Vector<2, ValueType>, 0, 1> xy;
			Vector2Swizzle<ValueType, Vector<2, ValueType>, 0, 2> xz;

			Vector2Swizzle<ValueType, Vector<2, ValueType>, 1, 2> yz;

			/* 3-Element swizzle */
			Vector3Swizzle<ValueType, Vector<3, ValueType>, 0, 1, 2> xyz;
		};
	};

	typedef Vector<3, float>	Vector3;
	typedef Vector<3, double>	DVector3;
}