#pragma once
#include "Sprite.h"

namespace hw3
{

	class TiledSprite :
		public Sprite
	{
	public:
		void SetTileInfo(int tileWidth, int tileHeight, int columns, int rows, int margin, int spacing);

		void SetTileId(int id);

		virtual void Draw();

	private:
		SDL_Rect	src_rect;

		int columns;
		int rows;
		int margin;
		int spacing;

		int tileId;
	};

}
