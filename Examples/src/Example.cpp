#define CIN_USE_SSE
#include "CinMath/CinMath.h"

int main()
{
	using namespace CinMath;

	Vector4 v4; /* 0 initialized vector */
	std::cout << v4 << '\n';

	v4.xyzw = { 1.0f, 1.0f, 1.0f, 1.0f };
	v4.xy *= 2.0f;

	std::cout << v4 << '\n';

	constexpr Matrix4 identityMatrix{ Matrix4::Identity() };
	std::cout << identityMatrix << '\n';

	Matrix4 matrix{ identityMatrix };
	matrix = TranslateIdentity<4, 4, float>(Vector3{ 1.0f, 2.0f, 0.0f });

	std::cout << matrix << '\n';

	Vector3 axis{ 0.0f, 0.0f, 1.0f };
	const float angle{ ToRadians(45.0f) };
	std::cout << "Angle: " << angle << '\n';

	Quaternion quaternion{ AxisAngleToQuaternion(angle, axis) };
	matrix = Rotate(Matrix4x4::Identity(), quaternion);

	std::cout << matrix << '\n';

	auto axisAngle{ QuaternionToAxisAngle(quaternion) };
	std::cout << axisAngle << '\n';

	return 0;
}