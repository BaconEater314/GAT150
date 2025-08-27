#pragma once
#include "Core/Time.h"
#include "Core/Singleton.h"
#include "Renderer/Renderer.h"
#include "Audio/AudioSystem.h"
#include "Input/InputSystem.h"
#include "Renderer/ParticleSystem.h"
#include "Resources/ResourceManager.h"
#include "Physics/Physics.h"

#include <memory>

namespace bacon {
	class Renderer;
	class AudioSystem;
	class InputSystem;
	class ParticleSystem;

	class Engine : public Singleton<Engine>{
	public:

		bool Initialize();
		void Kill();
		void Update();
		void Draw();
		
		Renderer& GetRenderer() { return *m_renderer; }
		InputSystem& GetInput() { return *m_input; }
		AudioSystem& GetAudio() { return *m_audio; }
		ParticleSystem& GetPS() { return *m_particleSystem; }
		Physics& GetPhysics() { return *m_physics; }
		Time& GetTime() { return m_time; }

	private:
		friend class Singleton;
		Engine() = default;

		Time m_time;

		std::unique_ptr<Renderer> m_renderer;
		std::unique_ptr<InputSystem> m_input;
		std::unique_ptr<AudioSystem> m_audio;
		std::unique_ptr<ParticleSystem> m_particleSystem;
		std::unique_ptr<Physics> m_physics;
	};

	inline Engine& GetEngine() { return Engine::Instance(); }
}