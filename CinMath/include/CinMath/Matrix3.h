#pragma once

namespace CinMath {
	template<typename ValueType>
	class Matrix<3, 3, ValueType> final
	{
	public:
		using UnderlyingType = ValueType;
	public:
		constexpr explicit Matrix<3, 3, ValueType>() noexcept
			:
			m11(static_cast<ValueType>(0)),
			m12(static_cast<ValueType>(0)),
			m13(static_cast<ValueType>(0)),
			m21(static_cast<ValueType>(0)),
			m22(static_cast<ValueType>(0)),
			m23(static_cast<ValueType>(0)),
			m31(static_cast<ValueType>(0)),
			m32(static_cast<ValueType>(0)),
			m33(static_cast<ValueType>(0))
		{}

		consteval explicit Matrix<3, 3, ValueType>(const ValueType value, [[maybe_unused]] ConstevalConstructorProxy&&) noexcept
			:
			m11(value),
			m12(static_cast<ValueType>(0)),
			m13(static_cast<ValueType>(0)),
			m21(static_cast<ValueType>(0)),
			m22(value),
			m23(static_cast<ValueType>(0)),
			m31(static_cast<ValueType>(0)),
			m32(static_cast<ValueType>(0)),
			m33(value)
		{}

		constexpr explicit Matrix<3, 3, ValueType>(const ValueType value) noexcept
			:
			m11(value),
			m12(static_cast<ValueType>(0)),
			m13(static_cast<ValueType>(0)),
			m21(static_cast<ValueType>(0)),
			m22(value),
			m23(static_cast<ValueType>(0)),
			m31(static_cast<ValueType>(0)),
			m32(static_cast<ValueType>(0)),
			m33(value)
		{}

		constexpr explicit Matrix<3, 3, ValueType>(
			const ValueType value1,
			const ValueType value2,
			const ValueType value3,
			const ValueType value4,
			const ValueType value5,
			const ValueType value6,
			const ValueType value7,
			const ValueType value8,
			const ValueType value9) noexcept
			:
			m11(value1),
			m12(value2),
			m13(value3),
			m21(value4),
			m22(value5),
			m23(value6),
			m31(value7),
			m32(value8),
			m33(value9)
		{}

		constexpr explicit Matrix<3, 3, ValueType>(std::array<ValueType, 3 * 3>&& values) noexcept
			:
			m11(values[0]),
			m12(values[1]),
			m13(values[2]),
			m21(values[3]),
			m22(values[4]),
			m23(values[5]),
			m31(values[6]),
			m32(values[7]),
			m33(values[8])
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

		constexpr bool operator==(const Matrix<3, 3, ValueType>& other) const noexcept
		{
			return
				m11 == other.m11 &&
				m12 == other.m12 &&
				m13 == other.m13 &&
				m21 == other.m21 &&
				m22 == other.m22 &&
				m23 == other.m23 &&
				m31 == other.m31 &&
				m32 == other.m32 &&
				m33 == other.m33;
		}

		constexpr bool operator!=(const Matrix<3, 3, ValueType>& other) const noexcept
		{
			return
				m11 != other.m11 ||
				m12 != other.m12 ||
				m13 != other.m13 ||
				m21 != other.m21 ||
				m22 != other.m22 ||
				m23 != other.m23 ||
				m31 != other.m31 ||
				m32 != other.m32 ||
				m33 != other.m33;
		}

		constexpr operator Matrix<3, 3, float>() const noexcept
		{
			return Matrix<3, 3, float>
			{
				static_cast<float>(m11), 
				static_cast<float>(m12), 
				static_cast<float>(m13), 
				static_cast<float>(m21), 
				static_cast<float>(m22), 
				static_cast<float>(m23), 
				static_cast<float>(m31), 
				static_cast<float>(m32), 
				static_cast<float>(m33) 
			};
		}

		constexpr operator Matrix<3, 3, double>() const noexcept
		{
			return Matrix<3, 3, double>
			{
				static_cast<double>(m11), 
				static_cast<double>(m12), 
				static_cast<double>(m13), 
				static_cast<double>(m21), 
				static_cast<double>(m22), 
				static_cast<double>(m23), 
				static_cast<double>(m31), 
				static_cast<double>(m32), 
				static_cast<double>(m33) 
			};
		}

		template<typename T> friend Matrix<3, 3, T> operator+(const Matrix<3, 3, T>& vector) noexcept;
		template<typename T> friend Matrix<3, 3, T> operator-(const Matrix<3, 3, T>& vector) noexcept;

		template<typename T> friend void operator+=(Matrix<3, 3, T>& lhs, const Vector<4, T>& rhs) noexcept;
		template<typename T> friend void operator-=(Matrix<3, 3, T>& lhs, const Vector<4, T>& rhs) noexcept;
		template<typename T> friend void operator*=(Matrix<3, 3, T>& lhs, const Vector<4, T>& rhs) noexcept;

		template<typename T> friend void operator+=(Matrix<3, 3, T>& lhs, const T scalar) noexcept;
		template<typename T> friend void operator-=(Matrix<3, 3, T>& lhs, const T scalar) noexcept;
		template<typename T> friend void operator*=(Matrix<3, 3, T>& lhs, const T scalar) noexcept;
		template<typename T> friend void operator/=(Matrix<3, 3, T>& lhs, const T scalar) noexcept;

		template<typename T> friend Matrix<3, 3, T> operator+(const Matrix<3, 3, T>& lhs, const Matrix<3, 3, T>& rhs) noexcept;
		template<typename T> friend Matrix<3, 3, T> operator-(const Matrix<3, 3, T>& lhs, const Matrix<3, 3, T>& rhs) noexcept;
		template<typename T> friend Matrix<3, 3, T> operator*(const Matrix<3, 3, T>& lhs, const Matrix<3, 3, T>& rhs) noexcept;

		template<typename T> friend Matrix<3, 3, T> operator+(const Matrix<3, 3, T>& lhs, const T scalar) noexcept;
		template<typename T> friend Matrix<3, 3, T> operator-(const Matrix<3, 3, T>& lhs, const T scalar) noexcept;
		template<typename T> friend Matrix<3, 3, T> operator*(const Matrix<3, 3, T>& lhs, const T scalar) noexcept;
		template<typename T> friend Matrix<3, 3, T> operator/(const Matrix<3, 3, T>& lhs, const T scalar) noexcept;
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

			struct
			{
				ValueType m11, m12, m13;
				ValueType m21, m22, m23;
				ValueType m31, m32, m33;
			};
		};

		[[nodiscard]] consteval static Matrix<3, 3, ValueType> Identity() noexcept
		{
			constexpr Matrix<3, 3, ValueType> result(static_cast<ValueType>(1), ConstevalConstructorProxy{});
			return result;
		}
	};

	typedef Matrix<3, 3, float>		Matrix3x3, Matrix3;
	typedef Matrix<3, 3, double>	DMatrix3x3, DMatrix3;
}