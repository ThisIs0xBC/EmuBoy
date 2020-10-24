#pragma once

#include "CPURegister.h"

//Full CPU class here
class CPU {

private:

public:
	Register* a;
	Register* b;
	Register* c;
	Register* d;
	Register* e;
	Register* g;
	Register* h;
	Register* l;
	FlagsRegister* f;

	//TODO: Add these
	//ProgramCounter pc;
	//MemoryBus memBus;

	CPU() {
		this->a = new Register();
		this->b = new Register();
		this->c = new Register();
		this->d = new Register();
		this->e = new Register();
		this->g = new Register();
		this->h = new Register();
		this->l = new Register();
		this->f = new FlagsRegister();
	}

	~CPU() {
		delete this->a;
		delete this->b;
		delete this->c;
		delete this->d;
		delete this->e;
		delete this->g;
		delete this->h;
		delete this->l;
		delete this->f;
	}

	uint8_t insADD(Register* targetReg);
};