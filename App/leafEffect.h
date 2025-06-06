#ifndef __LEAF_EFFECT_H__
#define __LEAF_EFFECT_H__

#include <LazyEngine.h>

class LeafEffect : public ParticleEmitter
{
public: 
	LeafEffect(); 
   ~LeafEffect(); 
   
	void setCamera(Camera & c);
   
	void update(); 
	void queueEffect();
   
private:
	std::vector<Vector3> velocity;
	std::vector<Vector3> acceleration;

	Texture leafTex[8];
	
  	Camera* camp;  
};

#endif/*__LEAF_EFFECT_H*/
