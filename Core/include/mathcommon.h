#ifndef __AE_MATHCOMMON_H__
#define __AE_MATHCOMMON_H__

#if 0
#include "../glm/glm.hpp"
#include "../glm/gtc/matrix_transform.hpp"
#include "../glm/gtc/type_ptr.hpp"
#include "../glm/gtc/quaternion.hpp" 
#endif 

#define MAX_LIGHT_SIZE 128

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

#define DEG2RAD(x) (x*(3.14159/180.0))
#define RAD2DEG(x) (x*(180.0/3.14159)) 

#define EPI 0.1
#if 1
static float Lerpf(float f1, float f2, float l)
{
	return (f1 + l * (f2 - f1)); 
} 

static float MoveTowardsf(float f1, float f2, float d)
{
	return (f1 + (f2-f1) * d);  
}
#endif
#endif/*__MATHCOMMON_H__*/
