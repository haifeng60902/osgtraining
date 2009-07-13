uniform sampler2D u_texture0;
uniform vec3 _ZZ3SconstantColor;

 // main procedure, the original name was C3E1v_anycolor
void main()
{
    gl_TexCoord[0]=gl_MultiTexCoord0;
    
    vec4 tex0 = texture2D(u_texture0, gl_MultiTexCoord0.xy);
    vec4 tempVertex = gl_Vertex;
    tempVertex.z = tex0.r * 10.0;
    
    gl_Position = gl_ModelViewProjectionMatrix * tempVertex;
    
    gl_FrontColor = vec4(_ZZ3SconstantColor,1);
    return;
} // main end
