/* tc-zpu.c -- Assembler code for the Zylin ZPU
   Copyright 1999, 2000, 2001, 2002, 2003, 2004 Free Software Foundation, Inc.
   Written by Oyvind Harboe <oyvind.harboe@zylin.com>

   This file is part of GAS, the GNU Assembler.

   GAS is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   GAS is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with GAS; see the file COPYING.  If not, write to
   the Free Software Foundation, 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.  */

#include "as.h"
#include "safe-ctype.h"
#include "subsegs.h"
#include "dwarf2dbg.h"
#include "elf/zpu.h"
#include "opcode/zpu.h"
#include <ctype.h>

const char comment_chars[] = ";!";
const char line_comment_chars[] = "#*";
const char line_separator_chars[] = "";

const char EXP_CHARS[] = "eE";
const char FLT_CHARS[] = "dD";



struct zpu_opcode_def {
  int used;
  struct zpu_opcode *opcode;
};

static struct zpu_opcode_def *zpu_opcode_defs = 0;
static int zpu_nb_opcode_defs = 0;

/* Local functions.  */
static int cmp_opcode (struct zpu_opcode *, struct zpu_opcode *);
static char *print_opcode_format (struct zpu_opcode *, int);
static char *skip_whites (char *);
static void print_opcode_list (void);
static void get_default_target (void);

static struct zpu_opcode *find_opcode (struct zpu_opcode_def *);




/* Dumps the list of instructions with syntax and then exit:
   1 -> Only dumps the list (sorted by name)
   2 -> Generate an example (or test) that can be compiled.  */
static short flag_print_opcodes = 0;

/* Opcode hash table.  */
static struct hash_control *zpu_hash;

/* Default cpu determined by 'get_default_target'.  */
static const char *default_cpu;

/* Number of opcodes in the sorted table (filtered by current cpu).  */
static int num_opcodes;

/* The opcodes sorted by name and filtered by current cpu.  */
static struct zpu_opcode *zpu_sorted_opcodes;


static void s_bss PARAMS ((int));

/* This table describes all the machine specific pseudo-ops the assembler
   has to support.  The fields are:
   pseudo-op name without dot
   function to call to execute this pseudo-op
   Integer arg to pass to the function.  */
const pseudo_typeS md_pseudo_table[] = {

  {"bss", s_bss, 0},
  {0, 0, 0}
};

/* Options and initialization.  */

const char *md_shortopts = "Sm:";

struct option md_longopts[] = {

  {NULL, no_argument, NULL, 0}
};
size_t md_longopts_size = sizeof (md_longopts);

/* Get the target cpu for the assembler.  This is based on the configure
   options and on the   If no option is specified,
   we must get the default.  */
const char *
zpu_arch_format (void)
{
  get_default_target ();
  return "elf32-zpu";
}

enum bfd_architecture
zpu_arch (void)
{
  get_default_target ();
  return bfd_arch_zpu;
}

int
zpu_mach (void)
{
  return 0;
}

/* Listing header selected according to cpu.  */
const char *
zpu_listing_header (void)
{
   return "zpu GAS ";
}

void
md_show_usage (FILE *stream)
{
  get_default_target ();
  fprintf (stream, _("\
Zylin ZPU options:\n\
  --print-insn-syntax     print the syntax of instruction in case of error\n\
  --print-opcodes         print the list of instructions with syntax\n\
  --generate-example      generate an example of each instruction\n\
                          (used for testing)\n"));

}
/* Try to identify the default target based on the BFD library.  */
static void
get_default_target (void)
{
  const bfd_target *target;
  bfd abfd;


  default_cpu = "unknown";
  target = bfd_find_target (0, &abfd);
	  default_cpu = "zpu";
}
int
md_parse_option (int c,  char *arg)
{
	(void)c;
	(void)arg;
	return 0;
}

symbolS *
md_undefined_symbol (char *name ATTRIBUTE_UNUSED)
{
  return 0;
}

/* Equal to MAX_PRECISION in atof-ieee.c.  */
#define MAX_LITTLENUMS 6

/* Turn a string in input_line_pointer into a floating point constant
   of type TYPE, and store the appropriate bytes in *LITP.  The number
   of LITTLENUMS emitted is stored in *SIZEP.  An error message is
   returned, or NULL on OK.  */
