#pragma once
#include "GameEngine/Component.h"

namespace bacon {
	class AudioSource : public Component {
	public:
		std::string audioClipname;

		void Update(float dt) override;
		void Play();

		void Read(const json::value_t& value) override;
	};
}