layout (location = 0) in vec3 LE_Vert;
layout (location = 1) in vec2 LE_Tex; 
layout (location = 2) in vec3 LE_Norm; 
layout (location = 3) in vec3 LE_Tan; 

in vec3 LE_Normal0; 
in vec3 LE_WorldPos0;
in vec3 LE_Tangent0; 
in vec3 LE_Bitangent0; 
in vec3 LE_FragPos0; 

uniform mat3 LE_TBN; //transpose(inverse(LocalToWorld))
uniform mat4 LE_PVM; 
uniform mat4 LE_proj; 
uniform mat4 LE_view; 
uniform mat4 LE_model; 

void LE_PassTBN()
{
	vec3 norm = normalize(LE_Norm); 
    vec3 tang = normalize(LE_Tan); 
    vec3 bitang = normalize(cross(norm, tang)); 
    
    LE_Normal0 = vec3(LE_model * vec4(norm, 0.0)); 
	LE_Tangent0 = vec3(LE_model * vec4(tang, 0.0)); 
	LE_Bitangent0 = vec3(LE_model * vec4(bitang, 0.0)); 
}
