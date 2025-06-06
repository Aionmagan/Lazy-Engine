#include "Scene.h" 
#include <LazyEngine.h>

#include "mm_select.h" 

#include <cstdio>

void MainMenu()
{
printf("MainMenu()\n");
	gRenderer.setBGColor(1, 0, 0);

	Camera cam; 
	cam.transform.position = Vector3(0, 5, 35);
	cam.transform.lookAt(Vector::Zero());
	cam.applyView(); 
	
	MM_Select selectionScreen;
	
	while(!gInput.eventQuit() && gameState == GameState::MAINMENU)
	{
		gInput.update();
		gTime.update();				
		
		selectionScreen.SelectPlayer();
		if (gInput.button(BN_CROSS))
			gameState = GameState::GAMEPLAY;
		
		gRenderer.drawQueue();
	}
	
	gRenderer.removeQueue();
}
