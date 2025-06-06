#include "bSphere.h"

#include <cstdio>
#include <cmath>
#include "colcommon.h"
#include "mathcommon.h" 

//#define PUSHDATATEST 1
#if PUSHDATATEST
/*possible solution is to use a struct for data*/
struct PushData
{
   Vector output; //call touched normals
   float distance; //all of the distances added
   int average; 
};

#endif 

bool TestSphereTriangle(Sphere s, Vector & a, Vector & b, Vector & c, Vector & p)
{
	p = ClosestPtPointTriangle(s.center, a, b ,c); 
	
	Vector v = p - s.center;
	return Vector::Dot(v, v) <= s.radius * s.radius; 
}

void Sphere::updatePosition(Vector position)
{
	center = position + offset;
}

int Sphere::overlapSphere(const Sphere & b)
{
	Vector d = center - b.center; 
	float dis2 = Vector::Dot(d, d); 
	
	float rad = radius + b.radius; 
	return dis2 <= rad * rad; 
}
 
Vector Sphere::pushBack(const Sphere & b)
{
	Vector dir = center - b.center; 
	dir.normalize(); 
	
	float dis = Vector::Distance(center, b.center); 
	dis = dis - radius; 
	dis = b.radius - dis; 
	 
	return (dis*dir); 
}

bool Sphere::SphereOnMesh(Model & model)
{
	return Sphere::SphereOnMesh(model, 45, Vector::Up()); //maybe 30
}

bool Sphere::SphereOnMesh(Model & model, float degree, Vector angle)
{
	Vector a, b, c; 
	Vector point, n, out; 
	Vector nd;

#if PUSHDATATEST	
	PushData pd={0}; 
printf("avg = %f\n", pd.distance); 
#endif
	//Vector avg;  
	//int avgDir = 0; 
	//static int m =0, i;
	bool touched = false;
	float radian = cosf(DEG2RAD(degree));


	for(int i = 0; i < model.face_count; ++i)
	{		
#if 0				    		
		 a = Vector(model.verts[model.faces[0][i].vx].x,
				    model.verts[model.faces[0][i].vx].y,
				    model.verts[model.faces[0][i].vx].z);

		 b = Vector(model.verts[model.faces[0][i].vy].x,
				    model.verts[model.faces[0][i].vy].y,
				    model.verts[model.faces[0][i].vy].z);
	   
		 c = Vector(model.verts[model.faces[0][i].vz].x,
				    model.verts[model.faces[0][i].vz].y,
				    model.verts[model.faces[0][i].vz].z);
#else
		 a.x = model.verts[model.faces[i].vx].x;
		 a.y = model.verts[model.faces[i].vx].y;
		 a.z = model.verts[model.faces[i].vx].z;

		 b.x = model.verts[model.faces[i].vy].x;
		 b.y = model.verts[model.faces[i].vy].y;
		 b.z = model.verts[model.faces[i].vy].z;
	   
		 c.x = model.verts[model.faces[i].vz].x;
		 c.y = model.verts[model.faces[i].vz].y;
		 c.z = model.verts[model.faces[i].vz].z;
		 
		 //avg = (a + b + c) / 3; 
//printf();		 
		 //if (Vector::SqrDistance(avg, center) > 3000)
		 //{
		 	//printf("distance %f\n", Vector::SqrDistance(avg, center));  
		 	//continue; 
		 //}
#endif 				    
		if (TestSphereTriangle(*this, a, b, c, point))
		{
		 	n = Vector(model.norms[model.faces[i].nx].x,
				       model.norms[model.faces[i].nx].y,
				       model.norms[model.faces[i].nx].z);

			if(Vector::Dot(angle, n) >= radian)
			{
				//if (avgDir++)
				nd = angle * (radius - Vector::Distance(center, point));
#if PUSHDATATEST				
				pd.output += angle; 
				pd.distance += (Vector::Distance(center, point));
				pd.average++; 
#endif 	 
			}else
			{
				nd = n * (radius - Vector::Distance(center, point));
#if PUSHDATATEST			
				pd.output += n; 
				pd.distance += (Vector::Distance(center, point));
				pd.average++; 
#endif			
			}
			out += nd; 

			touched = true; 
		} 
	}
	
	if (touched)
	{
		//p = out;//.normalized();
		pointOnMesh = out; 
#if PUSHDATATEST		
		printf("out = %f\n", pd.output.magnitude());
		pd.output.normalize();
		pd.distance /= pd.average; 
		pointOnMesh = pd.output * (radius - pd.distance); 
		printf("pointOnMesh = %f\n", pointOnMesh.magnitude()); 
#endif		
	}
	
	return touched; 
}
