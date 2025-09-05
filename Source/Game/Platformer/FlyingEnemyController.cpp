#include "FlyingEnemyController.h"
#include "../GamePCH.h"

using namespace bacon;

FACTORY_REGISTER(FlyingEnemyController)

void FlyingEnemyController::Start() {
	m_rigidBody = owner->GetComponent<RigidBody>();
}

void FlyingEnemyController::Update(float dt) {

	// move towards player
	auto player = owner->scene->GetActorByName<Actor>("platformPlayer");
	if (player) {
		vec2 direction = player->transform.position - owner->transform.position;
		m_rigidBody->ApplyForce(direction.Normalized() * speed);
	}
}

void FlyingEnemyController::OnCollision(bacon::Actor* other) {
	other->dead = true;
	owner->dead = true;
}

void FlyingEnemyController::Read(const bacon::json::value_t& value) {
	Object::Read(value);

	JSON_READ(value, speed);
	JSON_READ(value, maxSpeed);
	JSON_READ(value, jump);
	JSON_READ(value, attackSpeed);
}