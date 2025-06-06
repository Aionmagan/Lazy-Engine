#include "shaderClass.h" 
#include <cstdio>
#include "shader/le_vs.h"
#include "shader/le_fs.h" 

enum ShaderToRead
{
	VS, FS
};

void CheckForLE(std::string & str, ShaderToRead shader)
{
	size_t len = str.find("#includeLE");
	//std::cout << str << " | " << len << std::endl;
	if (len==std::string::npos)return; 
	//std::cout << le_vs << std::endl;
#define LE_INCLUDE 10
	// ensure ifstream objects can throw exceptions:
#if 1
	str.replace(len, 10, "");
	switch(shader)
	{
		default:
		case VS:
			//str.replace(len, len+LE_INCLUDE, le_vs); 
			str.insert(len, le_vs); 
			//str.append(le_vs, len, le_vs.size());
			break;
		case FS: 
			str.insert(len, le_fs);
			//str.replace(len, len+LE_INCLUDE, le_fs); 
			break;
	}
	
	//std::cout << str << std::endl;
#else
	std::ifstream shaderFile; 
	shaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		//str.erase(len, len+LE_INCLUDE);
		//shaderFile.open("le_vs.glsl");
		switch(shader)
		{
			default:
			case VS:
				shaderFile.open("shader/le_vs.glsl"); 
				break;
			case FS: 
				shaderFile.open("shader/le_fs.glsl"); 
				break;
		}
		
		std::cout << "is open ? " << shaderFile.is_open() << std::endl;
		std::stringstream shaderStream; 
		shaderStream << shaderFile.rdbuf(); 		
		shaderFile.close();
		std::string buffer = shaderStream.str(); 
		
		std::cout << "where here" << std::endl;
		//str.append(buffer, buffer.size());
		str.replace(len, len+LE_INCLUDE, shaderStream.str()); 
		std::cout << shaderStream.str() << std::endl;
	}
	catch(std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::" << e.what() << std::endl;
	}
	//std::cout << str << std::endl;
#endif
#undef LE_INCLUDE
}

Shader::Shader(){}

Shader::Shader(const char* vs, const char* fs)
{
	load(vs, fs); 
}

