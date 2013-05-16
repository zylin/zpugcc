/* Subroutines used for code generation on transputer.
   Copyright (C) 1992, 1993, 1994, 1995 Free Software Foundation, Inc.

   Written by Øyvind Harboe <oyvind.harboe@zylin.com>

This file is part of GNU CC.

GNU CC is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2, or (at your option)
any later version.

GNU CC is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with GNU CC; see the file COPYING.  If not, write to
the Free Software Foundation, 59 Temple Place - Suite 330,
Boston, MA 02111-1307, USA.  */

#include <stdio.h>
#include <limits.h>
#include "config.h"
#include "system.h"
#include "coretypes.h"
#include "tm.h"
#include "rtl.h"
#include "tree.h"
#include "tm_p.h"
#include "regs.h"
#include "real.h"
#include "insn-config.h"
#include "insn-flags.h"
#include "expr.h"
#include "recog.h"
#include "reload.h"
#include "output.h"
#include "hard-reg-set.h"
#include "real.h"
#include "insn-config.h"
#include "conditions.h"
#include "output.h"
#include "insn-attr.h"
#include "flags.h"
#include "libfuncs.h"
#include "toplev.h"
#include "basic-block.h"
#include "function.h"
#include "ggc.h"

#include "target.h"
#include "target-def.h"

const char *zpu_board_name;



static const int MAX_ADDSP=15*4;
/* GCC's concept of registers and the ZPU's concept of registers sometimes,
 * but not always refer to the same
 * 
 * Hence we have a table of rtx expressions that redirect to the correct
 * location 
 */
static GTY(()) rtx reg[R_NUM];
static unsigned int regStackTop;

static int regMapper[R_NUM-R_STACK_REG];
static int debug_output=0;
static rtx current_insn;
static int stackOffset; /* when the RTL references the SP, we need to track the offset */

#define missingOperand() \
{\
		fprintf(stderr, "Instruction emit failure:\n"); \
		debug_rtx (current_insn); \
		fprintf(stderr, "\n"); \
		abort(); \
}

static int zpu_first_only_push(rtx x, rtx find);
static int loadstoresp_offset(rtx operand, int *found);
static void zpu_storesp(int offset);
static int prevImmediate;
static void zpu_asm(const char *format, rtx *operands);
static void store_to_operand(rtx *operand);
static void zpu_loadsp(int offset);
static const char *zpu_immediate(rtx *operand);
static int calcStackRegSize(void);
static int totalStackOffset(void);

static int stackSlotNum(int regNo)
{
	if (regMapper[regNo-R_STACK_REG]==-1)
	{
		missingOperand();
	}
	return regMapper[regNo-R_STACK_REG];
}

/* sp + offset to stack register */
static int stackRegOffset(rtx operand)
{
	int num;
	num=stackSlotNum(REGNO(operand));
	return current_function_outgoing_args_size+num*4-totalStackOffset();
}

static int addSpRange(rtx operand, int *found)
{
	*found=0;
	
	if (current_function_calls_alloca)
	{
		/* no way to know in this case */
		return -1;
	}
	
	if ((GET_CODE(operand)==REG)&&(REGNO(operand)<R_NUM))
	{
		if (GET_CODE(reg[REGNO(operand)])==MEM)
		{
			return loadstoresp_offset(reg[REGNO(operand)], found)-totalStackOffset();
		} else
		{
			if ((REGNO(operand)>=R_STACK_REG)&&
				(REGNO(operand)<=R_STACK_REG_LAST))
			{
				*found=1;
				return stackRegOffset(operand);
			}
		}
	} else 
	{
		return loadstoresp_offset(operand, found)-totalStackOffset();
	}
	return -1;
}

static void pushHardReg(rtx reg)
{
	rtx regAddr=GEN_INT(REGNO(reg)*4);

	if (TARGET_MEMREG)
	  {
	zpu_asm("im _memreg+%0", &regAddr);
	zpu_asm("load", NULL);
	  } else
	    {
	zpu_asm("im %0", &regAddr);
  zpu_asm("im _regpush", NULL);
  zpu_asm("call", NULL);
	    }

}

static void pushRegAddress(rtx operand)
{
	/* painful handling of compatiblity with obscure case
	 * of alloca or dynamically sized objects on stack
	 */
	int num;
	rtx offset;
	
	num=stackSlotNum(REGNO(operand));
	pushHardReg(hard_frame_pointer_rtx);
	offset=GEN_INT(-(get_frame_size()+calcStackRegSize())+num*4);
	zpu_immediate(&offset);
	stackOffset+=4;
	zpu_asm("add", NULL);
}


static void pushreg(rtx operand)
{
	if (REGNO(operand)<R_STACK_REG)
	{
		if (REGNO(operand)<R_NUM)
		{
		  pushHardReg(operand);
		} else
		{
			missingOperand();
		}
	} else if (REGNO(operand)<R_NUM)
	{
		if (current_function_calls_alloca)
		{
			pushRegAddress(operand);
			zpu_asm("load", NULL);
		} else
		{
			int num;
			num=stackSlotNum(REGNO(operand));
			zpu_loadsp(current_function_outgoing_args_size+num*4);
			stackOffset+=4;
		}
	} else
	{
		missingOperand();
	}
}

static void popHardReg(rtx reg)
{
  rtx addr;
  addr=GEN_INT(REGNO(reg)*4);

  if (TARGET_MEMREG)
    {
  zpu_asm("im _memreg+%0", &addr);
  zpu_asm("store", NULL);
    } else
      {
  zpu_asm("im %0", &addr);
  zpu_asm("im _regpop", NULL);
  zpu_asm("call", NULL);

      }

}

static void popreg(rtx operand)
{
	if (REGNO(operand)<R_STACK_REG)
	{
		if (REGNO(operand)<R_NUM)
		{
		  popHardReg(operand);
		}
	} else if (REGNO(operand)<R_NUM)
	{
		if (current_function_calls_alloca)
		{
			pushRegAddress(operand);
			zpu_asm("store", NULL);
		} else
		{
			int num;
			num=stackSlotNum(REGNO(operand));
			zpu_storesp(current_function_outgoing_args_size+num*4);
		}
	} else
	{
		missingOperand();
	}
}


/* returns true if both are registers and they are the same register*/
static int compareReg(rtx a, rtx b)
{
	if (GET_CODE(a)!=REG)
	{
		return 0;
	}
	if (GET_CODE(b)!=REG)
	{
		return 0;
	}	
	
	return REGNO(a)==REGNO(b);
}

static void comment(const char *format ATTRIBUTE_UNUSED, rtx *operands ATTRIBUTE_UNUSED)
{
#if 0
	/* the testsuite chokes on this */
	output_asm_insn(format, operands);
#endif
}

const char * zpu_asm_multi(const char *format, rtx *operands, int byteCount ATTRIBUTE_UNUSED)
{
	int im;
	/* imX, matches IM & IMPCREL */
	im=strncmp("im", format, 2)==0;
	
	if (im&&prevImmediate)
	{
		/* we need to break the pipe when two immediate instructions follow eachother */
		output_asm_insn("nop", operands);
	}
	output_asm_insn(format, operands);
	
	prevImmediate=im;
	return "";
}

static void zpu_asm(const char *format, rtx *operands)
{
	zpu_asm_multi(format, operands, 1);
}



struct RegStackEntry GTY(())
{
	rtx reg; /* the current location of the register */
};

static GTY(()) struct RegStackEntry regStack[R_NUM*2];
static const unsigned int regStackSize=sizeof(regStack)/sizeof(*regStack);

static rtx next_insn_saved;
static rtx current_insn_saved;

static void storeToReg(rtx newLocation, rtx origReg)
{
	comment("; explicit pop", &newLocation);
	if (GET_CODE(newLocation)==REG)
	{
		popreg(newLocation);
	} else
	{
		int found;
		int loadsp_offset=loadstoresp_offset(newLocation, &found);
		if (!found)
		{
			fprintf(stderr, "\nZPU: corrupt regStack\n");
			missingOperand();
		}
		
		comment("; store to register on stack %0", &origReg);
		zpu_storesp(loadsp_offset);
	}
}


static void persistReg(rtx t)
{
	storeToReg(reg[REGNO(t)], t);
 	stackOffset+=4;
}


