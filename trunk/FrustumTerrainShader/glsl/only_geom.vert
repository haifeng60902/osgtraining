uniform sampler2D u_texture0;
uniform sampler2D u_texture1;
uniform vec3 posOffset;
uniform vec3 posVis;
uniform vec3 colorP;
uniform vec3 colorS;
uniform float dist;
uniform float fKofScale;

void main()
{
	vec4 position = gl_Vertex * fKofScale;
	position.w = 1.0;
	
	position += vec4( posOffset.xyz, 0.0 );
	
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
		position = vec4( floor( gl_Vertex.x * 0.5 ) * 2.0 * fKofScale, 
			floor( gl_Vertex.y * 0.5 ) * 2.0 * fKofScale ,
			0.0 , 1.0 );
			
		position += vec4( posOffset.xyz , 0.0 );
	}
	
	vec4 tex0 = texture2D( u_texture0 , position.xy / 262144.0 );
	
	//fill texcoords
	vec2 texCoord1 = ( gl_Vertex.zw * 512.0 + posOffset.xy ) / 262144.0 * 512.0;
	vec4 texOffset = texture2D( u_texture1 , texCoord1 ) * 16.0;
	vec4 texAdd = gl_Vertex / fKofScale * 0.125;
	
	gl_TexCoord[0] = texOffset + texAdd * 256.0 / 4096.0;
	
	//scale height
	position.z = tex0.r * 3000.0;
	
	gl_Position = gl_ModelViewProjectionMatrix * position;
}