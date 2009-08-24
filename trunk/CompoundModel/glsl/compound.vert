uniform sampler2D u_texture1;
uniform float offset_y;

void main()
{
	vec4 offset = texture2D( u_texture1 , vec2( gl_Vertex.w , offset_y ) ) * 60.0 * 128.0;
	vec4 newPos = gl_Vertex + vec4( offset.xy , 0 , 0 );
	gl_Position = gl_ModelViewProjectionMatrix * vec4( newPos.xyz , 1.0 );
	gl_TexCoord[0] = gl_MultiTexCoord0;
}