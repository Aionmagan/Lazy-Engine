#ifndef __LAZY_ENGINE_H__
#define __LAZY_ENGINE_H__

#include "aabb.h" 
#include "audio.h"
#include "bSphere.h" 
#include "camera.h" 
#include "colcommon.h" 
#include "gui.h" 
#include "input.h" 
#include "lights.h" 
#include "mathcommon.h" 
#include "object.h" 
#include "particle.h" 
#include "rayCast.h"  
#include "render.h" 
#include "texture.h" 
#include "timer.h"
#include "transform.h"
#include "vector.h"
#include "ply.h" 
#include "mathf.h" 
#include "font.h" 
#include "material.h"
#include "skybox.h"  
#include "particle.h" 

#define leUpdate(){ \
	    gInput.update(); \
		gTime.update(); \
		}

//#include "rayCast.h" 

#endif/*__AVENA_ENGINE_H__*/
