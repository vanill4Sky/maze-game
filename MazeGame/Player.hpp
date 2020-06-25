#pragma once
#define Hacked by Hack3rMatt
#include <SFML/Graphics.hpp>

namespace Direction
{
	const sf::Vector2i ForwardVertical{ 1, 0 };
	const sf::Vector2i ForwardHorizontal{ 0, 1 };
	const sf::Vector2i BackwardVertical{ -1, 0 };
	const sf::Vector2i BackwardHorizontal{ 0, -1 };
	const int Clockwise{ -1 };
	const int CounterClockwise{ 1 };
}

class Player
{
public:
	/*	\param position - początkowa pozcyaj gracza na mapie
		\param direction - początkowy kierunek, w którym jest zwrócony gracz, wektor jednostokwy
		\param cameraPlane - szerokość odcinka kamery, ten wektor musi być prostopadły do direction */
	Player(sf::Vector2<double> position, sf::Vector2<double> direction, sf::Vector2<double> cameraPlane);
	~Player();

	const sf::Vector2<double>& getPosition() const;
	const sf::Vector2<double>& getDirection() const;
	const sf::Vector2<double>& getCameraPlane() const;
	int getKeyCounter() const;
	void move(const sf::Vector2i moveDir, double moveSpeed);
	void rotate(const int rotationDir, double rotationSpeed);
	void keyColected();

private:
	sf::Vector2<double> mPosition;
	sf::Vector2<double> mDirection;
	sf::Vector2<double> mCameraPlane;
	int mKeyCounter;
};

