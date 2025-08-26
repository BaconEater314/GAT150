#include "Enemy.h"
#include "GameRocket.h"
#include "GameData.h"
#include "../GamePCH.h"

using namespace bacon;

FACTORY_REGISTER(Enemy)

void Enemy::Start() {
    OBSERVER_ADD("player_dead");

    m_rigidbody = owner->GetComponent<RigidBody>();
    fireTimer = fireRate;
}

void Enemy::Update(float dt){
    Actor* enemy = owner->scene->GetActorByName<Actor>("enemy");

    bool playerSeen = false;

    if (enemy) {
        vec2 direction{ 0,0 };
        direction = enemy->transform.position - owner->transform.position;
        
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

        auto rocket = Instantiate("rocket", owner->transform);
        Transform transform{ this->owner->transform.position, this->owner->transform.rotation, 2.0f };
        rocket->tag = "enemy";

        owner->scene->AddActor(std::move(rocket));
    }
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
                EVENT_NOTIFY_DATA(add_points, 300);
            }
            else {
                EVENT_NOTIFY_DATA(add_points, 300);
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

void Enemy::OnNotify(const bacon::Event& event){
    if (compare(event.id, "player_dead")) owner->dead = true;
}
