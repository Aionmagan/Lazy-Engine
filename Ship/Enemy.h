#ifndef __ENEMY_H__
#define __ENEMY_H__

#include <LazyEngine.h>
#include <string>

class Enemy
{
public:
	Enemy(std::string filename, Vector3 pos);
	Enemy();
   ~Enemy();
	
	void init(std::string filename, Vector3 pos);
	void update();
	void setPosition(Vector3 pos);
	Vector3 & getPosition();
private:
	Model enemyMod;
	Texture enemyTex; 
	Shader enemyShader;
	GameObject enemy; 

	int life;
	Quaternion rotationOffset;
};

#endif/*__ENEMY_H__*/
