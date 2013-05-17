/* Definitions of target machine for GNU compiler for INMOS transputer family.
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


#undef LIB_SPEC
#define LIB_SPEC "--start-group -lc -lbcc --end-group"


#undef  STARTFILE_SPEC
#define STARTFILE_SPEC "crt0.o%s crt_io.o%s crti%O%s crtbegin%O%s"

#undef  ENDFILE_SPEC
#define ENDFILE_SPEC "crtend%O%s crtn%O%s"


/* just a shorthand for those hard-to-remember options */
#define TARGET_OPTION_TRANSLATE_TABLE \
  { "-phi", "-mboard=phi" },  \
  { "-abel", "-mboard=abel" },  \
  { "-zeta", "-mboard=zeta" }
  
#define CC1_SPEC "" 

#define ASM_SPEC "%{Os:--defsym OPTIMIZE_SIZE=1}"

#define LINK_SPEC "%{mboard=phi:--defsym ZPU_ID=2} %{mboard=zeta:--defsym ZPU_ID=1} %{mboard=abel:--defsym ZPU_ID=0}" 



/* The ZPU architecture is stack/0-operand architecture, so omitting the
 * frame pointer is fundamental to any sort of decent code quality.
 * 
 * -fomit-frame-pointer will be enabled at all optimisation levels/options
 * with CAN_DEBUG_WITHOUT_FP defined.
 */
#define CAN_DEBUG_WITHOUT_FP 1

 


extern int target_flags;


extern int target_flags;



#define ZPU_MULT (1<<0)
#define ZPU_DIV (1<<1)
#define ZPU_MOD (1<<2)
#define ZPU_NEG (1<<3)
#define ZPU_LOADSP (1<<4)
#define ZPU_STORESP (1<<5)
#define ZPU_PUSHSPADD (1<<6)
#define ZPU_CALLPCREL (1<<7)
#define ZPU_CALL (1<<8)
#define ZPU_ADDSP (1<<9)
#define ZPU_SUB (1<<10)
#define ZPU_XOR (1<<11)
#define ZPU_FLIP (1<<12)
#define ZPU_ASHIFTRT (1<<13)
#define ZPU_ASHIFTL (1<<14)
#define ZPU_SHIFTL (1<<15)
#define ZPU_NEQBRANCH (1<<16)
#define ZPU_LSHIFTRT (1<<17)

#define ZPU_BYTEOP (1<<18)
#define ZPU_SHORTOP (1<<19)
#define ZPU_EQ (1<<20)
#define ZPU_COMPARE (1<<21)
#define ZPU_POPPCREL (1<<22)
#define ZPU_BYTESBIG (1<<23)
#define ZPU_BITSBIG (1<<24)
#define ZPU_MEMREG (1<<25)





#define TARGET_SWITCHES_DEFAULT (0x7fffffff&~ZPU_BITSBIG)




#define TARGET_MULT ((target_flags & ZPU_MULT)!=0)
#define TARGET_DIV ((target_flags & ZPU_DIV)!=0)
#define TARGET_MOD ((target_flags & ZPU_MOD)!=0)
#define TARGET_NEG ((target_flags & ZPU_NEG)!=0)
#define TARGET_LOADSP ((target_flags & ZPU_LOADSP)!=0)
#define TARGET_STORESP ((target_flags & ZPU_STORESP)!=0)
#define TARGET_ADDSP ((target_flags & ZPU_ADDSP)!=0)
#define TARGET_PUSHSPADD ((target_flags & ZPU_PUSHSPADD)!=0)
#define TARGET_NEQBRANCH ((target_flags & ZPU_NEQBRANCH)!=0)
#define TARGET_ASHIFTRT ((target_flags & ZPU_ASHIFTRT)!=0)
#define TARGET_ASHIFTL ((target_flags & ZPU_ASHIFTL)!=0)
#define TARGET_LSHIFTRT ((target_flags & ZPU_LSHIFTRT)!=0)
#define TARGET_CALL ((target_flags & ZPU_CALL)!=0)
#define TARGET_CALLPCREL ((target_flags & ZPU_CALLPCREL)!=0)
#define TARGET_BYTEOP ((target_flags & ZPU_BYTEOP)!=0)
#define TARGET_SHORTOP ((target_flags & ZPU_SHORTOP)!=0)
#define TARGET_EQ ((target_flags & ZPU_EQ)!=0)
#define TARGET_COMPARE ((target_flags & ZPU_COMPARE)!=0)
#define TARGET_POPPCREL ((target_flags & ZPU_POPPCREL)!=0)
#define TARGET_BYTESBIG ((target_flags & ZPU_BYTESBIG)!=0)
#define TARGET_BITSBIG ((target_flags & ZPU_BITSBIG)!=0)
#define TARGET_MEMREG ((target_flags & ZPU_MEMREG)!=0)


