#ifndef __TRANSFORM_H__
#define __TRANSFORM_H__

#include "vector.h"
#include "quaternion.h" 
#include "matrix.h" 

#include "mathcommon.h" 

class Transform
{
private: 
	
public: 
	Transform* parent; 
	Matrix4 selfMatrix; 
	//glm::mat4 selfMatrix; 
	
	Transform();
   ~Transform(); 
    
	Vector position; 
	//Vector rotation; 
	Vector scale; 
	Vector eulerAngles;
	Quaternion rotation; 
	
	void rotateXYZ(float x, float y, float z); 
	void rotateXYZ(const Vector & v);
	
	void rotateZYX(float x, float y, float z);
	void rotateZYX(const Vector & v); 
	 
	void rotate(float x, float y, float z);
	void rotate(Vector & v); 
	
	void translate(float x, float y, float z);
	void translate(Vector & v);  
	
	void setParent(Transform & t);
	//void updateChilds();  
	void lookAt(Vector target); 
	
	Vector forward(); 
	Vector right(); 
	Vector up(); 
};

#endif/*__TRANSFORM_H__*/
