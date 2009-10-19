uniform sampler2D u_texture2;
uniform vec4 posOffset;

void main()
{
	vec4 position = gl_Vertex + posOffset;
	
	//calc hight map
	vec2 texCoord1 = ( posOffset.xy / 262144.0 ) * ( 1.0 - 1.0 / 1024.0 ) + 1.0 / 2048.0;
	vec4 tex1 = texture2D( u_texture2 , texCoord1 );
	
	//scale height
	position.z += tex1.r * 1500.0;
	
	position.w = 1.0;
	
	//calc final position
	gl_Position = gl_ModelViewProjectionMatrix * position;
	
	//copy tex_coord
	gl_TexCoord[0]=gl_MultiTexCoord0;
}