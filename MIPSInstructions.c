//*****************************************************************************
//
//	Program:		MIPSInstructions.c
//	Author:			Dilesh Fernando <fernando.dilesh@gmail.com>
//					Cheng-Yeh Lee <chengyeh90@gmail.com>
//					Vuong Nguyen <nptvuong2912@gmail.com>
//					Diego Soliz Castro <zilosgodi@gmail.com>
//	Date:			2017-04-21
//	Description:	Implementation of MIPS Instructions.
//
//*****************************************************************************

#include <stdio.h>
#include <stdlib.h>

#include "MIPSInstructions.h"

/*
 * NOTE: delete all print statements from each function afters testing.
 */

/*
 NOOP -- no operation
 Description:	Performs no operation.
 Operation: 	advance_pc (4);
 Syntax: 	noop
 Encoding: 	0000 0000 0000 0000 0000 0000 0000 0000
 */
extern void NOOP() {
	// Do nothing
}

/*
 SLL -- Shift left logical
 Description:	Shifts a register value left by the shift amount listed in the instruction and places the result in a third register. Zeroes are shifted in.
 Operation: 	$d = $t << h; advance_pc (4);
 Syntax: 	sll $d, $t, h
 Encoding: 	0000 00ss ssst tttt dddd dhhh hh00 0000
 */
extern void SLL(RegisterFile theRegisterFile, uint32_t Rs, uint32_t Rt,
		uint32_t Rd, uint32_t ShiftAmt) {
	uint32_t s, t, d;
	RegisterFile_Read(theRegisterFile, Rs, &s, Rt, &t);
	RegisterFile_Write(theRegisterFile, true, Rd, t << ShiftAmt);

}

/*
 SRL -- Shift right logical
 Description:	Shifts a register value right by the shift amount (shamt) and places the value in the destination register. Zeroes are shifted in.
 Operation: 	$d = $t >> h; advance_pc (4);
 Syntax: 	srl $d, $t, h
 Encoding: 	0000 00-- ---t tttt dddd dhhh hh00 0010
 */
extern void SRL(RegisterFile theRegisterFile, uint32_t Rs, uint32_t Rt,
		uint32_t Rd, uint32_t ShiftAmt) {
	uint32_t s, t, d;
	RegisterFile_Read(theRegisterFile, Rs, &s, Rt, &t);
	RegisterFile_Write(theRegisterFile, true, Rd, t >> ShiftAmt);
}

/*
 SRA -- Shift right arithmetic
 Description:	Shifts a register value right by the shift amount (shamt) and places the value in the destination register. The sign bit is shifted in.
 Operation: 	$d = $t >> h; advance_pc (4);
 Syntax: 	sra $d, $t, h
 Encoding: 	0000 00-- ---t tttt dddd dhhh hh00 0011
 */
extern void SRA(RegisterFile theRegisterFile, uint32_t Rs, uint32_t Rt,
		uint32_t Rd, uint32_t ShiftAmt) {
	uint32_t s, t, d;
	RegisterFile_Read(theRegisterFile, Rs, &s, Rt, &t);

	//Check the signed bit
	uint32_t signBit = t >> 4;

	//If sign bit is 1, Rt is signed else not signed
	if (signBit == 1) {
		// Rt is signed number

		//Generate a mask
		//Shift right by n bits.
		uint32_t mask = 31 << (5 - ShiftAmt); // 31(decimal) = 11111(binary)

		//AND the mask.
		RegisterFile_Write(theRegisterFile, true, Rd, (t >> ShiftAmt) & mask);

	} else {
		// Rt is unsigned number
		RegisterFile_Write(theRegisterFile, true, Rd, t >> ShiftAmt);
	}
}

/*
 SLLV -- Shift left logical variable
 Description:	Shifts a register value left by the value in a second register and places the result in a third register. Zeroes are shifted in.
 Operation: 	$d = $t << $s; advance_pc (4);
 Syntax: 	sllv $d, $t, $s
 Encoding: 	0000 00ss ssst tttt dddd d--- --00 0100
 */
