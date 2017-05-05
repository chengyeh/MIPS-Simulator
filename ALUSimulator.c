//*****************************************************************************
//--ALUSimulator.c
//
//		Author: 		Gary J. Minden
//		Organization:	KU/EECS/EECS 645
//		Date:			2017-04-22 (B70422)
//		Version:		1.0
//		Description:	This is the test standin for a simple ALU simulator
//		Notes:
//
//*****************************************************************************
//

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdarg.h>

#include <stdio.h>

#include "RegisterFile_01.h"
#include "ALUSimulator.h"
#include "MIPSInstructions.h"

extern void ALUSimulator(RegisterFile theRegisterFile, uint32_t OpCode,
		uint32_t Rs, uint32_t Rt, uint32_t Rd, uint32_t ShiftAmt,
		uint32_t FunctionCode, uint32_t ImmediateValue, uint32_t* Status) {
	printf(">>ALU: Opcode: %02X; Rs: %02X; Rt: %02X; Rd: %02X;\n", OpCode, Rs,
			Rt, Rd);

	printf(
			">>>>ALU: ShiftAmt: %02X; FunctionCode: %02X; ImmediateValue: %04X;\n",
			ShiftAmt, FunctionCode, ImmediateValue);

	// Determine type instruction
	// If OpCode is 0, its R type instruction else I type instruction
	if (OpCode == 0) {
		//R-Type instruction
		switch (FunctionCode) {
		case 0:
			if ((Rs == 0) && (Rt == 0) && (Rd == 0) && (ShiftAmt == 0)
					&& (ImmediateValue == 0)) {
				// Bit pattern for NOOP
				NOOP();
			} else {
				SLL(theRegisterFile, Rs, Rt, Rd, ShiftAmt);
			}
			break;
		case 2:
			SRL(theRegisterFile, Rs, Rt, Rd, ShiftAmt);
			break;
		case 3:
			SRA(theRegisterFile, Rs, Rt, Rd, ShiftAmt);
			break;
		case 4:
			SLLV(theRegisterFile, Rs, Rt, Rd);
			break;
		case 6:
			SRLV(theRegisterFile, Rs, Rt, Rd);
			break;
		case 32:
			ADD(theRegisterFile, Rs, Rt, Rd);
			break;
		case 33:
			ADDU(theRegisterFile, Rs, Rt, Rd);
			break;
		case 34:
			SUB(theRegisterFile, Rs, Rt, Rd);
			break;
		case 35:
			SUBU(theRegisterFile, Rs, Rt, Rd);
			break;
		case 36:
			AND(theRegisterFile, Rs, Rt, Rd);
			break;
		case 37:
			OR(theRegisterFile, Rs, Rt, Rd);
			break;
		case 38:
			XOR(theRegisterFile, Rs, Rt, Rd);
			break;
		case 42:
			SLT(theRegisterFile, Rs, Rt, Rd);
			break;
		case 43:
			SLTU(theRegisterFile, Rs, Rt, Rd);
			break;
		default:
			//Wrong instruction.
			printf(
					ANSI_COLOR_RED_BACK "Error: Wrong instruction." ANSI_COLOR_RESET "\n");
			//return (1);
		}
	} else {
		//I-Type instruction
		switch (OpCode) {
		case 8:
			ADDI(theRegisterFile, Rs, Rt, ImmediateValue);
			break;
		case 9:
			ADDIU(theRegisterFile, Rs, Rt, ImmediateValue);
			break;
		case 10:
			SLTI(theRegisterFile, Rs, Rt, ImmediateValue);
			break;
		case 11:
			SLTIU(theRegisterFile, Rs, Rt, ImmediateValue);
			break;
		default:
			//Wrong instruction.
			printf(
					ANSI_COLOR_RED_BACK "Error: Wrong instruction." ANSI_COLOR_RESET "\n");
			//return (1);
		}
	}

} //End of ALUSimulator function
