#include "EnemyController.h"
#include "../GamePCH.h"

using namespace bacon;

FACTORY_REGISTER(EnemyController)

void EnemyController::Start() {
	m_rigidBody = owner->GetComponent<RigidBody>();
}

void EnemyController::Update(float dt) {

	float dir = 0;

	// move towards player
	auto player = owner->scene->GetActorByName<Actor>("platformPlayer");
	if (player) {
		if (player->transform.position.x < owner->transform.position.x) dir = -1;
		else dir = 1;
	}

	if (dir != 0) {
		m_rigidBody->ApplyForce(vec2{ 1, 0 } *dir * 500);
	}
}

void EnemyController::OnCollision(bacon::Actor* other) {
}

void EnemyController::Read(const bacon::json::value_t& value) {
	Object::Read(value);

	JSON_READ(value, speed);
	JSON_READ(value, maxSpeed);
	JSON_READ(value, jump);
	JSON_READ(value, attackSpeed);
}