#ifndef __LE_MATERIAL_H__
#define __LE_MATERIAL_H__

#include <vector.h>

struct Material
{ 	
	Vector3 ambient; 
	Vector3 diffuse;
	Vector3 specular; 
	float shininess; 
	
	Material();	
	
	void setAmbient(float x, float y, float z); 
	void setAmbient(Vector3 v); 
	
	void setDiffuse(float x, float y, float z); 
	void setDiffuse(Vector3 v); 
	
	void setSpecular(float x, float y, float z); 
	void setSpecular(Vector3 v); 
	
	void setShininess(float s); 
};

#endif/*__LE_MATERIAL_H__*/
