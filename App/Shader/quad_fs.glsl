#version 330 core

#includeLE

void main()
{
	float t = texture(Texture1, LE_TexCoord).r; 
	LE_FragColor = vec4(vec3(t), 1.0);// texture(Texture1, LE_TexCoord); 	
}
