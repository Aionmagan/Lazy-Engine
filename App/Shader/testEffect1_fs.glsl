#version 330 core



#includeLE

void main()
{
	vec4 t = texture(Texture1, LE_TexCoord);
	if (t.a < 0.1) discard;
	//if (all(greaterThan(vec3(0.9999), t.rgb))) discard;
	LE_FragColor = vec4(t.rgb, 0.4); 	
}
