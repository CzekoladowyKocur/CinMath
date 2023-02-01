#include "CinMath/CinMath.h"
#include <iostream>

inline void ExampleMatrix() noexcept
{
    using namespace CinMath;
	using namespace CinMath::Printing;
    
	std::cout << "Identity(): " << Matrix4::Identity();
	std::cout << "Matrix4(2.0f): " << Matrix4(2.0f);
	std::cout << MatrixPrinter(Matrix4(2.0f), ThickMatrixPrintSpecificer());
}