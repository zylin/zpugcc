// support.il
// Jeremy Singer
// 18 Jan 03

// Runtime support code for the
// gcc .net generated il asm.


// stack and frame pointer saved vars

.data D_0 = int32(0)
.data D_1 = int32(0)

.field public static int32 * sp at D_0
.field public static int32 * fp at D_1


// entry routine, sets up runtime stack,
// sp and fp, then calls the main()
// method, which should have been 
// defined by the gcc generated code.

.method public static void clr_start() cil managed
{
	.entrypoint
	.maxstack 10
	.locals(valuetype 'array int[1000]')

	// set up sp and fp
	ldloca 0
	ldc.i4 399996
	add
	dup
	stsfld int32 * '<Module>'::sp
	stsfld int32 * '<Module>'::fp

	call int32 '<Module>'::main()
	// print out the return value
        ldstr "main returned: "
        call void [mscorlib]System.Console::Write(string)
        call void [mscorlib]System.Console::WriteLine(int32)
	ret
}


.class public explicit sealed serializable ansi 'array int[1000]' extends [mscorlib]System.ValueType
{
        .pack 4
        .size 400000
        .field [0] public specialname int32 elem__
}

