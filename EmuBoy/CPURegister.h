#pragma once

#include <cstdint>

enum CPUFlags {
	FLAG_CARRY = 1,
	FLAG_HALF_CARRY = 2,
	FLAG_SUBTRACT = 4,
	FLAG_ZERO = 8
};

class Register;
class CombinedRegister;
class FlagsRegister;

// This could potentially be an inherited class from Register. Maybe I will change it in future.
class CombinedRegister {

private:
	uint16_t value;

protected:

public:

	uint16_t getValue() { return this->value; }
	void     setValue(uint16_t newVal) { this->value = newVal; }

	CombinedRegister() {
		this->value = 0x0;
	}

	CombinedRegister(uint16_t _value) {
		this->value = _value;
	}

	~CombinedRegister() {

	}

};

class Register {

private:
	uint8_t value;

protected:

public:

	uint8_t getValue()				 { return this->value; }
	void    setValue(uint8_t newVal) { this->value = newVal; }

	CombinedRegister* operator+(const Register& reg) {
		return new CombinedRegister(this->value << 8 | reg.value);
	}

	Register() {
		this->value = 0x0;
	}

	~Register() {
		
	}
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