#pragma once

#include <memory>
#include <map>

#include "StateMachine.hpp"
#include "AssetManager.hpp"
#include "InputManager.hpp"

struct GameData
{
	StateMachine stateMachine;
	sf::RenderWindow window;
	AssetManager assets;
	InputManager input;
	std::map<std::string, int> configs;
};

using GameDataRef = std::shared_ptr<GameData>;
