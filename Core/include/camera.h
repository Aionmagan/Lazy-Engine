#ifndef __LE_CAMERA_H__
#define __LE_CAMERA_H__

#include "matrix.h"
#include "vector.h" 
#include "transform.h"
#include "mathcommon.h"

class Camera
{
public: 
	Camera(); 
   ~Camera(); 
   
    Transform transform; 
   	
   	void applyView();
   	void setViewport(int x, int y, int width, int height);  
   
private:
	//glm::mat4 r;
	//glm::mat4 t;  
	Matrix4 r, t; 
public:
	//static glm::mat4 view; 
	//static glm::mat4 invView; 

	//rename this shit better lmao
	static Matrix4 view; 
	static Matrix4 invView;
	static Matrix4 BB;  
	static Matrix4 viewRot; 
	static Vector3 viewPos;
	//bool firstPersonView;

};

#endif/*__LE_CAMERA_H__*/