extern void SLLV(RegisterFile theRegisterFile, uint32_t Rs, uint32_t Rt,
		uint32_t Rd) {
	uint32_t s, t, d;
	RegisterFile_Read(theRegisterFile, Rs, &s, Rt, &t);
	RegisterFile_Write(theRegisterFile, true, Rd, t << s);
}

/*
 SRLV -- Shift right logical variable
 Description:	Shifts a register value right by the amount specified in $s and places the value in the destination register. Zeroes are shifted in.
 Operation: 	$d = $t >> $s; advance_pc (4);
 Syntax: 	srlv $d, $t, $s
 Encoding: 	0000 00ss ssst tttt dddd d000 0000 0110
 */
extern void SRLV(RegisterFile theRegisterFile, uint32_t Rs, uint32_t Rt,
		uint32_t Rd) {
	uint32_t s, t, d;
	RegisterFile_Read(theRegisterFile, Rs, &s, Rt, &t);
	RegisterFile_Write(theRegisterFile, true, Rd, t >> s);
}

/*
 ADD -- Add (with overflow)
 Description:	Adds two registers and stores the result in a register
 Operation: 	$d = $s + $t; advance_pc (4);
 Syntax: 	add $d, $s, $t
 Encoding: 	0000 00ss ssst tttt dddd d000 0010 0000
 */
extern void ADD(RegisterFile theRegisterFile, uint32_t Rs, uint32_t Rt,
		uint32_t Rd) {
	uint32_t s, t;
	RegisterFile_Read(theRegisterFile, Rs, &s, Rt, &t);
	int32_t s_int = s;
	int32_t t_int = t;
	int32_t d = s + t;

	RegisterFile_Write(theRegisterFile, true, Rd, d);
}

/*
 ADDU -- Add unsigned (no overflow)
 Description:	Adds two registers and stores the result in a register
 Operation: 	$d = $s + $t; advance_pc (4);
 Syntax: 	addu $d, $s, $t
 Encoding: 	0000 00ss ssst tttt dddd d000 0010 0001
 */
extern void ADDU(RegisterFile theRegisterFile, uint32_t Rs, uint32_t Rt,
		uint32_t Rd) {
	uint32_t s, t;
	RegisterFile_Read(theRegisterFile, Rs, &s, Rt, &t);
	RegisterFile_Write(theRegisterFile, true, Rd, t + s);
}

/*
 SUB -- Subtract
 Description:	Subtracts two registers and stores the result in a register
 Operation: 	$d = $s - $t; advance_pc (4);
 Syntax: 	sub $d, $s, $t
 Encoding: 	0000 00ss ssst tttt dddd d000 0010 0010
 */
extern void SUB(RegisterFile theRegisterFile, uint32_t Rs, uint32_t Rt,
		uint32_t Rd) {
	uint32_t s, t;
	RegisterFile_Read(theRegisterFile, Rs, &s, Rt, &t);
	int32_t s_int = s;
	int32_t t_int = t;
	int32_t d = s - t;

	RegisterFile_Write(theRegisterFile, true, Rd, d);
}

/*
 SUBU -- Subtract unsigned
 Description:	Subtracts two registers and stores the result in a register
 Operation: 	$d = $s - $t; advance_pc (4);
 Syntax: 	subu $d, $s, $t
 Encoding: 	0000 00ss ssst tttt dddd d000 0010 0011
 */
extern void SUBU(RegisterFile theRegisterFile, uint32_t Rs, uint32_t Rt,
		uint32_t Rd) {
	uint32_t s, t;
	RegisterFile_Read(theRegisterFile, Rs, &s, Rt, &t);
	RegisterFile_Write(theRegisterFile, true, Rd, s - t);
}

/*
 AND -- Bitwise and
 Description:	Bitwise ands two registers and stores the result in a register
 Operation: 	$d = $s & $t; advance_pc (4);
 Syntax: 	and $d, $s, $t
 Encoding: 	0000 00ss ssst tttt dddd d000 0010 0100
 */
