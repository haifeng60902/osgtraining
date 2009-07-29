void main()
{
	gl_Position = gl_ModelViewMatrix * gl_Vertex;
	
	gl_Position.xy += gl_MultiTexCoord0.zw * 2.0;
	
	gl_Position = gl_ProjectionMatrix * gl_Position;
	
	gl_TexCoord[0] = gl_MultiTexCoord0;
} 