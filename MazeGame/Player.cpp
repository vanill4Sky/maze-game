#include "Player.hpp"


Player::Player(sf::Vector2<double> position, sf::Vector2<double> direction, sf::Vector2<double> cameraPlane)
	: mPosition(position), mDirection(direction), mCameraPlane(cameraPlane), mKeyCounter(0)
{
}

Player::~Player()
{
}

const sf::Vector2<double>& Player::getPosition() const
{
	return mPosition;
}

const sf::Vector2<double>& Player::getDirection() const
{
	return mDirection;
}

const sf::Vector2<double>& Player::getCameraPlane() const
{
	return mCameraPlane;
}

int Player::getKeyCounter() const
{
	return mKeyCounter;
}

void Player::move(const sf::Vector2i moveDir, double moveSpeed)
{
	mPosition.x += moveDir.x * mDirection.x * moveSpeed;
	mPosition.y += moveDir.y * mDirection.y * moveSpeed;
}

void Player::rotate(const int rotationDir, double rotationSpeed)
{
	auto rotateVector = [&rotationDir](sf::Vector2<double> vector, float angle)->sf::Vector2<double>
	{
		angle *= rotationDir;
		return sf::Vector2<double>{ vector.x * cos(angle) - vector.y * sin(angle), 
									vector.x * sin(angle) + vector.y * cos(angle) };
	};

	mDirection = rotateVector(mDirection, rotationSpeed);
	mCameraPlane = rotateVector(mCameraPlane, rotationSpeed);
}

void Player::keyColected()
{
	mKeyCounter++;
}

