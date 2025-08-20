#pragma once
#include "GameEngine/Component.h"

class Player : public bacon::Component {
public:
	Player() = default;

	void Update(float dt) override;
	void OnCollision(class bacon::Actor* other);

	void Read(const bacon::json::value_t& value) override;

	float speed;
	float rotationRate;
	float fireRate = 0.3f;
	float fireTimer = 0.0f;
};