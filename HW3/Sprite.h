#pragma once

#include <SDL.h>
#include <SDL_image.h>

namespace hw3
{

	class Sprite
	{
	public:
		Sprite();
		virtual ~Sprite();

		bool LoadImageFromFile(char const * filename);

		virtual void Draw();

		void SetRect(SDL_Rect const & rect);

		inline void Move(int x, int y) { rect.x += x; rect.y += y; }
		inline void SetPosition(int x, int y) { rect.x = x; rect.y = y; }

		inline SDL_Rect& Rect() { return rect; }

	protected:
		SDL_Renderer*	renderer;
		SDL_Texture*	texture;
		SDL_Rect		rect;
	};

}

