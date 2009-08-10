uniform float osg_FrameTime;
uniform vec3 lightPos;
uniform vec4 centerPos;
varying vec3 light;

void main()
{	
	//new center position
	gl_Position = gl_ModelViewMatrix * gl_Vertex;
	
	float offset = gl_Vertex.x + gl_Vertex.y + gl_Vertex.z;
	
	//calculate angle
	float angle = atan( gl_ModelViewMatrix[2][0] , gl_ModelViewMatrix[2][1]) + cos( osg_FrameTime * 2.0 + cos( offset ) * 4.0 ) * 0.05;
	
	mat3 mvM = mat3( vec3( cos( angle ) , -sin( angle ) , 0 ) ,
		vec3( sin( angle ), cos( angle ) , 0 ) ,
		vec3( 0,0,1) );
		
	float angleY = cos( ( osg_FrameTime * 32.0 ) + cos( offset ) ) * 0.785398 * 0.05;
	mat3 mvR = mat3( vec3( cos( angleY ) ,  0 , sin( angleY ) ) ,
		vec3( 0,1,0) ,
		vec3( -sin( angleY ), 0 , cos( angleY ) ) );
	
	//calculate new vertex position
	vec3 rotPos = mvR * mvM * vec3( gl_MultiTexCoord0.zw , 0 );
	gl_Position.xyz += rotPos;
	
	//in screen coord
	gl_Position = gl_ProjectionMatrix * gl_Position;
	
////////LIGHTING////////////////////////////////////////////////
	//offset vertex in new local coordinat system
	vec3 offsetVertex = gl_Vertex.xyz - centerPos.xyz;
	
	light = vec3( 1 ,1, 1);
	vec3 lightVec = normalize( lightPos );
	
	light.x = dot( lightVec , offsetVertex );
	if ( light.x < 0.0 )
		light.y = 0.3;
	else
	{
		light.x = min( light.x , centerPos.w );
		light.y = ( 1.0 - light.x / centerPos.w ) * 1.57079633;
		light.y = cos( light.y ) + 0.3;
	}

	gl_TexCoord[0] = gl_MultiTexCoord0;
} 