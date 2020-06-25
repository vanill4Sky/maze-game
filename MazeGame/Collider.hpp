#pragma once

#include "Player.hpp"
#include "Map.hpp"

class Collider
{
public:
	Collider();
	~Collider();

	/* \return zwraca wartość true jeśli wystąpi kolizja gracza ze ścianą */
	bool checkWallCollision(Player const& player, Map const& map, sf::Vector2i const moveDir, double const& moveSpeed);
	/* \return zwraca wartość true jeśli wystąpi kolizja gracza z drzwiami */
	bool checkDoorCollision(Player const& player, Map const& map, sf::Vector2i const moveDir, double const& moveSpeed);
	/* \return zwraca wartość true jeśli wystąpi kolizja gracza ze spritem */
	bool checkSpriteCollision(Player const& player, Sprite const & sprite);
};

