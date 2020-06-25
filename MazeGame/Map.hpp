#pragma once

#include <vector>
#include <array>
#include <stack>
#include <random>
#include <algorithm>
#include <utility>
#include <SFML/Graphics.hpp>

#include <iostream>

#include "Sprite.hpp"
#include "Values.hpp"

class Map
{
public:
	/*	\opis mapa tworzona jest w konstruktorze za pomoc algorytmu DFS,
		otrzymana plansza ma wymiary (mazeHeight * 2 + 1) na (mazeWidth * 2 + 1),
		na mapie umieszczane są równierz klucze i drzwi */
	Map(int mazeHeight, int mazeWidth);
	~Map();
	
	int getHeight() const;
	int getWidth() const;
	/*	\return stała referencja wektora zawierjącego wszystkie sprity umieszczone na mapie, 
		w tym przypadku maksymalnie 2 klucze */
	std::vector<Sprite> const& getSprites() const;
	/*	\return referencja wektora zawierjący wszystkie sprity umieszczone na mapie */
	std::vector<Sprite> & getSprites();

	/*	\return wartość kwadratu mapy o danych współrzędnych */
	int const& operator() (int column, int row) const;
	/* \return wartość kwadratu mapy o danych współrzędnych */
	int const& operator() (sf::Vector2i& coords) const;

private:
	const int mMazeHeight; 	//wysokość labiryntu liczona w komorach, 1  komora = 9 mniejszych kwadratów
	const int mMazeWidth; 	//szerokość labiryntu liczona w komorach
	const int mMapHeight; 	//wysokość mapy = mazeHeight * 2 + 1
	const int mMapWidth;  	//szerokość mapy =  mazeWidth * 2 + 1
	
	std::vector<int> mMap;	//tablica zawierająca mape, wartości komórek odpowiadają identyfikatorą tekstur
	std::vector<std::pair<sf::Vector2i, int> > mDeadEnds;	//tablica z ślepymi korytarzami
	std::vector<Sprite> mKeys;
};


