/* Target-dependent code for Zylin ZPU

   Copyright 1999, 2000, 2001, 2002, 2003, 2004 Free Software
   Foundation, Inc.

   Contributed by Stephane Carrez, stcarrez@nerim.fr

This file is part of GDB.

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */


#include "defs.h"
#include "frame.h"
#include "frame-unwind.h"
#include "frame-base.h"
#include "dwarf2-frame.h"
#include "trad-frame.h"
#include "symtab.h"
#include "gdbtypes.h"
#include "gdbcmd.h"
#include "gdbcore.h"
#include "gdb_string.h"
#include "value.h"
#include "inferior.h"
#include "dis-asm.h"  
#include "symfile.h"
#include "objfiles.h"
#include "arch-utils.h"
#include "regcache.h"
#include "reggroups.h"

#include "target.h"
#include "opcode/zpu.h"
#include "elf/zpu.h"
#include "elf-bfd.h"

#define RETURN_ADDR_SIZE 4

#define HARD_R0_REGNUM 	0
#define HARD_R1_REGNUM 	1
#define HARD_R2_REGNUM 	2
#define HARD_R3_REGNUM 	3
#define HARD_R4_REGNUM 	4
#define HARD_R5_REGNUM 	5
#define HARD_R6_REGNUM 	6
#define HARD_R7_REGNUM 	7
#define HARD_SP_REGNUM 	32
#define HARD_PC_REGNUM 	33

#define ZPU_NUM_REGS        (34)

#define ZPU_REG_SIZE    (4)

struct insn_sequence;
struct gdbarch_tdep
  {
    /* ELF flags for ABI.  */
    int elf_flags;
  };


struct zpu_unwind_cache
{
  /* The previous frame's inner most stack address.  Used as this
     frame ID's stack_addr.  */
  CORE_ADDR prev_sp;
  /* The frame's base, optionally used by the high-level debug info.  */
  CORE_ADDR base;
  CORE_ADDR pc;
  int argSize; /* argument size */
  int frameSize; /* frame size */
  int savedSize; /* size of saved registers */
  CORE_ADDR return_pc;

  /* Table indicating the location of each and every register.  */
  struct trad_frame_saved_reg *saved_regs;
};

/* Table of registers for ZPU.  This includes the hard registers
   and the soft registers used by GCC.  */
static char *
zpu_register_names[] =
{
	"r0",  "r1",  "r2",  "r3",  "r4",  "r5",  "r6", "r7",
	"r8",  "r9",  "r10", "r11", "r12", "r13", "r14", "r15",
	"r16", "r17", "r18", "r19", "r20", "r21", "r22", "r23",
	"r24", "r25", "r26", "r27", "r28", "r29", "r30", "r31",
	 "sp", "pc"
};


static const char *
zpu_register_name (int reg_nr)
{
  if ((reg_nr <0)||(reg_nr>ZPU_NUM_REGS))
    return NULL;

  return zpu_register_names[reg_nr];
}

/* breakpoint is always the same as PC address w/0x00.  */
static const unsigned char *
zpu_breakpoint_from_pc (CORE_ADDR *pcptr, int *lenptr)
{
  static unsigned char breakpoint[] = {0x00};
  
  *lenptr = sizeof (breakpoint);
  return breakpoint;
}

/* Return the GDB type object for the "standard" data type
   of data in register N.  */

static struct type *
zpu_register_type (struct gdbarch *gdbarch, int reg_nr)
{
  return builtin_type_uint32;
}

static void
zpu_store_return_value (struct type *type, struct regcache *regcache,
                            const void *valbuf)
{
    error ("not implemented store return value..");
}


/* Given a return value in `regcache' with a type `type', 
   extract and copy its value into `valbuf'.  */
static void
zpu_extract_return_value (struct type *type, struct regcache *regcache,
                              void *valbuf)
{
  regcache_raw_read (regcache, HARD_R0_REGNUM, valbuf);
}