extern void AND(RegisterFile theRegisterFile, uint32_t Rs, uint32_t Rt,
		uint32_t Rd) {
	uint32_t s, t, d;
	RegisterFile_Read(theRegisterFile, Rs, &s, Rt, &t);
	RegisterFile_Write(theRegisterFile, true, Rd, s & t);

}

/*
 OR -- Bitwise or
 Description:	Bitwise logical ors two registers and stores the result in a register
 Operation: 	$d = $s | $t; advance_pc (4);
 Syntax: 	or $d, $s, $t
 Encoding: 	0000 00ss ssst tttt dddd d000 0010 0101
 */
extern void OR(RegisterFile theRegisterFile, uint32_t Rs, uint32_t Rt,
		uint32_t Rd) {
	uint32_t s, t, d;
	RegisterFile_Read(theRegisterFile, Rs, &s, Rt, &t);
	RegisterFile_Write(theRegisterFile, true, Rd, s | t);
}

/*
 XOR -- Bitwise exclusive or
 Description:	Exclusive ors two registers and stores the result in a register
 Operation: 	$d = $s ^ $t; advance_pc (4);
 Syntax: 	xor $d, $s, $t
 Encoding: 	0000 00ss ssst tttt dddd d--- --10 0110
 */
extern void XOR(RegisterFile theRegisterFile, uint32_t Rs, uint32_t Rt,
		uint32_t Rd) {
	uint32_t s, t, d;
	RegisterFile_Read(theRegisterFile, Rs, &s, Rt, &t);
	RegisterFile_Write(theRegisterFile, true, Rd, s ^ t);
}

/*
 SLT -- Set on less than (signed)
 Description:	If $s is less than $t, $d is set to one. It gets zero otherwise.
 Operation: 	if $s < $t $d = 1; advance_pc (4); else $d = 0; advance_pc (4);
 Syntax: 	slt $d, $s, $t
 Encoding: 	0000 00ss ssst tttt dddd d000 0010 1010
 */
extern void SLT(RegisterFile theRegisterFile, uint32_t Rs, uint32_t Rt,
		uint32_t Rd) {
	uint32_t s, t;
	RegisterFile_Read(theRegisterFile, Rs, &s, Rt, &t);
	int32_t s_int = s;
	int32_t t_int = t;
	RegisterFile_Write(theRegisterFile, true, Rd, s_int < t_int);
}

/*
 SLTU -- Set on less than unsigned
 Description:	If $s is less than $t, $d is set to one. It gets zero otherwise.
 Operation: 	if $s < $t $d = 1; advance_pc (4); else $d = 0; advance_pc (4);
 Syntax: 	sltu $d, $s, $t
 Encoding: 	0000 00ss ssst tttt dddd d000 0010 1011
 */
extern void SLTU(RegisterFile theRegisterFile, uint32_t Rs, uint32_t Rt,
		uint32_t Rd) {
	uint32_t s, t;
	RegisterFile_Read(theRegisterFile, Rs, &s, Rt, &t);
	RegisterFile_Write(theRegisterFile, true, Rd, s < t);
}

/*
 ADDI -- Add immediate (with overflow)
 Description:	Adds a register and a sign-extended immediate value and stores the result in a register
 Operation: 	$t = $s + imm; advance_pc (4);
 Syntax: 	addi $t, $s, imm
 Encoding: 	0010 00ss ssst tttt iiii iiii iiii iiii
 */
extern void ADDI(RegisterFile theRegisterFile, uint32_t Rs, uint32_t Rt,
		uint32_t ImmediateValue) {
	// Initialized and assign local variables
	uint32_t s, t, imm;

	// Determine ImmediateValue is negative number
	const int isNegative = (ImmediateValue & (1 << 15)) != 0;

	// Assign imm value
	if (isNegative) {
		imm = ImmediateValue | ~((1 << 16) - 1);
	} else {
		imm = ImmediateValue;
	}

	RegisterFile_Read(theRegisterFile, Rs, &s, Rt, &t);
	RegisterFile_Write(theRegisterFile, true, Rt, s + imm);
}

