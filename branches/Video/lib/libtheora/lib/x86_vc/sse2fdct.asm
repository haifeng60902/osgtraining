; x86_vc/sse2fdct.asm
; converted from x86/sse2fdct.c by Dmitry S. Baikov
;

;;
;; gcc -I../../include -I../../../libogg-1.1.4/include -DOC_X86_64_ASM -D_WIN32 -D__CYGWIN__ -c sse2fdct.c
;; objdump -Mintel --no-show-raw-insn -d sse2fdct.o > sse2fdct.asm
;; gvim ;)

.code

OC_FDCT8x8 MACRO
; /*Note: xmm15={0}x8 and xmm14={-1}x8.*/
; /*Stage 1:*/
	movdqa xmm11,xmm0
	movdqa xmm10,xmm1
	movdqa xmm9,xmm2
	movdqa xmm8,xmm3
; /*xmm11=t7'=t0-t7*/
	psubw  xmm11,xmm7
; /*xmm10=t6'=t1-t6*/
	psubw  xmm10,xmm6
; /*xmm9=t5'=t2-t5*/
	psubw  xmm9,xmm5
; /*xmm8=t4'=t3-t4*/
	psubw  xmm8,xmm4
; /*xmm0=t0'=t0+t7*/
	paddw  xmm0,xmm7
; /*xmm1=t1'=t1+t6*/
	paddw  xmm1,xmm6
; /*xmm5=t2'=t2+t5*/
	paddw  xmm5,xmm2
; /*xmm4=t3'=t3+t4*/
	paddw  xmm4,xmm3
; /*xmm2,3,6,7 are now free.*/
; /*Stage 2:*/
	movdqa xmm3,xmm0
	mov    rcx,5a806a0ah
	movdqa xmm2,xmm1
	movd   xmm13,ecx
	movdqa xmm6,xmm10
	pshufd xmm13,xmm13,0h
; /*xmm2=t2''=t1'-t2'*/
	psubw  xmm2,xmm5
	pxor   xmm12,xmm12
; /*xmm3=t3''=t0'-t3'*/
	psubw  xmm3,xmm4
	psubw  xmm12,xmm14
; /*xmm10=t5''=t6'-t5'*/
	psubw  xmm10,xmm9
	paddw  xmm12,xmm12
; /*xmm4=t0''=t0'+t3'*/
	paddw  xmm4,xmm0
; /*xmm1=t1''=t1'+t2'*/
	paddw  xmm1,xmm5
; /*xmm6=t6''=t6'+t5'*/
	paddw  xmm6,xmm9
; /*xmm0,xmm5,xmm9 are now free.*/
; /*Stage 3:*/
; /*xmm10:xmm5=t5''*27146+0xB500
;   xmm0=t5''*/
	movdqa xmm5,xmm10
	movdqa xmm0,xmm10
	punpckhwd xmm10,xmm12
	pmaddwd xmm10,xmm13
	punpcklwd xmm5,xmm12
	pmaddwd xmm5,xmm13
; /*xmm5=(t5''*27146+0xB500>>16)+t5''*/
	psrad  xmm10,10h
	psrad  xmm5,10h
	packssdw xmm5,xmm10
	paddw  xmm5,xmm0
; /*xmm0=s=(t5''*27146+0xB500>>16)+t5''+(t5''!=0)>>1*/
	pcmpeqw xmm0,xmm15
	psubw  xmm0,xmm14
	paddw  xmm0,xmm5
	movdqa xmm5,xmm8
	psraw  xmm0,1h
; /*xmm5=t5'''=t4'-s*/
	psubw  xmm5,xmm0
; /*xmm8=t4''=t4'+s*/
	paddw  xmm8,xmm0
; /*xmm0,xmm7,xmm9,xmm10 are free.*/
; /*xmm7:xmm9=t6''*27146+0xB500*/
	movdqa xmm7,xmm6
	movdqa xmm9,xmm6
	punpckhwd xmm7,xmm12
	pmaddwd xmm7,xmm13
	punpcklwd xmm9,xmm12
	pmaddwd xmm9,xmm13
