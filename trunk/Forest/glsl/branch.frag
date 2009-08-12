uniform sampler2D u_texture0;
varying vec4 diffuse;

// main procedure, the original name was C3E1v_anycolor
void main()
{
	vec4 colorScale = diffuse + gl_LightSource[0].ambient;
	colorScale.w = 1.0;
	vec4 tex0 = texture2D( u_texture0 , gl_TexCoord[0].st );
	
	gl_FragColor = tex0 * colorScale;
}