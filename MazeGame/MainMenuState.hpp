#pragma once

#include <array>

#include "Values.hpp"
#include "Button.hpp"
#include "State.hpp"
#include "GameData.hpp"
#include "ConfigurationState.hpp"
#include "HelpState.hpp"
#include "CreditsState.hpp"
#include "GameInitState.hpp"


const int MENU_OPTION_NUMBER{ 5 };
const std::array<std::string, MENU_OPTION_NUMBER> MENU_OPTION_TEXT =
{
	"KONIEC",
	"AUTOR",
	"POMOC",
	"USTAWIENIA",
	"NOWA GRA"
};
enum MenuOptionId
{
	End,
	Author,
	Help,
	Options,
	NewGame
};

class MainMenuState :
	public State
{
public:
	MainMenuState(GameDataRef data);
	~MainMenuState();

	void init();
	void handleInput();
	void update(float dt);
	void draw(float dt);

private:
	GameDataRef mData;

	sf::Sprite mBackground;
	sf::Sprite mTitle;
	std::vector<Button> mButtons;

};

