#include "mesh.h"
#include <cstdio>
#include <cstring>
#include <cstdlib>

#include "vector.h" 

void tangentNormal3(VertexData & v1, VertexData & v2, VertexData & v3)
{
	Vector3 deltaPos1 = Vector3(v3.vx-v1.vx, v3.vy-v1.vy, v3.vz-v1.vz);
	Vector3 deltaPos2 = Vector3(v2.vx-v1.vx, v2.vy-v1.vy, v2.vz-v1.vz);
	
	Vector2 deltaUv1 = Vector2(v3.tu-v1.tu, v3.tv-v1.tv);
	Vector2 deltaUv2 = Vector2(v2.tu-v1.tu, v2.tv-v1.tv);
	
	float r = 1.0f / (deltaUv1.x * deltaUv2.y - deltaUv2.x * deltaUv1.y);
	
	//glm::vec3 tangent = (deltaPos1 * deltaUv2.y - deltaPos2 * deltaUv1.y) * r; 
	Vector3 tangent = r * ((deltaPos1 * deltaUv2.y) + (deltaPos2 * -deltaUv1.y)); 
	
	v1.tx = tangent.x; 
	v1.ty = tangent.y; 
	v1.tz = tangent.z; 
	
	v2.tx = tangent.x; 
	v2.ty = tangent.y; 
	v2.tz = tangent.z; 
	
	v3.tx = tangent.x; 
	v3.ty = tangent.y; 
	v3.tz = tangent.z; 
}

Model::Model(std::string filename, bool collisionMesh)
{
	load(filename, collisionMesh); 
}

