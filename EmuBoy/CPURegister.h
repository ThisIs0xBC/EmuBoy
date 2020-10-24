#pragma once

#include <cstdint>

class Register {

private:

public:
	uint8_t value;

	uint16_t operator+(const Register* reg) {
		return this->value << 8 | reg->value;
	}

	Register() {
		this->value = 0x0;
	}

	~Register() {
		
	}
};

enum CPUFlags {
	FLAG_CARRY = 1,
	FLAG_HALF_CARRY = 2,
	FLAG_SUBTRACT = 4,
	FLAG_ZERO = 8
};


// This could be an inherited class from Register. Maybe I will change it in future.
class FlagsRegister {
	
private:

public:
	bool zero;
	bool subtract;
	bool halfCarry;
	bool carry;

	uint8_t get8BitValue() {
		// carry is casted to a uint8_t because the compiler throws warnings otherwise as it would be doing bitwise ops on a bool and an int (bool | int)
		return (uint8_t)carry | (halfCarry << 1) | (subtract << 2) | (zero << 3);
	}

	FlagsRegister() {
		this->zero = false;
		this->subtract = false;
		this->halfCarry = false;
		this->carry = false;
	}

	~FlagsRegister() {

	}
};