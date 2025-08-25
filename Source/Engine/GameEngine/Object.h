#pragma once
#include "Core/Serializable.h"

#include <string>

#define CLASS_PROTOTYPE(classname) virtual std::unique_ptr<Object> Clone() { return std::make_unique<classname>(*this); }

namespace bacon {
	class Object : ISerializable{
	public:
		Object() = default;
		virtual ~Object() = default;

		std::string name;
		bool active = true;

		virtual std::unique_ptr<Object> Clone() = 0;

		void Read(const json::value_t& value) override;
	};
}