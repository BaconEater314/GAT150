#pragma once
//#include <box2d.box2d.h>
#include <memory>

namespace bacon {
	//inline b2Vec2 to_b2(const vec2& v) { return b2Vec2{ v.x,v.y }; }
	//inline vec2 to_vec2(const b2vec2& v) { return vec2{ v.x,v.y }; }

	class Physics {
	public:
		Physics() = default;

		bool Initialize();
		void Kill();

		void Update(float dt);

		vec2 WorldToPixel(const vec2& world) {}

	private:
		//b2WorldId m_worldId;
	};
}