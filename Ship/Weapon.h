#ifndef __WEAPON_H__
#define __WEAPON_H__

#include <LazyEngine.h>

#define BULLET_AMOUNT 20

class Weapon
{
public: 
	Weapon();
   ~Weapon();
   
   	void update();
   	void shoot(Vector3 position);
   	void setShootDirection(Vector3 dir);
   	void setShootSpeed(float speed);
private:
	Model shotMod;
	Texture shotTex;
	Shader shotShader; 
	GameObject shotList[BULLET_AMOUNT];
	Vector3 shotListDir[BULLET_AMOUNT];
	//Quaternion shotListRot[BULLET_AMOUNT];
	
	int shotRate; 
	int shotTimer;
	Vector3 shotDir;
	Quaternion shotRot;
	float shotSpeed;
};

#endif/*__WEAPON_H__*/
