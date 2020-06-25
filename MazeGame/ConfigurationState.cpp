#include "ConfigurationState.hpp"


ConfigurationState::ConfigurationState(GameDataRef data) : mData(data), mCurrentSize(data->configs.at("MapSize"))
{
}

ConfigurationState::~ConfigurationState()
{
	mData->configs["MapSize"] = mCurrentSize;
}

void ConfigurationState::init()
{
	mData->assets.loadTexture("ConfigurationBackground", CONFIGURATION_BACKGROUND_FILEPATH);
	mData->assets.loadTexture("ConfigurationTitle", CONFIGURATION_TITLE_FILEPATH);
	mData->assets.loadTexture("SquareButton", SQUARE_BUTTON_FILEPATH);

	mBackground.setTexture(mData->assets.getTexture("ConfigurationBackground"));
	mTitle.setTexture(mData->assets.getTexture("ConfigurationTitle"));

	/* setting texture for all buttons */
	mBackButton = Button{ mData->assets.getTexture("Button"), mData->assets.getFont("Arial"), "POWRÓT" };
	mCurrentSizeInfo = Button{ mData->assets.getTexture("Button"), mData->assets.getFont("Arial"), std::to_string(mCurrentSize) };
	mIncrementButton = Button{ mData->assets.getTexture("SquareButton"), mData->assets.getFont("Arial"), "+" };
	mDecrementButton = Button{ mData->assets.getTexture("SquareButton"), mData->assets.getFont("Arial"), "-" };

	mChangeSizeText = sf::Text(CHANGE_MAP_SIZE_TEXT, mData->assets.getFont("Arial"));

	/*setting position of all sprites*/
	mTitle.setPosition((SCREEN_WIDTH / 2) - (mTitle.getGlobalBounds().width / 2), MARGIN_SMALL);

	mBackButton.setPosition(MARGIN_SMALL, SCREEN_HEIGHT - (mBackButton.getGlobalBounds().height + MARGIN_SMALL));
	mIncrementButton.setPosition(
		SCREEN_WIDTH / 2 - mIncrementButton.getGlobalBounds().width - mCurrentSizeInfo.getGlobalBounds().width / 2 - MARGIN_SMALL,
		SCREEN_HEIGHT / 2 - mIncrementButton.getGlobalBounds().height / 2);
	mDecrementButton.setPosition(
		SCREEN_WIDTH / 2 + mCurrentSizeInfo.getGlobalBounds().width / 2 + MARGIN_SMALL,
		SCREEN_HEIGHT / 2 - mDecrementButton.getGlobalBounds().height / 2);
	mCurrentSizeInfo.setPosition(
		SCREEN_WIDTH / 2 - mCurrentSizeInfo.getGlobalBounds().width / 2,
		SCREEN_HEIGHT / 2 - mCurrentSizeInfo.getGlobalBounds().height / 2);

	/* setting position of the changeSizeText 
	   at first origin of the object is being set to the center, 
	   this operation makes position setting much more simpler */
	sf::FloatRect textRect{ mChangeSizeText.getLocalBounds() };

	mChangeSizeText.setOrigin(
		textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);
	mChangeSizeText.setPosition(
		SCREEN_WIDTH / 2,
		SCREEN_HEIGHT / 2 - mCurrentSizeInfo.getGlobalBounds().height);
}

void ConfigurationState::handleInput()
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
		if (mData->input.isButtonClicked(mIncrementButton, sf::Mouse::Left, mData->window))
		{
			mCurrentSize++;
		}
		if (mData->input.isButtonClicked(mDecrementButton, sf::Mouse::Left, mData->window))
		{
			mCurrentSize--;
		}
	}
}

void ConfigurationState::update(float dt)
{
	if (mCurrentSize > MAX_MAP_SIZE)
		mCurrentSize = MAX_MAP_SIZE;
	else if (mCurrentSize < MIN_MAP_SIZE)
		mCurrentSize = MIN_MAP_SIZE;

	mCurrentSizeInfo.setLabel(std::to_string(mCurrentSize));
}

void ConfigurationState::draw(float dt)
{
	mData->window.clear();

	mData->window.draw(mBackground);
	mData->window.draw(mTitle);
	mData->window.draw(mChangeSizeText);
	mBackButton.draw(mData->window);
	mIncrementButton.draw(mData->window);
	mDecrementButton.draw(mData->window);
	mCurrentSizeInfo.draw(mData->window);

	mData->window.display();
}
