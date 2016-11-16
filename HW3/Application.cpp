#include "Application.h"

#include <SDL.h>

namespace hw3
{

	Application* Application::instance = nullptr;

	Application::Application()
	{
		instance = this;
	}


	Application::~Application()
	{
		delete gameplay;
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
	}

	bool Application::Init()
	{
		if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
			return false;

		window = SDL_CreateWindow("", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);

		if (nullptr == window)
		{
			SDL_Quit();
			return false;
		}

		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

		if (nullptr == renderer)
		{
			SDL_DestroyWindow(window);
			SDL_Quit();
			return false;
		}

		gameplay = new GamePlay(this);
		gameplay->Init();

		return true;;
	}

	void Application::Run()
	{
		SDL_Event e;
		bool quit = false;
		while (!quit) {
			while (SDL_PollEvent(&e)) {
				if (e.type == SDL_QUIT) {
					quit = true;
				}
				if (e.type == SDL_KEYDOWN)
				{
					keys[e.key.keysym.scancode] = 1;
				}
				if (e.type == SDL_KEYUP)
				{
					keys[e.key.keysym.scancode] = 0;
				}
			}
			SDL_RenderClear(renderer);
			gameplay->Update();
			gameplay->Draw();
			SDL_RenderPresent(renderer);
		}
	}



}
