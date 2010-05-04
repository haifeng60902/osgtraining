void main()
{	
	//new center position
	gl_Position = gl_ModelViewMatrix * gl_Vertex;
	
	//in screen coord
	gl_Position = gl_ProjectionMatrix * gl_Position;
}