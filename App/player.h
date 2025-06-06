#ifndef __PLAYER_H__
#define __PLAYER_H__

#include<LazyEngine.h>
#include"charState.h"

class Player
{
public: 
	Player(); 
   ~Player(); 
   
   	void update();
   	void queue(); 
   	
   	Transform & getTransform();   	
   	Camera & getCamera(); 
   	
private:
	Model playerMod; 
	Texture playerTex;
	Texture playerNrm; 
	Material playerMat; 
	GameObject player;
	
	Model gunMod; 
	Texture gunTex; 
	Texture gunNrm; 
	Material gunMat; 
	GameObject gun;
	
	Camera playerCam;
	CharacterState playerState; 
	
	Transform origin; 
	
	Vector3 playerLookDir; 
	float playerHeight; 
	float slidingTimer; 
	float speed; 
	Transform localForward;
	
	void IdleState();
	void WalkState();
	void RunState();
	void CrouchState(); 
	void SlidingState();
};

#endif/*__PLAYER_H__*/
