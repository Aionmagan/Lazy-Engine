#ifndef __MATHF_H__
#define __MATHF_H__

#include "macro.h"
NAMESPACE_BEGIN(Mathf)
//should change from static struct to namespace maybe
//dislike the function overhead but meh
//struct Mathf
//{
	constexpr float PI     = 3.1415926535897932384626433832795f; 
	constexpr float TWOPI  = 6.283185307179586476925286766559f;
	constexpr float HALFPI = 1.5707963267948966192313216916398f;
	
	float Clamp      (float v, float min, float max); //need int form
	float Clamp01    (float v); 
	float Rad2Deg    (float a); 
	float Deg2Rad    (float a);
	float Lerp       (float a, float b, float d); 
	float Sqrt       (float a);
	float Abs        (float a); 
	int   Abs        (int   a);
	float Atan       (float a); 
	float Atan2      (float a, float b); 
	float Asin       (float a); 
	float Acos       (float a); 
	float Sin        (float a); 
	float Cos        (float a); 
	float Max        (float a, float b);
	float Min        (float a, float b);  
	float MoveTowards(float a, float b, float d);
	float RandomRangef(float a, float b); 
	int   RandomRangei(int a, int b);   
//};
NAMESPACE_END(Mathf)
#endif/*__MATHF_H__*/