char *
md_atof (int type, char *litP, int *sizeP)
{
  int prec;
  LITTLENUM_TYPE words[MAX_LITTLENUMS];
  LITTLENUM_TYPE *wordP;
  char *t;

  switch (type)
    {
    case 'f':
    case 'F':
    case 's':
    case 'S':
      prec = 2;
      break;

    case 'd':
    case 'D':
    case 'r':
    case 'R':
      prec = 4;
      break;

    case 'x':
    case 'X':
      prec = 6;
      break;

    case 'p':
    case 'P':
      prec = 6;
      break;

    default:
      *sizeP = 0;
      return _("Bad call to MD_ATOF()");
    }
  t = atof_ieee (input_line_pointer, type, words);
  if (t)
    input_line_pointer = t;

  *sizeP = prec * sizeof (LITTLENUM_TYPE);
  for (wordP = words; prec--;)
    {
      md_number_to_chars (litP, (long) (*wordP++), sizeof (LITTLENUM_TYPE));
      litP += sizeof (LITTLENUM_TYPE);
    }
  return 0;
}

valueT
md_section_align (asection *seg, valueT addr)
{
  int align = bfd_get_section_alignment (stdoutput, seg);
  return ((addr + (1 << align) - 1) & (-1 << align));
}

static int
cmp_opcode (struct zpu_opcode *op1, struct zpu_opcode *op2)
{
  return strcmp (op1->name, op2->name);
}


/* Initialize the assembler.  Create the opcode hash table
   (sorted on the names) with the M6811 opcode table
   (from opcode library).  */
void
md_begin (void)
{
  char *prev_name = "";
  struct zpu_opcode *opcodes;
  struct zpu_opcode_def *opc = 0;
  int i;

  get_default_target ();

  zpu_hash = hash_new ();

  /* Get a writable copy of the opcode table and sort it on the names.  */
  opcodes = (struct zpu_opcode *) xmalloc (zpu_num_opcodes *
					       sizeof (struct
						       zpu_opcode));
  zpu_sorted_opcodes = opcodes;
  num_opcodes = 0;
  for (i = 0; i < zpu_num_opcodes; i++)
    {
	  opcodes[num_opcodes] = zpu_opcodes[i];
	  num_opcodes++;
    }
  qsort (opcodes, num_opcodes, sizeof (struct zpu_opcode),
         (int (*) (const void*, const void*)) cmp_opcode);

  opc = (struct zpu_opcode_def *)
    xmalloc (num_opcodes * sizeof (struct zpu_opcode_def));
  zpu_opcode_defs = opc--;

  /* Insert unique names into hash table.  The M6811 instruction set
     has several identical opcode names that have different opcodes based
     on the operands.  This hash table then provides a quick index to
     the first opcode with a particular name in the opcode table.  */
  for (i = 0; i < num_opcodes; i++, opcodes++)
    {

      if (strcmp (prev_name, opcodes->name))
	{
	  prev_name = (char *) opcodes->name;

	  opc++;
	  opc->opcode = opcodes;
	  opc->used = 0;
	  hash_insert (zpu_hash, opcodes->name, opc);
	}

    }
  opc++;
  zpu_nb_opcode_defs = opc - zpu_opcode_defs;

  if (flag_print_opcodes)
    {
      print_opcode_list ();
      exit (EXIT_SUCCESS);
    }
  linkrelax = 0;
}

void
zpu_init_after_args (void)
{
}

/* Builtin help.  */

/* Return a string that represents the operand format for the instruction.
   When example is true, this generates an example of operand.  This is used
   to give an example and also to generate a test.  */
static char *
print_opcode_format (struct zpu_opcode *opcode, int example)
{
	(void)opcode;
	(void)example;
  static char buf[128];
  char *p;

  p = buf;
  buf[0] = 0;

  return buf;
}

/* Prints the list of instructions with the possible operands.  */
static void
print_opcode_list (void)
{
  int i;
  char *prev_name = "";
  struct zpu_opcode *opcodes;
  int example = flag_print_opcodes == 2;


  opcodes = zpu_sorted_opcodes;

  /* Walk the list sorted on names (by md_begin).  We only report
     one instruction per line, and we collect the different operand
     formats.  */
  for (i = 0; i < num_opcodes; i++, opcodes++)
    {
      char *fmt = print_opcode_format (opcodes, example);

      if (example)
	{
	  printf ("L%d:\t", i);
	  printf ("%s %s\n", opcodes->name, fmt);
	}
      else
	{
	  if (strcmp (prev_name, opcodes->name))
	    {
	      if (i > 0)
		printf ("\n");

	      printf ("%-5.5s ", opcodes->name);
	      prev_name = (char *) opcodes->name;
	    }
	  if (fmt[0])
	    printf ("  [%s]", fmt);
	}
    }
  printf ("\n");
}


static char *
skip_whites (char *p)
{
	while (isspace(*p))
	{
	    p++;
	}
  return p;
}

