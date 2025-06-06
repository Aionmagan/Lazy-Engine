#include "render.h"
#include "input.h"
#include "timer.h" 
#include "matrix.h"
#include "camera.h" 

#include "mathcommon.h"

#include "shader/le_sm.h" 

#include <iostream>
#include <ctime>

Renderer::Renderer()
{
	//SW = 640; 
	//SH = 480; 
	
	SW = 1280;
	SH = 720;
#if 0	
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK | SDL_INIT_AUDIO);
	
	window = SDL_CreateWindow("Avena Engine", SDL_WINDOWPOS_CENTERED, 
										  SDL_WINDOWPOS_CENTERED, 
										  SW, SH, SDL_WINDOW_OPENGL);
	//SDL_SetWindowFullscreen(window, 1); 
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    
    context = SDL_GL_CreateContext(window);
    
    glViewport(0, 0, SW, SH);
    
    glMatrixMode(GL_PROJECTION);
    //glLoadIdentity();
    Matrix proj; 
	proj.perspectiveProj(45.0f, ((float)SW/(float)SH), 0.1f, 10000.0f); 
#endif
    //glLoadMatrixf(MatrixToArray(proj));
    //glLoadMatrixf(proj.elem);  
    //gluPerspective(45.0f, ((GLfloat)SW/(GLfloat)SH), 0.1f, 10000.0f);
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK | SDL_INIT_AUDIO)!=0)
	{
		std::cout << "SDL_Init Failed" << std::endl; 
	}
	
	srand(time(NULL));
	
	window = SDL_CreateWindow("Lazy Engine", SDL_WINDOWPOS_CENTERED, 
								     		 SDL_WINDOWPOS_CENTERED, 
								     SW, SH, SDL_WINDOW_OPENGL);
	//SDL_SetWindowFullscreen(window, 1); 
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
       
    context = SDL_GL_CreateContext(window);
    SDL_GL_MakeCurrent(window, context);
    
    proj.perspectiveProj(45.0f, ((float)SW/(float)SH), 0.1f, 1000.0f);
    //proj.orthoProj(-10.0f, 10.0f, -10.0f, 10.0f, 1.0f, 50.0f);
    //proj = glm::perspective(glm::radians(45.0f), (float)SW/(float)SH, 0.1f, 1000.0f);
    
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
    	std::cout << "GLEW failed" << std::endl;
    }
    glViewport(0, 0, SW, SH);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glEnable(GL_DEPTH_TEST);
    
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  
    
    lightListIndex = 0;
    skyboxp = NULL; 
    
    //glEnable(GL_CULL_FACE);
	//glCullFace(GL_FRONT);
    
    CreateShadowFBO();
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}
 
Renderer::~Renderer()
{
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void Renderer::setSkybox(Skybox & sb)
{
	skyboxp =& sb; 
}

void Renderer::removeSkybox()
{
	skyboxp = NULL; 
}

int Renderer::sendLightToList(Light & l)
{
	lightList.push_back(&l); 
	return lightListIndex++; 
}   

void Renderer::removeLightFromList(int lli)
{
	lightList.erase(lightList.begin() + lli); 
	lightListIndex--;
}
   
void Renderer::setProj(float aspect, float near, float far)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
}

void Renderer::clearDepth()
{
	glClear(GL_DEPTH_BUFFER_BIT);
}

void Renderer::setBGColor(int r, int g, int b)
{
	glClearColor(r/255.0f, g/255.0f, b/255.0f, 1.0f);
}

void Renderer::CreateShadowFBO()
{
	glGenFramebuffers(1, &depthMapFBO); 
	
	DW = 4096; 
	DH = 4096; 
	
	glGenTextures(1, &depthMap); 
	glBindTexture(GL_TEXTURE_2D, depthMap); 
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, 
				 DW, DH, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	
	float clampColor[] = {1.0f,1.0f,1.0f,1.0f};
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, clampColor);
	
	glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, 
						   GL_TEXTURE_2D, depthMap, 0); 
						   
	glDrawBuffer(GL_NONE); 
	glReadBuffer(GL_NONE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0); 						   
	shadowMapShader.loadProgram(le_sm_vs.c_str(), le_sm_fs.c_str()); 
	
	ortho.orthoProj(-15.0f, 15.0f, -15.0f, 15.0f, 1.0f, 100.0f); 
	//ortho.perspectiveProj(45.0f, ((float)SW/(float)SH), 0.1f, 50.0f);
}

