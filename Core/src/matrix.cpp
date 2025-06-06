#include "matrix.h"
#include <cstring>
#include <cmath>
#include <cstdio>

Matrix4::Matrix4(float m11, float m12, float m13, float m14,
               float m21, float m22, float m23, float m24,
               float m31, float m32, float m33, float m34,
               float m41, float m42, float m43, float m44)
{
    elem[0 ] = m11; elem[1 ] = m12; elem[2 ] = m13; elem[3 ] = m14; 
    elem[4 ] = m21; elem[5 ] = m22; elem[6 ] = m23; elem[7 ] = m24; 
    elem[8 ] = m31; elem[9 ] = m32; elem[10] = m33; elem[11] = m34;
    elem[12] = m41; elem[13] = m42; elem[14] = m43; elem[15] = m44; 
}               
        
Matrix4::Matrix4(const Matrix4 & m)
{
    (*this) = m; 
}
 
Matrix4::Matrix4()
{
    identity(); 
}
 
Matrix4::~Matrix4()
{

}

void Matrix4::identity()
{
    elem[0 ] = 1.0f; elem[1 ] = 0.0f; elem[2 ] = 0.0f; elem[3 ] = 0.0f; 
    elem[4 ] = 0.0f; elem[5 ] = 1.0f; elem[6 ] = 0.0f; elem[7 ] = 0.0f; 
    elem[8 ] = 0.0f; elem[9 ] = 0.0f; elem[10] = 1.0f; elem[11] = 0.0f;
    elem[12] = 0.0f; elem[13] = 0.0f; elem[14] = 0.0f; elem[15] = 1.0f;  
}

void Matrix4::translate(float x, float y, float z)
{
    identity(); 
    
    //row major need to change
    //elem[0][3] = x; 
    //elem[1][3] = y; 
    //elem[2][3] = z; 
	
    elem[12] = x; 
    elem[13] = y; 
    elem[14] = z;  
    
    //elem[3 ] = x; 
    //elem[7 ] = y; 
    //elem[11] = z; 
}

void Matrix4::scale(float x, float y, float z)
{
    identity(); 
    
    //elem[0][0] = x; 
    //elem[1][1] = y; 
    //elem[2][2] = z; 
    
    elem[0 ] = x; 
    elem[5 ] = y;
    elem[10] = z;  
}

/*all rotation uses radians*/
void Matrix4::rotate(float x, float y, float z)
{
    //doesn't work because it's overwritting all matrices
    //should multiply
    //rotateZ(z);
    //rotateY(y); 
    //rotateX(x); 
    
    float xc = cosf(x); 
    float xs = sinf(x); 
    float yc = cosf(y); 
    float ys = sinf(y); 
    float zc = cosf(z); 
    float zs = sinf(z); 
    
    
    //elem[0][0] = yc*zc; 
    //elem[1][1] = xc*zc - xs*ys*zs; 
    //elem[2][2] = xc*yc; 
    
    //elem[0][1] = -(yc*zs);
    //elem[0][2] =  ys; 
    //elem[1][0] =  zc*xs*ys + xc*zs; 
    //elem[1][2] = -(yc*xs); 
    //elem[2][0] = -(xc*zc*ys + xs*ys); 
    //elem[2][1] =  zc*xs + xc*ys*zs; 
    
    /*this is in XYZ order, need to change it later to ZYX
     *but i'm too tired now
     */
     

}
 
void Matrix4::rotateX(float radian)
{
    identity(); 
    
    float c = cosf(radian); 
    float s = sinf(radian); 
    
    //elem[1][1] =  c; 
    //elem[1][2] =  s;
    //elem[2][1] = -s;
    //elem[2][2] =  c; 
    elem[5 ] =  c; 
    elem[6 ] = -s; 
    elem[9 ] =  s; 
    elem[10] =  c; 
}

void Matrix4::rotateY(float radian)
{
    identity(); 
    
    float c = cosf(radian);
    float s = sinf(radian);
    
    //elem[0][0] =  c; 
    //elem[0][2] =  s;
    //elem[2][0] = -s;
    //elem[2][2] =  c; 
    
    elem[0 ] =  c; 
    elem[2 ] =  s; 
    elem[8 ] = -s; 
    elem[10] =  c; 
}

void Matrix4::rotateZ(float radian)
{
    identity(); 
    
    float c = cosf(radian);
    float s = sinf(radian);
    
    //elem[0][0] =  c; 
    //elem[0][1] =  s;
    //elem[1][0] = -s;
    //elem[1][1] =  c; 
    
    elem[0 ] =  c;
    elem[1 ] = -s; 
    elem[4 ] =  s;
    elem[5 ] =  c; 
}

/*================================
 *Vector parameters
 *===============================*/
void Matrix4::translate(Vector & v)
{
    identity(); 
    
    elem[12] = v.x; 
    elem[13] = v.y; 
    elem[14] = v.z; 
}

void Matrix4::scale(Vector & v)
{
    identity(); 
    
    elem[0 ] = v.x; 
    elem[5 ] = v.y;
    elem[10] = v.z;  
}

