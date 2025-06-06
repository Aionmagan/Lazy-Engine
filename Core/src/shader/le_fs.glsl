
struct Material
{
	vec3 ambient; 
	vec3 diffuse; 
	vec3 specular; 
	float shininess; 
}; 

uniform Material material;

struct Light
{
	int  type; //directional / spot / point
	vec3 color; 
	vec3 position; 

	//directional|spot
	vec3 direction;
	
	//point|spot
	float constant; 
	float linear; 
	float quadratic; 
	
	float cutoff; 
	
	int enabled; 
};

#define MAX_LIGHTS 128

uniform int   lightListSize; 
uniform Light lightList[MAX_LIGHTS];

in vec3 LE_Normal0; 
in vec3 LE_WorldPos0;
in vec3 LE_Tangent0; 
in vec3 LE_Bitangent0; 
in vec3 LE_FragPos0; 

uniform sampler2D Texture1; 
uniform sampler2D Texture2; 
uniform sampler2D Texture3; 

