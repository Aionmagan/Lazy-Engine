#ifndef __MATRIX_H__
#define __MATRIX_H__

#include "vector.h"
#include "quaternion.h"

struct Matrix4
{
    Matrix4(float m11, float m12, float m13, float m14,
           float m21, float m22, float m23, float m24,
           float m31, float m32, float m33, float m34,
           float m41, float m42, float m43, float m44);
            
    Matrix4(const Matrix4 & m); 
    Matrix4(); //identity
   ~Matrix4(); 
   
    void identity(); 
   
    void translate(float x, float y, float z); 
    void scale(float x, float y, float z);
    
    /*all rotation uses radians*/
    /*rotate function is Z Y X order*/
    void rotate(float x, float y, float z);  
    void rotateX(float radian);
    void rotateY(float radian);
    void rotateZ(float radian);
    
    void transpose(); 
    
/*================================
 *Vector parameters
 *===============================*/
    void translate(Vector & v);
    void scale(Vector & v);  
    void rotate(Vector & v);  
    
    void lookAt(Vector & eye, Vector & forward, Vector & up);
    void perspectiveProj(float fov, float aspect, float near, float far);
    void orthoProj(float left, float right, float bottom, float top, float near, float far);
    void quaternionToMatrix(const Quaternion & q); 
    
/*=================================
 *static functions and operators 
 *================================*/
    Matrix4 & operator = (const Matrix4 & m);
    float  & operator() (unsigned int r, unsigned int c);
    float    operator() (unsigned int r, unsigned int c)const;  
    
//private:
    //float elem[4][4]; //elements
public: 

    float elem[16];

};


/*=================================
 * Global operators / function
 *================================*/
Matrix4 operator - (const Matrix4 & m);
Matrix4 operator - (const Matrix4 & m1, const Matrix4 & m2);
Matrix4 operator + (const Matrix4 & m1, const Matrix4 & m2);
Matrix4 operator * (const Matrix4 & m1, const Matrix4 & m2);
Vector  operator * (const Matrix4 & m, const Vector & v);
Vector  operator * (const Vector & v , const Matrix4 & m); 
Matrix4 operator * (const Matrix4 & m, const float s);
Matrix4 operator * (const float s, const Matrix4 & m);

//make this a static function later
Matrix4 Transpose(const Matrix4 & m); 
Matrix4 Inverse(const Matrix4 & m); 
//tmp function 
float * MatrixToArray(const Matrix4 & m);

struct Matrix3
{
	Matrix3(float m11, float m12, float m13,
	        float m21, float m22, float m23,
	        float m31, float m32, float m33); 
	        
	Matrix3(const Matrix3 & m); 
	Matrix3(const Matrix4 & m); 
	Matrix3(); 
   ~Matrix3();
   
   	void identity();
   
	Matrix3 & operator = (const Matrix3 & m);
    float  & operator() (unsigned int r, unsigned int c);
    float    operator() (unsigned int r, unsigned int c)const;    
    
    float elem[9]; 
};

Matrix3 Transpose(const Matrix3 & m); 
Matrix3 Inverse(const Matrix3 & m); 

#endif/*__MATRIX_H__*/
