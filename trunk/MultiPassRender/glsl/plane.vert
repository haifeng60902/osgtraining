//fragment position
varying vec4 varPos;

//Light Source Position in viewer space
varying vec4 v4LightPos;

//Original Light Sorce position
uniform vec4 u4LightPos;

void main()
{
	varPos = gl_ModelViewMatrix * gl_Vertex;
	v4LightPos = gl_ModelViewMatrix * u4LightPos;
	gl_TexCoord[0] = gl_MultiTexCoord0;
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}