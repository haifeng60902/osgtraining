void main()
{	
	//new center position
	gl_Position = gl_ModelViewMatrix * gl_Vertex;
	
	//transfer color
	gl_FrontColor = gl_Color;
	
	//in screen coord
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}