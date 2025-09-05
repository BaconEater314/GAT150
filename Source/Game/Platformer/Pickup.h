#pragma once

#include "GameEngine/Component.h"
#include "Physics/Collidable.h"

class Pickup : public bacon::Component, public bacon::ICollidable {
public:
	Pickup() = default;

	CLASS_PROTOTYPE(Pickup)

	void Start() override;
	void Update(float dt) override;
	void OnCollision(class bacon::Actor* other) override;

	void Read(const bacon::json::value_t& value) override;

	bacon::RigidBody* m_rigidBody{ nullptr };
};