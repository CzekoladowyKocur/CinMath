#include "Benchmark.h"
#include "UnitTests.h"
#include <cstring>
#include <iostream>
#define UNIT_TEST

int main(const char argc, const char** argv)
{
#ifdef UNIT_TEST
	(void)argc;
	(void)argv;
	return UnitTests();
#else
	bool clearResults{ false };
	if (argc > 1)
		clearResults = strcmp(argv[1], "--clear") == 0;

	if (clearResults)
		std::cout << "Clearing tests...\n";
	
	return Benchmark(clearResults);
#endif
}