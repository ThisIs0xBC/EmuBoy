#include "tests.h"

#include <iostream>

#define CHECK_FLAGS(flags, expectedFlags) (flags == expectedFlags)

CPU* Tests::testCPU = nullptr;

// I named the variable processor because cpu seems to be a keyword according to VS2019
void printCPUFlags(CPU* processor) {
	// Get the current CPU flags listed as an 8 bit uint where the LSB nibble has contains 4 bools, each one being a flag
	uint8_t currentFlags = processor->f.get8BitValue();

	if (currentFlags & FLAG_ZERO) std::cout << "FLAG_ZERO Set" << std::endl;
	if (currentFlags & FLAG_SUBTRACT) std::cout << "FLAG_SUBTRACT Set" << std::endl;
	if (currentFlags & FLAG_HALF_CARRY) std::cout << "FLAG_HALF_CARRY Set" << std::endl;
	if (currentFlags & FLAG_CARRY) std::cout << "FLAG_CARRY Set" << std::endl;
}

bool Tests::testInstructions()
{
	// Test every single instruction with multiple different
	// CPU states to make sure they all return the expected values
	if (!testADD()) return false;
	if (!testADDHL()) return false;
	if (!testADC()) return false;
	if (!testSUB()) return false;
	if (!testSBC()) return false;
	if (!testAND()) return false;
	if (!testOR()) return false;
	if (!testXOR()) return false;
	if (!testCP()) return false;


	return true;
}

bool Tests::testADD()
{

	testCPU = new CPU();

	testCPU->b.setValue(15ui8);
	testCPU->insADD(testCPU->b);
	if (testCPU->a.getValue() != 15ui8) return false;
	if (!CHECK_FLAGS(testCPU->f.get8BitValue(), 0ui8)) return false;

	testCPU->c.setValue(1ui8);
	testCPU->insADD(testCPU->c);
	if (testCPU->a.getValue() != 16ui8) return false;
	if (!CHECK_FLAGS(testCPU->f.get8BitValue(), FLAG_HALF_CARRY)) return false; //Half Carry Should Be 1 Now

	testCPU->d.setValue(240ui8);
	testCPU->insADD(testCPU->d);
	if (testCPU->a.getValue() != 0ui8) return false;
	printCPUFlags(testCPU);
	if (!CHECK_FLAGS(testCPU->f.get8BitValue(), (FLAG_ZERO | FLAG_CARRY))) return false; //Zero + Carry Flags Should Be 1 Now

	return true;
}

bool Tests::testADDHL()
{
	testCPU = new CPU();

	testCPU->setCombinedRegisterValue(testCPU->b, testCPU->c, 4095ui16);
	testCPU->insADDHL(testCPU->b + testCPU->c);
	if ((testCPU->h + testCPU->l).getValue() != 4095ui16) return false;
	if (!CHECK_FLAGS(testCPU->f.get8BitValue(), 0ui16)) return false;

	testCPU->setCombinedRegisterValue(testCPU->d, testCPU->e, 1ui16);
	testCPU->insADDHL(testCPU->d + testCPU->e);
	if ((testCPU->h + testCPU->l).getValue() != 4096ui16) return false;
	if (!CHECK_FLAGS(testCPU->f.get8BitValue(), FLAG_HALF_CARRY)) return false; //Half Carry Should Be 1 Now

	testCPU->setCombinedRegisterValue(testCPU->d, testCPU->e, 61440ui16);
	testCPU->insADDHL(testCPU->d + testCPU->e);
	if ((testCPU->h + testCPU->l).getValue() != 0ui16) return false;
	if (!CHECK_FLAGS(testCPU->f.get8BitValue(), (FLAG_ZERO | FLAG_CARRY))) return false; //Zero + Carry Flags Should Be 1 Now

	return true;
}

