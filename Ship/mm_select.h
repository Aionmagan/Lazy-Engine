#ifndef __MM_SELECT_H__
#define __MM_SELECT_H__

#include <LazyEngine.h>

#define PLAYER_AMOUNT 4

class MM_Select
{
public: 
	MM_Select();
   ~MM_Select();
   
   	void SelectPlayer();
   	
private:
	
	Model mod_ship_list[PLAYER_AMOUNT];
	Texture tex_ship_list[PLAYER_AMOUNT];
	
	Shader normalShader; 
	Shader shadowShader; 
	
	GameObject ship;
	GameObject shipShadow; 
};

#endif/*__MM_SELECT_H__*/
