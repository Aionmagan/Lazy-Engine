#include "transform.h"
#include <cmath>
#include <mathcommon.h>

Transform::Transform()
{
	position = Vector(0.0f, 0.0f, 0.0f); 
	rotation = Quaternion(); 
	scale    = Vector(1.0f, 1.0f, 1.0f); 
	
	//forward = Vector(0.0f, 0.0f, 1.0f); 
	//right   = Vector(1.0f, 0.0f, 0.0f); 
	//up      = Vector(0.0f, 1.0f, 0.0f); 
	
	parent = NULL;
}

Transform::~Transform()
{

}

void Transform::rotateXYZ(float x, float y, float z)
{
    Quaternion q1, q2, q3; 
    
    q1 = Quaternion::Euler(x, 0.0f, 0.0f);
    q2 = Quaternion::Euler(0.0f, y, 0.0f); 
    q3 = Quaternion::Euler(0.0f, 0.0f, z); 
    
    q1 = (q3 * q2 * q1);
    
    rotation = q1;  
}

void rotateXYZ(const Vector & v)
{
    //rotateXYZ(v.x, v.y, v.z); 
}

void Transform::rotateZYX(float x, float y, float z)
{
    Quaternion q1, q2, q3; 
    
    q1 = Quaternion::Euler(x, 0.0f, 0.0f);
    q2 = Quaternion::Euler(0.0f, y, 0.0f); 
    q3 = Quaternion::Euler(0.0f, 0.0f, z); 
    
    q1 = (q1 * q2 * q3);
    
    rotation = q1;
}

void Transform::rotateZYX(const Vector & v)
{
    //rotateXYZ(v.x, v.y, v.z); 
}

void Transform::rotate(float x, float y, float z)
{
	//rotation.x += x; 
	//rotation.y += y; 
	//rotation.z += z; 
	eulerAngles = Vector(fmod(x+eulerAngles.x, 360.0f), 
                         fmod(y+eulerAngles.y, 360.0f), 
                         fmod(z+eulerAngles.z, 360.0f));
                          
	rotation *= Quaternion::Euler(x, y, z); 
}

void Transform::rotate(Vector & v)
{
	eulerAngles = Vector(fmod(v.x+eulerAngles.x, 360.0f), 
                         fmod(v.y+eulerAngles.y, 360.0f), 
                         fmod(v.z+eulerAngles.z, 360.0f));
                          
	rotation *= Quaternion::Euler(v); 
}
	
void Transform::translate(float x, float y, float z)
{
	position.x += x; 
	position.y += y; 
	position.z += z; 
}

void Transform::translate(Vector & v)
{
	position += v; 
}

void Transform::setParent(Transform & t)
{
	parent = &t; 
}

void Transform::lookAt(Vector target)
{
	Vector dir = target - position; 
	
	if (dir == Vector::Zero()) return; 
	
	dir = Vector::Normalize(dir);
	float x = RAD2DEG(-asinf(dir.y)); 
	float y = RAD2DEG(-atan2f(-dir.x, -dir.z)); 
	
	Quaternion q1 = Quaternion::Euler(0, y, 0); 
	Quaternion q = Quaternion::Euler(x, 0, 0) * q1;
	//Quaternion q = Quaternion::Euler(x, y, 0);
	//q = Quaternion::Normalize(q);
	
	rotation = q;  
}

/*void Transform::updateChilds()
{
	child->position += position; 
}*/

Vector Transform::forward()
{
	return rotation * Vector::Forward(); 
}
 
Vector Transform::right()
{
	return rotation * Vector::Right(); 
}

Vector Transform::up()
{
	return rotation * Vector::Up(); 
}