static void discardRegStackTop(int persist)
{
	rtx newLocation;
	int i;
	if ((regStackTop>regStackSize)||(regStackTop<=0))
	{
		fprintf(stderr, "ZPU: corrupt regStack\n");
		missingOperand();
	}

	/* this is where we pop the register to... */
	newLocation=gen_rtx_REG(SImode, REGNO(regStack[regStackTop-1].reg));
	
	/* ...or is it still on the stack? */
	for (i=regStackTop-2; i>=0; i--)
	{
		if (compareReg(regStack[regStackTop-1].reg, regStack[i].reg))
		{
			newLocation=gen_rtx_MEM(SImode, 
				gen_rtx_PLUS(SImode, gen_rtx_REG(SImode, R_SP), GEN_INT(-(i+1)*4)));
			break;
		}
	}
	
	reg[REGNO(regStack[regStackTop-1].reg)]=newLocation;
	
	if (persist)
	{
		/* pop the register into the current location */
		storeToReg(newLocation, regStack[regStackTop-1].reg);
	}

	regStackTop--;
}

static void popRegStack(void)
{
	discardRegStackTop(1);
}

static void pushRegStack(rtx t)
{
	if (regStackTop>=regStackSize)
	{
		fprintf(stderr, "ZPU: corrupt regStack\n");
		missingOperand();
	}
	
	regStack[regStackTop].reg=t;
	regStackTop++;
	
	/* GCC does not know that we are changing the stack pointer.
	 * 
	 * Hence the saved registers are at a negative offset to GCC's concept of 
	 * SP
	 */
	reg[REGNO(t)]=gen_rtx_MEM(SImode, 
		gen_rtx_PLUS(SImode, gen_rtx_REG(SImode, R_SP), GEN_INT(-regStackTop*4)));
}


static int zpu_noop_set(rtx insn)
{
	rtx set;
	set=single_set(insn);
	if (set!=NULL_RTX)
	{
		return 
		    GET_CODE (SET_SRC (set)) == REG
	    && GET_CODE (SET_DEST (set)) == REG
	    && REGNO (SET_SRC (set)) == REGNO (SET_DEST (set));
	}
	return 0;
}

static int zpu_can_be_split(rtx insn)
{
	rtx set;
	set=single_set(insn);
	if (set!=NULL_RTX)
	{
		return (GET_MODE(SET_SRC (set)) != SImode);
	}
	return 0;
}


/* it is safe to err on the side of caution here and return 0
 * if we don't know.
 */
static rtx zpu_next_insn(rtx insn)
{
  while (insn)
    {
      insn = NEXT_INSN (insn);
      switch (GET_CODE(insn))
      {
      	case JUMP_INSN:
      	return insn;
      	
      	case INSN:
			if (zpu_noop_set(insn))
			{
		      	/* DRAGONS! we must skip noop moves, because they 
		      	 * are eliminated by the emitter
		      	 */
		      	 break;
  	        }
  	        
  	        if (zpu_can_be_split(insn))
  	        {
  	        	return NULL;
  	        }

			return insn;

		/* skip */      	
		case NOTE:
      	break;
      	
      	default:
      	/* we don't handle these */
      	return NULL;
      }
    }

  return insn;
}

static int stackPlusConst(rtx operand, int *found) 
{
	rtx op0,op1;
	*found=0;
	if(GET_CODE(operand) != PLUS)
	{
		return 0;
	}
	op0=XEXP (operand, 0);
	op1=XEXP (operand, 1);
	if((GET_CODE(op0)==REG) &&(REGNO(op0)==R_SP)
					&& (GET_CODE(op1)==CONST_INT))
	{
		*found=1;
		return INTVAL(op1);
	}
	if((GET_CODE(op1)==REG) &&(REGNO(op1)==R_SP)
					&& (GET_CODE(op0)==CONST_INT))
	{
		*found=1;
		return INTVAL(op0);
	}
	return 0;
}

static int loadstoresp_offset(rtx operand, int *found) 
{
	*found=0;
	if (GET_MODE(operand)!=SImode)
	{
		return -1;
	}
	if (GET_CODE(operand)!=MEM)
	{
		return -1;
	}
	operand=XEXP(operand, 0);
	
	if ((GET_CODE(operand)==REG)&&(REGNO(operand)==R_SP))
	{
		*found=1;
		return 0;
	}
	return stackPlusConst(operand, found);
}



int zpu_binary_operator (rtx op  ATTRIBUTE_UNUSED, enum machine_mode mode ATTRIBUTE_UNUSED)
{
	if (GET_MODE(op)!=SImode)
	{
		return 0;
	}
	
	switch (GET_CODE(op))
	{
		case LE:
		case GE:
		case LEU:
		case GEU:
		case GT:
		case LT:
		case GTU:
		case LTU:
	    case COMPARE:
	    case ASHIFT:
	    case XOR:


		case IOR:
		case AND:
		case MINUS:
		case PLUS:

		return 1;
	    case ASHIFTRT:
	      return TARGET_ASHIFTRT;
	    case LSHIFTRT:
	      return TARGET_LSHIFTRT;
		case MULT:
		  return TARGET_MULT;
		case DIV:
		  return TARGET_DIV;
		case MOD:
		  return TARGET_MOD;
		
		default:
		break;
	}
	return 0;
}


	
		
int zpu_unary_operator (rtx op  ATTRIBUTE_UNUSED, enum machine_mode mode ATTRIBUTE_UNUSED)
{
	if (GET_MODE(op)!=SImode)
	{
		return 0;
	}
	
	switch (GET_CODE(op))
	{
		case NEG:
		case NOT:
		return 1;
		
		default:
		break;
	}
	return 0;
}

static int countReg;

static int opCheckTerminal(rtx op, enum machine_mode mode ATTRIBUTE_UNUSED, int strict)
{
	if (CONSTANT_P(op)&&(GET_CODE(op)!=CONST_DOUBLE))
	{
		return 1;
	}
	
	switch (GET_CODE(op))
	{
	    case REG:
	    	if ((REGNO(op)<FIRST_PSEUDO_REGISTER)||!strict)
	    	{
	    		if ((REGNO(op)!=R_PC)&&(REGNO(op)!=R_SP))
	    		{
		    		countReg++;
	    		}
	    		return 1;
	    	}
	    	break;

	    default:
	    break;
	}

  	return 0;
}

/* This function is not about what the ZPU is capable of, but what
 * the GCC & the backend wants/needs.
 */
static int opCheck(rtx op, enum machine_mode mode, int strict)
{
	switch (GET_CODE(op))
	{
		/* we support only *2,4,8 */
	    case MULT:
	    	if (opCheckTerminal(XEXP(op, 0), mode, strict))
	    	{
				if (GET_CODE(XEXP(op, 1))==CONST_INT)
				{
					int c=INTVAL(XEXP(op, 1));
					if ((c==2)||(c==4)||(c==8))
					{
						return 1;
					}
				}
	    	}
	    	return 0;
	    case PLUS:
	    	return opCheckTerminal(XEXP(op, 0), mode, strict)&&
	    	opCheckTerminal(XEXP(op, 1), mode, strict);

	    case PRE_DEC:
	    	if (REG_P(XEXP(op, 0))&&(REGNO(XEXP(op, 0))==R_SP))
	    	{
	    		return 1;
	    	}
	    	break;
	    	
	    case POST_INC:
	    	if (((mode==DFmode)||(mode==DImode))&&
		    	REG_P(XEXP(op, 0))&&
		    	(REGNO(XEXP(op, 0))==R_SP))
	    	{
	    		return 1;
	    	}
	    	
	    	if ((mode!=SImode)&&(mode!=HImode)&&(mode!=QImode))
	    	{
	    		return 0;
	    	}
	    	if (REG_P(XEXP(op, 0))&&
	    	((REGNO(XEXP(op, 0))<=R_SP)
	    	||
	    	(!strict&&(REGNO(XEXP(op, 0))>=FIRST_PSEUDO_REGISTER))
	    	
	    	))
	    	
	    	{
	    		return 1;
	    	}
	    	break;

	    default:
	    return opCheckTerminal(op, mode, strict);
	}

  	return 0;
}



int zpu_legitimate_address(enum machine_mode mode ATTRIBUTE_UNUSED, rtx x ATTRIBUTE_UNUSED, int strict ATTRIBUTE_UNUSED)
{
	countReg=0;
	
	if (opCheck(x, SImode, strict))
	{
		return countReg<MAX_REGS_PER_ADDRESS;
	}
	return 0;
}

