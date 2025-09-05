#include "Pickup.h"
#include "../GamePCH.h"
#include "PlatformerGame.h"

using namespace bacon;

FACTORY_REGISTER(Pickup)

void Pickup::Start() {
	m_rigidBody = owner->GetComponent<RigidBody>();
}

void Pickup::Update(float dt) {
	//
}

void Pickup::OnCollision(bacon::Actor* other) {
	if (compare(other->tag, "player")) {
		owner->dead = true;
	}
}

void Pickup::Read(const bacon::json::value_t& value) {
	Object::Read(value);
}