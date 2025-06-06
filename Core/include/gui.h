#ifndef __GUI_H__
#define __GUI_H__ 

#include "mesh.h"
#include "transform.h"
#include "texture.h" 
#include <vector>
//class Texture; 

class GUI
{
public:
	GUI(); 
   ~GUI(); 
  
	Transform transform;
	//std::vector<Texture> texture; 
	Texture* texture; 
	Model* model;  
	
	void referenceModel(Model & m); 
	void referenceTexture(Texture & t); 
	//void clearModelReference(); //sets rectModel again; 

	//static Model rectModel; //make this static and shared between all GUI instances 
};

#endif/*__GUI_H__*/
