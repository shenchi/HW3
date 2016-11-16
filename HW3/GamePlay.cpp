#include "GamePlay.h"

#include <chrono>

#include "Application.h"

typedef std::chrono::high_resolution_clock timer;

namespace hw3
{
	void GamePlay::Init()
	{
		mapSprite.LoadImageFromFile("Assets/tiles_spritesheet.png");
		mapSprite.SetTileInfo(70, 70, 12, 13, 0, 2);

		map.LoadFromFile("Assets/test.csv");
		map.SetSprite(&mapSprite);
		map.SetTileSize(TILE_WIDTH, TILE_HEIGHT);

		player.Init("Assets/blockerMad.png", TILE_WIDTH, TILE_HEIGHT);
		player.SetMap(&map);
		player.SetPosition(0, 0);

		enemy.Init("Assets/spinner.png", TILE_WIDTH, TILE_HEIGHT);
		enemy.SetMap(&map);
		enemy.SetTarget(&player);
		enemy.SetPosition(map.Width() - 1, 0);
	}

	void GamePlay::Update()
	{

		static auto lastTime = timer::now();
		auto now = timer::now();

		float deltaTime = std::chrono::duration<float>(now - lastTime).count();

		if (enemy.X() == player.X() && enemy.Y() == player.Y())
		{
			player.SetPosition(0, 0);
			enemy.SetPosition(map.Width() - 1, 0);
		}

		if (deltaTime > 0.2f)
		{
			lastTime = now;

			player.Update();

			if (!player.IsFalling())
			{
				int px = player.X();
				int py = player.Y();

				if (app->IsKeyPressed(SDL_SCANCODE_W) && map.IsClimable(px, py))
				{
					py--;
				}
				else if (app->IsKeyPressed(SDL_SCANCODE_A))
				{
					px--;
				}
				else if (app->IsKeyPressed(SDL_SCANCODE_D))
				{
					px++;
				}

				if (map.IsAir(px, py) || map.IsClimable(px, py))
					player.SetPosition(px, py);
			}

			enemy.Update();
		}
	}

	void GamePlay::Draw()
	{
		map.Draw();

		player.Draw();

		enemy.Draw();
	}

}
