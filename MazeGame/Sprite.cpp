#include "Sprite.hpp"

Sprite::Sprite(sf::Vector2<double> position, int textureId):
	mPosition(position), mTextureId(textureId)
{
}

Sprite::~Sprite()
{
}

sf::Vector2<double> const & Sprite::getPosition() const
{
	return mPosition;
}

int const & Sprite::getTextureId() const
{
	return mTextureId;
}