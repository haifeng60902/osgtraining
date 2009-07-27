// main procedure, the original name was C3E1v_anycolor
void main()
{
	gl_Position = ftransform();
	
	gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;
	gl_TexCoord[1] = gl_TextureMatrix[1] * gl_MultiTexCoord1;
	gl_TexCoord[2] = gl_TextureMatrix[2] * gl_MultiTexCoord2;
	gl_TexCoord[3] = gl_TextureMatrix[3] * gl_MultiTexCoord3;
}