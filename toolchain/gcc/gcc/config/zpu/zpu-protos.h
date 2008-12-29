/* Prototypes for exported functions defined in m68hc11.c
   Copyright (C) 1999, 2000, 2001, 2002, 2003, 2004 Free Software Foundation, Inc.
   Contributed by Stephane Carrez (stcarrez@nerim.fr)

This file is part of GCC.

GCC is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2, or (at your option)
any later version.

GCC is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with GCC; see the file COPYING.  If not, write to
the Free Software Foundation, 59 Temple Place - Suite 330,
Boston, MA 02111-1307, USA.  */



extern void zpu_expand_move (enum machine_mode, rtx, rtx);
void print_operand (FILE *file, rtx op, int letter);
int hard_register_operand (rtx op, enum machine_mode mode);
int soft_register_operand (rtx op, enum machine_mode mode);
int hard_memory_operand (rtx op, enum machine_mode mode);
int stack_pointer_operand (rtx op, enum machine_mode mode);
int any_operand (rtx op, enum machine_mode mode);
int any_nonimmediate_operand (rtx op, enum machine_mode mode);
int any_operator (rtx op, enum machine_mode mode);

int address_plus_operand (register rtx op, enum machine_mode mode);
const char *generate_jump(rtx loc, rtx insn);
#ifdef RTX_CODE
const char *generate_branch(enum rtx_code code, rtx loc, rtx insn);
#endif

const char *zpu_generate_move(rtx operands[], rtx insn);
const char *zpu_changestackpointer(rtx operands[], rtx insn);
const char *zpu_generate_if_then_else(rtx operands[], rtx insn);
const char *zpu_generate_if_zero_then_else(rtx operands[], rtx insn);
const char *zpu_generate_if_not_zero_then_else(rtx operands[], rtx insn);
const char *zpu_generate_reload(rtx operands[], rtx insn);
void zpu_prologue(FILE *file, HOST_WIDE_INT size);
void zpu_epilogue(FILE *file, HOST_WIDE_INT size);
const char *zpu_generate_binop(rtx operands[], rtx insn, const char *binop);
int zpu_legitimate_address(enum machine_mode mode, rtx x, int strict);
const char *zpu_generate_conditional_move(rtx operands[], rtx insn);
const char *zpu_jump(rtx operands[], rtx insn);
const char *zpu_jump_pcrel(rtx operands[], rtx insn);
const char *zpu_push(rtx operands[], rtx insn);
int zpu_nonimmediate(rtx op, enum machine_mode mode);
int zpu_initial_elimination_offset (int from, int to);
void zpu_expand_epilogue (void);
void zpu_expand_prologue (void);
rtx zpu_return_addr_rtx(void);
const char *zpu_call(rtx operands[], rtx insn);
const char *zpu_call_value(rtx operands[], rtx insn);

void zpu_start_asm(FILE *file);
const char * zpu_asm_multi(const char *format, rtx *operands, int byteCount);
int operand_check (char c, rtx op);
const char *zpu_table_jump(rtx operands[], rtx insn);

void zpu_expand_set(enum machine_mode mode, rtx operands[]);
const char *zpu_call(rtx operands[], rtx insn);
int zpu_binary_operator (rtx op  ATTRIBUTE_UNUSED, enum machine_mode mode ATTRIBUTE_UNUSED);
int zpu_unary_operator (rtx op  ATTRIBUTE_UNUSED, enum machine_mode mode ATTRIBUTE_UNUSED);
int zpu_return_pops_args (tree fundecl ATTRIBUTE_UNUSED, tree funtype, int size);
extern bool zpu_extra_constraint (rtx, int);
const char *zpu_generate_set(rtx insn);
int
move_double_dest_operand (rtx op, enum machine_mode mode);
int
move_double_src_operand (rtx op, enum machine_mode mode);
rtx
gen_split_move_double (rtx operands[]);
