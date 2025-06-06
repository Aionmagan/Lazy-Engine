#include "Weapon.h"

#include <cstdio>

Weapon::Weapon()
{
	shotMod.load("Assets/shot.obj");
	shotTex.load("Assets/shot.png");
	shotShader.load("Shader/mm_normal_vs.glsl", "Shader/mm_normal_fs.glsl"); 
	for(int i = 0; i < BULLET_AMOUNT; ++i)
	{
		shotList[i].reference(shotMod, shotTex, shotShader);
		shotList[i].transform.scale = 2.5f;
		shotList[i].setActive(false);
		gRenderer.queue(shotList[i]);
	}
	
	shotTimer = 0; 
	shotRate = 160;
	shotDir = 1;
	shotSpeed = 150.0f;
}

Weapon::~Weapon()
{

}

void Weapon::update()
{
	int areActive = 0;
	for(int i = 0; i < BULLET_AMOUNT; ++i)
	{
		if(shotList[i].isActive)
		{
#if 1
			shotList[i].transform.position += (shotSpeed * gTime.deltaTime()) * shotListDir[i];
			
			if (shotList[i].transform.position.y > 40.0f)
					shotList[i].setActive(false); 
			if (shotList[i].transform.position.y < -40.0f)
					shotList[i].setActive(false); 			
#else		
			shotList[i].transform.position.y += (shotSpeed * gTime.deltaTime()) * shotDir;
			if (shotDir >= 0)
			{
				if (shotList[i].transform.position.y > 40.0f)
					shotList[i].setActive(false); 
			}else
			{
				if (shotList[i].transform.position.y < -40.0f)
					shotList[i].setActive(false); 
					printf("pos y %f\n", shotList[i].transform.position.y);
			}
#endif			
				areActive++;
		}
	}
	
	//printf("Are Active %d / %d\n", areActive, BULLET_AMOUNT);
}

void Weapon::shoot(Vector3 position)
{
	if (shotTimer < gTime.getTicks())
	{
		for(int i = 0; i < BULLET_AMOUNT; ++i)
		{
			if(shotList[i].isActive == false)
			{
				shotList[i].transform.position = position;
				shotList[i].transform.rotation = shotRot;
				shotListDir[i] = shotDir; 
				shotList[i].setActive(true);
				break;
			}
		}
		
		shotTimer = gTime.getTicks() + shotRate;
	}
}

void Weapon::setShootDirection(Vector3 dir)
{
#if 1
	shotDir = dir.normalized();
	auto r = Mathf::Rad2Deg(Mathf::Atan2(-dir.x, dir.y));
	shotRot = Quaternion::Euler(0, 0, r);

#else
	shotDir = dir;

	float rot = (dir>=0) ? 0.0f : 180.0f;
	for(int i = 0; i < BULLET_AMOUNT; ++i)
	{
		shotList[i].transform.rotation = Quaternion::Euler(0, 0, rot);
	}
#endif
}

void Weapon::setShootSpeed(float speed)
{
	shotSpeed = speed;
}
