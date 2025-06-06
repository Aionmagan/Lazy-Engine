#include "leafEffect.h"
#include <cstdio>
LeafEffect::LeafEffect()
{
	for(int i = 0; i < 8; ++i)
	{
		char str[256];
		sprintf(str, "Assets/leafEffect/%d.png", i+1);
		std::string filename = str;
		leafTex[i].load(filename);
	}
	
	int particleAmount = 1000; 
	Shader shaders("Shader/testEffect_vs.glsl", "Shader/testEffect_fs.glsl");
	setShaders(shaders);
	initParticles("Assets/pe1.png", particleAmount);
	
	velocity.resize(particleAmount); 
	acceleration.resize(particleAmount); 
}

LeafEffect::~LeafEffect()
{

}

void LeafEffect::setCamera(Camera & c)
{
	camp =& c; 
}

void LeafEffect::update()
{
	Vector3 camPos= camp->transform.position; 
	transform.position = camPos+Vector::Right() * 2.0f; 
	static int sTimer = 0; 
	
	if (sTimer < gTime.getTicks())
	{
		int i = spawn(); 
		//printf("wtf %d\n", i);
		particles[i].transform.position.x += Mathf::RandomRangef(-14, 14); 
		particles[i].transform.position.z += Mathf::RandomRangef(-14, 14);		
		particles[i].transform.position.y += 20; 
		
		particles[i].texID = leafTex[Mathf::RandomRangei(0, 8)].id;
		particles[i].transform.scale = 0.4f;
		
		velocity[i] = Vector3(Mathf::RandomRangef(-3, -1),
							  Mathf::RandomRangef(-3, -5),
		                      Mathf::RandomRangef(-3, -1)); 
		                      
		acceleration[i] = Vector3(Mathf::RandomRangef(-1, 1), 
							      -2, 
							      Mathf::RandomRangef(-1, 1));
		
		sTimer = 4 + gTime.getTicks();
	}
	
	for(int i = 0; i < particles.size(); ++i)
	{
		if (particles[i].lifeSpan > 0)
		{
			velocity[i] += acceleration[i] * gTime.deltaTime();
			particles[i].transform.position += velocity[i] * gTime.deltaTime();
			particles[i].lifeSpan -= 0.4f; 
		}
	}
}

void LeafEffect::queueEffect()
{
	queue(); 
}