void print_operand (FILE *file, rtx op, int letter)
{
	
	if (letter=='R')
	{
		print_rtl (file, op);
		return;
	}
	
	switch (GET_CODE (op))
	{
		case PLUS: 
		print_operand(file, XEXP(op, 0), letter);
		fprintf(file, "+");
		print_operand(file, XEXP(op, 1), letter);
		break;
		case REG: 
			if (letter=='X')
			{
		    	fprintf(file, "%d", REGNO(op)*4);
			} else
			{
		    	fprintf(file, "%s", reg_names[REGNO (op)]);
			}
	    	break;
	    	
	    case CONST_DOUBLE:
	    {
	    	if (GET_MODE(op)==SFmode)
	    	{
			      REAL_VALUE_TYPE r;
			      long l;
			
			      REAL_VALUE_FROM_CONST_DOUBLE (r, op);
			      REAL_VALUE_TO_TARGET_SINGLE (r, l);
			      asm_fprintf (file, "%I0x%lx", l);
	    	}
	    	#if 0 
	    	else if (GET_MODE(op)==DFmode)
	    	{
			      REAL_VALUE_TYPE r;
			      long l[2];
			
			      REAL_VALUE_FROM_CONST_DOUBLE (r, op);
			      REAL_VALUE_TO_TARGET_DOUBLE (r, l);
			      asm_fprintf (file, "0x%08x%08x", l[0], l[1]);
	    	} 
	    	#endif
	    	else
	    	{
				output_addr_const(file, op);
	    	}
	    	break;
	    }
	    case CONST_INT:
	    	fprintf(file, "%d", (int)INTVAL (op));
			break;
			
	    case LABEL_REF:
	    case SYMBOL_REF:
		case CODE_LABEL:
	    	output_addr_const(file, op);
			break;
			
		case MEM:
			if (letter!='X')
			{
				fprintf(file, "(");
			}
			print_operand(file, XEXP (op, 0), letter);
			if (letter!='X')
			{
				fprintf(file, ")");
			}
			break;
			
			
		default:
			output_addr_const(file, op);
			break;
	}
}






static void initGenerate(rtx insn  ATTRIBUTE_UNUSED)
{
	current_insn=insn;

	if ((next_insn_saved!=NULL) && (current_insn!=next_insn_saved))
	{
		rtx t;
		fprintf(stderr, "ZPU: zpu_next_insn() broken\n");
		
		debug_rtx(current_insn_saved);
		
		/* for debugging purposes it is useful to look this up again so as
		 * to be able to step through the code
		 */
		t=zpu_next_insn(current_insn_saved);
		
		missingOperand();
	}
	
	stackOffset=0;
}

static int totalStackOffset(void)
{
	int t;
	/* this is the absolute difference between the ZPU stack
	 * pointer and GCC's concept of a stack pointer
	 */
	t=stackOffset-regStackTop*4;
	if (t>0)
	{
		fprintf(stderr, "ZPU: illegal stack offset %d\n", -t);
		missingOperand();
	}
	return t;
}

static void zpu_pushspadd(int offset) 
{
  rtx t;
	if (TARGET_PUSHSPADD)
	{
		t=GEN_INT((offset+4)/4);
		zpu_asm("im %0", &t);
		zpu_asm("pushspadd", &t);
	} else
	{
		t=GEN_INT(offset);
		zpu_asm("pushsp", &t);
		if (offset!=0)
		  {
		    zpu_asm("im %0", &t);
		    zpu_asm("add", &t);
		  }
	}
}

static void zpu_addsp(int offset) 
{
  rtx t;
		t=GEN_INT(offset);
			if (TARGET_ADDSP)
			  {
			    zpu_asm("addsp %0", &t);
			  } else
			    {
			    zpu_asm("pushsp", NULL);
			    if (offset!=0)
			      {
			    zpu_asm("im %0", &t);			    
			    zpu_asm("add", NULL);			    
			      }
			    zpu_asm("load", NULL);			    
			    zpu_asm("add", NULL);
			    }
}

static void zpu_coreloadsp(int offset)
{
  rtx t;
	if (offset<0)
	{
		missingOperand();
	}

	t=GEN_INT(offset);
	if (TARGET_LOADSP&&(offset/4<32))
	{
		zpu_asm("loadsp %0", &t);
	} else
	{
		zpu_pushspadd(offset);
		zpu_asm("load", &t);
	}
  
}


static void zpu_loadsp(int offset) 
{

	offset-=totalStackOffset();

	zpu_coreloadsp(offset);
	stackOffset-=4;
}


static void zpu_storesp(int offset) 
{
	rtx t;
	offset-=totalStackOffset();
	
	if (offset<0)
	{
		missingOperand();
	}
	
	if (TARGET_STORESP&&(offset/4<32))
	{
		t=GEN_INT(offset);
		zpu_asm("storesp %0", &t);
	} else
	{
		zpu_pushspadd(offset);
		zpu_asm("store", &t);
	}
}



static int zpu_stack_change(rtx x)
{
	rtx set;
	set=single_set(x);
	if (set!=NULL_RTX)
	{
		rtx dest=SET_DEST(set);
		rtx src=SET_SRC(set);
		if ((GET_CODE(dest)==REG)&&(REGNO(dest)==R_SP))
		{
			return 1;
		}
		
		if (GET_CODE(dest)==MEM)
		{
			if (GET_CODE(XEXP(dest, 0))==PRE_DEC)
			{
				if (REG_P(XEXP(XEXP(dest, 0), 0))&&REGNO(XEXP(XEXP(dest, 0), 0))==R_SP)
				{
					return 1;
				}
			}
		}
		if ((GET_CODE(dest)==REG)&&(REGNO(dest)==R_SP))
		{
			return 1;
		}
		if (GET_CODE(src)==MEM)
		{
			if (GET_CODE(XEXP(src, 0))==POST_INC)
			{
				if (REG_P(XEXP(XEXP(src, 0), 0))&&REGNO(XEXP(XEXP(src, 0), 0))==R_SP)
				{
					return 1;
				}
			}
		}
	}
	return 0;
}


static int isInBasicBlock(rtx insn)
{
	if (insn==NULL_RTX)
	{
		return 0;
	}
	if (GET_CODE(insn)==INSN)
	{
		if (!zpu_stack_change(insn))
		{
			rtx set;
			set=single_set(insn);
			if (set!=NULL_RTX)
			{
				if (GET_CODE(SET_SRC(set))!=ASM_OPERANDS)
				{
					return 1;
				}
			}
		}
	}
	return 0;
}




static void cleanupGenerate(void)
{
	rtx t;
	if (stackOffset!=0)
	{
		fprintf(stderr, "ZPU: stackOffset %d\n", stackOffset);
		missingOperand();
	}

	/* purge all dead registers off the stack */
	while ((regStackTop>0)&&find_regno_note(current_insn, REG_DEAD, REGNO(regStack[regStackTop-1].reg)))
	{
		popRegStack();
	}

	/* if we are at the end of the basic block, we must clean up
	 * any unpopped registers
	 */
	t=zpu_next_insn (current_insn);
	next_insn_saved=NULL_RTX;
	current_insn_saved=current_insn;
	
	if (isInBasicBlock(t))
	{
		next_insn_saved=t;
	} else
	{
		comment("; barrier, purge regstack", &current_insn);
		while (regStackTop>0)
		{		
			popRegStack();
		}
	}
}


static void push_operand_address(rtx *operand);
static void push_operand_value(rtx *operand);


static const char *zpu_immediate(rtx *operand)
{
	zpu_asm("im %0", operand);
	stackOffset-=4;
	return "";
}

static void zpu_neg(rtx *operand)
{
  if (TARGET_NEG)
    {
	zpu_asm("neg", operand);
    } else
      {
	/* FIX!!! is this the right sequence? */
   	/* No, it wasn't, "Not" should come first - AMR.*/ 
	zpu_asm("not", operand);
	zpu_asm("im 1", operand);
	zpu_asm("add", operand);
      }
}


/* is "find" the first operand to be pushed in "x".
 * 
 * It is safe to err on the side of caution and say "no", it will
 * only potentially make the code ever so slightly less efficient.
 */
