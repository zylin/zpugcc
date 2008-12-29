/* 
 * Copyright (C) 1999, 2000, 2001, 2002 Stephane Carrez (stcarrez@nerim.fr)	
 *
 * The authors hereby grant permission to use, copy, modify, distribute,
 * and license this software and its documentation for any purpose, provided
 * that existing copyright notices are retained in all copies and that this
 * notice is included verbatim in any distributions. No written agreement,
 * license, or royalty fee is required for any of the authorized uses.
 * Modifications to this software may be copyrighted by their authors
 * and need not follow the licensing terms described here, provided that
 * the new terms are clearly indicated on the first page of each file where
 * they apply.
 */


	.text
	
	.global	setjmp
	.globl	longjmp


setjmp:
	; store r0. We won't be needing it, but what the heck.
	im 0
	load
	loadsp 8 ; fetch argument
	store	

	; store r1
	im 4
	load
	loadsp 8 ; fetch argument
	im 4
	add
	store	

	; store r2
	im 8
	load
	loadsp 8 ; fetch argument
	im 8
	add
	store	

	; store r3
	im 12
	load
	loadsp 8 ; fetch argument
	im 12
	add
	store	

	; store r4
	im 16
	load
	loadsp 8 ; fetch argument
	im 16
	add
	store	

	; store r5
	im 20
	load
	loadsp 8 ; fetch argument
	im 20
	add
	store	

	; store r6
	im 24
	load
	loadsp 8 ; fetch argument
	im 24
	add
	store	

	; store r7
	im 28
	load
	loadsp 8 ; fetch argument
	im 28
	add
	store	

	; store sp
	pushsp
	loadsp 8 ; fetch argument
	im 8*4
	add
	store	

	; store return value from this fn into setjmp buffer
	loadsp 0
	loadsp 8
	im 8+8*4
	add
	store

	; store pc
	impcrel .Lto
	pushpc
	add
	
	loadsp 8 ; fetch argument
	im 4+8*4
	add
	store

	; set return value to 0
	im 0
	nop
	im 0
	store

.Lto:
	poppc


	; arguments are buffer + return value
longjmp:
	; load r1
	loadsp 4
	im 4
	add
	load
	im 4
	store

	; load r2
	loadsp 4
	im 8
	add
	load
	im 8
	store
	
	; load r3
	loadsp 4
	im 12
	add
	load
	im 12
	store

	; load r4
	loadsp 4
	im 16
	add
	load
	im 16
	store

	; load r5
	loadsp 4
	im 20
	add
	load
	im 20
	store

	; load r6
	loadsp 4
	im 24
	add
	load
	im 24
	store

	; load r7
	loadsp 4
	im 28
	add
	load
	im 28
	store

	; Danger! here be dragons!
	;
	; Once we are on the stack from the setjmp, 
	; remember that calling convention has destroyed
	; the arguments to the setjmp fn.


	; copy value of r0(which is decided by the second argument
	; to longjmp) to setjmp buffer
	loadsp 8
	loadsp 8
	store
	
	; store pointer to setjmp buffer in r0
	loadsp 4
	im 0
	store

	; restore stack
	loadsp 4
	im 8*4
	add
	load
	popsp
	
	; Danger! here be dragons!
	; have now switched stacks!
	
	; restore return address since it has been destroyed
	im 0
	load
	im 8+8*4
	add
	load
	storesp 4
	
	; push pc onto stack
	im 0
	load
	im 4+8*4
	add
	load

	; fill in correct value in r0, which we
	; take from the setjmp buffer....
	im 0
	load
	load
	im 0
	store
	
	poppc
