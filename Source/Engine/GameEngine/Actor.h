#pragma once
#include "../Math/Transform.h"
#include "../Renderer/Model.h"

#include <memory>
#include <string>

namespace bacon {
	class Actor {
	public:
		std::string name;
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
		Actor(Transform transform, std::shared_ptr<class Model> model) :
			transform { transform },
			m_model { model }
		{ }

		virtual void Update(float dt);
		virtual void Draw(class Renderer& renderer);

		virtual void OnCollision(Actor* other) = 0;

		float GetRadius();

	protected:
		std::shared_ptr<Model> m_model;

	private:
	};
}