/*
 ADDIU -- Add immediate unsigned (no overflow)
 Description:	Adds a register and a sign-extended immediate value and stores the result in a register
 Operation: 	$t = $s + imm; advance_pc (4);
 Syntax: 	addiu $t, $s, imm
 Encoding: 	0010 01ss ssst tttt iiii iiii iiii iiii
 */
extern void ADDIU(RegisterFile theRegisterFile, uint32_t Rs, uint32_t Rt,
		uint32_t ImmediateValue) {
	// Initialized and assign local variables
	uint32_t s, t, imm;

	// Determine ImmediateValue is negative number
	const int isNegative = (ImmediateValue & (1 << 15)) != 0;

	// Assign imm value
	if (isNegative) {
		imm = ImmediateValue | ~((1 << 16) - 1);
	} else {
		imm = ImmediateValue;
	}

	RegisterFile_Read(theRegisterFile, Rs, &s, Rt, &t);

	// TODO Implement ignore overflow

	RegisterFile_Write(theRegisterFile, true, Rt, s + imm);
}

/*
 SLTI -- Set on less than immediate (signed)
 Description:	If $s is less than immediate, $t is set to one. It gets zero otherwise.
 Operation: 	if $s < imm $t = 1; advance_pc (4); else $t = 0; advance_pc (4);
 Syntax: 	slti $t, $s, imm
 Encoding: 	0010 10ss ssst tttt iiii iiii iiii iiii
 */
extern void SLTI(RegisterFile theRegisterFile, uint32_t Rs, uint32_t Rt,
		uint32_t ImmediateValue) {
	// Initialized and assign local variables
	uint32_t s, t, imm;

	RegisterFile_Read(theRegisterFile, Rs, &s, Rt, &t);

	// Determine Rs register is negative number
	const int isNegativeRegister = (s & (1 << 31)) != 0;

	// Assign Rs value
	if (isNegativeRegister) {
		s = s | ~((1 << 32) - 1);
	} else {
		s = s;
	}

	// Determine ImmediateValue is negative number
	const int isNegative = (ImmediateValue & (1 << 15)) != 0;

	// Assign imm value
	if (isNegative) {
		imm = ImmediateValue | ~((1 << 16) - 1);
	} else {
		imm = ImmediateValue;
	}

	//RegisterFile_Read(theRegisterFile, Rs, &s, Rt, &t);

	// Implement the instruction
	if ((int32_t) s < (int32_t) imm) {
		RegisterFile_Write(theRegisterFile, true, Rt, 1);
	} else {
		RegisterFile_Write(theRegisterFile, true, Rt, 0);
	}
}

/*
 SLTIU -- Set on less than immediate unsigned
 Description:	If $s is less than the unsigned immediate, $t is set to one. It gets zero otherwise.
 Operation: 	if $s < imm $t = 1; advance_pc (4); else $t = 0; advance_pc (4);
 Syntax: 	sltiu $t, $s, imm
 Encoding: 	0010 11ss ssst tttt iiii iiii iiii iiii
 */
extern void SLTIU(RegisterFile theRegisterFile, uint32_t Rs, uint32_t Rt,
		uint32_t ImmediateValue) {
	// Initialized and assign local variables
	uint32_t s, t, imm;

	// Determine Rs register is negative number
	const int isNegativeRegister = (s & (1 << 31)) != 0;

	// Assign Rs value
	if (isNegativeRegister) {
		s = s | ~((1 << 32) - 1);
	} else {
		s = s;
	}

	// Determine ImmediateValue is negative number
	const int isNegative = (ImmediateValue & (1 << 15)) != 0;

	// Assign imm value
	if (isNegative) {
		imm = ImmediateValue | ~((1 << 16) - 1);
	} else {
		imm = ImmediateValue;
	}

	RegisterFile_Read(theRegisterFile, Rs, &s, Rt, &t);

	// Implement the instruction
	if ((int32_t) s < (int32_t) imm) {
		RegisterFile_Write(theRegisterFile, true, Rt, 1);
	} else {
		RegisterFile_Write(theRegisterFile, true, Rt, 0);
	}
}
