#include "Player.h"
#include "GameData.h"
#include "GameRocket.h"
#include "SpaceGame.h"
#include "../GamePCH.h"

using namespace bacon;

void Player::Update(float dt){

    float rotate = 0;
    if (GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_A)) rotate = -1;
    if (GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_D)) rotate = 1;

    transform.rotation += (rotate * rotationRate) * dt;
    
    //thrust
    float thrust = 0;
    if (GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_W)) {
        thrust = 1;
        Particle particle;
        particle.position = transform.position - 10;
        particle.velocity = vec2{ random::getReal(-200.0f,200.0f),random::getReal(-200.0f,200.0f) };
        particle.color = { 1,1,1 };
        particle.lifespan = 2;
        GetEngine().GetPS().AddParticle(particle);
    }
    if (GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_S)) { 
        thrust = -1; 
        Particle particle;
        particle.position = transform.position - 10;
        particle.velocity = vec2{ random::getReal(-200.0f,200.0f),random::getReal(-200.0f,200.0f) };
        particle.color = { 1,1,1 };
        particle.lifespan = 2;
        GetEngine().GetPS().AddParticle(particle);
    }

    vec2 direction{ 1,0 };
    vec2 force = direction.Rotate(math::degToRad(transform.rotation)) * thrust * speed;
    auto rb = GetComponent<RigidBody>();
    if (rb) rb->velocity += force * dt;

    transform.position.x = math::wrap(transform.position.x, 0.0f, (float)GetEngine().GetRenderer().GetWidth());
    transform.position.y = math::wrap(transform.position.y, 0.0f, (float)GetEngine().GetRenderer().GetHeight());

    //check fire key pressed 
    fireTimer -= dt;

    if (GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_SPACE) && fireTimer <= 0) {
        fireTimer = fireRate;
        Transform transform{ this->transform.position, this->transform.rotation, 2.0f};
        auto rocket = std::make_unique<Rocket>(transform);
        rocket->speed = 1500.0f;
        rocket->lifespan = 1.5f;
        rocket->name = "rocket";
        rocket->tag = "player";

        auto spriteRenderer = std::make_unique<SpriteRenderer>();
        spriteRenderer->textureName = "Images/krill.png";
        rocket->AddComponent(std::move(spriteRenderer));

        auto rb = std::make_unique<RigidBody>();
        rocket->AddComponent(std::move(rb));

        auto collider = std::make_unique<CircleCollider2D>();
        collider->radius = 10;
        rocket->AddComponent(std::move(collider));

        GetEngine().GetAudio().PlaySound(*Resources().Get<AudioClip>("pew", GetEngine().GetAudio()).get());

        scene->AddActor(std::move(rocket));
    }

    Actor::Update(dt);

}

void Player::OnCollision(Actor* other) {
    if (other->tag != tag) {
        dead = true;
        dynamic_cast<SpaceGame*>(scene->GetGame())->OnPlayerDeath();
    }
}
