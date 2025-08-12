#include "RigidBody.h"

namespace bacon {
	void RigidBody::Update(float dt) {
		owner->transform.position += velocity * dt;
		velocity = velocity * (1.0f / (1.0f + damping * dt));
	}
}

