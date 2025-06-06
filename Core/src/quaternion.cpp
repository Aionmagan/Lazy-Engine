    #include "quaternion.h"

#include <cstdio>
#include <cmath>
#include "mathf.h"
/*
 *===================================================
 *Member functions 
 *===================================================
 */
 
Quaternion::Quaternion(float x, float y, float z, float w)
{
    this->x = x; 
    this->y = y; 
    this->z = z; 
    this->w = w; 
}

Quaternion::Quaternion()
{
    x = 0.0f; 
    y = 0.0f; 
    z = 0.0f; 
    w = 1.0f; 
}

Quaternion::~Quaternion()
{
    
}
   
float Quaternion::magnitude()
{
    return sqrt((w*w)+(x*x)+(y*y)+(z*z));
}

void Quaternion::conjugate()
{
    x = -x; 
    y = -y; 
    z = -z; 
}   

/*float Quaternion::sqrMagnitude()
{
    return ((w*w)+(x*x)+(y*y)+(z*z));
}*/

bool Quaternion::operator == (const Quaternion & q)
{
    
}

/*Quaternion & Quaternion::operator -= (const Quaternion & q)
{
    return Quaternion(x-q.x, y-q.y, z-q.z, w-q.w); 
}

Quaternion & Quaternion::operator += (const Quaternion & q)
{
    return Quaternion(x+q.x, y+q.y, z+q.z, w+q.w); 
}*/

Quaternion & Quaternion::operator *= (const Quaternion & q)
{
    float ww = w*q.w - x*q.x - y*q.y - z*q.z; 
    float xx = w*q.x + x*q.w + y*q.z - z*q.y; 
    float yy = w*q.y + y*q.w + z*q.x - x*q.z;
    float zz = w*q.z + z*q.w + x*q.y - y*q.x; 
    
    w = ww; 
    x = xx; 
    y = yy; 
    z = zz; 
    
    return *this;
}

Quaternion Quaternion::Identity()
{
	Quaternion q; //contructor creats an identity quaternion
	return q; 
}

/*
 *===============================================
 *Static functions 
 *===============================================
 */
 
float Quaternion::Dot(const Quaternion & q1, const Quaternion & q2)
{
    return ((q1.w*q2.w)+(q1.x*q2.x)+(q1.y*q2.y)+(q1.z*q2.z));
}   

Quaternion Quaternion::Conjugate(const Quaternion & q)
{
    return Quaternion(-q.x, -q.y, -q.z, q.w);
}

Quaternion Quaternion::AxisAngle(float x, float y, float z, float angle)
{
	float half = (angle*0.5f) * (3.14159/180.0f); 
	float s = sinf(half); 
	
	return Quaternion(x*s, y*s, z*s, cosf(half)); 
}

Quaternion Quaternion::Euler(float x, float y, float z)
{
	Quaternion qx, qy, qz; 
	qx = Quaternion::AxisAngle(1.0f, 0.0f, 0.0f, x); 
	qy = Quaternion::AxisAngle(0.0f, 1.0f, 0.0f, y); 
	qz = Quaternion::AxisAngle(0.0f, 0.0f, 1.0f, z); 
	return (qz*qy*qx); 	

#if 0
    float halfx = (x*(3.14/180.0f)) * 0.5f; 
    float halfy = (y*(3.14/180.0f)) * 0.5f;  
    float halfz = (z*(3.14/180.0f)) * 0.5f; 
    
    float cx = cosf(halfx);
    float sx = sinf(halfx);
    float cy = cosf(halfy); 
    float sy = sinf(halfy); 
    float cz = cosf(halfz); 
    float sz = sinf(halfz); 
    
    Quaternion q; 
    
/*
def euler_to_quaternion(yaw, pitch, roll):

        qx = np.sin(roll/2) * np.cos(pitch/2) * np.cos(yaw/2) - np.cos(roll/2) * np.sin(pitch/2) * np.sin(yaw/2)
        qy = np.cos(roll/2) * np.sin(pitch/2) * np.cos(yaw/2) + np.sin(roll/2) * np.cos(pitch/2) * np.sin(yaw/2)
        qz = np.cos(roll/2) * np.cos(pitch/2) * np.sin(yaw/2) - np.sin(roll/2) * np.sin(pitch/2) * np.cos(yaw/2)
        qw = np.cos(roll/2) * np.cos(pitch/2) * np.cos(yaw/2) + np.sin(roll/2) * np.sin(pitch/2) * np.sin(yaw/2)

        return [qx, qy, qz, qw]
*/

    //q.x = sx*cy*cz - cx*sy*sz;
    //q.y = cx*sy*cz + sx*cy*sz; 
    //q.z = cx*cy*sz - sx*sy*cz; 
    //q.w = cx*cy*cz + sx*sy*sz;

//XYZ
    //q.w = cx*cy*cz - sx*sy*sz;
    //q.x = sy*cx*cz - sx*sz*cy; 
    //q.y = sx*sy*cz + sz*cx*cy; 
    //q.z = sx*cy*cz + sy*sz*cx;
//ZYX    
    q.w = sx*sy*sz + cx*cy*cz;
    q.x = sz*cx*cy + sx*sy*cz; 
    q.y = sx*sz*cy - sy*cx*cz; 
    q.z = sx*cy*cz - sy*sz*cx;
//YXZ
    //q.w = sx*sy*sz + cx*cy*cz;
    //q.x = sx*sz*cy + sy*cx*cz; 
    //q.y = sx*cy*cz - sy*sz*cx; 
    //q.z = sz*cx*cy - sx*sy*cz;
//YZX
    //q.w = cx*cy*cz - sx*sy*sz;
    //q.x = sx*sy*cz + sz*cx*cy; 
    //q.y = sx*cy*cz + sy*sz*cx; 
    //q.z = sy*cx*cz - sx*sz*cy;
//XZY
    //q.w = sx*sy*sz + cx*cy*cz;
    //q.x = sx*cy*cz - sy*sz*cx; 
    //q.y = sz*cx*cy - sx*sy*cz; 
    //q.z = sx*sz*cy + sy*cx*cz;
    
    //q.w = cz * cx * cy + sz * sx * sy;
    //q.x = cz * sx * cy - sz * cx * sy;
    //q.y = cz * cx * sy + sz * sx * cy;
    //q.z = sz * cx * cy - cz * sx * sy;
    
    //q.w = cz * cy * cx + sx * sy * sz;
    //q.x = sz * cy * cx - cx * sy * sz;
    //q.y = cz * sy * cx + sx * cy * sz;
    //q.z = cz * cy * sx - sx * sy * cz;
    
    return q;  
#endif                
}

