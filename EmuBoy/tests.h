#pragma once

#include "CPU.h"

namespace Tests {

	extern CPU* testCPU;

	bool testInstructions();

	bool testADD();
	bool testADDHL();
	bool testADC();
	bool testSUB();
	bool testSBC();
	bool testAND();
	bool testOR();
	bool testXOR();
	bool testCP();
	bool testINC();
	bool testDEC();
	bool testCCF();
	bool testSCF();
	bool testRRA();
	bool testRLA();
	bool testRRCA();
	bool testRRLA();
	bool testCPL();
	bool testBIT();
	bool testRESET();
	bool testSET();
	bool testSRL();
	bool testRR();
	bool testRL();
	bool testRRC();
	bool testRLC();
	bool testSRA();
	bool testSLA();
	bool testSWAP();
}