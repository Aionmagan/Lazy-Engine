#include "mathf.h" 

#include <cmath>
#include <cstdlib>

float Mathf::Clamp(float v, float min, float max)
{
	if (v > max) return max; 
	if (v < min) return min; 
	return v; 
}

float Mathf::Clamp01(float v)
{
	if (v > 1.0f) return 1.0f; 
	if (v < 0.0f) return 0.0f; 
	return v; 
}

float Mathf::Rad2Deg(float a)
{
	return (a * 180.0f / Mathf::PI);
}

float Mathf::Deg2Rad(float a)
{
	return (a * Mathf::PI / 180.0f);
}

float Mathf::Lerp(float a, float b, float d)
{
	return (a + d * (b - a)); 
}

float Mathf::Sqrt(float a)
{
	return sqrt(a); 
}

float Mathf::Abs(float a)
{
	if (a>=0.0f) return a;
	return -a;  
}

int Mathf::Abs(int a)
{
	if (a>=0) return a; 
	return -a;
}

float Mathf::Atan(float a)
{
	return atan(a); 
}

float Mathf::Atan2(float a, float b)
{
	return atan2(a, b);
}

float Mathf::Asin (float a)
{
	return asinf(a); 
}

float Mathf::Acos (float a)
{
	return acosf(a); 
}

float Mathf::Sin(float a)
{
	return sinf(a); 
}

float Mathf::Cos(float a)
{
	return cosf(a); 
}

float Mathf::Max(float a, float b)
{
	return (((a)>(b))?(a):(b));
}

float Mathf::Min(float a, float b)
{
	return (((a)<(b))?(a):(b));
}

float Mathf::MoveTowards(float a, float b, float d)
{
	return (a + (b-a) * d); 
}

float Mathf::RandomRangef(float a, float b)
{
	return a + (float)rand() / RAND_MAX * (b - a);
}

int Mathf::RandomRangei(int a, int b)
{
	return a + rand() % (b - a);
}	
