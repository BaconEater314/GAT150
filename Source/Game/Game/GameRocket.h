#pragma once
#include "GameEngine/Component.h"

class Rocket : public bacon::Component {
public:
	Rocket() = default;
	/*Rocket(const bacon::Transform& transform) :
		Actor{ transform}
	{}*/

	void Update(float dt) override;

	float speed = 200;

	void OnCollision(class Actor* other);

private:
};