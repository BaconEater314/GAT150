#include "Player.h"
#include "GameData.h"
#include "GameRocket.h"
#include "SpaceGame.h"
#include "../GamePCH.h"

using namespace bacon;

FACTORY_REGISTER(Player)

void Player::Update(float dt){
    float rotate = 0;
    if (GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_A)) rotate = -1;
    if (GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_D)) rotate = 1;

    owner->transform.rotation += (rotate * rotationRate) * dt;
    
    //thrust
    float thrust = 0;
    if (GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_W)) {
        thrust = 1;
        Particle particle;
        particle.position = owner->transform.position - 10;
        particle.velocity = vec2{ random::getReal(-200.0f,200.0f),random::getReal(-200.0f,200.0f) };
        particle.color = { 1,1,1 };
        particle.lifespan = 2;
        GetEngine().GetPS().AddParticle(particle);
    }
    if (GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_S)) { 
        thrust = -1; 
        Particle particle;
        particle.position = owner->transform.position - 10;
        particle.velocity = vec2{ random::getReal(-200.0f,200.0f),random::getReal(-200.0f,200.0f) };
        particle.color = { 1,1,1 };
        particle.lifespan = 2;
        GetEngine().GetPS().AddParticle(particle);
    }

    vec2 direction{ 1,0 };
    vec2 force = direction.Rotate(math::degToRad(owner->transform.rotation)) * thrust * speed;
    auto rb = owner->GetComponent<RigidBody>();
    if (rb) rb->velocity += force * dt;

    owner->transform.position.x = math::wrap(owner->transform.position.x, 0.0f, (float)GetEngine().GetRenderer().GetWidth());
    owner->transform.position.y = math::wrap(owner->transform.position.y, 0.0f, (float)GetEngine().GetRenderer().GetHeight());
    /*
    //check fire key pressed 
    fireTimer -= dt;

    if (GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_SPACE) && fireTimer <= 0) {
        fireTimer = fireRate;
        Transform transform{ this->owner->transform.position, this->owner->transform.rotation, 2.0f};
        auto rocket = std::make_unique<Rocket>(transform);
        rocket->speed = 1500.0f;
        rocket->lifespan = 1.5f;
        rocket->name = "rocket";
        rocket->tag = "player";

        auto spriteRenderer = std::make_unique<SpriteRenderer>();

        spriteRenderer->textureName = "Sprites/missile-1.png";
        rocket->AddComponent(std::move(spriteRenderer));

        auto rb = std::make_unique<RigidBody>();
        rocket->AddComponent(std::move(rb));

        auto collider = std::make_unique<CircleCollider2D>();
        collider->radius = 10;
        rocket->AddComponent(std::move(collider));

        GetEngine().GetAudio().PlaySound(*Resources().Get<AudioClip>("Sounds/pew.wav", GetEngine().GetAudio()).get());

        scene->AddActor(std::move(rocket));
    }

    Actor::Update(dt);
    */
}

void Player::OnCollision(Actor* other) {
    if (other->tag != owner->tag) {
        owner->m_health -= 1;
        EVENT_NOTIFY_DATA(lose_health, 1);
        owner->scene->GetGame()->LoseHealth(1);
    }
    if (owner->m_health <= 0) {
        EVENT_NOTIFY(player_dead);
        owner->dead = true;
        dynamic_cast<SpaceGame*>(owner->scene->GetGame())->OnPlayerDeath();
    }
}

void Player::Read(const bacon::json::value_t& value){
    Object::Read(value);

    JSON_READ(value, speed);
    JSON_READ(value, rotationRate);
    JSON_READ(value, fireRate);
}