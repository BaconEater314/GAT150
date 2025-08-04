#include "Actor.h"
#include "../Renderer/Model.h"

namespace bacon{
	void Actor::Update(float dt) {
		if (dead) return;

		if (lifespan != 0) {
			lifespan -= dt;
			dead = lifespan <= 0;
		}

		transform.position += velocity * dt;
		velocity = velocity * (1.0f / (1.0f + damping * dt));
	}

	void Actor::Draw(Renderer& renderer) {
		if (dead) return;

		m_model->Draw(renderer, transform);
	}

	float Actor::GetRadius() {
		return(m_model) ? m_model->GetRadius() * transform.scale * 0.75f : 0;
	}
}