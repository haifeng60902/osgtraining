uniform vec3 offset;

void main()
{
	vec4 pos = vec4( gl_Vertex.xyz + offset + gl_Color.xyz, gl_Vertex.w );
	
	gl_Position = gl_ModelViewProjectionMatrix * pos;
	gl_TexCoord[0] = gl_MultiTexCoord0;
}