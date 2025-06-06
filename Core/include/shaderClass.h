#ifndef __SHADER_CLASS_H__
#define __SHADER_CLASS_H__

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "mathcommon.h"
#include "vector.h" 
#include "matrix.h" 

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
public:
	GLuint ID; //shader id; 
	Shader(); 
	Shader(const char* vs, const char* fs);
	void load(const char* vs, const char* fs); 
	void loadProgram(const char* vs, const char* fs);
		
	void use(); 
	void setBool(const std::string & name, bool value) const; 
	void setInt(const std::string & name, int value) const;
	void setFloat(const std::string & name, float value) const;
	void setVec3(const std::string & name, float x, float y, float z);
	void setVec3(const std::string & name, Vector3 & v);
	void setVec4(const std::string & name, float x, float y, float z, float w); 
	void setVec4(const std::string & name, Vector4 & v);
	void setMat3(const std::string & name, GLboolean transpose, Matrix3 & m);
	void setMat4(const std::string & name, GLboolean transpose, Matrix4 & m);
public:
	GLuint PVMLoc, projLoc, viewLoc, modelLoc, TBNLoc;
	GLuint MatAmbLoc, MatDifLoc, MatSpeLoc, MatShiLoc;
	GLuint lSizeLoc, lViewPosLoc,
		   lTypeLoc [MAX_LIGHT_SIZE], lColorLoc [MAX_LIGHT_SIZE], 
		   lPosLoc  [MAX_LIGHT_SIZE], lDirLoc   [MAX_LIGHT_SIZE], 
		   lConstLoc[MAX_LIGHT_SIZE], lLinearLoc[MAX_LIGHT_SIZE],
		   lQuadLoc [MAX_LIGHT_SIZE], lCutoffLoc[MAX_LIGHT_SIZE],
		   lEnaLoc  [MAX_LIGHT_SIZE]; 		   	     
};

#endif//__SHADER_CLASS_H__