void Shader::load(const char* vs, const char* fs)
{
	// 1. retrieve the vertex/fragment source code from filePath
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;
	// ensure ifstream objects can throw exceptions:
	vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
	
	try
	{
		// open files
		vShaderFile.open(vs);
		fShaderFile.open(fs);
		std::stringstream vShaderStream, fShaderStream;
		// read file’s buffer contents into streams
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		// close file handlers
		vShaderFile.close();
		fShaderFile.close();
		
		//check for #include<LE>
		std::string vsTmp = vShaderStream.str(); 
		std::string fsTmp = fShaderStream.str(); 
		
		CheckForLE(vsTmp, ShaderToRead::VS);
		CheckForLE(fsTmp, ShaderToRead::FS);  
		
		// convert stream into string
		//vertexCode = vShaderStream.str();
		//fragmentCode = fShaderStream.str();
		vertexCode = vsTmp; 
		fragmentCode = fsTmp;
	}
	catch(std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}

	loadProgram(vertexCode.c_str(), fragmentCode.c_str()); 
#if 0	
	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();
	
	// 2. compile shaders
	unsigned int vertex, fragment;
	int success;
	char infoLog[512];
	// vertex Shader
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);
	// print compile errors if any
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if(!success)
	{
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << vs << "\n" <<
						infoLog << std::endl;
	};
	
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);
	// print compile errors if any
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if(!success)
	{
		glGetShaderInfoLog(fragment, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << fs << "\n" << 
						infoLog << std::endl;
	};
	
	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	glLinkProgram(ID);
	// print linking errors if any
	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if(!success)
	{
		glGetProgramInfoLog(ID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" <<
						infoLog << std::endl;
	}
	// delete shaders; they’re linked into our program and no longer necessary
	glDeleteShader(vertex);
	glDeleteShader(fragment);
	
	PVMLoc = glGetUniformLocation(ID, "LE_PVM");
	projLoc = glGetUniformLocation(ID, "LE_proj"); 
	viewLoc = glGetUniformLocation(ID, "LE_view");
	modelLoc = glGetUniformLocation(ID, "LE_model");
	TBNLoc = glGetUniformLocation(ID, "LE_TBN"); 
	
	MatAmbLoc = glGetUniformLocation(ID, "LE_material.ambient"); 
	MatDifLoc = glGetUniformLocation(ID, "LE_material.diffuse"); 
	MatSpeLoc = glGetUniformLocation(ID, "LE_material.specular"); 
	MatShiLoc = glGetUniformLocation(ID, "LE_material.shininess"); 
	
	lSizeLoc  = glGetUniformLocation(ID, "LE_lightListSize");
	lViewPosLoc = glGetUniformLocation(ID, "LE_viewPos"); 
	
	for(int i = 0; i < MAX_LIGHT_SIZE; ++i)
	{
		char str[9][512]; 
		
		sprintf(str[0], "LE_lightList[%d].type"      , i);
		sprintf(str[1], "LE_lightList[%d].color"     , i);
		sprintf(str[2], "LE_lightList[%d].position"  , i);
		sprintf(str[3], "LE_lightList[%d].direction" , i);
		sprintf(str[4], "LE_lightList[%d].constant"  , i);
		sprintf(str[5], "LE_lightList[%d].linear"    , i);
		sprintf(str[6], "LE_lightList[%d].quadratic" , i);
		sprintf(str[7], "LE_lightList[%d].cutoff"    , i);
		sprintf(str[8], "LE_lightList[%d].enabled"   , i);
		//printf("%s %s %s %s %s\n", str[0], str[1], str[2], str[3], str[4]);
		
		lTypeLoc[i]   = glGetUniformLocation(ID, str[0]);
		lColorLoc[i]  = glGetUniformLocation(ID, str[1]);
		lPosLoc[i]    = glGetUniformLocation(ID, str[2]);
		lDirLoc[i]    = glGetUniformLocation(ID, str[3]);
	    lConstLoc[i]  = glGetUniformLocation(ID, str[4]);
	    lLinearLoc[i] = glGetUniformLocation(ID, str[5]); 
	    lQuadLoc[i]   = glGetUniformLocation(ID, str[6]); 
	    lCutoffLoc[i] = glGetUniformLocation(ID, str[7]); 		
		lEnaLoc[i]    = glGetUniformLocation(ID, str[8]); 
	}
#endif
}

void Shader::loadProgram(const char* vs, const char* fs)
{
	// 2. compile shaders
	unsigned int vertex, fragment;
	int success;
	char infoLog[512];
	// vertex Shader
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vs, NULL);
	glCompileShader(vertex);
	// print compile errors if any
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if(!success)
	{
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << vs << "\n" <<
						infoLog << std::endl;
	};
	
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fs, NULL);
	glCompileShader(fragment);
	// print compile errors if any
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if(!success)
	{
		glGetShaderInfoLog(fragment, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << fs << "\n" << 
						infoLog << std::endl;
	};
	
	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	glLinkProgram(ID);
	// print linking errors if any
	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if(!success)
	{
		glGetProgramInfoLog(ID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" <<
						infoLog << std::endl;
	}
	// delete shaders; they’re linked into our program and no longer necessary
	glDeleteShader(vertex);
	glDeleteShader(fragment);
	
	PVMLoc = glGetUniformLocation(ID, "LE_PVM");
	projLoc = glGetUniformLocation(ID, "LE_proj"); 
	viewLoc = glGetUniformLocation(ID, "LE_view");
	modelLoc = glGetUniformLocation(ID, "LE_model");
	TBNLoc = glGetUniformLocation(ID, "LE_TBN"); 
	
	MatAmbLoc = glGetUniformLocation(ID, "LE_material.ambient"); 
	MatDifLoc = glGetUniformLocation(ID, "LE_material.diffuse"); 
	MatSpeLoc = glGetUniformLocation(ID, "LE_material.specular"); 
	MatShiLoc = glGetUniformLocation(ID, "LE_material.shininess"); 
	
	lSizeLoc  = glGetUniformLocation(ID, "LE_lightListSize");
	lViewPosLoc = glGetUniformLocation(ID, "LE_viewPos"); 
	
	for(int i = 0; i < MAX_LIGHT_SIZE; ++i)
	{
		char str[9][512]; 
		
		sprintf(str[0], "LE_lightList[%d].type"      , i);
		sprintf(str[1], "LE_lightList[%d].color"     , i);
		sprintf(str[2], "LE_lightList[%d].position"  , i);
		sprintf(str[3], "LE_lightList[%d].direction" , i);
		sprintf(str[4], "LE_lightList[%d].constant"  , i);
		sprintf(str[5], "LE_lightList[%d].linear"    , i);
		sprintf(str[6], "LE_lightList[%d].quadratic" , i);
		sprintf(str[7], "LE_lightList[%d].cutoff"    , i);
		sprintf(str[8], "LE_lightList[%d].enabled"   , i);
		//printf("%s %s %s %s %s\n", str[0], str[1], str[2], str[3], str[4]);
		
		lTypeLoc[i]   = glGetUniformLocation(ID, str[0]);
		lColorLoc[i]  = glGetUniformLocation(ID, str[1]);
		lPosLoc[i]    = glGetUniformLocation(ID, str[2]);
		lDirLoc[i]    = glGetUniformLocation(ID, str[3]);
	    lConstLoc[i]  = glGetUniformLocation(ID, str[4]);
	    lLinearLoc[i] = glGetUniformLocation(ID, str[5]); 
	    lQuadLoc[i]   = glGetUniformLocation(ID, str[6]); 
	    lCutoffLoc[i] = glGetUniformLocation(ID, str[7]); 		
		lEnaLoc[i]    = glGetUniformLocation(ID, str[8]); 
	}	
}

void Shader::use()
{
	glUseProgram(ID); 
}

void Shader::setBool(const std::string & name, bool value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::setInt(const std::string & name, int value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string & name, float value) const
{
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setVec3(const std::string & name, float x, float y, float z)
{
	glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
}

void Shader::setVec3(const std::string & name, Vector3 & v)
{
	setVec3(name, v.x,v.y,v.z); 
}

void Shader::setVec4(const std::string & name, float x, float y, float z, float w)
{
	glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w);
}

void Shader::setVec4(const std::string & name, Vector4 & v)
{
	setVec4(name, v.x,v.y,v.z,v.w); 
}

void Shader::setMat3(const std::string & name, GLboolean transpose, Matrix3 & m)
{
	glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, transpose, m.elem);
}

void Shader::setMat4(const std::string & name, GLboolean transpose, Matrix4 & m)
{
	glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, transpose, m.elem);
}

