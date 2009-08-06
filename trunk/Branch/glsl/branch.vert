uniform vec3 lightPos;
uniform mat4 wRot;
uniform mat4 wRot0;
uniform mat4 wRot1;
uniform mat4 wRot2;
uniform mat4 wRot3;
varying vec4 diffuse;

void main()
{	
	int i = gl_MultiTexCoord0.q;
	mat4 R;
	if ( i == 0)
		R = wRot0;
	else
		if ( i == 1 )
			R = wRot1;
		else
			if ( i == 2 )
				R = wRot2;
			else
				if ( i == 3 )
					R = wRot3;
	
	gl_Position = R * gl_Vertex;
	gl_Position = mix( gl_Vertex , gl_Position , gl_MultiTexCoord0.p );
	gl_Position = gl_ModelViewProjectionMatrix * gl_Position;
	
	////////////////////////////////////////////////
	//light
	vec3 normal = gl_Normal;
	vec3 lightVector = normalize( lightPos );
	float nxDir = max( 0.0 , dot( normal , lightVector ) );
	diffuse = gl_LightSource[0].diffuse * nxDir;
	
	gl_TexCoord[0] = gl_MultiTexCoord0;
}