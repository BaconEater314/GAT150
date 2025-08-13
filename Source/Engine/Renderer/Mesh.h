#pragma once

namespace bacon {
	class Mesh {
		Mesh() = default;

		bool Load(const std::string& filename);
	};
}