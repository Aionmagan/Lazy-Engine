#version 330 core

#includeLE //always include this after all variables

void main()
{
	vec4 texColor = texture(Texture1, LE_TexCoord);

	if(texColor.a < 0.5f) {discard;}

	vec3 colorResult = LE_CalculateLightList(texColor.xyz); 

	vec4 d = (vec4(colorResult, 1.0f) * texColor);

	float depth = LE_linearDepth(gl_FragCoord.z)/far;
	//LE_FragColor = mix(d, vec4(.65, .65, .70, 1.0), depth+0.2);
	
	//LE_FragColor = vec4(vec3(depth), 1.0);
	LE_FragColor = vec4(colorResult, 1.0) * texColor; 
	//FragColor = d * (1.0f - depth) + vec4(depth * vec3(.85, .85, .90), 1.0);
	//FragColor = mix(vec4(vec3(linearDepth(gl_FragCoord.z)/far), 1.0f), d, 0.8);
}
