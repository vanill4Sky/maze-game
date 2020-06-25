#include "GameOverState.hpp"


GameOverState::GameOverState(GameDataRef data, bool isWinner) :
	mData(data), mIsWinner(isWinner)
{
}

GameOverState::~GameOverState()
{
}

void GameOverState::init()
{
	if (mIsWinner)
		mData->assets.loadTexture("GameOverTitle", GAMEOVER_WIN_TITLE_FILEPATH);
	else
		mData->assets.loadTexture("GameOverTitle", GAMEOVER_LOSE_TITLE_FILEPATH);

	mBackground.setTexture(mData->assets.getTexture("MainMenuBackground"));
	mGameOverTitle.setTexture(mData->assets.getTexture("GameOverTitle"));
	mExitButton = Button{ mData->assets.getTexture("Button"), mData->assets.getFont("Arial"), "KONIEC" };
	mRetryButton = Button{ mData->assets.getTexture("Button"), mData->assets.getFont("Arial"), "POWRÓT" };

	if (mIsWinner)
		mGameOverInfo = sf::Text(L"Gratulacje! Niestety ksiê¿niczka jest w innym labiryncie.", mData->assets.getFont("Arial"));
	else
		mGameOverInfo = sf::Text(L"Œlepa uliczka, koniec gry!", mData->assets.getFont("Arial"));

	mGameOverTitle.setPosition((SCREEN_WIDTH / 2) - (mGameOverTitle.getGlobalBounds().width / 2), MARGIN_SMALL);
	mExitButton.setPosition(
		SCREEN_WIDTH - mExitButton.getGlobalBounds().width - MARGIN_SMALL,
		SCREEN_HEIGHT - (mExitButton.getGlobalBounds().height + MARGIN_SMALL));
	mRetryButton.setPosition(
		MARGIN_SMALL,
		SCREEN_HEIGHT - (mRetryButton.getGlobalBounds().height + MARGIN_SMALL));
	mGameOverInfo.setOrigin(0, 0);
	mGameOverInfo.setPosition(
		SCREEN_WIDTH / 2 - mGameOverInfo.getGlobalBounds().width / 2,
		SCREEN_HEIGHT / 2 - mGameOverInfo.getGlobalBounds().height / 2);
}

void GameOverState::handleInput()
{
	sf::Event event;

	while (mData->window.pollEvent(event))
	{
		if (sf::Event::Closed == event.type)
		{
			mData->window.close();
		}

		if (mData->input.isButtonClicked(mExitButton, sf::Mouse::Left, mData->window))
		{
			mData->window.close();
		}
		if (mData->input.isButtonClicked(mRetryButton, sf::Mouse::Left, mData->window))
		{
			mData->stateMachine.removeState();
		}
	}
}

void GameOverState::update(float dt)
{
}

void GameOverState::draw(float dt)
{
	mData->window.clear();

	mData->window.draw(mBackground);
	mData->window.draw(mGameOverTitle);
	mData->window.draw(mGameOverInfo);
	mRetryButton.draw(mData->window);
	mExitButton.draw(mData->window);

	mData->window.display();
}