void Matrix4::rotate(Vector & v)
{
    rotate(v.x, v.y, v.z); 
}

void Matrix4::transpose()
{
    Matrix4 t(*this); 
    
    for(int i = 0; i < 4; ++i)
    {
        for(int j = 0; j < 4; ++j)
        {
            //elem[i][j] = t(j,i); 
            elem[i+j*4] = t.elem[j+i*4];
        }
    }
}

void Matrix4::lookAt(Vector & eye, Vector & forward, Vector & up)
{
#if 0
		glm::vec3 eye = camPos; 
		glm::vec3 forward = camPos+camDir;
		glm::vec3 upward = camUp; 
		
		glm::vec3 f = glm::normalize(eye - forward);
		glm::vec3 r = glm::normalize(glm::cross(upward, f)); 
		glm::vec3 u = glm::normalize(glm::cross(f, r)); 
		
		glm::vec3 t = glm::vec3(glm::dot(eye, r),
						   glm::dot(eye, u),
						   glm::dot(eye, f));
						   
		glm::mat4 v = glm::mat4(1.0f);
		
#if 0	//removed the need for transpose	
		v[0][0] = r.x; v[0][1] = r.y; v[0][2] = r.z; v[0][3] = -t.x;
		v[1][0] = u.x; v[1][1] = u.y; v[1][2] = u.z; v[1][3] = -t.y;
		v[2][0] = f.x; v[2][1] = f.y; v[2][2] = f.z; v[2][3] = -t.z;
		
		v = glm::transpose(v); 
#endif		
		v[0][0] = r.x; v[0][1] = u.x; v[0][2] = f.x; v[3][0] = -t.x;
		v[1][0] = r.y; v[1][1] = u.y; v[1][2] = f.y; v[3][1] = -t.y;
		v[2][0] = r.z; v[2][1] = u.z; v[2][2] = f.z; v[3][2] = -t.z;
#endif 		
	Vector f = Vector::Normalize(eye - forward); 
	Vector r = Vector::Normalize(Vector::Cross(up, f)); 
	Vector u = Vector::Normalize(Vector::Cross(f, r)); 
	
	Vector t = Vector(Vector::Dot(eye, r), 
	                  Vector::Dot(eye, u), 
	                  Vector::Dot(eye, f)); 
	
	identity();                
	
	elem[0] = r.x; elem[1] = u.x; elem[2 ] = f.x; elem[12] = -t.x; 
	elem[4] = r.y; elem[5] = u.y; elem[6 ] = f.y; elem[13] = -t.y; 
	elem[8] = r.z; elem[9] = u.z; elem[10] = f.z; elem[14] = -t.z; 
}

void Matrix4::orthoProj(float left, float right, float bottom, float top, float near, float far)
{
	if (left == right || top == bottom || near == far)
		printf("orthographic projection invalid\n"); 
		
	float rl = right - left; 
	float tb = top - bottom; 
	float fn = far - near; 
	
	elem[0] = 2.0f / rl; 
	elem[5] = 2.0f / tb; 
	elem[10] = -2.0f / fn; 
	elem[12] = -(right + left) / rl;
	elem[13] = -(top + bottom) / tb; 
	elem[14] = -(far + near) / fn; 
	elem[15] = 1.0f;
	
}

void Matrix4::perspectiveProj(float fov, float aspect, float near, float far)
{
#if 0

/*
 *---------------------------------------------------------------------------------------------------------------------
 *the artifacting is caused by the proj matrix, vu.clip is expecting it to be left handed
 *will implement left handed on the ps2 side and make the PC side convert left handed user code to right handed later 
 *---------------------------------------------------------------------------------------------------------------------
 */
	float w = tanf(fov*3.14159/360.0f);
	float h = w/aspect;
	float x = 0.0f;
	float y = 0.0f;

	elem[0] = 1.0f/w;
	elem[1] = 0.0f;
	elem[2] = 0.0f;
	elem[3] = 0.0f;

	elem[4] = 0.0f;
	elem[5] = 1.0f/h;
	elem[6] = 0.0f;
	elem[7] = 0.0f;

	elem[8] = x/w;
	elem[9] = y/h;
	elem[10] = (far+near)/(far-near);
	elem[11] = 1.0f;

	elem[12] = -elem[8];
	elem[13] = -elem[9];
	elem[14] = -2.0f*near*far/(far-near);
	elem[15] = 0.0f;
#else
    float hf = (fov*3.14f/180.0f)*0.5f; 
    //float w = 1.0f / (aspect * tan(hf));
    float h = 1.0f / tan(hf);
    float w = h / aspect; 
    float nmf = near - far; 
    float fnear = (near+far) / nmf; 
    float far2  = 2*near*far / nmf; 
    
    identity(); 
    
    elem[0 ] = w;
    elem[5 ] = h; 
    elem[10] = fnear; 
    elem[14] = far2; 
    elem[11] = -1.0f;
    elem[15] = 0.0f;   
    
    //Transpose(*this); //remove when colum-major is implemented everywhere else
#endif
}