Quaternion Quaternion::Normalize(Quaternion & q)
{
	float l = q.magnitude(); 
	return Quaternion(q.x/l, q.y/l, q.z/l, q.w); 
}

Quaternion Quaternion::Slerp(const Quaternion & q1, const Quaternion & q2, float l)
{
	float cosHalf = q1.w * q2.w + q1.x * q2.x + q1.y * q2.y + q1.z * q2.z; 
	
	if (Mathf::Abs(cosHalf) >= 1.0f)
		return q1; 
	 	
	float half = Mathf::Acos(cosHalf); 
	float sinHalf = Mathf::Sqrt(1.0f - cosHalf*cosHalf);
	
	if (Mathf::Abs(sinHalf) < 0.001f)
	{
		return Quaternion(q1.x * 0.5f + q2.x * 0.5f,
						  q1.y * 0.5f + q2.y * 0.5f,
						  q1.z * 0.5f + q2.z * 0.5f,
						  q1.w * 0.5f + q2.w * 0.5f);
	} 
	
	float ratioA = Mathf::Sin((1.0f - l) * half) / sinHalf; 
	float ratioB = Mathf::Sin(l * half) / sinHalf; 
	
	return Quaternion(q1.x * ratioA + q2.x * ratioB,
					  q1.y * ratioA + q2.y * ratioB,
					  q1.z * ratioA + q2.z * ratioB,
					  q1.w * ratioA + q2.w * ratioB);
}

Quaternion Quaternion::LookRotation(const Vector & forward, const Vector & up)
{
    Vector tforward = forward;
    Vector tup = up;  
    Vector::OrthoNormalize(tforward, tup);
    Vector right = Vector::Cross(tup, tforward);  
    
    Quaternion ret; 
    ret.w = sqrt(1.0f + right.x + tup.y + tforward.z) * 0.5f;
    float w4_recip = 1.0f / (4.0f * ret.w); 
    ret.x = (tup.z - tforward.y) * w4_recip; 
    ret.y = (tforward.x - right.z) * w4_recip; 
    ret.z = (right.y - tup.x) * w4_recip; 
    //ret.x = (lookAt.y - rup.z) * w4_recip; 
    //ret.y = (right.z - lookAt.x) * w4_recip; 
    //ret.z = (rup.x - right.y) * w4_recip; 
    
    return ret; 
}

