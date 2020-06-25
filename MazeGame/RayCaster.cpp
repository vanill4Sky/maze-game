#include "RayCaster.hpp"

using namespace std;

RayCaster::RayCaster(GameDataRef data):
	mData(data), 
	mScreenWidth(data->window.getSize().x), 
	mScreenHeight(mData->window.getSize().y),
	mGreyColor(0xD3, 0xD3, 0xD3)
{
	mData->assets.loadTexture("MegaTexture", MEGA_TEXTURE_FILEPATH);

	mZBuffer.resize(data->window.getSize().x);
	megaTexture = data->assets.getTexture("MegaTexture");
}

RayCaster::~RayCaster()
{
}

void RayCaster::drawWalls(const Player& player, const Map& map)
{
	sf::VertexArray currentCastStripe(sf::Lines, 6);

	for (int screenX = 0; screenX < mScreenWidth; screenX++)
	{
		sf::Vector2<double> rayPosition{ player.getPosition() };
		/* calculating ray direction from both player dirrection and camera plane */
		double cameraPlaneSection = (2 * screenX) / static_cast<double>(mScreenWidth) - 1;
		sf::Vector2<double> rayDirection{ player.getDirection() + player.getCameraPlane() * cameraPlaneSection };

		sf::Vector2i currentSquare{ static_cast<sf::Vector2i>(rayPosition) };

		/* distance from ray position to next horizontal(y) and vertical(x) wall in current square */
		sf::Vector2<double> wallDistance;
		/* distance the ray has to travel from 1 y-wall to the next y-wall, or from 1 x-wall to the next x-wall */
		sf::Vector2<double> deltaDistance{ std::abs(1.0 / rayDirection.x), std::abs(1.0 / rayDirection.y) };
		/* what direction step in vertical and horizontal direction */
		sf::Vector2i step;
		
		Side side{ Side::Vertical };

		double perpWallDistance;
		int wallHeight;

		if (rayDirection.x < 0)
		{
			step.x = -1;
			/* distance from ray position to the first east wall */
			wallDistance.x = (rayPosition.x - currentSquare.x) * deltaDistance.x;
		}
		else
		{
			step.x = 1;
			/* distance from ray position to the first west wall (that is why 1 is added) */
			wallDistance.x = (currentSquare.x + 1.0 - rayPosition.x) * deltaDistance.x;
		}
		if (rayDirection.y < 0)
		{
			step.y = -1;
			/* distance from ray position to the first north wall */
			wallDistance.y = (rayPosition.y - currentSquare.y) * deltaDistance.y;
		}
		else
		{
			step.y = 1;
			/* distance from ray position to the first south wall (that is why 1 is added) */
			wallDistance.y = (currentSquare.y + 1.0 - rayPosition.y) * deltaDistance.y;
		}

		/* performing DDA algorithm */
		while (map(currentSquare.x, currentSquare.y) == 0)
		{
			if (wallDistance.x < wallDistance.y)
			{
				wallDistance.x += deltaDistance.x;
				currentSquare.x += step.x;
				side = Side::Vertical;
			}
			else
			{
				wallDistance.y += deltaDistance.y;
				currentSquare.y += step.y;
				side = Side::Horizontal;
			}
		}

		/* calcualating perpenticular to camera plane wall distance */
		if (side == Side::Vertical)
		{
			perpWallDistance = (currentSquare.x - rayPosition.x + (1 - step.x) / 2) / rayDirection.x;
		}
		else
		{
			perpWallDistance = (currentSquare.y - rayPosition.y + (1 - step.y) / 2) / rayDirection.y;
		}

		mZBuffer[screenX] = perpWallDistance;

		wallHeight = static_cast<int>(mScreenHeight / perpWallDistance);

		int lineStart = (-wallHeight + mScreenHeight) / 2;
		int lineEnd = lineStart + wallHeight;

		double wallHitPoint;
		if (side == Side::Vertical)
		{
			wallHitPoint = rayPosition.y + perpWallDistance * rayDirection.y;
		}
		else
		{
			wallHitPoint = rayPosition.x + perpWallDistance * rayDirection.x;
		}
		/* we want only the fractional part */
		wallHitPoint -= std::floor(wallHitPoint);

		/* calculating which column of the texture should be use */
		int textureColumn = static_cast<int>(wallHitPoint * DEFAULT_TEXTURE_SIZE);
		if (side == Side::Vertical && rayDirection.x > 0 || side == Side::Horizontal && rayDirection.y < 0)
		{
			textureColumn = DEFAULT_TEXTURE_SIZE - textureColumn - 1;
		}
		/* making on side of the wall darker, pseudo shadow effect */
		sf::Color shadow = sf::Color::White;
		if (side == Side::Vertical) {
			shadow = mGreyColor;
		}

		/* floor */
		currentCastStripe.append(sf::Vertex(sf::Vector2f(screenX, mScreenHeight), sf::Color::White));
		currentCastStripe.append(sf::Vertex(sf::Vector2f(screenX, lineEnd), shadow));
		/* walls */
		currentCastStripe.append(
			sf::Vertex{ sf::Vector2f(screenX, lineStart),
			shadow,
			sf::Vector2f(textureColumn + (map(currentSquare) - 1) * DEFAULT_TEXTURE_SIZE, 0) });
		currentCastStripe.append(
			sf::Vertex{ sf::Vector2f(screenX, lineEnd),
			shadow,
			sf::Vector2f(textureColumn + (map(currentSquare) - 1) * DEFAULT_TEXTURE_SIZE, DEFAULT_TEXTURE_SIZE) });
		/* ceiling */
		currentCastStripe.append(sf::Vertex(sf::Vector2f(screenX, lineStart), mGreyColor));
		currentCastStripe.append(sf::Vertex(sf::Vector2f(screenX, 0), sf::Color::Black));

		mData->window.draw(currentCastStripe, &megaTexture);

		currentCastStripe.clear();
	}
}

