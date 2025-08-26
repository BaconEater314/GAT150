#pragma once
#include "GameEngine/Component.h"

class Enemy : public bacon::Component, public bacon::ICollidable, public bacon::IObserver {
public:
	Enemy() = default;

	void Update(float dt) override;

	CLASS_PROTOTYPE(Enemy)

	void Start() override;

	float speed = 200;
	float fireTimer = 3;
	float fireRate = 1;
	bacon::RigidBody* m_rigidbody{ nullptr };

	void OnCollision(class bacon::Actor* other) override;
	void OnNotify(const bacon::Event& event) override;
};