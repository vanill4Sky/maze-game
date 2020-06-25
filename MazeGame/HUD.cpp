#include "HUD.hpp"

HUD::HUD()
{
}

HUD::HUD(GameDataRef data, int timeLimit, int keysPickedUp, int keysAll):
	mData{ data }, 
	mTimeText{ "CZAS: " + std::to_string(timeLimit), data->assets.getFont("Beef'd") },
	mKeyText{ "KLUCZE: " + std::to_string(keysPickedUp) + "/" + std::to_string(keysAll), data->assets.getFont("Beef'd") },
	mKeysAll{ keysAll }
{
	mTimeText.setOrigin(0, 0);
	mTimeText.setPosition(0, MARGIN_SMALL);
	mTimeText.setFillColor(sf::Color::White);

	mKeyText.setOrigin(0, 0);
	mKeyText.setPosition(mData->window.getSize().x - mKeyText.getGlobalBounds().width - MARGIN_SMALL, MARGIN_SMALL);
	mKeyText.setFillColor(sf::Color::White);
}

HUD::~HUD()
{
}

void HUD::draw() const
{
	mData->window.draw(mTimeText);
	mData->window.draw(mKeyText);
}

void HUD::updateTime(int const& seconds)
{
	mTimeText.setString("CZAS: " + std::to_string(seconds));
}

void HUD::updateKeys(int const& keysPickedUp)
{
	mKeyText.setString("KLUCZE: " + std::to_string(keysPickedUp) + "/" + std::to_string(mKeysAll));
}

