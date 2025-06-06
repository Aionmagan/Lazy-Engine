#ifndef __LE_SM_VS_H__
#define __LE_SM_VS_H__

#include <string>

static const std::string le_sm_vs = R"(
#version 330 core
layout (location = 0) in vec3 vert; 
layout (location = 1) in vec2 uv;
 
uniform mat4 PVM; 
out vec2 uv0; 

void main()
{
	uv0 = uv; 
	gl_Position = PVM * vec4(vert, 1.0); 
}
)";

static const std::string le_sm_fs = R"(
#version 330 core

uniform sampler2D Texture1;
in vec2 uv0;

void main()
{
	//float f = gl_FragCoord.z * texture(Texture1, uv0).a; 
	//gl_FragDepth = (1.0 - f);
	//gl_FragDepth = gl_FragCoord.z * (1.0-texture(Texture1, uv0).a); 
	
	float fd = gl_FragCoord.z; 
	if (texture(Texture1, uv0).a <= 0.3)
		fd = 1.0; 
	gl_FragDepth = fd; 
}
)";

#endif/*__LE_SM_VS_H__*/