bool Tests::testADC()
{

	testCPU = new CPU();

	testCPU->b.setValue(14ui8);
	testCPU->insADC(testCPU->b);
	if (testCPU->a.getValue() != 14ui8) return false;
	if (!CHECK_FLAGS(testCPU->f.get8BitValue(), 0ui8)) return false;

	testCPU->c.setValue(1ui8);
	testCPU->f.setFlagCarry(true);
	testCPU->insADC(testCPU->c);
	if (testCPU->a.getValue() != 16ui8) return false;
	if (!CHECK_FLAGS(testCPU->f.get8BitValue(), FLAG_HALF_CARRY)) return false; //Half Carry Should Be 1 Now

	testCPU->d.setValue(239ui8);
	testCPU->f.setFlagCarry(true);
	testCPU->insADC(testCPU->d);
	if (testCPU->a.getValue() != 0ui8) return false;
	if (!CHECK_FLAGS(testCPU->f.get8BitValue(), (FLAG_ZERO | FLAG_CARRY))) return false; //Zero + Carry Flags Should Be 1 Now

	return true;
}

bool Tests::testSUB()
{

	testCPU = new CPU();

	testCPU->a.setValue(255ui8);
	testCPU->b.setValue(15ui8);
	testCPU->insSUB(testCPU->b);
	if (testCPU->a.getValue() != 240ui8) return false;
	if (!CHECK_FLAGS(testCPU->f.get8BitValue(), FLAG_SUBTRACT)) return false;

	testCPU->c.setValue(1ui8);
	testCPU->insSUB(testCPU->c);
	if (testCPU->a.getValue() != 239ui8) return false;
	if (!CHECK_FLAGS(testCPU->f.get8BitValue(), (FLAG_SUBTRACT | FLAG_HALF_CARRY))) return false; //Half Carry Should Be 1 Now

	testCPU->d.setValue(494ui8); //Gets us to 0, wrapped back to 255, then back to 0, so the zero and carry flags are true
	testCPU->insSUB(testCPU->d);
	if (testCPU->a.getValue() != 0ui8) return false;
	if (!CHECK_FLAGS(testCPU->f.get8BitValue(), (FLAG_ZERO | FLAG_SUBTRACT | FLAG_CARRY))) return false; //Zero + Carry Flags Should Be 1 Now

	return true;
}

bool Tests::testSBC()
{
	
	testCPU = new CPU();

	testCPU->a.setValue(255ui8);
	testCPU->b.setValue(14ui8);
	testCPU->insSBC(testCPU->b);
	if (testCPU->a.getValue() != 241ui8) return false;
	if (!CHECK_FLAGS(testCPU->f.get8BitValue(), FLAG_SUBTRACT)) return false;

	testCPU->c.setValue(1ui8);
	testCPU->f.setFlagCarry(true);
	testCPU->insSBC(testCPU->c);
	if (testCPU->a.getValue() != 239ui8) return false;
	if (!CHECK_FLAGS(testCPU->f.get8BitValue(), (FLAG_SUBTRACT | FLAG_HALF_CARRY))) return false; //Half Carry Should Be 1 Now

	testCPU->d.setValue(238ui8); //Gets us to 0, wrapped back to 255, then back to 0, so the zero and carry flags are true
	testCPU->f.setFlagCarry(true);
	testCPU->insSBC(testCPU->d);
	if (testCPU->a.getValue() != 0ui8) return false;
	if (!CHECK_FLAGS(testCPU->f.get8BitValue(), (FLAG_ZERO | FLAG_SUBTRACT))) return false; //Zero + Carry Flags Should Be 1 Now

	return true;
}

bool Tests::testAND()
{

	testCPU = new CPU();

	testCPU->a.setValue(45i8);
	testCPU->b.setValue(4ui8);
	testCPU->insAND(testCPU->b);
	if (testCPU->a.getValue() != 4ui8) return false;
	if (!CHECK_FLAGS(testCPU->f.get8BitValue(), 0ui8)) return false;

	testCPU->a.setValue(45i8);
	testCPU->c.setValue(0ui8);
	testCPU->insAND(testCPU->c);
	if (testCPU->a.getValue() != 0ui8) return false;
	if (!CHECK_FLAGS(testCPU->f.get8BitValue(), FLAG_ZERO)) return false;

	testCPU->a.setValue(245ui8);
	testCPU->d.setValue(0xF);
	testCPU->insAND(testCPU->d);
	if (testCPU->a.getValue() != 5ui8) return false;
	if (!CHECK_FLAGS(testCPU->f.get8BitValue(), 0ui8)) return false; //Half Carry Should Be 1 Now

	return true;
}

