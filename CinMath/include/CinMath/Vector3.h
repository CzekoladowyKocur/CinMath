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

		explicit Vector<3, ValueType>(
			const ValueType value) noexcept
			:
			x(value),
			y(value),
			z(value)
		{}

		explicit Vector<3, ValueType>(
			const ValueType x,
			const ValueType y,
			const ValueType z) noexcept
			:
			x(x),
			y(y),
			z(z)
		{}

		CIN_MATH_INLINE operator ValueType* () noexcept
		{
			return raw;
		}

		CIN_MATH_INLINE operator const ValueType* () const noexcept
		{
			return raw;
		}

		CIN_MATH_INLINE ValueType& operator[](const Length_t index) noexcept
		{
			return raw[index];
		}

		CIN_MATH_INLINE const ValueType operator[](const Length_t index) const noexcept
		{
			return raw[index];
		}

		friend Vector<3, ValueType> CIN_CALL operator+(const Vector<3, ValueType>& vector) noexcept;
		friend Vector<3, ValueType> CIN_CALL operator-(const Vector<3, ValueType>& vector) noexcept;

		friend void CIN_CALL operator+=(Vector<3, ValueType>& lhs, const Vector<4, ValueType>& rhs) noexcept;
		friend void CIN_CALL operator-=(Vector<3, ValueType>& lhs, const Vector<4, ValueType>& rhs) noexcept;
		friend void CIN_CALL operator*=(Vector<3, ValueType>& lhs, const Vector<4, ValueType>& rhs) noexcept;
		friend void CIN_CALL operator/=(Vector<3, ValueType>& lhs, const Vector<4, ValueType>& rhs) noexcept;

		friend void CIN_CALL operator+=(Vector<3, ValueType>& lhs, const ValueType scalar) noexcept;
		friend void CIN_CALL operator-=(Vector<3, ValueType>& lhs, const ValueType scalar) noexcept;
		friend void CIN_CALL operator*=(Vector<3, ValueType>& lhs, const ValueType scalar) noexcept;
		friend void CIN_CALL operator/=(Vector<3, ValueType>& lhs, const ValueType scalar) noexcept;

		friend Vector<3, ValueType> CIN_CALL operator+(const Vector<3, ValueType>& lhs, const Vector<3, ValueType>& rhs) noexcept;
		friend Vector<3, ValueType> CIN_CALL operator-(const Vector<3, ValueType>& lhs, const Vector<3, ValueType>& rhs) noexcept;
		friend Vector<3, ValueType> CIN_CALL operator*(const Vector<3, ValueType>& lhs, const Vector<3, ValueType>& rhs) noexcept;
		friend Vector<3, ValueType> CIN_CALL operator/(const Vector<3, ValueType>& lhs, const Vector<3, ValueType>& rhs) noexcept;

		friend Vector<3, ValueType> CIN_CALL operator+(const Vector<3, ValueType>& lhs, const ValueType scalar) noexcept;
		friend Vector<3, ValueType> CIN_CALL operator-(const Vector<3, ValueType>& lhs, const ValueType scalar) noexcept;
		friend Vector<3, ValueType> CIN_CALL operator*(const Vector<3, ValueType>& lhs, const ValueType scalar) noexcept;
		friend Vector<3, ValueType> CIN_CALL operator/(const Vector<3, ValueType>& lhs, const ValueType scalar) noexcept;
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
			Vector2Swizzle<ValueType, Vector<2, ValueType>, 1, 0> yx;
			
			Vector2Swizzle<ValueType, Vector<2, ValueType>, 1, 2> yz;
			Vector2Swizzle<ValueType, Vector<2, ValueType>, 2, 1> zy;

			Vector2Swizzle<ValueType, Vector<2, ValueType>, 2, 0> zx;
			Vector2Swizzle<ValueType, Vector<2, ValueType>, 0, 2> xz;

			/* 3-Element swizzle */
			Vector3Swizzle<ValueType, Vector<3, ValueType>, 0, 1, 2> xyz;
			Vector3Swizzle<ValueType, Vector<3, ValueType>, 2, 1, 0> zyx;
		};
	};

	typedef Vector<3, float> Vector3;
}