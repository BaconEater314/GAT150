#include "Model.h"
#include "Renderer.h"

namespace bacon {
	void Model::Draw(class Renderer& renderer, const vec2& position, float rotation, float scale) {

		//check if points empty, if so, return
		if (m_points.empty()) { return; }

		renderer.SetColor(m_color.r, m_color.g, m_color.b);

		for (int i = 0; i < m_points.size()-1; i++) {
			vec2 p1 = (m_points[i].Rotate(math::degToRad(rotation)) * scale) + position;
			vec2 p2 = (m_points[i + 1].Rotate(math::degToRad(rotation)) * scale) + position;

			renderer.DrawLine(p1.x, p1.y, p2.x, p2.y);
		}
	}
	void Model::Draw(Renderer& renderer, const Transform& transform){
		Draw(renderer, transform.position, transform.rotation, transform.scale);
	}

	void Model::CalculateRadius(){
		m_radius = 0;
		for (auto& point : m_points) {
			float length = point.Length();
			if (length > m_radius) m_radius = length;
		}
	}
}