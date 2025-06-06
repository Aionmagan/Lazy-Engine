#ifndef __MESH_H__
#define __MESH_H__

#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL2/SDL.h>

#include <string>
#include <vector>

struct VertexData
{
	float vx, vy, vz; 
	float tu, tv; 
	float nx, ny, nz;
	float tx, ty, tz; //tangent 
};

struct Vertex
{
	float x, y, z; 
};

struct UV
{
	float u, v; 
};

struct Face
{
	int vx, vy, vz; 
	int nx, ny, nz; 
	int ux, uy, uz;
};

class Model
{
public:
	std::vector<VertexData> data; 	
	
	std::vector<Vertex> verts; 
	std::vector<Vertex> norms; 
	std::vector<Face> 	faces;
	int               	face_count; 
	//std::vector<TangentData> tangentData; 
	Model(std::string filename, bool collisionMesh = false);
	Model();
   ~Model();
   
   	bool load(std::string filename, bool collisionMesh = false); 
   	void freeMemory(); 
public: 

	GLuint m_VBO, m_VAO; 
	
private:
	void SetupVertex(); 
};

#endif/*__MESH_H__*/
