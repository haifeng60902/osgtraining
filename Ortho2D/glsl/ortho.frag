uniform sampler2D u_texture0;

void main()
{
	vec4 res0 = texture2D( u_texture0 , gl_TexCoord[0].st );
	
	gl_FragColor = vec4( res0.rgb , 1.0);	
}