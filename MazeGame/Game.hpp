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
	/*	\opis metoda wywo�ywana po utworzeniu okna aplikacji
		zawiera g��wn� p�tle gry */
	void Run();

	sf::Clock mClock; //pomiar d�ugo�ci trwania jednej klatki
	GameDataRef mData = std::make_shared<GameData>(); //wska�nik do danych aplikacji

	const float TIME_SLICE{ 1.0f / 120.0f }; //czas trwania jednej klatki
};

