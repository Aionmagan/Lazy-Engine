#include "object.h"

GameObject::GameObject()
{
	model = NULL; 
	ply = NULL;
	md2 = NULL; 
	//texture = NULL; 
	
	md2state.current_frame = 0; 
	md2state.next_frame = 1; 
	md2state.last_anim_select = 0; 
	md2state.anim_select = 0; 
	md2state.lerp = 0.0f; 
	
	uOffset = 0.0f; 
	vOffset = 0.0f;
	
	isActive = true;
	//textureIndex = 0; 
	//for(int i = 0; i < 8; ++i)
	//	texture[i] = NULL; 
}

GameObject::GameObject(Model & m, Texture & t, Shader & s)
{
	isActive = true;
	reference(m, t, s); 
}

GameObject::~GameObject()
{
	if (model)
	{
		model->freeMemory(); 
		model = NULL;
	}
		
	if (md2)
	{
		md2->freeMemory(); 
		md2 = NULL; 
	}
}

void GameObject::setActive(bool active)
{
	isActive = active;
}

void GameObject::referenceModel(Model & m)
{
	model =& m; 
}

void GameObject::referenceModel(PlyMesh & m)
{
	ply =& m; 
}

void GameObject::referenceModel(MD2 & m)
{
	md2 =& m; 
} 

void GameObject::referenceTexture(Texture & t)
{
	//texture =& t; 
	texture.push_back(&t);
	//texture.push_back(t);
	//texture[textureIndex++] = &t; 
	//texture[textureIndex++] = t; 
}

void GameObject::reference(Model & m)
{
	model =& m; 
}

void GameObject::reference(Texture & t)
{
	texture.push_back(&t);
	//texture[textureIndex++] = &t; 
	//texture.push_back(t);
	//texture[textureIndex++] = t; 
}

void GameObject::reference(Texture & t, int index)
{
	texture.at(index) = &t;
}

void GameObject::reference(Model & m, Texture & t)
{
	reference(m); 
	reference(t); 
}

//not needed but for consistancy
void GameObject::reference(Shader & s)
{
	shaders = s; 
}

void GameObject::reference(Material & m)
{
	material = m; 
}

void GameObject::reference(Model & m, Texture & t, Shader & s)
{
	reference(m);
	reference(t); 
	reference(s);
}

void GameObject::reference(Model & m, Texture & t, Shader & s, Material & mat)
{
	reference(m);
	reference(t); 
	reference(s);
	reference(mat);
}
