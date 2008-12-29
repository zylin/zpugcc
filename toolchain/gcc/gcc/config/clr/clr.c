/* clr.c
 * Jeremy Singer
 * 7 Jan 03
 */

/* N.B. At the moment, all the functions defined
 * here are DUMMIES.
 */

#include "config.h"
#include <setjmp.h>
#include "system.h"
#include "rtl.h"
#include "tree.h"
#include "tm_p.h"
#include "regs.h"
#include "hard-reg-set.h"
#include "real.h"
#include "insn-config.h"
#include "conditions.h"
#include "output.h"
#include "insn-attr.h"
#include "flags.h"
#include "except.h"
#include "function.h"
#include "recog.h"
#include "expr.h"
#include "toplev.h"
#include "basic-block.h"
#include "ggc.h"



void function_prologue(FILE *file, int size) {

  int num_args = current_function_args_info.regs;

  /* We have set up GCC to allow us to pass
   * a maximum of 8 arguments in registers.
   * See MAX_ARGS_IN_REGS definition in
   * clr.h
   */
  
  int num_args_in_regs = (num_args < 8) ? num_args : 8;
  int i;

  /* Work out what fp and sp offsets should be
   */

  int fp_offset = FIRST_PARM_OFFSET();
  int sp_offset = size + current_function_outgoing_args_size + 4;

  for (i = 0; i < num_args_in_regs; i++) {
    if (i>0) fprintf(file, ",");
    fprintf(file, "int32");
  }
  fprintf(file, ") cil managed\n");
  fprintf(file, "{\n\n");

  /* clr directives for stack and locals sizes */
  fprintf(file, "\t.maxstack 10\n");
  fprintf(file,
	  "\t.locals (int32,int32,int32,int32,int32,"
	  "int32,int32,int32,int32,int32,"
	  "int32,int32,int32,int32,int32,"
	  "int32,int32,int32,int32,int32,"
	  "int32,int32,int32,int32,int32,"
	  "int32,int32,int32,"
	  "int32 *, int32 *,"
	  "int32,int32)\n\n");
  /* fprintf(file, "<start of function>\n\n"); */
  /* fprintf(file, "\t// fp_offset = %d\n", fp_offset); */
  /* fprintf(file, "\t// sp_offset = %d\n", sp_offset); */

  /* First of all, work out sp and fp from 
   * static fields and calculated offsets.
   * NEW_FP = OLD_SP - fp_offset
   * NEW_SP = NEW_FP - sp_offset
   * (jds31 - this means we don't actually _need_
   *  to save OLD_FP, hmmm, never mind.)
   */

  fprintf(file, "\tldsfld int32 * '<Module>'::sp\n");
  fprintf(file, "\tldc.i4 %d\n", fp_offset);
  fprintf(file, "\tsub\n");
  fprintf(file, "\tdup\n");
  fprintf(file, "\tstloc %d\n", FRAME_POINTER_REGNUM);
  fprintf(file, "\tldc.i4 %d\n", sp_offset);
  fprintf(file, "\tsub\n");
  fprintf(file, "\tstloc %d\n\n", STACK_POINTER_REGNUM);

  fprintf(file, "\t// no args = %d\n\n", num_args);
  
  
  /* Loop through register arguments, and
   * move them out of CLR args[] into
   * the incoming argument registers
   * of our pseudo-register-file, (really
   * CLR locals[]).
   */

  for (i = 0; i < num_args_in_regs; i++) {
    
    /* On CLR, upon function entry, first argument
     * is stored in args[0]. Since we are only using
     * static methods, this will be the first argument
     * supplied to the function, rather than a 'this'
     * reference.
     */
    
    fprintf(file, "\tldarg %d\n", i);
    
    /* Our GCC register file layout is set up so
     * that incoming arguments live in r11 to r18.
     * (Really locals[11] to locals[18].
     * r11 is FIRST_ARG_REG_IN
     * These definitions are set up in clr.h
     */
    
    fprintf(file, "\tstloc %d\n", FIRST_ARG_REG_IN + i);
  }

  if (num_args_in_regs > 0) fprintf(file, "\n");

}


void function_epilogue(FILE *file, int size) {
  
  // fprintf(file, "// <end of function>\n");
  fprintf(file, "}\n\n");

}


int initial_fp_sp_offset() {

  return 1;

}


void notice_update_cc(rtx exp, rtx insn) {

  /*  */

}

void print_operand(FILE *file, rtx x, int code) {

  if (GET_CODE(x) == REG) {
    fprintf(file, "%d", REGNO(x));
  }
  else if (GET_CODE(x) == CONST_INT) {
    fprintf(file, "%d", INTVAL(x));
  }
  else if (GET_CODE(x) == MEM) {
    print_operand_address(file, XEXP(x, 0));
  }
  else if (GET_CODE(x) == CONST) {
    fprintf(file, "Const ...");
  }
  else if (GET_CODE(x) == LABEL_REF) {
    fprintf(file, "L%d", CODE_LABEL_NUMBER(x));
  }
  else if (GET_CODE(x) == SYMBOL_REF) {
    assemble_name(file, XSTR(x, 0));
  }
  else {
    fprintf(file, "operand %d", x);
  }
}


