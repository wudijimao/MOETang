#include "main.h"
#include <iostream>
#include "AppDelegate.h"
using namespace std;


int APIENTRY _tWinMain(HINSTANCE hInstance,
					   HINSTANCE hPrevInstance,
					   LPTSTR    lpCmdLine,
					   int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

    // create the application instance
    AppDelegate app;

    return cocos2d::Application::getInstance()->run();
}

