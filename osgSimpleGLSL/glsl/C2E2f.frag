uniform sampler2D u_texture0;
uniform vec3 _ZZ3SconstantColor;

 // main procedure, the original name was C2E2f_passthru
void main()
{
    gl_FragColor = vec4( _ZZ3SconstantColor, 1.0f);
    return;
} // main end
