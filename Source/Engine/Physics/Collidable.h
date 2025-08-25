#pragma once

namespace bacon {
	class ICollidable {
	public:
		virtual ~ICollidable() = default;

		virtual void OnCollision(class Actor* other) = 0;
	};
}