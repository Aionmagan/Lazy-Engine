#include <particle.h>
#include <algorithm>
#include "render.h" 

ParticleEmitter::ParticleEmitter()
{

}

ParticleEmitter::~ParticleEmitter()
{
	particles.clear();
}

void ParticleEmitter::initParticles(std::string filename, int particleAmount)
{
#if 0 
	VertexData vd[]=
	{
		{.vx = -1.0f, .vy =  1.0f, .vz = 0.0f, .tu = 0.0f, .tv = 1.0f, .nx = 0.0f, .ny = 0.0f, .nz = -1.0f},
		{.vx =  1.0f, .vy = -1.0f, .vz = 0.0f, .tu = 1.0f, .tv = 0.0f, .nx = 0.0f, .ny = 0.0f, .nz = -1.0f},
		{.vx = -1.0f, .vy = -1.0f, .vz = 0.0f, .tu = 0.0f, .tv = 0.0f, .nx = 0.0f, .ny = 0.0f, .nz = -1.0f},
		{.vx = -1.0f, .vy =  1.0f, .vz = 0.0f, .tu = 0.0f, .tv = 1.0f, .nx = 0.0f, .ny = 0.0f, .nz = -1.0f},
		{.vx =  1.0f, .vy =  1.0f, .vz = 0.0f, .tu = 1.0f, .tv = 1.0f, .nx = 0.0f, .ny = 0.0f, .nz = -1.0f},
		{.vx =  1.0f, .vy = -1.0f, .vz = 0.0f, .tu = 1.0f, .tv = 0.0f, .nx = 0.0f, .ny = 0.0f, .nz = -1.0f},		
	};

	for(int i = 0; i < 6; ++i)
		particleModel.data.push_back(vd[i]);
#else 
	particleModel.load("../Core/static/quad.obj"); 		
#endif

	Particle p; 
	//p.transform.setParent(transform); 
	texture.load(filename);
	p.model =& particleModel; 
	p.materialp =& particleMaterial; 
	p.texID = texture.id; 
	p.shaders = particleShader;
	p.lifeSpan = 0; 
	
	for(int i = 0; i < particleAmount; ++i)
		particles.push_back(p);
}

void ParticleEmitter::setShaders(Shader & s)
{
	particleShader = s; 
}

int ParticleEmitter::spawn()
{
	int particleAmount = particles.size();
	for(int i = 0; i < particleAmount; ++i)
	{
		if (particles[i].lifeSpan > 0) continue;
		particles[i].transform.position = transform.position;
		particles[i].lifeSpan = 100; 
		return i;
	}
}

void ParticleEmitter::queue()
{
	gRenderer.queue(*this);
	
#if 1
	int size = particles.size(); 
	for(int i = 0; i < size; ++i)
		if (particles[i].lifeSpan > 0)
			gRenderer.queue(particles[i]); 
#else
	std::sort(particles.begin(), particles.end(), std::greater<Particle>());
	int size = particles.size(); 
	for(int i = 0; i < size; ++i)
		if (particles[i].lifeSpan > 0)
			gRenderer.queue(particles[i]); 
#endif
}
