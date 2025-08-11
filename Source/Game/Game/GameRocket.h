#pragma once
#include "../../Engine/GameEngine/Actor.h"

class Rocket : public bacon::Actor {
public:
	Rocket() = default;
	Rocket(const bacon::Transform& transform) :
		Actor{ transform}
	{}

	void Update(float dt) override;

	float speed = 200;

	void OnCollision(Actor* other) override;

private:
};