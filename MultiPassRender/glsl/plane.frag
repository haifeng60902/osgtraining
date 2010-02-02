uniform sampler2D u_texture0;
uniform sampler2D u_texture1;
uniform sampler2D u_texture2;

//
// pack a floating point value from [0,1] into RGBA8 vector
//
vec4 packFloatToVec4i( float value )
{
	vec4 bitSh   = vec4 ( 1.0 , 255.0 , 65025.0 , 16581375.0 );
	
	vec4 res = fract ( value * bitSh );
	
	//vec4 res;
	//res.x = value - floor( value );
	//res.y = value * 255.0 - floor( value * 255.0 );
	//res.z = value * 65025.0 - floor( value * 65025.0 );
	//res.w = value * 16581375.0 - floor( value * 16581375.0 );
 
    return res;
}

void main()
{
	vec4 res0 = texture2D( u_texture2 , gl_TexCoord[0].st );
	
	//vec4 depth = packFloatToVec4i( res0.x );
	
	gl_FragColor = res0;	
}