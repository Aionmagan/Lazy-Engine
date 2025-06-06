#ifndef __LE_VS_GLSL_H__
#define __LE_VS_GLSL_H__

#include <string>

static const std::string le_vs = R"(
//INCLUDED LE_VS
layout (location = 0) in vec3 LE_Vert;
layout (location = 1) in vec2 LE_Tex; 
layout (location = 2) in vec3 LE_Norm; 
layout (location = 3) in vec3 LE_Tan; 

out vec2 LE_TexCoord; 
out vec3 LE_Normal; 
out vec3 LE_Tangent; 
out vec3 LE_Bitangent; 
out vec3 LE_FragPos; 
out vec4 LE_FragPosLightSpace;

uniform mat3 LE_TBN;
uniform mat4 LE_PVM; 
uniform mat4 LE_proj; 
uniform mat4 LE_view; 
uniform mat4 LE_model; 
uniform mat4 LE_lightSpace;
uniform mat4 LE_lightPV;

//replace this when i can
void LE_PassTBN()
{
	vec3 norm = normalize(LE_Norm); 
    vec3 tang = normalize(LE_Tan); 
    //maybe compute this on the model side
    vec3 bitang = normalize(cross(norm, tang)); 
    
    LE_Normal = vec3(LE_model * vec4(norm, 0.0)); 
	LE_Tangent = vec3(LE_model * vec4(tang, 0.0)); 
	LE_Bitangent = vec3(LE_model * vec4(bitang, 0.0)); 
}
//INCLUDED LE_FS)";

#endif
