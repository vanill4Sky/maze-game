#pragma once

#include "Values.hpp"
#include "GameData.hpp"

class HUD
{
public:
	HUD();
	/*	\param timeLimit - limit czasu
		\param keysAll - liczba wszystkich kluczy na mapie */
	HUD(GameDataRef data, int timeLimit, int keysPickedUp, int keysAll);
	~HUD();
	
	void draw() const;
	/*	\opis aktualizuje pozostały do końca gry czas */
	void updateTime(int const& seconds);
	/*	\opis aktualizuje liczbę pozostałych do zebrania kluczy */
	void updateKeys(int const& keysPickedUp);

private:
	GameDataRef mData;
	sf::Text mTimeText;
	int mKeysAll;
	sf::Text mKeyText;
};