enum return_value_convention
zpu_return_value (struct gdbarch *gdbarch, struct type *valtype,
		      struct regcache *regcache, void *readbuf,
		      const void *writebuf)
{
  if (TYPE_CODE (valtype) == TYPE_CODE_STRUCT
      || TYPE_CODE (valtype) == TYPE_CODE_UNION
      || TYPE_CODE (valtype) == TYPE_CODE_ARRAY 
      || TYPE_LENGTH (valtype) > 4)
    return RETURN_VALUE_STRUCT_CONVENTION;
  else
    {
      if (readbuf != NULL)
	zpu_extract_return_value (valtype, regcache, readbuf);
      if (writebuf != NULL)
	zpu_store_return_value (valtype, regcache, writebuf);
      return RETURN_VALUE_REGISTER_CONVENTION;
    }
}

static int
gdb_print_insn_zpu (bfd_vma memaddr, disassemble_info *info)
{
	return print_insn_zpu (memaddr, info);
}



#define PUSHPC 1
#define LOAD 4
#define STORE 5
#define POPPC 6
#define ADD 8
#define PUSHSP 9
#define POPSP 10

static int decodeImmediate(unsigned char t)
{
	return (((int)((signed char)(t<<1)))>>1);
}

/* skip copy of return value to register */
CORE_ADDR skip_store_retval(CORE_ADDR ip)
{
	unsigned char t;
	CORE_ADDR scan=ip;
	
	t=read_memory_integer (scan++, 1);
	if (t==0x80)
	{
		t=read_memory_integer (scan++, 1);
		if (t==LOAD)
		{
			t=read_memory_integer (scan++, 1);
			if (((t&0x7f)>=0)&&((t&0x7f)<=12))
			{
				t=read_memory_integer (scan++, 1);
				if (t==STORE)
				{
					return scan;
				}
			}
		}
	}
	return ip;
}


void scan_stack_change(CORE_ADDR *ip_core, int * const frameSize, int * const gotFrame)
{
	unsigned char t;
	*gotFrame=0;
	t=read_memory_integer ((*ip_core)++, 1);
	if (t==PUSHSP)
	{
		*gotFrame=1;

		t=read_memory_integer ((*ip_core)++, 1);
		if ((t&0x80)!=0)
		{
			/* amount of stack allocated is < 63  bytes 
			 * 
			 * allocate space on stack
	     436:       09              pushsp
	     437:       f8              im -8
	     438:       08              add
	     439:       0a              popsp
			 * 
			 * */	
			*frameSize=decodeImmediate(t);
			
			*gotFrame=1;
			
		} else
		{
			CORE_ADDR frameSizeAddr;
			/*
		 * allocate space on stack, but > 63 bytes
	     4:   09              pushsp
	     5:   01              pushpc
	     6:   97              im 23
	     7:   08              add
	     8:   04              load
	     9:   08              add
	     a:   0a              popsp
			*/		
			
			frameSizeAddr=*ip_core;
			t=read_memory_integer ((*ip_core)++, 1);
			*gotFrame=0;
	
			if (t==PUSHPC)
			{			
				t=read_memory_integer ((*ip_core)++, 1);
				if ((t&0x80)!=0)
				{
					frameSizeAddr+=decodeImmediate(t);
					
					t=read_memory_integer ((*ip_core)++, 1);
					if (t==ADD)
					{
						t=read_memory_integer ((*ip_core)++, 1);
						if (t==LOAD)
						{
							*frameSize=read_memory_integer(frameSizeAddr, 4);
							
							*gotFrame=1;
						}
					}
				}
			}
		}


		if (*gotFrame)
		{		
			*gotFrame=0;
			
			/*
			 *      9:   08              add
			 *      a:   0a              popsp
			 */
			t=read_memory_integer ((*ip_core)++, 1);
			if (t==ADD)
			{
				t=read_memory_integer ((*ip_core)++, 1);
				if (t==POPSP)
				{
					*gotFrame=1;
				}	
			}
		}
	}	 
}

