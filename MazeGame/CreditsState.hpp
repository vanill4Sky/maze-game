#pragma once

#include "Values.hpp"
#include "State.hpp"
#include "GameData.hpp"
#include "Button.hpp"

class CreditsState :
	public State
{
public:
	CreditsState(GameDataRef data);
	~CreditsState();

	void init();
	void handleInput();
	void update(float dt);
	void draw(float dt);


private:
	GameDataRef mData;

	sf::Sprite mBackground;
	Button mBackButton;
};