bool Tests::testOR()
{

	testCPU = new CPU();

	testCPU->a.setValue(0ui8);
	testCPU->b.setValue(17ui8);
	testCPU->insOR(testCPU->b);
	if (testCPU->a.getValue() != 17ui8) return false;
	if (!CHECK_FLAGS(testCPU->f.get8BitValue(), 0ui8)) return false;

	testCPU->a.setValue(0ui8);
	testCPU->c.setValue(0ui8);
	testCPU->insOR(testCPU->c);
	if (testCPU->a.getValue() != 0ui8) return false;
	if (!CHECK_FLAGS(testCPU->f.get8BitValue(), FLAG_ZERO)) return false; //Half Carry Should Be 1 Now

	testCPU->a.setValue(4ui8);
	testCPU->d.setValue(17ui8);
	testCPU->insOR(testCPU->d);
	if (testCPU->a.getValue() != 21ui8) return false;
	if (!CHECK_FLAGS(testCPU->f.get8BitValue(), 0ui8)) return false; //Half Carry Should Be 1 Now

	return true;

}

bool Tests::testXOR()
{
	
	testCPU = new CPU();

	testCPU->a.setValue(0i8);
	testCPU->b.setValue(0ui8);
	testCPU->insXOR(testCPU->b);
	if (testCPU->a.getValue() != 0ui8) return false;
	if (!CHECK_FLAGS(testCPU->f.get8BitValue(), FLAG_ZERO)) return false;

	testCPU->a.setValue(45ui8);
	testCPU->c.setValue(45ui8);
	testCPU->insXOR(testCPU->c);
	if (testCPU->a.getValue() != 0ui8) return false;
	if (!CHECK_FLAGS(testCPU->f.get8BitValue(), FLAG_ZERO)) return false; //Half Carry Should Be 1 Now

	testCPU->a.setValue(45i8);
	testCPU->d.setValue(21ui8);
	testCPU->insXOR(testCPU->d);
	if (testCPU->a.getValue() != 56ui8) return false;
	if (!CHECK_FLAGS(testCPU->f.get8BitValue(), 0ui8)) return false;

	return true;
}

bool Tests::testCP()
{
	
	testCPU = new CPU();

	testCPU->a.setValue(255ui8);
	testCPU->b.setValue(15ui8);
	testCPU->insCP(testCPU->b);
	if (testCPU->a.getValue() != 240ui8) return false;
	if (!CHECK_FLAGS(testCPU->f.get8BitValue(), FLAG_SUBTRACT)) return false;

	testCPU->c.setValue(1ui8);
	testCPU->insCP(testCPU->c);
	if (testCPU->a.getValue() != 239ui8) return false;
	if (!CHECK_FLAGS(testCPU->f.get8BitValue(), (FLAG_SUBTRACT | FLAG_HALF_CARRY))) return false; //Half Carry Should Be 1 Now

	testCPU->d.setValue(494ui8); //Gets us to 0, wrapped back to 255, then back to 0, so the zero and carry flags are true
	testCPU->insCP(testCPU->d);
	if (testCPU->a.getValue() != 0ui8) return false;
	if (!CHECK_FLAGS(testCPU->f.get8BitValue(), (FLAG_ZERO | FLAG_SUBTRACT | FLAG_CARRY))) return false; //Zero + Carry Flags Should Be 1 Now

	return true;
}

bool Tests::testINC()
{
	return false;
}

bool Tests::testDEC()
{
	return false;
}

bool Tests::testCCF()
{
	return false;
}

bool Tests::testSCF()
{
	return false;
}

bool Tests::testRRA()
{
	return false;
}

bool Tests::testRLA()
{
	return false;
}

bool Tests::testRRCA()
{
	return false;
}

bool Tests::testRRLA()
{
	return false;
}

bool Tests::testCPL()
{
	return false;
}

bool Tests::testBIT()
{
	return false;
}

bool Tests::testRESET()
{
	return false;
}

bool Tests::testSET()
{
	return false;
}

bool Tests::testSRL()
{
	return false;
}

bool Tests::testRR()
{
	return false;
}

bool Tests::testRL()
{
	return false;
}

bool Tests::testRRC()
{
	return false;
}

bool Tests::testRLC()
{
	return false;
}

bool Tests::testSRA()
{
	return false;
}

bool Tests::testSLA()
{
	return false;
}

bool Tests::testSWAP()
{
	return false;
}
