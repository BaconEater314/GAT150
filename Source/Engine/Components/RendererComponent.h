#pragma once
#include "GameEngine/Component.h"

namespace bacon {
	class RendererComponent : public Component {
	public:
		virtual void Draw(class Renderer& renderer) = 0;
	};
}