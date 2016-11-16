#include <Windows.h>

#include "Application.h"
#include "TiledSprite.h"
#include "TiledMap.h"

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	hw3::Application app;

	app.Init();

	app.Run();
	return 0;
}
