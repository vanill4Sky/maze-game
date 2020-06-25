#pragma once

#include <SFML/Graphics.hpp>

#include "GameData.hpp"
#include "SplashState.hpp"

class Game
{
public:
	Game(int screenWidth, int screenHeight, std::string windowTitle);
	~Game();

private:
	/*	\opis metoda wywo³ywana po utworzeniu okna aplikacji
		zawiera g³ówn¹ pêtle gry */
	void Run();

	sf::Clock mClock; //pomiar d³ugoœci trwania jednej klatki
	GameDataRef mData = std::make_shared<GameData>(); //wskaŸnik do danych aplikacji

	const float TIME_SLICE{ 1.0f / 120.0f }; //czas trwania jednej klatki
};

