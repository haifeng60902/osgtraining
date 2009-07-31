uniform float osg_FrameTime;

void main()
{
	gl_Position = gl_ModelViewMatrix * gl_Vertex;
	
	float angle = atan( gl_ModelViewMatrix[2][0] , gl_ModelViewMatrix[2][1]);
	
	vec2 CS = vec2( cos( angle ) , sin( angle ));
	gl_Position.x += dot( CS , gl_MultiTexCoord0.zw );
	CS.y *= -1.0;
	gl_Position.y += dot( CS.yx , gl_MultiTexCoord0.zw );
	
	gl_Position = gl_ProjectionMatrix * gl_Position;
	
	gl_TexCoord[0] = gl_MultiTexCoord0;
} 