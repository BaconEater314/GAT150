#include "Actor.h"
#include "Renderer/Renderer.h"

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

		renderer.DrawTexture(m_texture.get(), transform.position.x, transform.position.y, transform.rotation, transform.scale);
	}

	float Actor::GetRadius() {
		return(m_texture) ? (m_texture->GetSize().Length()) * transform.scale * 0.75f : 0;
	}
}