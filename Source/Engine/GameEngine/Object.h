#pragma once

namespace bacon {
	class Object {
	public:
		Object() = default;
		virtual ~Object() = default;

		std::string name;
		bool active = true;

	private:
	};
}