#ifndef __LE_FS_GLSL_H__
#define __LE_FS_GLSL_H__

#include <string>

//idea for later, calla mainimage function with in/out parameters 
//so the user doesn't need to call main in glsl 

static const std::string le_fs = R"(
//INCLUDED LE_FS
out vec4 LE_FragColor; 

struct Material
{
	//sampler2D diffuse; 
	//sampler2D specular;
	//sampler2D rought
	//sampler2D AO; 
	
	vec3 ambient; 
	vec3 diffuse; 
	vec3 specular; 
	float shininess; 
}; 

uniform Material LE_material;

//MOVE THIS TO UNIFORM BUFFER OBJECT
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

#define LE_MAX_LIGHTS 128

uniform int   LE_lightListSize; 
uniform Light LE_lightList[LE_MAX_LIGHTS];
//MOVE THIS TO UNIFORM BUFFER OBJECT

uniform vec3 LE_viewPos;

in vec2 LE_TexCoord;
in vec3 LE_Normal; 
in vec3 LE_Tangent; 
in vec3 LE_Bitangent; 
in vec3 LE_FragPos; 
in vec4 LE_FragPosLightSpace;

//REMOVE THIS WHEN MATERIALS GET TEXTURE SUPPORT
uniform sampler2D Texture1; 
uniform sampler2D Texture2; 
uniform sampler2D Texture3;

uniform sampler2D shadowMap; 
//REMOVE THIS WHEN MATERIALS GET TEXTURE SUPPORT

float ShadowCalc(vec4 fragPosLightSpace)
{
#if 1
	vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
	
	projCoords = projCoords * 0.5 + 0.5;
	//float closestDepth = texture(shadowMap, projCoords.xy).r; 
	float currentDepth = projCoords.z; 
	float bias = 0.0005; 
	
	float shadow = 0.0; 
	vec2 texelSize = 1.0 / textureSize(shadowMap, 0); 
	for(int x = -1; x <= 1; ++x)
	{
		for(int y = -1; y <= 1; ++y)
		{
			float pcfDepth = texture(shadowMap, projCoords.xy + vec2(x, y) * texelSize).r; 
			
			shadow += (currentDepth - bias > pcfDepth) ? 1.0 : 0.0; 
		}
	}
	
	shadow /= 9.0; 
	
	if (projCoords.z > 1.0)
		shadow = 0.0;
		
	return shadow; 
#else
	vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
	
	projCoords = projCoords * 0.5 + 0.5;
	float closestDepth = texture(shadowMap, projCoords.xy).r; 
	float currentDepth = projCoords.z; 
	
	//float bias = max(0.05 * (1.0 - dot(LE_Normal, LE_lightList[0].direction)), 0.005);
	float bias = 0.0005;
	
	//float cosTheta = max(dot(LE_Normal, LE_lightList[0].direction), 0.0);
	//float bias = 0.005*tan(acos(cosTheta));
	//bias = clamp(bias, 0,0.01);
	return (currentDepth - bias > closestDepth) ? 1.0 : 0.0; 
#endif
}

vec3 LE_GetNormalTBN()
{
	vec3 BumpMap = texture(Texture2, LE_TexCoord).xyz; 	
	BumpMap = 2.0f * BumpMap - vec3(1.0f);
	
	vec3 Normal = normalize(LE_Normal); 
	vec3 Tangent = normalize(LE_Tangent); 
	vec3 Bitangent = normalize(LE_Bitangent); 
	
	mat3 TBN = mat3(Tangent, Bitangent, Normal); 
	vec3 newNormal = normalize(TBN * BumpMap); 
	
	return newNormal; 
}

vec3 LE_CalcDirectionalLight(int lightIndex, vec3 color, vec3 normal)
{
	vec3 ambient = LE_lightList[lightIndex].color * color * LE_material.ambient;
		
    float diff = max(dot(normal, -LE_lightList[lightIndex].direction), 0.0);
    vec3 diffuse =  1.0 * (LE_lightList[lightIndex].color * color * (diff * LE_material.diffuse));
    
	vec3 viewDir = normalize(LE_viewPos - LE_FragPos);
    vec3 reflectDir = reflect(-LE_lightList[lightIndex].direction, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), LE_material.shininess);
    vec3 specular = 0.6 * LE_lightList[lightIndex].color * (spec * LE_material.specular);
	
	//float shadow = ShadowCalc(LE_FragPosLightSpace);
    //return (ambient - (shadow) * (diffuse + specular));
    return (ambient + diffuse + specular);
}

vec3 LE_CalcPointLight(int lightIndex, vec3 color, vec3 normal)
{
	 vec3 lightDir = normalize(LE_lightList[lightIndex].position - LE_FragPos);
	float diff = max(dot(normal, lightDir), 0.0);
	float dis = length(LE_lightList[lightIndex].position - LE_FragPos);
	float atten =diff / (LE_lightList[lightIndex].constant + 
						 LE_lightList[lightIndex].linear  * dis + 
						 LE_lightList[lightIndex].quadratic * (dis * dis));

	vec3 ambient = 256.0 * atten * LE_lightList[lightIndex].color * color * LE_material.ambient; 

	vec3 diffuse = ( color * LE_material.diffuse) * atten;
	vec3 viewDir = normalize(LE_viewPos - LE_FragPos); 
	vec3 halfwayDir = normalize(lightDir + viewDir);
	float spec = pow(max(dot(normal, lightDir), 0.0), LE_material.shininess) * atten;
	vec3 specular = 2.6f * LE_lightList[lightIndex].color * (spec * LE_material.specular);

    
    return (ambient + diffuse + specular);
}

float near = 0.1f;
float far = 7.0f; 

float LE_linearDepth(float depth)
{
	return (2.0 * near * far)/(far + near - (depth * 2.0 - 1.0) * (far -near));
}

vec3 LE_CalculateLightList(vec3 texColor)
{
	vec3 outputColor = vec3(0.0);	
	vec3 norm = LE_GetNormalTBN();

	for(int i = 0; i < LE_lightListSize; ++i)
	{
		if (LE_lightList[i].enabled == 0) continue;

		vec3 diffuse;
		switch(LE_lightList[i].type)
		{
			default:
			case 0: //directional
			{
				float shadow = ShadowCalc(LE_FragPosLightSpace);
				diffuse = LE_CalcDirectionalLight(i, texColor, norm) * (1.0-(shadow*0.5));
			}
				break;
			case 1: //point
			diffuse = LE_CalcPointLight(i, texColor, norm); 
				break;
		}
		
		outputColor += diffuse;
	}
	//float shadow = ShadowCalc(LE_FragPosLightSpace);
	return outputColor;//*(1.0-(shadow*0.5)); 
}
//INCLUDED LE_FS)";

#endif/*__LE_FS_GLSL_H*/
