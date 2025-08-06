#pragma once
#include "GameEngine/Actor.h"

class Player : public bacon::Actor {
public:
	Player() = default;
	Player(const bacon::Transform& transform, bacon::res_t<bacon::Texture> texture) :
		Actor{ transform, texture }
	{ }

	void Update(float dt) override;

	void OnCollision(Actor* other) override;

public:
	float speed;
	float rotationRate;
	float fireRate = 0.3f;
	float fireTimer = 0.0f;

private:
};