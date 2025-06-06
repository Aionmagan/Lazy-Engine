#ifndef __LIGHTS_H__
#define __LIGHTS_H__ 

#include <vector.h>
#include <transform.h>

enum LightType
{
	DIRECTIONAL, 
	POINT,
	SPOT
};

struct Light
{
	LightType lightType; 
	Vector3 color;
	float constant; 
	float linear; 
	float quadratic; 
	float cutoff; 
	bool isEnabled; 
	
	Light();
   ~Light();
   
   	//position | direction
   	Transform transform; 
   	
   	void setType(LightType type);
   	void setEnable(bool enable);
   	//void setColor(int r, int g, int b); 
   	void setColor(float r, float g, float b);
private: 
	int lightIndex; 
};

#endif/*__LIGHTS_H__*/
