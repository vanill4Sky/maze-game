#pragma once

#include <SFML/Graphics.hpp>
#include <string>

unsigned const int DEFAULT_CHARACTER_SIZE{ 30 };

class Button
{
public:
	Button();
	Button(const sf::Texture& texture, const sf::Font& font, std::string label, 
		unsigned const int characterSize = DEFAULT_CHARACTER_SIZE, sf::Color textColor = sf::Color::White);
	Button(const sf::Texture& texture, const sf::Font& font, std::wstring label,
		unsigned const int characterSize = DEFAULT_CHARACTER_SIZE, sf::Color textColor = sf::Color::White);
	~Button();

	void setTexture(sf::Texture const& texture);
	void setFont(sf::Font const& font);
	void setLabel(std::string const label);
	void setPosition(float const x, float const y);
	void setPosition(sf::Vector2f const& position);
	void setCharacterSize(unsigned int const size);

	sf::FloatRect getGlobalBounds() const;
	const sf::Vector2f& getPosition() const;

	void draw(sf::RenderWindow& window);

private:
	sf::Sprite mBox;
	sf::Text mText;
};