void Matrix4::quaternionToMatrix(const Quaternion & q)
{
#if 1

#if 0
    float x2, y2, z2; 
    float xy, yz, xz; 
    float wz, wx, wy;
    
    x2 = 2.0f * (q.x*q.x);
    y2 = 2.0f * (q.y*q.y); 
    z2 = 2.0f * (q.z*q.z); 
    
    xy = 2.0f * q.x*q.y; 
    yz = 2.0f * q.y*q.z; 
    xz = 2.0f * q.x*q.z; 
    
    wx = 2.0f * q.w*q.x; 
    wy = 2.0f * q.w*q.y; 
    wz = 2.0f * q.w*q.z; 
    
    identity(); 
    
    elem[0 ] = 1.0f - y2 - z2;
    elem[5 ] = 1.0f - x2 - z2; 
    elem[10] = 1.0f - x2 - y2; 
    
    elem[1 ] = xy + wz;
    elem[2 ] = xz - wy;

    elem[4 ] = xy - wz;
    elem[6 ] = xz + wy;
    
    elem[8 ] = yz + wx;     
    elem[9 ] = yz - wx;  
    
    //transpose(); //keep this until all of the matrix class is colum-major
#else
/*
    float x2, y2, z2;
    float xx, xy, xz; 
    float yy, yz, zz;
    float wx, wy, wz;
    
    identity();
    
    x2 = q.x + q.x; 
    y2 = q.y + q.y; 
    z2 = q.z + q.z; 
    
    xx = q.x * x2;
    xy = q.x * y2; 
    xz = q.x * z2; 
    yy = q.y * y2; 
    yz = q.y * z2; 
    zz = q.z * z2; 
    wx = q.w * x2; 
    wy = q.w * y2; 
    wz = q.w * z2; 
    
    elem[0 ] = 1.0f - (yy + zz); 
    elem[5 ] = 1.0f - (xx + zz);
    elem[10] = 1.0f - (xx + yy); 
    
    elem[4 ] = xy - wz;
    elem[8 ] = xz + wy; 
    
    elem[1 ] = xy + wz;
    elem[9 ] = yz - wx;
    
    elem[2 ] = xz - wy;
    elem[6 ] = yz + wx;
*/

	float xx = q.x*q.x; 
	float yy = q.y*q.y; 
	float zz = q.z*q.z; 
	float yz = q.y*q.z; 
	float zx = q.z*q.x; 
	float xy = q.x*q.y; 
	float wx = q.w*q.x; 
	float wy = q.w*q.y; 
	float wz = q.w*q.z; 

	identity(); 
#if 0
	/*right*/ 
	elem[0 ] = 1.0f - 2.0f * (yy + zz); 
	elem[4 ] =        2.0f * (xy + wz); 
	elem[8 ] =        2.0f * (zx - wy); 
	
	elem[1 ] =        2.0f * (xy - wz); 
	elem[5 ] = 1.0f - 2.0f * (xx + zz); 
	elem[9 ] =        2.0f * (yz + wx); 
	
	elem[2 ] =        2.0f * (zx + wy); 
	elem[6 ] =        2.0f * (yz - wx);  
	elem[10] = 1.0f - 2.0f * (xx + yy); 
	
	transpose(); 
#endif	
	elem[0 ] = 1.0f - 2.0f * (yy + zz); 
	elem[1 ] =        2.0f * (xy + wz); 
	elem[2 ] =        2.0f * (zx - wy); 
	
	elem[4 ] =        2.0f * (xy - wz); 
	elem[5 ] = 1.0f - 2.0f * (xx + zz); 
	elem[6 ] =        2.0f * (yz + wx); 
	
	elem[8 ] =        2.0f * (zx + wy); 
	elem[9 ] =        2.0f * (yz - wx);  
	elem[10] = 1.0f - 2.0f * (xx + yy); 
	
#endif

#else

    float x2  = q.x + q.x;
    float y2  = q.y + q.y;
    float z2  = q.z + q.z;
    float xx2 = q.x * x2;
    float xy2 = q.x * y2;
    float xz2 = q.x * z2;
    float yy2 = q.y * y2;
    float yz2 = q.y * z2;
    float zz2 = q.z * z2;
    float sx2 = q.w * x2;
    float sy2 = q.w * y2;
    float sz2 = q.w * z2;
    
    identity(); 
    //transpose(); 
    elem[0 ] = 1 - (yy2 + zz2); 
    elem[5 ] = 1 - (xx2 + zz2); 
    elem[10] = 1 - (xx2 + yy2); 
    
    elem[1] = xy2 + sz2;
    elem[2] = xz2 - sy2; 
    
    elem[4] = xy2 - sz2; 
    elem[6] = yz2 + sx2; 
    
    elem[8] = xz2 + sy2; 
    elem[9] = yz2 - sx2; 
    
    //transpose(); 
#endif     
}
    
    
/*=================================
 *static functions and operators 
 *================================*/

