#include "PlatformerGame.h"
#include "../GamePCH.h"

using namespace bacon;

bool PlatformerGame::Initialize() {
	OBSERVER_ADD(player_dead);
	OBSERVER_ADD(lose_health);
	OBSERVER_ADD(add_points);

	m_scene = std::make_unique<bacon::Scene>(this);
	m_scene->Load("Scenes/prototype.json");
	m_scene->Load("Scenes/level.json");

	return true;
}

void PlatformerGame::Kill(){
	//
}

void PlatformerGame::Update(float dt) {
	switch (m_gameState)
	{
	case GameState::Initialize:
		m_gameState = GameState::StartRound;
		break;
	case GameState::Title:

		break;
	case GameState::StartGame:

		break;
	case GameState::StartRound:
		SpawnPlayer();
		SpawnEnemy();
		m_gameState = GameState::Game;
		break;
	case GameState::Game:

		break;
	case GameState::PlayerDead:

		break;
	case GameState::GameOver:

		break;
	default:
		break;
	}

	m_scene->Update(GetEngine().GetTime().GetDeltaTime());
}

void PlatformerGame::Draw(class bacon::Renderer& renderer) {
	m_scene->Draw(renderer);
	GetEngine().GetPS().Draw(renderer);
}

void PlatformerGame::SpawnPlayer() {
	auto player = Instantiate("platformPlayer");
	//player->transform.position = vec2{ random::getReal(0.0f,1080.0f),0.0f };
	m_scene->AddActor(std::move(player));
}

void PlatformerGame::SpawnEnemy() {
	auto enemy = Instantiate("platformEnemy");
	//player->transform.position = vec2{ random::getReal(0.0f,1080.0f),0.0f };
	m_scene->AddActor(std::move(enemy));
}

void PlatformerGame::OnPlayerDeath() {

}

void PlatformerGame::OnNotify(const Event& event) {

}
