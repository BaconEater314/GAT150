#pragma once

namespace bacon {
	class MeshRenderer : public Component {
	public:
		std::string meshName;

		CLASS_PROTOTYPE(MeshRenderer)

		void Update(float dt) override;
		void Draw(Renderer& renderer);
	};
}