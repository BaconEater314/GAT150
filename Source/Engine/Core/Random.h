#pragma once
#include "Math/Vector2.h"
#include "Math/Math.h"

#include <cstdlib>
#include <random>

namespace bacon::random {
	//generates a random integer value
	inline int GetRandom() { return rand(); }

	//generates a random integer in the range [0, max)
	inline int GetRandom(int max) { return rand() % max; }

	//generates a random integer in the range (min, max)
	inline int GetRandom(int max, int min) { return min + GetRandom(max - min + 1); }

	//generates a random float in the range [0.0, 1.0]
	inline float GetRandomFloat() { return rand() / (float)RAND_MAX; }

    inline std::mt19937& generator() {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        return gen;
    }

    inline void seed(unsigned int value) {
        generator().seed(value);
    }

    inline int getInt(int min, int max) {
        std::uniform_int_distribution<> dist(min, max);
        return dist(generator());
    }

    inline int getInt(int max) {
        return getInt(0, max - 1);
    }

    inline int getInt() {
        static std::uniform_int_distribution<> dist;
        return dist(generator());
    }

    template <typename T = float>
    inline T getReal(T min, T max) {
        std::uniform_real_distribution<T> dist(min, max);
        return dist(generator());
    }

    template <typename T = float>
    inline T getReal(T max) {
        return getReal(static_cast<T>(0), static_cast<T>(max));
    }

    template <typename T = float>
    inline T getReal() {
        static std::uniform_real_distribution<T> dist(static_cast<T>(0), static_cast<T>(1));
        return dist(generator());
    }

    inline bool getBool() {
        static std::bernoulli_distribution dist(0.5);
        return dist(generator());
    }

	inline vec2 onUnitCircle() {
		float radians = getReal(math::twoPi);
		vec2 v;
		v.x = math::cosf(radians);
		v.y = math::sinf(radians);
        return {math::cosf(radians), math::sinf(radians)};
	}
}