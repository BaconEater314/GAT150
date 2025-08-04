#pragma once
#include "../../Engine/GameEngine/Actor.h"

class Rocket : public bacon::Actor {
public:
	Rocket() = default;
	Rocket(const bacon::Transform& transform, std::shared_ptr<bacon::Model> model) :
		Actor{ transform, model }
	{}

	void Update(float dt) override;

	float speed = 200;

	void OnCollision(Actor* other) override;

private:
};