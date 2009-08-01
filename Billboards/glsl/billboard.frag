uniform sampler2D u_texture0;
varying vec3 light;

void main()
{
	gl_FragColor = texture2D( u_texture0 , gl_TexCoord[ 0 ].st );
	
	gl_FragColor *= vec4( light.yyy , 1.0 );
}