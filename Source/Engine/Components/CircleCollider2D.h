#pragma once
#include "ColliderComponent.h"

namespace bacon {
	class CircleCollider2D : public ColliderComponent {
	public:
		float radius;

		void Update(float dt) override;

		bool CheckCollision(ColliderComponent& other) override;

		void Read(const json::value_t& value) override;
	};
}