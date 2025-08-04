#include "SpaceGame.h"
#include "Math/Vector2.h"
#include "Renderer/Model.h"
#include "GameEngine/Scene.h"
#include "Core/Random.h"
#include "Renderer/Renderer.h"
#include "Engine.h"
#include "Player.h"
#include "Enemy.h"
#include "GameEngine/Game.h"
#include "Input/InputSystem.h"
#include "GameData.h"
#include "Core/Time.h"
#include "GameEngine/Actor.h"
#include "Renderer/ParticleSystem.h"
#include "Audio/AudioSystem.h"

#include <vector>

using namespace bacon;

bool SpaceGame::Initialize() {
    m_scene = std::make_unique<bacon::Scene>(this);

    m_titleFont = std::make_shared<Font>();
    m_titleFont->Load("Surprise Valentine.ttf",128);

    m_uiFont = std::make_shared<Font>();
    m_uiFont->Load("Surprise Valentine.ttf", 48);

    m_titleText = std::make_unique<Text>(m_titleFont);
    m_scoreText = std::make_unique<Text>(m_uiFont);
    m_livesText = std::make_unique<Text>(m_uiFont);

    return true;
}

void SpaceGame::Update(float dt){
    switch (m_gameState){
    case SpaceGame::GameState::Initialize:
        m_gameState = GameState::Title;
        break;
    case SpaceGame::GameState::Title:
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
        std::shared_ptr<Model> model = std::make_shared<Model>(GameData::shipPoints, vec3{ 1,0,0 });
        Transform transform{ vec2{bacon::GetEngine().GetRenderer().GetWidth() * 0.5f,GetEngine().GetRenderer().GetHeight() * 0.5f},0,10 };
        auto player = std::make_unique<Player>(transform, model);
        player->speed = 750.0f;
        player->rotationRate = 180.0f;
        player->damping = 1.5f;
        player->name = "player";
        player->tag = "player";
        player->health = 3;

        m_scene->AddActor(std::move(player));
        m_gameState = GameState::Game;
    }
        break;

    case SpaceGame::GameState::Game:
    {
        m_enemySpawnTimer -= dt;
        if (m_enemySpawnTimer <= 0) {
            m_enemySpawnTimer = 3;

            SpawnEnemy();
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
            m_songTimer == 146;
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

        //create enemies
        std::shared_ptr<Model> enemyModel = std::make_shared<Model>(GameData::enemyPoints, vec3{ 1,1,0 });

        vec2 position = player->transform.position + random::onUnitCircle() * random::getReal(500.0f, 1000.0f);
        Transform transform{ position, random::getReal(0.0f,360.0f), 10};

        
        std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>(transform, enemyModel);
        enemy->damping = 1.5f;
        enemy->fireRate = 3;
        enemy->fireTimer = 5;
        enemy->speed = (random::GetRandomFloat() * 300) + 300;
        enemy->tag = "enemy";
        enemy->health = 1;
        m_scene->AddActor(std::move(enemy));
    }
}

void SpaceGame::SpawnDreadnought() {
    Player* player = m_scene->GetActorByName<Player>("player");
    if (player) {

        dreadFire = true;

        //create enemies
        std::shared_ptr<Model> dreadModel = std::make_shared<Model>(GameData::dreadnoughtPoints, vec3{ 1,0,0 });

        vec2 position = player->transform.position + random::onUnitCircle() * random::getReal(2000.0f, 2500.0f);
        Transform transform{ position, 0, 10 };


        std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>(transform, dreadModel);
        enemy->damping = 1.5f;
        enemy->fireRate = 0.25;
        enemy->fireTimer = 3;
        enemy->health = 5;
        enemy->speed = (random::GetRandomFloat() * 50) + 200;
        enemy->name = "dread";
        enemy->tag = "enemy";
        m_scene->AddActor(std::move(enemy));

        if (dreadFire) {
            dreadFire = false;
            //GetEngine().GetAudio().PlaySound("laser");
        }
    }
}

void SpaceGame::Kill() {

}