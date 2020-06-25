#include "AssetManager.hpp"

AssetManager::AssetManager()
{
}

AssetManager::~AssetManager()
{
}

void AssetManager::loadTexture(std::string const name, std::string const fileName)
{
	sf::Texture texture;

	if (texture.loadFromFile(fileName))
	{
		mTextures[name] = texture;
	}
}

void AssetManager::loadFont(std::string const name, std::string const fileName)
{
	sf::Font font;

	if (font.loadFromFile(fileName))
	{
		mFonts[name] = font;
	}
}

sf::Texture const& AssetManager::getTexture(std::string const name) const
{
	return mTextures.at(name);
}

sf::Font const& AssetManager::getFont(std::string const name) const
{
	return mFonts.at(name);
}

