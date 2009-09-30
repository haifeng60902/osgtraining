uniform vec3 posOffset;
uniform vec3 posVis;
uniform vec3 colorP;
uniform vec3 colorS;
uniform float dist;

void main()
{
	vec4 position = gl_Vertex;
	position += vec4( posOffset.xyz , 0.0 );
	
	//calc distance from viewer to input vertex
	float fDist = ( position.x - posVis.x ) * ( position.x - posVis.x ) + ( position.y - posVis.y ) * ( position.y - posVis.y );
	fDist = sqrt( fDist );
	
	//two different way to calculate final vertex position
	if( fDist < dist )
	{
		gl_FrontColor = vec4( colorP , 1.0 );
	}
	else
	{
		gl_FrontColor = vec4( colorS , 1.0 );
		position = vec4( floor( gl_Vertex.x * 0.5 ) * 2.0 , 
			floor( gl_Vertex.y * 0.5 ) * 2.0 ,
			gl_Vertex.z , gl_Vertex.w );
			
		position += vec4( posOffset.xyz , 0.0 );
	}
	
	gl_Position = gl_ModelViewProjectionMatrix * position;
}