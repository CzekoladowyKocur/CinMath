#pragma once

namespace CinMath {
	template<typename ValueType>
	class Matrix<4, 4, ValueType> final
	{
	public:
		using UnderlyingType = ValueType;
	public:
		explicit Matrix<4, 4, ValueType>() noexcept
		{
			raw[0] = static_cast<ValueType>(0);
			raw[1] = static_cast<ValueType>(0);
			raw[2] = static_cast<ValueType>(0);
			raw[3] = static_cast<ValueType>(0);
			raw[4] = static_cast<ValueType>(0);
			raw[5] = static_cast<ValueType>(0);
			raw[5] = static_cast<ValueType>(0);
			raw[6] = static_cast<ValueType>(0);
			raw[7] = static_cast<ValueType>(0);
			raw[8] = static_cast<ValueType>(0);
			raw[9] = static_cast<ValueType>(0);
			raw[10] = static_cast<ValueType>(0);
			raw[11] = static_cast<ValueType>(0);
			raw[12] = static_cast<ValueType>(0);
			raw[13] = static_cast<ValueType>(0);
			raw[14] = static_cast<ValueType>(0);
			raw[15] = static_cast<ValueType>(0);
		}

		explicit Matrix<4, 4, ValueType>(const ValueType value) noexcept
		{
			raw[0] = value;
			raw[1] = static_cast<ValueType>(0);
			raw[2] = static_cast<ValueType>(0);
			raw[3] = static_cast<ValueType>(0);
			raw[4] = static_cast<ValueType>(0);
			raw[5] = value;
			raw[6] = static_cast<ValueType>(0);
			raw[7] = static_cast<ValueType>(0);
			raw[8] = static_cast<ValueType>(0);
			raw[9] = static_cast<ValueType>(0);
			raw[10] = value;
			raw[11] = static_cast<ValueType>(0);
			raw[12] = static_cast<ValueType>(0);
			raw[13] = static_cast<ValueType>(0);
			raw[14] = static_cast<ValueType>(0);
			raw[15] = value;
		}

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
			raw[9] = value10;
			raw[10] = value11;
			raw[11] = value12;
			raw[12] = value13;
			raw[13] = value14;
			raw[14] = value15;
			raw[15] = value16;
		}

		explicit Matrix<4, 4, ValueType>(std::array<ValueType, 4 * 4>&& values) noexcept
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
			raw[9] = values[9];
			raw[10] = values[10];
			raw[11] = values[11];
			raw[12] = values[12];
			raw[13] = values[13];
			raw[14] = values[14];
			raw[15] = values[15];
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

		friend Matrix<4, 4, ValueType> CIN_CALL operator+(const Matrix<4, 4, ValueType>& vector) noexcept;
		friend Matrix<4, 4, ValueType> CIN_CALL operator-(const Matrix<4, 4, ValueType>& vector) noexcept;

		friend void CIN_CALL operator+=(Matrix<4, 4, ValueType>& lhs, const Vector<4, ValueType>& rhs) noexcept;
		friend void CIN_CALL operator-=(Matrix<4, 4, ValueType>& lhs, const Vector<4, ValueType>& rhs) noexcept;
		friend void CIN_CALL operator*=(Matrix<4, 4, ValueType>& lhs, const Vector<4, ValueType>& rhs) noexcept;

		friend void CIN_CALL operator+=(Matrix<4, 4, ValueType>& lhs, const ValueType scalar) noexcept;
		friend void CIN_CALL operator-=(Matrix<4, 4, ValueType>& lhs, const ValueType scalar) noexcept;
		friend void CIN_CALL operator*=(Matrix<4, 4, ValueType>& lhs, const ValueType scalar) noexcept;
		friend void CIN_CALL operator/=(Matrix<4, 4, ValueType>& lhs, const ValueType scalar) noexcept;

		friend Matrix<4, 4, ValueType> CIN_CALL operator+(const Matrix<4, 4, ValueType>& lhs, const Matrix<4, 4, ValueType>& rhs) noexcept;
		friend Matrix<4, 4, ValueType> CIN_CALL operator-(const Matrix<4, 4, ValueType>& lhs, const Matrix<4, 4, ValueType>& rhs) noexcept;
		friend Matrix<4, 4, ValueType> CIN_CALL operator*(const Matrix<4, 4, ValueType>& lhs, const Matrix<4, 4, ValueType>& rhs) noexcept;

		friend Matrix<4, 4, ValueType> CIN_CALL operator+(const Matrix<4, 4, ValueType>& lhs, const ValueType scalar) noexcept;
		friend Matrix<4, 4, ValueType> CIN_CALL operator-(const Matrix<4, 4, ValueType>& lhs, const ValueType scalar) noexcept;
		friend Matrix<4, 4, ValueType> CIN_CALL operator*(const Matrix<4, 4, ValueType>& lhs, const ValueType scalar) noexcept;
		friend Matrix<4, 4, ValueType> CIN_CALL operator/(const Matrix<4, 4, ValueType>& lhs, const ValueType scalar) noexcept;

		friend Vector<4, ValueType> CIN_CALL operator*(const Matrix<4, 4, ValueType>& lhs, const Vector<4, ValueType>& rhs) noexcept;
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
		};
	};

	typedef Matrix<4, 4, float>		Matrix4x4, Matrix4;
}