# CinMath is an inline, header only C++20 linear algebra and mathematics library. 
### In order to easily work with GLSL, the operations are **column-major**. The library supports arithmetic operations on vectors, matrices and quaternions. It also provides basic transformation functions.

### CinMath utilizes SIMD intrinsics (single instruction multiple data) - both 128 bit wide and 256 bit wide registers can be used to parallelize non-dependant computations.

### Using the library
##### All of the library functionalities come in a single header (CinMath.h). The library can be configured to either use SSE or AVX instruction sets with a single define, above the main header:
```cpp
#define CIN_USE_SSE // For sse instructions
#include "CinMath/CinMath.h"
```

```cpp
#define CIN_USE_AVX // For avx instructions
#include "CinMath/CinMath.h"
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

### Cloning the repository (contains glm submodule for unit testing):
`git clone --recursive https://github.com/CzekoladowyKocur/CinMath.git`

### Building
#### The header library can be used on both windows and linux.
##### Project building (unit tests + benchmark): currently windows only. To build the project, simply run the GenerateWindowsProject.bat file. 

### Unit testing
##### The project comes with unit tests defined for most of the available functionality. The test results are compared against glm (https://github.com/g-truc/glm).
