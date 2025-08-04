#pragma once
#include <fmod.hpp>
#include <string>
#include <map>

namespace bacon {
	class AudioSystem {
	public:
		AudioSystem() = default;

		bool Initialize();
		void Kill();

		void Update();

		bool AddSound(const std::string& filename, const std::string& name = "");
		bool PlaySound(const std::string& name);

	private:
		bool CheckFMODResult(FMOD_RESULT result);
	private:
		FMOD::System* m_system{ nullptr };
		std::map<std::string, FMOD::Sound*> m_sounds;
	};
}
