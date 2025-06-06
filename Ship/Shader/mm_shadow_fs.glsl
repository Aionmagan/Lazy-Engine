#version 330 core

#includeLE //always include this after all variables

void main()
{
	vec4 texColor = texture(Texture1, LE_TexCoord);
	
	if(texColor.a < 0.5f) {discard;}
	
	LE_FragColor = texColor * vec4(vec3(0.3), 1.0);
}