Matrix4 & Matrix4::operator = (const Matrix4 & m)
{
    //elem[0][0] = m(0,0); elem[0][1] = m(0,1); elem[0][2] = m(0,2); elem[0][3] = m(0,3);
    //elem[1][0] = m(1,0); elem[1][1] = m(1,1); elem[1][2] = m(1,2); elem[1][3] = m(1,3);
    //elem[2][0] = m(2,0); elem[2][1] = m(2,1); elem[2][2] = m(2,2); elem[2][3] = m(2,3);
    //elem[3][0] = m(3,0); elem[3][1] = m(3,1); elem[3][2] = m(3,2); elem[3][3] = m(3,3);
     
    elem[0 ] = m.elem[0 ]; elem[1 ] = m.elem[1 ]; elem[2 ] = m.elem[2 ]; elem[3 ] = m.elem[3 ]; 
    elem[4 ] = m.elem[4 ]; elem[5 ] = m.elem[5 ]; elem[6 ] = m.elem[6 ]; elem[7 ] = m.elem[7 ]; 
    elem[8 ] = m.elem[8 ]; elem[9 ] = m.elem[9 ]; elem[10] = m.elem[10]; elem[11] = m.elem[11]; 
    elem[12] = m.elem[12]; elem[13] = m.elem[13]; elem[14] = m.elem[14]; elem[15] = m.elem[15]; 
    return *this; 
}

float & Matrix4::operator() (unsigned int r, unsigned int c)
{
    //return elem[r+c*4];
    return elem[c+r*4]; 
}

float Matrix4::operator() (unsigned int r, unsigned int c)const
{
    //return elem[r+c*4];
    return elem[c+r*4];
}  


/*=================================
 * Global operators
 *================================*/
Matrix4 operator - (const Matrix4 & m)
{
/*  compiler didn't like this for libs
    return Matrix(-m(0,0), -m(0,1), -m(0,2), -m(0,3),
                  -m(1,0), -m(1,1), -m(1,2), -m(1,3),
                  -m(2,0), -m(2,1), -m(2,2), -m(2,3),
                  -m(3,0), -m(3,1), -m(3,2), -m(3,3)); 
*/
    Matrix4 mtx(-m(0,0), -m(0,1), -m(0,2), -m(0,3),
               -m(1,0), -m(1,1), -m(1,2), -m(1,3),
               -m(2,0), -m(2,1), -m(2,2), -m(2,3),
               -m(3,0), -m(3,1), -m(3,2), -m(3,3)); 
                  
    return mtx; 
}

Matrix4 operator - (const Matrix4 & m1, const Matrix4 & m2)
{
    Matrix4 mtx(m1(0,0) - m2(0,0), m1(0,1) - m2(0,1), m1(0,2) - m2(0,2), m1(0,3) - m2(0,3),
	           m1(1,0) - m2(1,0), m1(1,1) - m2(1,1), m1(1,2) - m2(1,2), m1(1,3) - m2(1,3),
	           m1(2,0) - m2(2,0), m1(2,1) - m2(2,1), m1(2,2) - m2(2,2), m1(2,3) - m2(2,3),
	           m1(3,0) - m2(3,0), m1(3,1) - m2(3,1), m1(3,2) - m2(3,2), m1(3,3) - m2(3,3));
	return mtx; 
}

Matrix4 operator + (const Matrix4 & m1, const Matrix4 & m2)
{
    Matrix4 mtx(m1(0,0) + m2(0,0), m1(0,1) + m2(0,1), m1(0,2) + m2(0,2), m1(0,3) + m2(0,3),
	           m1(1,0) + m2(1,0), m1(1,1) + m2(1,1), m1(1,2) + m2(1,2), m1(1,3) + m2(1,3),
	           m1(2,0) + m2(2,0), m1(2,1) + m2(2,1), m1(2,2) + m2(2,2), m1(2,3) + m2(2,3),
	           m1(3,0) + m2(3,0), m1(3,1) + m2(3,1), m1(3,2) + m2(3,2), m1(3,3) + m2(3,3));
	return mtx; 
}

