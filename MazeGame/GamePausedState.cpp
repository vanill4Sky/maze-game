#include "GamePausedState.hpp"


GamePausedState::GamePausedState(GameDataRef data) : mData(data)
{
}

GamePausedState::~GamePausedState()
{
}

void GamePausedState::init()
{
	mData->assets.loadTexture("GamePausedBackground", GAME_PAUSED_STATE_BACKGROUND_FILEPATH);

	mBackground.setTexture(mData->assets.getTexture("GamePausedBackground"));
	mBackground.setPosition(
		SCREEN_WIDTH / 2 - mBackground.getGlobalBounds().width / 2,
		SCREEN_HEIGHT / 2 - mBackground.getGlobalBounds().height / 2);

	for (int i = 0; i < PAUSE_OPTIONS_NUMBER; i++)
	{
		mButtons.at(i) = Button(mData->assets.getTexture("Button"), 
								mData->assets.getFont("Arial"), 
								PAUSE_OPTION_TEXT.at(i));
		mButtons.at(i).setPosition(
			SCREEN_WIDTH / 2 - mButtons.at(i).getGlobalBounds().width / 2,
			SCREEN_HEIGHT - ((mButtons.at(i).getGlobalBounds().height + MARGIN_SMALL) * (i + 2)));
	}
}

void GamePausedState::handleInput()
{
	sf::Event event;

	while (mData->window.pollEvent(event))
	{
		if (sf::Event::Closed == event.type)
		{
			mData->window.close();
		}

		for (size_t i = 0; i < mButtons.size(); i++)
		{
			if (mData->input.isButtonClicked(mButtons.at(i), sf::Mouse::Left, mData->window))
			{
				switch (i)
				{
				case OptionId::Resume:
					mData->configs["GoBackToMainMenu"] = false;
					mData->stateMachine.removeState();
					break;
				case OptionId::ReturnToMenu:
					mData->configs["GoBackToMainMenu"] = true;
					mData->stateMachine.removeState();
					break;
				case OptionId::Exit:
					mData->window.close();
					break;
				}
			}
		}
	}
}

void GamePausedState::update(float dt)
{
}

void GamePausedState::draw(float dt)
{
	mData->window.draw(mBackground);
	for (auto&& btn : mButtons)
		btn.draw(mData->window);

	mData->window.display();
}
