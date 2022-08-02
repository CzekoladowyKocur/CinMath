# CinMath is an inline, header only C++20 linear algebra and mathematics library. 
### In order to easily work with GLSL, the operations are **column-major**. The library supports arithmetic operations on vectors, matrices and quaternions. It also provides basic transformation functions.

### CinMath utilizes SIMD intrinsics (single instruction multiple data intrinsics): both 128 bit wide and 256 bit wide registers can be used to parallelize non-dependant computations.

### Using the library
##### Currently, all of the library functionalities come in a single header (CinMath.h). The library can be configured to either use SSE or AVX instruction sets with a single define, above the main header:
`#define CIN_USE_SSE` for SSE or `#define CIN_USE_AVX` for AVX optimizations.

### Cloning the repository
##### To clone the repository: (contains glm submodule for unit testing)
`git clone --recursive https://github.com/CzekoladowyKocur/CinMath.git`

### Building
##### Currently windows only. To build the project, simply run the GenerateWindowsProject.bat file. 

### Unit testing
##### The project comes with unit tests defined for most of the available functionality. The test results are compared against glm (https://github.com/g-truc/glm). 