/*
 * Example prologue:
 * 
 * save registers
     430:       84              im 4
     431:       04              load
     432:       88              im 8
     433:       04              load
     434:       8c              im 12
     435:       04              load
*/

/* fill in zpu_unwind_cache structure w/information about fn.
 * 
 * primary return value returns first instruction after prologue
 */
static CORE_ADDR
zpu_scan_prologue (
/* address of function to scan */
CORE_ADDR ip, 
/* current pc inside function */
CORE_ADDR current_pc,
/* fill in this structure */
struct zpu_unwind_cache *info,
struct trad_frame_saved_reg *saved_regs)

{
	int frameSize=0;
	int gotFrame=1;
  info->frameSize = 0;
  if (ip > current_pc)
  {
  	/* sanity check */
    return current_pc;
  }

  if (ip == 0)
    {
		/* we're not inside a fn w/debug info. */
      return ip;
    }

	CORE_ADDR ip_core=ip;
	int i;

	/* skip saving of registers... At most r1-r3 */
	unsigned char t;
	for (i=0; i<3; i++)
	{
		t=read_memory_integer (ip_core++, 1);
		if (t==PUSHSP)
		{
			/* found all saved registers... */
			break; 
		}
		
		/* quick&dirty check on whether this is a saved register */
		switch (t)
		{
			case 4+128:
			case 8+128:
			case 12+128:
			break;
			
			default:
			return ip;
		}

		if (saved_regs!=NULL)
		{
			int reg=(t&0x7f)/4;
			saved_regs[reg].addr=-i*4;
		}
		
		t=read_memory_integer (ip_core++, 1);
		if (t!=LOAD)
		{
			return ip;
		}
	}

	/* size of saved registers */
	info->savedSize=i*4;
	
	if (saved_regs!=NULL)
	{
		/* add size of registers... */
		for (i=0; i<4; i++)
		{
		    if (trad_frame_addr_p (info->saved_regs, i))
	    	  {
	    	  	saved_regs[i].addr+=info->savedSize;
	    	  }
		}
	}
	
	ip=ip_core; /* this is the first instruction as far as we know for now */

	
	/* figure out how much stack that has been allocated */
	if (i!=3)
	{
		/* step back an address */
		ip_core--;
	}


	/* at this point we might be frameless, so only continue scanning 
	 * as long as we see expected frame instructions and only commit frame
	 * size when we actually see the frame allocated.
	 */
	scan_stack_change(&ip_core, &frameSize, &gotFrame);
	
	if (gotFrame&&(frameSize<0))
	{
		info->frameSize=-frameSize;
		ip=ip_core;
	}
	
	return ip;
}

CORE_ADDR zpu_skip_prologue (CORE_ADDR ip)
{
  struct zpu_unwind_cache tmp_cache = { 0 };

  return zpu_scan_prologue (ip, (CORE_ADDR) -1, &tmp_cache, NULL);
}

static CORE_ADDR
zpu_unwind_sp (struct gdbarch *gdbarch, struct frame_info *next_frame)
{
  ULONGEST sp;
  frame_unwind_unsigned_register (next_frame, HARD_SP_REGNUM, &sp);
  return sp;
}

static CORE_ADDR
zpu_unwind_pc (struct gdbarch *gdbarch, struct frame_info *next_frame)
{
  ULONGEST pc;

  frame_unwind_unsigned_register (next_frame, gdbarch_pc_regnum (gdbarch),
                                  &pc);
  return pc;
}


/* examine stack frame, starting from next_frame */