static int checkRange(int val, int bits)
{
	int prevSign;
	prevSign=(val>>(bits-1))&1;
	if (prevSign)
	{
		return ((val>>bits)&0x7f)!=0x7f;
	} else
	{
		return ((val>>bits)&0x7f)!=0x00;
	}
}

static void emit_insn_core(int insn)
{
	  char *f;
	  f = frag_more (1);
	  dwarf2_emit_insn (1);
	  number_to_chars_bigendian (f, insn, 1);
}

static int immediate=0;
static int prevImmediate=0;

static void emit_insn(int insn)
{
	emit_insn_core(insn);
}


static int emit7Bits(int val, int pos)
{
	return ((val>>pos)&0x7f)|0x80;
}

/* generate immediate sequence */
static int genImmediate(char *buffer, int val)
{
   	int first=1;
	int i,j;
	j=0;
	for (i=4; i>=0; i--)
	{
 		if (!first||(i==0)||checkRange(val, i*7))
 		{
 			buffer[j++]=emit7Bits(val, i*7);
 			first=0;
 		}
	}
	return j;
}

static int flip(int val)
{
	int t=0;
	int i;
	for (i=0; i<32; i++)
	{
		t<<=1;
		t|=(val>>i)&1;
	}
	return t;
}


/* build_insn simple instruction */
static void
build_immediate_insn (expressionS *oper, int fixed14)
{
	if (oper->X_op == O_constant)
    {
    	int val;
    	int length;
    	int i;
    	int a;
    	int b;
    	char buffer[10]; /* maximum length */
    	
    	val=oper->X_add_number;

		a=genImmediate(buffer, val);
		b=genImmediate(buffer, flip(val))+1;
		if (b<a)
		{
			length=genImmediate(buffer, flip(val));
			buffer[length++]=ZPU_flip;
		} else
		{
			length=genImmediate(buffer, val);
		}
		
		for (i=0; i<length; i++)
		{
			emit_insn(buffer[i]);
		}
    } else
    {
    	char *f;
    	if (fixed14)
    	{
			fix_new_exp (frag_now, frag_now_fix (), 2, oper, 0, BFD_RELOC_ZPU_IM_14_NONRELAX);
			f = frag_more (2);
			dwarf2_emit_insn(2);  
    	} else
    	{
			fix_new_exp (frag_now, frag_now_fix (), 5, oper, 0, BFD_RELOC_ZPU_IM_32);
			f = frag_more (5);
			dwarf2_emit_insn(5);  
    	}
    }
}


static void build_loadstoresp(enum ZPU_OPCODE opcode, expressionS *oper)
{
	int offset;
	if (oper->X_op != O_constant)
	{
	  as_bad (_("illegal loadsp operand"));
	} 
	
	offset=oper->X_add_number/4;
	
	if ((offset<0)||(offset>31))
	{
	  as_bad (_("illegal loadsp operand"));
	}
	
	/* we invert bit 4. This allows the same sp+offset circuitry to be used 
	 * for addsp & loadsp/storesp */
	offset=offset^0x10;
	emit_insn(opcode+offset);
}

static void build_addsp(enum ZPU_OPCODE opcode, expressionS *oper)
{
	int offset;
	if (oper->X_op != O_constant)
	{
	  as_bad (_("illegal addsp operand"));
	} 
	
	offset=oper->X_add_number/4;
	
	if ((offset<0)||(offset>15))
	{
	  as_bad (_("illegal addsp operand"));
	}
	
	emit_insn(opcode+offset);
}


/* Opcode identification and operand analysis.  */


/* Find the real opcode and its associated operands.  We use a progressive
   approach here.  On entry, 'opc' points to the first opcode in the
   table that matches the opcode name in the source line.  We try to
   isolate an operand, find a possible match in the opcode table.
   We isolate another operand if no match were found.  The table 'operands'
   is filled while operands are recognized.

   Returns the opcode pointer that matches the opcode name in the
   source line and the associated operands.  */
static struct zpu_opcode *
find_opcode (struct zpu_opcode_def *opc)
{
       return opc->opcode;
 }

/* Gas line assembler entry point.  */

/* This is the main entry point for the machine-dependent assembler.  str
   points to a machine-dependent instruction.  This function is supposed to
   emit the frags/bytes it assembles to.  */
