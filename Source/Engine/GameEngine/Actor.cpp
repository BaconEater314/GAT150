#include "Actor.h"
#include "Renderer/Renderer.h"
#include "Components/RendererComponent.h"

namespace bacon{
	void Actor::Update(float dt) {
		if (dead) return;

		if (lifespan != 0) {
			lifespan -= dt;
			if (lifespan <= 0) {
				dead = true;
			}
		}

		//update all components
		for (auto& component : m_components) {
			if(component->active) component->Update(dt);
		}
	}

	void Actor::Draw(Renderer& renderer) {
		if (dead) return;

		for (auto& component : m_components) {
			if (component->active) {
				auto rendererComponent = dynamic_cast<RendererComponent*>(component.get());
				if (rendererComponent) rendererComponent->Draw(renderer);
			}
		}

		//renderer.DrawTexture(m_texture.get(), transform.position.x, transform.position.y, transform.rotation, transform.scale);
	}

	void Actor::AddComponent(std::unique_ptr<Component> component){
		component->owner = this;
		m_components.push_back(std::move(component));
	}
}