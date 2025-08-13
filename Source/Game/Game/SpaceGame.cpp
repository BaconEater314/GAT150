#include "../GamePCH.h"
#include "GameData.h"
#include "SpaceGame.h"
#include "Engine.h"
#include "Player.h"
#include "Enemy.h"

using namespace bacon;

bool SpaceGame::Initialize() {
    m_scene = std::make_unique<bacon::Scene>(this);

    m_titleText = std::make_unique<Text>(Resources().GetWithID<Font>("title_font", "Fonts/Surprise Valentine.ttf", 128.0f));
    m_scoreText = std::make_unique<Text>(Resources().GetWithID<Font>("ui_font", "Fonts/Surprise Valentine.ttf", 48.0f));
    m_livesText = std::make_unique<Text>(Resources().GetWithID<Font>("ui_font", "Fonts/Surprise Valentine.ttf", 48.0f));
    m_healthText = std::make_unique<Text>(Resources().GetWithID<Font>("ui_font", "Fonts/Surprise Valentine.ttf", 48.0f));

    return true;
}

void SpaceGame::Update(float dt){
    switch (m_gameState){
    case SpaceGame::GameState::Initialize:
        m_gameState = GameState::Title;
        break;
    case SpaceGame::GameState::Title:
        m_scene->RemoveAllActors();
        if (GetEngine().GetInput().GetKeyPressed(SDL_SCANCODE_SPACE)) {
            m_gameState = GameState::StartGame;
        }
        break;
    case SpaceGame::GameState::StartGame:
        m_score = 0;
        m_lives = 3;
        dreadAlive = false;
        playGameOver = true;
        m_songTimer = 0;
        
        m_gameState = GameState::StartRound;
        break;
    case SpaceGame::GameState::StartRound:
    {
        m_scene->RemoveAllActors();

        if (dreadAlive) {
            SpawnDreadnought();
        }
        //create player
        Transform transform{ vec2{bacon::GetEngine().GetRenderer().GetWidth() * 0.5f,GetEngine().GetRenderer().GetHeight() * 0.5f},0,1 };
        auto player = std::make_unique<Player>(transform);
        player->speed = 750.0f;
        player->rotationRate = 180.0f;
        player->name = "player";
        player->tag = "player";
        player->m_health = 3;
        m_scene->GetGame()->LoseHealth(-3);

        auto spriteRenderer = std::make_unique<SpriteRenderer>();
        spriteRenderer->textureName = "Sprites/large_grey_01.png";
        player->AddComponent(std::move(spriteRenderer));

        auto rb = std::make_unique<RigidBody>();
        rb->damping = 1.5f;
        player->AddComponent(std::move(rb));

        auto collider = std::make_unique<CircleCollider2D>();
        collider->radius = 50;
        player->AddComponent(std::move(collider));

        m_scene->AddActor(std::move(player));
        m_gameState = GameState::Game;
    }
        break;

    case SpaceGame::GameState::Game:
    {
        m_enemySpawnTimer -= dt;
        if (m_score > 2000) {
            m_enemySpawnTimer -= dt;
        }
        if (m_score > 5000) {
            m_enemySpawnTimer -= dt;
        }
        if (m_score > 10000) {
            m_enemySpawnTimer -= dt;
        }
        if (m_enemySpawnTimer <= 0) {
            m_enemySpawnTimer = 3;
            SpawnEnemy();
        }
        if (m_score % 2000 == 0 && m_lives < 3 && m_score > 0) {
            m_lives += 1;
        }
        if (m_score % 1000 == 0 && m_score > 0 && !dreadAlive) {
            dreadAlive = true;
            SpawnDreadnought();
        }

        if (m_score > 5000) {
            if (m_score % 500 == 0 && !dreadAlive) {
                dreadAlive = true;
                SpawnDreadnought();
            }
        }
        if (m_scene->GetActorByName("dread") == nullptr) dreadAlive = false;

        if (m_songTimer == 0) {
            //GetEngine().GetAudio().PlaySound("music");
            m_songTimer = 146;
        } else {
            m_songTimer -= 1;
        }
    }
        break;
    case SpaceGame::GameState::PlayerDead:
        m_stateTimer -= dt;
        if (m_stateTimer <= 0) {
            m_lives--;
            if (m_lives <= 0) {
                m_gameState = GameState::GameOver;
                m_stateTimer = 3;
            }
            else m_gameState = GameState::StartRound;

        }

        break;
    case SpaceGame::GameState::GameOver:
        m_stateTimer -= dt;
        if (playGameOver) {
            GetEngine().GetAudio().PlaySound("game_over");
            playGameOver = false;
        }
        if(m_stateTimer <= 0) m_gameState = GameState::Title;
        break;
    default:
        break;
    }

    if (GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_Q)) {
        GetEngine().GetTime().setTimeScale(0.5f);
    } else {
        GetEngine().GetTime().setTimeScale(1);
    }

    m_scene->Update(GetEngine().GetTime().GetDeltaTime());
}

