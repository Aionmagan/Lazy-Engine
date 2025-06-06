#ifndef __TEST_PARTICLE_H__
#define __TEST_PARTICLE_H__

#include <LazyEngine.h>

struct anim
{
	int texIndex; 
	int animTimer;
};

class TestEffect : public ParticleEmitter
{
public: 
	TestEffect(int es);
   ~TestEffect(); 
   
   Shader shaders;
   
   Model emitterMod; 
   Texture emitterTex;
   GameObject emitter; 
   
   void update(); 
   void queueEffect();
  
  	int effectSelection;
  	int spawnTimer; 
private:
	std::vector<Vector3> velocity;
	std::vector<Vector3> acceleration;
	//std::vector<Texture> fireTex;
	Texture fireTex[241];
	Texture smokeTex[241];
	std::vector<anim> animation; 
	Light lit; 
};

#endif/*__TEST_PARTICLE_H__*/
