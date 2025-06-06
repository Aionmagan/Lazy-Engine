#version 330 core

#includeLE

void main()
{
	LE_FragColor = texture(Texture1, LE_TexCoord) * vec4(LE_material.ambient, 1.0);  
}
