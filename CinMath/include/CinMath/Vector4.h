#pragma once

namespace CinMath {
	template<typename ValueType>
	class Vector<4, ValueType> final
	{
	public:
		using UnderlyingType = ValueType;
	public:
		constexpr explicit Vector<4, ValueType>() noexcept
			:
			x(static_cast<ValueType>(0)),
			y(static_cast<ValueType>(0)),
			z(static_cast<ValueType>(0)),
			w(static_cast<ValueType>(0))
		{}

		constexpr explicit Vector<4, ValueType>(
			const ValueType value) noexcept
			:
			x(value),
			y(value),
			z(value),
			w(value)
		{}

		constexpr explicit Vector<4, ValueType>(
			const ValueType x,
			const ValueType y,
			const ValueType z,
			const ValueType w) noexcept
			:
			x(x),
			y(y),
			z(z),
			w(w)
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

		constexpr bool operator==(const Vector<4, ValueType>& other) const noexcept
		{
			return x == other.x && y == other.y && z == other.z && w == other.w;
		}

		constexpr bool operator!=(const Vector<4, ValueType>& other) const noexcept
		{
			return x != other.x || y != other.y || z != other.z || w != other.w;
		}

		constexpr operator Vector<4, float>() const noexcept
		{
			return Vector<4, float>{ static_cast<float>(x), static_cast<float>(y), static_cast<float>(z), static_cast<float>(w) };
		}

		constexpr operator Vector<4, double>() const noexcept
		{
			return Vector<4, double>{ static_cast<double>(x), static_cast<double>(y), static_cast<double>(z), static_cast<double>(w) };
		}

		template<typename T> friend Vector<4, T> operator+(const Vector<4, T>& vector) noexcept;
		template<typename T> friend Vector<4, T> operator-(const Vector<4, T>& vector) noexcept;

		template<typename T> friend void operator+=(Vector<4, T>& lhs, const Vector<4, T>& rhs) noexcept;
		template<typename T> friend void operator-=(Vector<4, T>& lhs, const Vector<4, T>& rhs) noexcept;
		template<typename T> friend void operator*=(Vector<4, T>& lhs, const Vector<4, T>& rhs) noexcept;
		template<typename T> friend void operator/=(Vector<4, T>& lhs, const Vector<4, T>& rhs) noexcept;

		template<typename T> friend void operator+=(Vector<4, T>& lhs, const T scalar) noexcept;
		template<typename T> friend void operator-=(Vector<4, T>& lhs, const T scalar) noexcept;
		template<typename T> friend void operator*=(Vector<4, T>& lhs, const T scalar) noexcept;
		template<typename T> friend void operator/=(Vector<4, T>& lhs, const T scalar) noexcept;

		template<typename T> friend Vector<4, T> operator+(const Vector<4, T>& lhs, const Vector<4, T>& rhs) noexcept;
		template<typename T> friend Vector<4, T> operator-(const Vector<4, T>& lhs, const Vector<4, T>& rhs) noexcept;
		template<typename T> friend Vector<4, T> operator*(const Vector<4, T>& lhs, const Vector<4, T>& rhs) noexcept;
		template<typename T> friend Vector<4, T> operator/(const Vector<4, T>& lhs, const Vector<4, T>& rhs) noexcept;

		template<typename T> friend Vector<4, T> operator+(const Vector<4, T>& lhs, const T scalar) noexcept;
		template<typename T> friend Vector<4, T> operator-(const Vector<4, T>& lhs, const T scalar) noexcept;
		template<typename T> friend Vector<4, T> operator*(const Vector<4, T>& lhs, const T scalar) noexcept;
		template<typename T> friend Vector<4, T> operator/(const Vector<4, T>& lhs, const T scalar) noexcept;

		template<typename T> friend Vector<4, T> operator*(const Vector<4, T>& lhs, const Matrix<4, 4, T>& rhs) noexcept;
	public:
		union
		{
			struct
			{
				Storage<4, ValueType>::Container data;
			};

			struct
			{
				ValueType raw[4];
			};

			struct
			{
				ValueType x, y, z, w;
			};

			struct
			{
				ValueType r, g, b, a;
			};

			/* 2-Element swizzle */
			Vector2Swizzle<ValueType, Vector<2, ValueType>, 0, 1> xy;
			Vector2Swizzle<ValueType, Vector<2, ValueType>, 0, 2> xz;
			Vector2Swizzle<ValueType, Vector<2, ValueType>, 0, 3> xw;

			Vector2Swizzle<ValueType, Vector<2, ValueType>, 1, 2> yz;
			Vector2Swizzle<ValueType, Vector<2, ValueType>, 1, 3> yw;

			Vector2Swizzle<ValueType, Vector<2, ValueType>, 2, 3> zw;

			/* 3-Element swizzle */
			Vector3Swizzle<ValueType, Vector<3, ValueType>, 0, 1, 2> xyz;
			Vector3Swizzle<ValueType, Vector<3, ValueType>, 1, 2, 3> yzw;

			/* 4-Element swizzle */
			Vector4Swizzle<ValueType, Vector<4, ValueType>, 0, 1, 2, 3> xyzw;
		};
	};

	typedef Vector<4, float>	Vector4;
	typedef Vector<4, double>	DVector4;
}