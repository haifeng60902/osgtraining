uniform vec3 lightPos;
uniform mat4 wRot;
varying vec4 diffuse;

void main()
{
	gl_Position = wRot * gl_Vertex;
	gl_Position = gl_ModelViewProjectionMatrix * gl_Position;
	
	////////////////////////////////////////////////
	//light
	vec3 normal = gl_Normal;
	vec3 lightVector = normalize( lightPos );
	float nxDir = max( 0.0 , dot( normal , lightVector ) );
	diffuse = gl_LightSource[0].diffuse * nxDir;
	
	gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;
}