#define TARGET_SWITCHES \
{ \
    { "mult", ZPU_MULT, "MULT instruction" },\
    { "no-mult", -ZPU_MULT, "MULT instruction" },\
    { "div", ZPU_DIV, "DIV instruction" },\
    { "no-div", -ZPU_DIV, "DIV instruction" },\
    { "mod", ZPU_MOD, "MOD instruction" },\
    { "no-mod", -ZPU_MOD, "MOD instruction" },\
    { "neg", ZPU_NEG, "NEG instruction" },\
    { "no-neg", -ZPU_NEG, "NEG instruction" },\
    { "loadsp", ZPU_LOADSP, "LOADSP instruction" },\
    { "no-loadsp", -ZPU_LOADSP, "LOADSP instruction" },\
    { "storesp", ZPU_STORESP, "STORESP instruction" },\
    { "no-storesp", -ZPU_STORESP, "STORESP instruction" },\
    { "pushspadd", ZPU_PUSHSPADD, "PUSHSPADD instruction" },\
    { "no-pushspadd", -ZPU_PUSHSPADD, "PUSHSPADD instruction" },\
    { "neqbranch", ZPU_NEQBRANCH, "NEQBRANCH instruction" },\
    { "no-neqbranch", -ZPU_NEQBRANCH, "NEQBRANCH instruction" },\
    { "addsp", ZPU_ADDSP, "ADDSP instruction" },\
    { "no-addsp", -ZPU_ADDSP, "ADDSP instruction" },\
    { "ashiftrt", ZPU_ASHIFTRT, "ASHIFTRIGHT instruction" },\
    { "no-ashiftrt", -ZPU_ASHIFTRT, "ASHIFTRIGHT instruction" },\
    { "ashiftl", ZPU_ASHIFTL, "ASHIFTLEFT instruction" },\
    { "no-ashiftl", -ZPU_ASHIFTL, "ASHIFTLEFT instruction" },\
    { "lshiftrt", ZPU_LSHIFTRT, "LSHIFTRIGHT instruction" },\
    { "no-lshiftrt", -ZPU_LSHIFTRT, "LSHIFTRIGHT instruction" },\
    { "call", ZPU_CALL, "CALL instruction" },\
    { "no-call", -ZPU_CALL, "CALL instruction" },\
    { "callpcrel", ZPU_CALLPCREL, "CALLPCREL instruction" },\
    { "no-callpcrel", -ZPU_CALLPCREL, "CALLPCREL instruction" },\
    { "shortop", ZPU_SHORTOP, "LOADH/STOREH instructions" },\
    { "no-shortop", -ZPU_SHORTOP, "LOADH/STOREH instructions" },\
    { "byteop", ZPU_BYTEOP, "LOADB/STOREB insructions" },\
    { "no-byteop", -ZPU_BYTEOP, "LOADB/STOREB insructions" },\
    { "eq", ZPU_EQ, "EQ insructions" },\
    { "no-eq", -ZPU_EQ, "EQ insructions" },\
    { "compare", ZPU_COMPARE, "COMPARE insructions" },\
    { "no-compare", -ZPU_COMPARE, "COMPARE insructions" },\
    { "poppcrel", ZPU_POPPCREL, "POPPCREL insructions" },\
    { "no-poppcrel", -ZPU_POPPCREL, "POPPCREL insructions" },\
    { "memreg", ZPU_MEMREG, "Store r0-r3 in memory location 0-15" },\
    { "no-memreg", -ZPU_MEMREG, "CALL _regpush and _regpop for r0-r3" },\
    { "", TARGET_SWITCHES_DEFAULT, "" }\
}

