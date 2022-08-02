#pragma once

namespace CinMath {
	template<typename ValueType>
	class alignas(16) Vector<4, ValueType> final
	{
	public:
		using UnderlyingType = ValueType;
	public:
		explicit Vector<4, ValueType>() noexcept
			:
			x(static_cast<ValueType>(0)),
			y(static_cast<ValueType>(0)),
			z(static_cast<ValueType>(0)),
			w(static_cast<ValueType>(0))
		{}

		explicit Vector<4, ValueType>(
			const ValueType value) noexcept
			:
			x(value),
			y(value),
			z(value),
			w(value)
		{}

		explicit Vector<4, ValueType>(
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

		friend Vector<4, ValueType> CIN_CALL operator+(const Vector<4, ValueType>& vector) noexcept;
		friend Vector<4, ValueType> CIN_CALL operator-(const Vector<4, ValueType>& vector) noexcept;
		
		friend void CIN_CALL operator+=(Vector<4, ValueType>& lhs, const Vector<4, ValueType>& rhs) noexcept;
		friend void CIN_CALL operator-=(Vector<4, ValueType>& lhs, const Vector<4, ValueType>& rhs) noexcept;
		friend void CIN_CALL operator*=(Vector<4, ValueType>& lhs, const Vector<4, ValueType>& rhs) noexcept;
		friend void CIN_CALL operator/=(Vector<4, ValueType>& lhs, const Vector<4, ValueType>& rhs) noexcept;

		friend void CIN_CALL operator+=(Vector<4, ValueType>& lhs, const ValueType scalar) noexcept;
		friend void CIN_CALL operator-=(Vector<4, ValueType>& lhs, const ValueType scalar) noexcept;
		friend void CIN_CALL operator*=(Vector<4, ValueType>& lhs, const ValueType scalar) noexcept;
		friend void CIN_CALL operator/=(Vector<4, ValueType>& lhs, const ValueType scalar) noexcept;

		friend Vector<4, ValueType> CIN_CALL operator+(const Vector<4, ValueType>& lhs, const Vector<4, ValueType>& rhs) noexcept;
		friend Vector<4, ValueType> CIN_CALL operator-(const Vector<4, ValueType>& lhs, const Vector<4, ValueType>& rhs) noexcept;
		friend Vector<4, ValueType> CIN_CALL operator*(const Vector<4, ValueType>& lhs, const Vector<4, ValueType>& rhs) noexcept;
		friend Vector<4, ValueType> CIN_CALL operator/(const Vector<4, ValueType>& lhs, const Vector<4, ValueType>& rhs) noexcept;

		friend Vector<4, ValueType> CIN_CALL operator+(const Vector<4, ValueType>& lhs, const ValueType scalar) noexcept;
		friend Vector<4, ValueType> CIN_CALL operator-(const Vector<4, ValueType>& lhs, const ValueType scalar) noexcept;
		friend Vector<4, ValueType> CIN_CALL operator*(const Vector<4, ValueType>& lhs, const ValueType scalar) noexcept;
		friend Vector<4, ValueType> CIN_CALL operator/(const Vector<4, ValueType>& lhs, const ValueType scalar) noexcept;

		friend Vector<4, ValueType> CIN_CALL operator*(const Vector<4, ValueType>& lhs, const Matrix<4, 4, ValueType>& rhs) noexcept;
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
		};
	};

	typedef Vector<4, float> Vector4;
}