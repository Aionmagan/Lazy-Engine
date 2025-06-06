#ifndef __LE_PARTICLE_H__
#define __LE_PARTICLE_H__

#include <string>
#include <vector>
#include "mesh.h" 
#include "vector.h" 
#include "transform.h" 
#include "texture.h"
#include "shaderClass.h" 
#include "material.h"

struct Particle
{
	Model* model; 
	Material* materialp;
	Transform transform;
	Shader shaders; 
	float lifeSpan; 
	int texID; 	
	
#if 0	
	Vector3 worldPos; 

	bool operator > (const Particle & p) const
	{
		return (p.worldPos.z > worldPos.z); 
	}
#endif
};

class ParticleEmitter
{
public: 
	ParticleEmitter();
   ~ParticleEmitter(); 
   
   std::vector<Particle> particles; 
   
   Transform transform;
   Model particleModel;
   Material particleMaterial;  
   Texture texture; 
   Shader particleShader; 
   
   void initParticles(std::string filename, int particleAmount); 
   void setShaders(Shader & s);
    
   int spawn(); 
   void queue(); 
   virtual void update(){};  
};
#if 0
#include <gui.h>

struct Particle
{
	Vector scale; 
	Vector location;
	Vector velocity;
	Vector acceleration;
	int lifespan;
	int texIndex; 
};

class ParticleSystem
{
public: 
	ParticleSystem(); 
	ParticleSystem(int count); 
   ~ParticleSystem(); 
   
   	void setParticlesAmount(int count);
 	void referenceModel(Model & m);
 	void referenceTexture(Texture & t);
	std::vector<Particle> particles; 
	//std::vector<Texture> texture;
	Texture* texture;
	Model* model;
};
#endif 

#endif/*__LE_PARTICLE_H__*/
