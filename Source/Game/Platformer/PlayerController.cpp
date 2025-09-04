#include "PlayerController.h"
#include "../GamePCH.h"

using namespace bacon;

FACTORY_REGISTER(PlayerController)

void PlayerController::Start(){
	m_rigidBody = owner->GetComponent<RigidBody>();
}

void PlayerController::Update(float dt){
	float dir = 0;
	if (GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_A)) dir = -1;
	if (GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_D)) dir = 1;

	if (dir != 0) {
		m_rigidBody->ApplyForce(vec2{ 1 * dir * 2000, 0 });
	}

	if (GetEngine().GetInput().GetKeyPressed(SDL_SCANCODE_SPACE)) {
		m_rigidBody->ApplyForce(vec2{0,-1 * jump * 250});
	}

	auto spriteRenderer = owner->GetComponent<SpriteRenderer>();
	if (spriteRenderer) {
		if (math::fabs(m_rigidBody->velocity.x != 0.1f)) {
			spriteRenderer->flipH = (m_rigidBody->velocity.x < 0);
		}

	}
}

void PlayerController::OnCollision(bacon::Actor* other){
	//std::cout << other->name << std::endl;
}

void PlayerController::Read(const bacon::json::value_t& value){
	Object::Read(value);

	JSON_READ(value, speed);
	JSON_READ(value, maxSpeed);
	JSON_READ(value, jump);
	JSON_READ(value, attackSpeed);
}
