#version 330 core

#includeLE

void main()
{
	LE_FragColor = texture(Texture1, LE_TexCoord); 	
}
