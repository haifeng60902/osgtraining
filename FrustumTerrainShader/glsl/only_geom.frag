uniform sampler2D u_texture2;

void main()
{
	vec4 tex2 = texture2D( u_texture2 , gl_TexCoord[0].st );
	
	gl_FragColor = tex2;
}