struct zpu_unwind_cache *
zpu_frame_unwind_cache (struct frame_info *next_frame,
                            void **this_prologue_cache)
{
  ULONGEST this_base;
  struct zpu_unwind_cache *info;
  CORE_ADDR current_pc;
  int i;

  if ((*this_prologue_cache))
    return (*this_prologue_cache);

  info = FRAME_OBSTACK_ZALLOC (struct zpu_unwind_cache);
  
  /* NOTE! by setting the info pointer here, we avoid infinite recursion. 
   * Make sure that we do not use the 'info' structure before we have filled
   * in the bits we are asking questions about...
   */
  (*this_prologue_cache) = info;
  
  info->saved_regs = trad_frame_alloc_saved_regs (next_frame);

	/* frame_func_unwind() returns 0 if no fn was found */
  info->pc = frame_func_unwind (next_frame);

  info->frameSize = 0;

  /* figure out frame pointer.... */
  frame_unwind_unsigned_register (next_frame, HARD_SP_REGNUM, &this_base);
  if (this_base == 0)
    {
      info->base = 0;
      return info;
    }

  current_pc = frame_pc_unwind (next_frame);
  if (info->pc != 0)
    zpu_scan_prologue (info->pc, current_pc, info, info->saved_regs);


  /* PC is saved immediately before saved off registers */
  info->saved_regs[HARD_PC_REGNUM].addr = this_base+info->frameSize+info->savedSize;

	/* we need to scan the instructions at the return address to figure out the
	 * size of the arguments passed to the fn.
	 */
	info->return_pc=read_memory_integer(info->saved_regs[HARD_PC_REGNUM].addr, 4);

	CORE_ADDR scan=info->return_pc;
	int gotIt;
	
	scan=skip_store_retval(scan);

	scan_stack_change(&scan, &info->argSize, &gotIt);
	if (info->argSize<0)
	{
		/* don't know what the caller is doing, but it isn't popping arguments off
		 * the stack
		 */
		info->argSize=0; 
	}

  
  info->prev_sp = info->saved_regs[HARD_PC_REGNUM].addr + RETURN_ADDR_SIZE;

  info->base = this_base;



  /* The previous frame's SP needed to be computed.  Save the computed
     value.  */
  trad_frame_set_value (info->saved_regs, HARD_SP_REGNUM, info->prev_sp);

  return info;
}

/* Given a GDB frame, determine the address of the calling function's
   frame.  This will be used to create a new GDB frame struct.  */

static void
zpu_frame_this_id (struct frame_info *next_frame,
                       void **this_prologue_cache,
                       struct frame_id *this_id)
{
  struct zpu_unwind_cache *info
    = zpu_frame_unwind_cache (next_frame, this_prologue_cache);
  CORE_ADDR func;
  struct frame_id id;

  func = frame_func_unwind (next_frame);

  id = frame_id_build (info->base, func);
  (*this_id) = id;
}

static void
zpu_frame_prev_register (struct frame_info *next_frame,
                             void **this_prologue_cache,
                             int regnum, int *optimizedp,
                             enum lval_type *lvalp, CORE_ADDR *addrp,
                             int *realnump, void *bufferp)
{
  struct zpu_unwind_cache *info
    = zpu_frame_unwind_cache (next_frame, this_prologue_cache);

  trad_frame_prev_register (next_frame, info->saved_regs, regnum,
                            optimizedp, lvalp, addrp, realnump, bufferp);
}

static const struct frame_unwind zpu_frame_unwind = {
  NORMAL_FRAME,
  zpu_frame_this_id,
  zpu_frame_prev_register
};

const struct frame_unwind *
zpu_frame_sniffer (struct frame_info *next_frame)
{
  return &zpu_frame_unwind;
}

static CORE_ADDR
zpu_frame_base_address (struct frame_info *next_frame, void **this_cache)
{
  struct zpu_unwind_cache *info
    = zpu_frame_unwind_cache (next_frame, this_cache);

  return info->base;
}


