#ifndef __LE_BSPHERE_H__
#define __LE_BSPHERE_H__

#include "vector.h"
#include "mesh.h" 

struct Sphere
{
	Vector offset; 
	Vector center; 
	Vector pointOnMesh; 
	float radius; 
	
	void   updatePosition(Vector position); 
	
	int    overlapSphere(const Sphere & b); 
	Vector pushBack(const Sphere & b); 
	
	bool SphereOnMesh(Model & model);
	bool SphereOnMesh(Model & model, float degree, Vector angle);
};

#endif/*__LE_BSPHERE_H__*/
