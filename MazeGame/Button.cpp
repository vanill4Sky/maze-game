#include "Button.hpp"

Button::Button()
{
}

Button::Button(const sf::Texture& texture, const sf::Font& font, std::string label,
	unsigned const int characterSize, sf::Color textColor)
{
	mBox.setTexture(texture);

	mText.setFont(font);
	mText.setString(label);
	mText.setCharacterSize(characterSize);
	mText.setFillColor(textColor);
	mText.setStyle(sf::Text::Bold);
}

Button::Button(const sf::Texture& texture, const sf::Font& font, std::wstring label,
	unsigned const int characterSize, sf::Color textColor)
{
	mBox.setTexture(texture);

	mText.setFont(font);
	mText.setString(label);
	mText.setCharacterSize(characterSize);
	mText.setFillColor(textColor);
	mText.setStyle(sf::Text::Bold);
}

Button::~Button()
{
}

void Button::setTexture(sf::Texture const& texture)
{
	mBox.setTexture(texture);
}

void Button::setFont(sf::Font const& font)
{
	mText.setFont(font);
}

void Button::setLabel(std::string const label)
{
	mText.setString(label);
}

void Button::setPosition(float const x, float const y)
{
	mBox.setPosition(x, y);

	sf::FloatRect textRect{ mText.getLocalBounds() };
	/* centring the origin */
	mText.setOrigin(
		textRect.left + textRect.width / 2.0f, 
		textRect.top + textRect.height / 2.0f);
	mText.setPosition(
		x + mBox.getGlobalBounds().width / 2, 
		y + mBox.getGlobalBounds().height / 2);
}

void Button::setPosition(sf::Vector2f const& position)
{
	this->setPosition(position.x, position.y);
}

void Button::setCharacterSize(unsigned int const size)
{
	mText.setCharacterSize(size);
}

sf::FloatRect Button::getGlobalBounds() const
{
	return mBox.getGlobalBounds();
}

const sf::Vector2f & Button::getPosition() const
{
	return mBox.getPosition();
}

void Button::draw(sf::RenderWindow& window)
{
	window.draw(mBox);
	window.draw(mText);
}
