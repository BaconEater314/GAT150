#pragma once
#include "Core/StringHelper.h"
#include "Resource.h"
#include "Core/Singleton.h"

#include <string>
#include <map>
#include <iostream>

namespace bacon {
	class ResourceManager : public Singleton<ResourceManager> {
	public:
		template<typename T, typename ... Args>
		res_t<T> Get(const std::string& name, Args&& ... args);

		template<typename T, typename ... Args>
		res_t<T> GetWithID(const std::string& id, const std::string& name, Args&& ... args);

	private:
		friend class Singleton<ResourceManager>;
		ResourceManager() = default;

		std::map <std::string, res_t<Resource>> m_resources;
	};

	template <typename T, typename ... Args>
	inline res_t<T> ResourceManager::Get(const std::string& name, Args&& ... args) { return GetWithID<T>(name,name, std::forward<Args>(args)...); }

	template <typename T, typename ... Args>
	inline res_t<T> ResourceManager::GetWithID(const std::string& id, const std::string& name, Args&& ... args) {
		std::string key = ToLower(id);

		auto iter = m_resources.find(key);
		//check if exists
		if (iter != m_resources.end()) {
			//get value into iterator
			auto base = iter->second;
			//cast to data type T
			auto resource = std::dynamic_pointer_cast<T>(base);
			//check if cast is successful
			if (resource == nullptr) {
				std::cerr << "Resource type mismatch: " << key << std::endl;
				return res_t<T>();
			}
			//return resource
			return resource;
		}

		//load resource
		res_t<T> resource = std::make_shared<T>();
		if (resource->Load(name, std::forward<Args>(args)...) == false) {
			std::cerr << "Could not load resource: " << name << std::endl;
			return res_t<T>();
		}

		//add resource to resource manager
		m_resources[key] = resource;

		return resource;
	}

	inline ResourceManager& Resources() { return ResourceManager::Instance(); }
}