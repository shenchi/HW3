#include "TiledSprite.h"

namespace hw3
{

	void TiledSprite::SetTileInfo(int tileWidth, int tileHeight, int columns, int rows, int margin, int spacing)
	{
		this->columns = columns;
		this->rows = rows;
		this->margin = margin;
		this->spacing = spacing;

		src_rect.w = tileWidth;
		src_rect.h = tileHeight;

		SetTileId(0);
	}

	void TiledSprite::SetTileId(int id)
	{
		if (id < 0 || id >= columns * rows)
			return;

		tileId = id;

		int x = id % columns;
		int y = id / columns;

		src_rect.x = margin + (src_rect.w + spacing) * x;
		src_rect.y = margin + (src_rect.h + spacing) * y;
	}

	void TiledSprite::Draw()
	{
		if (nullptr == texture)
			return;

		SDL_RenderCopy(renderer, texture, &src_rect, &rect);
	}

}
