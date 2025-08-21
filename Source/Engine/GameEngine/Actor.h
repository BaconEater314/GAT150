#pragma once
#include "Object.h"
#include "Math/Transform.h"
#include "Renderer/Mesh.h"
#include "Renderer/Texture.h"
#include "Component.h"
#include "Core/Factory.h"

#include <memory>
#include <string>
#include <vector>

namespace bacon {
	class Actor : public Object {
	public:
		std::string tag;

		bool dead { false };
		float lifespan { 0 };
		bool persistant = false;

		Transform transform;
		class Scene* scene{ nullptr };

		float m_health;


	public:
		Actor() = default;
		Actor(Transform transform) :
			transform { transform }
		{ }
		Actor(const Actor& other);

		CLASS_PROTOTYPE(Actor)

		virtual void Update(float dt);
		virtual void Draw(class Renderer& renderer);
		void Read(const json::value_t& value) override;

		virtual void OnCollision(Actor* other) {};

		void AddComponent(std::unique_ptr<Component> component);

		template <typename T>
		T* GetComponent(); 

		template <typename T>
		std::vector<T*> GetComponents();

	protected:
		std::vector<std::unique_ptr<Component>> m_components;
	};

	template<typename T>
	inline T* Actor::GetComponent(){
		for (auto& component : m_components) {
			auto result = dynamic_cast<T*>(component.get());
			if (result) return result;
		}
		return nullptr;
	}

	template<typename T>
	inline std::vector<T*> Actor::GetComponents() {

		std::vector<T*> results;

		for (auto& component : m_components) {
			auto result = dynamic_cast<T*>(component.get());
			if (result) results.push_back(result);
		}
		return results;
	}
}