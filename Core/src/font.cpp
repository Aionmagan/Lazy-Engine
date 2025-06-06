#include "font.h" 
#include <cstdarg>

bool    Font::isInit;
Vertex  Font::quad[4];
int     Font::indeces[6];

void draw_char(Font & f)
{
	
}

Font::Font()
{
	if (!Font::isInit)
	{
		InitGeometry(); 
		Font::isInit = true; 
	}
	texture = NULL;
	setColor(255, 255, 255); 
	
	transform.scale = 0.0015f;
	transform.position.x = -0.04f;
	transform.position.z = 0.11f;
}

Font::~Font()
{

}

void Font::text(std::string strin, ...)
{
	std::string str; 
	
	size_t spos = strin.find('%');
	
	if (spos>0)
	{
		str = strin.substr(0, spos);
		char strout[512];
		size_t npos;// = strin.find(spos, '%');
		va_list args;
		va_start(args, strin);
		
		while(spos != -1)
		{
			switch(strin[++spos])
			{
				case 'd':
					//printf("found d\n");
					sprintf(strout, "%d", va_arg(args, int));
					break;
				case 'f':
					sprintf(strout, "%f", va_arg(args, double));
					break;
				case 's':
					sprintf(strout, "%s", va_arg(args, char*));
					break;
				case 'c':
					sprintf(strout, "%c", va_arg(args, int));
					break;
			}
			
			str += strout;
			npos = strin.find('%', spos);
			str += strin.substr(++spos, npos-1 - spos); 
			spos = npos; 
			//break;
		}
		//for(int i = 0; i < 
		
		va_end(args);  
	}else
	{
		str = strin; 
	}

	stringLength = str.length(); 
	UV tmp={1.0f, 0.0f}; 
	float p = 0.0f;
	//printf("length %d | %d\n", str.length(), stringLength);
	float u1, v1, u2, v2; 
	int ix, iy;
	
	posOffset.clear();
	uvcoords.clear();
	
	for(int i = 0; i < stringLength; ++i)
	{
		ix = str[i]%16*16;//(str[i] % 16) * 16;
    	iy = str[i]/16*16;//(str[i] / 16) * 16;
		u1 = ix / 256.0f; //1
		v1 = iy / 256.0f; //0
		u2 = (ix + 15) / 256.0f; //0
		v2 = (iy + 15) / 256.0f; //1
//printf("uv = %f, %f, %f, %f\n", u1, v1, u2, v2);
//printf("let = %d, %d, %d\n", ix, iy, (int)str[i]);
		posOffset.push_back(p+2.016f);
		
		//tmp.u = 1.0f;
		//tmp.v = 0.0f;
		tmp.u = u1;
		tmp.v = v1;
		uvcoords.push_back(tmp);
		//tmp.u = 0.0f;
		//tmp.v = 1.0f; 
		tmp.u = u2;
		tmp.v = v1;
		uvcoords.push_back(tmp);
		//tmp.u = 0.0f;
		//tmp.v = 0.0f;
		tmp.u = u2;
		tmp.v = v2;
		uvcoords.push_back(tmp);
		//tmp.u = 1.0f;
		//tmp.v = 0.0f;


//second
		tmp.u = u1;
		tmp.v = v2;
		uvcoords.push_back(tmp);
		//tmp.u = 1.0f;
		//tmp.v = 1.0f;
		tmp.u = u1;
		tmp.v = v1;
		uvcoords.push_back(tmp);
		//tmp.u = 0.0f;
		//tmp.v = 1.0f;
		tmp.u = u2;
		tmp.v = v2;
		uvcoords.push_back(tmp);		
		
#if 0
		tmp.u = u1;
		tmp.v = v1;
		uvcoords.push_back(tmp);
		//tmp.u = 1.0f;
		//tmp.v = 1.0f;
		tmp.u = u1;
		tmp.v = v2;
		uvcoords.push_back(tmp);
		//tmp.u = 0.0f;
		//tmp.v = 1.0f;
		tmp.u = u2;
		tmp.v = v2;
		uvcoords.push_back(tmp);
#endif
		p = posOffset[i];
	}
}

void Font::referenceTexture(Texture & t)
{
	texture =& t; 
}

void Font::setColor(int r, int g, int b)
{
	color = (0xff << 24) |  (b << 16) | (g << 8) | r;
}

void Font::InitGeometry()
{
#if 0
	 {-1, -1, 0, // bottom left corner
      -1,  1, 0, // top left corner
       1,  1, 0, // top right corner
       1, -1, 0}; // bottom right corner

	 indices[] = {0,1,2, // first triangle (bottom left - top left - top right)
                     0,2,3}; 
#endif 
                     
	Font::quad[0].x = -1.0f; Font::quad[0].y = -1.0f; Font::quad[0].z = 0.1f;
	Font::quad[1].x =  1.0f; Font::quad[1].y = -1.0f; Font::quad[1].z = 0.1f;
	Font::quad[2].x = -1.0f; Font::quad[2].y =  1.0f; Font::quad[2].z = 0.1f;
	Font::quad[3].x =  1.0f; Font::quad[3].y =  1.0f; Font::quad[3].z = 0.1f;
	
	Font::indeces[0] = 2;
	Font::indeces[1] = 3;  
	Font::indeces[2] = 1;
	Font::indeces[3] = 0;
	Font::indeces[4] = 2;  
	Font::indeces[5] = 1;
}
