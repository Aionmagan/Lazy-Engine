#ifndef __GUN_FLASH_H__
#define __GUN_FLASH_H__

#include <LazyEngine.h>

class GunFlash
{
public:
	GunFlash(); 
   ~GunFlash(); 
   
   	void update(); 
   	void queue(); 
   	void setTransform(Transform & t); 
private:
	Model flashMod; 
	Texture flashTex; 
	GameObject flash;
	
	Transform* startp;
	
	int flashTime;  
	Light flashLight; 
	Light testLight;  
};

#endif/*__GUN_FLASH_H__*/
