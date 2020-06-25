#pragma once

#include "Values.hpp"
#include "GameData.hpp"
#include "Button.hpp"

class ConfigurationState :
	public State
{
public:
	ConfigurationState(GameDataRef data);
	~ConfigurationState();

	void init();
	void handleInput();
	void update(float dt);
	void draw(float dt);
	
private:
	GameDataRef mData;
	sf::Sprite mBackground;
	sf::Sprite mTitle;
	Button mBackButton;
	Button mIncrementButton;
	Button mDecrementButton;
	Button mCurrentSizeInfo;
	sf::Text mChangeSizeText;
	int mCurrentSize;
};