void Renderer::draw(GameObject & obj)
{	
	//unbind all textures and only ever use 8 texture limit for now
	for(int i = 0; i < 8; ++i)
	{
		glActiveTexture(GL_TEXTURE0 + i); 
		glBindTexture(GL_TEXTURE_2D, 0);
	}	
	
	//hacky as shit code, remove later
	obj.shaders.setInt("Texture1", 0);
	obj.shaders.setInt("Texture2", 1);
	obj.shaders.setInt("shadowMap", 6); 
	//hacky as shit code, remove later
	
	glActiveTexture(GL_TEXTURE6); 
	glBindTexture(GL_TEXTURE_2D, depthMap); 
	
	size_t len = obj.texture.size();
	for(int i = 0; i < len; ++i)
	{
		glActiveTexture(GL_TEXTURE0 + i); 
		//printf("id = %d\n", obj.texture[i]->id);
		glBindTexture(GL_TEXTURE_2D, obj.texture[i]->id);
	}

		//printf("got called\n");
	glBindVertexArray(obj.model->m_VAO);  
		glDrawArrays(GL_TRIANGLES, 0, obj.model->data.size());
}

void Renderer::draw(Particle & particle)
{
	//unbind all textures and only ever use 8 texture limit for now
	for(int i = 0; i < 8; ++i)
	{
		glActiveTexture(GL_TEXTURE0 + i); 
		glBindTexture(GL_TEXTURE_2D, 0);
	}	
	
	//hacky as shit code, remove later
	particle.shaders.setInt("Texture1", 0);
	particle.shaders.setInt("Texture2", 1);
	//hacky as shit code, remove later

	glActiveTexture(GL_TEXTURE0); 
	//printf("id = %d\n", obj.texture[i]->id);
	glBindTexture(GL_TEXTURE_2D, particle.texID);

		//printf("got called\n");
	glBindVertexArray(particle.model->m_VAO);  
		glDrawArrays(GL_TRIANGLES, 0, particle.model->data.size());
}

void Renderer::queue(GameObject & obj, MatrixPath mp)
{
	if (obj.model == NULL && obj.md2 == NULL && obj.ply == NULL){ return; }
	
	aeQueue q; 
	q.mesh = MeshPath::LE_GO; 
	q.vo = (void*)&obj; 
	q.o = &obj; 
	q.mat = mp; 
	
	renderList.push_back(q); 
}

//maybe move this somewhere else 
void Renderer::queue(ParticleEmitter & p)
{
	Matrix4 useless4;
	Matrix3 useless3;
	MatrixPath mp = MatrixPath::LE_MAT_3D;
	calMat(useless4, useless4, useless4, useless3, 
		   p.transform, mp);
		   
	p.update();
}

void Renderer::queue(Particle & p, MatrixPath mp)
{
	aeQueue q; 
	q.mesh = MeshPath::LE_PARTICLE;
	q.vo = (void*)&p; 
	q.mat = mp; 
	
	renderList.push_back(q); 
}

void Renderer::queue(GUI & gui, MatrixPath mp)
{
	if (gui.model == NULL){ return; }
	
	aeQueue q; 
	q.mesh = MeshPath::LE_GUI; 
	//q.o =& obj; 
	q.mat = mp; 
	
	renderList.push_back(q);
}

void Renderer::queue(Font & font, MatrixPath mp)
{	
	aeQueue q; 
	q.mesh = MeshPath::LE_FONT; 
	//q.o =& obj; 
	q.vo = (void*)&font; 
	q.mat = mp; 
	
	renderList.push_back(q);
}

void Renderer::queue(CommandPath cp)
{
	aeQueue q; 
	q.mesh = MeshPath::LE_COMMAND;
	q.vo = NULL; 
	q.com = cp; 
	
	renderList.push_back(q); 
} 

