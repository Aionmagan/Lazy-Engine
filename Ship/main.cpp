#include <cstdio> 
#include <LazyEngine.h> 
#include <cmath>

#include "Scene.h" 

int main(int argc, char*argv[])
{
	gRenderer.setBGColor(0, 0, 0);
	
	
	//Skybox sb("Assets/Skybox.png");

	gameState = GameState::MAINMENU;
	while(!gInput.eventQuit())
	{
		gTime.update(); 
		gInput.update();

		switch(gameState)
		{
			default:
			case GameState::MAINMENU:
				MainMenu();
				break;
			case GameState::GAMEPLAY:
				GamePlay();
				break;
		}
	}
	
	return 0; 
}