static int zpu_first_push(rtx x, rtx find)
{
  int i, j; 
  enum rtx_code code;
  const char *format_ptr;
  int count;
  
  if (x==NULL)
  	return 0;

	if (CONSTANT_P(x))
	{
		return 0;
	}


	code=GET_CODE(x);
  switch (code)
    {
    	case EXPR_LIST:
    	return 0;
    	
    	case SET:
    		return zpu_first_push(SET_SRC(x), find);

		case PLUS:
		case XOR:
		case AND:
		case IOR:
		return zpu_first_push(XEXP(x, 0), find)||zpu_first_push(XEXP(x, 1), find);

		case REG:
		return (x==find);
		
		/* these are handled by the generic code below */
		case INSN:
		break;
		
    	default:
    	/* err on the side of caution */
    	return 0;
    }


  format_ptr = GET_RTX_FORMAT (code);
  count = 0;

  for (i = 0; i < GET_RTX_LENGTH (code); i++) 
    {
      switch (*format_ptr++)
	{
	case 'e':
	  return zpu_first_push (XEXP (x, i), find);

	case 'E':
 	  for (j = 0; j < XVECLEN (x, i); j++)
	    return zpu_first_push (XVECEXP (x, i, j), find);
	}
    }
  return 0;
}

static void zpu_call_asm(void)
{
  if (TARGET_CALL)
    {
   zpu_asm("call", NULL);
    } else
      {
	
   zpu_asm("pushsp ; CALL insn - duplicate top of stack", NULL);
   zpu_asm("load", NULL);
   zpu_asm("im 6 ; post POPC address", NULL);
   zpu_asm("pushpc", NULL);
   zpu_asm("add", NULL);
   zpu_asm("pushsp", NULL);
   zpu_asm("im 4", NULL);
   zpu_asm("add", NULL);
   zpu_asm("store", NULL);
   zpu_asm("poppc ; call function ", NULL);
   
      }
}


static void zpu_gen_call(rtx *operand)
{
	comment("/* call %R0 */", operand);

	if (GET_CODE(operand[0])!=MEM)
	{
		missingOperand();
	}

	if (TARGET_CALLPCREL&&CONSTANT_P(XEXP(operand[0], 0)))
	{
		zpu_asm("impcrel %0", operand);
		zpu_asm("callpcrel", operand);
	} else
	{
		/* address to call... */
		push_operand_address(operand);
	
		if (regStackTop!=0)
		{
			fprintf(stderr, "ZPU: regStackTop %d\n", regStackTop);
			missingOperand();
		}
		zpu_call_asm();


		stackOffset+=4;
	}
}


static int
zpu_count_occurrences (rtx x, rtx find)
{
  int i, j;
  enum rtx_code code;
  const char *format_ptr;
  int count;
  
  if (x==NULL)
  	return 0;

	code=GET_CODE(x);
  switch (code)
    {
    	case EXPR_LIST:
    	return 0;
    	default:
    	break;
    }

  if ((GET_CODE(x) == REG)&&(REGNO(x)==REGNO(find)))
    return 1;


  format_ptr = GET_RTX_FORMAT (code);
  count = 0;

  for (i = 0; i < GET_RTX_LENGTH (code); i++)
    {
      switch (*format_ptr++)
	{
	case 'e':
	  count += zpu_count_occurrences (XEXP (x, i), find);
	  break;

	case 'E':
	  for (j = 0; j < XVECLEN (x, i); j++)
	    count += zpu_count_occurrences (XVECEXP (x, i, j), find);
	  break;
	}
    }
  return count;
}

/* we must err on the side of caution here. */
static int zpu_first_only_push(rtx x, rtx find)
{
	int result=0;
	if (zpu_first_push(x, find))
	{
	  enum rtx_code code;
	  code=GET_CODE(x);
	  if (code==SET)
	  {
	  	x=SET_SRC(x);
	  }
		
		if (zpu_count_occurrences(x, find)==1)
		{
			result=1;
		}
	}
	return result;
}






/* if:
 * - the GCC-register is REG_DEAD or overwritten 
 * - the GCC-register is on top of the stack 
 * - the first push in the instruction is the GCC-register
 * - we only use the register once in the operation
 * 
 * then we can simply remove the instructions that pop/push
 */
static int dead_or_overwritten(rtx insn, rtx op)
{
	int result=0;
	if (find_regno_note(insn, REG_DEAD, REGNO (op)))
	{					
		result=1;
	} else 
	{
		rtx set = single_set (insn);
		if (set!=NULL_RTX)
		{
			if (SET_DEST(set)==op)
			{
				result=1;
			}
		}
	}
	
	return result;
}

/* Check if the operand on the regStack is one of the operands and
 * push it first 
 */
static void push_assosiative(rtx operand)
{
	if ((regStackTop>0)&&compareReg(regStack[regStackTop-1].reg, XEXP(operand, 1)))
	{
		push_operand_value(&XEXP(operand, 1));
		push_operand_value(&XEXP(operand, 0));
	} else
	{
		/* either this is the other correct way, or it doesn't matter which way we
		 * do it.
		 */
		push_operand_value(&XEXP(operand, 0));
		push_operand_value(&XEXP(operand, 1));
	}
}


static int isFreePopPush(rtx *operand)
{
	int freePopPush=0;
	if ((GET_CODE(*operand)==REG)&&(REGNO(*operand)<R_NUM)&&(GET_CODE(reg[REGNO(*operand)])==MEM))
	{
		/* the GCC-register must be on top of the stack for a free push */
		if (stackOffset==0)
		{
			if (regStackTop<=0)
			{
				fprintf(stderr, "ZPU: regStack corrupted\n");
				missingOperand();
			}
			
			if (dead_or_overwritten(current_insn, *operand))
			{
				if (zpu_first_only_push(current_insn, *operand))
				{
					comment("; stripping regstack until free pop&push is found %0", operand);
					/* strip the regstack until we have a free pop */
					while (!compareReg(regStack[regStackTop-1].reg, *operand))
					{
						popRegStack();
					}
	
					if (regStackTop<=0)
					{
						missingOperand();
					}
					comment("; eliminated pop&push %0", operand);
					if (debug_output)
					{
						fprintf(stderr, "ZPU: eliminated poppush!\n");
						debug_rtx (current_insn); 
					}
					freePopPush=1;
				}
			}
		}
	}
	return freePopPush;
}

