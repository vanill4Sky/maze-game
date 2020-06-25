#include "GameState.hpp"

GameState::GameState(GameDataRef data) :
	mData(data),
	mPlayer(PLAYER_INITIAL_POSITION, PLAYER_INITIAL_DIRECTION, CAMERA_PLANE_INITIAL),
	mMap(data->configs.at("MapSize"), data->configs.at("MapSize")),
	mRayCaster(data),
	mLimitTime(data->configs.at("InitTime")),
	mElapsedTime(0)
{
}

GameState::~GameState()
{
}

void GameState::init()
{
	mData->assets.loadFont("Beef'd", FONT_BEEF_D_FILEPATH);

	mTimer.restart();
	mHud = HUD(mData, mLimitTime, mPlayer.getKeyCounter(), mMap.getSprites().size());

	mData->input.restart();
}

void GameState::handleInput()
{
	sf::Event event;

	while (mData->window.pollEvent(event))
	{
		switch (event.type)
		{
			case sf::Event::Closed:
				mData->window.close();
				break;
			case sf::Event::KeyPressed:
				mData->input.updateKeyPressed(event.key.code);
				break;
			case sf::Event::KeyReleased:
				mData->input.updateKeyReleased(event.key.code);
				break;
			default:
				break;
		}
	}
}

void GameState::update(float dt)
{
	if (mData->input.isKeyPressed(sf::Keyboard::Right))
		mPlayer.rotate(Direction::Clockwise, dt * ROTATION_SPEED);

	if (mData->input.isKeyPressed(sf::Keyboard::Left))
		mPlayer.rotate(Direction::CounterClockwise, dt * ROTATION_SPEED);

	if (mData->input.isKeyPressed(sf::Keyboard::Up))
	{

		if (!mCollider.checkWallCollision(mPlayer, mMap, Direction::ForwardVertical, dt * MOVE_SPEED))
			mPlayer.move(Direction::ForwardVertical, dt * MOVE_SPEED);
		if (!mCollider.checkWallCollision(mPlayer, mMap, Direction::ForwardHorizontal, dt * MOVE_SPEED))
			mPlayer.move(Direction::ForwardHorizontal, dt * MOVE_SPEED);
	}

	if (mData->input.isKeyPressed(sf::Keyboard::Down))
	{
		if (!mCollider.checkWallCollision(mPlayer, mMap, Direction::BackwardVertical, dt * MOVE_SPEED))
			mPlayer.move(Direction::BackwardVertical, dt * MOVE_SPEED);
		if (!mCollider.checkWallCollision(mPlayer, mMap, Direction::BackwardHorizontal, dt * MOVE_SPEED))
			mPlayer.move(Direction::BackwardHorizontal, dt * MOVE_SPEED);
	}

	if (mData->input.isKeyPressed(sf::Keyboard::Escape))
	{
		mData->stateMachine.addState(std::make_unique<GamePausedState>(mData), false);
	}
	
	std::vector<Sprite>::iterator it;

	for (it = mMap.getSprites().begin(); it != mMap.getSprites().end(); ++it)
	{
		if (mCollider.checkSpriteCollision(mPlayer, *it))
		{
			mMap.getSprites().erase(it);
			mPlayer.keyColected();
			mHud.updateKeys(mPlayer.getKeyCounter());
			break;
		}
	}
	
	if (mTimer.getElapsedTime().asSeconds() > 1.0f)
	{
		mElapsedTime++;
		mHud.updateTime(mLimitTime - mElapsedTime);
		mTimer.restart();

		if (mElapsedTime == mLimitTime)
		{
			mData->stateMachine.addState(std::make_unique<GameOverState>(mData, false));
		}
	}
	
	if (checkWin(dt * MOVE_SPEED))
	{
		mData->stateMachine.addState(std::make_unique<GameOverState>(mData, true));
	}
	
}

void GameState::draw(float dt)
{
	mData->window.clear();

	mRayCaster.drawWalls(mPlayer, mMap);
	mRayCaster.drawSprites(mPlayer, mMap);
	mHud.draw();

	mData->window.display();
}

void GameState::resume()
{
	mData->input.restart();
	mTimer.restart();

	if (mData->configs.at("GoBackToMainMenu"))
		mData->stateMachine.removeState();
}

bool GameState::checkWin(double const& moveSpeed)
{
	/* przepraszam */
	return ((mCollider.checkDoorCollision(mPlayer, mMap, Direction::ForwardHorizontal, moveSpeed) ||
			mCollider.checkDoorCollision(mPlayer, mMap, Direction::ForwardVertical, moveSpeed) ||
			mCollider.checkDoorCollision(mPlayer, mMap, Direction::BackwardHorizontal, moveSpeed) ||
			mCollider.checkDoorCollision(mPlayer, mMap, Direction::BackwardVertical, moveSpeed))) &&
			(mMap.getSprites().size() == 0);
}
