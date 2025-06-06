#include "enemy.h" 

Enemy::Enemy()
{
	enemyMod.load("Assets/ghoul.obj");
	enemyTex.load("Assets/ghoul.png"); 
	enemyNrm.load("Assets/ghoul_NRM.png"); 
	
	enemy.reference(enemyMod); 
	enemy.reference(enemyTex); 
	enemy.reference(enemyNrm); 
	
	enemyMat.shininess = 32.0f; 
	
	enemy.shaders.load("Shader/enemy_vs.glsl", "Shader/enemy_fs.glsl");
	enemy.material = enemyMat; 
	enemy.transform.position.y = 0.0f;
	enemy.transform.position.z = 10.75f;
}

Enemy::~Enemy()
{

}

void Enemy::update()
{

}

void Enemy::queue()
{
	gRenderer.queue(enemy); 
}
