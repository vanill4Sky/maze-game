#pragma once

#include <map>
#include <SFML/Graphics.hpp>

class AssetManager
{
public:
	AssetManager();
	~AssetManager();

	/*	\opis wczytuje plik z teksturą z dysku do pamięci
		\param name - identyfikator tekstury 
		\param fileName - nazwa pliku z teksturą */
	void loadTexture(std::string const name, std::string const fileName);
	/*	\opis wczytuje plik z fontem z dysku do pamięci
		\param name - identyfikator fontu 
		\param fileName - nazwa pliku z fontem */
	void loadFont(std::string const name, std::string const fileName);
	/*	\param name - identyfikator fontu 
		\return referencja do obiektu fontu o danej nazwie */
	sf::Texture const& getTexture(std::string const name) const;
	/*	\param name - identyfikator fontu 
		\return referencja do obiektu fontu o danej nazwie */
	sf::Font const& getFont(std::string const name) const;

private:
	std::map<std::string, sf::Texture> mTextures;
	std::map<std::string, sf::Font> mFonts;
};

