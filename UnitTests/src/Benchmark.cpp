#pragma once

#include <chrono>
#include <fstream>
#include <sstream>
#ifndef GLM_SILENT_WARNINGS
#define GLM_SILENT_WARNINGS
#endif
#define GLM_FORCE_AVX
#define GLM_FORCE_ALIGNED
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"


#define CIN_USE_AVX
#include "CinMath/CinMath.h"

#define FORCE_LINKING(x) { [[maybe_unused]] volatile void* volatile dummy = &x; }
constexpr std::size_t Max{ 30 };

#define SPEED_TEST_DATA_VECTOR4																	\
(float)(rand() % 20), (float)(rand() % 20), (float)(rand() % 20), (float)(rand() % 20)			

#define SPEED_TEST_DATA_MATRIX_4																\
(float)(rand() % 20), (float)(rand() % 20), (float)(rand() % 20), (float)(rand() % 20),			\
(float)(rand() % 20), (float)(rand() % 20), (float)(rand() % 20), (float)(rand() % 20),			\
(float)(rand() % 20), (float)(rand() % 20), (float)(rand() % 20), (float)(rand() % 20),			\
(float)(rand() % 20), (float)(rand() % 20), (float)(rand() % 20), (float)(rand() % 20)

class Timer
{
public:
	Timer()
		:
		m_Running(false),
		m_StartTime({}),
		m_EndTime({})
	{}

	void Start()
	{
		m_StartTime = std::chrono::high_resolution_clock::now();
		m_Running = true;
	}

	void Stop()
	{
		m_EndTime = std::chrono::high_resolution_clock::now();
		m_Running = false;
	}

	double ElapsedMilliseconds()
	{
		const std::chrono::time_point<std::chrono::high_resolution_clock> endTime = m_Running ? std::chrono::high_resolution_clock::now() : m_EndTime;
		return static_cast<double>(std::chrono::duration_cast<std::chrono::milliseconds>(endTime - m_StartTime).count());
	}

	double ElapsedNanoseconds()
	{
		std::chrono::time_point<std::chrono::high_resolution_clock> endTime = m_Running ? std::chrono::high_resolution_clock::now() : m_EndTime;
		return static_cast<double>(std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - m_StartTime).count());
	}

	double ElapsedSeconds()
	{
		return ElapsedMilliseconds() / 1000.0;
	}

private:
	std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTime;
	std::chrono::time_point<std::chrono::high_resolution_clock> m_EndTime;
	bool m_Running;
};

constexpr std::size_t g_TestCount{ 1'000'000 };

void BenchmarkMatrix4Multiplication(std::fstream& output)
{
	output << "MATRIX 4:\n";
	output << "Multiplication:\n";

	float data[16]{ SPEED_TEST_DATA_MATRIX_4 };
	CinMath::Matrix4 matrix1;
	CinMath::Matrix4 matrix2;

	glm::mat4 glmmatrix1;
	glm::mat4 glmmatrix2;
	
	std::memcpy(&matrix1, data, sizeof(CinMath::Matrix4));
	std::memcpy(&matrix2, data, sizeof(CinMath::Matrix4));

	std::memcpy(&glmmatrix1, data, sizeof(CinMath::Matrix4));
	std::memcpy(&glmmatrix2, data, sizeof(CinMath::Matrix4));

	Timer timer;
	timer.Start();

	for (uint32_t i{ 0 }; i < g_TestCount; ++i)
	{
		auto result1{ matrix1 * matrix2 };
		auto result2{ matrix2 * matrix1 };
		auto result3{ result1 * result2 * matrix1 * matrix2 };

		FORCE_LINKING(result1);
		FORCE_LINKING(result2);
		FORCE_LINKING(result3);
	}

	timer.Stop();
	const double cinTotal{ timer.ElapsedNanoseconds() };
	output << "Cinnamon: Elapsed time (ns): " << std::setprecision(20) << cinTotal << '\n';
	timer.Start();
	for (uint32_t i{ 0 }; i < g_TestCount; ++i)
	{
		auto result1 { glmmatrix1 * glmmatrix2};
		auto result2 { glmmatrix2 * glmmatrix1};
		auto result3{ result1 * result2 * glmmatrix1 * glmmatrix2 };
		
		FORCE_LINKING(result1);
		FORCE_LINKING(result2);
		FORCE_LINKING(result3);
	}
	const double glmTotal{ timer.ElapsedNanoseconds() };
	output << "Glm: Elapsed time (ns): " << std::setprecision(20) << glmTotal << '\n';
	timer.Stop();
	output << "\n\n";

	std::cout << "Matrix4 multiplication ratio [CIN / GLM]: " << cinTotal / glmTotal << '\n';
}

