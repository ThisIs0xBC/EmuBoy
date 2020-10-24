#include "CPU.h"

#include <iostream>

uint8_t CPU::insADD(Register* targetReg) {

	uint8_t aVal = this->a->getValue();
	uint8_t targetVal = targetReg->getValue();

	uint8_t result = aVal + targetVal;

	// SET FLAGS
	// If operation results in an arithmetic overflow, set the flag. We could also just do if (result < aVal) (default C++ uint behaviour is to wrap when overflowed) here but I prefer this method for now
	if (aVal > UINT8_MAX - targetVal) this->f->carry = true;
	// We are not subtracting
	this->f->subtract = false;
	this->f->zero = result == 0;
	// The halfCarry flag gets set if adding the lower nibbles of the target register's 
	// value and register A together result in a value bigger than 0xF. If the result is
	// larger than 0xF then the addition caused a carry from the lower nibble to the upper nibble.
	this->f->halfCarry = (aVal & 0xF) + (targetVal & 0xF) > 0xF;

	this->a->setValue(result);

	return result;
}

uint16_t CPU::insADDHL(CombinedRegister* targetReg) {

	uint16_t hlVal = (*this->h + *this->l)->getValue(); //Operator overloading from my Register class
	uint16_t targetVal = targetReg->getValue();

	uint16_t result = hlVal + targetVal;

	// SET FLAGS
	// If operation results in an arithmetic overflow, set the flag. We could also just do if (result < aVal) (default C++ uint behaviour is to wrap when overflowed) here but I prefer this method for now
	if (hlVal > UINT16_MAX - targetVal) this->f->carry = true;
	// We are not subtracting
	this->f->subtract = false;
	this->f->zero = result == 0;
	// The halfCarry flag gets set if adding the 2 lower nibbles of the target register's value and the 
	// lower nibble of the HL register's value together result in a value bigger than 0xFF. If the result 
	// is larger than 0xFF then the addition caused a carry from the 3 lower nibbles to the upper nibble.
	this->f->halfCarry = (hlVal & 0xFF) + (targetVal & 0xFF) > 0xFF;

	this->h->setValue(result >> 8);	  //Top half of result
	this->l->setValue(result & 0xFF); //Bottom half of result

	return result;
}

uint8_t CPU::insADC(Register* targetReg) {

	uint8_t aVal = this->a->getValue();
	uint8_t targetVal = targetReg->getValue();

	uint8_t result = aVal + targetVal;

	// SET FLAGS
	// If operation results in an arithmetic overflow, set the flag. We could also just do if (result < aVal) here (as default C++ uint behaviour is to wrap when overflowed) but I prefer this method for now
	if (aVal > UINT8_MAX - targetVal) this->f->carry = true;
	// We are not subtracting
	this->f->subtract = false;
	this->f->zero = result == 0;
	// The halfCarry flag gets set if adding the lower nibbles of the target register's 
	// value and register A together result in a value bigger than 0xF. If the result is
	// larger than 0xF then the addition caused a carry from the lower nibble to the upper nibble.
	this->f->halfCarry = (aVal & 0xF) + (targetVal & 0xF) > 0xF;

	this->a->setValue(result + this->f->carry);

	return result;
}

uint8_t CPU::insSUB(Register* targetReg) {

	uint8_t aVal = this->a->getValue();
	uint8_t targetVal = targetReg->getValue();

	uint8_t result = aVal - targetVal;

	// SET FLAGS
	// If operation results in an arithmetic overflow, set the flag. We could also just do if (result < aVal) (default C++ uint behaviour is to wrap when overflowed) here but I prefer this method for now
	if (aVal < targetVal) this->f->carry = true;
	// We are not subtracting
	this->f->subtract = true;
	this->f->zero = result == 0;
	// The halfCarry flag gets set if adding the lower nibbles of the target register's 
	// value and register A together result in a value smaller than 0x1F. If the result is
	// smaller than 0x1F then the subtraction caused a carry from the upper nibble to the lower nibble.
	this->f->halfCarry = (aVal & 0xF) + (targetVal & 0xFF) >= 0x1F;

	this->a->setValue(result);

	return result;
}

uint8_t CPU::insSBC(Register* targetReg) {

	uint8_t aVal = this->a->getValue();
	uint8_t targetVal = targetReg->getValue();

	uint8_t result = aVal - targetVal;

	// SET FLAGS
	// If operation results in an arithmetic overflow, set the flag. We could also just do if (result < aVal) (default C++ uint behaviour is to wrap when overflowed) here but I prefer this method for now
	if (aVal < targetVal) this->f->carry = true;
	// We are not subtracting
	this->f->subtract = true;
	this->f->zero = result == 0;
	// The halfCarry flag gets set if adding the lower nibbles of the target register's 
	// value and register A together result in a value smaller than 0x1F. If the result is
	// smaller than 0x1F then the subtraction caused a carry from the upper nibble to the lower nibble.
	this->f->halfCarry = (aVal & 0xF) + (targetVal & 0xFF) >= 0x1F;

	this->a->setValue(result - this->f->carry);

	return result;

}

uint8_t CPU::insAND(Register* targetReg) {
	
	uint8_t aVal = this->a->getValue();
	uint8_t result = aVal & targetReg->getValue();
	this->a->setValue(result);

	return result;
}

uint8_t CPU::insOR(Register* targetReg) {

	uint8_t aVal = this->a->getValue();
	uint8_t result = aVal | targetReg->getValue();
	this->a->setValue(result);

	return result;
}

uint8_t CPU::insXOR(Register* targetReg) {

	uint8_t aVal = this->a->getValue();
	uint8_t result = aVal ^ targetReg->getValue();
	this->a->setValue(result);

	return result;
}

