varying vec4 varPos;

//
// pack a floating point value from [0,1] into RGBA8 vector
//
vec4 packFloatToVec4i( const float value )
{
    const vec4 bitSh   = vec4 ( 1.0 , 255.0 , 255.0 * 255.0 , 255.0*255.0*255.0 );
	
    //vec4 res = fract ( value * bitSh );
    vec4 res;
    res.x = value;
    res.y = value * 255.0 - floor( value * 255.0 );
    res.z = value * 255.0 * 255.0 - floor( value * 255.0 * 255.0 );
    res.w = value * 255.0 * 255.0 * 255.0 - floor( value * 255.0 * 255.0 * 255.0 );
    
	
    return res;
}

void main()
{
	float depth = 0.0039525079;
	gl_FragColor = packFloatToVec4i( depth );
}