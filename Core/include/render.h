#ifndef __RENDER_H__
#define __RENDER_H__

#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL2/SDL.h>
#include <math.h>

#include "object.h"
#include "vector.h" 
#include "font.h" 
#include "lights.h" 
#include "skybox.h" 
#include "shaderClass.h" 

#include "gui.h" 

#include <vector>

//RENAME EVERYTHING TO LE_
enum MatrixPath
{
	LE_MAT_3D,
	LE_MAT_3D_SRT,
	LE_MAT_3D_STR,
	LE_MAT_3D_RTS,
	LE_MAT_3D_TRS,
	LE_MAT_UI,
	LE_MAT_BILLBOARD,
};


//maybe gone too
enum MeshPath
{
	LE_GO,
	LE_PARTICLE,
	LE_FONT,
	LE_GUI, 
	LE_COMMAND
};

enum CommandPath
{
	LE_CLEARDEPTH, 
	LE_CLEARCOLOR, 
	LE_CLEARALL
};

struct aeQueue
{
	MeshPath mesh;
	void* vo; 
	GameObject* o;
	//ListPath list; 
	MatrixPath mat;
	CommandPath com;  
};

class Renderer
{
public:
	//std::vector<aeQueue> obliList; 
	//std::vector<aeQueue> tranList; 
	
	//remove upper list's they are dreamcast only stuff outdated
	std::vector<aeQueue> renderList; 
	std::vector<Light* > lightList;
	Skybox* skyboxp; 
	
	int DW, DH;
	GLuint depthMap; 
	GLuint depthMapFBO; 
	Shader shadowMapShader; 
	void CreateShadowFBO();
	Matrix4 ortho; 
	Matrix4 lightSpaceMatrix;
	Matrix4 lpvm;  
	//later add proper render function calls
	void calLightMat(Matrix4 & PVMOut, 
				     Matrix4 & viewOut, 
				     Matrix4 & modelOut,
				     Transform & transform, 
				     Transform & lightTran, 
				     MatrixPath & mp); 
	void renderDepthMap(); 
	
	int lightListIndex; 
	
    SDL_Window* window; 
    SDL_Surface* wsurface; 
    SDL_Surface* grid; 
    SDL_GLContext context; 
	
    int SW, SH; 
    //Vector light; 
    //Vector lightpos; 
    //glm::mat4 proj;
    Matrix4 proj;
    
    void drawObj(GameObject & obj);
    void drawPly(GameObject & obj); 

    void drawFont(Font & font);
    void draw(GameObject & obj);
    void draw(Particle & particle); 
    
    void setupShaders(Shader & shaders, 
    				  Material & material,
    				  Matrix4 & PVMOut, 
					  Matrix4 & viewOut, 
					  Matrix4 & modelOut,
					  Matrix3 & TBNOut);
    //void calMat(glm::mat4 & PVMOut, 
    //			glm::mat4 & viewOut, 
    //			glm::mat4 & modelOut,
    //			glm::mat3 & tbnOut, Transform & transform, MatrixPath & mp);
    void calMat(Matrix4 & PVMOut, 
    			Matrix4 & viewOut, 
    			Matrix4 & modelOut,
    			Matrix3 & TBNOut, Transform & transform, MatrixPath & mp);
public: 
    Renderer(); 
   ~Renderer();
   	
   	/*internal use*/
   	void setSkybox(Skybox & sb);
   	void removeSkybox(); 
   	int sendLightToList(Light & l);
   	void removeLightFromList(int lli); 
   	/*internal use*/
   	
    void setProj(float aspect, float near, float far); 

	void clearDepth(); 
    void setBGColor(int r, int g, int b); 
    
    void queue(GameObject & obj,
    		   MatrixPath mp = MatrixPath::LE_MAT_3D);
    
    void queue(ParticleEmitter & p); 		   
	void queue(Particle & p,
    		   MatrixPath mp = MatrixPath::LE_MAT_BILLBOARD);    		   
    		   
    void queue(GUI & gui,
    		   MatrixPath mp = MatrixPath::LE_MAT_UI);
    		   
    void queue(Font & font, 
    		   MatrixPath mp = MatrixPath::LE_MAT_UI);
    		   
    void queue(CommandPath cp); 
    
    void drawQueue(); 
    void removeQueue();
};

/*
 *==================================
 * Global instance of Renderer
 *==================================
 */
 
extern Renderer gRenderer; 

#endif/*__RENDER_H__*/
