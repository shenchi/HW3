#pragma once

#include "Sprite.h"
#include "Constants.h"

namespace hw3
{
	class TiledMap;

	class Character
	{
	public:

		void Init(char const * filename, int width, int height);

		inline void SetPosition(int x, int y) { this->x = x; this->y = y; }

		inline void SetMap(TiledMap* m) { map = m; }

		inline bool IsFalling() const { return falling; }

		inline int X() const { return x; }
		inline int Y() const { return y; }

		virtual void Update();
		virtual void Draw();

	protected:
		Sprite	sprite;

		TiledMap*	map;

		int		x;
		int		y;

		bool falling = false;
	};


}
