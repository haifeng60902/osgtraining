uniform sampler2D u_texture0;
uniform sampler2D u_texture1;
varying vec4 position;

void main()
{
	vec4 posTex = texture2D( u_texture1 , gl_Normal.xy ) * 262144.0;
	
	//if( posTex.w > 0.1 )
	//{
		position = gl_Vertex + vec4( posTex.xy , 0.0 , 0.0 );
		position = gl_ModelViewProjectionMatrix * position;
		gl_Position = position;
	//}
	//else
	//{
	//	position = vec4( 0.0 , 0.0, 0.0 , 0.0);
	//	gl_Position = position;
	//}
}