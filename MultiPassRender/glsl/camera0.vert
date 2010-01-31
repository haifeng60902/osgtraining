varying vec4 varPos;

void main()
{
	varPos = gl_ModelViewMatrix * gl_Vertex;
	
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}