uniform sampler2D u_texture0;
uniform sampler2D u_texture1;
uniform sampler2D u_texture2;

uniform float offsetX;
uniform float offsetY;

uniform float scaleX;
uniform float scaleY;

uniform float offsetScaleX;
uniform float offsetScaleY;

varying vec2 texCoord0;

void main()
{
	vec4 texTile = texture2D( u_texture0 , texCoord0 ) * 256.0f;
	if( texTile != floor( texTile ) )
		discard;
	texTile *= 0.0625;
	
//	if ( tX != floor( tX ) )
//		discard;
		
	vec2 sTC0 = texCoord0 * 512.0f;
	
	vec2 offsetTex = fract( sTC0 );

	vec2 nTC0 = vec2( texTile.x + offsetTex.x * 0.0625f , texTile.y + offsetTex.y * 0.0625f );
	
	vec4 res0 = texture2D( u_texture1 , nTC0 );
	
	gl_FragColor = res0;
	
}