extern const char *zpu_board_name;

#define TARGET_OPTIONS {						      \
 { "board=", &zpu_board_name, N_("Specify the ZPU board name"), 0} }


#define MULTILIB_DEFAULTS { "O0" } 


#define TARGET_VERSION fprintf (stderr, " (ZPU syntax)");


#define BITS_BIG_ENDIAN                 0 /* TARGET_BITSBIG */
#define BYTES_BIG_ENDIAN                1 /* TARGET_BYTESBIG */
#define WORDS_BIG_ENDIAN                1 /* TARGET_BYTESBIG */
#define BITS_PER_UNIT                   8
#define BITS_PER_WORD                   32
#define UNITS_PER_WORD                  4

/* Define this macro if it is advisable to hold scalars in registers
   in a wider mode than that declared by the program.  In such cases, 
   the value is constrained to be within the bounds of the declared
   type, but kept valid in the wider mode.  The signedness of the
   extension may differ from that of the type.  */
#define PROMOTE_MODE(MODE,UNSIGNEDP,TYPE) \
if (GET_MODE_CLASS (MODE) == MODE_INT		\
    && GET_MODE_SIZE (MODE) < UNITS_PER_WORD)	\
{						\
  (MODE) = word_mode;				\
}
#define PROMOTE_FUNCTION_ARGS
#define PROMOTE_FUNCTION_RETURN


#define POINTER_SIZE                    BITS_PER_WORD

#define PARM_BOUNDARY            BITS_PER_WORD
#define STACK_BOUNDARY           BITS_PER_WORD
#define FUNCTION_BOUNDARY        BITS_PER_UNIT
#define BIGGEST_ALIGNMENT        BITS_PER_WORD
#define BIGGEST_FIELD_ALIGNMENT  BITS_PER_WORD

#define EMPTY_FIELD_BOUNDARY  BITS_PER_WORD

#define CONSTANT_ALIGNMENT(EXP, ALIGN) BITS_PER_WORD
#define DATA_ALIGNMENT(TYPE, ALIGN) BITS_PER_WORD
#define LOCAL_ALIGNMENT(TYPE, ALIGN) BITS_PER_WORD

#define STRICT_ALIGNMENT  1

#define MAX_FIXED_MODE_SIZE 32

#define TARGET_FLOAT_FORMAT  IEEE_FLOAT_FORMAT


#define SHORT_TYPE_SIZE 16
#define INT_TYPE_SIZE 32
#define FLOAT_TYPE_SIZE 32
#define LONG_TYPE_SIZE BITS_PER_WORD
#define MAX_WCHAR_TYPE_SIZE 32
#define DOUBLE_TYPE_SIZE 64
#define LONG_LONG_TYPE_SIZE 64

#define DEFAULT_SIGNED_CHAR  0

#define DEFAULT_SHORT_ENUMS  0

#define TARGET_BELL                     007
#define TARGET_BS                       010
#define TARGET_TAB                      011
#define TARGET_NEWLINE                  012
#define TARGET_VT                       013
#define TARGET_FF                       014
#define TARGET_CR                       015

#define R_R0          (0)
#define R_R1          (1)
#define R_R2          (2)
#define R_R3  	      (3)
#define R_NUM         (32)


#define FIRST_PSEUDO_REGISTER     36

