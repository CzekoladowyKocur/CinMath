#pragma once

namespace CinMath {
	inline namespace literals { struct RadiansProxy; }
	inline namespace literals { struct DegreesProxy; }

	template<typename ValueType>
	struct TRadians;

	template<typename ValueType>
	struct TDegrees;

	template<typename ValueType>
	class TAngle;

	template<typename ValueType>
	struct TRadians 
	{
		constexpr explicit TRadians() noexcept
			:
			Value(static_cast<ValueType>(0))
		{}

		constexpr TRadians(const TRadians&) noexcept = default;
		constexpr TRadians& operator=(const TRadians&) noexcept = default;
		
		/* Conversion */
		constexpr operator ValueType() const noexcept
		{
			return Value;
		}

		constexpr operator TAngle<ValueType>() const noexcept
		{
			return TAngle<ValueType>(*this);
		}

		constexpr TDegrees<ValueType> ToDegrees() const noexcept
		{
			return TDegrees<ValueType>(Value * (static_cast<ValueType>(180) / Constants::PI<ValueType>));
		}

		/* Comparison operators */
		constexpr bool operator==(const TRadians<ValueType> other) const noexcept
		{
			return Value == other.Value;
		}

		constexpr bool operator!=(const TRadians<ValueType> other) const noexcept
		{
			return Value != other.Value;
		}

		constexpr bool operator==(const TDegrees<ValueType> degrees) const noexcept
		{
			return Value == degrees.ToRadians();
		}

		constexpr bool operator!=(const TDegrees<ValueType> degrees) const noexcept
		{
			return Value != degrees.ToRadians();
		}

		constexpr bool operator==(const TAngle<ValueType> angle) const noexcept
		{
			return Value == angle.ToRadians();
		}

		constexpr bool operator!=(const TAngle<ValueType> angle) const noexcept
		{
			return Value != angle.ToRadians();
		}

		template<typename T> friend constexpr void operator+=(TRadians<T>& lhs, const TRadians<T>& rhs) noexcept;
		template<typename T> friend constexpr void operator-=(TRadians<T>& lhs, const TRadians<T>& rhs) noexcept;
		template<typename T> friend constexpr void operator*=(TRadians<T>& lhs, const TRadians<T>& rhs) noexcept;
		template<typename T> friend constexpr void operator/=(TRadians<T>& lhs, const TRadians<T>& rhs) noexcept;

		template<typename T> friend constexpr TRadians<T> operator+(const TRadians<T>& lhs, const TRadians<T>& rhs) noexcept;
		template<typename T> friend constexpr TRadians<T> operator-(const TRadians<T>& lhs, const TRadians<T>& rhs) noexcept;
		template<typename T> friend constexpr TRadians<T> operator*(const TRadians<T>& lhs, const TRadians<T>& rhs) noexcept;
		template<typename T> friend constexpr TRadians<T> operator/(const TRadians<T>& lhs, const TRadians<T>& rhs) noexcept;

		static constexpr TRadians FromValue(const ValueType value) noexcept
		{
			TRadians result;
			result.Value = value;
			return result;
		}
	public:
		ValueType Value;
		friend struct TDegrees<ValueType>;

		/* Used by proxy to construct from value */
		friend struct literals::RadiansProxy;
	public:
		constexpr explicit TRadians(const ValueType value) noexcept
			:
			Value(value)
		{}
	};

	typedef TRadians<float>		Radians;
	typedef TRadians<double>	DRadians;

	template<typename ValueType>
	struct TDegrees
	{
		constexpr explicit TDegrees() noexcept
			:
			Value(static_cast<ValueType>(0))
		{}

		constexpr TDegrees(const TDegrees&) noexcept = default;
		constexpr TDegrees& operator=(const TDegrees&) noexcept = default;
		
		constexpr TDegrees& operator=(const ValueType value) noexcept
		{
			Value = value;
			return *this;
		}

		/* Conversion */
		constexpr operator ValueType() const noexcept
		{
			return Value;
		}

