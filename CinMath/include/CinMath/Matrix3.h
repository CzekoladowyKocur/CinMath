#pragma once

namespace CinMath {
	template<typename ValueType>
	class Matrix<3, 3, ValueType> final
	{
	public:
		using UnderlyingType = ValueType;
	public:
		explicit Matrix<3, 3, ValueType>() noexcept
		{
			raw[0] = static_cast<ValueType>(0);
			raw[1] = static_cast<ValueType>(0);
			raw[2] = static_cast<ValueType>(0);
			raw[3] = static_cast<ValueType>(0);
			raw[4] = static_cast<ValueType>(0);
			raw[5] = static_cast<ValueType>(0);
			raw[6] = static_cast<ValueType>(0);
			raw[7] = static_cast<ValueType>(0);
			raw[8] = static_cast<ValueType>(0);
		}

		explicit Matrix<3, 3, ValueType>(const ValueType value) noexcept
		{
			raw[0] = value;
			raw[1] = static_cast<ValueType>(0);
			raw[2] = static_cast<ValueType>(0);
			raw[3] = static_cast<ValueType>(0);
			raw[4] = value;
			raw[5] = static_cast<ValueType>(0);
			raw[6] = static_cast<ValueType>(0);
			raw[7] = static_cast<ValueType>(0);
			raw[8] = value;
		}

		explicit Matrix<3, 3, ValueType>(
			const ValueType value1,
			const ValueType value2,
			const ValueType value3,
			const ValueType value4,
			const ValueType value5,
			const ValueType value6,
			const ValueType value7,
			const ValueType value8,
			const ValueType value9) noexcept
		{
			raw[0] = value1;
			raw[1] = value2;
			raw[2] = value3;
			raw[3] = value4;
			raw[4] = value5;
			raw[5] = value6;
			raw[6] = value7;
			raw[7] = value8;
			raw[8] = value9;
		}

		explicit Matrix<3, 3, ValueType>(std::array<ValueType, 3 * 3>&& values) noexcept
		{
			raw[0] = values[0];
			raw[1] = values[1];
			raw[2] = values[2];
			raw[3] = values[3];
			raw[4] = values[4];
			raw[5] = values[5];
			raw[6] = values[6];
			raw[7] = values[7];
			raw[8] = values[8];
		}

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

		friend Matrix<3, 3, ValueType> CIN_CALL operator+(const Matrix<3, 3, ValueType>& vector) noexcept;
		friend Matrix<3, 3, ValueType> CIN_CALL operator-(const Matrix<3, 3, ValueType>& vector) noexcept;

		friend void CIN_CALL operator+=(Matrix<3, 3, ValueType>& lhs, const Vector<4, ValueType>& rhs) noexcept;
		friend void CIN_CALL operator-=(Matrix<3, 3, ValueType>& lhs, const Vector<4, ValueType>& rhs) noexcept;
		friend void CIN_CALL operator*=(Matrix<3, 3, ValueType>& lhs, const Vector<4, ValueType>& rhs) noexcept;

		friend void CIN_CALL operator+=(Matrix<3, 3, ValueType>& lhs, const ValueType scalar) noexcept;
		friend void CIN_CALL operator-=(Matrix<3, 3, ValueType>& lhs, const ValueType scalar) noexcept;
		friend void CIN_CALL operator*=(Matrix<3, 3, ValueType>& lhs, const ValueType scalar) noexcept;
		friend void CIN_CALL operator/=(Matrix<3, 3, ValueType>& lhs, const ValueType scalar) noexcept;

		friend Matrix<3, 3, ValueType> CIN_CALL operator+(const Matrix<3, 3, ValueType>& lhs, const Matrix<3, 3, ValueType>& rhs) noexcept;
		friend Matrix<3, 3, ValueType> CIN_CALL operator-(const Matrix<3, 3, ValueType>& lhs, const Matrix<3, 3, ValueType>& rhs) noexcept;
		friend Matrix<3, 3, ValueType> CIN_CALL operator*(const Matrix<3, 3, ValueType>& lhs, const Matrix<3, 3, ValueType>& rhs) noexcept;

		friend Matrix<3, 3, ValueType> CIN_CALL operator+(const Matrix<3, 3, ValueType>& lhs, const ValueType scalar) noexcept;
		friend Matrix<3, 3, ValueType> CIN_CALL operator-(const Matrix<3, 3, ValueType>& lhs, const ValueType scalar) noexcept;
		friend Matrix<3, 3, ValueType> CIN_CALL operator*(const Matrix<3, 3, ValueType>& lhs, const ValueType scalar) noexcept;
		friend Matrix<3, 3, ValueType> CIN_CALL operator/(const Matrix<3, 3, ValueType>& lhs, const ValueType scalar) noexcept;
	public:
		union
		{
			struct
			{
				MatrixStorage<3, 3, ValueType>::Container data;
			};

			struct
			{
				ValueType raw[3 * 3];
			};
		};
	};

	typedef Matrix<3, 3, float>		Matrix3x3, Matrix3;
}