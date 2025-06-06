#include "skybox.h" 
#include "render.h" 

Skybox::Skybox(Texture & skyTex)
{
	//generate cube geometry... but i don't want to use geometry shaders
	//generate shaders as well later 
	
	
}

Skybox::Skybox(std::string skyboxTexture)
{
	//generate cube geometry... but i don't want to use geometry shaders
	//generate shaders as well later 
	
	cubeMod.load("../Core/static/skybox.obj"); 
	cubeTex.load(skyboxTexture); 
	go.reference(cubeMod, cubeTex); 
	go.shaders.load("../Core/static/skybox_vs.glsl", 
	                "../Core/static/skybox_fs.glsl");
	                
	gRenderer.setSkybox(*this); 
}

Skybox::~Skybox()
{
	gRenderer.removeSkybox();
}

void Skybox::setAmbient(float x, float y, float z)
{
	go.material.setAmbient(x, y, z); 
}

