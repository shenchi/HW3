#include "Sprite.h"
#include "Application.h"

namespace hw3
{

	Sprite::Sprite()
		:
		renderer(nullptr),
		texture(nullptr)
	{
		renderer = Application::Instance()->GetRenderer();
	}


	Sprite::~Sprite()
	{
		if (nullptr != texture)
		{
			SDL_DestroyTexture(texture);
			texture = nullptr;
		}
	}

	bool Sprite::LoadImageFromFile(char const * filename)
	{
		SDL_Surface* surface = IMG_Load(filename);

		if (nullptr == surface)
		{
			return false;
		}

		texture = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_FreeSurface(surface);

		if (nullptr == texture)
		{
			return false;
		}

		return true;
	}

	void Sprite::Draw()
	{
		if (nullptr == texture)
			return;

		SDL_RenderCopy(renderer, texture, nullptr, &rect);
	}

	void Sprite::SetRect(SDL_Rect const & rect)
	{
		this->rect = rect;
	}

}
