#include "camera.h"

#include <GL/gl.h>
#include <GL/glu.h>
#include <cstdio>

//glm::mat4 Camera::view;
//glm::mat4 Camera::invView; 
Matrix4 Camera::view; 
Matrix4 Camera::invView;
Matrix4 Camera::BB; 
Matrix4 Camera::viewRot; 
Vector3 Camera::viewPos; 

Camera::Camera()
{

}

Camera::~Camera()
{

}

void Camera::applyView()
{
	//t = translate(glm::mat4(1.0f), glm::vec3(-transform.position.x,
	 //           			   		-transform.position.y,
	  //          			   		-transform.position.z));
	//t.transpose();               
	//t.translate(-transform.position.x,
	//	   		-transform.position.y,
	//	   		-transform.position.z);	
	//r.quaternionToMatrix(transform.rotation); 

	//r = glm::mat4_cast(glm::quat(transform.rotation.w,
	//							 transform.rotation.x,
	 //                         	 transform.rotation.y,
	  //                        	 transform.rotation.z));
	
	//view = r * t; 
	//view = t * r; 
	
	t.translate(-transform.position.x,
	            -transform.position.y,
	            -transform.position.z);
	//t.transpose();               
	r.quaternionToMatrix(transform.rotation); 
	
	view = r * t; 
	viewRot = r; 
	viewPos.x = transform.position.x; 
	viewPos.y = transform.position.y; 
	viewPos.z = transform.position.z; 
	//view = t * r; 
	
	r.transpose(); 
	BB = r; 
	//view.elem[0]  = -view.elem[0];
	//view.elem[4]  = -view.elem[4];
	//view.elem[8]  = -view.elem[8];
	//view.elem[12] = -view.elem[12];
#if 0	
	printf("view:\n %f %f %f %f\n %f %f %f %f\n %f %f %f %f\n %f %f %f %f\n", 
			view[0][0], view[0][1], view[0][2], view[0][3], 
			view[1][0], view[1][1], view[1][2], view[1][3],
			view[2][0], view[2][1], view[2][2], view[2][3],
			view[3][0], view[3][1], view[3][2], view[3][3]);
#endif
	//view.elem[0]  = -view.elem[0];
	//view.elem[4]  = -view.elem[4];
	//view.elem[8]  = -view.elem[8];
	//view.elem[12] = -view.elem[12];
	
}

void Camera::setViewport(int x, int y, int width, int height)
{
	glViewport(x, y, width, height); 
}