; /*xmm9=(t6''*27146+0xB500>>16)+t6''*/
	psrad  xmm7,10h
	psrad  xmm9,10h
	packssdw xmm9,xmm7
	paddw  xmm9,xmm6
; /*xmm9=s=(t6''*27146+0xB500>>16)+t6''+(t6''!=0)>>1*/
	pcmpeqw xmm6,xmm15
	psubw  xmm6,xmm14
	paddw  xmm9,xmm6
	movdqa xmm7,xmm11
	psraw  xmm9,1h
; /*xmm7=t6'''=t7'-s*/
	psubw  xmm7,xmm9
; /*xmm9=t7''=t7'+s*/
	paddw  xmm9,xmm11
; /*xmm0,xmm6,xmm10,xmm11 are free.*/
; /*Stage 4:*/
; /*xmm10:xmm0=t1''*27146+0xB500*/
	movdqa xmm0,xmm1
	movdqa xmm10,xmm1
	punpcklwd xmm0,xmm12
	pmaddwd xmm0,xmm13
	punpckhwd xmm10,xmm12
	pmaddwd xmm10,xmm13
; /*xmm0=(t1''*27146+0xB500>>16)+t1''*/
	psrad  xmm0,10h
	psrad  xmm10,10h
	mov    rcx,20006a0ah
	packssdw xmm0,xmm10
	movd   xmm13,ecx
	paddw  xmm0,xmm1
; /*xmm0=s=(t1''*27146+0xB500>>16)+t1''+(t1''!=0)*/
	pcmpeqw xmm1,xmm15
	pshufd xmm13,xmm13,0h
	psubw  xmm1,xmm14
	paddw  xmm0,xmm1
; /*xmm10:xmm4=t0''*27146+0x4000*/
	movdqa xmm1,xmm4
	movdqa xmm10,xmm4
	punpcklwd xmm4,xmm12
	pmaddwd xmm4,xmm13
	punpckhwd xmm10,xmm12
	pmaddwd xmm10,xmm13
; /*xmm4=(t0''*27146+0x4000>>16)+t0''*/
	psrad  xmm4,10h
	psrad  xmm10,10h
	mov    rcx,6cb7h
	packssdw xmm4,xmm10
	movd   xmm12,ecx
	paddw  xmm4,xmm1
; /*xmm4=r=(t0''*27146+0x4000>>16)+t0''+(t0''!=0)*/
	pcmpeqw xmm1,xmm15
	pshufd xmm12,xmm12,0h
	psubw  xmm1,xmm14
	mov    rcx,7fff6c84h
	paddw  xmm4,xmm1
; /*xmm0=_y[0]=u=r+s>>1
;   The naive implementation could cause overflow, so we use
;    u=(r&s)+((r^s)>>1).*/
	movdqa xmm6,xmm0
	pxor   xmm0,xmm4
	pand   xmm6,xmm4
	psraw  xmm0,1h
	movd   xmm13,ecx
	paddw  xmm0,xmm6
; /*xmm4=_y[4]=v=r-u*/
	pshufd xmm13,xmm13,0h
	psubw  xmm4,xmm0
; /*xmm1,xmm6,xmm10,xmm11 are free.*/
; /*xmm6:xmm10=60547*t3''+0x6CB7*/
	movdqa xmm10,xmm3
	movdqa xmm6,xmm3
	punpcklwd xmm10,xmm3
	pmaddwd xmm10,xmm13
	mov    rcx,61f861f8h
	punpckhwd xmm6,xmm3
	pmaddwd xmm6,xmm13
	movd   xmm13,ecx
	paddd  xmm10,xmm12
	pshufd xmm13,xmm13,0h
	paddd  xmm6,xmm12
; /*xmm1:xmm2=25080*t2''
;   xmm12=t2''*/
	movdqa xmm11,xmm2
	movdqa xmm12,xmm2
	pmullw xmm2,xmm13
	pmulhw xmm11,xmm13
	movdqa xmm1,xmm2
	punpcklwd xmm2,xmm11
	punpckhwd xmm1,xmm11
