;; GCC machine description for Zylin CPU
;; Copyright (C) 1992, 1993, 1994, 1995, 2004 Free Software Foundation, Inc.
;;
;; Written by Oyvind Harboe <oyvind.harboe@zylin.com>
;;
;; This file is part of GNU CC.
;;
;; GNU CC is free software; you can redistribute it and/or modify
;; it under the terms of the GNU General Public License as published by
;; the Free Software Foundation; either version 2, or (at your option)
;; any later version.
;;
;; GNU CC is distributed in the hope that it will be useful,
;; but WITHOUT ANY WARRANTY; without even the implied warranty of
;; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
;; GNU General Public License for more details.
;;
;; You should have received a copy of the GNU General Public License
;; along with GNU CC; see the file COPYING.  If not, write to
;; the Free Software Foundation, 59 Temple Place - Suite 330,
;; Boston, MA 02111-1307, USA.  */



(define_constants
  [
   (R_STACK_REG 8)
   (R_STACK_REG_LAST 31)
   (R_SP 32)
   (R_PC 33)
/* fake frame/arg pointer. These are impossible registers that must be eliminated
 * or compilation will fail
 */
(R_FAKE_FP 34)
(R_FAKE_AP 35)  ]
)




;; 32 bit move
(define_expand "movsf"
   [(set (match_operand:SF 0 "nonimmediate_operand" "=g")
	(match_operand:SF 1 "general_operand" "g"))]
  ""
{
zpu_expand_set(SFmode, operands);
DONE;
})

;; 32 bit move
(define_expand "movsi"
   [(set (match_operand:SI 0 "nonimmediate_operand" "=g")
	(match_operand:SI 1 "general_operand" "g"))]
  ""
{
zpu_expand_set(SImode, operands);
DONE;
})


  
;; 16 bit move
(define_expand "movhi"
   [(set (match_operand:HI 0 "nonimmediate_operand" "=g")
	(match_operand:HI 1 "general_operand" "g"))]
  ""
{
zpu_expand_set(HImode, operands);
DONE;
})

;; 8 bit moves
(define_expand "movqi"
   [(set (match_operand:QI 0 "nonimmediate_operand" "=g")
	(match_operand:QI 1 "general_operand" "g"))]
  ""
{
zpu_expand_set(QImode, operands);
DONE;
})

;; Catch some special cases early
(define_insn "*changestackpointer"
  [(set (reg:SI R_SP)
       (plus:SI (reg:SI R_SP)
                 (match_operand:SI 0 "immediate_operand" "i")))]
  ""
  "*return zpu_changestackpointer(operands, insn);")




(define_insn "*generic_move_si"
   [(set (match_operand:SI 0 "nonimmediate_operand" "=g")
	(match_operand:SI 1 "general_operand" "g"))]
  ""
  "*return zpu_generate_move(operands, insn);")

(define_insn "*generic_move_sf"
   [(set (match_operand:SF 0 "nonimmediate_operand" "=g")
	(match_operand:SF 1 "general_operand" "g"))]
  ""
  "*return zpu_generate_move(operands, insn);")

(define_insn "*generic_move_hi"
   [(set (match_operand:HI 0 "nonimmediate_operand" "=g")
	(match_operand:HI 1 "general_operand" "g"))]
  ""
  "*return zpu_generate_move(operands, insn);")




(define_insn "*generic_move_qi"
   [(set (match_operand:QI 0 "nonimmediate_operand" "=g")
	(match_operand:QI 1 "general_operand" "g"))]
  ""
  "*return zpu_generate_move(operands, insn);")

