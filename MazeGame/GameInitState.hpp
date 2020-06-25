#pragma once

#include "State.hpp"
#include "GameData.hpp"
#include "Values.hpp"
#include "GameState.hpp"

const int INIT_OPTIONS_NUMBER{ 3 };
enum InitOptionId { Hard, Medium, Easy };
const std::array<const std::wstring, INIT_OPTIONS_NUMBER> INIT_OPTION_TEXT
{
	L"TRUDNY",
	L"ŒREDNI",
	L"£ATWY"
};

class GameInitState :
	public State
{
public:
	GameInitState(GameDataRef data);
	~GameInitState();

	void init();
	void handleInput();
	void update(float dt);
	void draw(float dt);

private:
	GameDataRef mData;
	sf::Sprite mBackground;
	std::array<Button, INIT_OPTIONS_NUMBER> mButtons;
};

