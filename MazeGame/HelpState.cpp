#include "HelpState.hpp"


HelpState::HelpState(GameDataRef data) : mData(data)
{
}

HelpState::~HelpState()
{
}

void HelpState::init()
{
	mData->assets.loadTexture("HelpBackground", HELP_BACKGROUND_FILEPATH);

	mBackground.setTexture(mData->assets.getTexture("HelpBackground"));
	mBackButton = Button(mData->assets.getTexture("Button"), mData->assets.getFont("Arial"), "POWRÓT");

	mBackButton.setPosition(MARGIN_SMALL, SCREEN_HEIGHT - (mBackButton.getGlobalBounds().height + MARGIN_SMALL));
}

void HelpState::handleInput()
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

void HelpState::update(float dt)
{
}

void HelpState::draw(float dt)
{
	mData->window.clear();

	mData->window.draw(mBackground);
	mBackButton.draw(mData->window);

	mData->window.display();
}
