#pragma once

#include "CPURegister.h"

//Full CPU class here
class CPU {

private:

public:
	Register a;
	Register b;
	Register c;
	Register d;
	Register e;
	Register g;
	Register h;
	Register l;
	FlagsRegister f;

	//TODO: Add these
	//ProgramCounter pc;
	//MemoryBus memBus;

	CPU() {
		a = Register();
		b = Register();
		c = Register();
		d = Register();
		e = Register();
		g = Register();
		h = Register();
		l = Register();
		f = FlagsRegister();

	}

	~CPU() {
		
	}

	void setCombinedRegisterValue(Register &msbReg, Register &lsbReg, uint16_t value);

	uint8_t insADD(Register targetReg);
	uint16_t insADDHL(CombinedRegister targetReg);
	uint8_t insADC(Register targetReg);
	uint8_t insSUB(Register targetReg);
	uint8_t insSBC(Register targetReg);
	uint8_t insAND(Register targetReg);
	uint8_t insOR(Register targetReg);
	uint8_t insXOR(Register targetReg);
	uint8_t insCP(Register targetReg);
	uint8_t insINC(Register targetReg);
	uint8_t insDEC(Register targetReg);
	bool insCCF();
	bool insSCF();
	uint8_t insRRA();
	uint8_t insRLA();
	uint8_t insRRCA();
	uint8_t insRLCA();
	uint8_t insCPL();
	bool insBIT(uint8_t bit, Register targetReg); //Actually uint3 but uint8 works too
	void insRESET(uint8_t bit, Register targetReg); //Actually uint3 but uint8 works too
	void insSET(uint8_t bit, Register targetReg); //Actually uint3 but uint8 works too
	uint8_t insSRL(Register targetReg);
	uint8_t insRR(Register targetReg);
	uint8_t insRL(Register targetReg);
	uint8_t insRRC(Register targetReg);
	uint8_t insRLC(Register targetReg);
	uint8_t insSRA(Register targetReg);
	uint8_t insSLA(Register targetReg);
	uint8_t insSWAP(Register targetReg);
};