#define FIXED_REGISTERS \
  /*0,1,2,3,4,5,6,7                                                    SP,PC,fp,ap*/ \
  { 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 1, 1, 1, 1}

#define CALL_USED_REGISTERS \
  /*0,1,2,3,4,5,6,7, 0,1,2,3,4,5,6,7, 0,1,2,3,4,5,6,7, 0,1,2,3,4,5,6,7,SP,PC,fp,ap*/ \
  { 1,0,1,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 1, 1, 1, 1}

/* KLUDGE!
 * 
 * We don't want GCC to use the memory mapped register r0-r7. Normally it
 * won't unless it has to. 
 * 
 * However, somewhere in GCC there is a clever mechanism to make the hard frame
 * register availble for general allocation even though it is marked as a
 * fixed register.
 * 
 * Using R3(memory mapped register) is harmless, but not optimal.
 */
#define REG_ALLOC_ORDER {\
	8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31, \
	0,1,2,3,4,5,6,7, \
	32, 33, 34, 35 }


#define HARD_REGNO_NREGS(REGNO, MODE) ((GET_MODE_SIZE(MODE) + UNITS_PER_WORD -1)/UNITS_PER_WORD)

/* we only allow >32 bits in non-memory mapped registers */
#define HARD_REGNO_MODE_OK(REGNO, MODE) ((REGNO>=R_STACK_REG)||(GET_MODE_SIZE(MODE)<=UNITS_PER_WORD))

#define MODES_TIEABLE_P(MODE1, MODE2) 1
 
#define AVOID_CCMODE_COPIES

enum reg_class
{
    NO_REGS,
    GENERAL_REGS,
    ALL_REGS,
    LIM_REG_CLASSES
};

#define N_REG_CLASSES                   (int) LIM_REG_CLASSES

#define REG_CLASS_NAMES \
  { "NO_REGS",                                          \
    "GENERAL_REGS",                                     \
    "ALL_REGS" }

#define REG_CLASS_CONTENTS \
  {\
  	{0, 0},              \
    {0xffffff0d, 0xf}, \
    {0xffffff0d, 0xf}, }

#define REGNO_REG_CLASS(REGNO) (((REGNO)<FIRST_PSEUDO_REGISTER)?GENERAL_REGS:ALL_REGS)
#define BASE_REG_CLASS GENERAL_REGS
#define INDEX_REG_CLASS GENERAL_REGS
#define REG_CLASS_FROM_LETTER(C) NO_REGS

#define REGNO_OK_FOR_INDEX_P(REGNO) 1

#define REGNO_OK_FOR_BASE_P(REGNO) 1

#define PREFERRED_RELOAD_CLASS(X,CLASS) GENERAL_REGS

/* #define SMALL_REGISTER_CLASSES 0 */

/* #define CLASS_LIKELY_SPILLED_P(class)  1 */

#define CLASS_MAX_NREGS(CLASS, MODE) HARD_REGNO_NREGS(CLASS, MODE)

#define CONST_OK_FOR_LETTER_P(VALUE, C) 0

#define CONST_DOUBLE_OK_FOR_LETTER_P(VALUE, C) 0

#define EXTRA_CONSTRAINT(X, C) 0
#define EXTRA_MEMORY_CONSTRAINT(C,STR) 0
#define EXTRA_ADDRESS_CONSTRAINT(C,STR) 0

#define STACK_GROWS_DOWNWARD
#undef ARGS_GROW_DOWNWARD


/* By letting the frame grow downwards, we'll have the 
 * final stack slot assignments, the pseudo registers,
 * with the smallest offsets. This has a major impact
 * on code size
 */
#define FRAME_GROWS_DOWNWARD


#define STARTING_FRAME_OFFSET 0

#define FIRST_PARM_OFFSET(FUNDECL)  (0)

#define RETURN_ADDR_RTX(COUNT, FRAMEADDR) ((COUNT) == 0	\
   ? zpu_return_addr_rtx() \
   : NULL_RTX)

