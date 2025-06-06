#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <LazyEngine.h>

class Player
{
public:
	Player();
   ~Player();
   
   void update();
   Vector3 & getPosition();
private:
	Model playerMod;
	Texture playerTex;
	Shader playerShader;
	GameObject player;
	
	Quaternion rotationOffset;
	Vector3 posOffset;
};

#endif/__PLAYER_H__**/