void Renderer::calLightMat(Matrix4 & PVMOut, 
						   Matrix4 & viewOut, 
						   Matrix4 & modelOut,
						   Transform & transform, 
						   Transform & lightTran, 
						   MatrixPath & mp)
{
	static Matrix4 t, s, r, lt, lr, lightView; 

	t.translate(transform.position.x, transform.position.y, transform.position.z); 
	s.scale(transform.scale.x, transform.scale.y, transform.scale.z); 
	r.quaternionToMatrix(transform.rotation);

	lt.translate(lightTran.position.x-Camera::viewPos.x, lightTran.position.y, lightTran.position.z-Camera::viewPos.z);
	lr.quaternionToMatrix(lightTran.rotation);
	lightSpaceMatrix = lr * lt; 
	
	switch(mp)
	{
		case MatrixPath::LE_MAT_3D_SRT:
		{
			if (transform.parent) 
			{
				transform.selfMatrix = s * r * t;
				transform.selfMatrix = transform.selfMatrix * transform.parent->selfMatrix;
			}
			else
			{
				transform.selfMatrix = s * r * t;
			}
			//transform.selfMatrix.transpose();
			
			PVMOut = ortho * lightSpaceMatrix * transform.selfMatrix;
			viewOut = lightSpaceMatrix; 
			modelOut = transform.selfMatrix;   
		}
			break;
		case MatrixPath::LE_MAT_3D_STR:
		{
			if (transform.parent) 
			{
				transform.selfMatrix = s * t * r;
				transform.selfMatrix = transform.selfMatrix * transform.parent->selfMatrix;
			}
			else
			{
				transform.selfMatrix = s * t * r;
			}
			
			PVMOut = ortho * lightSpaceMatrix * transform.selfMatrix;
			viewOut = lightSpaceMatrix; 
			modelOut = transform.selfMatrix;   
		}
			break;
		case MatrixPath::LE_MAT_3D_RTS:
		{
			if (transform.parent) 
			{
				transform.selfMatrix = r * t * s;
				transform.selfMatrix = transform.selfMatrix * transform.parent->selfMatrix;
			}
			else
			{
				transform.selfMatrix = r * t * s;
			}
			
			PVMOut = ortho * lightSpaceMatrix * transform.selfMatrix;
			viewOut = lightSpaceMatrix; 
			modelOut = transform.selfMatrix;   
		}		
			break;
		case MatrixPath::LE_MAT_3D: 
		case MatrixPath::LE_MAT_3D_TRS:
		{
			if (transform.parent) 
			{
				transform.selfMatrix = t * r * s;
				transform.selfMatrix = transform.selfMatrix * transform.parent->selfMatrix;
			}
			else
			{
				transform.selfMatrix = t * r * s;
			}
			
			PVMOut = ortho * lightSpaceMatrix * transform.selfMatrix;
			viewOut = lightSpaceMatrix; 
			modelOut = transform.selfMatrix;   
		}		
			break;

		default:
			//printf("MatrixPath not set\n");
			break;
	}	
	
	lpvm = ortho * lightSpaceMatrix;
}

void Renderer::renderDepthMap()
{
	int rLen = (int)renderList.size(); 
	int i; 
	bool toRender = false; 
	GLuint tvao, modelsize, texID; 
	//glm::mat4 PVM, view, model;
	Matrix4 PVM, view, model;
	Matrix3 TBN; 
	GameObject *go;
	Particle * particlep; 


	glViewport(0, 0, DW, DH);
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_FRONT); 
	glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO); 
	glClear(GL_DEPTH_BUFFER_BIT);
	
	shadowMapShader.use(); 
	for(i = 0; i < rLen; ++i)
	{		
		switch(renderList[i].mesh)
		{
			case MeshPath::LE_GO:
			{
				go = (GameObject*)renderList[i].vo;
				calLightMat(PVM, view, model, go->transform, lightList[0]->transform, renderList[i].mat);
				shadowMapShader.setMat4("PVM", GL_FALSE, PVM); 
				//setupShaders(go->shaders, go->material, PVM, view, model, TBN); 		
				//draw(*go);  
				tvao = go->model->m_VAO;
				modelsize = go->model->data.size();
				texID = go->texture[0]->id; 
				toRender = true; 
			}
				break;
			case MeshPath::LE_PARTICLE:
			{
				//glDepthMask(GL_FALSE);
				particlep = (Particle*)renderList[i].vo;
				calLightMat(PVM, view, model, particlep->transform, lightList[0]->transform, renderList[i].mat);
				shadowMapShader.setMat4("PVM", GL_FALSE, PVM);
				//setupShaders(particlep->shaders, *particlep->materialp, PVM, view, model, TBN); 		
				//draw(*particlep);
				//glDepthMask(GL_TRUE);
				tvao = particlep->model->m_VAO;
				modelsize = particlep->model->data.size();				
				texID = particlep->texID;
				
				toRender = true; 
			}
				break;				
		}
		
		if (toRender)
		{
			//unbind all textures and only ever use 8 texture limit for now
			for(int i = 0; i < 8; ++i)
			{
				glActiveTexture(GL_TEXTURE0 + i); 
				glBindTexture(GL_TEXTURE_2D, 0);
			}	
#if 0			
			//hacky as shit code, remove later
			obj.shaders.setInt("Texture1", 0);
			obj.shaders.setInt("Texture2", 1);
			//hacky as shit code, remove later
			
			size_t len = obj.texture.size();
			for(int i = 0; i < len; ++i)
			{
				glActiveTexture(GL_TEXTURE0 + i); 
				//printf("id = %d\n", obj.texture[i]->id);
				glBindTexture(GL_TEXTURE_2D, obj.texture[i]->id);
			}
#endif
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, texID);
				//printf("got called\n");
			glBindVertexArray(tvao);  
				glDrawArrays(GL_TRIANGLES, 0, modelsize);
				//printf("model rendererd\n");
		}
		
		toRender = false; 
	}
	
	glBindFramebuffer(GL_FRAMEBUFFER, 0); 
	//glCullFace(GL_BACK);
	//glDisable(GL_CULL_FACE);
}