/* rtx for return address *before* prologue */
#define INCOMING_RETURN_ADDR_RTX \
  gen_rtx_MEM (VOIDmode, gen_rtx_REG (VOIDmode, STACK_POINTER_REGNUM))
  
#define INCOMING_FRAME_SP_OFFSET 4



#define STACK_POINTER_REGNUM  R_SP

/* this will be eliminated. The magic trick here is to use a "fake frame pointer" that
 * is eliminated.
 * 
 * Additional voodoo is to have the hard frame pointer late amongst the registers
 * so it isn't allocated when it is impossible to replace the
 * frame pointer with the stack pointer. 
 * 
 * It would be disaterous not to eliminate R_FAKE_FP, since it
 * doesn't actually exist
 */
#define FRAME_POINTER_REGNUM  R_FAKE_FP
#define HARD_FRAME_POINTER_REGNUM  R_R3

/* this will be eliminated*/
#define ARG_POINTER_REGNUM  R_FAKE_AP

#define STATIC_CHAIN_REGNUM  R_R2

#define FRAME_POINTER_REQUIRED (current_function_calls_alloca || current_function_has_nonlocal_goto)

#define ELIMINABLE_REGS {					\
	{FRAME_POINTER_REGNUM, STACK_POINTER_REGNUM}, \
	{FRAME_POINTER_REGNUM, HARD_FRAME_POINTER_REGNUM}, \
	{ARG_POINTER_REGNUM, STACK_POINTER_REGNUM}, \
	{ARG_POINTER_REGNUM, HARD_FRAME_POINTER_REGNUM} \
		}
		
/* avoid reload happily eliminating the arg pointer when
 * the frame pointer can't be eliminted.
 */	
#define CAN_ELIMINATE(FROM, TO) \
  ((TO) == STACK_POINTER_REGNUM ? ! frame_pointer_needed : 1)

#define INITIAL_ELIMINATION_OFFSET(from_reg,to_reg,offset) {offset=zpu_initial_elimination_offset(from_reg, to_reg);}

#define HAVE_POST_INCREMENT 1

#define HAVE_PRE_DECREMENT 1

#define PROMOTE_PROTOTYPES 1

#define ACCUMULATE_OUTGOING_ARGS 1

/* What does GCC do differently if we tell it that these registers are part of a
 * register window?
 */
#define LOCAL_REGNO(REGNO) (((REGNO) >= R_STACK_REG) && ((REGNO) <= R_STACK_REG_LAST))


#define RETURN_POPS_ARGS(FUNDECL,FUNTYPE,SIZE) 0


#define FUNCTION_ARG(CUM, MODE, TYPE, NAMED) 0

#define FUNCTION_ARG_PARTIAL_NREGS(CUM, MODE, TYPE, NAMED)  0

#define FUNCTION_ARG_PASS_BY_REFERENCE(CUM, MODE, TYPE, NAMED)  0

typedef struct {
  /* The first arg_regno free after scanning the arguments so far.  */
  int lst_free_reg;

  /* The flag set by FUNCTION_ARG_PRESCAN saying we dont want to pass
     anything in registers for current call.  */
  int must_pass_in_stack;
} CUMULATIVE_ARGS;


#define INIT_CUMULATIVE_ARGS(CUM, FNTYPE, LIBNAME, INDIRECT, N_NAMED_ARGS) 

#define RESET_CUMULATIVE_ARGS(CUM, FNTYPE, LIBNAME) 

#define FUNCTION_ARG_ADVANCE(CUM, MODE, TYPE, NAMED) 
  
#define FUNCTION_ARG_REGNO_P(REGNO)  0

#define FUNCTION_VALUE(VALTYPE, FUNC) gen_rtx (REG, TYPE_MODE (VALTYPE), R_R0)

#define LIBCALL_VALUE(MODE) gen_rtx (REG, MODE, R_R0)

#define FUNCTION_VALUE_REGNO_P(REGNO) ((REGNO) == R_R0 )



