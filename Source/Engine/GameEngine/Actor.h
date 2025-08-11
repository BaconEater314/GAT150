#pragma once
#include "Object.h"
#include "Math/Transform.h"
#include "Renderer/Model.h"
#include "Renderer/Texture.h"
#include "Component.h"

#include <memory>
#include <string>

namespace bacon {
	class Actor : public Object {
	public:
		std::string tag;

		vec2 velocity{ 0, 0 };
		float damping{ 0.2f };

		bool dead { false };
		float lifespan { 0 };

		Transform transform;
		class Scene* scene{ nullptr };

		float health;

	public:
		Actor() = default;
		Actor(Transform transform) :
			transform { transform }
		{ }

		virtual void Update(float dt);
		virtual void Draw(class Renderer& renderer);

		virtual void OnCollision(Actor* other) = 0;

		float GetRadius();

		void AddComponent(std::unique_ptr<Component> component);

	protected:
		std::vector<std::unique_ptr<Component>> m_components;

	private:
	};
}