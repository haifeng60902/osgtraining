// glslv output by Cg compiler
// cgc version 2.1.0017, build date Feb 17 2009
// command line args: -profile glslv
// source file: C3E1v_anycolor.cg
//vendor NVIDIA Corporation
//version 2.1.0.17
//profile glslv
//program C3E1v_anycolor
//semantic C3E1v_anycolor.constantColor
//var float3 constantColor :  : _ZZ3SconstantColor : 1 : 1
//var float2 position : $vin.POSITION : POSITION : 0 : 1
//var float4 C3E1v_anycolor.position : $vout.POSITION : POSITION : -1 : 1
//var float3 C3E1v_anycolor.color : $vout.COLOR : COLOR : -1 : 1

struct C3E1v_Output {
    vec4 position;
    vec3 color;
};

C3E1v_Output _ZZ3Sret_0;
uniform vec3 _ZZ3SconstantColor;

 // main procedure, the original name was C3E1v_anycolor
void main()
{

    C3E1v_Output _ZZ4SOUT;

    _ZZ4SOUT.position = vec4(gl_Vertex.x, gl_Vertex.z, 0.00000000E+000, 1.00000000E+000);
    _ZZ3Sret_0.position = _ZZ4SOUT.position;
    _ZZ3Sret_0.color = _ZZ3SconstantColor;
    gl_FrontColor.xyz = _ZZ3SconstantColor;
    gl_Position = _ZZ4SOUT.position;
    return;
} // main end
