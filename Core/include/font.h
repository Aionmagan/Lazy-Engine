#ifndef __LE_FONT_H__
#define __LE_FONT_H__

#include "texture.h" 
#include "transform.h" 
#include "mesh.h" 
#include <vector>

class Font
{
public: 
	Font();
   ~Font();
   
  	void text(std::string strin, ...);
  	
  	void referenceTexture(Texture & t);
  	void setColor(int r, int g, int b);
  	
  	Transform transform; 
  	Texture* texture; 
  	
  	int color; 
  	int stringLength; 
  	
  	std::vector<float> posOffset; 
	std::vector<UV>    uvcoords; 
  	
  	static bool        isInit;
  	static Vertex      quad[4];
	static int         indeces[6];
	  
private: 
	void InitGeometry(); 
};

#endif/*__LE_FONT_H__*/