		constexpr operator TAngle<ValueType>() const noexcept
		{
			return TAngle<ValueType>(*this);
		}
		
		constexpr TRadians<ValueType> ToRadians() const noexcept
		{
			return TRadians(Value * (Constants::PI<ValueType> / static_cast<ValueType>(180)));
		}

		/* Comparison operators */
		constexpr bool operator==(const TDegrees<ValueType> other) const noexcept
		{
			return Value == other;
		}

		constexpr bool operator!=(const TDegrees<ValueType> other) const noexcept
		{
			return Value != other;
		}

		constexpr bool operator==(const TRadians<ValueType> radians) const noexcept
		{
			return Value == radians.ToDegrees();
		}

		constexpr bool operator!=(const TRadians<ValueType> radians) const noexcept
		{
			return Value != radians.ToDegrees();
		}

		constexpr bool operator==(const TAngle<ValueType> angle) const noexcept
		{
			return Value == angle.ToDegrees();
		}

		constexpr bool operator!=(const TAngle<ValueType> angle) const noexcept
		{
			return Value != angle.ToDegrees();
		}

		template<typename T> friend constexpr void operator+=(TDegrees<T>& lhs, const TDegrees<T>& rhs) noexcept;
		template<typename T> friend constexpr void operator-=(TDegrees<T>& lhs, const TDegrees<T>& rhs) noexcept;
		template<typename T> friend constexpr void operator*=(TDegrees<T>& lhs, const TDegrees<T>& rhs) noexcept;
		template<typename T> friend constexpr void operator/=(TDegrees<T>& lhs, const TDegrees<T>& rhs) noexcept;
		
		template<typename T> friend constexpr TDegrees<T> operator+(const TDegrees<T>& lhs, const TDegrees<T>& rhs) noexcept;
		template<typename T> friend constexpr TDegrees<T> operator-(const TDegrees<T>& lhs, const TDegrees<T>& rhs) noexcept;
		template<typename T> friend constexpr TDegrees<T> operator*(const TDegrees<T>& lhs, const TDegrees<T>& rhs) noexcept;
		template<typename T> friend constexpr TDegrees<T> operator/(const TDegrees<T>& lhs, const TDegrees<T>& rhs) noexcept;

		static constexpr TDegrees FromValue(const ValueType value) noexcept
		{
			TDegrees result;
			result.Value = value;
			return result;
		}
	public:
		ValueType Value;
		friend struct TRadians<ValueType>;

		/* Used by proxy to construct from value */
		friend struct literals::DegreesProxy;
	private:
		constexpr explicit TDegrees(const ValueType value) noexcept
			:
			Value(value)
		{}
	};

	typedef TDegrees<float>		Degrees;
	typedef TDegrees<double>	DDegrees;

	template<typename ValueType>
	class TAngle final
	{
	public:
		using UnderlyingType = ValueType;
	public:
		consteval explicit TAngle() noexcept
			:
			Radians()
		{}

		constexpr explicit TAngle(const TRadians<ValueType> radians) noexcept
			:
			Radians(radians)
		{}

		constexpr explicit TAngle(const TDegrees<ValueType> degrees) noexcept
			:
			Radians(degrees.ToRadians())
		{}

		constexpr TAngle(const TAngle&) noexcept = default;

		/* Conversion */
		constexpr TRadians<ValueType> ToRadians() const noexcept
		{
			return Radians;
		}

		constexpr TDegrees<ValueType> ToDegrees() const noexcept
		{
			return Radians.ToDegrees();
		}

		/* Comparison operators */
		constexpr bool operator==(const TAngle<ValueType> other) const noexcept
		{
			return Radians == other.Radians;
		}

		constexpr bool operator!=(const TAngle<ValueType> other) const noexcept
		{
			return Radians != other.Radians;
		}

		constexpr bool operator==(const TRadians<ValueType> radians) const noexcept
		{
			return Radians == radians;
		}

