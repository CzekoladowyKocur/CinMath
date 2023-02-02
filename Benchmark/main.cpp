#include <benchmark/benchmark.h>
#include <random>
#include <cstdlib>

#define CIN_USE_DEFAULT_INSTRUCTION_SET
//#define CIN_USE_SSE
//#define CIN_USE_AVX
#include "CinMath/CinMath.h"

static void BM_Matrix4x4Multiplication(benchmark::State& state) noexcept
{
	srand(static_cast<unsigned int>(time(nullptr)));

	const CinMath::Matrix4 a
	{
		static_cast<float>(rand()), static_cast<float>(rand()), static_cast<float>(rand()), static_cast<float>(rand()),
		static_cast<float>(rand()), static_cast<float>(rand()), static_cast<float>(rand()), static_cast<float>(rand()),
		static_cast<float>(rand()), static_cast<float>(rand()), static_cast<float>(rand()), static_cast<float>(rand()),
		static_cast<float>(rand()), static_cast<float>(rand()), static_cast<float>(rand()), static_cast<float>(rand())
	};

	const CinMath::Matrix4 b
	{
		static_cast<float>(rand()), static_cast<float>(rand()), static_cast<float>(rand()), static_cast<float>(rand()),
		static_cast<float>(rand()), static_cast<float>(rand()), static_cast<float>(rand()), static_cast<float>(rand()),
		static_cast<float>(rand()), static_cast<float>(rand()), static_cast<float>(rand()), static_cast<float>(rand()),
		static_cast<float>(rand()), static_cast<float>(rand()), static_cast<float>(rand()), static_cast<float>(rand())
	};

	benchmark::ClobberMemory();
	for (const auto _ : state)
		benchmark::DoNotOptimize(a * b);

	state.SetItemsProcessed(state.iterations());
}

BENCHMARK(BM_Matrix4x4Multiplication);
BENCHMARK_MAIN();