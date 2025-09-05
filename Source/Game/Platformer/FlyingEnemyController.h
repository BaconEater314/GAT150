#pragma once

#include "GameEngine/Component.h"
#include "Physics/Collidable.h"

class FlyingEnemyController : public bacon::Component, public bacon::ICollidable {
public:
	FlyingEnemyController() = default;

	CLASS_PROTOTYPE(FlyingEnemyController)

	void Start() override;
	void Update(float dt) override;
	void OnCollision(class bacon::Actor* other) override;

	void Read(const bacon::json::value_t& value) override;

	float speed = 0;
	float maxSpeed = 0;
	float jump = 0;
	float attackSpeed = 0;
	float attackTimer = 0.0f;

	bacon::RigidBody* m_rigidBody{ nullptr };
};
