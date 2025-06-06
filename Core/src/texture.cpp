#include "texture.h"

#include <cstdio>
#include <cstdlib>
//#include <malloc.h>
//#include <png.h>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/gl.h>
//#include <GL/glut.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define CLEANUP(x) { ret = (x); goto cleanup; }

#if defined(__WIN32__)
	typedef char uint8_t;
#endif

Texture::Texture(std::string filename, bool mipmap)
{
	width = 0; 
	height = 0; 
	alpha = false; 
	id = 0; 
	load(filename, mipmap); 
}
Texture::Texture()
{
	width = 0; 
	height = 0; 
	alpha = false; 
	id = 0;
}
 
Texture::~Texture()
{
	freeMemory();
}

int Texture::load(std::string filename, bool mipmap)
{
	int nrc; 
	int W, H; 
	GLuint ID; 
	stbi_set_flip_vertically_on_load(1);
	unsigned char* data = stbi_load(filename.c_str(), &W, &H, &nrc, 0);
	if (data != NULL)
	{
		int textureFormate = (nrc > 3) ? GL_RGBA : GL_RGB; 
		glGenTextures(1, &ID); 
		glBindTexture(GL_TEXTURE_2D, ID); 
			glTexImage2D(GL_TEXTURE_2D, 0, textureFormate, W, H, 0, textureFormate, GL_UNSIGNED_BYTE, data);
			//glGenerateMipmap(GL_TEXTURE_2D); 
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		
		if (mipmap)
		{
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
			//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_LINEAR);
			//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_LOD,0.862f);
			//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_LOD,0.99f);
			//glTexParameterf(GL_TEXTURE_2D ,GL_TEXTURE_LOD_BIAS,-0.7f);
			
			glGenerateMipmap(GL_TEXTURE_2D);
		}else
		{
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);		
		}
		
		//printf("data before free %s\n", data);
		stbi_image_free(data); 
		printf("loaded %s\n", filename.c_str());
		//printf("data after free %s\n", data);
		id = ID;
		width = W;
		height = H;
		alpha = true;
		
		return 1;
	}else 
	{
		//std::cout << "image loading failed" <<std::endl;
		printf("can't open %s\n", filename.c_str()); 
		return 0;
	}
}

void Texture::freeMemory()
{
	glDeleteTextures(1, &id);
}
