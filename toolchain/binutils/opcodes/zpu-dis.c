/* Disassemble Zylin ZPU instructions.
   Copyright 1995, 1998, 2000, 2001, 2002 Free Software Foundation, Inc.

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

#include <stdio.h>
#include "sysdep.h"
#define STATIC_TABLE
#define DEFINE_TABLE

#include "opcode/zpu.h"
#include "zpu-opc.h"
#include "dis-asm.h"

static fprintf_ftype fpr;
static void *stream;
static struct disassemble_info *local_info;





#define GETINFO(size,type,pcrel)\
	case ADDR_PCREL: size = 0;type=-1;pcrel=1;break;\
	case ADDR_IMMEDIATE: size = 0;type=-1;pcrel=0;break;\
	case ADDR_IMPLIED: size = 0;type=-1;pcrel=0;break;\



static void print_operand PARAMS ((int, char *, unsigned int *));

static void
print_operand (lookup, format, args)
     int lookup;
     char *format;
     unsigned int *args;
{
  int val;
  int c;

  while (*format)
    {
      switch (c = *format++)
	{
	case '$':
	  val = args[(*format++) - '0'];
	  if (lookup)
	    {
#if 0
	      name = findname (val);
	      if (name)
		fpr (stream, "%s", name);
	      else
#endif
		local_info->print_address_func (val, local_info);
	    }
	  else
	    fpr (stream, "0x%x", val);

	  break;
	default:
	  fpr (stream, "%c", c);
	  break;
	}
    }
}

int
print_insn_zpu (memaddr, info)
     bfd_vma memaddr;
     struct disassemble_info *info;
{
  int status = 0;
  unsigned char insn[4];
  const struct zpu_opcode *op=NULL;
  int i;
  int args[2];
  stream = info->stream;
  fpr = info->fprintf_func;
  local_info = info;
  for (i = 0; i < 4 && status == 0; i++)
    {
      status = info->read_memory_func (memaddr + i, insn + i, 1, info);
    }

	  for (i=0; i<zpu_num_opcodes; i++)
	  {
	  	if ((zpu_opcodes[i].code==insn[0])||((zpu_opcodes[i].code&insn[0]&0x80)!=0))
	  	{
	  		op=zpu_opcodes+i;
	  		break;
	  	}
	  }

	if ((insn[0]>=ZPU_storesp)&&(insn[0]<ZPU_storesp+32))
	{
		fpr (stream, "storesp %d", ((insn[0]-ZPU_storesp)^0x10)*4);
	} else if ((insn[0]>=ZPU_loadsp)&&(insn[0]<ZPU_loadsp+32))
	{
		fpr (stream, "loadsp %d", ((insn[0]-ZPU_loadsp)^0x10)*4);
	} else
	{
		switch (insn[0])
		{
			case ZPU_addsp:
			case ZPU_addsp+1:
			case ZPU_addsp+2:
			case ZPU_addsp+3:
			case ZPU_addsp+4:
			case ZPU_addsp+5:
			case ZPU_addsp+6:
			case ZPU_addsp+7:
			case ZPU_addsp+8:
			case ZPU_addsp+9:
			case ZPU_addsp+10:
			case ZPU_addsp+11:
			case ZPU_addsp+12:
			case ZPU_addsp+13:
			case ZPU_addsp+14:
			case ZPU_addsp+15:
			  fpr (stream, "addsp %d", (insn[0]-ZPU_addsp)*4);
			break;
			
				
				
			default:
				if (op==NULL)
				{
					  fpr (stream, ".byte %d", insn[0]);
				} else if ((insn[0]&0x80)!=0)
				{
					int t;\
				  	t=(int)((signed char)((insn[0]<<1)&0xff));\
			  		t>>=1;\
					
					fpr (stream, "im %d", t);
				} else
				{
				  fpr (stream, "%s", op->name);
				
				  /* Prepare all the posible operand values.  */
				  {
				  	int size=1;
				    switch (op->amode)
				      {
					  case ADDR_IMMEDIATE:
					  {
					  	int t;
					  	t=(int)((signed char)((insn[0]<<1)&0xff));
					  	t>>=1;
						args[0] = t;
						print_operand (0, "	$0", args);
						size += 0;
					  }
						break;
					  case ADDR_IMPLIED:
							size += 0;
						break;
				      }
				  }
				}
			  break;
		}
	}
    return 1; // size is always 1
}