Quaternion Quaternion::FromToRotation(const Vector & fromDirection, const Vector & toDirection)
{
#if 1

	 Vector from_norm = fromDirection.normalized();
	 Vector to_norm = toDirection.normalized();
	 float cos_angle = Vector::Dot(from_norm, to_norm);
    //Vector from_norm = normalize(from);
    //Vector to_norm = normalize(to);

    //float cos_angle = Vector::Dot(from_norm, to_norm);
    
    // Handle the case where vectors are parallel or anti-parallel
    if (cos_angle > 0.9999f) { // Almost parallel
        return {0.0f, 0.0f, 0.0f, 1.0f}; // Identity quaternion
    }
    if (cos_angle < -0.9999f) { // Almost anti-parallel
       // Choose an arbitrary axis perpendicular to from_norm
        Vector arbitrary_axis;
        if (Mathf::Abs(from_norm.x) < 0.1) {
            arbitrary_axis = {1.0f, 0.0f, 0.0f};
        } else {
            arbitrary_axis = {0.0f, 1.0f, 0.0f};
        }
        Vector rotation_axis = Vector::Normalize(Vector::Cross(from_norm, arbitrary_axis));
        return Quaternion(rotation_axis.x, rotation_axis.y, rotation_axis.z, 0.0f); // 180-degree rotation
    }

    Vector3 rotation_axis = Vector::Normalize(Vector::Cross(from_norm, to_norm));
    float angle = Mathf::Acos(cos_angle) * 0.5f;

    float sin_half_angle = Mathf::Sin(angle);
    float cos_half_angle = Mathf::Cos(angle);

    return Quaternion(rotation_axis.x * sin_half_angle,
				 	  rotation_axis.y * sin_half_angle,
					  rotation_axis.z * sin_half_angle,
					  cos_half_angle);
#else
		const Vector unitFrom = fromDirection.normalized();
		const Vector unitTo = toDirection.normalized();
		const float d = Vector::Dot(unitFrom, unitTo);

		if (d >= 1.0f)
		{
			// In the case where the two vectors are pointing in the same
			// direction, we simply return the identity rotation.
			return Quaternion::Identity();
		}
		else if (d <= -1.0f)
		{
			// If the two vectors are pointing in opposite directions then we
			// need to supply a quaternion corresponding to a rotation of
			// PI-radians about an axis orthogonal to the fromDirection.
			Vector axis = Vector::Cross(unitFrom, Vector::Right());
			if (axis.sqrMagnitude() < 1e-6)
			{
				// Bad luck. The x-axis and fromDirection are linearly
				// dependent (colinear). We'll take the axis as the vector
				// orthogonal to both the y-axis and fromDirection instead.
				// The y-axis and fromDirection will clearly not be linearly
				// dependent.
				axis = Vector::Cross(unitFrom, Vector::Up());
			}

			// Note that we need to normalize the axis as the cross product of
			// two unit vectors is not nececessarily a unit vector.
			axis.normalize(); 
			return Quaternion::AxisAngle(axis.x, axis.y, axis.z, Mathf::PI); 
			//return angleAxis(M_PI, axis.normalized());
		}
		else
		{
			// Scalar component.
			const float s = Mathf::Sqrt(unitFrom.sqrMagnitude() * unitTo.sqrMagnitude())
				+ Vector::Dot(unitFrom, unitTo);

			// Vector component.
			const Vector v = Vector::Cross(unitFrom, unitTo);
			Quaternion q(v.x, v.y, v.z, s);
			// Return the normalized quaternion rotation.
			return Quaternion::Normalize(q); 
			//return Quaternion(s, v).normalized();
		}
#endif
}

Quaternion Quaternion::Euler(const Vector & v)
{
    return Euler(v.x, v.y, v.z); 
}

/*Quaternion & Quaternion::operator /= (const Quaternion & q)
{

}
*/

/*
 *===============================================
 *Global functions / operators
 *===============================================
 */
Quaternion operator - (const Quaternion & q)
{
    return Quaternion(-q.x, -q.y, -q.z, -q.w); 
}

/*Quaternion operator - (const Quaternion & q1, const Quaternion & q2)
{
    return Quaternion(q1.x - q2.x, q1.y - q2.y, q1.z - q2.z, ); 
}

Quaternion operator + (const Quaternion & q1, const Quaternion & q2)
{

}
*/
Quaternion operator * (const Quaternion & q1, const Quaternion & q2)
{
    float ww = q1.w*q2.w - q1.x*q2.x - q1.y*q2.y - q1.z*q2.z; 
    float xx = q1.w*q2.x + q1.x*q2.w + q1.y*q2.z - q1.z*q2.y; 
    float yy = q1.w*q2.y + q1.y*q2.w + q1.z*q2.x - q1.x*q2.z;
    //float yy = q1.w*q2.y - q1.x*q2.z + q1.y*q2.w + q1.z*q2.x;
    float zz = q1.w*q2.z + q1.z*q2.w + q1.x*q2.y - q1.y*q2.x; 
    //float zz = q1.w*q2.z + q1.x*q2.y - q1.y*q2.z + q1.z*q2.x; 
    
    return Quaternion(xx, yy, zz, ww); 
}
/*
Quaternion operator / (const Quaternion & q1, const Quaternion & q2)
{

}
*/