void
md_assemble (char *str)
{
  struct zpu_opcode_def *opc;
  struct zpu_opcode *opcode;

  unsigned char *op_start;
  unsigned char *op_end;
  char name[20];
  int nlen = 0;

  /* Drop leading whitespace.  */
  str=skip_whites(str);

  /* Find the opcode end and get the opcode in 'name'.  The opcode is forced
     lower case (the opcode table only has lower case op-codes).  */
  for (op_start = op_end = (unsigned char *) (str);
       *op_end && nlen < 20 && !is_end_of_line[*op_end] && !isspace(*op_end);
       op_end++)
    {
      name[nlen] = TOLOWER (op_start[nlen]);
      nlen++;
    }
  name[nlen] = 0;

  if (nlen == 0)
    {
      as_bad (_("No instruction or missing opcode."));
      return;
    }

  /* Find the opcode definition given its name.  */
  opc = (struct zpu_opcode_def *) hash_find (zpu_hash, name);
  if (opc==0)
  {
	  as_bad (_("illegal instruction"));
      return;
  }
  
  input_line_pointer = skip_whites(op_end);

  if (opc)
    {
      opc->used++;
      opcode = find_opcode (opc);
    }
  else
    opcode = 0;

	immediate=0;

	if (opcode->amode==ADDR_IMMEDIATE)
	{
		expressionS ex;
		expression (&ex);
		
		switch (opcode->code)
		{
			case ZPU_addsp:
				build_addsp(opcode->code, &ex);
			break;
			case ZPU_storesp:
			case ZPU_loadsp:
			{
				build_loadstoresp(opcode->code, &ex);
			} 
			break;
			
			default:
			immediate=1;
		    build_immediate_insn (&ex, (opcode->code==ZPU_im14));
		    break;
		}
		
	} else if (opcode->amode==ADDR_PCREL)
	{
		char *f;
		expressionS ex;
		expression (&ex);

		immediate=1;
		fix_new_exp (frag_now, frag_now_fix (), 5, &ex, 1, BFD_RELOC_ZPU_IM_32_PCREL);
		f = frag_more (5);
		dwarf2_emit_insn(5);  
	} else 
	{
	    emit_insn(opcode->code);
	}
	if (immediate&&prevImmediate)
	{
		as_bad (_("Two consequtive IM instructions is illegal"));
	}
	prevImmediate=immediate;
}

/* If while processing a fixup, a reloc really needs to be created
   then it is done here.  */
arelent *
tc_gen_reloc (asection *section ATTRIBUTE_UNUSED, fixS *fixp)
{
  arelent *reloc;

  reloc = (arelent *) xmalloc (sizeof (arelent));
  reloc->sym_ptr_ptr = (asymbol **) xmalloc (sizeof (asymbol *));
  *reloc->sym_ptr_ptr = symbol_get_bfdsym (fixp->fx_addsy);
  reloc->address = fixp->fx_frag->fr_address + fixp->fx_where;
	  assert(fixp->fx_r_type != 0);
	reloc->howto = bfd_reloc_type_lookup (stdoutput, fixp->fx_r_type);
	
  if (reloc->howto == (reloc_howto_type *) NULL)
    {
      as_bad_where (fixp->fx_file, fixp->fx_line,
		    _("Relocation %d is not supported by object file format."),
		    (int) fixp->fx_r_type);
      return NULL;
    }

  /* Since we use Rel instead of Rela, encode the vtable entry to be
     used in the relocation's section offset.  */
  if (fixp->fx_r_type == BFD_RELOC_VTABLE_ENTRY)
    reloc->address = fixp->fx_offset;

  reloc->addend = fixp->fx_offset;
  return reloc;
}



void
md_convert_frag (bfd *abfd ATTRIBUTE_UNUSED, asection *sec ATTRIBUTE_UNUSED,
                 fragS *fragP ATTRIBUTE_UNUSED)
{
  as_fatal (_("md_convert_frag invoked\n"));
}

/* Force truly undefined symbols to their maximum size, and generally set up
   the frag list to be relaxed.  */
int
md_estimate_size_before_relax (fragS *fragP ATTRIBUTE_UNUSED, asection *segment ATTRIBUTE_UNUSED)
{
  as_fatal (_("zpu_estimate_size_before_relax invoked\n"));
  return 0;
}

