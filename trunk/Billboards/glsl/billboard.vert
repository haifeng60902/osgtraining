uniform float osg_FrameTime;
uniform vec3 lightPos;
varying vec3 light;

void main()
{	
	//new center position
	gl_Position = gl_ModelViewMatrix * gl_Vertex;
	
	//calculate angle
	float angle = atan( gl_ModelViewMatrix[2][0] , gl_ModelViewMatrix[2][1]);
	
	//calculate new vertex position
	vec2 CS = vec2( cos( angle ) , sin( angle ));
	gl_Position.x += dot( CS , gl_MultiTexCoord0.zw );
	CS.y *= -1.0;
	gl_Position.y += dot( CS.yx , gl_MultiTexCoord0.zw );
	
	//in screen coord
	gl_Position = gl_ProjectionMatrix * gl_Position;
	
////////LIGHTING////////////////////////////////////////////////
	light = vec3( 1 ,1, 1);
	vec3 lightVec = -normalize( lightPos );
	light.x = dot( lightVec.xyz , gl_Vertex.xyz );
	if ( light.x > 0.0 )
		light.y = 0.0;

	gl_TexCoord[0] = gl_MultiTexCoord0;
} 