Matrix4 operator * (const Matrix4 & m1, const Matrix4 & m2)
{
    Matrix4 result; 
#if 1	    
    for(int i = 0; i < 4; ++i)
    {
        for(int j = 0; j < 4; ++j)
        {  
            float v = 0; 
            for(int k = 0; k < 4; ++k)
            {
                //v += m1(i,k) * m2(k,j);
                v += m1(k,j) * m2(i,k);
            }
            result(i, j) = v; 
        }
    }
#else

#if 0

	result(0,0) = m2(0,0)*m1(0,0) + m2(1,0)*m1(0,1) + m2(2,0)*m1(0,2) + m2(3,0)*m1(0,3);
	result(1,0) = m2(0,0)*m1(1,0) + m2(1,0)*m1(1,1) + m2(2,0)*m1(1,2) + m2(3,0)*m1(1,3);
	result(2,0) = m2(0,0)*m1(2,0) + m2(1,0)*m1(2,1) + m2(2,0)*m1(2,2) + m2(3,0)*m1(2,3);
	result(3,0) = m2(0,0)*m1(3,0) + m2(1,0)*m1(3,1) + m2(2,0)*m1(3,2) + m2(3,0)*m1(3,3);
	
	result(0,1) = m2(0,1)*m1(0,0) + m2(1,1)*m1(0,1) + m2(2,1)*m1(0,2) + m2(3,1)*m1(0,3);
	result(1,1) = m2(0,1)*m1(1,0) + m2(1,1)*m1(1,1) + m2(2,1)*m1(1,2) + m2(3,1)*m1(1,3);
	result(2,1) = m2(0,1)*m1(2,0) + m2(1,1)*m1(2,1) + m2(2,1)*m1(2,2) + m2(3,1)*m1(2,3);
	result(3,1) = m2(0,1)*m1(3,0) + m2(1,1)*m1(3,1) + m2(2,1)*m1(3,2) + m2(3,1)*m1(3,3);
	
	result(0,2) = m2(0,2)*m1(0,0) + m2(1,2)*m1(0,1) + m2(2,2)*m1(0,2) + m2(3,2)*m1(0,3);
	result(1,2) = m2(0,2)*m1(1,0) + m2(1,2)*m1(1,1) + m2(2,2)*m1(1,2) + m2(3,2)*m1(1,3);
	result(2,2) = m2(0,2)*m1(2,0) + m2(1,2)*m1(2,1) + m2(2,2)*m1(2,2) + m2(3,2)*m1(2,3);
	result(3,2) = m2(0,2)*m1(3,0) + m2(1,2)*m1(3,1) + m2(2,2)*m1(3,2) + m2(3,2)*m1(3,3);

	result(0,3) = m2(0,3)*m1(0,0) + m2(1,3)*m1(0,1) + m2(2,3)*m1(0,2) + m2(3,3)*m1(0,3);
	result(1,3) = m2(0,3)*m1(1,0) + m2(1,3)*m1(1,1) + m2(2,3)*m1(1,2) + m2(3,3)*m1(1,3);
	result(2,3) = m2(0,3)*m1(2,0) + m2(1,3)*m1(2,1) + m2(2,3)*m1(2,2) + m2(3,3)*m1(2,3);
	result(3,3) = m2(0,3)*m1(3,0) + m2(1,3)*m1(3,1) + m2(2,3)*m1(3,2) + m2(3,3)*m1(3,3);
	
#else

	result(0,0) = m1(0,0)*m2(0,0) + m1(0,1)*m2(1,0) + m1(0,2)*m2(2,0) + m1(0,3)*m2(3,0);
	result(0,1) = m1(0,0)*m2(0,1) + m1(0,1)*m2(1,1) + m1(0,2)*m2(2,1) + m1(0,3)*m2(3,1);
	result(0,2) = m1(0,0)*m2(0,2) + m1(0,1)*m2(1,2) + m1(0,2)*m2(2,2) + m1(0,3)*m2(3,2);
	result(0,3) = m1(0,0)*m2(0,3) + m1(0,1)*m2(1,3) + m1(0,2)*m2(2,3) + m1(0,3)*m2(3,3);
	
	result(1,0) = m1(1,0)*m2(0,0) + m1(1,1)*m2(1,0) + m1(1,2)*m2(2,0) + m1(1,3)*m2(3,0);
	result(1,1) = m1(1,0)*m2(0,1) + m1(1,1)*m2(1,1) + m1(1,2)*m2(2,1) + m1(1,3)*m2(3,1);
	result(1,2) = m1(1,0)*m2(0,2) + m1(1,1)*m2(1,2) + m1(1,2)*m2(2,2) + m1(1,3)*m2(3,2);
	result(1,3) = m1(1,0)*m2(0,3) + m1(1,1)*m2(1,3) + m1(1,2)*m2(2,3) + m1(1,3)*m2(3,3);
	
	result(2,0) = m1(2,0)*m2(0,0) + m1(2,1)*m2(1,0) + m1(2,2)*m2(2,0) + m1(2,3)*m2(3,0);
	result(2,1) = m1(2,0)*m2(0,1) + m1(2,1)*m2(1,1) + m1(2,2)*m2(2,1) + m1(2,3)*m2(3,1);
	result(2,2) = m1(2,0)*m2(0,2) + m1(2,1)*m2(1,2) + m1(2,2)*m2(2,2) + m1(2,3)*m2(3,2);
	result(2,3) = m1(2,0)*m2(0,3) + m1(2,1)*m2(1,3) + m1(2,2)*m2(2,3) + m1(2,3)*m2(3,3);

	result(2,0) = m1(2,0)*m2(0,0) + m1(2,1)*m2(1,0) + m1(2,2)*m2(2,0) + m1(2,3)*m2(3,0);
	result(2,1) = m1(2,0)*m2(0,1) + m1(2,1)*m2(1,1) + m1(2,2)*m2(2,1) + m1(2,3)*m2(3,1);
	result(2,2) = m1(2,0)*m2(0,2) + m1(2,1)*m2(1,2) + m1(2,2)*m2(2,2) + m1(2,3)*m2(3,2);
	result(2,3) = m1(2,0)*m2(0,3) + m1(2,1)*m2(1,3) + m1(2,2)*m2(2,3) + m1(2,3)*m2(3,3);
#endif

#endif

	return result; 
}

