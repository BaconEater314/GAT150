#include "GameRocket.h"
#include "Player.h"
#include "../GamePCH.h"

using namespace bacon;

FACTORY_REGISTER(Player)

void Rocket::Update(float dt) {
    vec2 force = vec2{ 1,0 }.Rotate(math::degToRad(owner->transform.rotation)) * speed;
    auto rb = owner->GetComponent<RigidBody>();
    if (rb) rb->velocity = force;

    float angle = owner->transform.rotation + random::getReal(-60.0f, 60.0f);
    vec2 velocity = vec2{ 1,0 }.Rotate(math::degToRad(angle));
    velocity *= random::getReal(80.0f, 150.f);

    Particle particle;
    particle.position = owner->transform.position;
    particle.velocity = random::onUnitCircle() * random::getReal(20.0f, 120.0f);
    particle.color = (tag == "enemy") ? vec3{ 0, 1, 1 } : vec3{ 1, 0.5, 0 };
    particle.lifespan = random::getReal(0.15f, 0.3f);
    GetEngine().GetPS().AddParticle(particle);

    Actor::Update(dt);
}

void Rocket::OnCollision(Actor* other){
    if (other->tag != tag) {
        dead = true;
    }
}
