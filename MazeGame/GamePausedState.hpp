#pragma once

#include <SFML/Graphics.hpp>
#include <array>

#include "State.hpp"
#include "GameData.hpp"
#include "Values.hpp"
#include "Button.hpp"
#include "MainMenuState.hpp"

const int PAUSE_OPTIONS_NUMBER{ 3 };
enum OptionId { Exit, ReturnToMenu, Resume};
const std::array<const std::string, PAUSE_OPTIONS_NUMBER> PAUSE_OPTION_TEXT
{
	"KONIEC",
	"MENU",
	"WZNOWIENIE"
};

class GamePausedState :
	public State
{
public:
	GamePausedState(GameDataRef data);
	~GamePausedState();

	void init();
	void handleInput();
	void update(float dt);
	void draw(float dt);

private:
	sf::Sprite mBackground;
	std::array<Button, PAUSE_OPTIONS_NUMBER> mButtons;
	GameDataRef mData;
};