; /*xmm10=u=(25080*t2''+60547*t3''+0x6CB7>>16)+(t3''!=0)*/
	paddd  xmm10,xmm2
	paddd  xmm6,xmm1
	psrad  xmm10,10h
	pcmpeqw xmm3,xmm15
	psrad  xmm6,10h
	psubw  xmm3,xmm14
	packssdw xmm10,xmm6
	paddw  xmm10,xmm3
; /*xmm2=_y[2]=u
;   xmm10=s=(25080*u>>16)-t2''*/
	movdqa xmm2,xmm10
	pmulhw xmm10,xmm13
	psubw  xmm10,xmm12
; /*xmm1:xmm6=s*21600+0x2800*/
	pxor   xmm12,xmm12
	psubw  xmm12,xmm14
	mov    rcx,28005460h
	movd   xmm13,ecx
	pshufd xmm13,xmm13,0h
	movdqa xmm6,xmm10
	movdqa xmm1,xmm10
	punpcklwd xmm6,xmm12
	pmaddwd xmm6,xmm13
	mov    rcx,0e3dh
	punpckhwd xmm1,xmm12
	pmaddwd xmm1,xmm13
; /*xmm6=(s*21600+0x2800>>18)+s*/
	psrad  xmm6,12h
	psrad  xmm1,12h
	movd   xmm12,ecx
	packssdw xmm6,xmm1
	pshufd xmm12,xmm12,0h
	paddw  xmm6,xmm10
; /*xmm6=_y[6]=v=(s*21600+0x2800>>18)+s+(s!=0)*/
	mov    rcx,7fff54dch
	pcmpeqw xmm10,xmm15
	movd   xmm13,ecx
	psubw  xmm10,xmm14
	pshufd xmm13,xmm13,0h
	paddw  xmm6,xmm10
; /*xmm1,xmm3,xmm10,xmm11 are free.*/
; /*xmm11:xmm10=54491*t5'''+0x0E3D*/
	movdqa xmm10,xmm5
	movdqa xmm11,xmm5
	punpcklwd xmm10,xmm5
	pmaddwd xmm10,xmm13
	mov    rcx,8e3a8e3ah
	punpckhwd xmm11,xmm5
	pmaddwd xmm11,xmm13
	movd   xmm13,ecx
	paddd  xmm10,xmm12
	pshufd xmm13,xmm13,0h
	paddd  xmm11,xmm12
; /*xmm7:xmm12=36410*t6'''
;   xmm1=t6'''*/
	movdqa xmm3,xmm7
	movdqa xmm1,xmm7
	pmulhw xmm3,xmm13
	pmullw xmm7,xmm13
	paddw  xmm3,xmm1
	movdqa xmm12,xmm7
	punpckhwd xmm7,xmm3
	punpcklwd xmm12,xmm3
; /*xmm10=u=(54491*t5'''+36410*t6'''+0x0E3D>>16)+(t5'''!=0)*/
	paddd  xmm10,xmm12
	paddd  xmm11,xmm7
	psrad  xmm10,10h
	pcmpeqw xmm5,xmm15
	psrad  xmm11,10h
	psubw  xmm5,xmm14
	packssdw xmm10,xmm11
	pxor   xmm12,xmm12
	paddw  xmm10,xmm5
; /*xmm5=_y[5]=u
;   xmm1=s=t6'''-(36410*u>>16)*/
	psubw  xmm12,xmm14
	movdqa xmm5,xmm10
	mov    rcx,340067c8h
	pmulhw xmm10,xmm13
	movd   xmm13,ecx
	paddw  xmm10,xmm5
	pshufd xmm13,xmm13,0h
	psubw  xmm1,xmm10
; /*xmm11:xmm3=s*26568+0x3400*/
	movdqa xmm3,xmm1
	movdqa xmm11,xmm1
	punpcklwd xmm3,xmm12
	pmaddwd xmm3,xmm13
	mov    rcx,7b1bh
	punpckhwd xmm11,xmm12
	pmaddwd xmm11,xmm13
