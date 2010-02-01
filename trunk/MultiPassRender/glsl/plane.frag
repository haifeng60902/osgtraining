uniform sampler2D u_texture0;

void main()
{
	vec4 res0 = texture2D( u_texture0 , gl_TexCoord[0].st );
	res0.x = res0.x + res0.w;
	res0.y = res0.y + res0.w;
	res0.z = res0.z + res0.w;
	
	gl_FragColor = vec4( res0.xyz , 1.0 );	
}