#include <material.h>
	
Material::Material()
{
	ambient = Vector3(1.0f); 
	diffuse = Vector3(1.0f);
	specular = Vector3(1.0f); 
	shininess = 0; 
}

void Material::setAmbient(float x, float y, float z)
{
	ambient.x = x;
	ambient.y = y;
	ambient.z = z; 
}

void Material::setAmbient(Vector3 v)
{
	setAmbient(v.x, v.y, v.z); 
}

void Material::setDiffuse(float x, float y, float z)
{
	diffuse.x = x;
	diffuse.y = y;
	diffuse.z = z;
}

void Material::setDiffuse(Vector3 v)
{
	setDiffuse(v.x, v.y, v.z); 
}

void Material::setSpecular(float x, float y, float z)
{
	specular.x = x;
	specular.y = y;
	specular.z = z;
}

void Material::setSpecular(Vector3 v)
{
	setSpecular(v.x, v.y, v.z); 
}

void Material::setShininess(float s)
{
	shininess = s;
}
