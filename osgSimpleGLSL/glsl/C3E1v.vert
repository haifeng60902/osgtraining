uniform vec3 _ZZ3SconstantColor;

 // main procedure, the original name was C3E1v_anycolor
void main()
{
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
    gl_TexCoord[0]=gl_MultiTexCoord0;
    gl_TexCoord[1]=gl_MultiTexCoord0;
    
    gl_FrontColor = vec4(_ZZ3SconstantColor,1);
    return;
} // main end
