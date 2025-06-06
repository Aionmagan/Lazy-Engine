#ifndef __LE_COL_COMMON_H__
#define __LE_COL_COMMON_H__

#include "vector.h"

static Vector ClosestPtPointTriangle(Vector & p, Vector & a, Vector & b, Vector & c)
{
#if 1
	Vector ab = b-a; 
	Vector ac = c-a; 
	Vector ap = p-a; 
	
	float d1 = Vector::Dot(ab, ap);
	float d2 = Vector::Dot(ac, ap); 	
	if (d1 <= 0.0f && d2 <= 0.0f) return a; 
	
	Vector bp = p - b; 
	float d3 = Vector::Dot(ab, bp); 
	float d4 = Vector::Dot(ac, bp); 	
	if (d3 >= 0.0f && d4 <= d3) return b; 
	
	float vc = d1*d4 - d3*d2; 
	if (vc <= 0.0f && d1 >= 0.0f && d3 <= 0.0f)
	{
		float v = d1 / (d1 - d3); 
		return a + v * ab; 
	}
	
	Vector cp = p - c; 
	float d5 = Vector::Dot(ab, cp); 
	float d6 = Vector::Dot(ac, cp); 	
	if (d6 >= 0.0f && d5 <= d6) return c; 
	
	float vb = d5*d2 - d1*d6;
	if (vb <= 0.0f && d2 >= 0.0f && d6 <= 0.0f)
	{
		float w = d2 / (d2 - d6);
		return a + w * ac; 
	}
	
	float va = d3*d6 - d5*d4;
	//float d4d3 = d4 - d3; 
	//float d5d6 = d5 - d6; 
	//if (va <= 0.0f && d4d3 >= 0.0f && d5d6 >= 0.0f)
	if (va <= 0.0f && (d4 - d3) >= 0.0f && (d5 - d6) >= 0.0f)
	{
		//float w = d4d3 / (d4d3 + d5d6); 
		float w = (d4 - d3) / ((d4 - d3) + (d5 - d6));
		return b + w * (c - b); 
	}
	
	float denom = 1.0f / (va + vb + vc); 
	float v = vb * denom; 
	float w = vc * denom; 
	
	return a + ab * v + ac * w; 
#else
	Vector ab = b-a; 
	Vector ac = c-a; 
	Vector bc = c-b; 
	
	float snom   = Vector::Dot(p-a, ab);
	float sdenom = Vector::Dot(p-b, a-b); 
	
	float tnom   = Vector::Dot(p - a, ac); 
	float tdenom = Vector::Dot(p - c, a - c);
	
	if (snom <= 0.0f && tnom <= 0.0f) return a; 
	
	float unom   = Vector::Dot(p - b, bc);
	float udenom = Vector::Dot(p - c, b - c); 
	
	if (sdenom <= 0.0f && unom <= 0.0f) return b; 
	if (tdenom <= 0.0f && udenom <= 0.0f) return c; 
	  
	Vector n = Vector::Cross(b - a, c - a); 
	
	float vc = Vector::Dot(n, Vector::Cross(a - p, b - p)); 
	if (vc <= 0.0f && snom >= 0.0f && sdenom >= 0.0f)
		return a + snom / (snom + sdenom) * ab; 
		
	float va = Vector::Dot(n, Vector::Cross(b - p, c - p)); 
	if (va <= 0.0f && unom >= 0.0f && udenom >= 0.0f)
		return b + unom / (unom + udenom) * bc; 
		
	float vb = Vector::Dot(n, Vector::Cross(c - p, a - p));
	if (vb <= 0.0f && tnom >= 0.0f && tdenom >= 0.0f)
		return a + tnom / (tnom + tdenom) * ac; 
		
	float u = va / (va + vb + vc); 
	float v = vb / (va + vb + vc);
	float w = 1.0f - u - v; // same as vc / (va + vb + vc);

	return u * a + v * b + w * c; 
#endif
}

#endif/*__LE_COL_COMMON_H__*/