Vector  operator * (const Matrix4 & m, const Vector & v)
{
	Vector result; 
	
#if 0	
	for(int i = 0; i < 4; ++i)
    {
        for(int j = 0; j < 4; ++j)
        {  
            float v = 0; 
            for(int k = 0; k < 4; ++k)
            {
                //v += m1(i,k) * m2(k,j);
                v += m(k,j) * m2(i,k);
            }
            result(i, j) = v; 
        }
    }
#endif 
    
	result.x = m(0,0) * v.x + m(0,1) * v.y + m(0,2) * v.z + m(0,3) * v.w;
	result.y = m(1,0) * v.x + m(1,1) * v.y + m(1,2) * v.z + m(1,3) * v.w;
	result.z = m(2,0) * v.x + m(2,1) * v.y + m(2,2) * v.z + m(2,3) * v.w;
	result.w = m(3,0) * v.x + m(3,1) * v.y + m(3,2) * v.z + m(3,3) * v.w;    
	
	return result; 
}

Vector  operator * (const Vector & v , const Matrix4 & m)
{

}

Matrix4 operator * (const Matrix4 & m, const float s)
{
    Matrix4 mtx(m(0,0) * s, m(0,1) * s, m(0,2) * s, m(0,3) * s,
	           m(1,0) * s, m(1,1) * s, m(1,2) * s, m(1,3) * s,
	           m(2,0) * s, m(2,1) * s, m(2,2) * s, m(2,3) * s,
	           m(3,0) * s, m(3,1) * s, m(3,2) * s, m(3,3) * s);
	return mtx; 
}

Matrix4 operator * (const float s, const Matrix4 & m)
{
    Matrix4 mtx(m(0,0) * s, m(0,1) * s, m(0,2) * s, m(0,3) * s,
	           m(1,0) * s, m(1,1) * s, m(1,2) * s, m(1,3) * s,
	           m(2,0) * s, m(2,1) * s, m(2,2) * s, m(2,3) * s,
	           m(3,0) * s, m(3,1) * s, m(3,2) * s, m(3,3) * s);
	return mtx; 
}

Matrix4 Transpose(const Matrix4 & m)
{
    Matrix4 t; 
    
    for(int i = 0; i < 4; ++i)
    {
        for(int j = 0; j < 4; ++j)
        {
            t(i,j) = m(j,i); 
        }
    }
    
    return t; 
}

