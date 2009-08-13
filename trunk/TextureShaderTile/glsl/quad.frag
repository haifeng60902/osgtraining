uniform sampler2D u_texture0;
uniform sampler2D u_texture1;
uniform sampler2D u_texture2;

uniform float offsetX;
uniform float offsetY;

uniform float scaleX;
uniform float scaleY;

uniform float offsetScaleX;
uniform float offsetScaleY;

void main()
{
	vec4 texTile = texture2D( u_texture0 , gl_TexCoord[0].st );
	vec2 sTC = gl_TexCoord[0].st * 512.0;
	
	//vec4 offsetTex = texture2D( u_texture2 , sTC );
	vec2 offsetTex = fract( sTC );
	
	offsetTex.x = offsetTex.x * scaleX + offsetScaleX;
	offsetTex.y = offsetTex.y * scaleY + offsetScaleY;
		
	vec2 nTC0 = vec2( texTile.x * 16.0 + offsetTex.x / 16.0, texTile.y * 16.0 + offsetTex.y / 16.0 );
	vec2 nTC1 = vec2( texTile.x * 16.0 + offsetTex.x / 16.0 + offsetX, texTile.y * 16.0 + offsetTex.y / 16.0 );
	vec2 nTC2 = vec2( texTile.x * 16.0 + offsetTex.x / 16.0 , texTile.y * 16.0 + offsetTex.y / 16.0 + offsetY );
	vec2 nTC3 = vec2( texTile.x * 16.0 + offsetTex.x / 16.0 + offsetX, texTile.y * 16.0 + offsetTex.y / 16.0 + offsetY );
	
	vec4 res0 = texture2D( u_texture1 , nTC0 );
	vec4 res1 = texture2D( u_texture1 , nTC1 );
	vec4 res2 = texture2D( u_texture1 , nTC2 );
	vec4 res3 = texture2D( u_texture1 , nTC3 );
	gl_FragColor = res0 * 0.25 + res1 * 0.25 + res2 * 0.25 + res3 * 0.25;
	
}