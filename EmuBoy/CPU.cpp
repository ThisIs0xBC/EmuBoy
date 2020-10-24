#include "CPU.h"

uint8_t CPU::insADD(Register* targetReg) {

	uint8_t aVal = this->a->value;
	uint8_t targetVal = targetReg->value;

	//if ((targetVal < 0) && (aVal < 0 - x)) /* `a + x` would underflow */; //We dont need to check for underflow

	uint8_t result = aVal + targetVal;

	// SET FLAGS
	// If operation results in an arithmetic overflow, set the flag. We could also just do if (result < aVal) (default C++ uint behaviour is to wrap when overflowed) here but I prefer this method for now
	if (aVal > UINT8_MAX - targetVal) this->f->carry = true;
	// We are not subtracting
	this->f->subtract = false;
	this->f->zero = result == 0;
	// The halfCarry flag gets set if adding the lower nibbles of the value and register A
	// together result in a value bigger than 0xF. If the result is larger than 0xF
	// then the addition caused a carry from the lower nibble to the upper nibble.
	this->f->halfCarry = (aVal & 0xF) + (targetVal & 0xF) > 0xF;

	this->a->value = result;

	return result;
}