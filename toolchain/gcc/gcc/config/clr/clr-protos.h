/*
 * clr-protos.h
 * Jeremy Singer
 * 10 Jan 03
 */

/* declares function prototypes
 * which are to be used in the
 * machine definition files
 * for the GCC .NET backend
 */

extern void function_prologue PARAMS ((FILE *, int));
extern void function_epilogue PARAMS ((FILE *, int));

#if_def RTX_CODE

extern void notice_update_cc PARAMS ((rtx, rtx));
extern void print_operand PARAMS ((FILE *, rtx, int));
extern void print_operand_address PARAMS ((FILE *, rtx));

#endif /* RTX_CODE */
