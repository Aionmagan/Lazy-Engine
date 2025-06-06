#ifndef __QUAD_DEPTH_H__
#define __QUAD_DEPTH_H__

#include <LazyEngine.h>

class QDepth
{
public: 
	QDepth();
   ~QDepth(); 
   
   void update();
   void queue(); 
   
   Model quadMod; 
   Texture quadTex; 
   GameObject quadObj; 
};

#endif