void Renderer::setupShaders(Shader & shaders, Material & material,
    				  		Matrix4 & PVM, Matrix4 & view, 
    				  		Matrix4 & model, Matrix3 & TBN)
{
	shaders.use();
	glUniformMatrix4fv(shaders.PVMLoc, 1, GL_FALSE, PVM.elem);
	glUniformMatrix4fv(shaders.projLoc, 1, GL_FALSE, proj.elem);
	glUniformMatrix4fv(shaders.viewLoc, 1, GL_FALSE, view.elem);
	glUniformMatrix4fv(shaders.modelLoc, 1, GL_FALSE, model.elem);
	glUniformMatrix3fv(shaders.TBNLoc, 1, GL_FALSE, TBN.elem);

	glUniformMatrix4fv(glGetUniformLocation(shaders.ID, "LE_lightSpace"), 1, GL_FALSE, lpvm.elem);
	
	//glUniformMatrix4fv(glGetUniformLocation(shaders.ID, "LE_lightPV"), 1, GL_FALSE, lpvm.elem);	

	glUniform3fv(shaders.MatAmbLoc, 1, material.ambient.elem);
	glUniform3fv(shaders.MatDifLoc, 1, material.diffuse.elem);
	glUniform3fv(shaders.MatSpeLoc, 1, material.specular.elem);
	glUniform1f(shaders.MatShiLoc, material.shininess);

	glUniform3fv(shaders.lViewPosLoc, 1, Camera::viewPos.elem);

	glUniform1i(shaders.lSizeLoc, (int)lightListIndex); 

//UNIFORM BUFFER OBJECT THIS
	for(int i = 0; i < lightList.size(); ++i)
	{	                                   
		glUniform1i(shaders.lTypeLoc[i], (int)lightList[i]->lightType);	
		glUniform3fv(shaders.lColorLoc[i], 1, lightList[i]->color.elem);										   
		glUniform3fv(shaders.lPosLoc[i], 1, lightList[i]->transform.position.elem);
		
		//tdir = lightList[i]->transform.forward();	
			   
		glUniform1f(shaders.lConstLoc[i], lightList[i]->constant);
		glUniform1f(shaders.lLinearLoc[i], lightList[i]->linear);
		glUniform1f(shaders.lQuadLoc[i], lightList[i]->quadratic);
		glUniform1f(shaders.lCutoffLoc[i], lightList[i]->cutoff);
		
		//glUniform3f(go->shaders.lDirLoc[i], tdir.x, tdir.y, tdir.z);
		glUniform3fv(shaders.lDirLoc[i], 1, lightList[i]->transform.forward().elem);
		
		glUniform1i(shaders.lEnaLoc[i], (int)lightList[i]->isEnabled);
	}
//UNIFORM BUFFER OBJECT THIS
	
}

