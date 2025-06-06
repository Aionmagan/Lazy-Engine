#include "testParticle.h"
//#include <sstream>

TestEffect::TestEffect(int es)
{
	//emitterMod.load("../Core/static/quad.obj");//("Assets/emitter.obj"); 
	//Texture tmpTex;
	effectSelection = es;
	spawnTimer = 0;
	//std::stringstream ss;
	std::string filename; 
	for(int i = 240; i > 0; --i)
	{
		char str[256];
		
		if (effectSelection)
		{
		sprintf(str, "Assets/fireEffect/%d.png", i);
		filename = str;
		fireTex[i-1].load(filename); 
		}else
		{
		sprintf(str, "Assets/smokeEffect/%d.png", i);
		filename = str;
		smokeTex[240-i].load(filename); 
		}
		//tmpTex.load(filename);
		//fireTex.push_back(tmpTex);
	}
	
	emitterMod.load("Assets/emitter.obj"); 
   	emitterTex.load("Assets/pe2.png");
   	emitter.reference(emitterMod, emitterTex);
   	emitter.shaders.load("Shader/emitter_vs.glsl", "Shader/emitter_fs.glsl"); 
    //emitter.transform.scale = 1000;
    if (effectSelection)
    	shaders.load("Shader/testEffect1_vs.glsl", "Shader/testEffect1_fs.glsl");
    else
		shaders.load("Shader/testEffect_vs.glsl", "Shader/testEffect_fs.glsl");
	setShaders(shaders); 
	int particleAmount = 1000;
	initParticles("Assets/pe1.png", particleAmount);
	velocity.resize(particleAmount); 
	acceleration.resize(particleAmount);
	animation.resize(particleAmount);
	
	lit.setType(LightType::POINT);
	lit.setColor(0.41f, 0.25f, 0.12f);
	lit.linear = 0.01f; 
	lit.quadratic = 0.3f; 
	lit.setEnable(true);
}

TestEffect::~TestEffect()
{

}

void TestEffect::update()
{
	static float r; 
	//static int spawnTimer = 0; 
 
	r += 0.1;
	//r = 90.0;// + (90.0f * effectSelection);
	
	Quaternion q;
	q = Quaternion::Euler(0, r, 0);
	transform.position = q * Vector::Forward() * 13.0f + Vector::Up() * 1.0f;
	emitter.transform.position = transform.position;
	lit.transform.position = transform.position; 
	
	if (spawnTimer < gTime.getTicks())
	{
		//printf("spawn\n");
		spawnTimer = 2 + gTime.getTicks();
		int i = spawn(); 
		//if (effectSelection)
		//	printf("i = %d\n", i);
		particles[i].transform.position.x += Mathf::RandomRangef(-1, 1); 
		particles[i].transform.position.z += Mathf::RandomRangef(-1, 1); 
		particles[i].transform.position.y += 1.0f;
		velocity[i] = Vector3(Mathf::RandomRangef(-0.1f, 0.1f), 
							   Mathf::RandomRangef(3, 5), 
							   Mathf::RandomRangef(-0.1f, 0.1f));
		acceleration[i] = Vector3(Mathf::RandomRangef(-1, 1), 
							      2, 
							      Mathf::RandomRangef(-1, 1));
		particles[i].transform.scale = 2.0f;
		animation[i].texIndex = Mathf::RandomRangei(0, 10);
		//particles[i].texID = fireTex[0].id; 
		//animation[i].animTimer = 50 + gTime.getTicks();
	}
	//printf("spawnTimer = %d\n", spawnTimer);
	for(int i = 0; i < particles.size(); ++i)
	{
		if (particles[i].lifeSpan > 0)
		{
			velocity[i] += acceleration[i] * gTime.deltaTime();
		//printf("i %d\n", i);
			//particles[i].transform.scale -= 1.0f * gTime.deltaTime();
			if (particles[i].transform.scale.x < 0)
				particles[i].transform.scale = Vector3::Zero();  
			particles[i].transform.position += velocity[i] * gTime.deltaTime();
			//particles[i].transform.position.y -= 5.0f* gTime.deltaTime();
			if (effectSelection)
				particles[i].lifeSpan -= 1.5f; 
			else
				particles[i].lifeSpan -= 0.5f; 
			
			if (animation[i].animTimer < gTime.getTicks())
			{		
				float d = Vector::Distance(particles[i].transform.position, transform.position);							
				
				if (d > 8.0f)
					particles[i].transform.scale += 1.0f * gTime.deltaTime();

#if 0					
				if (d > 4.0f)
				{
					particles[i].texID = smokeTex[animation[i].texIndex++].id;
					animation[i].animTimer = 10 + gTime.getTicks();
				}else
				{
					particles[i].texID = fireTex[animation[i].texIndex++].id;
					animation[i].animTimer = 1 + gTime.getTicks();
				}
#else 
				if (effectSelection)
				{
					particles[i].texID = fireTex[animation[i].texIndex++].id;
					animation[i].animTimer = 10 + gTime.getTicks();
				}else
				{
					particles[i].texID = smokeTex[animation[i].texIndex++].id;
					animation[i].animTimer = 10 + gTime.getTicks();
				}
#endif								
				if (animation[i].texIndex > 239)
					animation[i].texIndex = 0;
				//animation[i].animTimer = 10 + gTime.getTicks();
				//printf("texIndex %d | %d\n", particles[i].texID, animation[i].texIndex);
			}
			//particles[i].lifeSpan = particles[i].transform.position.y; 
		}
	}
}

void TestEffect::queueEffect()
{
	gRenderer.queue(emitter); 
	queue();
}
