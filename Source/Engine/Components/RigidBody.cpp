#include "RigidBody.h"

namespace bacon {
	FACTORY_REGISTER(RigidBody)

	void RigidBody::Update(float dt) {
		owner->transform.position += velocity * dt;
		velocity = velocity * (1.0f / (1.0f + damping * dt));
	}
}