; /*xmm3=(s*26568+0x3400>>17)+s*/
	psrad  xmm3,11h
	psrad  xmm11,11h
	movd   xmm12,ecx
	packssdw xmm3,xmm11
	pshufd xmm12,xmm12,0h
	paddw  xmm3,xmm1
; /*xmm3=_y[3]=v=(s*26568+0x3400>>17)+s+(s!=0)*/
	mov    rcx,7fff7b16h
	pcmpeqw xmm1,xmm15
	movd   xmm13,ecx
	psubw  xmm1,xmm14
	pshufd xmm13,xmm13,0h
	paddw  xmm3,xmm1
; /*xmm1,xmm7,xmm10,xmm11 are free.*/
; /*xmm11:xmm10=64277*t7''+0x7B1B*/
	movdqa xmm10,xmm9
	movdqa xmm11,xmm9
	punpcklwd xmm10,xmm9
	pmaddwd xmm10,xmm13
	mov    rcx,31f131f1h
	punpckhwd xmm11,xmm9
	pmaddwd xmm11,xmm13
	movd   xmm13,ecx
	paddd  xmm10,xmm12
	pshufd xmm13,xmm13,0h
	paddd  xmm11,xmm12
; /*xmm12:xmm7=12785*t4''*/
	movdqa xmm7,xmm8
	movdqa xmm1,xmm8
	pmullw xmm7,xmm13
	pmulhw xmm1,xmm13
	movdqa xmm12,xmm7
	punpcklwd xmm7,xmm1
	punpckhwd xmm12,xmm1
; /*xmm10=u=(12785*t4''+64277*t7''+0x7B1B>>16)+(t7''!=0)*/
	paddd  xmm10,xmm7
	paddd  xmm11,xmm12
	psrad  xmm10,10h
	pcmpeqw xmm9,xmm15
	psrad  xmm11,10h
	psubw  xmm9,xmm14
	packssdw xmm10,xmm11
	pxor   xmm12,xmm12
	paddw  xmm10,xmm9
; /*xmm1=_y[1]=u
;   xmm10=s=(12785*u>>16)-t4''*/
	psubw  xmm12,xmm14
	movdqa xmm1,xmm10
	mov    rcx,3000503bh
	pmulhw xmm10,xmm13
	movd   xmm13,ecx
	psubw  xmm10,xmm8
	pshufd xmm13,xmm13,0h
; /*xmm8:xmm7=s*20539+0x3000*/
	movdqa xmm7,xmm10
	movdqa xmm8,xmm10
	punpcklwd xmm7,xmm12
	pmaddwd xmm7,xmm13
	punpckhwd xmm8,xmm12
	pmaddwd xmm8,xmm13
; /*xmm7=(s*20539+0x3000>>20)+s*/
	psrad  xmm7,14h
	psrad  xmm8,14h
	packssdw xmm7,xmm8
	paddw  xmm7,xmm10
; /*xmm7=_y[7]=v=(s*20539+0x3000>>20)+s+(s!=0)*/
	pcmpeqw xmm10,xmm15
	psubw  xmm10,xmm14
	paddw  xmm7,xmm10
ENDM

OC_TRANSPOSE8x8 MACRO
	movdqa xmm8,xmm4
; /*xmm4 = f3 e3 f2 e2 f1 e1 f0 e0*/
	punpcklwd xmm4,xmm5
; /*xmm8 = f7 e7 f6 e6 f5 e5 f4 e4*/
	punpckhwd xmm8,xmm5
; /*xmm5 is free.*/
	movdqa xmm5,xmm0
; /*xmm0 = b3 a3 b2 a2 b1 a1 b0 a0*/
	punpcklwd xmm0,xmm1
; /*xmm5 = b7 a7 b6 a6 b5 a5 b4 a4*/
	punpckhwd xmm5,xmm1
; /*xmm1 is free.*/
	movdqa xmm1,xmm6
; /*xmm6 = h3 g3 h2 g2 h1 g1 h0 g0*/
	punpcklwd xmm6,xmm7
; /*xmm1 = h7 g7 h6 g6 h5 g5 h4 g4*/
	punpckhwd xmm1,xmm7
; /*xmm7 is free.*/
	movdqa xmm7,xmm2
