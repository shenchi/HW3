#pragma once

#include "Constants.h"
#include "Sprite.h"
#include "TiledSprite.h"
#include "TiledMap.h"
#include "Character.h"
#include "Enemy.h"

namespace hw3
{
	class Application;

	class GamePlay
	{
	public:
		GamePlay(Application* app) : app(app) {}


		void Init();

		void Update();
		void Draw();

	private:
		Application* app;

		TiledSprite	mapSprite;
		TiledMap	map;

		Character	player;
		Enemy		enemy;
	};

}
