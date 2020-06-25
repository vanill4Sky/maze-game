#include "GameInitState.hpp"


GameInitState::GameInitState(GameDataRef data) : mData{ data }
{
}

GameInitState::~GameInitState()
{
}

void GameInitState::init()
{
	mData->assets.loadTexture("InitBackground", GAME_INIT_STATE_BACKGROUND_FILEPATH);
	
	mBackground.setTexture(mData->assets.getTexture("InitBackground"));

	for (int i = 0; i <	INIT_OPTIONS_NUMBER; i++)
	{
		mButtons.at(i) = Button(mData->assets.getTexture("Button"),
			mData->assets.getFont("Arial"),
			INIT_OPTION_TEXT.at(i));
		mButtons.at(i).setPosition(
			SCREEN_WIDTH / 2 - mButtons.at(i).getGlobalBounds().width / 2,
			SCREEN_HEIGHT - ((mButtons.at(i).getGlobalBounds().height + MARGIN_SMALL) * (i + 2)));
	}
}

void GameInitState::handleInput()
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
				case InitOptionId::Easy:
					mData->configs["InitTime"] = 60 * 3;
					break;
				case InitOptionId::Medium:
					mData->configs["InitTime"] = 60 * 2;
					break;
				case InitOptionId::Hard:
					mData->configs["InitTime"] = 60;
					break;
				}
				mData->stateMachine.addState(std::make_unique<GameState>(mData));
			}
		}
	}
}

void GameInitState::update(float dt)
{
}

void GameInitState::draw(float dt)
{
	mData->window.clear();

	mData->window.draw(mBackground);
	for (auto&& btn : mButtons)
		btn.draw(mData->window);

	mData->window.display();
}
