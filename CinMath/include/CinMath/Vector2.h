#pragma once

namespace CinMath {
	template<typename ValueType>
	class Vector<2, ValueType> final
	{
	public:
		using UnderlyingType = ValueType;
	public:
		constexpr explicit Vector<2, ValueType>() noexcept
			:
			x(static_cast<ValueType>(0)),
			y(static_cast<ValueType>(0))
		{}

		constexpr explicit Vector<2, ValueType>(
			const ValueType value) noexcept
			:
			x(value),
			y(value)
		{}

		constexpr explicit Vector<2, ValueType>(
			const ValueType x,
			const ValueType y) noexcept
			:
			x(x),
			y(y)
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

		constexpr bool operator==(const Vector<2, ValueType>& other) const noexcept
		{
			return x == other.x && y == other.y;
		}

		constexpr bool operator!=(const Vector<2, ValueType>& other) const noexcept
		{
			return x != other.x || y != other.y;
		}

		constexpr operator Vector<2, float>() const noexcept
		{
			return Vector<2, float>{ static_cast<float>(x), static_cast<float>(y) };
		}

		constexpr operator Vector<2, double>() const noexcept
		{
			return Vector<2, double>{ static_cast<double>(x), static_cast<double>(y) };
		}

		template<typename T> friend Vector<2, T> operator+(const Vector<2, T>& vector) noexcept;
		template<typename T> friend Vector<2, T> operator-(const Vector<2, T>& vector) noexcept;

		template<typename T> friend void operator+=(Vector<2, T>& lhs, const Vector<4, T>& rhs) noexcept;
		template<typename T> friend void operator-=(Vector<2, T>& lhs, const Vector<4, T>& rhs) noexcept;
		template<typename T> friend void operator*=(Vector<2, T>& lhs, const Vector<4, T>& rhs) noexcept;
		template<typename T> friend void operator/=(Vector<2, T>& lhs, const Vector<4, T>& rhs) noexcept;

		template<typename T> friend void operator+=(Vector<2, T>& lhs, const T scalar) noexcept;
		template<typename T> friend void operator-=(Vector<2, T>& lhs, const T scalar) noexcept;
		template<typename T> friend void operator*=(Vector<2, T>& lhs, const T scalar) noexcept;
		template<typename T> friend void operator/=(Vector<2, T>& lhs, const T scalar) noexcept;

		template<typename T> friend Vector<2, T> operator+(const Vector<2, T>& lhs, const Vector<2, T>& rhs) noexcept;
		template<typename T> friend Vector<2, T> operator-(const Vector<2, T>& lhs, const Vector<2, T>& rhs) noexcept;
		template<typename T> friend Vector<2, T> operator*(const Vector<2, T>& lhs, const Vector<2, T>& rhs) noexcept;
		template<typename T> friend Vector<2, T> operator/(const Vector<2, T>& lhs, const Vector<2, T>& rhs) noexcept;

		template<typename T> friend Vector<2, T> operator+(const Vector<2, T>& lhs, const T scalar) noexcept;
		template<typename T> friend Vector<2, T> operator-(const Vector<2, T>& lhs, const T scalar) noexcept;
		template<typename T> friend Vector<2, T> operator*(const Vector<2, T>& lhs, const T scalar) noexcept;
		template<typename T> friend Vector<2, T> operator/(const Vector<2, T>& lhs, const T scalar) noexcept;
	public:
		union
		{
			struct
			{
				Storage<2, ValueType>::Container data;
			};

			struct
			{
				ValueType raw[2];
			};

			struct
			{
				ValueType x, y;
			};

			struct
			{
				ValueType u, v;
			};

			/* 2-Element swizzle */
			Vector2Swizzle<ValueType, Vector<2, ValueType>, 0, 1> xy;
		};
	};

	typedef Vector<2, float>	Vector2;
	typedef Vector<2, double>	DVector2;
}