#ifndef __OBJECT_H__
#define __OBJECT_H__

#include "vector.h"
//#include "mesh.h"
//#include "transform.h"
//#include "texture.h" 
#include "md2.h"
#include "ply.h"
//#include "gui.h" 
#include "particle.h"
#include "shaderClass.h" 
#include "material.h" 

#include <string>
#include <vector>


class GameObject //: public Model
{
//private: 
	
public:
	Transform transform; 
	//Texture*   texture; 
	std::vector<Texture *> texture; 
	//int textureIndex; 
	//Texture texture[8];
	
	Model*    model; 
	PlyMesh*  ply;
	MD2*      md2; 
	Md2LocalData md2state; 
	
	Material material; 
	Shader shaders; 
	//just an idea
	bool isActive;
	float uOffset; 
	float vOffset; 
	//Vector position; 
	//Vector rotation; 
	//Vector scale; 

	//GameObject(std::string filename):Model(filename){}
	//GameObject(Model & model){this->model = &model;}  
	//GameObject(const char* vs, const char* fs);
	GameObject(); 
	GameObject(Model & m, Texture & t, Shader & s);
   ~GameObject(); 
   	
   	void setActive(bool active);
   	//outdated
   	void referenceModel(Model & m);
   	void referenceModel(PlyMesh & m);  
   	void referenceModel(MD2 & m); 
   	void referenceTexture(Texture & t);
   	//outdated
   	
   	void reference(Model & m); 
   	void reference(Texture & t);
   	void reference(Texture & t, int index);
   	void reference(Model & m, Texture & t);
   	
   	//not needed but for consistancy
   	void reference(Shader & s); 
   	void reference(Material & m);
   	void reference(Model & m, Texture & t, Shader & s); 
   	void reference(Model & m, Texture & t, Shader & s, Material & mat); 
   	
};

#endif/*__OBJECT_H__*/
