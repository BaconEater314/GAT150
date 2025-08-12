#pragma once
#include "GameEngine/Component.h"

namespace bacon {
	class ColliderComponent : public Component {
	public:
		virtual bool CheckCollision(ColliderComponent& other) = 0;
	};
}