static int postIncMemSize;
static void push_operand_value(rtx *operand)
{
	if (CONSTANT_P(*operand))
	{
		zpu_immediate(operand);
		return;
	} 


	if (GET_CODE(*operand)==REG)
	{
		if (REGNO(*operand)==R_PC)
		{
			zpu_asm("pushpc", operand);
			stackOffset-=4;
		} else if (REGNO(*operand)==R_SP)
		{
			zpu_asm("pushsp", operand);
			
			if (stackOffset>0)
			{
				missingOperand();
			}
			
			if (totalStackOffset()<0)
			{
				rtx offset=GEN_INT(-totalStackOffset());
				comment("; stack adjustment offset", &offset);
				zpu_asm("im %0", &offset);
				zpu_asm("add", operand);
			}
			
			stackOffset-=4;
		} else if (REGNO(*operand)<R_NUM)
		{
			/* push GCC-register */
			if (GET_CODE(reg[REGNO(*operand)])==MEM)
			{
				if (isFreePopPush(operand))
				{
					/* we pretend we pushed it into the stack and clear the top
					 * stack slot
					 */
					discardRegStackTop(0);
					stackOffset-=4;
				} else
				{
					comment("; referring to unpopped register %0", operand);
					if (debug_output)
					{
						fprintf(stderr, "ZPU: unpopped register\n");
						debug_rtx (reg[REGNO(*operand)]); 
					}
					push_operand_value(&reg[REGNO(*operand)]);
				}
			} else
			{
				pushreg(*operand);
				stackOffset-=4;
			}
		} else 
		{
			missingOperand();
		}
		return;
	} else if (GET_CODE (*operand) == POST_INC)
	{
		rtx reg;
		rtx size;
		reg=XEXP (*operand, 0);
		if (GET_CODE(reg)!=REG)
		{
			missingOperand();
		}
		
		if (REGNO(reg)>=R_SP)
		{
			missingOperand();
		}

		push_operand_value(&reg);

		zpu_coreloadsp(0);		
		stackOffset-=4;
		size=GEN_INT(postIncMemSize);
		zpu_asm("im %0", &size);
		zpu_asm("add", operand);
		
		/* we must not leave anything on the stack here */
		persistReg(reg);
	} else if (GET_CODE (*operand) == MEM)
	{
		int found;
		int loadsp_offset=loadstoresp_offset(*operand, &found);
		if ((GET_CODE(XEXP (*operand, 0))==POST_INC)&&(GET_CODE(XEXP (XEXP (*operand, 0), 0))==REG)&&(REGNO(XEXP (XEXP (*operand, 0), 0))==R_SP))
		{
			/* NOTE!!! We pop this off the stack even though it was placed there before we entered
			 * this tree expansion. */
			stackOffset-=4;
		} else if (found)
 		{ 
			zpu_loadsp(loadsp_offset);
		} else
		{
			postIncMemSize=GET_MODE_SIZE(GET_MODE(*operand));
			
			push_operand_value(&XEXP (*operand, 0));
			switch (GET_MODE(*operand))
			{
				case SFmode:
				case SImode:
					zpu_asm("load", operand);
					break;
				case HImode:
				  if (TARGET_SHORTOP)
				    {
					zpu_asm("loadh", NULL);
				    } else
				      {
					zpu_asm("im _loadh", NULL);
					zpu_call_asm();
				      }
					break;
				case QImode:
				  if (TARGET_BYTEOP)
				    {
					zpu_asm("loadb", NULL);
				    } else
				      {
					zpu_asm("im _loadb", NULL);
					zpu_call_asm();
				      }

					break;
				default:
					fprintf(stderr, "FIX!!!! miissing operand\n");
					print_rtl(stderr, *operand);
					fprintf(stderr, "\n");
					break;
			}
		}
	} else if (GET_CODE(*operand)==PLUS)
	{
		int found;
		int offset;
		offset=stackPlusConst(*operand, &found);
		if (found&&((offset%4)==0))
		{
			offset-=totalStackOffset();
			zpu_pushspadd(offset);
			stackOffset-=4;
		} else 
		if (isFreePopPush(&XEXP(*operand, 0))||isFreePopPush(&XEXP(*operand, 1)))
		{
			push_assosiative(*operand);
			zpu_asm("add", operand);
			stackOffset+=4;
		} else
		{
			offset=addSpRange(XEXP(operand[0], 0), &found);
			if ((!found)||((offset+4)>MAX_ADDSP))
			{
				push_operand_value(&XEXP(operand[0], 0));
				offset=addSpRange(XEXP(operand[0], 1), &found);
				if (found&&(offset<=MAX_ADDSP))
				{
					zpu_addsp(offset);
				} else
				{
					push_operand_value(&XEXP(operand[0], 1));
					zpu_asm("add", NULL);
					stackOffset+=4;
				}
			} else
			{
				push_operand_value(&XEXP(operand[0], 1));
				zpu_addsp(offset+4);
			}
		}
	} else if ((GET_CODE(*operand)==COMPARE)||(GET_CODE(*operand)==MINUS))
	{
		push_operand_value(&XEXP (*operand, 0));
		push_operand_value(&XEXP (*operand, 1));
		zpu_asm("sub", operand);
		stackOffset+=4;
	} else if (GET_CODE(*operand)==LABEL_REF)
	{
		zpu_immediate(operand);
	} else if (GET_CODE(*operand)==SYMBOL_REF)
	{
		zpu_immediate(operand);
	} else  if (GET_CODE(*operand)==CODE_LABEL)
	{
		zpu_immediate(operand);
	} else if (GET_CODE(*operand)==XOR)
	{
		push_assosiative(*operand);
		zpu_asm("xor", operand);
		stackOffset+=4;  /* lost one */
	} else if (GET_CODE(*operand)==AND)
	{
		push_assosiative(*operand);
		zpu_asm("and", operand);
		stackOffset+=4;  /* lost one */
	} else if (GET_CODE(*operand)==IOR)
	{
		push_assosiative(*operand);
		zpu_asm("or", operand);
		stackOffset+=4;  /* lost one */
	} else if (GET_CODE(*operand)==NOT)
	{
		push_operand_value(&XEXP (*operand, 0));
		zpu_asm("not", operand);
	} else if (GET_CODE(*operand)==NEG)
	{
		push_operand_value(&XEXP (*operand, 0));
		zpu_neg(operand);
	} else if ((GET_CODE(*operand)==EQ)||(GET_CODE(*operand)==NE))
	{
		push_operand_value(&XEXP (*operand, 0));
		push_operand_value(&XEXP (*operand, 1));
		if (TARGET_EQ)
		  {
		zpu_asm("eq", operand);
		  } else
		    {
		zpu_asm("im _eq", NULL);
		zpu_call_asm();
		    }
		if (GET_CODE(*operand)==NE)
		{   

			zpu_asm("not", operand);
			zpu_asm("im 1", operand);
			zpu_asm("and", operand);
		}
		stackOffset+=4;  /* lost one */
	} else if ((GET_CODE(*operand)==LE)||(GET_CODE(*operand)==GE)||
	           (GET_CODE(*operand)==LEU)||(GET_CODE(*operand)==GEU)||
	           (GET_CODE(*operand)==GT)||(GET_CODE(*operand)==LT)||
	           (GET_CODE(*operand)==GTU)||(GET_CODE(*operand)==LTU))
	{
		int sign;
		int flip_args;
		int equal;
		int code=GET_CODE(*operand);
		
		comment("/* %R0 */", operand);

		/* 'less than' is the base case here and then we tweak it into the 
		 * other cases
		 */
		sign        =(code==GE) || (code==LE) || (code==GT) || (code==LT);
		flip_args   =(code==GT) || (code==GE) || (code==GTU) || (code==GEU);
		equal       =(code==GE) || (code==LE) || (code==GEU) || (code==LEU);

		push_operand_value(&XEXP (*operand, flip_args?0:1)); /* b */
		push_operand_value(&XEXP (*operand, flip_args?1:0)); /* a */		
				
		if (!sign)
		{
			if (equal)
			{
			  if (TARGET_COMPARE)
			    {
				zpu_asm("ulessthanorequal", operand);
			    } else
			      {
				zpu_asm("im _ulessthanorequal", NULL);
				zpu_call_asm();
			      }
			} else
			{
			  if (TARGET_COMPARE)
			    {
				zpu_asm("ulessthan", operand);
			    } else
			      {
				zpu_asm("im _ulessthan", NULL);
				zpu_call_asm();
			      }
			}
		} else 
		{
			if (equal)
			{
			  if (TARGET_COMPARE)
			    {
				zpu_asm("lessthanorequal", operand);
			    } else
			      {
				zpu_asm("im _lessthanorequal", NULL);
				zpu_call_asm();
			      }
			} else
			{
			  if (TARGET_COMPARE)
			    {
				zpu_asm("lessthan", operand);
			    } else
			      {
				zpu_asm("im _lessthan", NULL);
				zpu_call_asm();
			      }
			}
		}
		
		stackOffset+=4;  /* lost one */
	} else if (GET_CODE(*operand)==LSHIFTRT)
	{
	  push_operand_value(&XEXP (*operand, 0));
	  push_operand_value(&XEXP (*operand, 1));
	  zpu_asm("lshiftright", operand);
	  stackOffset+=4;  /* lost one */
	} else if (GET_CODE(*operand)==ASHIFTRT)
	{
		push_operand_value(&XEXP (*operand, 0));
		push_operand_value(&XEXP (*operand, 1));
		zpu_asm("ashiftright", operand);
		stackOffset+=4;  /* lost one */
	} else if (GET_CODE(*operand)==ASHIFT)
	{
		if ((GET_CODE(XEXP (*operand, 1))==CONST_INT)&&(INTVAL(XEXP (*operand, 1))==1))
		{
			push_operand_value(&XEXP (*operand, 0));
			zpu_addsp(0); 
		} else
		{
			push_operand_value(&XEXP (*operand, 0));
			push_operand_value(&XEXP (*operand, 1));
			zpu_asm("ashiftleft", operand);
			stackOffset+=4;  /* lost one */
		}
	} else if (GET_CODE(operand[0])==MULT)
	{
		int mult=1;
		/* NOTE! This is a most crucial optimisation as MULT is used in
		 * address modes.
		 */
		if ((GET_CODE(XEXP(*operand, 1))==CONST_INT)) 
		{
			int c=INTVAL(XEXP(*operand, 1));
			if ((c==0)||(c==1))
			{
				missingOperand();
			}
			
			if ((c==2)||((optimize&&!optimize_size)&&((c==4)||(c==8))))
			{
				mult=0; 
				push_operand_value(&XEXP (*operand, 0));
				while (c>1)
				{
					zpu_addsp(0);
					c/=2;
				}
			}
		}
		
		if (mult)
		{		
			push_operand_value(&XEXP (*operand, 0));
			push_operand_value(&XEXP (*operand, 1));
			zpu_asm("mult", operand);
			stackOffset+=4;
		}
	} else if (GET_CODE(operand[0])==DIV)
	{
		push_operand_value(&XEXP (*operand, 1));
		push_operand_value(&XEXP (*operand, 0));
		zpu_asm("div", operand);
		stackOffset+=4;
	} else if (GET_CODE(operand[0])==MOD)
	{
		push_operand_value(&XEXP (*operand, 1));
		push_operand_value(&XEXP (*operand, 0));
		zpu_asm("mod", operand);
		stackOffset+=4;
	} else if (GET_CODE(operand[0])==ZERO_EXTEND)
	{
		push_operand_value(&XEXP (*operand, 0));
		if (GET_CODE(XEXP (*operand, 0))!=MEM)
		{
			switch (GET_MODE(XEXP (*operand, 0)))
			{
				case VOIDmode:
				/* its a bit silly to extend a VOIDmode, i.e. a constant,
				 * 
				 * This is a no-op.
				 */
				break;
				case QImode:
				zpu_asm("im 0xff", operand);
				zpu_asm("and", operand);
				break;
				case HImode:
				zpu_asm("im 0xffff", operand);
				zpu_asm("and", operand);
				break;
				default:
				missingOperand();
			}
		}
	} else 
	{
		print_rtl(stderr, *operand);
		missingOperand();
	}
}





