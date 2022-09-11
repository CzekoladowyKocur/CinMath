namespace CinMath {
	template<typename ValueType>
	class QuaternionBase final
	{
	public:
		consteval explicit QuaternionBase() noexcept
			:
			a(static_cast<ValueType>(0)),
			b(static_cast<ValueType>(0)),
			c(static_cast<ValueType>(0)),
			d(static_cast<ValueType>(0))
		{}

		explicit QuaternionBase(
			const ValueType a,
			const ValueType b,
			const ValueType c,
			const ValueType d) noexcept
			:
			a(a),
			b(b),
			c(c),
			d(d)
		{}

		explicit QuaternionBase(
			const ValueType scalar,
			const Vector<3, ValueType>& vector) noexcept
			:
			scalar(scalar),
			vector(vector)
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

		CIN_MATH_INLINE constexpr operator Vector<4, ValueType>() const noexcept
		{
			return Vector<4, ValueType>
			{
				raw[0], raw[1], raw[2], raw[3],
			};
		}

		friend QuaternionBase<ValueType> CIN_CALL operator+(const QuaternionBase<ValueType>& quaternion) noexcept;
		friend QuaternionBase<ValueType> CIN_CALL operator-(const QuaternionBase<ValueType>& quaternion) noexcept;

		friend QuaternionBase<ValueType> CIN_CALL operator+(const QuaternionBase<ValueType>& lhs, const QuaternionBase<ValueType>& rhs) noexcept;
		friend QuaternionBase<ValueType> CIN_CALL operator-(const QuaternionBase<ValueType>& lhs, const QuaternionBase<ValueType>& rhs) noexcept;
		friend QuaternionBase<ValueType> CIN_CALL operator*(const QuaternionBase<ValueType>& lhs, const QuaternionBase<ValueType>& rhs) noexcept;
		friend QuaternionBase<ValueType> CIN_CALL operator/(const QuaternionBase<ValueType>& lhs, const QuaternionBase<ValueType>& rhs) noexcept;

		friend QuaternionBase<ValueType> CIN_CALL operator*(const QuaternionBase<ValueType>& quaternion, const ValueType scalar) noexcept;
		friend QuaternionBase<ValueType> CIN_CALL operator/(const QuaternionBase<ValueType>& quaternion, const ValueType scalar) noexcept;
	public:
		union
		{
			struct
			{
				/* Quaternion storage is the same as vector4 storage */
				Storage<4, ValueType>::Container data;
			};

			struct
			{
				ValueType raw[4];
			};

			struct
			{
				ValueType a;
				ValueType b;
				ValueType c;
				ValueType d;
			};

			struct
			{
				ValueType scalar;
				Vector<3, ValueType> vector;
			};
		};
	};

	typedef QuaternionBase<float>	Quaternion;
	typedef QuaternionBase<double>	DQuaternion;
}