; /*xmm7 = d3 c3 d2 c2 d1 c1 d0 c0*/
	punpcklwd xmm7,xmm3
; /*xmm2 = d7 c7 d6 c6 d5 c5 d4 c4*/
	punpckhwd xmm2,xmm3
; /*xmm3 is free.*/
	movdqa xmm3,xmm0
; /*xmm0 = d1 c1 b1 a1 d0 c0 b0 a0*/
	punpckldq xmm0,xmm7
; /*xmm3 = d3 c3 b3 a3 d2 c2 b2 a2*/
	punpckhdq xmm3,xmm7
; /*xmm7 is free.*/
	movdqa xmm7,xmm5
; /*xmm5 = d5 c5 b5 a5 d4 c4 b4 a4*/
	punpckldq xmm5,xmm2
; /*xmm7 = d7 c7 b7 a7 d6 c6 b6 a6*/
	punpckhdq xmm7,xmm2
; /*xmm2 is free.*/
	movdqa xmm2,xmm4
; /*xmm2 = h1 g1 f1 e1 h0 g0 f0 e0*/
	punpckldq xmm2,xmm6
; /*xmm4 = h3 g3 f3 e3 h2 g2 f2 e2*/
	punpckhdq xmm4,xmm6
; /*xmm6 is free.*/
	movdqa xmm6,xmm8
; /*xmm6 = h5 g5 f5 e5 h4 g4 f4 e4*/
	punpckldq xmm6,xmm1
; /*xmm8 = h7 g7 f7 e7 h6 g6 f6 e6*/
	punpckhdq xmm8,xmm1
; /*xmm1 is free.*/
	movdqa xmm1,xmm0
; /*xmm0 = h0 g0 f0 e0 d0 c0 b0 a0*/
	punpcklqdq xmm0,xmm2
; /*xmm1 = h1 g1 f1 e1 d1 c1 b1 a1*/
	punpckhqdq xmm1,xmm2
; /*xmm2 is free.*/
	movdqa xmm2,xmm3
; /*xmm2 = h2 g2 f2 e2 d2 c2 b2 a2*/
	punpcklqdq xmm2,xmm4
; /*xmm3 = h3 g3 f3 e3 d3 c3 b3 a3*/
	punpckhqdq xmm3,xmm4
; /*xmm4 is free.*/
	movdqa xmm4,xmm5
; /*xmm4 = h4 g4 f4 e4 d4 c4 b4 a4*/
	punpcklqdq xmm4,xmm6
; /*xmm5 = h5 g5 f5 e5 d5 c5 b5 a5*/
	punpckhqdq xmm5,xmm6
; /*xmm6 is free.*/
	movdqa xmm6,xmm7
; /*xmm6 = h6 g6 f6 e6 d6 c6 b6 a6*/
	punpcklqdq xmm6,xmm8
; /*xmm7 = h7 g7 f7 e7 d7 c7 b7 a7*/
	punpckhqdq xmm7,xmm8
; /*xmm8 is free.*/
ENDM

