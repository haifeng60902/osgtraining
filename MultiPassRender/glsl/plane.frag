uniform sampler2D u_texture0;
uniform sampler2D u_texture1;
uniform sampler2D u_texture2;

//fragment position
varying vec4 varPos;

//Light Source Position in viewer space
uniform vec4 u4LightPos;

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
	vec4 res1 = texture2D( u_texture1 , gl_TexCoord[0].st );
	
	//extract normal
	vec3 v3Normal =  res0.xyz * 2.0 - 1.0;
	
	float zEye = fZNear * fZFar / ( res0.w * ( fZFar - fZNear ) - fZFar );
	
	//for now eyeCoord contain camera space x,y,z fragment value
	vec3  eyeCoord = -varPos.xyz * zEye;
	
	//get light vector
	vec3 v3LightVec = eyeCoord - u4LightPos.xyz;
	
	//calc light direction
	vec3 v3Dir = -normalize( v3LightVec );
	float fL = max( 0.0 , dot( v3Normal , v3Dir ) );
	
	vec4 depth = packFloatToVec4i( fL );
	gl_FragColor = res1 * ( vec4( fL , fL , fL , 0.0 ) + vec4( 0.3 , 0.3 , 0.3 , 1.0 ) );
}