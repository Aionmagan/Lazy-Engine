#ifndef __PLY_H__
#define __PLY_H__

#include <vector>
#include <string>

#include "mesh.h" 

struct Color
{
	float r, g, b, a; 
};

struct PlyFace
{
	unsigned int x, y, z; 
};

class  PlyMesh
{
public:
	std::vector<Vertex>  verts; 
	std::vector<UV> 	 uvs; 
	std::vector<Vertex>  norms;
	std::vector<Color>   colors; 
	std::vector<PlyFace> faces;
	int               	 face_count; 

public:
	PlyMesh(std::string filename);
	PlyMesh(std::string filename, bool compileList);
	PlyMesh(); //for data oriented 
   ~PlyMesh(); 	
   	void freeMemory(); 
   	bool load(std::string filename); 
   	bool load(std::string filename, bool compileList); 

};

#endif/*__PLY_H__*/
