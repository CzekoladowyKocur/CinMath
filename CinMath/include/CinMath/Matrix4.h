#pragma once

namespace CinMath {
	template<typename ValueType>
	class Matrix<4, 4, ValueType> final
	{
	public:
		using UnderlyingType = ValueType;
	public:
		consteval explicit Matrix<4, 4, ValueType>() noexcept
			:
			m11(static_cast<ValueType>(0)),
			m12(static_cast<ValueType>(0)),
			m13(static_cast<ValueType>(0)),
			m14(static_cast<ValueType>(0)),
			m21(static_cast<ValueType>(0)),
			m22(static_cast<ValueType>(0)),
			m23(static_cast<ValueType>(0)),
			m24(static_cast<ValueType>(0)),
			m31(static_cast<ValueType>(0)),
			m32(static_cast<ValueType>(0)),
			m33(static_cast<ValueType>(0)),
			m34(static_cast<ValueType>(0)),
			m41(static_cast<ValueType>(0)),
			m42(static_cast<ValueType>(0)),
			m43(static_cast<ValueType>(0)),
			m44(static_cast<ValueType>(0))
		{}

		consteval explicit Matrix<4, 4, ValueType>(const ValueType value, [[maybe_unused]] ConstevalConstructorProxy&&) noexcept
			:
			m11(value),
			m12(static_cast<ValueType>(0)),
			m13(static_cast<ValueType>(0)),
			m14(static_cast<ValueType>(0)),
			m21(static_cast<ValueType>(0)),
			m22(value),
			m23(static_cast<ValueType>(0)),
			m24(static_cast<ValueType>(0)),
			m31(static_cast<ValueType>(0)),
			m32(static_cast<ValueType>(0)),
			m33(value),
			m34(static_cast<ValueType>(0)),
			m41(static_cast<ValueType>(0)),
			m42(static_cast<ValueType>(0)),
			m43(static_cast<ValueType>(0)),
			m44(value)
		{}

		explicit Matrix<4, 4, ValueType>(const ValueType value) noexcept
			:
			m11(value),
			m12(static_cast<ValueType>(0)),
			m13(static_cast<ValueType>(0)),
			m14(static_cast<ValueType>(0)),
			m21(static_cast<ValueType>(0)),
			m22(value),
			m23(static_cast<ValueType>(0)),
			m24(static_cast<ValueType>(0)),
			m31(static_cast<ValueType>(0)),
			m32(static_cast<ValueType>(0)),
			m33(value),
			m34(static_cast<ValueType>(0)),
			m41(static_cast<ValueType>(0)),
			m42(static_cast<ValueType>(0)),
			m43(static_cast<ValueType>(0)),
			m44(value)
		{}

		explicit Matrix<4, 4, ValueType>(
			const ValueType value1,
			const ValueType value2,
			const ValueType value3,
			const ValueType value4,
			const ValueType value5,
			const ValueType value6,
			const ValueType value7,
			const ValueType value8,
			const ValueType value9,
			const ValueType value10,
			const ValueType value11,
			const ValueType value12,
			const ValueType value13,
			const ValueType value14,
			const ValueType value15,
			const ValueType value16) noexcept
			:
			m11(value1),
			m12(value2),
			m13(value3),
			m14(value4),
			m21(value5),
			m22(value6),
			m23(value7),
			m24(value8),
			m31(value9),
			m32(value10),
			m33(value11),
			m34(value12),
			m41(value13),
			m42(value14),
			m43(value15),
			m44(value16)
		{}

		explicit Matrix<4, 4, ValueType>(std::array<ValueType, 4 * 4>&& values) noexcept
			:
			m11(values[0]),
			m12(values[1]),
			m13(values[2]),
			m14(values[3]),
			m21(values[4]),
			m22(values[5]),
			m23(values[6]),
			m24(values[7]),
			m31(values[8]),
			m32(values[9]),
			m33(values[10]),
			m34(values[11]),
			m41(values[12]),
			m42(values[13]),
			m43(values[14]),
			m44(values[15])
		{}

		constexpr ~Matrix<4, 4, ValueType>() noexcept = default;

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

		[[nodiscard]] friend Matrix<4, 4, ValueType> CIN_CALL operator+(const Matrix<4, 4, ValueType>& vector) noexcept;
		[[nodiscard]] friend Matrix<4, 4, ValueType> CIN_CALL operator-(const Matrix<4, 4, ValueType>& vector) noexcept;

		friend void CIN_CALL operator+=(Matrix<4, 4, ValueType>& lhs, const Vector<4, ValueType>& rhs) noexcept;
		friend void CIN_CALL operator-=(Matrix<4, 4, ValueType>& lhs, const Vector<4, ValueType>& rhs) noexcept;
		friend void CIN_CALL operator*=(Matrix<4, 4, ValueType>& lhs, const Vector<4, ValueType>& rhs) noexcept;

		friend void CIN_CALL operator+=(Matrix<4, 4, ValueType>& lhs, const ValueType scalar) noexcept;
		friend void CIN_CALL operator-=(Matrix<4, 4, ValueType>& lhs, const ValueType scalar) noexcept;
		friend void CIN_CALL operator*=(Matrix<4, 4, ValueType>& lhs, const ValueType scalar) noexcept;
		friend void CIN_CALL operator/=(Matrix<4, 4, ValueType>& lhs, const ValueType scalar) noexcept;

		[[nodiscard]] friend Matrix<4, 4, ValueType> CIN_CALL operator+(const Matrix<4, 4, ValueType>& lhs, const Matrix<4, 4, ValueType>& rhs) noexcept;
		[[nodiscard]] friend Matrix<4, 4, ValueType> CIN_CALL operator-(const Matrix<4, 4, ValueType>& lhs, const Matrix<4, 4, ValueType>& rhs) noexcept;
		[[nodiscard]] friend Matrix<4, 4, ValueType> CIN_CALL operator*(const Matrix<4, 4, ValueType>& lhs, const Matrix<4, 4, ValueType>& rhs) noexcept;

		[[nodiscard]] friend Matrix<4, 4, ValueType> CIN_CALL operator+(const Matrix<4, 4, ValueType>& lhs, const ValueType scalar) noexcept;
		[[nodiscard]] friend Matrix<4, 4, ValueType> CIN_CALL operator-(const Matrix<4, 4, ValueType>& lhs, const ValueType scalar) noexcept;
		[[nodiscard]] friend Matrix<4, 4, ValueType> CIN_CALL operator*(const Matrix<4, 4, ValueType>& lhs, const ValueType scalar) noexcept;
		[[nodiscard]] friend Matrix<4, 4, ValueType> CIN_CALL operator/(const Matrix<4, 4, ValueType>& lhs, const ValueType scalar) noexcept;

		[[nodiscard]] friend Vector<4, ValueType> CIN_CALL operator*(const Matrix<4, 4, ValueType>& lhs, const Vector<4, ValueType>& rhs) noexcept;
	public:
		union
		{
			struct
			{
				MatrixStorage<4, 4, ValueType>::Container data;
			};

			struct
			{
				ValueType raw[4 * 4];
			};

			struct
			{
				ValueType m11, m12, m13, m14;
				ValueType m21, m22, m23, m24;
				ValueType m31, m32, m33, m34;
				ValueType m41, m42, m43, m44;
			};
		};

		[[nodiscard]] consteval static Matrix<4, 4, ValueType> Identity() noexcept
		{
			constexpr Matrix<4, 4, ValueType> result(static_cast<ValueType>(1), ConstevalConstructorProxy{});
			return result;
		}
	};

	typedef Matrix<4, 4, float>		Matrix4x4, Matrix4;
}