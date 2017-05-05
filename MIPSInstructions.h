//*****************************************************************************
//
//	Program:		MIPSInstructions.h
//	Author:			Dilesh Fernando <fernando.dilesh@gmail.com>
//					Cheng-Yeh Lee <chengyeh90@gmail.com>
//					Vuong Nguyen <nptvuong2912@gmail.com>
//					Diego Soliz Castro <zilosgodi@gmail.com>
//	Date:			2017-04-21
//	Description:	A program to simulate MIPS Instructions.
//
//*****************************************************************************

#include <stdint.h>
#include "RegisterFile_01.h"

#define ANSI_COLOR_RED_BACK "\x1b[41m"
#define ANSI_COLOR_RED      "\x1b[31m"
#define ANSI_COLOR_GREEN    "\x1b[32m"
#define ANSI_COLOR_YELLOW   "\x1b[33m"
#define ANSI_COLOR_BLUE     "\x1b[34m"
#define ANSI_COLOR_MAGENTA  "\x1b[35m"
#define ANSI_COLOR_CYAN     "\x1b[36m"
#define ANSI_COLOR_RESET    "\x1b[0m"

#ifndef __MIPSInstructions_H_
#define __MIPSInstructions_H_

extern void NOOP();

extern void SLL(RegisterFile theRegisterFile, uint32_t Rs, uint32_t Rt,
		uint32_t Rd, uint32_t ShiftAmt);

extern void SRL(RegisterFile theRegisterFile, uint32_t Rs, uint32_t Rt,
		uint32_t Rd, uint32_t ShiftAmt);

extern void SRA(RegisterFile theRegisterFile, uint32_t Rs, uint32_t Rt,
		uint32_t Rd, uint32_t ShiftAmt);

extern void SLLV(RegisterFile theRegisterFile, uint32_t Rs, uint32_t Rt,
		uint32_t Rd);

extern void SRLV(RegisterFile theRegisterFile, uint32_t Rs, uint32_t Rt,
		uint32_t Rd);

extern void ADD(RegisterFile, uint32_t, uint32_t, uint32_t);

extern void ADDU(RegisterFile theRegisterFile, uint32_t Rs, uint32_t Rt,
		uint32_t Rd);

extern void SUB(RegisterFile theRegisterFile, uint32_t Rs, uint32_t Rt,
		uint32_t Rd);

extern void SUBU(RegisterFile theRegisterFile, uint32_t Rs, uint32_t Rt,
		uint32_t Rd);

extern void AND(RegisterFile theRegisterFile, uint32_t Rs, uint32_t Rt,
		uint32_t Rd);

extern void OR(RegisterFile theRegisterFile, uint32_t Rs, uint32_t Rt,
		uint32_t Rd);

extern void XOR(RegisterFile theRegisterFile, uint32_t Rs, uint32_t Rt,
		uint32_t Rd);

extern void SLT(RegisterFile theRegisterFile, uint32_t Rs, uint32_t Rt,
		uint32_t Rd);

extern void SLTU(RegisterFile theRegisterFile, uint32_t Rs, uint32_t Rt,
		uint32_t Rd);

extern void ADDI(RegisterFile theRegisterFile, uint32_t Rs, uint32_t Rt,
		uint32_t ImmediateValue);

extern void ADDIU(RegisterFile theRegisterFile, uint32_t Rs, uint32_t Rt,
		uint32_t ImmediateValue);

extern void SLTI(RegisterFile theRegisterFile, uint32_t Rs, uint32_t Rt,
		uint32_t ImmediateValue);

extern void SLTIU(RegisterFile theRegisterFile, uint32_t Rs, uint32_t Rt,
		uint32_t ImmediateValue);

#endif  // __MIPSInstructions_H_
