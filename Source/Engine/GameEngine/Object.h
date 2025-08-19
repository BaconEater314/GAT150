#pragma once
#include "Core/Serializable.h"

#include <string>

namespace bacon {
	class Object : Serializable{
	public:
		Object() = default;
		virtual ~Object() = default;

		std::string name;
		bool active = true;

		void Read(const json::value_t& value) override;
	};
}