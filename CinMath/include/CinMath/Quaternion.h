namespace CinMath {
	template<typename ValueType>
	class TQuaternion final
	{
	public:
		constexpr explicit TQuaternion() noexcept
			:
			a(static_cast<ValueType>(0)),
			b(static_cast<ValueType>(0)),
			c(static_cast<ValueType>(0)),
			d(static_cast<ValueType>(0))
		{}

		constexpr explicit TQuaternion(
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

		constexpr explicit TQuaternion(
			const ValueType scalar,
			const Vector<3, ValueType>& vector) noexcept
			:
			scalar(scalar),
			vector(vector)
		{}

		constexpr CIN_MATH_INLINE operator ValueType* () noexcept
		{
			return raw;
		}
	
		constexpr CIN_MATH_INLINE operator const ValueType* () const noexcept
		{
			return raw;
		}

		constexpr CIN_MATH_INLINE ValueType& operator[](const Length_t index) noexcept
		{
			return raw[index];
		}

		constexpr CIN_MATH_INLINE const ValueType operator[](const Length_t index) const noexcept
		{
			return raw[index];
		}

		constexpr CIN_MATH_INLINE operator Vector<4, ValueType>() const noexcept
		{
			return Vector<4, ValueType>
			{
				raw[0], raw[1], raw[2], raw[3]
			};
		}

		constexpr bool operator==(const TQuaternion<ValueType>& other) const noexcept
		{
			return 
				raw[0] == other.raw[0] &&
				raw[1] == other.raw[1] &&
				raw[2] == other.raw[2] &&
				raw[3] == other.raw[3];
		}

		constexpr bool operator!=(const TQuaternion<ValueType>& other) const noexcept
		{
			return 
				raw[0] != other.raw[0] ||
				raw[1] != other.raw[1] ||
				raw[2] != other.raw[2] ||
				raw[3] != other.raw[3];
		}

		template<typename T> friend TQuaternion<T> operator+(const TQuaternion<T>& quaternion) noexcept;
		template<typename T> friend TQuaternion<T> operator-(const TQuaternion<T>& quaternion) noexcept;

		template<typename T> friend TQuaternion<T> operator+(const TQuaternion<T>& lhs, const TQuaternion<T>& rhs) noexcept;
		template<typename T> friend TQuaternion<T> operator-(const TQuaternion<T>& lhs, const TQuaternion<T>& rhs) noexcept;
		template<typename T> friend TQuaternion<T> operator*(const TQuaternion<T>& lhs, const TQuaternion<T>& rhs) noexcept;
		template<typename T> friend TQuaternion<T> operator/(const TQuaternion<T>& lhs, const TQuaternion<T>& rhs) noexcept;

		template<typename T> friend TQuaternion<T> operator*(const TQuaternion<T>& quaternion, const T scalar) noexcept;
		template<typename T> friend TQuaternion<T> operator/(const TQuaternion<T>& quaternion, const T scalar) noexcept;
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

	typedef TQuaternion<float>	Quaternion;
	typedef TQuaternion<double>	DQuaternion;
}