void
md_apply_fix3 (fixS *fixP, valueT *valP ATTRIBUTE_UNUSED, segT seg ATTRIBUTE_UNUSED)
{
	if (linkrelax)
	{
		  /* We shouldn't ever get here because linkrelax is nonzero.  */
		  abort ();
		  fixP->fx_done = 1;
	} else
	{
		  char *where;
		  long value = * valP;
		  int op_type;
		
		  if (fixP->fx_addsy == (symbolS *) NULL)
		    fixP->fx_done = 1;
		
		  /* We don't actually support subtracting a symbol.  */
		  if (fixP->fx_subsy != (symbolS *) NULL)
		    as_bad_where (fixP->fx_file, fixP->fx_line, _("Expression too complex."));
		
		  op_type = fixP->fx_r_type;
		
		  /* The BFD_RELOC_32 is necessary for the support of --gstabs.  */
		  where = fixP->fx_frag->fr_literal + fixP->fx_where;
		
		  switch (fixP->fx_r_type)
		    {
			case BFD_RELOC_ZPU_IM_7:
			case BFD_RELOC_ZPU_IM_14:
			case BFD_RELOC_ZPU_IM_21:
			case BFD_RELOC_ZPU_IM_28:
			case BFD_RELOC_ZPU_IM_32:
			case BFD_RELOC_ZPU_IM_7_PCREL:
			case BFD_RELOC_ZPU_IM_14_PCREL:
			case BFD_RELOC_ZPU_IM_21_PCREL:
			case BFD_RELOC_ZPU_IM_28_PCREL:
			case BFD_RELOC_ZPU_IM_32_PCREL:
		    case BFD_RELOC_32:
		    case BFD_RELOC_16:
			case BFD_RELOC_ZPU_IM_14_NONRELAX:
				  fixP->fx_done = 0;
				break;

	    case BFD_RELOC_32_PCREL:
		    case BFD_RELOC_24_PCREL:
		    case BFD_RELOC_16_PCREL:
		    case BFD_RELOC_8_PCREL:
		    as_bad_where (fixP->fx_file, fixP->fx_line, _("Unsupported relocatoin type."));
		      break;

		    case BFD_RELOC_8:
			  fixP->fx_done = 1;
		      md_number_to_chars (where, value, fixP->fx_size);
		      break;
		      #if 0
		    case BFD_RELOC_32:
		      bfd_putb32 ((bfd_vma) value, (unsigned char *) where);
		      break;
		    case BFD_RELOC_16:
		      bfd_putb16 ((bfd_vma) value, (unsigned char *) where);
		      break;
		#endif
		    default:
		      as_fatal (_("Line %d: unknown 1 relocation type: 0x%x."),
				fixP->fx_line, fixP->fx_r_type);
		    }
	}
}

long
md_pcrel_from (fixS *fixP ATTRIBUTE_UNUSED)
{
	return fixP->fx_where + fixP->fx_frag->fr_address;
}

static void
s_bss (ignore)
     int ignore ATTRIBUTE_UNUSED;
{
  /* We don't support putting frags in the BSS segment, we fake it
     by marking in_bss, then looking at s_skip for clues.  */

  subseg_set (bss_section, 0);
  demand_empty_rest_of_line ();
}

/* See whether we need to force a relocation into the output file.  */
int
tc_zpu_force_relocation (fixS *fixP)
{
	switch (fixP->fx_r_type)
	{
		case BFD_RELOC_ZPU_IM_7:
		case BFD_RELOC_ZPU_IM_14:
		case BFD_RELOC_ZPU_IM_21:
		case BFD_RELOC_ZPU_IM_28:
		case BFD_RELOC_ZPU_IM_32:
		case BFD_RELOC_ZPU_IM_7_PCREL:
		case BFD_RELOC_ZPU_IM_14_PCREL:
		case BFD_RELOC_ZPU_IM_21_PCREL:
		case BFD_RELOC_ZPU_IM_28_PCREL:
		case BFD_RELOC_ZPU_IM_32_PCREL:
		case BFD_RELOC_ZPU_IM_14_NONRELAX:
	    return 1;
		 default:
		 break;
	}

  return generic_force_reloc (fixP);
}

int
tc_zpu_fix_adjustable (fixS *fixP)
{
  switch (fixP->fx_r_type)
    {
      /* For the linker relaxation to work correctly, these relocs
         need to be on the symbol itself.  */
    case BFD_RELOC_16:
    case BFD_RELOC_32:

	/* plus these */
		case BFD_RELOC_ZPU_IM_7:
		case BFD_RELOC_ZPU_IM_14:
		case BFD_RELOC_ZPU_IM_21:
		case BFD_RELOC_ZPU_IM_28:
		case BFD_RELOC_ZPU_IM_32:
		case BFD_RELOC_ZPU_IM_7_PCREL:
		case BFD_RELOC_ZPU_IM_14_PCREL:
		case BFD_RELOC_ZPU_IM_21_PCREL:
		case BFD_RELOC_ZPU_IM_28_PCREL:
		case BFD_RELOC_ZPU_IM_32_PCREL:
		case BFD_RELOC_ZPU_IM_14_NONRELAX:
      return 0;

    default:
      return 1; 
    }
}
