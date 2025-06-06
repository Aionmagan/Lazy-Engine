#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include <string>

class Texture
{
public:  
	int width; 
	int height; 
	bool alpha; 

	unsigned int id;

	Texture(std::string filename, bool mipmap = true);
	Texture(); 
   ~Texture(); 
	
	int load(std::string filename, bool mipmap = true); 
	void freeMemory();
};

#endif/*__TEXTURE_H__*/
