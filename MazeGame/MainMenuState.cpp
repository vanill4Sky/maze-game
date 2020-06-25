#include "MainMenuState.hpp"
#include "iostream"

MainMenuState::MainMenuState(GameDataRef data) : mData(data)
{
	mData->configs["MapSize"] = DEFAULT_MAP_SIZE;
}

MainMenuState::~MainMenuState()
{
}

void MainMenuState::init()
{
	mData->assets.loadTexture("MainMenuBackground", MAIN_MENU_BACKGROUND_FILEPATH);
	mData->assets.loadTexture("GameTitle", GAME_TITLE_FILEPATH);
	mData->assets.loadTexture("Button", BUTTON_FILEPATH);
	mData->assets.loadFont("Arial", FONT_ARIAL_FILEPATH);

	mBackground.setTexture(mData->assets.getTexture("MainMenuBackground"));

	mTitle.setTexture(mData->assets.getTexture("GameTitle"));
	mTitle.setPosition((SCREEN_WIDTH / 2) - (mTitle.getGlobalBounds().width / 2), MARGIN_SMALL);

	/* buttons initialization */
	for (int i = 0; i < MENU_OPTIONS; i++)
	{
		mButtons.push_back(
			Button(mData->assets.getTexture("Button"), mData->assets.getFont("Arial"), MENU_OPTION_TEXT[i]));

		mButtons.at(i).setPosition(
			SCREEN_WIDTH / 2 - mButtons.at(0).getGlobalBounds().width / 2,
			SCREEN_HEIGHT - ((mButtons.at(i).getGlobalBounds().height + MARGIN_SMALL) * (i + 1)));
	}
}

void MainMenuState::handleInput()
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
				case MenuOptionId::NewGame:
					mData->stateMachine.addState(std::make_unique<GameInitState>(mData), false);
					break;
				case MenuOptionId::Options:
					mData->stateMachine.addState(std::make_unique<ConfigurationState>(mData), false);
					break;
				case MenuOptionId::Help:
					mData->stateMachine.addState(std::make_unique<HelpState>(mData), false);
					break;
				case MenuOptionId::Author:
					mData->stateMachine.addState(std::make_unique<CreditsState>(mData), false);
					break;
				case MenuOptionId::End:
					mData->window.close();
					break;
				}
			}
		}
	}
}

void MainMenuState::update(float dt)
{
}

void MainMenuState::draw(float dt)
{
	mData->window.clear();

	mData->window.draw(mBackground);
	mData->window.draw(mTitle);
	for (auto&& button : mButtons)
		button.draw(mData->window);

	mData->window.display();
}
