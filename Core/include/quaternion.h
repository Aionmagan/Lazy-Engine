#ifndef __QUATERNION_H__
#define __QUATERNION_H__

#include "vector.h"
struct Vector; 

struct Quaternion
{
	float x, y, z, w; 
	
	Quaternion(float x, float y, float z, float w);
	Quaternion();
   ~Quaternion(); 
   
   float magnitude(); 
   void conjugate(); 
   
   bool         operator == (const Quaternion & q);  
   Quaternion & operator *= (const Quaternion & q);

   
   static Quaternion Identity();
/*
*===============================================
*Static functions
*===============================================
*/
   static float Dot(const Quaternion & q1, const Quaternion & q2); 
   static Quaternion Conjugate(const Quaternion & q); 
   /*heading pitch roll | from Z to X in that order*/
   static Quaternion AxisAngle(float x, float y, float z, float angle); 
   static Quaternion Euler(float x, float y, float z); 
   static Quaternion Euler(const Vector & v);
   static Quaternion Normalize(Quaternion & q); 
   static Quaternion Slerp(const Quaternion & q1, const Quaternion & q2, float l); 
   static Quaternion LookRotation(const Vector & forward, const Vector & up); 
   static Quaternion FromToRotation(const Vector & fromDirection, const Vector & toDirection);
};




/*
 *===============================================
 *Global functions / operators
 *===============================================
 */
Quaternion operator - (const Quaternion & q);
Quaternion operator * (const Quaternion & q1, const Quaternion & q2);

#endif/*__QUATERNION_H__*/
