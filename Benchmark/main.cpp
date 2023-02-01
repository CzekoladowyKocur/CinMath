#include <benchmark/benchmark.h>
#include <random>
#include <cstdlib>
#include <vector>

#define CIN_USE_DEFAULT_INSTRUCTION_SET
//#define CIN_USE_SSE
//#define CIN_USE_AVX

#include "CinMath/CinMath.h"

constexpr size_t g_TestCount{ 1'000U };
static_assert(g_TestCount % 2U == 0, "Must be divisible by two");

static inline void Matrix4x4Multiplication(const std::vector<CinMath::Matrix4x4>& matrices) noexcept
{
	for(size_t i{ 0U }; i < g_TestCount; i += 2U)
		benchmark::DoNotOptimize(matrices[i + 0U] * matrices[i + 1U]);
}

static void BM_Matrix4x4Multiplication(benchmark::State& state)
{
	srand(static_cast<unsigned int>(time(nullptr)));

	std::vector<CinMath::Matrix4x4> matrices(g_TestCount, CinMath::Matrix4x4{});
	for(size_t i{ 0U }; i < g_TestCount; i += 2U)
	{
		CinMath::Matrix4& a{ matrices[i + 0U] };
		CinMath::Matrix4& b{ matrices[i + 1U] };

		for(size_t j{ 0U }; j < 16U; ++j)
		{
			a[j] = static_cast<float>(rand());
			b[j] = static_cast<float>(rand());
		}
	}

	for(auto _ : state)
		Matrix4x4Multiplication(matrices);

	state.SetItemsProcessed(g_TestCount * state.iterations());
}

BENCHMARK(BM_Matrix4x4Multiplication);
BENCHMARK_MAIN();