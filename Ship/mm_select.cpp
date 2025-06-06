#include "mm_select.h" 
#include <cstdio>

#include "GameManager.h"

MM_Select::MM_Select()
{
	for(int i = 0; i < PLAYER_AMOUNT; ++i)
	{
		char str[512];
		sprintf(str,"Assets/Ship%d.obj", i);
		std::string s(str);
		mod_ship_list[i].load(s); 
		
		sprintf(str,"Assets/Ship%d.png", i);
		s = str;
		tex_ship_list[i].load(s);
	}
	
	normalShader.load("Shader/mm_normal_vs.glsl", "Shader/mm_normal_fs.glsl");
	shadowShader.load("Shader/mm_shadow_vs.glsl", "Shader/mm_shadow_fs.glsl");
	
	ship.reference(mod_ship_list[0], tex_ship_list[0], normalShader);
	shipShadow.reference(mod_ship_list[0], tex_ship_list[0], shadowShader);
	
	float xPos = -12;
	
	ship.transform.position.y = 3;
	
	ship.transform.position.x = xPos;
	shipShadow.transform.position.x = xPos;
	
	shipShadow.transform.scale.y = -1;
	shipShadow.transform.position.y = -10;
	
	gRenderer.queue(ship);
	gRenderer.queue(shipShadow);
}

MM_Select::~MM_Select()
{

}

void MM_Select::SelectPlayer()
{
	static int selected = 0;
	static float rot = 0;
	
	rot += 1.0f; 
	
	if (gInput.buttonDown(BN_LEFT))
		selected++; 
	if (gInput.buttonDown(BN_RIGHT))
		selected--; 
		
	if (selected > PLAYER_AMOUNT-1)
		selected = 0; 
	if (selected < 0)
		selected = PLAYER_AMOUNT-1;
		
	ship.reference(mod_ship_list[selected]);
	shipShadow.reference(mod_ship_list[selected]); 
	ship.reference(tex_ship_list[selected], 0);
	shipShadow.reference(tex_ship_list[selected], 0); 
	
	ship.transform.rotation = Quaternion::Euler(0, rot, 0); 
	shipShadow.transform.rotation = ship.transform.rotation;
	
	if (gInput.buttonDown(BN_CROSS))
		gameManager.SetSelectedShip(selected);
}