Matrix4 Inverse(const Matrix4 & m)
{
    //double inv.elem[16], det;
    Matrix4 inv;
    float det; 
    int i;

    inv.elem[0] = m.elem[5]  * m.elem[10] * m.elem[15] - 
             m.elem[5]  * m.elem[11] * m.elem[14] - 
             m.elem[9]  * m.elem[6]  * m.elem[15] + 
             m.elem[9]  * m.elem[7]  * m.elem[14] +
             m.elem[13] * m.elem[6]  * m.elem[11] - 
             m.elem[13] * m.elem[7]  * m.elem[10];

    inv.elem[4] = -m.elem[4]  * m.elem[10] * m.elem[15] + 
              m.elem[4]  * m.elem[11] * m.elem[14] + 
              m.elem[8]  * m.elem[6]  * m.elem[15] - 
              m.elem[8]  * m.elem[7]  * m.elem[14] - 
              m.elem[12] * m.elem[6]  * m.elem[11] + 
              m.elem[12] * m.elem[7]  * m.elem[10];

    inv.elem[8] = m.elem[4]  * m.elem[9] * m.elem[15] - 
             m.elem[4]  * m.elem[11] * m.elem[13] - 
             m.elem[8]  * m.elem[5] * m.elem[15] + 
             m.elem[8]  * m.elem[7] * m.elem[13] + 
             m.elem[12] * m.elem[5] * m.elem[11] - 
             m.elem[12] * m.elem[7] * m.elem[9];

    inv.elem[12] = -m.elem[4]  * m.elem[9] * m.elem[14] + 
               m.elem[4]  * m.elem[10] * m.elem[13] +
               m.elem[8]  * m.elem[5] * m.elem[14] - 
               m.elem[8]  * m.elem[6] * m.elem[13] - 
               m.elem[12] * m.elem[5] * m.elem[10] + 
               m.elem[12] * m.elem[6] * m.elem[9];

    inv.elem[1] = -m.elem[1]  * m.elem[10] * m.elem[15] + 
              m.elem[1]  * m.elem[11] * m.elem[14] + 
              m.elem[9]  * m.elem[2] * m.elem[15] - 
              m.elem[9]  * m.elem[3] * m.elem[14] - 
              m.elem[13] * m.elem[2] * m.elem[11] + 
              m.elem[13] * m.elem[3] * m.elem[10];

    inv.elem[5] = m.elem[0]  * m.elem[10] * m.elem[15] - 
             m.elem[0]  * m.elem[11] * m.elem[14] - 
             m.elem[8]  * m.elem[2] * m.elem[15] + 
             m.elem[8]  * m.elem[3] * m.elem[14] + 
             m.elem[12] * m.elem[2] * m.elem[11] - 
             m.elem[12] * m.elem[3] * m.elem[10];

    inv.elem[9] = -m.elem[0]  * m.elem[9] * m.elem[15] + 
              m.elem[0]  * m.elem[11] * m.elem[13] + 
              m.elem[8]  * m.elem[1] * m.elem[15] - 
              m.elem[8]  * m.elem[3] * m.elem[13] - 
              m.elem[12] * m.elem[1] * m.elem[11] + 
              m.elem[12] * m.elem[3] * m.elem[9];

    inv.elem[13] = m.elem[0]  * m.elem[9] * m.elem[14] - 
              m.elem[0]  * m.elem[10] * m.elem[13] - 
              m.elem[8]  * m.elem[1] * m.elem[14] + 
              m.elem[8]  * m.elem[2] * m.elem[13] + 
              m.elem[12] * m.elem[1] * m.elem[10] - 
              m.elem[12] * m.elem[2] * m.elem[9];

    inv.elem[2] = m.elem[1]  * m.elem[6] * m.elem[15] - 
             m.elem[1]  * m.elem[7] * m.elem[14] - 
             m.elem[5]  * m.elem[2] * m.elem[15] + 
             m.elem[5]  * m.elem[3] * m.elem[14] + 
             m.elem[13] * m.elem[2] * m.elem[7] - 
             m.elem[13] * m.elem[3] * m.elem[6];

    inv.elem[6] = -m.elem[0]  * m.elem[6] * m.elem[15] + 
              m.elem[0]  * m.elem[7] * m.elem[14] + 
              m.elem[4]  * m.elem[2] * m.elem[15] - 
              m.elem[4]  * m.elem[3] * m.elem[14] - 
              m.elem[12] * m.elem[2] * m.elem[7] + 
              m.elem[12] * m.elem[3] * m.elem[6];

    inv.elem[10] = m.elem[0]  * m.elem[5] * m.elem[15] - 
              m.elem[0]  * m.elem[7] * m.elem[13] - 
              m.elem[4]  * m.elem[1] * m.elem[15] + 
              m.elem[4]  * m.elem[3] * m.elem[13] + 
              m.elem[12] * m.elem[1] * m.elem[7] - 
              m.elem[12] * m.elem[3] * m.elem[5];

    inv.elem[14] = -m.elem[0]  * m.elem[5] * m.elem[14] + 
               m.elem[0]  * m.elem[6] * m.elem[13] + 
               m.elem[4]  * m.elem[1] * m.elem[14] - 
               m.elem[4]  * m.elem[2] * m.elem[13] - 
               m.elem[12] * m.elem[1] * m.elem[6] + 
               m.elem[12] * m.elem[2] * m.elem[5];

    inv.elem[3] = -m.elem[1] * m.elem[6] * m.elem[11] + 
              m.elem[1] * m.elem[7] * m.elem[10] + 
              m.elem[5] * m.elem[2] * m.elem[11] - 
              m.elem[5] * m.elem[3] * m.elem[10] - 
              m.elem[9] * m.elem[2] * m.elem[7] + 
              m.elem[9] * m.elem[3] * m.elem[6];

    inv.elem[7] = m.elem[0] * m.elem[6] * m.elem[11] - 
             m.elem[0] * m.elem[7] * m.elem[10] - 
             m.elem[4] * m.elem[2] * m.elem[11] + 
             m.elem[4] * m.elem[3] * m.elem[10] + 
             m.elem[8] * m.elem[2] * m.elem[7] - 
             m.elem[8] * m.elem[3] * m.elem[6];

    inv.elem[11] = -m.elem[0] * m.elem[5] * m.elem[11] + 
               m.elem[0] * m.elem[7] * m.elem[9] + 
               m.elem[4] * m.elem[1] * m.elem[11] - 
               m.elem[4] * m.elem[3] * m.elem[9] - 
               m.elem[8] * m.elem[1] * m.elem[7] + 
               m.elem[8] * m.elem[3] * m.elem[5];

    inv.elem[15] = m.elem[0] * m.elem[5] * m.elem[10] - 
              m.elem[0] * m.elem[6] * m.elem[9] - 
              m.elem[4] * m.elem[1] * m.elem[10] + 
              m.elem[4] * m.elem[2] * m.elem[9] + 
              m.elem[8] * m.elem[1] * m.elem[6] - 
              m.elem[8] * m.elem[2] * m.elem[5];

    det = m.elem[0] * inv.elem[0] + m.elem[1] * inv.elem[4] + m.elem[2] * inv.elem[8] + m.elem[3] * inv.elem[12];

    if (det == 0)
        return m;

    det = 1.0 / det;

	//Matrix4 invOut;
    //for (i = 0; i < 16; i++)
    //    invOut.elem[i] = inv.elem[i] * det;

    return Matrix4(inv.elem[0 ] * det, inv.elem[1 ] * det, inv.elem[2 ] * det, inv.elem[3 ] * det,
                   inv.elem[4 ] * det, inv.elem[5 ] * det, inv.elem[6 ] * det, inv.elem[7 ] * det,
                   inv.elem[8 ] * det, inv.elem[9 ] * det, inv.elem[10] * det, inv.elem[11] * det,
                   inv.elem[12] * det, inv.elem[13] * det, inv.elem[14] * det, inv.elem[15] * det);
}

