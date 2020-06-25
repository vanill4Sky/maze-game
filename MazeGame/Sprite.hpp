#pragma once

#include <SFML/Graphics.hpp>

class Sprite
{
public:
	Sprite(sf::Vector2<double> position, int textureId);
	~Sprite();

	sf::Vector2<double> const& getPosition() const;
	int const& getTextureId() const;

private:
	sf::Vector2<double> mPosition;
	int mTextureId;
};