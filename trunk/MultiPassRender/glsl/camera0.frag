varying vec4 varPos;
varying vec3 n;

//for texture access
uniform sampler2D u_texture0;

//near and far plane clip
uniform float fZNear;
uniform float fZFar;

//
// pack a floating point value from [0,1] into RGBA8 vector
//
vec4 packFloatToVec4i( float value )
{
	vec4 bitSh   = vec4 ( 1.0 , 255.0 , 65025.0 , 16581375.0 );
	
	vec4 res = fract ( value * bitSh );
 
    return res;
}

void main()
{	
	//pack normal
	vec3    n2   = normalize ( n );
	
	//pack depth value from camera space view to diapason [-1..1]
	float fZFar = 20.0;
	float fZNear = 1.0;
	float fPackDepth = 1.0 / ( fZFar - fZNear ) * ( fZFar + fZNear + 2.0 * fZFar * fZNear / varPos.z );
	
	//pack normal vector and depth from [-1..1] to [0..1]
	gl_FragData[ 0 ] = vec4( 0.5 * n2 + vec3( 0.5 ) , ( fPackDepth + 1.0 ) * 0.5 );
	gl_FragData[ 1 ] = texture2D( u_texture0 , gl_TexCoord[0].st );
}