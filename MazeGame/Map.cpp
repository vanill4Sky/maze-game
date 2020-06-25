#include "Map.hpp"

#include <iostream>


Map::Map(int mazeHeight, int mazeWidth) : mMazeHeight(mazeHeight), mMazeWidth(mazeWidth), 
										  mMapHeight(mazeHeight * 2 + 1), mMapWidth(mazeWidth * 2 + 1)
{
	/* CONSTS AND TYPES */
	const sf::Vector2i DFS_STARTING_CEIL{ 0, 0 };
	const size_t CEIL_SIZE = 9;
	const size_t CEIL_CENTER = CEIL_SIZE / 2;

	struct Ceil
	{
		bool wasVisited;
		std::array<bool, CEIL_SIZE> wall;

		Ceil() : wasVisited(false)
		{
			std::fill_n(wall.begin(), CEIL_SIZE, true);
			wall.at(CEIL_CENTER) = false;
		}

		void removeWall(int side) { wall.at(side) = false; }
		void markVisited() { wasVisited = true; }
	};

	const std::array<const sf::Vector2i, 4> directions
	{
		sf::Vector2i(0, -1),
		sf::Vector2i(0,  1),
		sf::Vector2i(-1,  0),
		sf::Vector2i(1,  0)
	};

	/* VARIABLES */
	std::vector<Ceil> maze(mazeHeight * mazeWidth);
	std::stack<sf::Vector2i> currentPath;
	std::vector<sf::Vector2i> ceilsToVisit;
	sf::Vector2i currentCeil, nextCeil;
	std::default_random_engine randomEngine(std::random_device{}());
	bool backtracking{ false };

	/* LAMBDAS */
	/* converts coordinates (in range 0 <= x < mMazeWidth, 0 <= y < mMazeHeight) to vector index */
	auto getIndex = [this](sf::Vector2i coords)->size_t { return coords.x + coords.y * mMazeWidth; };
	/* converts coordinates (in range 0 <= x < 3, 0 <= y < 3) to array index */
	auto getCeilWallIndex = [](sf::Vector2i coords)->size_t { return coords.x + coords.y * 3; };
	/* check is next step safe */
	auto isOutOfBound = [this](sf::Vector2i coords)->bool
	{
		if (coords.x < 0 || coords.y < 0 || coords.x >= mMazeWidth || coords.y >= mMazeHeight)
			return true;
		else
			return false;
	};
	auto getRandomNumber = [&randomEngine](unsigned int min, unsigned int max)->size_t 
	{ 
		return std::uniform_int_distribution<size_t>{min, max}(randomEngine); 
	};

	/* MAZE GENERATOR */
	/* maze generation algorithm = DFS */
	ceilsToVisit.reserve(4);
	currentPath.push(DFS_STARTING_CEIL);

	while (!currentPath.empty())
	{
		currentCeil = currentPath.top();
		maze.at(getIndex(currentCeil)).markVisited();

		for (auto const& dir : directions)
		{
			if (!isOutOfBound(currentCeil + dir) && !maze.at(getIndex(currentCeil + dir)).wasVisited)
			{
				ceilsToVisit.push_back(currentCeil + dir);
			}
		}
		if (ceilsToVisit.empty())
		{
			if(!backtracking)
				mDeadEnds.push_back(std::make_pair(currentCeil, currentPath.size()));
			backtracking = true;

			currentPath.pop();
			continue;
		}
		else
		{
			backtracking = false;
		}

		nextCeil = ceilsToVisit.at(getRandomNumber(0, ceilsToVisit.size() - 1));
		ceilsToVisit.clear();

		for (auto const& dir : directions)
		{
			if (nextCeil - currentCeil == dir)
			{
				maze.at(getIndex(currentCeil)).removeWall(getCeilWallIndex(sf::Vector2i{ 1, 1 } + dir));
				maze.at(getIndex(nextCeil)).removeWall(getCeilWallIndex(sf::Vector2i{ 1, 1 } - dir));
				break;
			}
		}

		currentPath.push(nextCeil);
	}
	/* end of dfs */

	auto deadEndsCompare = [](std::pair<sf::Vector2i, int> const& a, std::pair<sf::Vector2i, int> const& b)
	{
		return a.second < b.second;
	};
	/* sorting dead ends in ascending order */
	std::sort(mDeadEnds.begin(), mDeadEnds.end(), deadEndsCompare);
	/* dead end with longest path now becoms the exit door */
	sf::Vector2i finishDeadEnd = mDeadEnds.back().first;
	mDeadEnds.pop_back();

	/* putting keys on map */
	for (int i = 0; i < 2 && mDeadEnds.size() > 0; i++)
	{
		sf::Vector2<double> keyPosition(mDeadEnds.back().first.x * 2 + 1, mDeadEnds.back().first.y * 2 + 1);
		keyPosition += sf::Vector2<double> {0.5, 0.5}; //adding halves to get the center of the square
		mDeadEnds.pop_back();

		mKeys.push_back(Sprite{ keyPosition, TextureId::SpriteKey });
	}

	/* making map from maze */
	mMap.resize(mMapHeight * mMapWidth);

	for (int i = 0; i < mMazeHeight; i++)
	{
		for (int k = 0; k < 3; k++)
		{
			for (int j = 0; j < mMazeWidth; j++)
			{
				for (int l = 0; l < 3; l++)
				{
					if (maze.at(getIndex(sf::Vector2i(j, i))).wall[l + k * 3])
						mMap.at(j * 2 + l + (i * 2 + k) * mMapWidth) = TextureId::WallBrick;
					else
						mMap.at(j * 2 + l + (i * 2 + k) * mMapWidth) = 0;

					if(finishDeadEnd == sf::Vector2i(j, i))
						mMap.at(j * 2 + 1 + (i * 2 + 1) * mMapWidth) = TextureId::WallDoor;
				}
			}
		}
	}
}

Map::~Map()
{
}

int Map::getHeight() const
{
	return mMapHeight;
}

int Map::getWidth() const
{
	return mMapWidth;
}

std::vector<Sprite> const& Map::getSprites() const
{
	return mKeys;
}

std::vector<Sprite>& Map::getSprites()
{
	return mKeys;
}

int const & Map::operator()(int column, int row) const
{
	return mMap.at(column + row * mMapWidth);
}

int const & Map::operator()(sf::Vector2i & coords) const
{
	return mMap.at(coords.x + coords.y * mMapWidth);
}

