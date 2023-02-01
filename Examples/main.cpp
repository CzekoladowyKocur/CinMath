#include "CinMath/CinMath.h"
#include "ExampleVector.hpp"
#include "ExampleSwizzling.hpp"
#include "ExampleMatrix.hpp"
#include "ExampleAngles.hpp"
#include "ExampleQuaternion.hpp"

#include <iostream>
#include <string_view>
#include <string>

#define EXAMPLE(example) 																									\
std::cout << "==============================\n" << "Running example: " << #example << "\n==============================\n"; \
Example##example(); 																										\
std::cout << "\n==============================\n" << "End example: " << #example << "\n==============================\n";						

int main([[maybe_unused]] const int, [[maybe_unused]] const char**) noexcept
{
	EXAMPLE(Vector);
	EXAMPLE(Swizzling);
	EXAMPLE(Matrix);
	EXAMPLE(Angles);
	EXAMPLE(Quaternion);

	return 0;
}