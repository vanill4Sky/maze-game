#include "CreditsState.hpp"

CreditsState::CreditsState(GameDataRef data) : mData(data)
{
}

CreditsState::~CreditsState()
{
}

void CreditsState::init()
{
	mData->assets.loadTexture("CreditsBackground", CREDITS_BACKGROUND_FILEPATH);

	mBackground.setTexture(mData->assets.getTexture("CreditsBackground"));
	mBackButton = Button(mData->assets.getTexture("Button"), mData->assets.getFont("Arial"), "POWRÓT");

	mBackButton.setPosition(MARGIN_SMALL, SCREEN_HEIGHT - (mBackButton.getGlobalBounds().height + MARGIN_SMALL));
}

void CreditsState::handleInput()
{
	sf::Event event;

	while (mData->window.pollEvent(event))
	{
		if (sf::Event::Closed == event.type)
		{
			mData->window.close();
		}

		if (mData->input.isButtonClicked(mBackButton, sf::Mouse::Left, mData->window))
		{
			mData->stateMachine.removeState();
		}
	}
}

void CreditsState::update(float dt)
{
}

void CreditsState::draw(float dt)
{
	mData->window.clear();

	mData->window.draw(mBackground);
	mBackButton.draw(mData->window);

	mData->window.display();
}
