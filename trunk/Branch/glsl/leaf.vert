uniform float osg_FrameTime;
uniform vec3 lightPos;
uniform mat4 wRot0;
uniform mat4 wRot1;
uniform mat4 wRot2;
uniform mat4 wRot3;
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
	gl_Position = gl_ModelViewMatrix * gl_Position;
	
	float offset = gl_Vertex.x + gl_Vertex.y + gl_Vertex.z;
	float angle = atan( gl_ModelViewMatrix[2][0] , gl_ModelViewMatrix[2][1]) + cos( osg_FrameTime * 10.0 + cos( offset ) * 4.0 ) * 0.05;
		
	mat3 mvM = mat3( vec3( cos( angle ) , -sin( angle ) , 0 ) ,
		vec3( sin( angle ), cos( angle ) , 0 ) ,
		vec3( 0,0,1) );
		
	//calculate new vertex position
	vec3 rotPos = mvM * vec3( gl_MultiTexCoord1.xy , 0 );
	gl_Position.xyz += rotPos;
		
	gl_Position = gl_ProjectionMatrix * gl_Position;
	
	////////////////////////////////////////////////
	//light
	vec3 normal = gl_Normal;
	vec3 lightVector = normalize( lightPos );
	float nxDir = max( 0.0 , dot( normal , lightVector ) );
	diffuse = gl_LightSource[0].diffuse * nxDir;
	diffuse.a = 1.0;
	
	gl_TexCoord[0] = gl_MultiTexCoord0;
	gl_TexCoord[1] = gl_MultiTexCoord1;
} 