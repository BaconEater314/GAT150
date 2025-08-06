#pragma once
#include "../../Engine/GameEngine/Actor.h"

class Rocket : public bacon::Actor {
public:
	Rocket() = default;
	Rocket(const bacon::Transform& transform, bacon::res_t<bacon::Texture> texture) :
		Actor{ transform, texture }
	{}

	void Update(float dt) override;

	float speed = 200;

	void OnCollision(Actor* other) override;

private:
};