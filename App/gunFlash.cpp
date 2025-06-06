#include "gunFlash.h" 
#include<cstdio>
GunFlash::GunFlash()
{
	flashMod.load("Assets/decal.obj"); 
	flashTex.load("Assets/flash1.png"); 
	flash.reference(flashMod); 
	flash.reference(flashTex); 
	flash.shaders.load("Shader/gunFlash_vs.glsl", "Shader/gunFlash_fs.glsl");
	flash.transform.scale = 0.25f;
	startp = NULL;  
	flashTime = 0; 
	
	flashLight.setType(LightType::POINT);
	flashLight.setColor(0.41f, 0.25f, 0.12f); 
	flashLight.setEnable(false);
	
	flashLight.linear = 3.01f; 
	flashLight.quadratic = 10.73f;
	
	testLight.setType(LightType::POINT);
	testLight.setColor(0.89f, 0.21f, 0.04f); 
	testLight.setEnable(false);
	
	testLight.linear = 0.01f; 
	testLight.quadratic = 0.3f;
	//flashLight.transform.position.y = 1000; 
}
 
GunFlash::~GunFlash()
{

}

void GunFlash::update()
{
	if (gInput.buttonDown(BN_R1))
	{
		static float r = 0; 
		r += 53.3f; 
		if (r > 360.0f) r = 0; 
		flash.transform.position = startp->position + startp->right() * 0.55f + startp->up() * 0.15f; 
		flash.transform.rotation = startp->rotation * Quaternion::AxisAngle(0, 0, 1, r);
		flashLight.transform.position = startp->position + startp->right() * 0.55f + startp->up() * 0.15f;
		flashLight.setEnable(true); 
		flashTime = gTime.getTicks() + 20; 
		//printf("got here\n"); 
	}
	
	if (gInput.button(BN_TRIANGLE))
		testLight.setEnable(true);
	static float p = 0; 
	static float c = 0;
	p += 11.0f; 
	c += 0.1f; 
	Quaternion q = Quaternion::Euler(0, p, 0); 
	testLight.transform.position = Vector3(0, 1, 0) - q * Vector3::Forward() * 15;
	testLight.setColor(0.5f*(Mathf::Sin(c*0.1f)+1.0), 0.5f*(Mathf::Sin(c*0.3f)+1.0), 0.5f*(Mathf::Cos(c*0.1f)+1.0));
	//flashLight.transform.position = startp->position + startp->right() * 0.55f + startp->up() * 0.15f;
}

void GunFlash::queue()
{
	if (flashTime > gTime.getTicks())
	{
		gRenderer.queue(flash); 
	}else
	{
		flashLight.setEnable(false);
	}
}

void GunFlash::setTransform(Transform & t)
{
	startp =& t; 
}