#define STRUCT_VALUE  0
#define STRUCT_VALUE_INCOMING  0


#define FUNCTION_PROFILER(FILE, LABELNO)

#define NO_PROFILE_COUNTERS	1


#define SETUP_INCOMING_VARARGS(CUM,MODE,TYPE,PRETEND_SIZE,NO_RTL) {}


/* Linktime relaxing is not an issue here w.r.t. making
 * sure that the trampoline is of constant size. Firstly 
 * the trampoline template is placed in the read-only segment, so
 * there is no link-time relaxing, secondly, the machine code
 * below does not use any relaxable relocations.
 * 
 * The fun part here is that we have to save & restore 
 * the static chain register without screwing up the stack frame.
 * 
 * We poke the return address to return to the trampoline in order to
 * restore the static chain register.
 * 
 */
#define TRAMPOLINE_TEMPLATE(FILE) \
{						\
  fprintf ((FILE), "; save return address\n");	\
  fprintf ((FILE), "	nop\n");	\
  fprintf ((FILE), "	nop\n");	\
  fprintf ((FILE), "	nop\n");	\
  fprintf ((FILE), "	nop\n");	\
  fprintf ((FILE), "; save static chain register\n");	\
  fprintf ((FILE), "	nop\n");	\
  fprintf ((FILE), "	nop\n");	\
  fprintf ((FILE), "	nop\n");	\
  fprintf ((FILE), "	nop\n");	\
  fprintf ((FILE), "; load static chain register\n");	\
  fprintf ((FILE), "	pushpc ; 24 \n");	\
  fprintf ((FILE), "	im 4+24\n");	\
  fprintf ((FILE), "	add\n");	\
  fprintf ((FILE), "	load\n");	\
  fprintf ((FILE), "	im %d\n", STATIC_CHAIN_REGNUM*4);	\
  fprintf ((FILE), "	store\n");	\
  fprintf ((FILE), "; call function\n");	\
  fprintf ((FILE), "	pushpc ; 18\n");	\
  fprintf ((FILE), "	im 18\n");	\
  fprintf ((FILE), "	add\n");	\
  fprintf ((FILE), "	load\n");	\
  fprintf ((FILE), "	poppc\n");	\
  fprintf ((FILE), "; restore static chain register\n");	\
  fprintf ((FILE), "	nop\n");	\
  fprintf ((FILE), "	nop\n");	\
  fprintf ((FILE), "	nop\n");	\
  fprintf ((FILE), "	nop\n");	\
  fprintf ((FILE), "	nop\n");	\
  fprintf ((FILE), "; return to original caller\n");	\
  fprintf ((FILE), "	nop\n");	\
  fprintf ((FILE), "	nop\n");	\
  fprintf ((FILE), "	nop\n");	\
  fprintf ((FILE), "	nop\n");	\
  fprintf ((FILE), "	nop\n");	\
  fprintf ((FILE), "	nop\n");	\
  fprintf ((FILE), "	nop\n");	\
  fprintf ((FILE), "	nop\n");	\
  fprintf ((FILE), "	.long	0 ; address\n");		\
  fprintf ((FILE), "	.long	0 ; static chain value\n");		\
  fprintf ((FILE), "	.long	0 ; save area for static chain register\n");		\
  fprintf ((FILE), "	.long	0 ; saved return address\n");		\
}

#define TRAMPOLINE_SIZE (32+16)
/* The alignment of a trampoline, in bits.  */
#define TRAMPOLINE_ALIGNMENT  32

#define INITIALIZE_TRAMPOLINE(TRAMP, FNADDR, CXT)  \
{									\
  emit_move_insn (gen_rtx (MEM, SImode, plus_constant ((TRAMP), 32+4)),	\
		  (CXT));						\
  emit_move_insn (gen_rtx (MEM, SImode, plus_constant ((TRAMP), 32+0)),	\
		  (FNADDR));						\
}


