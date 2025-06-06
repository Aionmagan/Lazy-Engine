#include "Enemy.h"

Enemy::Enemy(std::string filename, Vector3 pos)
{
	init(filename, pos);
}

Enemy::Enemy()
{
	
}

Enemy::~Enemy()
{

}

void Enemy::init(std::string filename, Vector3 pos)
{
	enemyMod.load(filename+".obj");
	enemyTex.load(filename+".png"); 
	enemyShader.load("Shader/mm_normal_vs.glsl","Shader/mm_normal_fs.glsl");
	enemy.reference(enemyMod, enemyTex, enemyShader);
	enemy.transform.scale = 100;
	setPosition(pos);
	
	auto q = Quaternion::Euler(0, 0, 0) * 
	         Quaternion::Euler(90, 0, 0);
	rotationOffset = q; 
	//enemy.transform.rotation = q; 	

	gRenderer.queue(enemy);
}

void Enemy::update()
{
	static float r1 = 0; 
	static float r2 = 0;
	
	r1 += 0.03f * gTime.deltaTime();
	r2 += 0.08f * gTime.deltaTime();
	 
	float c = 20.0f * Mathf::Cos(r1); 
	float s = 30.0f * Mathf::Sin(r2); 
	enemy.transform.rotation = Quaternion::Euler(c, s, 0) * rotationOffset;
}

void Enemy::setPosition(Vector3 pos)
{
	enemy.transform.position = pos;
}

Vector3 & Enemy::getPosition()
{
	return enemy.transform.position;
}
