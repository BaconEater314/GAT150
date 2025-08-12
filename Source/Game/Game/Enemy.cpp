#include "Enemy.h"
#include "GameRocket.h"
#include "GameData.h"

using namespace bacon;

void Enemy::Update(float dt){

    Actor* player = scene->GetActorByName("player");

    bool playerSeen = false;

    if (player) {
        vec2 direction{ 0,0 };
        direction = player->transform.position - transform.position;
        
        direction = direction.Normalized();
        vec2 forward = vec2{ 1,0 }.Rotate(math::degToRad(transform.rotation));

        float angle = vec2::SignedAngleBetween(forward,direction);
        angle = math::sign(angle);
        transform.rotation += math::radToDeg(angle * dt * 5);

        angle = math::radToDeg(vec2::AngleBetween(forward, direction));
        playerSeen = angle < 30;
    }


    vec2 force = vec2{1,0}.Rotate(math::degToRad(transform.rotation)) * speed;
    auto rb = GetComponent<RigidBody>();
    if (rb) rb->velocity += force * dt;

    transform.position.x = math::wrap(transform.position.x, 0.0f, (float)GetEngine().GetRenderer().GetWidth());
    transform.position.y = math::wrap(transform.position.y, 0.0f, (float)GetEngine().GetRenderer().GetHeight());

    fireTimer -= dt;
    if (fireTimer <= 0 && playerSeen) {
        fireTimer = fireRate;

        Transform transform{ this->transform.position, this->transform.rotation, 2.0f };
        auto rocket = std::make_unique<Rocket>(transform);
        rocket->speed = 1500.0f;
        rocket->lifespan = 1.5f;
        rocket->name = "rocket";
        rocket->tag = "enemy";

        auto spriteRenderer = std::make_unique<SpriteRenderer>();
        spriteRenderer->textureName = "Images/krill.png";
        rocket->AddComponent(std::move(spriteRenderer));

        auto rb = std::make_unique<RigidBody>();
        rocket->AddComponent(std::move(rb));

        auto collider = std::make_unique<CircleCollider2D>();
        collider->radius = 10;
        rocket->AddComponent(std::move(collider));

        scene->AddActor(std::move(rocket));
    }



    Actor::Update(dt);
}

void Enemy::OnCollision(Actor* other) {
    if (other->tag != tag) {
        int rand = random::getInt(0, 2);
        if (rand == 1) {
            GetEngine().GetAudio().PlaySound("impact");
        } else {
            GetEngine().GetAudio().PlaySound("other_impact");
        }
        health -= 1;
        if (health <= 0) {
            dead = true;
            if (scene->GetActorByName("dread")) {
                scene->GetGame()->AddPoints(300);
            }
            else {
                scene->GetGame()->AddPoints(100);
            }
        }
        for (int i = 0; i < 100; i++) {
            Particle particle;
            particle.position = transform.position;
            particle.velocity = random::onUnitCircle() * random::getReal(10.0f, 200.0f);
            particle.color = vec3{ 1, 1, 1 };
            particle.lifespan = 2;
            GetEngine().GetPS().AddParticle(particle);
        }
    }
}
