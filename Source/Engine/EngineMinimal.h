#pragma once

//core
#include "Core/File.h"
#include "Core/Logger.h"
#include "Core/Random.h"
#include "Core/Singleton.h"
#include "Core/StringHelper.h"
#include "Core/Time.h"
#include "Core/Json.h"
#include "Core/Factory.h"

//GameEngine
#include "GameEngine/Actor.h"
#include "GameEngine/Game.h"
#include "GameEngine/Object.h"
#include "GameEngine/Scene.h"

//Math
#include "Math/Math.h"
#include "Math/Transform.h"
#include "Math/Vector2.h"
#include "Math/Vector3.h"

//resources
#include "Resources/Resource.h"
#include "Resources/ResourceManager.h"

//third party libraries
#include <fmod.hpp>
#include <fmod_errors.h>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>

//standard library
#include <string>
#include <iostream>
#include <fstream>
#include <memory>
#include <vector>
#include <map>
#include <list>
#include <random>
#include <algorithm>
#include <cmath>
#include <filesystem>