#pragma once
#include "RendererComponent.h"

namespace bacon {
	class SpriteRenderer : public RendererComponent{
	public:
		std::string textureName;

		void Update(float dt) override;
		void Draw(Renderer& renderer) override;

		void Read(const json::value_t& value) override;
	};
}