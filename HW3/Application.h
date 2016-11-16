#pragma once

#include <SDL.h>

#include "GamePlay.h"

namespace hw3
{

	class Application
	{
		static Application* instance;
	public:

		inline static Application* Instance() { return instance; }

	public:
		Application();
		~Application();

		bool Init();

		void Run();

		bool IsKeyPressed(int key) { return (keys[key] == 1); }

		inline SDL_Renderer* GetRenderer() { return renderer; }

	private:
		SDL_Window* window;
		SDL_Renderer* renderer;

		GamePlay*	gameplay;

		char		keys[256] = { 0 };
	};

}