#define TARGET_MEM_FUNCTIONS

#define CONSTANT_ADDRESS_P(X)  CONSTANT_P(X)

/* reload can fail if we use more. This limit does not
 * apply to PC/SP. Reducing this from 10 to 2 had no measureable
 * impact on code size.
 */
#define MAX_REGS_PER_ADDRESS  2


#ifdef REG_OK_STRICT
#define GO_IF_LEGITIMATE_ADDRESS(MODE, X, LABEL)   {if (zpu_legitimate_address(MODE, X, 1)) goto LABEL;}
/* Nonzero if X is a hard reg that can be used as a base reg.  */
#define REG_OK_FOR_BASE_P(X) (REGNO(X)<FIRST_PSEUDO_REGISTER)
#else
#define GO_IF_LEGITIMATE_ADDRESS(MODE, X, LABEL)   {if (zpu_legitimate_address(MODE, X, 0)) goto LABEL;}
/* Nonzero if X is a hard reg that can be used as a base reg
   or if it is a pseudo reg.  */
#define REG_OK_FOR_BASE_P(X) 1
#endif

#define REG_OK_FOR_INDEX_P(X) REG_OK_FOR_BASE_P (X)


#define LEGITIMIZE_ADDRESS(x, oldx, mode, win) 

#define GO_IF_MODE_DEPENDENT_ADDRESS(ADDR,LABEL)	\
 if (GET_CODE (ADDR) == POST_INC || GET_CODE (ADDR) == PRE_DEC) goto LABEL


#define LEGITIMATE_CONSTANT_P(X) 1

/* We need to print registers here as they are valid addresses
 * that can be sent to __asm() blocks as arguments
 */
#define OUTPUT_ADDR_CONST_EXTRA(STREAM, X, FAIL) \
{\
    if (GET_CODE (X) == REG)	\
      {									\
      	print_operand(STREAM, X, 0); \
      }									\
    else								\
      goto FAIL;							\
}

#define NOTICE_UPDATE_CC(exp, insn) CC_STATUS_INIT


#define REGISTER_MOVE_COST(MODE, CLASS1, CLASS2)	4

#define MEMORY_MOVE_COST(MODE,CLASS,IN)		1

#define BRANCH_COST  2
#define SLOW_BYTE_ACCESS  1
#define MOVE_RATIO                          (1+1)
#define NO_FUNCTION_CSE  1
#define NO_RECURSIVE_FUNCTION_CSE  1


#define TEXT_SECTION_ASM_OP  ".text"
#define DATA_SECTION_ASM_OP  ".data"

#define BSS_SECTION_ASM_OP  ".bss"


#define ASM_COMMENT_START                   "//"
#define ASM_APP_ON                          ""
#define ASM_APP_OFF                         ""

#define REGISTER_NAMES \
  { "R0", "R1", "R2", "R3", "R4", "R5", "R6", "R7", \
  	"R8", "R9", "R10","R11","R12","R13","R14","R15", \
  	"R16","R17","R18","R19","R20","R21","R22","R23", \
  	"R24","R25","R26","R27","R28","R29","R30","R31", \
  	"SP","PC", "*FAKEFRAMEPOINTER", "*FAKEARGPOINTER"}

 
#define PRINT_OPERAND(STREAM, X, CODE) print_operand(STREAM, X, CODE)

#define PRINT_OPERAND_ADDRESS(STREAM, X) \
  output_addr_const (STREAM, X);


#define ASM_OUTPUT_REG_PUSH(STREAM, REGNO) fprintf(STREAM, "im %d\nload\n", REGNO*4)
#define ASM_OUTPUT_REG_POP(STREAM, REGNO)  fprintf(STREAM, "im %d\nstore\n", REGNO*4)

/* This is how to output an element of a case-vector that is absolute.  */

#define ASM_OUTPUT_ADDR_VEC_ELT(FILE, VALUE)  \
  fprintf (FILE, "\t.long .L%d\n", VALUE)

