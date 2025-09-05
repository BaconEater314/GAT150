#include "PlayerController.h"
#include "../GamePCH.h"

using namespace bacon;

FACTORY_REGISTER(PlayerController)

void PlayerController::Start(){
	m_rigidBody = owner->GetComponent<RigidBody>();
}

void PlayerController::Update(float dt){
	vec2 velocity = m_rigidBody->GetVelocty();

	float dir = 0;
	if (GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_A)) dir = -1;
	if (GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_D)) dir = 1;

	if (dir != 0) {
		velocity.x += dir * 1000 * dt;
		//m_rigidBody->ApplyForce(vec2{ 1 * dir * 2000, 0 });
	}

	if (GetEngine().GetInput().GetKeyPressed(SDL_SCANCODE_SPACE)) {
		velocity.y = -jump;
		//m_rigidBody->ApplyForce(vec2{0,-1 * jump * 5});
	}

	auto spriteRenderer = owner->GetComponent<SpriteRenderer>();
	if (spriteRenderer) {
		if (math::fabs(velocity.x != 0.1f)) {
			spriteRenderer->flipH = (velocity.x < 0);
		}
	}
		
	velocity.x = math::min(velocity.x, 2000.0f);
	m_rigidBody->SetVelocity(velocity);
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
