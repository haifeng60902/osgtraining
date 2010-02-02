varying vec4 varPos;
varying vec3 n;

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
	//pack depth
	//float depth = ( varPos.z + 1.0 ) * 0.5;
	//gl_FragColor = packFloatToVec4i( depth );
	float depth = 0.0039525079;
	
	//pack normal
	vec3    n2   = normalize ( n );
	gl_FragColor = vec4 ( depth , 0.5*n2 + vec3(0.5) );
}