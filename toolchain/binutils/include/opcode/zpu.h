/* zpu.h -- Header file for Zylin ZPU opcode table
   Copyright 1999, 2000, 2002, 2003 Free Software Foundation, Inc.
   Written by Stephane Carrez (stcarrez@nerim.fr)

This file is part of GDB, GAS, and the GNU binutils.

GDB, GAS, and the GNU binutils are free software; you can redistribute
them and/or modify them under the terms of the GNU General Public
License as published by the Free Software Foundation; either version
1, or (at your option) any later version.

GDB, GAS, and the GNU binutils are distributed in the hope that they
will be useful, but WITHOUT ANY WARRANTY; without even the implied
warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See
the GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this file; see the file COPYING.  If not, write to the Free
Software Foundation, 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */

#ifndef _OPCODE_ZPU_H
#define _OPCODE_ZPU_H


enum ZPU_ADDRMODE
{
	ADDR_IMPLIED=1,
	ADDR_IMMEDIATE,
	ADDR_PCREL,
};


enum ZPU_OPCODE
{	
	ZPU_breakpoint=0,	
	ZPU_push_pc=59,	
	ZPU_pop_pc=4,
	ZPU_load=8,			
	ZPU_store=12,	
	ZPU_push_sp=2,
	ZPU_pop_sp=13,

	ZPU_add=5,
	ZPU_and=6,
	ZPU_or=7,

	ZPU_not=9,			
	ZPU_flip=10,	
	ZPU_nop=11,
	
	ZPU_addsp=16,
	
	ZPU_loadh=34,
	ZPU_storeh=35,
	ZPU_lessthan=36,
	ZPU_lessthanorequal=37,
	ZPU_ulessthan=38,
	ZPU_ulessthanorequal=39,
	ZPU_swap=40,
	ZPU_mult=41,
	ZPU_lshiftright=42,
	ZPU_ashiftleft=43,
	ZPU_ashiftright=44,
	ZPU_call=45,
	ZPU_eq=46,
	ZPU_neq=47,
	ZPU_neg=48,
	ZPU_sub=49,
	ZPU_xor=50,
	ZPU_loadb=51,
	ZPU_storeb=52,
	ZPU_div=53,
	ZPU_mod=54,
	ZPU_eqbranch=55,
	ZPU_neqbranch=56,
	ZPU_poppcrel=57,
	ZPU_config=58,
	ZPU_movebyte=59,
	ZPU_syscall=60,
	ZPU_pushspadd=61,
	ZPU_halfmult=62,
	ZPU_callpcrel=63,
	
	ZPU_impcrel=0, 		/* not an opcode, translates to IM instructions */
	
	ZPU_storesp=64, 	/* 32 instructions */
	
	ZPU_loadsp=64+32,	/* 32 instructions */
	
	
	ZPU_im=0x80,
	ZPU_im14=0,			/* nonrelaxable 14 bit immediate */
};


struct zpu_opcode
{
	enum ZPU_OPCODE code;
	char *name;
	enum ZPU_ADDRMODE amode;
};


/* The opcode table.  The table contains all the opcodes (all pages).
   You can't rely on the order.  */
extern const struct zpu_opcode zpu_opcodes[];
extern const int zpu_num_opcodes;

#endif /* _OPCODE_ZPU_H */
