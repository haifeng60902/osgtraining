uniform sampler2D u_texture0;
uniform sampler2D u_texture1;

 // main procedure, the original name was C2E2f_passthru
void main()
{
	vec4 tex0 = texture2D(u_texture0, gl_TexCoord[0].xy);
	vec4 tex1 = texture2D(u_texture1, gl_TexCoord[1].xy);
	
    gl_FragColor = mix( tex0 , tex1 , gl_Color );
    return;
} // main end
