varying vec4 position;

void main()
{
	if( position.w > 0.1 )
		gl_FragColor = vec4( 0,1,1, 0.5 );
	else
		discard;
}