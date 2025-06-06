#include "BackGround.h" 

#include <LazyEngine.h>

BG::BG()
{
	bgMod.load("Assets/BG.obj");
	bgTex.load("Assets/bg.png"); 
	//CHANGE THIS
	bgShader.load("Shader/bg_vs.glsl", "Shader/bg_fs.glsl");
	bg.reference(bgMod, bgTex, bgShader);
	
	bg.transform.position.z = -25; 
	bg.transform.scale = Vector3(100, 60, 1);
	
	vOffset = 0; 
	gRenderer.queue(bg);
}

BG::~BG()
{

}

void BG::update()
{
	vOffset += gTime.deltaTime() * (-gInput.lyAxis()*0.3f + 1);
	bgShader.use();
	bgShader.setFloat("vOffset", vOffset);
}
