#pragma once
#include "Core/Time.h"

#include <memory>

namespace bacon {
	class Renderer;
	class AudioSystem;
	class InputSystem;
	class ParticleSystem;

	class Engine {
	public:
		Engine() = default;

		bool Initialize();
		void Kill();
		void Update();
		void Draw();
		
		Renderer& GetRenderer() { return *m_renderer; }
		InputSystem& GetInput() { return *m_input; }
		AudioSystem& GetAudio() { return *m_audio; }
		ParticleSystem& GetPS() { return *m_particleSystem; }
		Time& GetTime() { return m_time; }

	private:
		Time m_time;

		std::unique_ptr<Renderer> m_renderer;

		std::unique_ptr<InputSystem> m_input;

		std::unique_ptr<AudioSystem> m_audio;

		std::unique_ptr<ParticleSystem> m_particleSystem;
	};

	Engine& GetEngine();
}