void SpaceGame::Draw(class Renderer& renderer){
    GetEngine().GetRenderer().DrawTexture(*Resources().Get<Texture>("Sprites/space.png", GetEngine().GetRenderer()).get(), 0, 0, 0, 1);


    if (m_gameState == GameState::Title) {
        m_titleText->Create(renderer, "BACON GAME", vec3{ 1,0,0 });
        m_titleText->Draw(renderer, 400, 600);
    }
    if (m_gameState == GameState::GameOver) {
        m_titleText->Create(renderer, "GAME OVER", vec3{ 1,0,0 });
        m_titleText->Draw(renderer, 600, 600);
    }

    m_scoreText->Create(renderer, "SCORE: " + std::to_string(m_score), {1,1,1});
    m_scoreText->Draw(renderer, (float)20, (float)20);

    m_livesText->Create(renderer, "LIVES: " + std::to_string(m_lives), {1,1,1});
    m_livesText->Draw(renderer, (float)renderer.GetWidth() - 150, (float)20);

    m_healthText->Create(renderer, "HEALTH: " + std::to_string(m_health), { 1,1,1 });
    m_healthText->Draw(renderer, ((float)renderer.GetWidth()/2)-100, (float)20);

    m_scene->Draw(renderer);

    GetEngine().GetPS().Draw(renderer);
}

void SpaceGame::OnPlayerDeath(){
    m_gameState = GameState::PlayerDead;
    m_stateTimer = 2;
}

void SpaceGame::SpawnEnemy(){
    Player* player = m_scene->GetActorByName<Player>("player");
    if (player) {

        vec2 position = player->transform.position + random::onUnitCircle() * random::getReal(500.0f, 1000.0f);
        Transform transform{ position, random::getReal(0.0f,360.0f), 2.0f};

        //creating an enemy
        std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>(transform);
        enemy->fireRate = 3;
        enemy->fireTimer = 5;
        enemy->speed = (random::GetRandomFloat() * 300) + 300;
        enemy->tag = "enemy";
        enemy->m_health = 1;

        auto spriteRenderer = std::make_unique<SpriteRenderer>();
        int rand = random::getInt(0, 5);
        if(rand == 0) spriteRenderer->textureName = "Sprites/purple_01.png";
        else if(rand == 1) spriteRenderer->textureName = "Sprites/purple_02.png";
        else if(rand == 2) spriteRenderer->textureName = "Sprites/purple_03.png";
        else if(rand == 3) spriteRenderer->textureName = "Sprites/purple_04.png";
        else if(rand == 4) spriteRenderer->textureName = "Sprites/purple_05.png";
        else if(rand == 5) spriteRenderer->textureName = "Sprites/purple_06.png";

        enemy->AddComponent(std::move(spriteRenderer));

        auto rb = std::make_unique<RigidBody>();
        rb->damping = 1.5f;
        enemy->AddComponent(std::move(rb));

        auto collider = std::make_unique<CircleCollider2D>();
        collider->radius = 50;
        enemy->AddComponent(std::move(collider));

        m_scene->AddActor(std::move(enemy));
    }
}

void SpaceGame::SpawnDreadnought() {
    Player* player = m_scene->GetActorByName<Player>("player");
    if (player) {

        dreadFire = true;

        vec2 position = player->transform.position + random::onUnitCircle() * random::getReal(2000.0f, 2500.0f);
        Transform transform{ position, 0, 5 };

        //creating a Dreadnought
        std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>(transform);
        enemy->fireRate = 0.25;
        enemy->fireTimer = 3;
        enemy->m_health = 5;
        enemy->speed = (random::GetRandomFloat() * 50) + 200;
        enemy->name = "dread";
        enemy->tag = "enemy";

        auto spriteRenderer = std::make_unique<SpriteRenderer>();
        spriteRenderer->textureName = "Sprites/red_06.png";
        enemy->AddComponent(std::move(spriteRenderer));

        auto rb = std::make_unique<RigidBody>();
        rb->damping = 1.5f;
        enemy->AddComponent(std::move(rb));

        auto collider = std::make_unique<CircleCollider2D>();
        collider->radius = 50;
        enemy->AddComponent(std::move(collider));

        m_scene->AddActor(std::move(enemy));

        if (dreadFire) {
            dreadFire = false;
            //GetEngine().GetAudio().PlaySound("laser");
        }
    }
}

void SpaceGame::Kill() {

}