static CORE_ADDR
zpu_frame_args_address (struct frame_info *next_frame, void **this_cache)
{
  CORE_ADDR addr;
  struct zpu_unwind_cache *info
    = zpu_frame_unwind_cache (next_frame, this_cache);

  addr = info->base + info->savedSize + RETURN_ADDR_SIZE;

  return addr;
}


static const struct frame_base zpu_frame_base = {
  &zpu_frame_unwind,
  zpu_frame_base_address,
  zpu_frame_base_address,
  zpu_frame_args_address
};


static struct gdbarch *
zpu_gdbarch_init (struct gdbarch_info info,
                      struct gdbarch_list *arches)
{
  struct gdbarch *gdbarch;
  struct gdbarch_tdep *tdep;
  int elf_flags;

  /* Extract the elf_flags if available.  */
  if (info.abfd != NULL
      && bfd_get_flavour (info.abfd) == bfd_target_elf_flavour)
    elf_flags = elf_elfheader (info.abfd)->e_flags;
  else
    elf_flags = 0;

  /* try to find a pre-existing architecture */
  for (arches = gdbarch_list_lookup_by_info (arches, &info);
       arches != NULL;
       arches = gdbarch_list_lookup_by_info (arches->next, &info))
    {
      if (gdbarch_tdep (arches->gdbarch)->elf_flags != elf_flags)
	continue;

      return arches->gdbarch;
    }

  /* Need a new architecture. Fill in a target specific vector.  */
  tdep = (struct gdbarch_tdep *) xmalloc (sizeof (struct gdbarch_tdep));
  gdbarch = gdbarch_alloc (&info, tdep);
  tdep->elf_flags = elf_flags;

  switch (info.bfd_arch_info->arch)
    {
    case bfd_arch_zpu:
      set_gdbarch_addr_bit (gdbarch, 32);
      set_gdbarch_pc_regnum (gdbarch, HARD_PC_REGNUM);
      set_gdbarch_num_regs (gdbarch, ZPU_NUM_REGS);
      break;

    default:
      break;
    }

  set_gdbarch_short_bit (gdbarch, 16);
  set_gdbarch_int_bit (gdbarch, 32);
  set_gdbarch_float_bit (gdbarch, 32);
  set_gdbarch_double_bit (gdbarch, 64 );
  set_gdbarch_long_double_bit (gdbarch, 64);
  set_gdbarch_long_bit (gdbarch, 32);
  set_gdbarch_ptr_bit (gdbarch, 32);
  set_gdbarch_long_long_bit (gdbarch, 64);

  /* Characters are unsigned.  */
  set_gdbarch_char_signed (gdbarch, 0);

  set_gdbarch_skip_prologue (gdbarch, zpu_skip_prologue);
  set_gdbarch_write_pc (gdbarch, generic_target_write_pc);

	/* frame stuff */
  frame_unwind_append_sniffer (gdbarch, dwarf2_frame_sniffer);

  set_gdbarch_unwind_pc (gdbarch, zpu_unwind_pc);
  set_gdbarch_unwind_sp (gdbarch, zpu_unwind_sp);

	/* register stuff */
  set_gdbarch_sp_regnum (gdbarch, HARD_SP_REGNUM);
  set_gdbarch_register_name (gdbarch, zpu_register_name);
  set_gdbarch_register_type (gdbarch, zpu_register_type);

  set_gdbarch_return_value (gdbarch, zpu_return_value);
  set_gdbarch_inner_than (gdbarch, core_addr_lessthan);
  set_gdbarch_breakpoint_from_pc (gdbarch, zpu_breakpoint_from_pc);
  set_gdbarch_print_insn (gdbarch, gdb_print_insn_zpu);
  return gdbarch;
}

extern initialize_file_ftype _initialize_zpu_tdep; /* -Wmissing-prototypes */

void
_initialize_zpu_tdep (void)
{
  register_gdbarch_init (bfd_arch_zpu, zpu_gdbarch_init);
} 
