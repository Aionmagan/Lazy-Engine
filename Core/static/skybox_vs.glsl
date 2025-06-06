#version 330 core

#includeLE //always include this after all variables

void main()
{
    LE_TexCoord = LE_Tex; 

    //LE_FragPos = (LE_model * vec4(LE_Vert, 1.0f)).xyz;
    //LE_PassTBN();
    
    gl_Position = LE_proj * LE_view * vec4(LE_Vert, 1.0);//proj * worldPos;
}
