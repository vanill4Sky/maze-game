#include "InputManager.hpp"


InputManager::InputManager()
{
}


InputManager::~InputManager()
{
}

bool InputManager::isSpriteClicked(sf::Sprite object, sf::Mouse::Button button, sf::RenderWindow & window)
{
	if (sf::Mouse::isButtonPressed(button))
	{
		//obiekt typu Rect to prostok¹t okalaj¹cy sprite
		sf::FloatRect tempRect(
			object.getPosition().x, object.getPosition().y,
			object.getGlobalBounds().width, object.getGlobalBounds().height);

		if (tempRect.contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window))))
		{
			return true;
		}
	}
	return false;
}

bool InputManager::isButtonClicked(Button& object, sf::Mouse::Button button, sf::RenderWindow& window)
{
	if (sf::Mouse::isButtonPressed(button))
	{
		//obiekt typu Rect to prostok¹t okalaj¹cy sprite
		sf::FloatRect tempRect(
			object.getPosition().x, object.getPosition().y,
			object.getGlobalBounds().width, object.getGlobalBounds().height);

		if(tempRect.contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window))))
		{
			return true;
		}
	}
	return false;
}

sf::Vector2i InputManager::getMousePosition(sf::RenderWindow & window)
{
	return sf::Mouse::getPosition(window);
}

void InputManager::updateKeyPressed(sf::Keyboard::Key key)
{
	mKeyPressed[key] = true;
}

void InputManager::updateKeyReleased(sf::Keyboard::Key key)
{
	mKeyPressed[key] = false;
}

const bool InputManager::isKeyPressed(sf::Keyboard::Key key) const
{
	if (mKeyPressed.count(key) == 0 || !mKeyPressed.at(key))
	{
		return false;
	}
	else
	{
		return true;
	}
}

void InputManager::restart()
{
	mKeyPressed.clear();
}
