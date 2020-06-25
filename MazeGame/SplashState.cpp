#include "SplashState.hpp"

SplashState::SplashState(GameDataRef data) : mData(data)
{
}


SplashState::~SplashState()
{
}

void SplashState::init()
{
	mData->assets.loadTexture("SplashStateBackground", SPLASH_STATE_BACKGROUND_FILEPATH);

	mBackground.setTexture(mData->assets.getTexture("SplashStateBackground"));
}

void SplashState::handleInput()
{
	sf::Event event;

	while (mData->window.pollEvent(event))
	{
		if (sf::Event::Closed == event.type)
		{
			mData->window.close();
		}
	}
}

void SplashState::update(float dt)
{
	if (mTimer.getElapsedTime().asSeconds() > SPLASH_STATE_SHOW_TIME)
	{
		mData->stateMachine.addState(std::make_unique<MainMenuState>(mData));
	}
}

void SplashState::draw(float dt)
{
	mData->window.clear(sf::Color{ 0x54, 0x54, 0x54, 0xff });

	mData->window.draw(mBackground);

	mData->window.display();
}
