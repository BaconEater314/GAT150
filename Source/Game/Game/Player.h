#pragma once
#include "GameEngine/Component.h"

class Player : public bacon::Component, public bacon::ICollidable {
public:
	Player() = default;

	CLASS_PROTOTYPE(Player)

	void Update(float dt) override;
	void OnCollision(class bacon::Actor* other) override;

	void Read(const bacon::json::value_t& value) override;

	float speed;
	float rotationRate;
	float fireRate = 0.3f;
	float fireTimer = 0.0f;
};