void BenchmarkMatrix4Addition(std::fstream& output)
{
	output << "MATRIX 4:\n";
	output << "Addition:\n";

	float data[16]{ SPEED_TEST_DATA_MATRIX_4 };
	CinMath::Matrix4 matrix1;
	CinMath::Matrix4 matrix2;

	glm::mat4 glmmatrix1;
	glm::mat4 glmmatrix2;

	auto res = glm::translate(glmmatrix2, {});

	std::memcpy(&matrix1, data, sizeof(CinMath::Matrix4));
	std::memcpy(&matrix2, data, sizeof(CinMath::Matrix4));

	std::memcpy(&glmmatrix1, data, sizeof(CinMath::Matrix4));
	std::memcpy(&glmmatrix2, data, sizeof(CinMath::Matrix4));

	Timer timer;
	timer.Start();

	for (uint32_t i{ 0 }; i < g_TestCount; ++i)
	{
		auto result1{ matrix1 + matrix2 };
		auto result2{ matrix2 + matrix1 };
		auto result3{ result1 + result2 + matrix1 + matrix2 };
		
		FORCE_LINKING(result1);
		FORCE_LINKING(result2);
		FORCE_LINKING(result3);
	}

	timer.Stop();
	const double cinTotal{ timer.ElapsedNanoseconds() };
	output << "Cinnamon: Elapsed time (ns): " << std::setprecision(20) << cinTotal << '\n';
	timer.Start();
	for (uint32_t i{ 0 }; i < g_TestCount; ++i)
	{
		auto result1{ glmmatrix1 + glmmatrix2 };
		auto result2{ glmmatrix2 + glmmatrix1 };
		auto result3{ result1 + result2 + glmmatrix1 + glmmatrix2 };
		
		FORCE_LINKING(result1);
		FORCE_LINKING(result2);
		FORCE_LINKING(result3);
	}
	const double glmTotal{ timer.ElapsedNanoseconds() };
	output << "Glm: Elapsed time (ns): " << std::setprecision(20) << glmTotal << '\n';
	timer.Stop();
	output << "\n\n";

	std::cout << "Matrix4 addition ratio [CIN / GLM]: " << cinTotal / glmTotal << '\n';
}

void BenchmarkMatrix4Transpose(std::fstream& output)
{
	output << "MATRIX 4:\n";
	output << "Transpose:\n";

	float data[16]{ SPEED_TEST_DATA_MATRIX_4 };
	CinMath::Matrix4 matrix1;
	CinMath::Matrix4 matrix2;

	glm::mat4 glmmatrix1;
	glm::mat4 glmmatrix2;

	std::memcpy(&matrix1, data, sizeof(CinMath::Matrix4));
	std::memcpy(&matrix2, data, sizeof(CinMath::Matrix4));

	std::memcpy(&glmmatrix1, data, sizeof(CinMath::Matrix4));
	std::memcpy(&glmmatrix2, data, sizeof(CinMath::Matrix4));

	Timer timer;
	timer.Start();

	for (uint32_t i{ 0 }; i < g_TestCount; ++i)
	{
		auto result1{ CinMath::Transpose(matrix1) };
		auto result2{ CinMath::Transpose(matrix2) };

		FORCE_LINKING(result1);
		FORCE_LINKING(result2);
	}

	timer.Stop();
	const double cinTotal{ timer.ElapsedNanoseconds() };
	output << "Cinnamon: Elapsed time (ns): " << std::setprecision(20) << cinTotal << '\n';
	timer.Start();
	for (uint32_t i{ 0 }; i < g_TestCount; ++i)
	{
		auto result1{ glm::transpose(glmmatrix1) };
		auto result2{ glm::transpose(glmmatrix2) };

		FORCE_LINKING(result1);
		FORCE_LINKING(result2);
	}
	const double glmTotal{ timer.ElapsedNanoseconds() };
	output << "Glm: Elapsed time (ns): " << std::setprecision(20) << glmTotal << '\n';
	timer.Stop();
	output << "\n\n";

	std::cout << "Matrix4 transpose ratio [CIN / GLM]: " << cinTotal / glmTotal << '\n';
}

