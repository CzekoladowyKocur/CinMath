#include "CinMath/CinMath.h"
#include <iostream>

inline void ExampleSwizzling() noexcept
{
    using namespace CinMath;
	using namespace CinMath::Printing;

    /* Print sizes */
    std::cout << "Size of 4-element vector: " << sizeof(Vector4) << '\n';
    std::cout << "Size of 4-element vector (double precision): " << sizeof(DVector4) << '\n';

    /* Double precision vector */
	constexpr DVector4 dVector4{ 1.0, 2.0, 3.0, 4.0 };
	std::cout << "Double Vector4: " << dVector4;
	std::cout << "Double Vector4 xy swizzle: " << dVector4.xy;
	std::cout << "Double Vector4 xyz swizzle: " << dVector4.xyz;
	std::cout << "Double Vector4 xyzw swizzle: " << dVector4.xyzw;

    const Vector2 vector2{ static_cast<Vector2>(static_cast<DVector2>(dVector4.xy)) };
    std::cout << "Swizzle cast to lower precision: " << vector2;
}