#ifndef __RAYCAST_H__
#define __RAYCAST_H__

#include "vector.h"
#include "bSphere.h"
#include "aabb.h"
#include <float.h> 

//#define FLT_MAX 10.0
#define EPS_RAY 0.2f
//#include "sphereCollision.h"
#if 0
struct Sphere
{
	Vector center; 
	float radius; 	
};
#endif 

class Ray
{
public: 
	Vector point; 
	Vector normal; 
	float distance; 
	
	Ray(); 
   ~Ray(); 
   bool castToAABB(Vector origin, Vector direction, AABB a, float & tmin, Vector & q); 
   bool castToSphere(Vector origin, Vector direction, float distance, Sphere & sphere, Vector & q, bool ignoreInside); 
   bool castOnMesh(Vector origin, Vector dir, Model & model);
   bool LineCast(); 
};

#endif/*__RAYCAST_H__*/
