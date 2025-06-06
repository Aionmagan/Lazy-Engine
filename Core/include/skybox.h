#ifndef __LE_SKYBOX_H__
#define __LE_SKYBOX_H__

#include <string>

#include "object.h"
#include "mesh.h"
#include "texture.h"

class Skybox
{
public:
	GameObject go;	
	
	Skybox(Texture & skyTex);
	Skybox(std::string skyboxTexture); 
   ~Skybox();
   
   	void setAmbient(float x, float y, float z); 
   	
private: 
	Model cubeMod;//?? maybe
	Texture cubeTex;
};

#endif/*__LE_SKYBOX_H__*/
