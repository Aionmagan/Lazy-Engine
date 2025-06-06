#version 330 core
#includeLE

void main()
{
	vec4 texColor = texture(Texture1, LE_TexCoord);
	
	if(texColor.a < 0.5f) {discard;}
	
	vec3 colorResult = LE_CalculateLightList(texColor.xyz); 
	
	vec4 d = (vec4(colorResult, 1.0f) * texColor);

	float depth = LE_linearDepth(gl_FragCoord.z)/far;
#if 0	
	if (gl_FragCoord.x < 1280/2)
	{
	LE_FragColor = vec4(vec3(depth), 1.0); 
	}else{
	LE_FragColor = vec4(colorResult, 1.0) * texColor; 
	}
#else	
	LE_FragColor = vec4(colorResult, 1.0); 
#endif
}
