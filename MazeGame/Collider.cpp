#include "Collider.hpp"

Collider::Collider()
{
}

Collider::~Collider()
{
}

bool Collider::checkWallCollision(Player const& player, Map const& map, sf::Vector2i const moveDir, double const& moveSpeed)
{
	sf::Vector2i comingPosition;
	comingPosition.x = static_cast<int>(player.getPosition().x + moveDir.x * player.getDirection().x * moveSpeed);
	comingPosition.y = static_cast<int>(player.getPosition().y + moveDir.y * player.getDirection().y * moveSpeed);

	return (map(comingPosition) > 0);
}

bool Collider::checkDoorCollision(Player const& player, Map const& map, sf::Vector2i const moveDir, double const& moveSpeed)
{
	sf::Vector2i comingPosition;
	comingPosition.x = static_cast<int>(player.getPosition().x + moveDir.x * player.getDirection().x * moveSpeed);
	comingPosition.y = static_cast<int>(player.getPosition().y + moveDir.y * player.getDirection().y * moveSpeed);

	return (map(comingPosition) == 2);
}

bool Collider::checkSpriteCollision(Player const & player, Sprite const & sprite)
{
	return static_cast<sf::Vector2i>(sprite.getPosition()) == static_cast<sf::Vector2i>(player.getPosition());
}

