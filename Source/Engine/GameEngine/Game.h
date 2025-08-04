#pragma once
#include "../Renderer/Renderer.h"

#include <memory>

namespace bacon {
	class Game {
	public:
		Game() = default;

		virtual bool Initialize() = 0;
		virtual void Kill() = 0;
		virtual void Update(float dt) = 0;
		virtual void Draw(class bacon::Renderer& renderer) = 0;

		void AddPoints(int points) { m_score += points; }
		int GetPoints() const { return m_score; }

		void SetLive(int lives) { m_lives = lives; }
		int GetLive() const { return m_lives; }

	protected:
		int m_score{ 0 };
		int m_lives{ 0 } ;

	public:
		std::unique_ptr<class Scene> m_scene;
	};
}