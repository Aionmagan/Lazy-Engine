#include "ply.h"

#include <cstdio>
#include <cstring>

PlyMesh::PlyMesh(std::string filename)
{
	load(filename); 
}

PlyMesh::PlyMesh(std::string filename, bool compileList)
{
	load(filename, compileList); 
}

PlyMesh::PlyMesh()
{
	
}

PlyMesh::~PlyMesh()
{
	freeMemory(); 
}

void PlyMesh::freeMemory()
{
	std::vector<Vertex> vverts; 
	std::vector<UV> 	vuvs; 
	std::vector<Vertex> vnorms; 
	std::vector<PlyFace> 	vfaces;

	
	this->verts.swap(vverts); 
	this->uvs.swap(vuvs); 
	this->norms.swap(vnorms); 
	this->face_count = 0; 
	this->faces.swap(vfaces); 
}

bool PlyMesh::load(std::string filename)
{
	return load(filename, true); //should maybe use default parameters but fuck C++, C FTW 
}

bool PlyMesh::load(std::string filename, bool compileList)
{
	FILE* fp = NULL; 
	
	unsigned int vert_mem; 
	unsigned int face_mem; 
	
	if ((fp = fopen(filename.c_str(), "r")) == NULL)
	{
		printf("ERROR: %s not found\n", filename.c_str()); 
		return false; 
	}
	
	printf("%s opened \n", filename.c_str());
	
	//loading headers
	while(1)
	{
   		char line[128];
   		int res = fscanf(fp, "%s", line);
   		if (res == EOF) {break;}
   		
   		//if (fgets(line, sizeof(line), fp)==NULL) break;
   		//printf("[%s]\n", line);
   		     if (strcmp(line, "vertex" ) == 0) {fscanf(fp, "%d", &vert_mem);}
   		else if (strcmp(line, "face" ) == 0) {fscanf(fp, "%d", &face_mem);}	
	}
	
	printf("%d, %d\n", vert_mem, face_mem);
	
	verts.resize(vert_mem); 
	norms.resize(vert_mem);
	uvs.resize(vert_mem);
	colors.resize(vert_mem); 
	faces.resize(face_mem); 
	//mesh->verts = (vert_t*) malloc(sizeof(vert_t) * vert_mem);
	//mesh->norms = (vert_t*) malloc(sizeof(vert_t) * vert_mem);
	//mesh->uvs   = (uv_t*  ) malloc(sizeof(uv_t  ) * vert_mem);
	//mesh->colors= (color_t*) malloc(sizeof(color_t) * vert_mem); 
	//mesh->faces = (face_t*) malloc(sizeof(face_t) * face_mem); 
	
	rewind(fp);
	
	while(1)
	{
		int i; 
		int useless; 
		char line[128];
   		int res = fscanf(fp, "%s", line);
		if (res == EOF) break;                
		//printf("%s", line);
		int r, g, b, a; 
		if (strcmp(line, "end_header") == 0)
		{
			//printf("i'm here\n");
			for(i = 0; i < vert_mem; ++i)
			{
							/*vertex normal uv vertex_color*/
				fscanf(fp,"%f %f %f %f %f %f %f %f %d %d %d %d\n",
				              &verts[i].x, &verts[i].y, &verts[i].z,
				              &norms[i].x, &norms[i].y, &norms[i].z,
				              &uvs[i].u, &uvs[i].v,
				              &r, &g, &b, &a);
				//printf("%d, %d, %d, %d\n", r, g, b, a);             
				colors[i].r = r/255.0f;
				colors[i].g = g/255.0f;
				colors[i].b = b/255.0f;
				colors[i].a = a/255.0f; 
			}
			
			for(i = 0; i < face_mem; ++i)
			{
				fscanf(fp, "%d %d %d %d\n", &useless, 
				       &faces[i].x, &faces[i].y, &faces[i].z);
			}
		}
	}
	
	//for(int i = 0; i < vert_mem; ++i)
	//printf("x%f, y%f, z%f",mesh->verts[i].x, mesh->verts[i].y, mesh->verts[i].z);
	
	face_count = face_mem; 
	
	printf("%s finished loading\n", filename.c_str());
	return true;	
}
