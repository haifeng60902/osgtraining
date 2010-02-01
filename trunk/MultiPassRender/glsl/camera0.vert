varying vec4 varPos;
varying vec3 n;

void main()
{
	varPos = gl_ModelViewMatrix * gl_Vertex;
	n = normalize ( gl_NormalMatrix * gl_Normal );                // transformed n
	
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}