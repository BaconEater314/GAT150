#include "EnginePCH.h"

namespace bacon {
	void bacon::Object::Read(const json::value_t& value) {
		JSON_READ(value, name);
		JSON_READ(value, active);
	}
}