/* even registers have addresses on a ZPU that we can push onto the stack */
static void push_operand_address(rtx *operand)
{
	if (GET_CODE (*operand) == MEM)
	{
		push_operand_value(&XEXP (*operand, 0));
	} else  if (GET_CODE(*operand)==SYMBOL_REF)
	{
		zpu_immediate(operand);
	}  else if (GET_CODE (*operand) == REG)
	{
		push_operand_value(operand);
	} else
	{
		missingOperand();
	}
}


static void store_to_operand(rtx *operand)
{
	if (GET_CODE(*operand)==PC)
	{
		zpu_asm("poppc ; jump", operand);
		stackOffset+=4;
	} else if (GET_CODE(*operand)==REG)
	{
		if (REGNO(*operand)==R_SP)
		{
			zpu_asm("popsp", operand);
			stackOffset+=4;
		} else if (REGNO(*operand)==R_PC)
		{
			zpu_asm("poppc ; jump", operand);
			stackOffset+=4;
		} else if (REGNO(*operand)<R_NUM)
		{
			if (regStackTop<regStackSize)
			{
				/* we always leave the value on the stack, if there is space
				 * 
				 * The cleanupGenerate() handles this case.
				 */
				comment("; left %0 on stack", operand);
				pushRegStack(*operand);
				stackOffset+=4;
			} else
			{
				comment("; regStack full", operand);
				persistReg(*operand);
			}
		} else
		{
			missingOperand();
		}
	} else if (GET_CODE(operand[0])==MEM)
	{
		int found;
		int loadsp_offset=loadstoresp_offset(*operand, &found);
		if ((GET_MODE(operand[0])!=SFmode)&&(GET_MODE(operand[0])!=SImode)&&(GET_MODE(operand[0])!=HImode)&&(GET_MODE(operand[0])!=QImode))
		{
			fprintf(stderr, "\nUnsupported dest\n");
			print_rtl (stderr, *operand);
			fprintf(stderr, "\n");
			abort();
		}
		
		
		if (GET_CODE(XEXP (operand[0], 0))==PRE_DEC)
		{
			rtx reg=XEXP(XEXP(operand[0], 0), 0);
			if (!REG_P(reg))
			{
				missingOperand();
			}
			if (REGNO(reg)==R_SP)
			{
				/* we've already pushed the result onto the stack. */
				/* we tell a small lie. We change the SP during tree expansion, but we intended to */
				stackOffset+=4;
			} else
			{
				missingOperand();
			}
		} else if (found)
 		{ 
			zpu_storesp(loadsp_offset);
			stackOffset+=4;
		} else
		{
			postIncMemSize=GET_MODE_SIZE(GET_MODE(*operand));
			
			push_operand_address(operand);
			switch (GET_MODE(operand[0]))
			{
				case SFmode:
				case SImode:
					zpu_asm("store", operand);
					break;
				case HImode:
				  if (TARGET_SHORTOP)
				    {
					zpu_asm("storeh", NULL);
				    } else
				      {
					zpu_asm("im _storeh", NULL);
					zpu_call_asm();
				      }
					break;
				case QImode:
				  if (TARGET_BYTEOP)
				    {
					zpu_asm("storeb", NULL);
				    } else
				      {
					zpu_asm("im _storeb", NULL);
					zpu_call_asm();
				      }

					break;
				default:
					fprintf(stderr, "FIX!!!! Missing operand\n");
					print_rtl(stderr, *operand);
					fprintf(stderr, "\n");
					break;
			}
			stackOffset+=8;
		}
	} else 
	{
		fprintf(stderr, "\nUnsupported dest\n");
		print_rtl (stderr, *operand);
		fprintf(stderr, "\n");
		abort();
		
		stackOffset+=4;
	}

}


const char *zpu_generate_move(rtx operands[], rtx insn ATTRIBUTE_UNUSED)
{
	initGenerate(insn);

	comment("/* move %R1, %R0 */", operands);

	/* first we push the source onto the stack, then we figure out the
	 * destination 
	 */
	push_operand_value(operands+1);
	
	store_to_operand(operands+0);

	cleanupGenerate();
		
	return "";
}

const char *zpu_generate_set(rtx insn)
{
	rtx set;
	initGenerate(insn);

	set=single_set(insn);
	comment("/* %R0 */", &set);

	/* first we push the source onto the stack, then we figure out the
	 * destination 
	 */
	push_operand_value(&SET_SRC(set));
	
	store_to_operand(&SET_DEST(set));
	
	cleanupGenerate();
		
	return "";
}

static void zpu_neqbranch(rtx operand)
{

  zpu_asm("impcrel %0", &operand);
  if (TARGET_NEQBRANCH)
    {

	zpu_asm("neqbranch", NULL);
    } else
      {
	zpu_asm("im _neqbranch", NULL);
	zpu_call_asm();
      }

}

const char *zpu_generate_if_then_else(rtx operands[], rtx insn ATTRIBUTE_UNUSED)
{
	initGenerate(insn);

	comment("/* if_then_else %R0 */", operands);
	
	/* evaluate boolean expression. this RTL contains the two suboperands */
	push_operand_value(&operands[0]);
	
	if (regStackTop!=0)
	{
		fprintf(stderr, "ZPU: regStackTop %d\n", regStackTop);
		missingOperand();
	}
	
	zpu_neqbranch(operands[3]);

	stackOffset+=4; 

	cleanupGenerate();
		
	return "";
}


const char *zpu_generate_if_not_zero_then_else(rtx operands[], rtx insn ATTRIBUTE_UNUSED)
{
	if ((GET_CODE(operands[2])!=CONST_INT)||INTVAL(operands[2])!=0)
	{
		return zpu_generate_if_then_else(operands, insn);
	} else
	{
		initGenerate(insn);
	
		/* evaluate boolean expression. this RTL contains the two suboperands */
		push_operand_value(&operands[0]);
		
		zpu_neqbranch(operands[1]);
		stackOffset+=4; 
	
		cleanupGenerate();
	}
		
	return "";
}


static const char *zpu_jump_core(rtx operands[], rtx insn ATTRIBUTE_UNUSED, int table)
{
	initGenerate(insn);
	comment("/* jump %R0 */", operands);

	/* put address on stack */	
	push_operand_value(operands+0);
	
	if (table)
	{
		comment("/* tablejump */", operands);
	}

	zpu_asm("poppc", operands);
	stackOffset+=4;

	cleanupGenerate();
	
	return "";
}

