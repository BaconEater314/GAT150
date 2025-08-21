#pragma once
#include "GameEngine/Component.h"

namespace bacon {
	class RigidBody : public Component {
	public:
		vec2 velocity{ 0,0 };
		float damping{ 0 };

		CLASS_PROTOTYPE(RigidBody)

		void Update(float dt) override;
		void Read(const json::value_t& value) override;
	};
}