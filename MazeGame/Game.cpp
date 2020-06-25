#include "Game.hpp"

Game::Game(int screenWidth, int screenHeight, std::string windowsTitle)
{
	mData->window.create(
		sf::VideoMode(screenWidth, screenHeight),
		windowsTitle,
		sf::Style::Close | sf::Style::Titlebar);
	mData->window.setFramerateLimit(60);
	mData->stateMachine.addState(std::make_unique<SplashState>(mData));

	Run();
}

Game::~Game()
{
}

void Game::Run()
{
	/* http://fabiensanglard.net/timer_and_framerate/index.php */

	float newTime;
	float frameTime;
	float currentTime = this->mClock.getElapsedTime().asSeconds();
	float accumulator = 0.0f;

	while (mData->window.isOpen())
	{
		mData->stateMachine.processStateChanges();

		newTime = mClock.getElapsedTime().asSeconds();
		frameTime = newTime - currentTime;

		if (frameTime > 0.2f)
		{
			frameTime = 0.2f;
		}

		currentTime = newTime;
		accumulator += frameTime;

		while (accumulator >= TIME_SLICE)
		{
			mData->stateMachine.getActiveState()->handleInput();
			mData->stateMachine.getActiveState()->update(TIME_SLICE);
			accumulator -= TIME_SLICE;
		}

		mData->stateMachine.getActiveState()->draw(TIME_SLICE);
	}
}
