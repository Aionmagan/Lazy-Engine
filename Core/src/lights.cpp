#include <lights.h>
#include <cstdio>
#include <render.h> 
#include <mathf.h>

Light::Light()
{
	isEnabled = true; 
	color = Vector3(1.0f, 1.0f, 1.0f);
	lightType = LightType::DIRECTIONAL; 
	transform.position = Vector3::Forward(); 
	lightIndex = gRenderer.sendLightToList(*this);
	
	constant = 1.0f; 
	linear = 0.09f; 
	quadratic = 0.032f;
	
	cutoff = 0; 
}

Light::~Light()
{
	gRenderer.removeLightFromList(lightIndex); 
}

void Light::setType(LightType type)
{
	lightType = type;
}

void Light::setEnable(bool enable)
{
	isEnabled = enable;
}

#if 0
void Light::setColor(int r, int g, int b)
{
	color.x = Mathf::Clamp01(r/255.0f); 
	color.y = Mathf::Clamp01(g/255.0f);
	color.z = Mathf::Clamp01(b/255.0f); 
}
#endif 

void Light::setColor(float r, float g, float b)
{
	color.x = r;
	color.y = g;
	color.z = b;
}
