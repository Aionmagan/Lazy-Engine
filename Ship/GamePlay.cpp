#include "Scene.h"

#include "BackGround.h"
#include "Player.h"
#include "Enemy.h"  
#include "Weapon.h"
#include <cstdio>

#define ENEMY_GROUP 3
#define ENEMY_AMOUNT 7

#include <cstdio>

void GamePlay()
{
printf("GamePlay()\n");
	
	BG bg; 
	
	Player player;
	Weapon weapon;
	
	Enemy enemyList[ENEMY_GROUP][ENEMY_AMOUNT];
	for(int i = 0; i < ENEMY_GROUP; ++i)
	{
		char str[512]; 
		sprintf(str,"Assets/Enemy%d", i);
		std::string filename(str); 
		for(int j = 0; j < ENEMY_AMOUNT; ++j)
		{
			enemyList[i][j].init(filename, Vector(j*16.0-48.0f, 
												  i*13.0f+5.0f, 0));
		}
	}
	Weapon enemyWeapon;
	enemyWeapon.setShootDirection(-1);
	enemyWeapon.setShootSpeed(70.0f);
	Camera cam; 
	cam.transform.position.z = 100;
	//cam.transform.position.y = -100;
	//cam.transform.rotation = Quaternion::Euler(-45, 0, 0);	
	cam.applyView();
		
	while(!gInput.eventQuit() && gameState == GameState::GAMEPLAY)
	{
		gInput.update();
		gTime.update();
		
		bg.update();
		
		player.update();
		weapon.update();
		
		if (gInput.button(BN_CROSS))
		{
			weapon.setShootDirection(Vector3::Up());
			weapon.shoot(player.getPosition()); 
		}
		
		int egw = Mathf::RandomRangei(0, ENEMY_GROUP);
		int esw = Mathf::RandomRangei(0, ENEMY_AMOUNT);
		
		enemyWeapon.setShootDirection(player.getPosition() - enemyList[egw][esw].getPosition());
		enemyWeapon.shoot(enemyList[egw][esw].getPosition());
		
		enemyWeapon.update();
		for(int i = 0; i < ENEMY_GROUP; ++i)
		{
			for(int j = 0; j < ENEMY_AMOUNT; ++j)
			{
				enemyList[i][j].update();
			}
		}		
		
		if (gInput.buttonDown(BN_CIRCLE))
			gameState = GameState::MAINMENU;
			
		gRenderer.drawQueue();
	}
	
	gRenderer.removeQueue();
}
