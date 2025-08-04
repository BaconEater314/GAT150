#pragma once
#include <SDL3/SDL.h>
#include <algorithm>
#include <cmath>

namespace bacon::math {
	constexpr float pi = 3.14159265358979323846264338327950288419f;
	constexpr float twoPi = 2 * pi;
	constexpr float halfPi = pi / 2;

	//converts an angle from radians to degrees or vice versa
	constexpr float radToDeg(float rad) { return rad * (180 / pi); }
	constexpr float degToRad(float deg) { return deg * (pi / 180); }

	/*template <typename T>
	T min(T a, T b) {
		return std::min(a,b)//(a < b) ? a : b;
	}*/

	constexpr int wrap(int value, int min, int max) {
		int range = max - min;
		int result = (value - min) % range;
		if (result < 0) result += range;

		return min + result;
	}

	inline float wrap(float value, float min, float max) {
		float range = max - min;
		float result = std::fmodf(value - min, range);
		if (result < 0) result += range;

		return min + result;
	}
	template<typename T>
	inline T sign(T v) {
		return (v < 0) ? (T)-1 : (v > 0) ? (T)1 : (T)0;
	}

	using std::min;
	using std::max;
	using std::clamp;
	using std::sqrt;
	using std::sqrtf;
	using std::sin;
	using std::sinf;
	using std::asin;
	using std::asinf;
	using std::cos;
	using std::cosf;
	using std::acos;
	using std::acosf;
	using std::tan;
	using std::tanf;
	using std::atan2;
	using std::atan2f;
}
	