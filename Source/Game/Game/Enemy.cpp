#include "Enemy.h"
#include "GameRocket.h"
#include "GameData.h"
#include "../GamePCH.h"

using namespace bacon;

FACTORY_REGISTER(Enemy)

void Enemy::Update(float dt){
    /*
    Actor* player = owner->scene->GetActorByName<Actor>("player");

    bool playerSeen = false;

    if (player) {
        vec2 direction{ 0,0 };
        direction = player->transform.position - owner->transform.position;
        
        direction = direction.Normalized();
        vec2 forward = vec2{ 1,0 }.Rotate(math::degToRad(owner->transform.rotation));

        float angle = vec2::SignedAngleBetween(forward,direction);
        angle = math::sign(angle);
        owner->transform.rotation += math::radToDeg(angle * dt * 5);

        angle = math::radToDeg(vec2::AngleBetween(forward, direction));
        playerSeen = angle < 30;
    }


    vec2 force = vec2{1,0}.Rotate(math::degToRad(owner->transform.rotation)) * speed;
    auto rb = owner->GetComponent<RigidBody>();
    if (rb) rb->velocity += force * dt;

    owner->transform.position.x = math::wrap(owner->transform.position.x, 0.0f, (float)GetEngine().GetRenderer().GetWidth());
    owner->transform.position.y = math::wrap(owner->transform.position.y, 0.0f, (float)GetEngine().GetRenderer().GetHeight());

    fireTimer -= dt;
    if (fireTimer <= 0 && playerSeen) {
        fireTimer = fireRate;

        Transform transform{ this->owner->transform.position, this->owner->transform.rotation, 2.0f };
        auto rocket = std::make_unique<Actor>(transform);
        rocket->speed = 1500.0f;
        owner->lifespan = 1.5f;
        rocket->name = "rocket";
        owner->tag = "enemy";

        auto spriteRenderer = std::make_unique<SpriteRenderer>();
        spriteRenderer->textureName = "Sprites/missile-2.png";
        owner->AddComponent(std::move(spriteRenderer));

        auto rb = std::make_unique<RigidBody>();
        owner->AddComponent(std::move(rb));

        auto collider = std::make_unique<CircleCollider2D>();
        collider->radius = 10;
        owner->AddComponent(std::move(collider));

        owner->scene->AddActor(std::move(rocket));
    }



    Actor::Update(dt);*/
}

void Enemy::OnCollision(Actor* other) {
    if (owner->tag != owner->tag) {
        int rand = random::getInt(0, 2);
        if (rand == 1) {
            GetEngine().GetAudio().PlaySound("impact");
        } else {
            GetEngine().GetAudio().PlaySound("other_impact");
        }
        owner->m_health -= 1;
        if (owner->m_health <= 0) {
            owner->dead = true;
            if (owner->scene->GetActorByName("dread")) {
                owner->scene->GetGame()->AddPoints(300);
            }
            else {
                owner->scene->GetGame()->AddPoints(100);
            }
        }
        for (int i = 0; i < 100; i++) {
            Particle particle;
            particle.position = owner->transform.position;
            particle.velocity = random::onUnitCircle() * random::getReal(10.0f, 200.0f);
            particle.color = vec3{ 1, 1, 1 };
            particle.lifespan = 2;
            GetEngine().GetPS().AddParticle(particle);
        }
    }
}
