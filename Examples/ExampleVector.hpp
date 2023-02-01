#include "CinMath/CinMath.h"

inline void ExampleVector() noexcept
{
    using namespace CinMath;
	using namespace CinMath::Printing;

    /* Print sizes */
    std::cout << "Size of 4-element vector: " << sizeof(Vector4) << '\n';
    std::cout << "Size of 4-element vector (double precision): " << sizeof(DVector4) << '\n';

	constexpr Vector2 vector2; // Default initializes to [0, 0]
	std::cout << "Default initialized vector: " << vector2;

	Vector3 vector3{ 3.0f, 6.0f, 9.0f };
	vector3 *= 2.0f;
	std::cout << "Vector3: " << vector3;

	{
		constexpr Vector2 vector2_{ 15.0f, 16.0f };
		constexpr DVector2 dVector2{ 5.0, 6.0 };

		std::cout << "Casted addition: " << vector2_ + static_cast<Vector2>(dVector2);
	}
}