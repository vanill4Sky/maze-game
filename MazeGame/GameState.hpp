#pragma once

#include <memory>

#include "State.hpp"
#include "Values.hpp"
#include "GameData.hpp"
#include "Player.hpp"
#include "Map.hpp"
#include "RayCaster.hpp"
#include "Collider.hpp"
#include "GameOverState.hpp"
#include "HUD.hpp"
#include "GamePausedState.hpp"

class GameState :
	public State
{
public:
	GameState(GameDataRef data);
	~GameState();


	void init();
	void handleInput();
	void update(float dt);
	void draw(float dt);
	void resume();

private:
	bool checkWin(double const& moveSpeed);

	GameDataRef mData;
	Player mPlayer;
	Map mMap;
	RayCaster mRayCaster;
	Collider mCollider;
	HUD mHud;

	sf::Clock mTimer;
	int mLimitTime;
	int mElapsedTime;
};

