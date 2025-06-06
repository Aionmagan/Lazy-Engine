#ifndef __SCENE_H__
#define __SCENE_H__

#include <LazyEngine.h>

enum GameState
{
	MAINMENU,
	GAMEPLAY,
};

extern GameState gameState;

void MainMenu();
void GamePlay();

#endif/*__SCENE_H__*/