const char *zpu_jump(rtx operands[], rtx insn ATTRIBUTE_UNUSED)
{
	return zpu_jump_core(operands, insn, 0);
}

const char *zpu_table_jump(rtx operands[], rtx insn ATTRIBUTE_UNUSED)
{
	return zpu_jump_core(operands, insn, 1);
}


const char *zpu_jump_pcrel(rtx operands[], rtx insn ATTRIBUTE_UNUSED)
{
	initGenerate(insn);

	if (regStackTop!=0)
	{
		fprintf(stderr, "ZPU: regStackTop %d\n", regStackTop);
		missingOperand();
	}

	/* put address on stack */	
	if (TARGET_POPPCREL)
	  {
	zpu_asm("impcrel %0", operands);
	zpu_asm("poppcrel", operands);
	  } else
	    {
	zpu_asm("im %0", operands);
	zpu_asm("poppc", NULL);
	    }
	
	cleanupGenerate();
	
	return "";
}


const char *generate_branch(enum rtx_code code ATTRIBUTE_UNUSED, rtx loc, rtx insn)
{
	return zpu_jump(&loc, insn);
}

const char *zpu_push(rtx operands[], rtx insn ATTRIBUTE_UNUSED)
{
	initGenerate(insn);
	comment("/* push %R0 */", operands);
	push_operand_value(operands+0);

	/* we tell a small lie. We change the SP during tree expansion, but we intended to */
	stackOffset+=4;
	
	cleanupGenerate();
	
	return "";
}


static int reg_save(int regno)
{
	int result=0;
    if (regs_ever_live[regno]&&!call_used_regs[regno])
	{
		result=1;
	}
	/* FIX!!! how do we check if we've eliminated the argument pointer? */
	return result;
}

static int calcSavedSize(void)
{
	int regno;
	int savedSize=0;
  for (regno = 0; regno < R_STACK_REG; regno++)
    if (reg_save(regno))
      {
      	savedSize+=4;
      }
	return savedSize;	 
}

static int calcStackRegSize(void)
{
	int regno;
	int savedSize=0;
  for (regno = R_STACK_REG; regno < FIRST_PSEUDO_REGISTER; regno++)
    if (reg_save(regno))
      {
      	savedSize+=4;
      }
	return savedSize;	 
}


/* Define the offset between two registers, one to be eliminated, and the
   other its replacement, at the start of a routine.  */
int zpu_initial_elimination_offset (int from, int to)
{
	int offset;
	/* The difference between the argument pointer and the stack pointer is
	 * the sum of the size of this function's frame, the callee register save
	 * area, and the fixed stack space needed for function calls (if any). 
	 */
	if (from == ARG_POINTER_REGNUM && to == STACK_POINTER_REGNUM)
	{
    	offset=current_function_outgoing_args_size + calcStackRegSize() + get_frame_size () + calcSavedSize() + 4 ;
	} else if (from == ARG_POINTER_REGNUM && to == HARD_FRAME_POINTER_REGNUM)
    {
    	offset=calcSavedSize() + 4;
    } else if (from == FRAME_POINTER_REGNUM && to == STACK_POINTER_REGNUM)
	{
		offset=current_function_outgoing_args_size + calcStackRegSize() + get_frame_size ();
	} else if (from == FRAME_POINTER_REGNUM && to == HARD_FRAME_POINTER_REGNUM)
	{
		offset=0;
	} else
	{
		abort ();
	}
    return offset;
}

static int allocFrameSize(void)
{
	return current_function_outgoing_args_size+calcStackRegSize()+get_frame_size();
}

void zpu_expand_prologue (void)
{
	int i;
  int regno;
  rtx insn;
  rtx mem_push_rtx;
	HOST_WIDE_INT frameSize;
	int mapper=0;
  
  	prevImmediate=0;
  	for (i=R_STACK_REG; i<R_NUM; i++)
  	{
    	regMapper[i-R_STACK_REG]=-1;
  	}
  	
   	for (i=0; i<R_NUM; i++)
  	{
		if ((i>=R_STACK_REG)&&reg_save(i))
	    {
	    	regMapper[i-R_STACK_REG]=mapper++;
	    }
  		reg[i]=gen_rtx_REG(SImode, i);
  	}
  	regStackTop=0;
  
  
  mem_push_rtx = gen_rtx_MEM (SImode, gen_rtx_PRE_DEC (Pmode, stack_pointer_rtx));
  
  /* Push each of the registers to save.  */
  for (regno = 0; regno < R_STACK_REG; regno++)
    if (reg_save(regno))
      {
	insn = emit_move_insn (mem_push_rtx, gen_rtx_REG (SImode, regno));
	RTX_FRAME_RELATED_P (insn) = 1; 
      }

  /* Set up the frame pointer, if required.  */
  if (frame_pointer_needed)
    {
      insn = emit_move_insn (hard_frame_pointer_rtx, stack_pointer_rtx);
	  RTX_FRAME_RELATED_P (insn) = 1; 
    }
	/* DANGER!!!! I believe that we can trust the GCC compiler to
	 * always eliminate the argument pointer register, if not we're
	 * in trouble, because we do not emit any code here */

	frameSize=allocFrameSize();
	if (frameSize>0)
	{
	  insn=emit_move_insn (stack_pointer_rtx, 
	  gen_rtx_PLUS (SImode, stack_pointer_rtx, GEN_INT (-frameSize)));
	  RTX_FRAME_RELATED_P (insn) = 1; 
	}

}

void zpu_expand_epilogue (void)
{
  rtx mem_pop_rtx, insn;
  int regno;
	HOST_WIDE_INT frameSize;
	rtx mem_push_rtx;
  
  mem_pop_rtx = gen_rtx_MEM (SImode, gen_rtx_POST_INC (Pmode, stack_pointer_rtx));
  
	frameSize=allocFrameSize();
	if (frameSize>0)
	  {
	  insn = emit_move_insn (stack_pointer_rtx, 
	  gen_rtx_PLUS (SImode, stack_pointer_rtx, GEN_INT (frameSize)));
	  RTX_FRAME_RELATED_P (insn) = 1;  
	  }

  /* Restore any call-saved registers.  */
  for (regno = R_STACK_REG - 1; regno >= 0; regno--)
    if (reg_save(regno))
      {
	insn = emit_move_insn (gen_rtx_REG (SImode, regno), mem_pop_rtx);
	  }

	/* FIX! a single poppc should suffice for no argument fn's */
	mem_push_rtx = gen_rtx_MEM (SImode, gen_rtx_PRE_DEC (Pmode, stack_pointer_rtx));
    insn = emit_jump_insn (gen_zpu_return());
}

rtx zpu_return_addr_rtx(void)
{
  return gen_rtx_MEM (Pmode, plus_constant (virtual_incoming_args_rtx, -4));
}


const char *zpu_call(rtx operands[], rtx insn ATTRIBUTE_UNUSED)
{
	initGenerate(insn);
	
	zpu_gen_call(operands);
	
	cleanupGenerate();
	return "";
}


const char *zpu_call_value(rtx operands[], rtx insn ATTRIBUTE_UNUSED)
{
	initGenerate(insn);
	
	zpu_gen_call(operands+1);
	
	if ((GET_CODE(operands[0])!=REG)&&(REGNO(operands[0])!=R_R0))
	{
		rtx reg=gen_rtx_REG(SImode, 0);
		pushreg(reg);
		stackOffset-=4;
		
		store_to_operand(operands+0);
	}

	cleanupGenerate();
	return "";
}

/* change all QImode and HImode to SImode load's*/

void zpu_expand_set(enum machine_mode mode, rtx operands[])
{
	emit_insn(gen_rtx_SET(mode, operands[0], operands[1]));
}



static void
zpu_file_start (void)
{
	default_file_start ();
}

/* Value is the number of bytes of arguments automatically
   popped when returning from a subroutine call.
   FUNDECL is the declaration node of the function (as a tree),
   FUNTYPE is the data type of the function (as a tree),
   or for a library call it is an identifier node for the subroutine name.
   SIZE is the number of bytes of arguments passed on the stack.

   On the ZPU, the RET insn may be used to pop them if the number
     of args is fixed, but if the number is variable then the caller
     must pop them all.
   Use of RET is should be a selectable option, since it is incompatible with
   standard Unix calling sequences.  If the option is not selected,
   the caller must always pop the args.

    */

