varying vec2 texCoord0;

void main()
{
	gl_Position = ftransform();
	gl_TexCoord[0] = gl_MultiTexCoord0;
	texCoord0 = vec2( gl_MultiTexCoord0.xy );
}