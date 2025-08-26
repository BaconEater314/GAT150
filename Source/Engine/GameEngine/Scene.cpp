#include "Components/ColliderComponent.h"
#include "Scene.h"
#include "EngineMinimal.h"

namespace bacon {
	bool Scene::Load(const std::string& sceneName) {
		//load json
		json::document_t document;
		if (!(json::Load(sceneName, document))) {
			Logger::Error("Could not load scene: {}", sceneName);
			return false;
		}

		//create scene
		Read(document);

		//start actors
		for (auto& actor : m_actors) {
			actor->Start();
		}

		return true;
	}

	void Scene::Update(float dt) {
		for (auto& actor : m_actors) {
			if (actor->active) {
				actor->Update(dt);
			}
		}

		//check for collision
		for (auto& actorA : m_actors) {
			for (auto& actorB : m_actors) {
				if (actorA == actorB || (actorA->dead || actorB->dead)) continue;

				auto colliderA = actorA->GetComponent<ColliderComponent>();
				auto colliderB = actorB->GetComponent<ColliderComponent>();

				//make sure both actors have a collider
				if (!colliderA || !colliderB) continue;

				if (colliderA->CheckCollision(*colliderB)) {
					actorA->OnCollision(actorB.get());
					actorB->OnCollision(actorA.get());
				}
			}
		}
	}

	void Scene::Draw(Renderer& renderer) {
		for (auto& actor :  m_actors) {
			if (actor->active) {
				actor->Draw(renderer);
			}
		}
	}
	void Scene::AddActor(std::unique_ptr<Actor> actor, bool start){
		actor->scene = this;
		if(start) actor->Start();
		m_actors.push_back(std::move(actor));
	}

	void Scene::RemoveAllActors(bool force){
		//remove non-persistant actors
		for (auto iter = m_actors.begin(); iter != m_actors.end();) {
			if (!(*iter)->persistant || force) {
				iter = m_actors.erase(iter);
			}
			else {
				iter++;
			}
		}
	}

	void bacon::Scene::Read(const json::value_t& value) {
		//read prototypes
		if (JSON_HAS(value, prototypes)) {
			for (auto& actorValue : JSON_GET(value, prototypes).GetArray()) {
				auto actor = Factory::Instance().Create<Actor>("Actor");
				actor->Read(actorValue);

				std::string name = actor->name;
				Factory::Instance().RegisterPrototype<Actor>(name, std::move(actor));
			}
		}

		//read actors
		if (JSON_HAS(value, actors)) {
			for (auto& actorValue : JSON_GET(value, actors).GetArray()) {
				auto actor = Factory::Instance().Create<Actor>("Actor");
				actor->Read(actorValue);

				AddActor(std::move(actor), false);
			}
		}
	}
}