uniform vec3 posOffset;
uniform vec3 posVis;
uniform vec3 colorP;
uniform vec3 colorS;
uniform float dist;

void main()
{
	vec4 position;
	position = gl_Vertex + vec4( posOffset.xyz , 0.0 );
	gl_Position = gl_ModelViewProjectionMatrix * position;
	
	float fDist = ( position.x - posVis.x ) * ( position.x - posVis.x ) + ( position.y - posVis.y ) * ( position.y - posVis.y );
	fDist = sqrt( fDist );
	
	gl_FrontColor = vec4( colorS , 1.0 );
	
	if( fDist < dist )
		gl_FrontColor = vec4( colorP , 1.0 );
}