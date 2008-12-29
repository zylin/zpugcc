/* The ZPU does not have a 64 bit register */
/* { dg-do compile { xfail m6811-*-* m6812-*-*} } */

f(){asm("%0"::"r"(1.5F));}g(){asm("%0"::"r"(1.5));}
