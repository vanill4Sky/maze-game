#pragma once

#include <map>
#include <SFML/Graphics.hpp>

#include "Button.hpp"

class InputManager
{
public:
	InputManager();
	~InputManager();
	
	/* 	\param object - sprawdzany sprite
		\param button - kod klawisza myszy, którego wciśnięcie jest sprawdzane
		\param window - aktywne okno */
	bool isSpriteClicked(sf::Sprite object, sf::Mouse::Button button, sf::RenderWindow& window);
	/* 	\param object - sprawdzany przycisk
		\param button - kod klawisza myszy, którego wciśnięcie jest sprawdzane
		\param window - aktywne okno */
	bool isButtonClicked(Button& object, sf::Mouse::Button button, sf::RenderWindow& window);
	sf::Vector2i getMousePosition(sf::RenderWindow& window);
	/*	\opis metoda aktualizuje słownik mKeyPressed, 
		kod klawisza podanego jako argument zostaje do niego wpisany
		z wartością true (klawisz wciśnięty) 
		\param key - kod wciśniętego klawisza */
	void updateKeyPressed(sf::Keyboard::Key key);
	/*	\opis metoda aktualizuje słownik mKeyPressed, 
		kod klawisza podanego jako argument zostaje do niego wpisany
		z wartością false (klawisz zwolniony) 
		\param key - kod zwolnionego klawisza */
	void updateKeyReleased(sf::Keyboard::Key key);
	const bool isKeyPressed(sf::Keyboard::Key key) const;
	void restart();

private:
	std::map<sf::Keyboard::Key, bool> mKeyPressed;
};

