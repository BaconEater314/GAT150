#pragma once
#include "../../Engine/GameEngine/Actor.h"

class Enemy : public bacon::Actor {
public:
	Enemy() = default;
	Enemy(const bacon::Transform& transform) :
		Actor{ transform}
	{ }

	void Update(float dt) override;

	float speed = 200;
	float fireTimer = 3;
	float fireRate = 1;

	void OnCollision(Actor* other) override;

private:
};