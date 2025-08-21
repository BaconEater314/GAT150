#pragma once
#include "GameEngine/Component.h"

class Enemy : public bacon::Component {
public:
	Enemy() = default;

	void Update(float dt) override;

	CLASS_PROTOTYPE(Enemy)

	float speed = 200;
	float fireTimer = 3;
	float fireRate = 1;

	void OnCollision(class bacon::Actor* other);

private:
};