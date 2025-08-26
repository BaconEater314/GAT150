#include "Observer.h"

namespace bacon {
	IObserver::~IObserver() {
		EventManager::Instance().RemoveObserver(*this);
	}
}