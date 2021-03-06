#pragma once

#include "State.hpp"
#include "Values.hpp"
#include "GameData.hpp"
#include "Button.hpp"


class HelpState :
	public State
{
public:
	HelpState(GameDataRef data);
	~HelpState();

	void init();
	void handleInput();
	void update(float dt);
	void draw(float dt);

private:
	GameDataRef mData;

	sf::Sprite mBackground;
	Button mBackButton;
};