float * MatrixToArray(const Matrix4 & m)
{
    static float m16[16]; 
    Matrix4 t(m); 
    t = Transpose(t); 
    
    int k; 
    for(int i = 0, j = 0; i < 16; ++i)
    {  
        if ((i-k)>=4) 
        {
            j++;
            k = i;  
        }
        m16[i] = t(j,i%4);
    }
    
    return m16;
} 

/*
 *============================================================
 *  MATRIX 3X3
 *============================================================
 */
 
Matrix3::Matrix3(float m11, float m12, float m13,
        float m21, float m22, float m23,
        float m31, float m32, float m33)
{
    elem[0 ] = m11; elem[1 ] = m12; elem[2 ] = m13;
    elem[3 ] = m21; elem[4 ] = m22; elem[5 ] = m23; 
    elem[6 ] = m31; elem[7 ] = m32; elem[8 ] = m33; 
}
        
Matrix3::Matrix3(const Matrix3 & m)
{
	*this = m; 
}
 
Matrix3::Matrix3(const Matrix4 & m)
{
	elem[0 ] = m.elem[0 ]; elem[1 ] = m.elem[1 ]; elem[2 ] = m.elem[2 ];
    elem[3 ] = m.elem[3 ]; elem[4 ] = m.elem[4 ]; elem[5 ] = m.elem[5 ];
    elem[6 ] = m.elem[6 ]; elem[7 ] = m.elem[7 ]; elem[8 ] = m.elem[8 ]; 
}
 
Matrix3::Matrix3()
{
	identity();
}

Matrix3::~Matrix3()
{

}

void Matrix3::identity()
{
    elem[0 ] = 1.0f; elem[1 ] = 0.0f; elem[2 ] = 0.0f;
    elem[3 ] = 0.0f; elem[4 ] = 1.0f; elem[5 ] = 0.0f;
    elem[6 ] = 0.0f; elem[7 ] = 0.0f; elem[8 ] = 1.0f;
}

Matrix3 & Matrix3::operator = (const Matrix3 & m)
{
    elem[0 ] = m.elem[0 ]; elem[1 ] = m.elem[1 ]; elem[2 ] = m.elem[2 ];
    elem[3 ] = m.elem[3 ]; elem[4 ] = m.elem[4 ]; elem[5 ] = m.elem[5 ];
    elem[6 ] = m.elem[6 ]; elem[7 ] = m.elem[7 ]; elem[8 ] = m.elem[8 ]; 
    return *this; 
}

float & Matrix3::operator() (unsigned int r, unsigned int c)
{
    //return elem[r+c*4];
    return elem[c+r*3]; 
}

float Matrix3::operator() (unsigned int r, unsigned int c)const
{
    //return elem[r+c*4];
    return elem[c+r*3];
}  

Matrix3 Transpose(const Matrix3 & m)
{
    Matrix3 t; 
    
    for(int i = 0; i < 3; ++i)
    {
        for(int j = 0; j < 3; ++j)
        {
            t(i,j) = m(j,i); 
        }
    }
    
    return t; 	
}

Matrix3 Inverse(const Matrix3 & m)
{
	float det = m(0, 0) * (m(1, 1) * m(2, 2) - m(2, 1) * m(1, 2)) -
		        m(0, 1) * (m(1, 0) * m(2, 2) - m(1, 2) * m(2, 0)) +
		        m(0, 2) * (m(1, 0) * m(2, 1) - m(1, 1) * m(2, 0));

	float invdet = 1.0f / det;

	Matrix3 minv; // inverse of matrix m
	minv(0, 0) = (m(1, 1) * m(2, 2) - m(2, 1) * m(1, 2)) * invdet;
	minv(0, 1) = (m(0, 2) * m(2, 1) - m(0, 1) * m(2, 2)) * invdet;
	minv(0, 2) = (m(0, 1) * m(1, 2) - m(0, 2) * m(1, 1)) * invdet;
	minv(1, 0) = (m(1, 2) * m(2, 0) - m(1, 0) * m(2, 2)) * invdet;
	minv(1, 1) = (m(0, 0) * m(2, 2) - m(0, 2) * m(2, 0)) * invdet;
	minv(1, 2) = (m(1, 0) * m(0, 2) - m(0, 0) * m(1, 2)) * invdet;
	minv(2, 0) = (m(1, 0) * m(2, 1) - m(2, 0) * m(1, 1)) * invdet;
	minv(2, 1) = (m(2, 0) * m(0, 1) - m(0, 0) * m(2, 1)) * invdet;
	minv(2, 2) = (m(0, 0) * m(1, 1) - m(1, 0) * m(0, 1)) * invdet;
	
	return minv;
}

