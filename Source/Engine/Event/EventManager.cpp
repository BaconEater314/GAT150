#include "EnginePCH.h"
#include "Core/StringHelper.h"

namespace bacon {
	void EventManager::AddObserver(const Event::id_t id, IObserver& observer){
		m_observers[ToLower(id)].push_back(&observer);
	}

	void EventManager::RemoveObserver(IObserver& observer){
		IObserver* observerPtr = &observer;

		//iterate through all event types
		for (auto& eventType : m_observers) {
			//get list of observers for event type
			auto observers = eventType.second;

			//remove matching observers for this event type
			std::erase_if(observers, [observerPtr](auto observer) {
				return (observer == observerPtr);
			});
		}
	}

	void EventManager::Notify(const Event& event){
		//find observers of event
		auto iter = m_observers.find(ToLower(event.id));
		if (iter != m_observers.end()) {
			//get observers of event
			auto& observers = iter->second;
			for (auto observer : observers) {
				observer->OnNotify(event);
			}
		}
		else {
			Logger::Warning("Could not find event: {}", event.id);
		}
	}

}