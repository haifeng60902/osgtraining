uniform sampler2D u_texture1;
uniform vec3 lightPos;
uniform mat4 wRot0;
uniform mat4 wRot1;
uniform mat4 wRot2;
uniform mat4 wRot3;
uniform vec3 posOffset;
varying vec4 diffuse;

void main()
{	
/////////////////////////////////////
//WIND CALCULATION
	float i = gl_MultiTexCoord0.q;
	mat4 R;
	if ( i == 0.0 )
		R = wRot0;
	else
		if ( i == 1.0 )
			R = wRot1;
		else
			if ( i == 2.0 )
				R = wRot2;
			else
				if ( i == 3.0 )
					R = wRot3;
	
	gl_Position = R * gl_Vertex;
	gl_Position = mix( gl_Vertex , gl_Position , gl_MultiTexCoord0.p );
	
	vec4 posTex = texture2D( u_texture1 , gl_Normal.xy );
	posTex *= vec4( 1024.0 , 1024.0 , 100.0 , 0.0 );
	gl_Position += posTex;
	
	gl_Position = gl_ModelViewProjectionMatrix * gl_Position;
	
	////////////////////////////////////////////////
	//light
	vec3 normal = gl_MultiTexCoord1.xyz;
	vec3 lightVector = normalize( lightPos );
	float nxDir = max( 0.0 , dot( normal , lightVector ) );
	diffuse = gl_LightSource[0].diffuse * nxDir;
	diffuse.a = 1.0;
	
	gl_TexCoord[0] = gl_MultiTexCoord0;
}