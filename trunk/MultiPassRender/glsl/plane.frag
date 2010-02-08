uniform sampler2D u_texture0;
uniform sampler2D u_texture1;
uniform sampler2D u_texture2;

//fragment position
varying vec4 varPos;

//Light Source Position
varying vec4 v4LightPos;

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
	vec4 res0 = texture2D( u_texture0 , gl_TexCoord[0].st );
	
	//extract normal
	vec3 v3Normal =  res0.xyz * 2.0 - 1.0;
	
	float zEye = 20.0 / ( res0.w * 19.0 - 20.0 );
	vec3  eyeCoord = varPos * zEye;
	//eyeCoord *= -1.0;
	
	vec4 depth = packFloatToVec4i( eyeCoord.z / 20.0 );
	
	//get light vector
	vec3 v3LightVec = eyeCoord - v4LightPos.xyz;
	v3LightVec = normalize( v3LightVec );
	
	float nxDir = max( 0.0 , dot( v3Normal , v3LightVec ) );
	
	//gl_FragColor = depth.abgr;
	gl_FragColor = nxDir;
}