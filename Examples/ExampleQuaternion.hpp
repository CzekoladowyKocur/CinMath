#include "CinMath/CinMath.h"
#include <iostream>

inline void ExampleQuaternion() noexcept
{
    using namespace CinMath;
    using namespace CinMath::Printing;

    const Angle angle{ 45_rad };
    std::cout << "Angle in radians: " << angle.ToRadians() << '\n';

    Vector3 rotationAxis{ 0.0f, 0.0f, 1.0f };
    Quaternion quaternion{ AxisAngleToQuaternion(angle, rotationAxis) };
    
    std::cout << quaternion << '\n';
}