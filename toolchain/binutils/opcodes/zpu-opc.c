/* zpu-opc.c -- Motorola 68HC11 & 68HC12 opcode list
   Copyright 1999, 2000, 2002 Free Software Foundation, Inc.
   Written by Stephane Carrez (stcarrez@nerim.fr)

This file is part of GDB, GAS, and the GNU binutils.

GDB, GAS, and the GNU binutils are free software; you can redistribute
them and/or modify them under the terms of the GNU General Public
License as published by the Free Software Foundation; either version
2, or (at your option) any later version.

GDB, GAS, and the GNU binutils are distributed in the hope that they
will be useful, but WITHOUT ANY WARRANTY; without even the implied
warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See
the GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this file; see the file COPYING.  If not, write to the Free
Software Foundation, 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
*/

#include <stdio.h>
#include "ansidecl.h"
#include "opcode/zpu.h"

#define TABLE_SIZE(X)       (sizeof(X) / sizeof(X[0]))

const struct zpu_opcode zpu_opcodes[]={
	{ZPU_breakpoint,		"breakpoint",		ADDR_IMPLIED},
	{ZPU_push_pc,			"pushpc",			ADDR_IMPLIED},
	{ZPU_or,				"or",				ADDR_IMPLIED},
	{ZPU_not,				"not",				ADDR_IMPLIED},
	{ZPU_load,				"load",				ADDR_IMPLIED},
	{ZPU_store,				"store",			ADDR_IMPLIED},
	{ZPU_pop_pc,			"poppc",			ADDR_IMPLIED},
	{ZPU_flip,				"flip",				ADDR_IMPLIED},
	{ZPU_add,				"add",				ADDR_IMPLIED},
	{ZPU_push_sp,			"pushsp",			ADDR_IMPLIED},
	{ZPU_pop_sp,			"popsp",			ADDR_IMPLIED},
	{ZPU_nop,				"nop",				ADDR_IMPLIED},
	{ZPU_and,				"and",				ADDR_IMPLIED},
	
	{ZPU_loadsp,			"loadsp",			ADDR_IMMEDIATE},
	{ZPU_storesp,			"storesp",			ADDR_IMMEDIATE},
	
	{ZPU_loadb,				"loadb",			ADDR_IMPLIED},
	{ZPU_storeb,			"storeb",			ADDR_IMPLIED},
	{ZPU_loadh,				"loadh",			ADDR_IMPLIED},
	{ZPU_storeh,			"storeh",			ADDR_IMPLIED},

	{ZPU_lessthan,			"lessthan",			ADDR_IMPLIED},
	{ZPU_lessthanorequal,	"lessthanorequal",	ADDR_IMPLIED},
	{ZPU_ulessthan,			"ulessthan",		ADDR_IMPLIED},
	{ZPU_ulessthanorequal,	"ulessthanorequal",	ADDR_IMPLIED},

	{ZPU_mult,				"mult",				ADDR_IMPLIED},
	{ZPU_halfmult,			"halfmult"	,		ADDR_IMPLIED},
	{ZPU_swap,				"swap",				ADDR_IMPLIED},
	{ZPU_div,				"div",				ADDR_IMPLIED},
	{ZPU_mod,				"mod",				ADDR_IMPLIED},
	{ZPU_eqbranch,			"eqbranch",			ADDR_IMPLIED},
	{ZPU_neqbranch,			"neqbranch",		ADDR_IMPLIED},
	
	{ZPU_poppcrel,			"poppcrel",			ADDR_IMPLIED},
	
	{ZPU_config,			"config",			ADDR_IMPLIED},
	{ZPU_movebyte,			"movebyte",			ADDR_IMPLIED},
	{ZPU_syscall,			"syscall",			ADDR_IMPLIED},
	{ZPU_pushspadd,			"pushspadd",		ADDR_IMPLIED},
	{ZPU_callpcrel,			"callpcrel",		ADDR_IMPLIED},

	{ZPU_lshiftright,		"lshiftright",		ADDR_IMPLIED},
	{ZPU_ashiftleft,		"ashiftleft",		ADDR_IMPLIED},

	{ZPU_ashiftright,		"ashiftright",		ADDR_IMPLIED},

	{ZPU_call,				"call",				ADDR_IMPLIED},
	
	{ZPU_eq,				"eq",				ADDR_IMPLIED},
	
	{ZPU_neq,				"neq",				ADDR_IMPLIED},
	
	{ZPU_neg,				"neg",				ADDR_IMPLIED},
	
	{ZPU_impcrel,			"impcrel",			ADDR_PCREL},

	{ZPU_sub,				"sub",				ADDR_IMPLIED},
	
	{ZPU_addsp,				"addsp",			ADDR_IMMEDIATE},
	
	{ZPU_xor,				"xor",				ADDR_IMPLIED},

	
	{ZPU_im,				"im",				ADDR_IMMEDIATE},
	
	{ZPU_im14,				"im14",				ADDR_IMMEDIATE},
	
};


const int zpu_num_opcodes = TABLE_SIZE (zpu_opcodes);