		constexpr bool operator!=(const TRadians<ValueType> radians) const noexcept
		{
			return Radians != radians;
		}

		constexpr bool operator==(const TDegrees<ValueType> degrees) const noexcept
		{
			return Radians == degrees.ToRadians();
		}

		constexpr bool operator!=(const TDegrees<ValueType> degrees) const noexcept
		{
			return Radians != degrees.ToRadians();
		}
	private:
		/* The angle is stored in radians */
		TRadians<ValueType> Radians;
	};

	typedef TAngle<float>		Angle;
	typedef TAngle<double>		DAngle;

	inline namespace literals {
		struct RadiansProxy
		{
			const long double Value;
			constexpr RadiansProxy(const long double value) noexcept
				:
				Value(value)
			{}

			template<typename ValueType>
			constexpr RadiansProxy operator*(const ValueType value) const noexcept requires std::is_integral_v<ValueType>
			{
				return RadiansProxy(Value * static_cast<const long double>(value));
			}

			template<typename ValueType>
			constexpr RadiansProxy operator/(const ValueType value) const noexcept requires std::is_integral_v<ValueType>
			{
				return RadiansProxy(Value / static_cast<const long double>(value));
			}

			constexpr operator Radians() const noexcept
			{
				return Radians(static_cast<float>(Value));
			}

			constexpr operator DRadians() const noexcept
			{
				return DRadians(static_cast<double>(Value));
			}

			constexpr operator Angle() const noexcept
			{
				return Angle(this->operator Radians());
			}

			constexpr operator DAngle() const noexcept
			{
				return DAngle(this->operator DRadians());
			}
		};

		struct DegreesProxy
		{
			const long double Value;
			constexpr DegreesProxy(const long double value) noexcept
				:
				Value(value)
			{}

			template<typename ValueType>
			constexpr DegreesProxy operator*(const ValueType value) const noexcept requires std::is_integral_v<ValueType>
			{
				return DegreesProxy(Value * static_cast<const long double>(value));
			}

			template<typename ValueType>
			constexpr DegreesProxy operator/(const ValueType value) const noexcept requires std::is_integral_v<ValueType>
			{
				return DegreesProxy(Value / static_cast<const long double>(value));
			}

			constexpr operator Degrees() const noexcept
			{
				return Degrees(static_cast<float>(Value));
			}

			constexpr operator DDegrees() const noexcept
			{
				return DDegrees(static_cast<double>(Value));
			}

			constexpr operator Angle() const noexcept
			{
				return Angle(this->operator Degrees());
			}

			constexpr operator DAngle() const noexcept
			{
				return DAngle(this->operator DDegrees());
			}
		};

		constexpr RadiansProxy operator""_rad(const long double radians) noexcept
		{
			return RadiansProxy{ radians };
		}

		constexpr DegreesProxy operator""_deg(const long double degrees) noexcept
		{
			return DegreesProxy{ degrees };
		}

		constexpr RadiansProxy operator""_rad(const unsigned long long int radians) noexcept
		{
			return RadiansProxy{ static_cast<double>(radians) };
		}

		constexpr DegreesProxy operator""_deg(const unsigned long long int degrees) noexcept
		{
			return DegreesProxy{ static_cast<double>(degrees) };
		}
	}

	constexpr RadiansProxy operator+(const RadiansProxy lhs, const RadiansProxy rhs) noexcept
	{
		return RadiansProxy{ lhs.Value + rhs.Value };
	}

	constexpr RadiansProxy operator-(const RadiansProxy lhs, const RadiansProxy rhs) noexcept
	{
		return RadiansProxy{ lhs.Value - rhs.Value };
	}

	constexpr DegreesProxy operator+(const DegreesProxy lhs, const DegreesProxy rhs) noexcept
	{
		return DegreesProxy{ lhs.Value + rhs.Value };
	}

	constexpr DegreesProxy operator-(const DegreesProxy lhs, const DegreesProxy rhs) noexcept
	{
		return DegreesProxy{ lhs.Value - rhs.Value };
	}
}