int
zpu_return_pops_args (tree fundecl ATTRIBUTE_UNUSED, tree funtype, int size)
{
  if (TREE_CODE (funtype) == IDENTIFIER_NODE)
    return size;

  if (TYPE_ARG_TYPES (funtype) == NULL_TREE
      || (TREE_VALUE (tree_last (TYPE_ARG_TYPES (funtype))) == void_type_node))
  	return size;
  
  return 0;
}





int
move_double_src_operand (rtx op, enum machine_mode mode)
{
  switch (GET_CODE (op))
    {
    case CONST_INT :
    case CONST_DOUBLE :
      return 1;

	case SUBREG:
    	/* FIX! not entirely sure why this isn't
    	 * handled by register_operand
    	 */
    	return 1;
	
    case REG :
      return register_operand (op, mode);
	
    #if 0
      /* (subreg (mem ...) ...) can occur here if the inner part was once a
	 pseudo-reg and is now a stack slot.  */
      if (GET_CODE (SUBREG_REG (op)) == MEM)
	return move_double_src_operand (SUBREG_REG (op), mode);
      else
	return register_operand (op, mode);
	#endif
    case MEM :
      /* Disallow auto inc/dec for now.  */
      if ((GET_CODE (XEXP (op, 0)) == POST_INC)&&
      (!REG_P(XEXP (XEXP (op, 0), 0))||
      REGNO(XEXP (XEXP (op, 0), 0)))!=R_SP)
		return 0;
      return memory_operand (op, mode);
    default :
      return 0;
    }
}

/* Return true if OP is an acceptable argument for a move destination.  */

int
move_double_dest_operand (rtx op, enum machine_mode mode)
{
  switch (GET_CODE (op))
    {
    case REG :
    case SUBREG :
      return register_operand (op, mode);
      #if 0
    case SUBREG :
      /* (subreg (mem ...) ...) can occur here if the inner part was once a
	 pseudo-reg and is now a stack slot.  */
      if (GET_CODE (SUBREG_REG (op)) == MEM)
	return address_operand (XEXP (SUBREG_REG (op), 0), mode);
      else
	return register_operand (op, mode);
	#endif
    case MEM :
      /* Disallow auto inc for now.  */
      if (GET_CODE (XEXP (op, 0)) == POST_INC)
      	return 0;
#if 0
	/* FIX!!!! a) why isn't this necessary? b) why does it break compilation? */
      if ((GET_CODE (XEXP (op, 0)) == PRE_DEC)&&
      ((!REG_P(XEXP (XEXP (op, 0), 0))||
      REGNO(XEXP (XEXP (op, 0), 0)))!=R_SP))
		return 0;
#endif		
      return memory_operand (op, mode);
    default :
      return 0;
    }
}


/* Split a 2 word move (DI or DF) into component parts.  */

rtx
gen_split_move_double (rtx operands[])
{
  enum machine_mode mode = GET_MODE (operands[0]);
  rtx dest = operands[0];
  rtx src  = operands[1];
  rtx val;

  /* We might have (SUBREG (MEM)) here, so just get rid of the
     subregs to make this code simpler.  It is safe to call
     alter_subreg any time after reload.  */
  if (GET_CODE (dest) == SUBREG)
    alter_subreg (&dest);
  if (GET_CODE (src) == SUBREG)
    alter_subreg (&src);

  start_sequence ();
  if (GET_CODE (dest) == REG)
    {
      int dregno = REGNO (dest);

      /* Reg = reg.  */
      if (GET_CODE (src) == REG)
	{
	  int sregno = REGNO (src);

	  int reverse = (dregno == sregno + 1);

	  /* We normally copy the low-numbered register first.  However, if
	     the first register operand 0 is the same as the second register of
	     operand 1, we must copy in the opposite order.  */
	  emit_insn (gen_rtx_SET (VOIDmode,
				  operand_subword (dest, reverse, TRUE, mode),
				  operand_subword (src,  reverse, TRUE, mode)));

	  emit_insn (gen_rtx_SET (VOIDmode,
				  operand_subword (dest, !reverse, TRUE, mode),
				  operand_subword (src,  !reverse, TRUE, mode)));
	}

      /* Reg = constant.  */
      else if (GET_CODE (src) == CONST_INT || GET_CODE (src) == CONST_DOUBLE)
	{
	  rtx words[2];
	  split_double (src, &words[0], &words[1]);
	  emit_insn (gen_rtx_SET (VOIDmode,
				  operand_subword (dest, 0, TRUE, mode),
				  words[0]));

	  emit_insn (gen_rtx_SET (VOIDmode,
				  operand_subword (dest, 1, TRUE, mode),
				  words[1]));
	}

      /* Reg = mem.  */
      else if (GET_CODE (src) == MEM)
	{
	  /* If the high-address word is used in the address, we must load it
	     last.  Otherwise, load it first.  */
	  int reverse
	    = (refers_to_regno_p (dregno, dregno + 1, XEXP (src, 0), 0) != 0);

	  /* We used to optimize loads from single registers as

		ld r1,r3+; ld r2,r3

	     if r3 were not used subsequently.  However, the REG_NOTES aren't
	     propagated correctly by the reload phase, and it can cause bad
	     code to be generated.  We could still try:

		ld r1,r3+; ld r2,r3; addi r3,-4

	     which saves 2 bytes and doesn't force longword alignment.  */
	  emit_insn (gen_rtx_SET (VOIDmode,
				  operand_subword (dest, reverse, TRUE, mode),
				  adjust_address (src, SImode,
						  reverse * UNITS_PER_WORD)));

	  emit_insn (gen_rtx_SET (VOIDmode,
				  operand_subword (dest, !reverse, TRUE, mode),
				  adjust_address (src, SImode,
						  !reverse * UNITS_PER_WORD)));
	}
      else
	abort ();
    }

  /* Mem = reg.  */
  /* We used to optimize loads from single registers as

	st r1,r3; st r2,+r3

     if r3 were not used subsequently.  However, the REG_NOTES aren't
     propagated correctly by the reload phase, and it can cause bad
     code to be generated.  We could still try:

	st r1,r3; st r2,+r3; addi r3,-4

     which saves 2 bytes and doesn't force longword alignment.  */
  else if (GET_CODE (dest) == MEM && (GET_CODE(XEXP(dest, 0))==PRE_DEC) && GET_CODE (src) == REG)
    {
      emit_insn (gen_rtx_SET (VOIDmode,
			      gen_rtx_MEM(SImode, XEXP(dest, 0)),
			      operand_subword (src, 1, TRUE, mode)));

      emit_insn (gen_rtx_SET (VOIDmode,
			      gen_rtx_MEM(SImode, XEXP(dest, 0)),
			      operand_subword (src, 0, TRUE, mode)));

    } else if (GET_CODE (dest) == MEM && GET_CODE (src) == REG)
    {
      emit_insn (gen_rtx_SET (VOIDmode,
			      adjust_address (dest, SImode, 0),
			      operand_subword (src, 0, TRUE, mode)));

      emit_insn (gen_rtx_SET (VOIDmode,
			      adjust_address (dest, SImode, UNITS_PER_WORD),
			      operand_subword (src, 1, TRUE, mode)));
    }

  else
  {
  	debug_rtx(operands[0]);
  	debug_rtx(operands[1]);
  	abort();
  }

  val = get_insns ();
  end_sequence ();
  return val;
}


const char *zpu_changestackpointer(rtx operands[], rtx insn)
{
  rtx t[2];
  rtx set;
  
  set=single_set(insn);
  if (set==NULL_RTX)
    {
      abort();
    }
  
  t[0]=stack_pointer_rtx;
  t[1]=SET_SRC(set);
  
  return zpu_generate_move(t, insn);
}






#undef TARGET_ASM_FILE_START
#define TARGET_ASM_FILE_START zpu_file_start
#undef TARGET_ASM_FILE_START_FILE_DIRECTIVE
#define TARGET_ASM_FILE_START_FILE_DIRECTIVE true


struct gcc_target targetm = TARGET_INITIALIZER;


#include "gt-zpu.h"
