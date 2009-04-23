// glslf output by Cg compiler
// cgc version 2.1.0017, build date Feb 17 2009
// command line args: -profile glslf
// source file: C2E2f_passthru.cg
//vendor NVIDIA Corporation
//version 2.1.0.17
//profile glslf
//program C2E2f_passthru
//var float4 color : $vin.COLOR : COLOR : 0 : 1
//var float4 C2E2f_passthru.color : $vout.COLOR : COLOR : -1 : 1

struct C2E2f_Output {
    vec4 color;
};

C2E2f_Output _ZZ3Sret_0;

 // main procedure, the original name was C2E2f_passthru
void main()
{


    _ZZ3Sret_0.color = gl_Color;
    gl_FragColor = gl_Color;
    return;
} // main end
