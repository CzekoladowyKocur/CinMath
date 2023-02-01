#include "CinMath/CinMath.h"
#include <iostream>

/*
void Update(const float deltaTimeSec)
{
    ...
    m_Rotation += 3_deg * deltaTimeSec; // Rotate by 3 degrees every second
}
*/

inline void ExampleAngles() noexcept
{
    using namespace CinMath;
	using namespace CinMath::Printing;

    const Radians rads{ 2_rad };
    std::cout << "Radians: " << rads << '\n';
    std::cout << "Radians to degrees: " << rads.ToDegrees() << '\n';

    const Degrees degrees{ 114.5916_deg };
    std::cout << "Degrees: " << degrees << '\n';
    std::cout << "Degrees to radians: " << degrees.ToRadians() << '\n';
    const Angle angleInRadians{ rads };
    std::cout << "Angle specified in radians:\n";
    std::cout << "Radians: " << angleInRadians.ToRadians() << '\n';
    std::cout << "Degrees: " << angleInRadians.ToDegrees() << '\n';
    std::cout << '\n';
    const Angle angleInDegrees{ degrees };
    std::cout << "Angle specified in degrees:\n";
    std::cout << "Radians: " << angleInDegrees.ToRadians() << '\n';
    std::cout << "Degrees: " << angleInDegrees.ToDegrees() << '\n';
    std::cout << '\n';

    std::cout << "Sinus of 90 degrees angle: " << sin(Angle{ 90_deg }.ToRadians());
}