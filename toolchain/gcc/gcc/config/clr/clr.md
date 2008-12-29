;; clr.md
;; Jeremy Singer (jds31@cl.cam.ac.uk)
;; 26 Dec 02

;; $Id: clr.md,v 1.13 2003/01/18 23:46:29 jds31 Exp jds31 $

;; GCC machine description file
;; for the Microsoft .NET 
;; Common Language Runtime (clr).

;; This is just a very simple implementation,
;; to see what kind of results we can get.
;; Instruction patterns are heavily based
;; on egcs-jvm, the Java Virtual Machine
;; gcc backend by Trent Waddington.

;; The assembler output is in Microsoft
;; ILAsm format, as described in the
;; ECMA .net specification documents,
;; (ECMA standard 335).
;; I used Serge Lidin's book
;; "Inside Microsoft .NET IL Assembler"
;; to help me understand the opcodes,
;; and the internal details of the clr.



;; No-op

(define_insn "nop"
  [(const_int 0)]
  ""
  "nop"
  )


;; Move instructions

(define_insn "movsi"
  [(set (match_operand:SI 0 "general_operand" "=r,r,r,m,m")
	(match_operand:SI 1 "general_operand" "r,i,m,r,i"))]
	""
	"@
	ldloc %1\\n\\tstloc %0\\n
	ldc.i4 %1\\n\\tstloc %0\\n
	%1\\n\\tldind.i4\\n\\tstloc %0\\n
	%0\\n\\tldloc %1\\n\\tstind.i4\\n
	%0\\n\\tldc.i4 %1\\n\\tstind.i4\\n")

(define_insn "movhi"
  [(set (match_operand:HI 0 "general_operand" "=r,r,r,m,m")
	(match_operand:HI 1 "general_operand" "r,i,m,r,i"))]
	""
	"@
	ldloc %1\\n\\tstloc %0\\n
        ldc.i4 %1\\n\\tstloc %0\\n
	%1\\n\\tldind.i2\\n\\tstloc %0\\n  ##FIXME! -this is signed, i think
	%0\\n\\tldloc %1\\n\\tstind.i2\\n
	%0\\n\\tldc.i4 %1\\n\\tstind.i2\\n"
	)

(define_insn "movqi"
  [(set (match_operand:QI 0 "nonimmediate_operand" "=r,r,r,m,m")
	(match_operand:QI 1 "general_operand" "r,i,m,r,i"))]
	""
	"@
	ldloc %1\\ns\\ttloc %0\\n
        ldc.i4 %1\\n\\tstloc %0\\n
	%1\\n\\tldind.i1\\n\\tstloc %0\\n ## FIXME! -this is signed, i think
	%0\\n\\tldloc %1\\n\\tstind.i1\\n
	%0\\n\\tldc.i4 %1\\n\\tstind.i1\\n"
	)


;; Arithmetic instructions

(define_insn "negsi2"
  [(set (match_operand:SI 0 "register_operand" "=r")
	(neg:SI (match_operand:SI 1 "register_operand" "r")))]
  ""
  "ldloc %1\\n\\tneg\\n\\tstloc %0\\n"
  )

(define_insn "addsi3"
  [(set (match_operand:SI 0 "register_operand" "=r,r,r,r")
	(plus:SI (match_operand:SI 1 "register_operand" "r,r,i,i")
	         (match_operand:SI 2 "register_operand" "r,i,r,i")))]
	""
	"@
	ldloc %1\\n\\tldloc %2\\n\\tadd\\n\\tstloc %0\\n
	ldloc %1\\n\\tldc.i4 %2\\n\\tadd\\n\\tstloc %0\\n
	ldc.i4 %1\\n\\tldloc %2\\n\\tadd\\n\\tstloc %0\\n
	ldc.i4 %1\\n\\tldc.i4 %2\\n\\tadd\\n\\tstloc %0\\n"
	)

(define_insn "mulsi3"
  [(set (match_operand:SI 0 "register_operand" "=r,r,r,r")
	(mult:SI (match_operand:SI 1 "register_operand" "r,r,i,i")
	         (match_operand:SI 2 "register_operand" "r,i,r,i")))]
	""
	"@
	ldloc %1\\n\\tldloc %2\\n\\tmul\\n\\tstloc %0\\n
	ldloc %1\\n\\tldc.i4 %2\\n\\tmul\\n\\tstloc %0\\n
	ldc.i4 %1\\n\\tldloc %2\\n\\tmul\\n\\tstloc %0\\n
	ldc.i4 %1\\n\\tldc.i4 %2\\n\\tmul\\n\\tstloc %0\\n"
	)

(define_insn "subsi3"
  [(set (match_operand:SI 0 "register_operand" "=r,r,r,r")
	(minus:SI (match_operand:SI 1 "register_operand" "r,r,i,i")
	          (match_operand:SI 2 "register_operand" "r,i,r,i")))]
	""
	"@
	ldloc %1\\n\\tldloc %2\\n\\tsub\\n\\tstloc %0\\n
	ldloc %1\\n\\tldc.i4 %2\\n\\tsub\\n\\tstloc %0\\n
	ldc.i4 %1\\n\\tldloc %2\\n\\tsub\\n\\tstloc %0\\n
	ldc.i4 %1\\n\\tldc.i4 %2\\n\\tsub\\n\\tstloc %0\\n"
	)

(define_insn "divsi3"
  [(set (match_operand:SI 0 "register_operand" "=r,r,r,r")
	(div:SI (match_operand:SI 1 "register_operand" "r,r,i,i")
	        (match_operand:SI 2 "register_operand" "r,i,r,i")))]
	""
	"@
	ldloc %1\\n\\tldloc %2\\n\\tdiv\\n\\tstloc %0\\n
	ldloc %1\\n\\tldc.i4 %2\\n\\tdiv\\n\\tstloc %0\\n
	ldc.i4 %1\\n\\tldloc %2\\n\\tdiv\\n\\tstloc %0\\n
	ldc.i4 %1\\n\\tldc.i4 %2\\n\\tdiv\\n\\tstloc %0\\n"
	)

(define_insn "udivsi3"
  [(set (match_operand:SI 0 "register_operand" "=r,r,r,r")
	(udiv:SI (match_operand:SI 1 "register_operand" "r,r,i,i")
	         (match_operand:SI 2 "register_operand" "r,i,r,i")))]
	""
	"@
	ldloc %1\\n\\tldloc %2\\n\\tdiv.un\\n\\tstloc %0\\n
	ldloc %1\\n\\tldc.i4 %2\\n\\tdiv.un\\n\\tstloc %0\\n
	ldc.i4 %1\\n\\tldloc %2\\n\\tdiv.un\\n\\tstloc %0\\n
	ldc.i4 %1\\n\\tldc.i4 %2\\n\\tdiv.un\\n\\tstloc %0\\n"
	)

(define_insn "modsi3"
  [(set (match_operand:SI 0 "register_operand" "=r,r,r,r")
	(mod:SI (match_operand:SI 1 "register_operand" "r,r,i,i")
	        (match_operand:SI 2 "register_operand" "r,i,r,i")))]
	""
	"@
	ldloc %1\\n\\tldloc %2\\n\\trem\\n\\tstloc %0\\n
	ldloc %1\\n\\tldc.i4 %2\\n\\trem\\n\\tstloc %0\\n
	ldc.i4 %1\\n\\tldloc %2\\n\\trem\\n\\tstloc %0\\n
	ldc.i4 %1\\n\\tldc.i4 %2\\n\\trem\\n\\tstloc %0\\n"
	)

(define_insn "umodsi3"
  [(set (match_operand:SI 0 "register_operand" "=r,r,r,r")
	(umod:SI (match_operand:SI 1 "register_operand" "r,r,i,i")
	         (match_operand:SI 2 "register_operand" "r,i,r,i")))]
	""
	"@
	ldloc %1\\n\\tldloc %2\\n\\trem.un\\n\\tstloc %0\\n
	ldloc %1\\n\\tldc.i4 %2\\n\\trem.un\\n\\tstloc %0\\n
	ldc.i4 %1\\n\\tldloc %2\\n\\trem.un\\n\\tstloc %0\\n
	ldc.i4 %1\\n\\tldc.i4 %2\\n\\trem.un\\n\\tstloc %0\\n"
	)


;; Logical instructions

(define_insn "one_cmplsi2"
  [(set (match_operand:SI 0 "register_operand" "=r")
	(not:SI (match_operand:SI 1 "register_operand" "r")))]
  ""
  "ldloc %1\\n\\tnot\\n\\tstloc %0\\n"
  )

(define_insn "andsi3"
  [(set (match_operand:SI 0 "register_operand" "=r,r,r,r")
	(and:SI (match_operand:SI 1 "register_operand" "r,r,i,i")
	        (match_operand:SI 2 "register_operand" "r,i,r,i")))]
	""
	"@
	ldloc %1\\n\\tldloc %2\\n\\tand\\n\\tstloc %0\\n
	ldloc %1\\n\\tldc.i4 %2\\n\\tand\\n\\tstloc %0\\n
	ldc.i4 %1\\n\\tldloc %2\\n\\tand\\n\\tstloc %0\\n
	ldc.i4 %1\\n\\tldc.i4 %2\\n\\tand\\n\\tstloc %0\\n"
	)

(define_insn "iorsi3"
  [(set (match_operand:SI 0 "register_operand" "=r,r,r,r")
	(ior:SI (match_operand:SI 1 "register_operand" "r,r,i,i")
	        (match_operand:SI 2 "register_operand" "r,i,r,i")))]
	""
	"@
	ldloc %1\\n\\tldloc %2\\n\\tor\\n\\tstloc %0\\n
	ldloc %1\\n\\tldc.i4 %2\\n\\tor\\n\\tstloc %0\\n
	ldc.i4 %1\\n\\tldloc %2\\n\\tor\\n\\tstloc %0\\n
	ldc.i4 %1\\n\\tldc.i4 %2\\n\\tor\\n\\tstloc %0\\n"
	)

(define_insn "xorsi3"
  [(set (match_operand:SI 0 "register_operand" "=r,r,r,r")
	(xor:SI (match_operand:SI 1 "register_operand" "r,r,i,i")
	        (match_operand:SI 2 "register_operand" "r,i,r,i")))]
	""
	"@
	ldloc %1\\n\\tldloc %2\\n\\txor\\n\\tstloc %0\\n
	ldloc %1\\n\\tldc.i4 %2\\n\\txor\\n\\tstloc %0\\n
	ldc.i4 %1\\n\\tldloc %2\\n\\txor\\n\\tstloc %0\\n
	ldc.i4 %1\\n\\tldc.i4 %2\\n\\txor\\n\\tstloc %0\\n"
	)


;; Shift instructions

;; FIXME - is the .NET clr 'shr' instr arithmetic or logical right shift?

(define_insn "ashrsi3"
  [(set (match_operand:SI 0 "register_operand" "=r,r,r,r")
	(ashiftrt:SI (match_operand:SI 1 "register_operand" "r,r,i,i")
	             (match_operand:SI 2 "register_operand" "r,i,r,i")))]
	""
	"@
	ldloc %1\\n\\tldloc %2\\n\\tshr\\n\\tstloc %0\\n
	ldloc %1\\n\\tldc.i4 %2\\n\\tshr\\n\\tstloc %0\\n
	ldc.i4 %1\\n\\tldloc %2\\n\\tshr\\n\\tstloc %0\\n
	ldc.i4 %1\\n\\tldc.i4 %2\\n\\tshr\\n\\tstloc %0\\n"
	)

(define_insn "lshrsi3"
  [(set (match_operand:SI 0 "register_operand" "=r,r,r,r")
	(lshiftrt:SI (match_operand:SI 1 "register_operand" "r,r,i,i")
	             (match_operand:SI 2 "register_operand" "r,i,r,i")))]
	""
	"@
	ldloc %1\\n\\tldloc %2\\n\\tshr.un\\n\\tstloc %0\\n
	ldloc %1\\n\\tldc.i4 %2\\n\\tshr.un\\n\\tstloc %0\\n
	ldc.i4 %1\\n\\tldloc %2\\n\\tshr.un\\n\\tstloc %0\\n
	ldc.i4 %1\\n\\tldc.i4 %2\\n\\tshr.un\\n\\tstloc %0\\n"
	)

(define_insn "ashlsi3"
  [(set (match_operand:SI 0 "register_operand" "=r,r,r,r")
	(ashift:SI (match_operand:SI 1 "register_operand" "r,r,i,i")
	           (match_operand:SI 2 "register_operand" "r,i,r,i")))]
	""
	"@
	ldloc %1\\n\\tldloc %2\\n\\tshl\\n\\tstloc %0\\n
	ldloc %1\\n\\tldc.i4 %2\\n\\tshl\\n\\tstloc %0\\n
	ldc.i4 %1\\n\\tldloc %2\\n\\tshl\\n\\tstloc %0\\n
	ldc.i4 %1\\n\\tldc.i4 %2\\n\\tshl\\n\\tstloc %0\\n"
	)


;; Compare instructions

;; We simply store the two operands
;; that are to be compared onto the
;; operand stack. The actual comparison
;; will take place as part of the branch
;; instruction, which is guaranteed
;; to be the next insn in the RTL.

(define_insn "cmpsi"
  [(set (cc0)
	(compare (match_operand:SI 0 "general_operand" "r,r,i,i")
		 (match_operand:SI 1 "general_operand" "r,i,r,i")))]
  ""
  "@
   ldloc %0\\n\\tldloc %1\\n
   ldloc %0\\n\\tldc.i4 %1\\n
   ldc.i4 %0\\n\\tldloc %1\\n
   ldc.i4 %0\\n\\tldc.i4 %1\\n"
   )


;; Conditional branches

;; The CLR does not have a condition code
;; register. Instead, we assume that
;; the operands to be compared are
;; the top two items on the operand stack.
;; All CLR conditional branch insns inspect
;; these top two items and pop them off
;; the stack. Thus we must be certain
;; that the operands are there already -
;; but this is guaranteed for us bu gcc,
;; since each conditional branch insn in
;; RTL is immediately preceded by a cmpsi
;; insn.

(define_insn "beq"
  [(set (pc)
	(if_then_else (eq (cc0) (const_int 0))
		      (label_ref (match_operand 0 "" ""))
		      (pc)))]
  ""
  "beq %l0")


(define_insn "bne"
  [(set (pc)
	(if_then_else (ne (cc0) (const_int 0))
		      (label_ref (match_operand 0 "" ""))
		      (pc)))]
  ""
  "bne.un %l0")

(define_insn "bgt"
  [(set (pc)
	(if_then_else (gt (cc0) (const_int 0))
		      (label_ref (match_operand 0 "" ""))
		      (pc)))]
  ""
  "bgt %l0")

(define_insn "bgtu"
  [(set (pc)
	(if_then_else (gtu (cc0) (const_int 0))
		      (label_ref (match_operand 0 "" ""))
		      (pc)))]
  ""
  "bgt.un %l0")

(define_insn "blt"
  [(set (pc)
	(if_then_else (lt (cc0) (const_int 0))
		      (label_ref (match_operand 0 "" ""))
		      (pc)))]
  ""
  "blt %l0")

(define_insn "bltu"
  [(set (pc)
	(if_then_else (ltu (cc0) (const_int 0))
		      (label_ref (match_operand 0 "" ""))
		      (pc)))]
  ""
  "blt.un %l0")

(define_insn "bge"
  [(set (pc)
	(if_then_else (ge (cc0) (const_int 0))
		      (label_ref (match_operand 0 "" ""))
		      (pc)))]
  ""
  "bge %l0")

(define_insn "bgeu"
  [(set (pc)
	(if_then_else (geu (cc0) (const_int 0))
		      (label_ref (match_operand 0 "" ""))
		      (pc)))]
  ""
  "bge.un %l0")

(define_insn "ble"
  [(set (pc)
	(if_then_else (le (cc0) (const_int 0))
		      (label_ref (match_operand 0 "" ""))
		      (pc)))]
  ""
  "ble %l0")

(define_insn "bleu"
  [(set (pc)
	(if_then_else (leu (cc0) (const_int 0))
		      (label_ref (match_operand 0 "" ""))
		      (pc)))]
  ""
  "ble.un %l0")

;; FIXME - we should also have anonymous
;; patterns for each of the possible 
;; reverse conditional branches - necessary
;; because jump optimisation can turn direct 
;; conditional branches into reverse
;; conditional branches.


;; Direct jump

(define_insn "jump"
  [(set (pc)
	(label_ref (match_operand 0 "" "")))]
  ""
  "br %l0")


;; Indirect jump

;; FIXME - is it possible to 
;; perform indirect jumps on 
;; clr?

(define_insn "indirect_jump"
  [(set (pc)
	(match_operand:SI 0 "register_operand" "r"))]
  ""
  "indjmp %0")


;; Calls

;; Procedure call - no return value

;; jds31 - old versions follow
;; - we used these for args
;; passed on stack frame

;;(define_insn "call"
;; [(parallel [(call (mem:QI (match_operand:SI 0 "" ""))
;;		    (match_operand:SI 1 "" ""))
;;	     (clobber (reg:SI 16))])]
;;  ""
;;  "call %0")

;; Function call - returns a value in a register

;;(define_insn "call_value"
;;  [(parallel [(set (match_operand:SI 0 "" "")
;;		   (call (mem:QI (match_operand:SI 1 "" ""))
;;			 (match_operand:SI 2 "" "")))
;;	      (clobber (reg:SI 16))])]
;;  ""
;;  "callv %1")

;; jds31 - new versions follow
;; - we use these for args passed
;; in registers
;; N.B. cut-and-pasted straight
;; from egcs-jvm md file ...


;; new call instructions

(define_insn "clr_call"
  [(call (mem:QI (match_operand:SI 0 "general_operand" "g"))
	         (match_operand:SI 1 "immediate_operand" "i"))]
  ""
;;   "call %0\\n")
  "* 
     static char s[1024];	
     static char s1[40];	
     int i;
     int num_reg_args = -1;

     /* jds31 - clear string s */
     sprintf(s, \"\");

     /* just kill the call to __main */
     if (!strcmp(XEXP(operands[0],0),\"__main\")) return \"\";

     /* jds31 - save frame ptr and stack ptr */
     sprintf(s1, \"ldloc 28\\n\\tstsfld int32 * '<Module>'::fp\\n\\t\");
     strcat(s,s1);
     sprintf(s1, \"ldloc 29\\n\\tstsfld int32 * '<Module>'::sp\\n\\t\");
     strcat(s,s1);

     num_reg_args = (clr_workout_arg_words(CALL_INSN_FUNCTION_USAGE(insn)));

     sprintf(s1, \"// num_reg_args = %d\\n\", num_reg_args); /* jds31 -debug */
     strcat(s,s1);                                           /* jds31 -debug */
     for (i=0; i<num_reg_args; i++) {
       sprintf(s1,\"\\tldloc %i\\n\", (i+19));  /* FIRST_ARG_REG == 19 */
       strcat(s,s1);
     }
     strcat(s,\"\\tcall void '<Module>'::%0(\");
     for (i=0; i<num_reg_args; i++) {
       if (i>0) strcat(s,\",\");
       strcat(s,\"int32\");
     }
     strcat(s,\")\\n\");

     return s;
  ")

(define_insn "clr_call_value"
  [(set (match_operand 0 "nonimmediate_operand" "=g")
	(call (mem:QI (match_operand:SI 1 "general_operand" "g"))
		      (match_operand:SI 2 "immediate_operand" "i")))]

  ""
;;  "// num_reg_args=%2\\n\\tcall_value %1\\n\\tstloc %0\\n")
  "* 
     static char s[1024];	
     static char s1[40];	
     int i;
     int num_reg_args = -1;

     /* jds31 - clear string s */
     sprintf(s, \"\");
   
     /* jds31 - first save stack ptr and frame ptr */
     sprintf(s1, \"ldloc 28\\n\\tstsfld int32 * '<Module>'::fp\\n\");
     strcat(s,s1);
     sprintf(s1, \"\\tldloc 29\\n\\tstsfld int32 * '<Module>'::sp\\n\");
     strcat(s,s1);

     num_reg_args = (clr_workout_arg_words(CALL_INSN_FUNCTION_USAGE(insn)));

     sprintf(s1, \"\\t// num_reg_args = %d\\n\", num_reg_args); /* jds31 -debug */
     strcat(s,s1);                                           /* jds31 -debug */
     for (i=0; i<num_reg_args; i++) {
       sprintf(s1,\"\\tldloc %i\\n\", (i+19));  /* FIRST_ARG_REG == 19 */
       strcat(s,s1);
     }
     strcat(s,\"\\tcall int32 '<Module>'::%1(\");
     for (i=0; i<num_reg_args; i++) {
       if (i>0) strcat(s,\",\");
       strcat(s,\"int32\");
     }
     strcat(s,\")\\n\");
     strcat(s,\"\\tstloc %0\\n\\n\");

     return s;
  ")

;; jds31 - note that in the following two expansions,
;;         we don't actually use the information calculated
;;         by pj_workout_arg_words(). We use
;;         clr_workout_arg_words() instead, in the 
;;         clr_call and clr_call_value patterns above. 
;;         pj_workout_arg_words() gave us the WRONG
;;         answers. clr_workout_arg_words() gives
;;         us the correct answers - based on code
;;         from egcs-jvm.

(define_expand "call"
  [(call (match_operand:SI 0 "general_operand" "g")
         (match_operand:SI 1 "immediate_operand" "i"))
   (use (match_operand:SI 2 "register_operand" "r"))
   (use (match_operand:SI 3 "" ""))]
  ""
  "
   {
     emit_call_insn (gen_clr_call (XEXP (operands[0], 0),
		                   pj_workout_arg_words (operands[1],
	                                         operands[2])));
     DONE;
   }")

(define_expand "call_value"
  [(set (match_operand:SI 0 "register_operand" "=r")
	(call (match_operand:SI 1 "general_operand" "g")
         (match_operand:SI 2 "immediate_operand" "i")))
   (use (match_operand:SI 3 "register_operand" "r"))
   (use (match_operand:SI 4 "" ""))]
  ""
  "
   {
     emit_call_insn (gen_clr_call_value (operands[0], 
	            	                 XEXP (operands[1], 0),
	                              	 pj_workout_arg_words (operands[2],
	                                               operands[3])));
     DONE;
   }")


;; Return

(define_insn "return"
  [(return)]
  ""
  "ldloc 0\\n\\tret")


;; End of clr.md




