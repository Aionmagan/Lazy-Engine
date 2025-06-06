#ifndef __ENEMY_H__
#define __ENEMY_H__

#include <LazyEngine.h>

class Enemy
{
public:
	Enemy(); 
   ~Enemy(); 
   
    void update(); 
    void queue(); 
   
private:
	
	Model enemyMod; 
	Texture enemyTex; 
	Texture enemyNrm; 
	Material enemyMat;
	GameObject enemy; 
};

#endif/*__ENEMY_H__*/
