uniform sampler2D u_texture0;
uniform sampler2D u_texture1;
varying vec4 diffuse;

void main()
{
	vec4 colorScale = diffuse + gl_LightSource[0].ambient;
	colorScale.w = 1.0;
	if( gl_TexCoord[ 1 ].p < 0.1 )
		gl_FragColor = texture2D( u_texture0 , gl_TexCoord[ 0 ].st ) * colorScale;
	else
		if( ( gl_TexCoord[ 1 ].p > 0.9 ) && ( gl_TexCoord[ 1 ].p < 1.1) ) 
			gl_FragColor = texture2D( u_texture0 , vec2( 1.0 - gl_TexCoord[ 0 ].s, gl_TexCoord[ 0 ].t ) ) * colorScale;
		else
			if( ( gl_TexCoord[ 1 ].p > 1.9 ) && ( gl_TexCoord[ 1 ].p < 2.1) ) 
				gl_FragColor = texture2D( u_texture1 , gl_TexCoord[ 0 ].st ) * colorScale;
			else
				if( ( gl_TexCoord[ 1 ].p > 2.9 ) && ( gl_TexCoord[ 1 ].p < 3.1) ) 
					gl_FragColor = texture2D( u_texture1 , vec2( 1.0 - gl_TexCoord[ 0 ].s, gl_TexCoord[ 0 ].t ) ) * colorScale;
				else
					discard;
}