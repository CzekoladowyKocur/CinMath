cmake_minimum_required(VERSION 3.0.0)

set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type")

set(CMAKE_CXX_STANDARD 20)           
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS NO)

include(FetchContent)
set(BENCHMARK_ENABLE_TESTING off)    
FetchContent_Declare(googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.11.0)      
FetchContent_Declare(googlebenchmark
        GIT_REPOSITORY https://github.com/google/benchmark.git
        GIT_TAG v1.6.0)              
FetchContent_MakeAvailable(googletest googlebenchmark)

if(MSVC)
  target_compile_options(gtest PRIVATE "/w")
  target_compile_options(gmock PRIVATE "/w")
  target_compile_options(benchmark PRIVATE "/w")
else()
  target_compile_options(gtest PRIVATE "-w")
  target_compile_options(gmock PRIVATE "-w")
  target_compile_options(benchmark PRIVATE "-w")
endif()

project(CinMathBenchmark
    VERSION 1.0
    DESCRIPTION "Cin Math Benchmark"
    LANGUAGES CXX)

if(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    add_compile_options(/W4 /WX)
elseif(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    add_compile_options(-Wall -Werror -mavx)
endif()

add_executable(CinMathBenchmark
    Benchmark/main.cpp)

target_link_libraries(CinMathBenchmark
    PRIVATE benchmark::benchmark)

target_include_directories(CinMathBenchmark
    PRIVATE Benchmark,
    CinMath/include)

target_compile_features(CinMathBenchmark
    PRIVATE cxx_std_20)

add_executable(TestSuite
    TestSuite/main.cpp)

target_include_directories(TestSuite
    PRIVATE Benchmark,    
    CinMath/include)

target_compile_features(TestSuite
    PRIVATE cxx_std_20)

add_executable(Examples
    Examples/main.cpp)

target_include_directories(Examples
    PRIVATE Benchmark,    
    CinMath/include)

target_compile_features(Examples
    PRIVATE cxx_std_20)