void Renderer::calMat(Matrix4 & PVMOut, 
					  Matrix4 & viewOut, 
					  Matrix4 & modelOut,
					  Matrix3 & TBNOut, Transform & transform, MatrixPath & mp)
{
	static Matrix4 t, s, r; 
	//glm::mat4 t(1.0f), s(1.0f), r(1.0f); 
	//t = glm::translate(t, glm::vec3(transform.position.x, transform.position.y, transform.position.z)); 
	//s = glm::scale(s, glm::vec3(transform.scale.x, transform.scale.y, transform.scale.z)); 
	t.translate(transform.position.x, transform.position.y, transform.position.z); 
	s.scale(transform.scale.x, transform.scale.y, transform.scale.z); 
	r.quaternionToMatrix(transform.rotation);
	//r = glm::mat4_cast(glm::quat(transform.rotation.w,
	//							 transform.rotation.x, 
	//		                     transform.rotation.y,
	//		                     transform.rotation.z));
	//collect the rotation only
	//Matrix3 tbn(Camera::view); 
	Matrix3 tbn(Transpose(Inverse(Camera::view)));
	TBNOut = tbn; 
	//TBNOut = Transpose(Inverse(tbn));                     
	//TBNOut = glm::transpose(glm::inverse(Camera::view));		                    
			
	switch(mp)
	{
		case MatrixPath::LE_MAT_3D_SRT:
		{
			if (transform.parent) 
			{
				transform.selfMatrix = s * r * t;
				transform.selfMatrix = transform.selfMatrix * transform.parent->selfMatrix;
			}
			else
			{
				transform.selfMatrix = s * r * t;
			}
			//transform.selfMatrix.transpose();
			
			PVMOut = proj * Camera::view * transform.selfMatrix;
			viewOut = Camera::view; 
			modelOut = transform.selfMatrix;   
		}
			break;
		case MatrixPath::LE_MAT_3D_STR:
		{
			if (transform.parent) 
			{
				transform.selfMatrix = s * t * r;
				transform.selfMatrix = transform.selfMatrix * transform.parent->selfMatrix;
			}
			else
			{
				transform.selfMatrix = s * t * r;
			}
			
			PVMOut = proj * Camera::view * transform.selfMatrix;
			viewOut = Camera::view; 
			modelOut = transform.selfMatrix;   
		}
			break;
		case MatrixPath::LE_MAT_3D_RTS:
		{
			if (transform.parent) 
			{
				transform.selfMatrix = r * t * s;
				transform.selfMatrix = transform.selfMatrix * transform.parent->selfMatrix;
			}
			else
			{
				transform.selfMatrix = r * t * s;
			}
			
			PVMOut = proj * Camera::view * transform.selfMatrix;
			viewOut = Camera::view; 
			modelOut = transform.selfMatrix;   
		}		
			break;
		case MatrixPath::LE_MAT_3D: 
		case MatrixPath::LE_MAT_3D_TRS:
		{
			if (transform.parent) 
			{
				transform.selfMatrix = t * r * s;
				transform.selfMatrix = transform.selfMatrix * transform.parent->selfMatrix;
			}
			else
			{
				transform.selfMatrix = t * r * s;
			}
			
			PVMOut = proj * Camera::view * transform.selfMatrix;
			viewOut = Camera::view; 
			modelOut = transform.selfMatrix;   
		}		
			break;
		case MatrixPath::LE_MAT_UI:
		{
			if (transform.parent) 
			{
				transform.selfMatrix = s * r * t;
				transform.selfMatrix = transform.selfMatrix * transform.parent->selfMatrix;
			}
			else
			{
				transform.selfMatrix = s * r * t;
			}
			
			//result = transform.selfMatrix;
			PVMOut = proj * transform.selfMatrix;
			viewOut.identity(); 
			modelOut = transform.selfMatrix;   
		}
			break;
		case MatrixPath::LE_MAT_BILLBOARD:
		{
			if (transform.parent) 
			{
				transform.selfMatrix = t * s;
				transform.selfMatrix = transform.selfMatrix * transform.parent->selfMatrix;
			}
			else
			{
				transform.selfMatrix = t * s;
			}		

		   	PVMOut = proj * Camera::view * transform.selfMatrix * Camera::BB; 
		   	viewOut = Camera::view; 
		   	modelOut = transform.selfMatrix; 
		}
			break;		
		default:
			printf("MatrixPath not set\n");
			break;
	}
	
	//out = result; 
}

