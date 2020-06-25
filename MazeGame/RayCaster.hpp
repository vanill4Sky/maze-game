#pragma once

#include <cmath>
#include <SFML/Graphics.hpp>
#include <algorithm>
#include <string>

#include "GameData.hpp"
#include "Player.hpp"
#include "Map.hpp"
#include "Values.hpp"

enum Side{ Vertical, Horizontal };

class RayCaster
{
public:
	RayCaster(GameDataRef data);
	~RayCaster();

	/*	\opis rysuje na ekranie oteksturowane ściany oraz sufit i podłogę z imitacją cieni */
	void drawWalls(const Player& player, const Map& map);
	/*	\opis dorysowuje sprity, które akurat widzi gracz; metoda nie wspiera nakładających się na siebie obiektów */
	void drawSprites(const Player& player, const Map& map);

private:
	GameDataRef mData;
	//bufor odległości każdego "paska" ściany od gracza
	std::vector<double> mZBuffer;
	//wszystkie tekstury wykorzystywane przez grę w jednej
	//takie rozwiązanie zwiększa wielokrotnie wydajność
	sf::Texture megaTexture;

	int const mScreenWidth;
	int const mScreenHeight;

	sf::Color const mGreyColor;
};

