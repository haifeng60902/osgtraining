uniform sampler2D u_texture0;

void main()
{
	vec4 tex0 = texture2D( u_texture0 , gl_TexCoord[0].st );
	
	gl_FragColor = tex0;
}