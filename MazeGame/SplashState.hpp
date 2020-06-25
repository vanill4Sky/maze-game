#pragma once

#include "Values.hpp"
#include "State.hpp"
#include "GameData.hpp"
#include "MainMenuState.hpp"

class SplashState :
	public State
{
public:
	SplashState(GameDataRef data);
	~SplashState();

	void init();

	void handleInput();
	void update(float dt);
	void draw(float dt);

private:
	GameDataRef mData;
	sf::Clock mTimer;
	sf::Sprite mBackground;
};

