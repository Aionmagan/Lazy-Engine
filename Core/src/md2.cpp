#include "md2.h"

#include <stdio.h>
#include <cstring>
#include <cmath>

void CalculateNormal(MD2 & md2, std::string filename)
{
	FILE* fp; 
	
	filename[filename.size() - 1] = 'n'; 
	vector3_t tnorm; 
	std::vector<vector3_t> tnormList; 
	if ((fp = fopen(filename.c_str(), "r")) == NULL)
	{	
		printf("%s missing please add\n", filename.c_str());
		printf("generating flat normals for %s\n", filename.c_str()); 
		
		vector3_t v; 
		
		for(int index = 0; index < md2.numFrames; ++index)
		{
			for(int i = 0; i < md2.numTriangles; ++i)
			{
				//finish this shit
			}
		}
		return; 
	}
	
   while(1)
   {
   		char line[256]; //256bit buffer
   		int res = fscanf(fp, "%s", line);
   		
   		if (res == EOF){break;}
   		
   		if(strcmp(line, "vn") == 0)
   		{
   		     fscanf(fp, "%f %f %f\n", &tnorm.point[0], 
				            		  &tnorm.point[1],
				      	    		  &tnorm.point[2]);
	 		 tnormList.push_back(tnorm);
   		}
   	}
   	
   	fflush(fp); 
   	fclose(fp);
   	
   	md2.normList.swap(tnormList); 
}
#if 1
void FlatNormal(vector3_t *v, float *p1, float *p2, float *p3 )
{
	float a[3], b[3], result[3];
	float length;
	a[0] = p1[0] - p2[0];
	a[1] = p1[1] - p2[1];
	a[2] = p1[2] - p2[2];
	b[0] = p1[0] - p3[0];
	b[1] = p1[1] - p3[1];
	b[2] = p1[2] - p3[2];
	result[0] = a[1] * b[2] - b[1] * a[2];
	result[1] = b[0] * a[2] - a[0] * b[2];
	result[2] = a[0] * b[1] - b[0] * a[1];
	// calculate the length of the normal
	length = (float)sqrt(result[0]*result[0] + result[1]*result[1] +
	result[2]*result[2]);
	// normalize and specify the normal
	//xtcNormal(result[0]/length, result[1]/length, result[2]/length);
	//vector3_t n={result[0]/length, result[1]/length, result[2]/length};
	v->point[0] = result[0]/length; 
	v->point[1] = result[1]/length; 
	v->point[2] = result[2]/length; 
}
#endif

MD2::MD2(){}

MD2::MD2(std::string filename, int tex_w, int tex_h)
{
	LoadModel(filename, tex_w, tex_h); 
}

MD2::~MD2(){}

