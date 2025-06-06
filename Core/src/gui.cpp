#include <gui.h>
#include <cstdio>

#if defined(__PC__)
//Model GUI::rectModel("Assets/GUI.obj");
#else
//Model GUI::rectModel("ASSETS/GUI.OBJ");
#endif

GUI::GUI()
{
printf("CALLED GUI CONSTRUCTOR\n"); 
	//model = &GUI::rectModel; 
	model = NULL;
}

GUI::~GUI()
{
	
}

void GUI::referenceModel(Model & m)
{
	model = &m; 
}

void GUI::referenceTexture(Texture & t)
{
	texture = &t; 
}

//void GUI::clearModelReference()
//{
	//model = &GUI::rectModel; 
//}