/* This is how to output an element of a case-vector that is relative.  */

#define ASM_OUTPUT_ADDR_DIFF_ELT(FILE, BODY, VALUE, REL)  \
  fprintf (FILE, "\t.long .L%d-.L%d\n", VALUE, REL)


#define ASM_OUTPUT_ALIGN(STREAM, POWER) \
  fprintf (STREAM, "\t.balign %u;\n", 1 << (POWER));

#define DBX_REGISTER_NUMBER(REGNO)  (REGNO)


#define CASE_VECTOR_MODE                    SImode


#define CASE_VECTOR_PC_RELATIVE 0


#define WORD_REGISTER_OPERATIONS


#define LOAD_EXTEND_OP(MODE)  ZERO_EXTEND

#define MOVE_MAX  UNITS_PER_WORD

#define TRULY_NOOP_TRUNCATION(OUTPREC, INPREC)  1

#define STORE_FLAG_VALUE  1


#define Pmode          SImode

#define FUNCTION_MODE  QImode

#define WORKSPACE_RESERVED_BYTES  (7 * UNITS_PER_WORD)

#define IN_WORDS(SIZE_IN_BYTES) \
  (((SIZE_IN_BYTES) + UNITS_PER_WORD - 1) / UNITS_PER_WORD)

#define WORD_ROUND(VALUE) \
  (((VALUE) + UNITS_PER_WORD - 1) & -UNITS_PER_WORD)

#define FLOAT_OPERAND(N) \
  (GET_MODE_CLASS (GET_MODE (operands[N])) == MODE_FLOAT)

extern
struct zpu_compare {
  struct rtx_def *op[2];   /* comparison operands */
  int fp;                  /* floating comparison required */
} zpu_compare;

/* Point that a function's arguments should be processed (in calls.c)
   from last to first, so that the integer regstack will be in the
   proper order before a call insn; no stack rearrangement will be needed.
   It is not quite right to define this macro here as it was not
   intended for user redefinition, but this yields the desired effect. */

#define PUSH_ARGS_REVERSED 1	/* If it's last to first */



/* This is called before generating rtl for every function.  */

#define INIT_EXPANDERS 



     
#define TARGET_CPU_CPP_BUILTINS()		\
  do						\
    {						\
      builtin_define_std ("zpu");		\
    }						\
  while (0)

  
#define GLOBAL_ASM_OP   "\t.globl\t"


/* we use setjmp/longjmp for C++ exception handling... */
#define DWARF2_UNWIND_INFO 0

/* ZPU hack! We have modified GCC to allow -fomit-frame-pointer to be more powerful */
#define ALLOW_REF_TO_SP_IN_CHANGE_SP_INSN 1


#undef DBX_OUTPUT_MAIN_SOURCE_FILE_END
#define DBX_OUTPUT_MAIN_SOURCE_FILE_END(FILE, FILENAME)			\
  fprintf (FILE,							\
	   "\t.text\n.stabs \"\",%d,0,0,.Letext\n.Letext:\n", N_SO)


/* see config/mips/elf.h */

/* Use __main method of constructor invocation.  */
#define TARGET_ASM_NAMED_SECTION default_elf_asm_named_section
/* On elf, we *do* have support for the .init and .fini sections, and we
   can put stuff in there to be executed before and after `main'.  We let
   crtstuff.c and other files know this by defining the following symbols.
   The definitions say how to change sections to the .init and .fini
   sections.  This is the same for all known elf assemblers.  */

#undef  INIT_SECTION_ASM_OP
#define INIT_SECTION_ASM_OP     "\t.section\t.init"
#undef  FINI_SECTION_ASM_OP
#define FINI_SECTION_ASM_OP     "\t.section\t.fini"


#undef  ASM_APP_ON
#define ASM_APP_ON "#APP\n"

#undef  ASM_APP_OFF
#define ASM_APP_OFF "#NO_APP\n"
