uniform sampler2D u_texture0;

uniform sampler2D u_texture3;
uniform sampler2D u_texture4;
uniform sampler2D u_texture5;
uniform sampler2D u_texture6;

void main()
{
	vec4 tex0 = texture2D( u_texture0 , gl_TexCoord[0].st );
	vec4 tex3 = texture2D( u_texture3 , gl_TexCoord[1].st );
	
	vec3 land_use = floor( vec3(tex0.xyz) * 255 );
	ivec3 sample = ivec3( 35 , 50 , 41 );
	
	if( sample == land_use )
	{
		gl_FragColor = tex3;
	}
	else
		gl_FragColor = tex0;
}