void print_operand_address(FILE *file, rtx addr) {

  switch(GET_CODE (addr)) {
  
  case REG:
    // fprintf(file, "[r%d]", REGNO(addr));
    fprintf(file, "ldloc %d\n\t", REGNO(addr));
    break;

  case PLUS:
    {
      rtx arg0 = XEXP(addr, 0);
      rtx arg1 = XEXP(addr, 1);
      
      if (GET_CODE(arg0) == REG) {
	if (GET_CODE(arg1) == REG) {
	  // fprintf(file, "r%d[r%d]", REGNO(arg0), REGNO(arg1));
	  fprintf(file, "ldloc %d\n\t", REGNO(arg0));
	  fprintf(file, "ldloc %d\n\t", REGNO(arg1));
	  fprintf(file, "add\n\t");
	}
	else if (GET_CODE(arg1) == CONST_INT) {
	  // fprintf(file, "r%d[#%d]", REGNO(arg0), INTVAL(arg1));
          fprintf(file, "ldloc %d\n\t", REGNO(arg0));
          fprintf(file, "ldc.i4 %d\n\t", INTVAL(arg1));
          fprintf(file, "add\n\t");
	}
       	else if (GET_CODE(arg1) == SYMBOL_REF) {
	  // fprintf(file, "r%d[", REGNO(arg0));
	  // assemble_name(file, XSTR(arg1, 0));
	  // fprintf(file, "]");
	  fprintf(file, "ldsflda valuetype vt_");
	  assemble_name(file, XSTR(arg1, 0));
	  fprintf(file, " '<Module>'::");
	  assemble_name(file, XSTR(arg1, 0));
	  fprintf(file, "\n\tldloc %d\n\t", REGNO(arg0));
	  fprintf(file, "add\n\t");
	}
	else {
	  fprintf(file, "r%d[op %d]", REGNO(arg0), arg1);
	}
      }
      else if (GET_CODE(arg0) == SYMBOL_REF) {
	if (GET_CODE(arg1) == CONST_INT) {
	  fprintf(file, "ldsflda valuetype vt_");
	  assemble_name(file, XSTR(arg0, 0));
	  fprintf(file, " '<Module>'::");
	  assemble_name(file, XSTR(arg0, 0));
	  fprintf(file, "\n\tldc.i4 %d\n\t", INTVAL(arg1));
	  fprintf(file, "add\n\t");
	}
	else {
	  assemble_name(file, XSTR(arg0, 0));
	  fprintf(file, "[op %d]", arg1);
	}
      }      
      else {
	fprintf(file, "(PLUS %d %d)", arg0, arg1);
      }
    }
    break;
  
  case LABEL_REF:
    fprintf(file, "L%d", CODE_LABEL_NUMBER(addr));
    break;
    
  case SYMBOL_REF:
    fprintf(file, "ldsflda valuetype vt_");
    assemble_name(file, XSTR(addr, 0));
    fprintf(file, " '<Module>'::");
    assemble_name(file, XSTR(addr, 0));
    break;

  case CONST_INT:
  case CONST:
    // fprintf(file, "constant addr");
    print_operand_address(file, XEXP(addr,0));
    break;
  
  default:
    fprintf(file, "address %d", addr);
    break;
  
  }

}

/* next routine has been copied from picoJava machine definition */
/* jds31 - and slightly altered - pJ added extra 2 regs */

/* Return in an rtx the number of words pushed onto the optop to be
   used as the word count in a call insn.  (NEXT_ARG_REG is NULL when
   called from expand_builtin_apply).  */

/* jds31 - this routine doesn't seem to work properly :-( */

rtx
pj_workout_arg_words (stack_size, next_arg_reg)
     rtx stack_size ATTRIBUTE_UNUSED;
     rtx next_arg_reg;
{
  return GEN_INT ((next_arg_reg ? REGNO (next_arg_reg) - FIRST_ARG_REG : 0));
}

/* jds31 - this routine works out the number
 *         of arguments to a function which
 *         are passed in registers, at each
 *         call site. (This value is returned
 *         as an int.)  Based on code
 *         from egcs-jvm, the jvm.md file
 */

int
clr_workout_arg_words(rtx expr_list)
{
  rtx link, theuse, thereg;
  int highest = FIRST_ARG_REG - 1;
  int num_reg_arg_words = -1;
 
  for (link = expr_list; link != 0;
       link = XEXP(link, 1))
    {
      theuse = XEXP(link,0);
      if (GET_CODE(theuse)!=USE) continue;
      thereg = XEXP(theuse,0);
      if (GET_CODE(thereg)!=REG) continue;
      if (REGNO(thereg)>highest) highest=REGNO(thereg);
    }

  num_reg_arg_words = (highest - FIRST_ARG_REG) + 1;
  return (num_reg_arg_words);
}

