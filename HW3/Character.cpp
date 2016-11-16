#include "Character.h"

#include "TiledMap.h"

namespace hw3
{
	void Character::Init(char const * filename, int width, int height)
	{
		sprite.LoadImageFromFile(filename);
		sprite.SetRect(SDL_Rect{ 0, 0, width, height });
	}

	void Character::Update()
	{
		if (map->IsAir(x, y + 1))
		{
			y++;
			falling = true;
		}
		else
		{
			falling = false;
		}
	}

	void Character::Draw()
	{
		sprite.SetPosition(
			x * TILE_WIDTH - (sprite.Rect().w - TILE_WIDTH) / 2,
			(y + 1) * TILE_WIDTH - sprite.Rect().h
		);
		sprite.Draw();
	}
}
