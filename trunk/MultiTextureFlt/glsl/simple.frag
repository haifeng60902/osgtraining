uniform sampler2D u_texture0;
uniform sampler2D u_texture1;
uniform sampler2D u_texture2;
uniform sampler2D u_texture3;

// main procedure, the original name was C3E1v_anycolor
void main()
{
	vec4 tex0 = texture2D( u_texture0 , gl_TexCoord[0].st );
	vec4 tex1 = texture2D( u_texture1 , gl_TexCoord[1].st );
	vec4 tex2 = texture2D( u_texture2 , gl_TexCoord[2].st );
	vec4 tex3 = texture2D( u_texture3 , gl_TexCoord[3].st );
	
	gl_FragColor = tex3;
}