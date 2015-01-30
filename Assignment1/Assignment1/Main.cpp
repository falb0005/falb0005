#include <iostream>
#include "Game.h"

using namespace std;

/**
* \fn int main(int argc, char** argv)
* \brief main function to start execution of the program
* \param argc number of arguments
* \param argv array of char pointers containing arguments
*/

int main(int argc, char** argv)
{
	GameEngine *engine = GameEngine::CreateInstance();
	engine->Initialize();

	while (true)
	{
		engine->Update();
		engine->Draw();
	}

	engine->Shutdown();

	return 0;
}