bool MD2::LoadModel(std::string filename, int tex_w, int tex_h)
{
	FILE* filePtr = NULL;               /*file pointer*/ 
	int fileLen; 			     		/*length of model file*/
	//char* buffer = NULL; 				/*file buffer*/
#if 1
	std::vector<meshIndex_t> ttriIndex; 
	std::vector<texCoord_t> tst; 
	std::vector<vector3_t> tpointList;
	std::vector<vector3_t> tnormList;  
#endif
	//modelData_t* model = NULL;          /*the model*/
	modelHeader_t* modelHeader = NULL;  /*model header*/
	//texture_t* md2Texture = NULL;       /*model texture*/
	
	//stIndex_t* stPtr = NULL;            /*texture indices*/
	frame_t* frame = NULL;              /*frame data*/
	//vector3_t* pointListPtr = NULL;      /*index variable*/
	//meshIndex_t* triIndex = NULL;            /*index variable*/
	//meshIndex_t* bufIndexPtr = NULL;         /*index variable*/
	int i, j;                    		/*index variables*/
	
	
	//tex_t texture;
	/*open the model file*/
	filePtr = fopen(filename.c_str(), "rb");
	if (filePtr == NULL)
	{
		printf("%s not found | check directory\n", filename.c_str()); 
		return false; 
	}
	/*find length of file*/
	fseek(filePtr, 0, SEEK_END);
	fileLen = ftell(filePtr); 
	fseek(filePtr, 0, SEEK_SET); 
printf("malloc in line 36\n");
	/*read entire file into buffer*/
	//buffer = (char*)malloc(sizeof(char)*fileLen+1);
	char buffer[fileLen+1]; 
	fread(buffer, sizeof(char), fileLen, filePtr); 
	
	fflush(filePtr); 
	fclose(filePtr); 
	
	/*extract model file header from buffer*/
	modelHeader = (modelHeader_t*)buffer; 
printf("malloc in line 42\n");
	/*allocate memory for model data*/
	//model = (modelData_t*)malloc(sizeof(modelData_t)); 
	//if (model == NULL)
		//return NULL; 

	printf("numXYZ = %d | numFrames = %d\n", modelHeader->numXYZ, 
	                                         modelHeader->numFrames);
printf("malloc in line 50\n");
	/*allocate memory for all vertices used in model , including animations*/
	//model->pointList = (vector3_t*)malloc(sizeof(vector3_t)*modelHeader->numXYZ*modelHeader->numFrames); 
	tpointList.resize(modelHeader->numXYZ*modelHeader->numFrames); 
	//int tpSize = sizeof(vector3_t)*modelHeader->numXYZ*modelHeader->numFrames;
	//vector3_t tp[modelHeader->numXYZ*modelHeader->numFrames];
	/*store vital model data*/
	//model->numPoints = modelHeader->numXYZ; 
	//model->numFrames = modelHeader->numFrames; 
	//model->frameSize = modelHeader->framesize; 
	numPoints = modelHeader->numXYZ; 
	numFrames = modelHeader->numFrames; 
	frameSize = modelHeader->framesize; 
	
printf("malloc in line 51\n");	
	/*loop number of frames in model file*/
	for(j = 0; j < modelHeader->numFrames; ++j)
	{
		/*offset to the points in this frame*/
		frame = (frame_t*)&buffer[modelHeader->offsetFrames + modelHeader->framesize * j]; 
//printf("frame translate %f %f %f\n", frame->translate[0], frame->translate[1], frame->translate[2]); 
		/*calculate the point positions based on frame details*/
		//pointListPtr = (vector3_t*)&model->pointList[modelHeader->numXYZ * j];
		vector3_t pointListPtr;// = pointList[modelHeader->numXYZ * j];
		//vector3_t normListPtr; 
		for(i = 0; i < modelHeader->numXYZ; ++i)
		{
			pointListPtr.point[0] = frame->scale[0] * 
			                           frame->fp[i].v[0]+
			                           frame->translate[0]; 

			pointListPtr.point[1] = frame->scale[1] * 
			                           frame->fp[i].v[1]+
			                           frame->translate[1]; 

			pointListPtr.point[2] = frame->scale[2] * 
			                           frame->fp[i].v[2]+
			                           frame->translate[2]; 
			                           
			tpointList[(modelHeader->numXYZ*j)+i] = pointListPtr;
			 //tp[(modelHeader->numXYZ*j)+i] = pointListPtr;
		}
		 
		
		
	}
printf("malloc in line 52\n");	
	//tpointList.
/*
	int stp = sizeof(tp) / sizeof(tp[0]); 
	for(i = 0; i < stp; ++i)
	{
//printf("tp [%d] = %f, %f, %f\n", i, tp[i].point[0], tp[i].point[1], tp[i].point[2]); 
		tpointList.push_back(tp[i]); 
	}
*/
printf("malloc in line 53\n");	


printf("malloc in line 93\n");
	/*allocate memory for the model texture coordinates*/
	//model->st = (texCoord_t*)malloc(sizeof(texCoord_t)*modelHeader->numST);
	tst.resize(modelHeader->numST); 
	
	/*store number of texture coordiantes*/
	numST = modelHeader->numST; 
	
	/*set texture pointer to texture coordinate offset*/
	stIndex_t* stPtr = (stIndex_t*)&buffer[modelHeader->offsetST];
	
	/*calculate and store the texture coordinates for the model*/
	texCoord_t tmpst; 
	for(i = 0; i < modelHeader->numST; ++i)
	{
		
		tst[i].s = (float)stPtr[i].s/(float)tex_w; 
		tst[i].t = (float)stPtr[i].t/(float)tex_h;		
		//tmpst.s = (float)stPtr[i].s/(float)tex_w; 
		//tmpst.t = (float)stPtr[i].t/(float)tex_h;
		//tst.push_back(tmpst);
	}
printf("malloc in line 109\n");	
	/*allocate the list of triangle indices*/
	//triIndex = (meshIndex_t*)malloc(sizeof(meshIndex_t)*modelHeader->numTris); 
	ttriIndex.resize(modelHeader->numTris); 
	 
	
	numTriangles = modelHeader->numTris;
	
	/*point to triangle indices in buffer*/
	meshIndex_t* bufIndexPtr = (meshIndex_t*)&buffer[modelHeader->offsetTris];
	
	/*for all triangles in each frame*/
	for(i = 0; i < modelHeader->numTris; ++i)
	{
		ttriIndex[i].meshIndex[0] = bufIndexPtr[i].meshIndex[0];
		ttriIndex[i].meshIndex[1] = bufIndexPtr[i].meshIndex[1];
		ttriIndex[i].meshIndex[2] = bufIndexPtr[i].meshIndex[2];
		ttriIndex[i].stIndex[0]   = bufIndexPtr[i].stIndex[0];
		ttriIndex[i].stIndex[1]   = bufIndexPtr[i].stIndex[1];
		ttriIndex[i].stIndex[2]   = bufIndexPtr[i].stIndex[2];	
	}
	
	
	printf("calculating normals\n"); 
	
	CalculateNormal(*this, filename); 
	
	this->currentFrame = 0; 
	this->nextFrame = 1; 
	this->interpol = 0.0f; 
	this->triIndex.swap(ttriIndex);
	this->st.swap(tst); 
	this->pointList.swap(tpointList); 
printf("md2 model loaded\n"); 
	return true; 
}

void MD2::freeMemory()
{
	std::vector<meshIndex_t> tii; 
	std::vector<texCoord_t> sti; 
	std::vector<vector3_t> pli;
	std::vector<vector3_t> nli; 
	
	this->triIndex.swap(tii); 
	this->st.swap(sti); 
	this->pointList.swap(pli);
	this->normList.swap(nli); 
}
