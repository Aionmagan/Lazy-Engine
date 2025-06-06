#ifndef __BACK_GROUND_H__
#define __BACK_GROUND_H__

#include <LazyEngine.h>

class BG
{
public:
	BG();
   ~BG();
   
   void update();
   
private:
	Model bgMod;
	Texture bgTex; 
	Shader bgShader;
	GameObject bg;
	
	float vOffset;
};

#endif/*__BACK_GROUND_H__*/
