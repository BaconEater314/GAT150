#pragma once
#include "GameEngine/Component.h"

class Enemy : public bacon::Component {
public:
	Enemy() = default;
	/*Enemy(const bacon::Transform& transform) :
		Actor{ transform}
	{ }*/

	void Update(float dt) override;

	float speed = 200;
	float fireTimer = 3;
	float fireRate = 1;

	void OnCollision(class Actor* other);

private:
};