void BenchmarkMatrix4Determinant(std::fstream& output)
{
	output << "MATRIX 4:\n";
	output << "Determinant:\n";

	float data[16]{ SPEED_TEST_DATA_MATRIX_4 };
	CinMath::Matrix4 matrix1;
	CinMath::Matrix4 matrix2;

	glm::mat4 glmmatrix1;
	glm::mat4 glmmatrix2;

	std::memcpy(&matrix1, data, sizeof(CinMath::Matrix4));
	std::memcpy(&matrix2, data, sizeof(CinMath::Matrix4));

	std::memcpy(&glmmatrix1, data, sizeof(CinMath::Matrix4));
	std::memcpy(&glmmatrix2, data, sizeof(CinMath::Matrix4));

	Timer timer;
	timer.Start();

	for (uint32_t i{ 0 }; i < g_TestCount; ++i)
	{
		auto result1{ CinMath::Determinant(matrix1) };
		auto result2{ CinMath::Determinant(matrix2) };

		FORCE_LINKING(result1);
		FORCE_LINKING(result2);
	}

	timer.Stop();
	const double cinTotal{ timer.ElapsedNanoseconds() };
	output << "Cinnamon: Elapsed time (ns): " << std::setprecision(20) << cinTotal << '\n';
	timer.Start();
	for (uint32_t i{ 0 }; i < g_TestCount; ++i)
	{
		auto result1{ glm::determinant(glmmatrix1) };
		auto result2{ glm::determinant(glmmatrix2) };

		FORCE_LINKING(result1);
		FORCE_LINKING(result2);
	}
	const double glmTotal{ timer.ElapsedNanoseconds() };
	output << "Glm: Elapsed time (ns): " << std::setprecision(20) << glmTotal << '\n';
	timer.Stop();
	output << "\n\n";

	std::cout << "Matrix4 determinant ratio [CIN / GLM]: " << cinTotal / glmTotal << '\n';
}

void BenchmarkVector4Multiplication(std::fstream& output)
{
	output << "VECTOR4 4:\n";
	output << "Multiplication:\n";

	float data[4]{ SPEED_TEST_DATA_VECTOR4 };
	CinMath::Vector4 vector1;
	CinMath::Vector4 vector2;

	glm::vec4 glmvector1;
	glm::vec4 glmvector2;

	std::memcpy(&vector1, data, sizeof(CinMath::Vector4));
	std::memcpy(&vector2, data, sizeof(CinMath::Vector4));

	std::memcpy(&glmvector1, data, sizeof(CinMath::Vector4));
	std::memcpy(&glmvector2, data, sizeof(CinMath::Vector4));

	Timer timer;
	timer.Start();

	for (uint32_t i{ 0 }; i < g_TestCount; ++i)
	{
		auto result1{ vector1 + vector2 };
		auto result2{ vector2 + vector1 };
		auto result3{ result1 + result2 + vector1 + vector2 };

		FORCE_LINKING(result1);
		FORCE_LINKING(result2);
		FORCE_LINKING(result3);
	}

	timer.Stop();
	const double cinTotal{ timer.ElapsedNanoseconds() };
	output << "Cinnamon: Elapsed time (ns): " << std::setprecision(20) << cinTotal << '\n';
	timer.Start();
	for (uint32_t i{ 0 }; i < g_TestCount; ++i)
	{
		auto result1{ glmvector1 + glmvector2 };
		auto result2{ glmvector2 + glmvector1 };
		auto result3{ result1 + result2 + glmvector1 + glmvector2 };

		FORCE_LINKING(result1);
		FORCE_LINKING(result2);
		FORCE_LINKING(result3);
	}
	const double glmTotal{ timer.ElapsedNanoseconds() };
	output << "Glm: Elapsed time (ns): " << std::setprecision(20) << glmTotal << '\n';
	timer.Stop();
	output << "\n\n";

	std::cout << "Vector4 multiplication ratio [CIN / GLM]: " << cinTotal / glmTotal << '\n';
}

int Benchmark(const bool clear)
{
	std::fstream output("C:/Martin/Testy/benchmark.txt", std::ofstream::out | (!clear ? std::ofstream::app : 0));
	if (!output.is_open())
		return EXIT_FAILURE;
	
	output << "Benchmark ";
#ifdef CIN_USE_DEFAULT_INSTRUCTION_SET
	output << "(Default instruction set)\n\n";
#elif defined CIN_USE_SSE
	output << "(SSE)\n\n";
#elif defined CIN_USE_AVX
	output << "(AVX)\n\n";
#endif
	BenchmarkMatrix4Multiplication(output);
	BenchmarkMatrix4Addition(output);
	BenchmarkMatrix4Transpose(output);
	BenchmarkMatrix4Determinant(output);

	BenchmarkVector4Multiplication(output);

	output.close();
	output << "-------------------\n\n";
	return 0;
}