bool Model::load(std::string filename, bool collisionMesh)
{
	FILE* fp = NULL; 
	
	std::vector<Vertex> vverts; 
	std::vector<UV>     vuvs; 
	std::vector<Vertex> vnorms; 
	std::vector<Face>   vfaces;
	//int                 vface_length; 
	
	Vertex tvert; 
   	UV     tuv; 
   	Vertex tnorm; 
   	Face   tface; 
   	
   	unsigned int cur_vert[3]; 
   	unsigned int cur_uv  [3]; 
   	unsigned int cur_norm[3];
	
	if ((fp = fopen(filename.c_str(), "r")) == NULL)
	{
   	    printf("file %s not found\n", filename.c_str());
   		return false; 
	} 
	
	printf("file %s was found\n", filename.c_str());
	

   while(1)
   {
	  	char line[256];
	  	int res = fscanf(fp, "%s", line);
	  	if (res == EOF) {break;}
	  

		if (strcmp(line, "v") == 0)
	  	{
	    	 fscanf(fp, "%f %f %f\n", &tvert.x, 
					        			&tvert.y, 
										&tvert.z);
										
			 vverts.push_back(tvert);
	  	}else if(strcmp(line, "vt") == 0)
	  	{
	    	 fscanf(fp, "%f %f\n"  , &tuv.u, 
				             		   &tuv.v);
				             		    
	 		 vuvs.push_back(tuv);
	  	}else if(strcmp(line, "vn") == 0)
	  	{
	    	 fscanf(fp, "%f %f %f\n", &tnorm.x, 
					        			&tnorm.y,
					  	    			&tnorm.z);
	 		 vnorms.push_back(tnorm);
	  	}else if(strcmp(line, "f") == 0)
	  	{
	    	 int match = 0; 
	    	 /*short may have to be replaced with unsigned int*/
	    	 match = fscanf(fp, "%d/%d/%d %d/%d/%d %d/%d/%d\n",
				          				&cur_vert[0], 
				          				&cur_uv  [0], 
				          				&cur_norm[0],

	        	            			&cur_vert[1], 
				          				&cur_uv  [1], 
				          				&cur_norm[1],

	        	            			&cur_vert[2], 
				          				&cur_uv  [2],
				          				&cur_norm[2]);		    	          				 	          			
			
			tface.vx = cur_vert[0] - 1;
			tface.vy = cur_vert[1] - 1;
			tface.vz = cur_vert[2] - 1; 	
			
			tface.ux = cur_uv[0] - 1;
			tface.uy = cur_uv[1] - 1;
			tface.uz = cur_uv[2] - 1; 		

			tface.nx = cur_norm[0] - 1;
			tface.ny = cur_norm[1] - 1;
			tface.nz = cur_norm[2] - 1; 
			
		
			vfaces.push_back(tface); 
			
	 		if (match != 9)
			{
	    		 printf("please enable 'keep vertex order'\n");
	   	     	 
	   	     	 fflush(fp); 
	   	     	 fclose(fp); 
	   	     	 
	   	     	 return false;
	 		}
	 		
//	 		vface_length++; 
//	 		printf("vface_length %d\n", vface_length); 
	 	}
   }
   printf("Finished loading model\n");
   

   fflush(fp); 
   fclose(fp); 
   
   	//std::vector<Vertex> vverts; 
	//std::vector<UV>     vuvs; 
	//std::vector<Vertex> vnorms; 
	//std::vector<Face>   vfaces;
	if (collisionMesh)
	{
		this->verts.swap(vverts);
		this->norms.swap(vnorms);
		this->face_count = vfaces.size(); 
		this->faces.swap(vfaces);
	}else{
	   VertexData d[3]; 
	   //TangentData tanValue; 
	   for(int i = 0; i	< vfaces.size(); ++i)
	   {
			d[0].vx = vverts[vfaces[i].vx].x; 
			d[0].vy = vverts[vfaces[i].vx].y; 
			d[0].vz = vverts[vfaces[i].vx].z; 
			
			d[0].tu = vuvs[vfaces[i].ux].u;
			d[0].tv = vuvs[vfaces[i].ux].v;
			
			d[0].nx = vnorms[vfaces[i].nx].x;
			d[0].ny = vnorms[vfaces[i].nx].y;
			d[0].nz = vnorms[vfaces[i].nx].z;
			
			//data.push_back(d[0]);
			
			d[1].vx = vverts[vfaces[i].vy].x; 
			d[1].vy = vverts[vfaces[i].vy].y; 
			d[1].vz = vverts[vfaces[i].vy].z; 
			
			d[1].tu = vuvs[vfaces[i].uy].u;
			d[1].tv = vuvs[vfaces[i].uy].v;
		
			d[1].nx = vnorms[vfaces[i].ny].x;
			d[1].ny = vnorms[vfaces[i].ny].y;
			d[1].nz = vnorms[vfaces[i].ny].z;
			
			//data.push_back(d[1]);
			
			d[2].vx = vverts[vfaces[i].vz].x; 
			d[2].vy = vverts[vfaces[i].vz].y; 
			d[2].vz = vverts[vfaces[i].vz].z; 
			
			d[2].tu = vuvs[vfaces[i].uz].u;
			d[2].tv = vuvs[vfaces[i].uz].v;
			
			d[2].nx = vnorms[vfaces[i].nz].x;
			d[2].ny = vnorms[vfaces[i].nz].y;
			d[2].nz = vnorms[vfaces[i].nz].z;
			
			//data.push_back(d[2]);
			
			//tangentNormal(tanValue, d[0], d[1], d[2]);
			//tangentData.push_back(tanValue);
			//tangentData.push_back(tanValue);
			//tangentData.push_back(tanValue);
			
			tangentNormal3(d[0], d[1], d[2]);
			
			data.push_back(d[0]);
			data.push_back(d[1]);
			data.push_back(d[2]);
	   }
	}
	
   SetupVertex();
   return true;
}

Model::Model()
{

} //for data oriented 

Model::~Model()
{
	std::vector<VertexData> vd; 	
	this->data.swap(vd); 
} 

void Model::freeMemory()
{
	std::vector<VertexData> vd; 	
	this->data.swap(vd); 
}

void Model::SetupVertex()
{
	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_VBO);
 
	glBindVertexArray(m_VAO); 
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(VertexData), 		data.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), 0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(3*sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(5*sizeof(float)));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(8*sizeof(float)));
	glEnableVertexAttribArray(3);
	glBindVertexArray(0);
}
