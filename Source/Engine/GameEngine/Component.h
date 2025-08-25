#pragma once
#include "Object.h"

namespace bacon {
	class Component : public Object {
	public:
		class Actor* owner { nullptr };

		Component() = default;

		virtual void Start() {}
		virtual void Destroyed() {}

		virtual void Update(float dt) = 0;
	};
}