void Renderer::drawQueue()
{
	if (lightList.size()>0)
		renderDepthMap();
	//int oLen = (int)obliList.size(); 
	//int tLen = (int)tranList.size(); 
	int rLen = (int)renderList.size(); 
	int i; 
	
	//glm::mat4 PVM, view, model;
	Matrix4 PVM, view, model;
	//glm::mat3 TBN;  
	Matrix3 TBN; 
	
	Vector3 tdir; 
	
	GameObject *go;
	Particle * particlep; 
	GUI *gui; 
	Font *font; 
	
	/*
	uniform mat4 PVM; //projection * view * model
	uniform mat4 view; 
	uniform mat4 model;
	uniform int  lightListSize; 
	uniform vec3 lightList[]; //light array list
	*/
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glViewport(0, 0, SW, SH); 
	
	if(skyboxp != NULL)
	{
		MatrixPath mp = MatrixPath::LE_MAT_3D;
		calMat(PVM, view, model, TBN, skyboxp->go.transform, mp);
		skyboxp->go.shaders.use();
		glUniformMatrix4fv(skyboxp->go.shaders.PVMLoc, 1, GL_FALSE, PVM.elem);
		glUniformMatrix4fv(skyboxp->go.shaders.projLoc, 1, GL_FALSE, proj.elem);
		glUniformMatrix4fv(skyboxp->go.shaders.viewLoc, 1, GL_FALSE, Camera::viewRot.elem);
		glUniformMatrix4fv(skyboxp->go.shaders.modelLoc, 1, GL_FALSE, model.elem);
		
		glUniform3fv(skyboxp->go.shaders.MatAmbLoc, 1, skyboxp->go.material.ambient.elem);
		draw(skyboxp->go);
		glClear(GL_DEPTH_BUFFER_BIT); 
	}
	
	for(i = 0; i < rLen; ++i)
	{		
		switch(renderList[i].mesh)
		{
			case MeshPath::LE_GO:
			{
				go = (GameObject*)renderList[i].vo;
				
				if (go->isActive == false) break;
				calMat(PVM, view, model, TBN, go->transform, renderList[i].mat);
				setupShaders(go->shaders, go->material, PVM, view, model, TBN); 		
				draw(*go);  
			}
				break;
			case MeshPath::LE_PARTICLE:
			{
				//glDisable(GL_BLEND);
				//glBlendFunc(GL_SRC_ALPHA, GL_ONE); 
				//glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE);
				glDepthMask(GL_FALSE);
				particlep = (Particle*)renderList[i].vo;
				//particlep->worldPos = view * model * particlep->transform.position; 
				calMat(PVM, view, model, TBN, particlep->transform, renderList[i].mat);
				setupShaders(particlep->shaders, *particlep->materialp, PVM, view, model, TBN); 		
				draw(*particlep);
				glDepthMask(GL_TRUE);
				//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);   
				//glEnable(GL_BLEND);
			}
				break;
			case MeshPath::LE_GUI:
				break;
			case MeshPath::LE_FONT:
			{
				font = (Font*)renderList[i].vo;
				//calMat(PVM, view, model, font->transform, obliList[i].mat); 
				//glLoadMatrixf(result.elem);
				//drawFont(*font);   
			}			
				break;
			case MeshPath::LE_COMMAND:
			{
				switch(renderList[i].com)
				{
					case CommandPath::LE_CLEARDEPTH:
						glClear(GL_DEPTH_BUFFER_BIT); 
						break;
					case CommandPath::LE_CLEARCOLOR:
						glClear(GL_COLOR_BUFFER_BIT); 
						break;
					case CommandPath::LE_CLEARALL:
						glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
						break;
				}
			}
				break;				
		}
		
		//render obliList here
	}

	SDL_GL_SwapWindow(window); 
	
	//in gcc 7.0.1 you can clear without checking for empty 
	//but idk which versions of gcc this source will compile in 
	//so old fasion way it is
	//if (!obliList.empty()) { obliList.clear(); }
	//if (!tranList.empty()) { tranList.clear(); }
	//if (!renderList.empty()) { renderList.clear(); }
}

void Renderer::removeQueue()
{
	if (!renderList.empty()) { renderList.clear(); }
}

Renderer gRenderer; 

