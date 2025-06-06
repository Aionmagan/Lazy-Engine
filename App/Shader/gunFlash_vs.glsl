#version 330 core

#includeLE

void main()
{
    LE_TexCoord = LE_Tex; 

    LE_FragPos = (LE_model * vec4(LE_Vert, 1.0)).xyz;
    LE_PassTBN();
    
    gl_Position = LE_PVM * vec4(LE_Vert, 1.0);//proj * worldPos;
}
