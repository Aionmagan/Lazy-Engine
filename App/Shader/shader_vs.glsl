#version 330 core

#includeLE

void main()
{
    LE_TexCoord = LE_Tex; 

    LE_FragPos = (LE_model * vec4(LE_Vert, 1.0f)).xyz;
    LE_PassTBN();
    
    //LE_FragPosLightSpace = LE_lightSpace * vec4(LE_Vert, 1.0);
    LE_FragPosLightSpace = LE_lightSpace * vec4(LE_FragPos, 1.0);
    gl_Position = LE_PVM * vec4(LE_Vert, 1.0);//proj * worldPos;

}
