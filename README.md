# CinMath is an inline, templated header only C++20 linear algebra and mathematics library. 
### In order to easily work with GLSL, the operations are performed in a **column-major** fashion. The library supports arithmetic operations on vectors, matrices and quaternions. It also provides basic transformation functions.

### CinMath utilizes SIMD intrinsics (single instruction multiple data) - both 128 bit wide and 256 bit wide registers can be used to parallelize non-dependant computations.

### Using the library
##### All of the library functionalities come in a single header (CinMath.h). The library can be configured to use either SSE or AVX instruction sets with a single define, above the main header:
```cpp
#define CIN_USE_DEFAULT_INSTRUCTION_SET // No SIMD (default)
#include "CinMath/CinMath.h"
```

```cpp
#define CIN_USE_SSE // For sse instructions
#include "CinMath/CinMath.h"
```

```cpp
#define CIN_USE_AVX // For avx instructions
#include "CinMath/CinMath.h"
```
![Instruction sets benchmark plot](https://github.com/CzekoladowyKocur/CinMath/blob/master/BenchmarkResults/Matrix%204x4%20multiplication%20comparison.png)
#### Type safe angle unit literals 
##### The library comes with Radians and Degrees types used for constructing Angles used in transformations
```cpp
const Radians rads{ 2_rad };
std::cout << "Radians: " << rads << '\n'; // Prints 2
std::cout << "Radians to degrees: " << rads.ToDegrees() << '\n'; // Prints 114.592

const Degrees degrees{ 114.5916_deg };
std::cout << "Degrees: " << degrees << '\n'; // Prints 114.5916
std::cout << "Degrees to radians: " << degrees.ToRadians() << '\n'; // Prints 2

const Angle angleInRadians{ rads }; // Degrees can be used too
std::cout << "Angle specified in radians:\n";
std::cout << "Radians: " << angleInRadians.ToRadians() << '\n';
std::cout << "Degrees: " << angleInRadians.ToDegrees() << '\n';
std::cout << '\n';

std::cout << "Sinus of 90 degrees angle: " << sin(Angle{ 90_deg }.ToRadians()); // standard sin() accepts an angle in radians. Prints 1
```
##### User defined literals can be used with arithmetic operators
```cpp
void Update(const float deltaTimeSec)
{
    ...
    m_Rotation += 3_deg * deltaTimeSec; // Rotate by 3 degrees every second
}
```

#### Swizzling
##### The library supports swizzling for vector types
```cpp
#include "CinMath/CinMath.h"

int main(const int argc, const char** argv)
{
	using namespace CinMath;

	Vector4 vector{ 0.0f, 0.0f, 0.0f, 0.0f };
	vector.xyz = { 1.0f, 1.0f, 1.0f };
	vector.z = 2.0f;
	vector.xy *= 1.0f;

	return 0;
}
```

### Cloning the repository:
`git clone https://github.com/CzekoladowyKocur/CinMath.git`

### Building
#### The header library can be used on both windows (MSVC) and linux (GCC) and possibly clang (not tested).
#### Project building
##### Requirements
1. Python 3
2. CMake (minimum version 3.0.0)
3. C++~20~ compatible compiler
##### Windows
run `BuildWindows.bat`
##### Linux 
run `./BuildLinux.sh`