;; 64 bit stuff taken from m32r.
;; required in order to support SIMD emulation
(define_expand "movdi"
  [(set (match_operand:DI 0 "nonimmediate_operand" "")
	(match_operand:DI 1 "general_operand" ""))]
  ""
  "
{
  if (GET_CODE (operands[0]) == MEM)
    operands[1] = force_reg (DImode, operands[1]);
}")

(define_insn "*movdi_insn"
  [(set (match_operand:DI 0 "move_double_dest_operand" "=r,r,r,r,m")
	(match_operand:DI 1 "move_double_src_operand" "r,n,F,m,r"))]
  "register_operand (operands[0], DImode) || register_operand (operands[1], DImode)"
  "#")

(define_split
  [(set (match_operand:DI 0 "move_double_dest_operand" "")
	(match_operand:DI 1 "move_double_src_operand" ""))]
  "reload_completed"
  [(match_dup 2)]
  "operands[2] = gen_split_move_double (operands);")


(define_expand "movdf"
  [(set (match_operand:DF 0 "nonimmediate_operand" "")
	(match_operand:DF 1 "general_operand" ""))]
  ""
  "
{
  if (GET_CODE (operands[0]) == MEM)
    operands[1] = force_reg (DFmode, operands[1]);
}")

(define_insn "*movdf_insn"
  [(set (match_operand:DF 0 "move_double_dest_operand" "=r,r,r,r,m")
	(match_operand:DF 1 "move_double_src_operand" "r,n,F,m,r"))]
  "register_operand (operands[0], DFmode) || register_operand (operands[1], DFmode)"
  "#")

(define_split
  [(set (match_operand:DF 0 "move_double_dest_operand" "")
	(match_operand:DF 1 "move_double_src_operand" ""))]
  "reload_completed"
  [(match_dup 2)]
  "operands[2] = gen_split_move_double (operands);")



(define_expand "addsi3"
  [(set (match_operand:SI 0 "nonimmediate_operand" "=g")
        (plus:SI (match_operand:SI 1 "general_operand" "g")
                 (match_operand:SI 2 "general_operand" "g")))]
  ""
  "")

(define_expand "multsi3"
  [(set (match_operand:SI 0 "nonimmediate_operand" "=g")
        (mult:SI (match_operand:SI 1 "general_operand" "g")
                 (match_operand:SI 2 "general_operand" "g")))]
  ""
  "")
  
(define_expand "iorsi3"
  [(set (match_operand:SI 0 "nonimmediate_operand" "=g")
        (ior:SI (match_operand:SI 1 "general_operand" "g")
                 (match_operand:SI 2 "general_operand" "g")))]
  ""
  "")
  
(define_expand "andsi3"
  [(set (match_operand:SI 0 "nonimmediate_operand" "=g")
        (and:SI (match_operand:SI 1 "general_operand" "g")
                 (match_operand:SI 2 "general_operand" "g")))]
  ""
  "")

(define_expand "xorsi3"
  [(set (match_operand:SI 0 "nonimmediate_operand" "=g")
        (xor:SI (match_operand:SI 1 "general_operand" "g")
                 (match_operand:SI 2 "general_operand" "g")))]
  ""
  "")
  
(define_expand "subsi3"
  [(set (match_operand:SI 0 "nonimmediate_operand" "=g")
        (minus:SI (match_operand:SI 1 "general_operand" "g")
                  (match_operand:SI 2 "general_operand" "g")))]
  ""
  "")
  
(define_expand "ashrsi3"
  [(set (match_operand:SI 0 "nonimmediate_operand" "=g")
        (ashiftrt:SI (match_operand:SI 1 "general_operand" "g")
                  (match_operand:SI 2 "general_operand" "g")))]
  ""
  "")
  
(define_expand "lshrsi3"
  [(set (match_operand:SI 0 "nonimmediate_operand" "=g")
        (lshiftrt:SI (match_operand:SI 1 "general_operand" "g")
                  (match_operand:SI 2 "general_operand" "g")))]
  ""
  "")
  
(define_expand "ashlsi3"
  [(set (match_operand:SI 0 "nonimmediate_operand" "=g")
        (ashift:SI (match_operand:SI 1 "general_operand" "g")
                  (match_operand:SI 2 "general_operand" "g")))]
  ""
  "")
  
(define_expand "negsi2"
  [(set (match_operand:SI 0 "nonimmediate_operand" "=g")
        (neg:SI (match_operand:SI 1 "general_operand" "g")))]
  ""
  "")
  
(define_expand "one_cmplsi2"
  [(set (match_operand:SI 0 "nonimmediate_operand" "=g")
        (not:SI (match_operand:SI 1 "general_operand" "g")))]
  ""
  "")

(define_insn "zero_extendqisi2"
  [(set (match_operand:SI 0 "nonimmediate_operand" "=g")
	(zero_extend:SI (match_operand:QI 1 "general_operand" "g")))]
  ""
  "*return zpu_generate_set(insn);")

(define_insn "zero_extendhisi2"
  [(set (match_operand:SI 0 "nonimmediate_operand" "=g")
	(zero_extend:SI (match_operand:HI 1 "general_operand" "g")))]
  ""
  "*return zpu_generate_set(insn);")


;; we can't have e.g. and, ior, xor, etc. as a valid operand,
;; but we can have it as an operator to an instruction
(define_insn "*binaryop"
  [(set (match_operand:SI 0 "nonimmediate_operand" "=g")
        (match_operator:SI 1 "zpu_binary_operator"
	       [(match_operand:SI 2 "general_operand" "g")
	        (match_operand:SI 3 "general_operand" "g")]))]
  ""
  "*return zpu_generate_move(operands, insn);")

(define_insn "*binaryop2"
  [(set (match_operand:SI 0 "nonimmediate_operand" "=g")
        (match_operator:SI 1 "zpu_binary_operator"
	       [(match_operator:SI 2 "zpu_binary_operator"
	         [(match_operand:SI 3 "general_operand" "g")
	          (match_operand:SI 4 "general_operand" "g")])
	        (match_operator:SI 5 "zpu_binary_operator"
	         [(match_operand:SI 6 "general_operand" "g")
	          (match_operand:SI 7 "general_operand" "g")])
	          ]))]
  ""
  "*return zpu_generate_move(operands, insn);")

(define_insn "*binaryop2a"
  [(set (match_operand:SI 0 "nonimmediate_operand" "=g")
        (match_operator:SI 1 "zpu_binary_operator"
			[
					(match_operator:SI 2 "zpu_binary_operator"
			    		[
							(match_operand:SI 3 "general_operand" "g")
						    (match_operand:SI 4 "general_operand" "g")
						] 
					)
					(match_operand:SI 5 "general_operand" "g") 
			]
		)
	)]
  ""
  "*return zpu_generate_move(operands, insn);")

(define_insn "*binaryop3"
  [(set (match_operand:SI 0 "nonimmediate_operand" "=g")
        (match_operator:SI 1 "zpu_binary_operator"
	       [(match_operand:SI 2 "general_operand" "g")
	        (match_operator:SI 3 "zpu_unary_operator"
	       [(match_operand:SI 4 "general_operand" "g")])]))]
  ""
  "*return zpu_generate_move(operands, insn);")


(define_insn "*unaryop"
  [(set (match_operand:SI 0 "nonimmediate_operand" "=g")
        (match_operator:SI 1 "zpu_unary_operator"
	       [(match_operand:SI 2 "general_operand" "g")]))]
  ""
  "*return zpu_generate_move(operands, insn);")

(define_insn "jump"
  [(set (pc) (label_ref (match_operand 0 "" "")))]
  ""
  "*return zpu_jump_pcrel(operands, insn);")

 
(define_insn "indirect_jump"
  [(set (pc) (match_operand:SI 0 "general_operand" "g"))]
  ""
  "*return zpu_jump(operands, insn);")

(define_insn "nop"
  [(const_int 0)]
  ""
  "nop")
 
(define_insn "call"
  [(call (match_operand 0 "memory_operand" "m")
	 (match_operand:SI 1 "immediate_operand" "i")) ]
  ""
  "*return zpu_call(operands, insn);")

(define_insn "call_value"
  [(set (match_operand 0 "nonimmediate_operand" "=g")
     (call (match_operand 1 "memory_operand" "m")
	    (match_operand:SI 2 "immediate_operand" "i")))]
  ""
  "*return zpu_call_value(operands, insn);")




(define_insn "tablejump"
  [(set (pc) (match_operand:SI 0 "general_operand" "g"))
   (use (label_ref (match_operand 1 "" "")))]
  ""
  "*return zpu_table_jump(operands, insn);")

  
(define_expand "prologue"
  [(const_int 1)]
  ""
  "
{
  zpu_expand_prologue ();
  DONE;
}")

(define_expand "epilogue"
  [(const_int 2)]
  ""
  "
{
  zpu_expand_epilogue ();
  DONE;
}")

;; ZPU poppc instruction is generated during RTL generation phase
(define_insn "zpu_return"
  [(return)]
  ""
  "*
{
return zpu_asm_multi(\"poppc\", operands, 1);
}")


(define_insn "*cbranchsi4_not_zero"
  [(set (pc) (if_then_else
	      (ne
	        (match_operand:SI 0 "nonimmediate_operand" "g")
	        (match_operand:SI 2 "general_operand" "g"))
	      (label_ref (match_operand 1 "" ""))
	      (pc)))]
  "!((GET_CODE(operands[2])!=CONST_INT)||INTVAL(operands[2])!=0)"
  "*return zpu_generate_if_not_zero_then_else(operands, insn);")

(define_expand "cbranchsi4"
  [(set (pc) (if_then_else
	      (match_operator:SI 0 "comparison_operator"
	       [(match_operand:SI 1 "general_operand" "g")
	        (match_operand:SI 2 "general_operand" "g")])
	      (label_ref (match_operand 3 "" ""))
	      (pc)))]
  ""
  "
  if (GET_CODE(operands[1])==CONSTANT_P_RTX)
  {
	/* we need to have constants in operand #1 reloaded as e.g. purge CONSTANT_P_RTX 
	   isn't able to dive into anything more complicated than simple sets. 
	   
	   We only need a quickfix here, because we'll be porting to GCC 4.0 at some point and
	   to quote a CVS HEAD changelog:
	   
	   rtl.def (CONSTANT_P_RTX): Die die die.
	   */
  	operands[1]=force_reg(SImode, operands[1]);
  }
  
  ")

  
(define_insn "*cbranchsi4"
  [(set (pc) (if_then_else
	      (match_operator:SI 0 "comparison_operator"
	       [(match_operand:SI 1 "general_operand" "g")
	        (match_operand:SI 2 "general_operand" "g")])
	      (label_ref (match_operand 3 "" ""))
	      (pc)))]
  ""
  "*return zpu_generate_if_then_else(operands, insn);")

(define_expand "nonlocal_goto"
  [(match_operand:SI 0 "" "")
   (match_operand:SI 1 "general_operand" "")
   (match_operand:SI 2 "general_operand" "")
   (match_operand:SI 3 "general_operand" "")]
  ""
  "
{
  rtx framePointer = operands[0];
  rtx handler = operands[1]; /* ok */
  rtx stack = operands[2]; /* ok  */
  rtx chain = operands[3];

	/* 
	the trick here is to finish accessing the pointer to the destination
	address before we restore the stack pointer.
	
	The register in which the jump address is kept might
	be in the current stack frame, in which case it is invalid after the
	stack pointer has been restored.


	??? How do we know whether or not to restore the frame pointer???	
	*/
  emit_move_insn (hard_frame_pointer_rtx, framePointer);
  
  /* save jump address on stack */
  emit_move_insn (gen_rtx_MEM(SImode, plus_constant(stack, -4)), handler);
  
  /* move address of label into static chain register */
  emit_move_insn (static_chain_rtx, chain);

  emit_move_insn (stack_pointer_rtx, plus_constant(stack, -4));

  emit_insn (gen_rtx_USE (VOIDmode, hard_frame_pointer_rtx));
  emit_insn (gen_rtx_USE (VOIDmode, static_chain_rtx));
  emit_insn (gen_rtx_USE (VOIDmode, stack_pointer_rtx));
  
  emit_jump_insn (gen_zpu_return());
  emit_barrier ();
  DONE;
}")


/* 
KLUDGE!!!! why isn't nonlocal_goto enough? 

On the surface of it, the standard builtin_longjmp expansion will
swap the first&last argument to nonlocal_goto....

*/
(define_expand "builtin_longjmp"
  [(use (match_operand:SI 0 "general_operand" "g"))]
  ""
{
  /* The elements of the buffer are, in order:  */
  int W = GET_MODE_SIZE (Pmode);
  rtx fp = gen_rtx_MEM (Pmode, operands[0]);
  rtx lab = gen_rtx_MEM (Pmode, plus_constant (operands[0], 1*W));
  rtx stack = gen_rtx_MEM (Pmode, plus_constant (operands[0], 2*W));

  /* This bit is similar to expand_builtin_longjmp except that it
     restores $gp as well.  */
  emit_move_insn (hard_frame_pointer_rtx, fp);
  
  emit_move_insn (gen_rtx_MEM(SImode, plus_constant(stack, -4)), lab);

  emit_move_insn (stack_pointer_rtx, plus_constant(stack, -4));
  
  emit_insn (gen_rtx_USE (VOIDmode, hard_frame_pointer_rtx));
  emit_insn (gen_rtx_USE (VOIDmode, stack_pointer_rtx));

  emit_jump_insn (gen_zpu_return());
  emit_barrier ();
  DONE;
})


