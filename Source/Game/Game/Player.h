#pragma once
#include "GameEngine/Component.h"

class Player : public bacon::Component {
public:
	Player() = default;
	/*Player(const bacon::Transform& transform) :
		Actor{ transform}
	{ }*/

	void Update(float dt) override;

	void OnCollision(class Actor* other);

public:
	float speed;
	float rotationRate;
	float fireRate = 0.3f;
	float fireTimer = 0.0f;

private:
};