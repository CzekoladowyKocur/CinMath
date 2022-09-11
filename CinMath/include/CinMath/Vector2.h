#pragma once

namespace CinMath {
	template<typename ValueType>
	class Vector<2, ValueType> final
	{
	public:
		using UnderlyingType = ValueType;
	public:
		consteval explicit Vector<2, ValueType>() noexcept
			:
			x(static_cast<ValueType>(0)),
			y(static_cast<ValueType>(0))
		{}

		explicit Vector<2, ValueType>(
			const ValueType value) noexcept
			:
			x(value),
			y(value)
		{}

		explicit Vector<2, ValueType>(
			const ValueType x,
			const ValueType y) noexcept
			:
			x(x),
			y(y)
		{}

		constexpr ~Vector<2, ValueType>() noexcept = default;

		constexpr operator ValueType* () noexcept
		{
			return raw;
		}

		constexpr  operator const ValueType* () const noexcept
		{
			return raw;
		}

		constexpr  ValueType& operator[](const Length_t index) noexcept
		{
			return raw[index];
		}

		constexpr  const ValueType operator[](const Length_t index) const noexcept
		{
			return raw[index];
		}

		[[nodiscard]] friend Vector<2, ValueType> CIN_CALL operator+(const Vector<2, ValueType>& vector) noexcept;
		[[nodiscard]] friend Vector<2, ValueType> CIN_CALL operator-(const Vector<2, ValueType>& vector) noexcept;

		friend void CIN_CALL operator+=(Vector<2, ValueType>& lhs, const Vector<4, ValueType>& rhs) noexcept;
		friend void CIN_CALL operator-=(Vector<2, ValueType>& lhs, const Vector<4, ValueType>& rhs) noexcept;
		friend void CIN_CALL operator*=(Vector<2, ValueType>& lhs, const Vector<4, ValueType>& rhs) noexcept;
		friend void CIN_CALL operator/=(Vector<2, ValueType>& lhs, const Vector<4, ValueType>& rhs) noexcept;

		friend void CIN_CALL operator+=(Vector<2, ValueType>& lhs, const ValueType scalar) noexcept;
		friend void CIN_CALL operator-=(Vector<2, ValueType>& lhs, const ValueType scalar) noexcept;
		friend void CIN_CALL operator*=(Vector<2, ValueType>& lhs, const ValueType scalar) noexcept;
		friend void CIN_CALL operator/=(Vector<2, ValueType>& lhs, const ValueType scalar) noexcept;

		[[nodiscard]] friend Vector<2, ValueType> CIN_CALL operator+(const Vector<2, ValueType>& lhs, const Vector<2, ValueType>& rhs) noexcept;
		[[nodiscard]] friend Vector<2, ValueType> CIN_CALL operator-(const Vector<2, ValueType>& lhs, const Vector<2, ValueType>& rhs) noexcept;
		[[nodiscard]] friend Vector<2, ValueType> CIN_CALL operator*(const Vector<2, ValueType>& lhs, const Vector<2, ValueType>& rhs) noexcept;
		[[nodiscard]] friend Vector<2, ValueType> CIN_CALL operator/(const Vector<2, ValueType>& lhs, const Vector<2, ValueType>& rhs) noexcept;

		[[nodiscard]] friend Vector<2, ValueType> CIN_CALL operator+(const Vector<2, ValueType>& lhs, const ValueType scalar) noexcept;
		[[nodiscard]] friend Vector<2, ValueType> CIN_CALL operator-(const Vector<2, ValueType>& lhs, const ValueType scalar) noexcept;
		[[nodiscard]] friend Vector<2, ValueType> CIN_CALL operator*(const Vector<2, ValueType>& lhs, const ValueType scalar) noexcept;
		[[nodiscard]] friend Vector<2, ValueType> CIN_CALL operator/(const Vector<2, ValueType>& lhs, const ValueType scalar) noexcept;
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
			Vector2Swizzle<ValueType, Vector<2, ValueType>, 1, 0> yx;
		};
	};

	typedef Vector<2, float> Vector2;
}