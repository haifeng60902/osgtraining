varying vec3 posOffset;

void main()
{
	vec4 position;
	position = gl_Vertex + vec4( posOffset.xyz , 0.0 );
	position = gl_ModelViewProjectionMatrix * position;
	gl_Position = position;
}