#pragma once
#include "GameEngine/Component.h"

class Rocket : public bacon::Component {
public:
	Rocket() = default;

	CLASS_PROTOTYPE(Rocket)

	void Update(float dt) override;

	float speed = 200;

	void OnCollision(class bacon::Actor* other);

private:
};