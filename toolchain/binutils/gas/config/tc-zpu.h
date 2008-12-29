/* tc-zpu.h -- Header file for tc-zpu.c.
   Copyright 1999, 2000, 2001, 2002 Free Software Foundation, Inc.

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
   along with GAS; see the file COPYING.  If not, write to the Free
   Software Foundation, 59 Temple Place - Suite 330, Boston, MA
   02111-1307, USA.  */

#define TC_ZPU

#ifdef ANSI_PROTOTYPES
struct fix;
#endif

#define TARGET_BYTES_BIG_ENDIAN 1


#ifndef BFD_ASSEMBLER
#error ZPU support requires BFD_ASSEMBLER
#endif

/* The target BFD architecture.  */
#define TARGET_ARCH (zpu_arch ())
extern enum bfd_architecture zpu_arch (void);

#define TARGET_MACH (zpu_mach ())
extern int zpu_mach (void);

#define TARGET_FORMAT (zpu_arch_format ())
extern const char *zpu_arch_format (void);

#define LISTING_WORD_SIZE 1	/* A word is 1 bytes */
#define LISTING_LHS_WIDTH 4	/* One word on the first line */
#define LISTING_LHS_WIDTH_SECOND 4	/* One word on the second line */
#define LISTING_LHS_CONT_LINES 4	/* And 4 lines max */
#define LISTING_HEADER zpu_listing_header ()
extern const char *zpu_listing_header (void);

/* Permit temporary numeric labels.  */
#define LOCAL_LABELS_FB 1

#define tc_init_after_args zpu_init_after_args
extern void zpu_init_after_args (void);



#define DWARF2_LINE_MIN_INSN_LENGTH 1

/* Use 32-bit address to represent a symbol address so that we can
   represent them with their page number.  */
#define DWARF2_ADDR_SIZE(bfd) 4

/* We don't need to handle .word strangely.  */
#define WORKING_DOT_WORD

#define md_number_to_chars           number_to_chars_bigendian

#define TC_HANDLES_FX_DONE

#define DIFF_EXPR_OK		/* .-foo gets turned into PC relative relocs */

#define md_operand(x)

#define TC_FORCE_RELOCATION(fix) tc_zpu_force_relocation (fix)
extern int tc_zpu_force_relocation (struct fix *);

#define tc_fix_adjustable(X) tc_zpu_fix_adjustable(X)
extern int tc_zpu_fix_adjustable (struct fix *);
