#include "GameRocket.h"
#include "Engine.h"
#include "GameEngine/Scene.h"
#include "Renderer/Renderer.h"
#include "Player.h"
#include "Core/Random.h"
#include "Renderer/ParticleSystem.h"

using namespace bacon;

void Rocket::Update(float dt) {
    vec2 force = vec2{ 1,0 }.Rotate(math::degToRad(transform.rotation)) * speed;
    velocity = force;

    //transform.position.x = math::wrap(transform.position.x, 0.0f, (float)GetEngine().GetRenderer().GetWidth());
    //transform.position.y = math::wrap(transform.position.y, 0.0f, (float)GetEngine().GetRenderer().GetHeight());

    float angle = transform.rotation + random::getReal(-60.0f, 60.0f);
    vec2 velocity = vec2{ 1,0 }.Rotate(math::degToRad(angle));
    velocity *= random::getReal(80.0f, 150.f);

    Particle particle;
    particle.position = transform.position;
    particle.velocity = random::onUnitCircle() * random::getReal(20.0f, 120.0f);
    particle.color = (tag == "enemy") ? vec3{ 0, 1, 1 } : vec3{ 1,1,0 };
    particle.lifespan = random::getReal(0.15f, 0.3f);
    GetEngine().GetPS().AddParticle(particle);

    Actor::Update(dt);
}

void Rocket::OnCollision(Actor* other){
    if (other->tag != tag) {
        dead = true;
    }
}