;/*SSE2 implementation of the fDCT for x86-64 only.
;  Because of the 8 extra XMM registers on x86-64, this version can operate
;   without any temporary stack access at all.*/
;void oc_enc_fdct8x8_x86_64sse2(ogg_int16_t _y[64],const ogg_int16_t _x[64]){

; see http://weblogs.asp.net/oldnewthing/archive/2004/01/14/58579.aspx and
;
; The first four parameters to a function are passed in rcx, rdx, r8 and r9.
;
; Any further parameters are pushed on the stack. Furthermore, space for the
; register parameters is reserved on the stack, in case the called function
; wants to spill them; this is important if the function is variadic. 
;
; All registers must be preserved across the call, except for
;   rax, rcx, rdx, r8, r-9, r10, and r11, which are scratch.

oc_enc_fdct8x8_x86_64sse2 PROC
; store output pointer
	mov rax,rcx
;    /*Load the input.*/
	movdqa xmm0,XMMWORD PTR [rdx]
	movdqa xmm1,XMMWORD PTR [rdx+10h]
	movdqa xmm2,XMMWORD PTR [rdx+20h]
	movdqa xmm3,XMMWORD PTR [rdx+30h]
	movdqa xmm4,XMMWORD PTR [rdx+40h]
	movdqa xmm5,XMMWORD PTR [rdx+50h]
	movdqa xmm6,XMMWORD PTR [rdx+60h]
	movdqa xmm7,XMMWORD PTR [rdx+70h]
;    /*Add two extra bits of working precision to improve accuracy; any more and
;       we could overflow.*/
;    /*We also add a few biases to correct for some systematic error that
;       remains in the full fDCT->iDCT round trip.*/
;    /*xmm15={0}x8*/
	pxor   xmm15,xmm15
;    /*xmm14={-1}x8*/
	pcmpeqb xmm14,xmm14
	psllw  xmm0,2h
;    /*xmm8=xmm0*/
	movdqa xmm8,xmm0
	psllw  xmm1,2h
;    /*xmm8={_x[7...0]==0}*/
	pcmpeqw xmm8,xmm15
	psllw  xmm2,2h
;    /*xmm8={_x[7...0]!=0}*/
	psubw  xmm8,xmm14
	psllw  xmm3,2h
;    /*%[a]=1*/
	mov    rcx,1h
;    /*xmm8={_x[6]!=0,0,_x[4]!=0,0,_x[2]!=0,0,_x[0]!=0,0}*/
	pslld  xmm8,10h
	psllw  xmm4,2h
;    /*xmm9={0,0,0,0,0,0,0,1}*/
	movd   xmm9,ecx
;    /*xmm8={0,0,_x[2]!=0,0,_x[0]!=0,0}*/
	pshufhw xmm8,xmm8,0h
	psllw  xmm5,2h
;    /*%[a]={1}x2*/
	mov    rcx,10001h
;    /*xmm8={0,0,0,0,0,0,0,_x[0]!=0}*/
	pshuflw xmm8,xmm8,1h
	psllw  xmm6,2h
;    /*xmm10={0,0,0,0,0,0,1,1}*/
	movd   xmm10,ecx
;    /*xmm0=_x[7...0]+{0,0,0,0,0,0,0,_x[0]!=0}*/
	paddw  xmm0,xmm8
	psllw  xmm7,2h
;    /*xmm0=_x[7...0]+{0,0,0,0,0,0,1,(_x[0]!=0)+1}*/
	paddw  xmm0,xmm10
;    /*xmm1=_x[15...8]-{0,0,0,0,0,0,0,1}*/
	psubw  xmm1,xmm9

;    /*Transform columns.*/
	OC_FDCT8x8
;    /*Transform rows.*/
	OC_TRANSPOSE8x8
	OC_FDCT8x8
;    /*TODO: zig-zag ordering?*/
	OC_TRANSPOSE8x8

;    /*xmm14={-2,-2,-2,-2,-2,-2,-2,-2}*/
	paddw  xmm14,xmm14
	psubw  xmm0,xmm14
	psubw  xmm1,xmm14
	psraw  xmm0,2h
	psubw  xmm2,xmm14
	psraw  xmm1,2h
	psubw  xmm3,xmm14
	psraw  xmm2,2h
	psubw  xmm4,xmm14
	psraw  xmm3,2h
	psubw  xmm5,xmm14
	psraw  xmm4,2h
	psubw  xmm6,xmm14
	psraw  xmm5,2h
	psubw  xmm7,xmm14
	psraw  xmm6,2h
	psraw  xmm7,2h
;    /*Store the result.*/
	movdqa XMMWORD PTR [rax],xmm0
	movdqa XMMWORD PTR [rax+10h],xmm1
	movdqa XMMWORD PTR [rax+20h],xmm2
	movdqa XMMWORD PTR [rax+30h],xmm3
	movdqa XMMWORD PTR [rax+40h],xmm4
	movdqa XMMWORD PTR [rax+50h],xmm5
	movdqa XMMWORD PTR [rax+60h],xmm6
	movdqa XMMWORD PTR [rax+70h],xmm7

	ret    
oc_enc_fdct8x8_x86_64sse2 ENDP

END
