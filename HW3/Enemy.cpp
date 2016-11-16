#include "Enemy.h"

#include "TiledMap.h"
#include "Dijkstra.h"

namespace hw3
{
	Enemy::Enemy()
	{
		frameSprite.LoadImageFromFile("Assets/frame.png");
		frameSprite.SetRect(SDL_Rect{ 0, 0, TILE_WIDTH, TILE_HEIGHT });
	}

	void Enemy::Update()
	{
		Character::Update();

		if (path.Size() > 1)
		{
			path.Pop();
			size_t h = path.Pop();
			map->Hash2Coord(h, x, y);
		}

		if (nullptr != target)
		{
			size_t st = map->Coord2Hash(x, y);
			size_t ed = map->Coord2Hash(target->X(), target->Y());

			// for pure Dijkstra, use this line
			//path = Dijkstra<TiledMap, int>(*map, st, ed);

			// for A*, use this line
			path = Dijkstra<TiledMap, int, TiledMap::Heuristic>(*map, st, ed, map->GetHeuristicFunc());
		}
	}

	void Enemy::Draw()
	{
		Character::Draw();

		for (size_t i = 0; i < path.Size(); ++i)
		{
			int x = 0, y = 0;
			map->Hash2Coord(path[i], x, y);

			frameSprite.SetPosition(x * TILE_WIDTH, y * TILE_HEIGHT);
			frameSprite.Draw();
		}
	}

}