void RayCaster::drawSprites(const Player& player, const Map& map)
{
	sf::VertexArray spriteCastStripe(sf::Lines, 2);

	for (size_t i = 0; i < map.getSprites().size(); i++)
	{
		sf::Vector2<double> currentSpritePosition = map.getSprites().at(i).getPosition();
		/* get sprite position relative to player */
		currentSpritePosition -= player.getPosition();

		/* sprite point is then transformed using camera plane vector by multiplication by inverse of the view matrix*/
		double inversedDet = 1.0 / (player.getCameraPlane().x * player.getDirection().y
			- player.getCameraPlane().y * player.getDirection().x);
		sf::Vector2<double> transformed(
			inversedDet * (player.getDirection().y * currentSpritePosition.x - player.getDirection().x * currentSpritePosition.y),
			inversedDet * (-player.getCameraPlane().y * currentSpritePosition.x + player.getCameraPlane().x * currentSpritePosition.y));
		
		int spriteScreenX = mScreenWidth / 2 * (1 + transformed.x / transformed.y);

		sf::Vector2i spriteSize{ 
			std::abs(static_cast<int>(mScreenHeight / transformed.y)), 
			std::abs(static_cast<int>(mScreenHeight / (transformed.y))) };
		sf::Vector2i spriteLineStart{ spriteScreenX - spriteSize.x / 2, (mScreenHeight - spriteSize.y) / 2 };
		sf::Vector2i spriteLineEnd{ spriteSize.x / 2 + spriteScreenX, spriteSize.y / 2 + mScreenHeight / 2 };

		/* we must to check start and end od spriteLine.x to avoid almost infinite loops */
		if (spriteLineStart.x < 0) spriteLineStart.x = 0;
		if (spriteLineEnd.x > mScreenWidth) spriteLineEnd.x = mScreenWidth;

		for (int screenX = spriteLineStart.x; screenX < spriteLineEnd.x; screenX++)
		{
			if (transformed.y > 0 && transformed.y < mZBuffer[screenX])
			{
				/* calculating which column of texture should be used (proportions) */
				int textureColumn = static_cast<int>((screenX - spriteScreenX + spriteSize.x / 2) * DEFAULT_TEXTURE_SIZE / spriteSize.x);

				spriteCastStripe.append(
					sf::Vertex{ sf::Vector2f(screenX, spriteLineStart.y),
								sf::Vector2f(textureColumn + DEFAULT_TEXTURE_SIZE * (TextureId::SpriteKey - 1) + 1, 0) });
				spriteCastStripe.append(
					sf::Vertex{ sf::Vector2f(screenX, spriteLineEnd.y),
								sf::Vector2f(textureColumn + DEFAULT_TEXTURE_SIZE * (TextureId::SpriteKey - 1) + 1, DEFAULT_TEXTURE_SIZE) });

				mData->window.draw(spriteCastStripe, &megaTexture);
				spriteCastStripe.clear();
			}
			
		}
	}
}


