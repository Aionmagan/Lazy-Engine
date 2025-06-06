#include "rayCast.h"
#include <cmath>

#include "mathcommon.h"
#include "colcommon.h"

bool TestRayTriangle(Vector origin, Vector dir, Vector a, Vector b, Vector c, Vector & p)
{
	Vector edge1 = b - a; 
	Vector edge2 = c - a; 
	Vector edge2Cross = Vector::Cross(dir, edge2);
	float det = Vector::Dot(edge1, edge2Cross);
	
	if (det > -EPI && det < EPI)
		return false;
		
	float invDet = 1.0f / det;   
	Vector s = origin - a; 
	float u = invDet * Vector::Dot(s, edge2Cross);
	
	if (u < 0 || u > 1) 
		return false;
		
	Vector edge1Cross = Vector::Cross(s, edge1); 
	float v = invDet * Vector::Dot(dir, edge1Cross); 
	
	if (v < 0 || u + v > 1)
		return false; 
		
	float t = invDet * Vector::Dot(edge2, edge1Cross);
	
	if (t > EPI)
	{
		p = origin + dir * t; 
		return true;
	} 
	
	return false;
}


Ray::Ray()
{

}
 
Ray::~Ray()
{

}

bool Ray::castToAABB(Vector origin, Vector direction, AABB a, float & tmin, Vector & q)
{
	tmin = 0.0f; 
	float tmax = FLT_MAX; 
	
	//for (int i = 0; i < 3; ++i)
	{
		if (fabsf(direction.x) < EPS_RAY)
		{
			if(origin.x < a.min.x || origin.x > a.max.x) return false; 
		}else 
		{
			float ood = 1.0f / direction.x; 
			float t1 = (a.min.x - origin.x) * ood; 
			float t2 = (a.max.x - origin.x) * ood; 
			
			if (t1 > t2)
			{
				float tmp = t1; 
				t1 = t2; 
				t2 = tmp; 
			}
			
			if (t1 > tmin) tmin = t1; 
			if (t2 > tmax) tmax = t2; 
			
			if (tmin > tmax) return false; 
		}
		
		if (fabsf(direction.y) < EPS_RAY)
		{
			if(origin.y < a.min.y || origin.y > a.max.y) return false; 
		}else 
		{
			float ood = 1.0f / direction.y; 
			float t1 = (a.min.y - origin.y) * ood; 
			float t2 = (a.max.y - origin.y) * ood; 
			
			if (t1 > t2)
			{
				float tmp = t1; 
				t1 = t2; 
				t2 = tmp; 
			}
			
			if (t1 > tmin) tmin = t1; 
			if (t2 > tmax) tmax = t2; 
			
			if (tmin > tmax) return false; 
		}
		
		if (fabsf(direction.z) < EPS_RAY)
		{
			if(origin.z < a.min.z || origin.z > a.max.z) return false; 
		}else 
		{
			float ood = 1.0f / direction.z; 
			float t1 = (a.min.z - origin.z) * ood; 
			float t2 = (a.max.z - origin.z) * ood; 
			
			if (t1 > t2)
			{
				float tmp = t1; 
				t1 = t2; 
				t2 = tmp; 
			}
			
			if (t1 > tmin) tmin = t1; 
			if (t2 > tmax) tmax = t2; 
			
			if (tmin > tmax) return false; 
		}
	}
	
	q = origin+direction*tmin; 
	return true; 
}

bool Ray::castToSphere(Vector origin, Vector direction, float distance, Sphere & sphere, Vector & q, bool ignoreInside)
{
	//float dist = distance * distance; 
	//float orToSp = sphere.center.sqrMagnitude();  
	
	q = sphere.center + (Vector::Up() * sphere.radius); 


	Vector m = origin - sphere.center; 
	//Vector n = m; 
	//n.normalized();
	float b = Vector::Dot(m, direction.normalized());
	float c = Vector::Dot(m, m) - sphere.radius*sphere.radius;  
	
	if (c > 0.0f && b > 0.0f) return false; 
	
	float discr = b*b - c; 
	
	if (discr < 0.0f) return false; 
	
	float t = -b - sqrt(discr); 
	
	if (t < 0.0f)
	{
		t = 0.0f; 

		if (!ignoreInside)
		{
			 t = -b + sqrt(discr); 
		}
	}
	
	q = origin + t * direction.normalized(); 
	
	//printf("q (%f, %f, %f) | t %f\n", q.x, q.y, q.z, t); 
	
	return true; 
	
/*	
	float radius = sphere.radius; 
	Vector o = origin; 
	Vector cv = sphere.transform.position;
	Vector oc = o - cv;
	float b = Vector::Dot(oc, direction); 
	float c = Vector::Dot(oc, oc)-(radius * radius); 
	float bbc = (b*b)-c; 
	float t2 = -b + sqrt(bbc);
	float t1 = -b - sqrt(bbc);
	
	return (((t1*t1) + (2*t1*b) + c)==0); 
*/
}

bool Ray::castOnMesh(Vector origin, Vector dir, Model & model)
{
	Vector a, b, c; 
	Vector point, n;
	float distance = 0;  
	//static int m =0, i;
	bool touched = false;


	for(int i = 0; i < model.face_count; ++i)
	{		
				    		
		 a = Vector(model.verts[model.faces[i].vx].x,
				    model.verts[model.faces[i].vx].y,
				    model.verts[model.faces[i].vx].z);

				
		 b = Vector(model.verts[model.faces[i].vy].x,
				    model.verts[model.faces[i].vy].y,
				    model.verts[model.faces[i].vy].z);
				   
		 c = Vector(model.verts[model.faces[i].vz].x,
				    model.verts[model.faces[i].vz].y,
				    model.verts[model.faces[i].vz].z);
				    
		//if (TestSphereTriangle(s, a, b, c, point))
		if (TestRayTriangle(origin, dir, a, b, c, point))
		{
		 	n = Vector(model.norms[model.faces[i].nx].x,
				       model.norms[model.faces[i].nx].y,
				       model.norms[model.faces[i].nx].z);
				       
			float d = Vector::SqrDistance(point, origin); 
			
			if (distance == 0 || distance > d)
			{
				//dis = Vector::Distance(point, origin); 
				distance = d; 
				//p = point; 
				this->point = point;
				this->normal = n; 
			}

			touched = true; 
		} 
	}
	
	if (touched)
	{
		this->distance = sqrt(distance); 
	}	
	
	return touched; 
}
