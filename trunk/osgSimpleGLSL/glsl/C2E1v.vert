// glslv output by Cg compiler
// cgc version 2.1.0017, build date Feb 17 2009
// command line args: -profile glslv
// source file: C2E1v_green.cg
//vendor NVIDIA Corporation
//version 2.1.0.17
//profile glslv
//program C2E1v_green
//var float2 position : $vin.POSITION : POSITION : 0 : 1
//var float4 C2E1v_green.position : $vout.POSITION : POSITION : -1 : 1
//var float3 C2E1v_green.color : $vout.COLOR : COLOR : -1 : 1

struct C2E1v_Output {
    vec4 position;
    vec3 color;
};

C2E1v_Output _ZZ3Sret_0;

 // main procedure, the original name was C2E1v_green
void main()
{

    C2E1v_Output _ZZ4SOUT;

    _ZZ4SOUT.position = vec4(gl_Vertex.x, gl_Vertex.z, 0.00000000E+000, 1.00000000E+000);
    _ZZ3Sret_0.position = _ZZ4SOUT.position;
    _ZZ3Sret_0.color = vec3( 0.00000000E+000, 1.00000000E+000, 0.00000000E+000);
    gl_FrontColor.xyz = vec3( 1.00000000E+000, 1.00000000E+000, 0.00000000E+000);
    gl_Position = _ZZ4SOUT.position;
    return;
} // main end
