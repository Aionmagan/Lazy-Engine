#version 330 core

uniform float gTime; 

#includeLE //always include this after all variables

void main()
{
    LE_TexCoord = LE_Tex; 

    LE_FragPos = (LE_model * vec4(LE_Vert, 1.0f)).xyz;
    LE_PassTBN();
    //vec4 t = LE_PVM * vec4(LE_Vert, 1.0);//proj * worldPos;
    vec3 vert = LE_Vert;
    vert.x = ((vert.y*vert.y*0.05) * sin(gTime*0.4f)) + vert.x; 
    //vert.z = (vert.z * cos(gTime*0.9f*vert.y)) + vert.z;
   	LE_FragPosLightSpace = LE_lightSpace * vec4(LE_FragPos, 1.0);
   	
    gl_Position = LE_PVM * vec4(vert, 1.0);
}
