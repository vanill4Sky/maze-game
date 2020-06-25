#pragma once

#include "State.hpp"
#include "Values.hpp"
#include "GameData.hpp"
#include "Button.hpp"

class GameOverState :
	public State
{
public:
	GameOverState(GameDataRef data, bool isWinner);
	~GameOverState();

	void init();
	void handleInput();
	void update(float dt);
	void draw(float dt);

private:
	GameDataRef mData;
	sf::Sprite mBackground;
	sf::Sprite mGameOverTitle;
	Button mExitButton;
	Button mRetryButton;
	sf::Text mGameOverInfo;
	bool mIsWinner;
};

