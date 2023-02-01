#pragma once

namespace CinMath {
	template<typename ValueType>
	class Matrix<2, 2, ValueType> final
	{
	public:
		using UnderlyingType = ValueType;
	public:
		consteval explicit Matrix<2, 2, ValueType>() noexcept
			:
			m11(static_cast<ValueType>(0)),
			m12(static_cast<ValueType>(0)),
			m21(static_cast<ValueType>(0)),
			m22(static_cast<ValueType>(0))
		{}

		consteval explicit Matrix<2, 2, ValueType>(const ValueType value, [[maybe_unused]] ConstevalConstructorProxy&&) noexcept
			:
			m11(value),
			m12(static_cast<ValueType>(0)),
			m21(static_cast<ValueType>(0)),
			m22(value)
		{}

		constexpr explicit Matrix<2, 2, ValueType>(const ValueType value) noexcept
			:
			m11(value),
			m12(static_cast<ValueType>(0)),
			m21(static_cast<ValueType>(0)),
			m22(value)
		{}

		constexpr explicit Matrix<2, 2, ValueType>(
			const ValueType value1,
			const ValueType value2,
			const ValueType value3,
			const ValueType value4) noexcept
			:
			m11(value1),
			m12(value2),
			m21(value3),
			m22(value4)
		{}

		constexpr explicit Matrix<2, 2, ValueType>(std::array<ValueType, 2 * 2>&& values) noexcept
			:
			m11(values[0]),
			m12(values[1]),
			m21(values[2]),
			m22(values[3])
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

		constexpr bool operator==(const Matrix<2, 2, ValueType>& other) const noexcept
		{
			return
				m11 == other.m11 &&
				m12 == other.m12 &&
				m21 == other.m21 &&
				m22 == other.m22;
		}

		constexpr bool operator!=(const Matrix<2, 2, ValueType>& other) const noexcept
		{
			return
				m11 != other.m11 ||
				m12 != other.m12 ||
				m21 != other.m21 ||
				m22 != other.m22;
		}

		constexpr operator Matrix<2, 2, float>() const noexcept
		{
			return Matrix<2, 2, float>
			{
				static_cast<float>(m11),
				static_cast<float>(m12),
				static_cast<float>(m21),
				static_cast<float>(m22)
			};
		}

		constexpr operator Matrix<2, 2, double>() const noexcept
		{
			return Matrix<2, 2, double>
			{
				static_cast<double>(m11),
				static_cast<double>(m12),
				static_cast<double>(m21),
				static_cast<double>(m22)
			};
		}

		[[nodiscard]] friend Matrix<2, 2, ValueType> CIN_MATH_CALL operator+(const Matrix<2, 2, ValueType>& vector) noexcept;
		[[nodiscard]] friend Matrix<2, 2, ValueType> CIN_MATH_CALL operator-(const Matrix<2, 2, ValueType>& vector) noexcept;

		friend void CIN_MATH_CALL operator+=(Matrix<2, 2, ValueType>& lhs, const Vector<4, ValueType>& rhs) noexcept;
		friend void CIN_MATH_CALL operator-=(Matrix<2, 2, ValueType>& lhs, const Vector<4, ValueType>& rhs) noexcept;
		friend void CIN_MATH_CALL operator*=(Matrix<2, 2, ValueType>& lhs, const Vector<4, ValueType>& rhs) noexcept;

		friend void CIN_MATH_CALL operator+=(Matrix<2, 2, ValueType>& lhs, const ValueType scalar) noexcept;
		friend void CIN_MATH_CALL operator-=(Matrix<2, 2, ValueType>& lhs, const ValueType scalar) noexcept;
		friend void CIN_MATH_CALL operator*=(Matrix<2, 2, ValueType>& lhs, const ValueType scalar) noexcept;
		friend void CIN_MATH_CALL operator/=(Matrix<2, 2, ValueType>& lhs, const ValueType scalar) noexcept;

		[[nodiscard]] friend Matrix<2, 2, ValueType> CIN_MATH_CALL operator+(const Matrix<2, 2, ValueType>& lhs, const Matrix<2, 2, ValueType>& rhs) noexcept;
		[[nodiscard]] friend Matrix<2, 2, ValueType> CIN_MATH_CALL operator-(const Matrix<2, 2, ValueType>& lhs, const Matrix<2, 2, ValueType>& rhs) noexcept;
		[[nodiscard]] friend Matrix<2, 2, ValueType> CIN_MATH_CALL operator*(const Matrix<2, 2, ValueType>& lhs, const Matrix<2, 2, ValueType>& rhs) noexcept;

		[[nodiscard]] friend Matrix<2, 2, ValueType> CIN_MATH_CALL operator+(const Matrix<2, 2, ValueType>& lhs, const ValueType scalar) noexcept;
		[[nodiscard]] friend Matrix<2, 2, ValueType> CIN_MATH_CALL operator-(const Matrix<2, 2, ValueType>& lhs, const ValueType scalar) noexcept;
		[[nodiscard]] friend Matrix<2, 2, ValueType> CIN_MATH_CALL operator*(const Matrix<2, 2, ValueType>& lhs, const ValueType scalar) noexcept;
		[[nodiscard]] friend Matrix<2, 2, ValueType> CIN_MATH_CALL operator/(const Matrix<2, 2, ValueType>& lhs, const ValueType scalar) noexcept;
	public:
		union
		{
			struct
			{
				MatrixStorage<2, 2, ValueType>::Container data;
			};

			struct
			{
				ValueType raw[2 * 2];
			};

			struct
			{
				ValueType m11, m12;
				ValueType m21, m22;
			};
		};

		[[nodiscard]] consteval static Matrix<2, 2, ValueType> Identity() noexcept
		{
			constexpr Matrix<2, 2, ValueType> result(static_cast<ValueType>(1), ConstevalConstructorProxy{});
			return result;
		}
	};

	typedef Matrix<2, 2, float>		Matrix2x2, Matrix2;
	typedef Matrix<2, 2, double>	DMatrix2x2, DMatrix2;
}