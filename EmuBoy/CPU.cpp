#include "CPU.h"

#include <iostream>

void CPU::setCombinedRegisterValue(Register &msbReg, Register &lsbReg, uint16_t value) {
	msbReg.setValue(value >> 8); //Top half of result
	lsbReg.setValue(value & 0xFF); //Bottom half of result
}

uint8_t CPU::insADD(Register targetReg) {

	uint8_t aVal = this->a.getValue();
	uint8_t targetVal = targetReg.getValue();

	uint8_t result = aVal + targetVal;

	// SET FLAGS
	this->f.setFlagZero(result == 0);
	this->f.setFlagSubtract(false); // We are not subtracting
	// The halfCarry flag gets set if adding the lower nibbles of the target register's 
	// value and register A together result in a value bigger than 0xF. If the result is
	// larger than 0xF then the addition caused a carry from the lower nibble to the upper nibble.
	this->f.setFlagHalfCarry((aVal & 0xF) + (targetVal & 0xF) > 0xF);
	// If operation results in an arithmetic overflow, set the flag. We could also just do if (result < aVal) (default C++ uint behaviour is to wrap when overflowed) here but I prefer this method for now
	this->f.setFlagCarry(aVal > UINT8_MAX - targetVal);


	this->a.setValue(result);

	return result;
}

uint16_t CPU::insADDHL(CombinedRegister targetReg) {

	uint16_t hlVal = (this->h + this->l).getValue(); //Operator overloading from my Register class
	uint16_t targetVal = targetReg.getValue();

	uint16_t result = hlVal + targetVal;

	// SET FLAGS
	this->f.setFlagZero(result == 0);
	this->f.setFlagSubtract(false); // We are not subtracting	
	// The halfCarry flag gets set if adding the 2 lower nibbles of the target register's value and the 
	// lower nibble of the HL register's value together result in a value bigger than 0xFF. If the result 
	// is larger than 0xFF then the addition caused a carry from the 3 lower nibbles to the upper nibble.
	this->f.setFlagHalfCarry((hlVal & 0xFFF) + (targetVal & 0xFFF) > 0xFFF);
	// If operation results in an arithmetic overflow, set the flag. We could also just do if (result < aVal) (default C++ uint behaviour is to wrap when overflowed) here but I prefer this method for now
	this->f.setFlagCarry(hlVal > UINT16_MAX - targetVal);

	this->h.setValue(result >> 8);	  //Top half of result
	this->l.setValue(result & 0xFF); //Bottom half of result

	return result;
}

uint8_t CPU::insADC(Register targetReg) {

	uint8_t aVal = this->a.getValue();
	uint8_t targetVal = targetReg.getValue() + this->f.getFlagCarry();

	uint8_t result = aVal + targetVal;

	// SET FLAGS
	this->f.setFlagZero(result == 0);
	this->f.setFlagSubtract(false); // We are not subtracting
	// The halfCarry flag gets set if adding the lower nibbles of the target register's 
	// value and register A together result in a value bigger than 0xF. If the result is
	// larger than 0xF then the addition caused a carry from the lower nibble to the upper nibble.
	this->f.setFlagHalfCarry((aVal & 0xF) + (targetVal & 0xF) > 0xF);
	// If operation results in an arithmetic overflow, set the flag. We could also just do if (result < aVal) here (as default C++ uint behaviour is to wrap when overflowed) but I prefer this method for now
	this->f.setFlagCarry(aVal > UINT8_MAX - targetVal);

	this->a.setValue(result);

	return result;
}

uint8_t CPU::insSUB(Register targetReg) {

	uint8_t aVal = this->a.getValue();
	uint8_t targetVal = targetReg.getValue();

	uint8_t result = aVal - targetVal;

	// SET FLAGS
	this->f.setFlagZero(result == 0);
	this->f.setFlagSubtract(true); // We are subtracting
	// The halfCarry flag gets set if adding the lower nibbles of the target register's 
	// value and register A together result in a value smaller than 0x1F. If the result is
	// smaller than 0x1F then the subtraction caused a carry from the upper nibble to the lower nibble.
	this->f.setFlagHalfCarry((aVal & 0xF) + (targetVal & 0xFF) >= 0x1F);
	// If operation results in an arithmetic overflow, set the flag. We could also just do if (result < aVal) (default C++ uint behaviour is to wrap when overflowed) here but I prefer this method for now
	this->f.setFlagCarry(aVal < targetVal);

	this->a.setValue(result);

	return result;
}

uint8_t CPU::insSBC(Register targetReg) {

	uint8_t aVal = this->a.getValue();
	uint8_t targetVal = targetReg.getValue() + this->f.getFlagCarry();

	uint8_t result = aVal - targetVal;

	// SET FLAGS
	this->f.setFlagZero(result == 0);
	this->f.setFlagSubtract(true); // We are subtracting
	// The halfCarry flag gets set if adding the lower nibbles of the target register's 
	// value and register A together result in a value smaller than 0x1F. If the result is
	// smaller than 0x1F then the subtraction caused a carry from the upper nibble to the lower nibble.
	this->f.setFlagHalfCarry((aVal >> 4) & (result >> 4) < 0xF);
	// If operation results in an arithmetic overflow, set the flag. We could also just do if (result < aVal) (default C++ uint behaviour is to wrap when overflowed) here but I prefer this method for now
	this->f.setFlagCarry(aVal < targetVal);

	this->a.setValue(result);

	return result;


}

uint8_t CPU::insAND(Register targetReg) {
	
	uint8_t aVal = this->a.getValue();
	uint8_t result = aVal & targetReg.getValue();

	// SET FLAGS
	this->f.setFlagZero(result == 0);
	this->f.setFlagSubtract(false);
	this->f.setFlagHalfCarry(true);
	this->f.setFlagCarry(false);

	this->a.setValue(result);

	return result;
}

uint8_t CPU::insOR(Register targetReg) {

	uint8_t aVal = this->a.getValue();
	uint8_t result = aVal | targetReg.getValue();

	// SET FLAGS
	this->f.setFlagZero(result == 0);
	this->f.setFlagSubtract(false);
	this->f.setFlagHalfCarry(false);
	this->f.setFlagCarry(false);

	this->a.setValue(result);

	return result;
}

uint8_t CPU::insXOR(Register targetReg) {

	uint8_t aVal = this->a.getValue();
	uint8_t result = aVal ^ targetReg.getValue();

	// SET FLAGS
	this->f.setFlagZero(result == 0);
	this->f.setFlagSubtract(false);
	this->f.setFlagHalfCarry(false);
	this->f.setFlagCarry(false);

	this->a.setValue(result);

	return result;
}

uint8_t CPU::insCP(Register targetReg) {

	uint8_t aVal = this->a.getValue();
	uint8_t targetVal = targetReg.getValue();

	uint8_t result = aVal - targetVal;


	// SET FLAGS
	this->f.setFlagZero(result == 0);
	this->f.setFlagSubtract(true); // We are subtracting
	// The halfCarry flag gets set if adding the lower nibbles of the target register's 
	// value and register A together result in a value larger than 0x1F. If the result is
	// larger than 0x1F then the subtraction caused a carry from the upper nibble to the lower nibble.
	this->f.setFlagHalfCarry((aVal & 0xF) + (targetVal & 0xFF) >= 0x1F);
	// If operation results in an arithmetic overflow, set the flag. We could also just do if (result < aVal) (default C++ uint behaviour is to wrap when overflowed) here but I prefer this method for now
	this->f.setFlagCarry(aVal < targetVal);
	
	// We don't store the result for the CP instruction

	return result;
}

uint8_t CPU::insINC(Register targetReg) {

	uint8_t targetVal = targetReg.getValue();
	uint8_t result = targetVal + 1;

	// SET FLAGS
	this->f.setFlagZero(result == 0);
	this->f.setFlagSubtract(false);
	// The halfCarry flag gets set if adding the lower nibbles of the target register's 
	// value and register A together result in a value bigger than 0xF. If the result is
	// larger than 0xF then the addition caused a carry from the lower nibble to the upper nibble.
	this->f.setFlagHalfCarry((targetVal & 0xF) + (0x1 & 0xF) > 0xF);
	this->f.setFlagCarry(targetVal > UINT8_MAX - 1);

	targetReg.setValue(result);

	return result;
}

uint8_t CPU::insDEC(Register targetReg) {

	uint8_t targetVal = targetReg.getValue();
	uint8_t result = targetVal - 1;

	// SET FLAGS
	this->f.setFlagZero(result == 0);
	this->f.setFlagSubtract(true); // We are subtracting
	// The halfCarry flag gets set if adding the lower nibbles of the target register's 
	// value and register A together result in a value smaller than 0x1F. If the result is
	// smaller than 0x1F then the subtraction caused a carry from the upper nibble to the lower nibble.
	this->f.setFlagHalfCarry((targetVal & 0xF) + (0x1 & 0xFF) >= 0x1F);
	// If operation results in an arithmetic overflow, set the flag. We could also just do if (result < aVal) (default C++ uint behaviour is to wrap when overflowed) here but I prefer this method for now
	this->f.setFlagCarry(targetVal < 1);

	targetReg.setValue(result);

	return result;
}

bool CPU::insCCF() {

	bool currentCarryState = this->f.getFlagCarry();
	bool newCarryState = !currentCarryState;

	// SET FLAGS
	this->f.setFlagSubtract(false);
	this->f.setFlagHalfCarry(false);
	this->f.setFlagCarry(newCarryState);

	return newCarryState;
}

bool CPU::insSCF() {

	// SET FLAGS
	this->f.setFlagSubtract(false);
	this->f.setFlagHalfCarry(false);
	this->f.setFlagCarry(true);

	return true;
}

uint8_t CPU::insRRA() {

	uint8_t aVal = this->a.getValue();
	uint8_t result = (uint8_t)this->f.getFlagCarry() | (aVal >> 1);
	bool newCarry = aVal & 0x1;

	// SET FLAGS
	this->f.setFlagZero(false);
	this->f.setFlagSubtract(false);
	this->f.setFlagHalfCarry(false);
	this->f.setFlagCarry(newCarry);

	this->a.setValue(result);

	return result;
}

uint8_t CPU::insRLA()
{

	uint8_t aVal = this->a.getValue();
	uint8_t result = (aVal << 1) | (uint8_t)this->f.getFlagCarry();
	bool newCarry = aVal >> 7;

	// SET FLAGS
	this->f.setFlagZero(false);
	this->f.setFlagSubtract(false);
	this->f.setFlagHalfCarry(false);
	this->f.setFlagCarry(newCarry);

	this->a.setValue(result);

	return result;
}

uint8_t CPU::insRRCA()
{
	
	uint8_t aVal = this->a.getValue();
	uint8_t result = aVal >> 1;
	bool newCarry = aVal & 0x1;

	// SET FLAGS
	this->f.setFlagZero(false);
	this->f.setFlagSubtract(false);
	this->f.setFlagHalfCarry(false);
	this->f.setFlagCarry(newCarry);

	this->a.setValue(result);

	return result;
}

uint8_t CPU::insRLCA()
{
	
	uint8_t aVal = this->a.getValue();
	uint8_t result = (aVal << 1) | (aVal >> 7);
	bool newCarry = aVal >> 7;

	// SET FLAGS
	this->f.setFlagZero(false);
	this->f.setFlagSubtract(false);
	this->f.setFlagHalfCarry(false);
	this->f.setFlagCarry(newCarry);

	this->a.setValue(result);

	return result;

}

uint8_t CPU::insCPL()
{

	uint8_t aVal = this->a.getValue();
	uint8_t result = ~aVal;

	// SET FLAGS
	this->f.setFlagSubtract(true);
	this->f.setFlagHalfCarry(true);

	this->a.setValue(result);

	return result;

}

bool CPU::insBIT(uint8_t bit, Register targetReg)
{
	
	// SET FLAGS
	if ((targetReg.getValue()) & (1 << (bit))) {
		this->f.setFlagZero(true);
		return true;
	}
	else {
		this->f.setFlagZero(false);
		return false;
	}

	this->f.setFlagSubtract(false);
	this->f.setFlagHalfCarry(true);

}

void CPU::insRESET(uint8_t bit, Register targetReg)
{

	uint8_t targetVal = targetReg.getValue();
	uint8_t result = targetVal & ~(1UL << bit);

	targetReg.setValue(result);
}

void CPU::insSET(uint8_t bit, Register targetReg)
{
	
	uint8_t targetVal = targetReg.getValue();
	uint8_t result = targetVal |= 1 << bit;

	targetReg.setValue(result);
}

uint8_t CPU::insSRL(Register targetReg)
{
	
	uint8_t targetVal = targetReg.getValue();
	uint8_t result = targetVal >> 1;
	bool newCarry = targetVal & 0x1;

	// SET FLAGS
	this->f.setFlagZero(result == 0);
	this->f.setFlagSubtract(false);
	this->f.setFlagHalfCarry(false);
	this->f.setFlagCarry(newCarry);

	targetReg.setValue(result);

	return result;
}

uint8_t CPU::insRR(Register targetReg)
{
	
	uint8_t targetVal = targetReg.getValue();
	uint8_t result = (uint8_t)this->f.getFlagCarry() | (targetVal >> 1);
	bool newCarry = targetVal & 0x1;

	// SET FLAGS
	this->f.setFlagZero(result == 0);
	this->f.setFlagSubtract(false);
	this->f.setFlagHalfCarry(false);
	this->f.setFlagCarry(newCarry);

	targetReg.setValue(result);

	return result;
}

uint8_t CPU::insRL(Register targetReg)
{

	uint8_t targetVal = targetReg.getValue();
	uint8_t result = (targetVal << 1) | (uint8_t)this->f.getFlagCarry();
	bool newCarry = targetVal >> 7;

	// SET FLAGS
	this->f.setFlagZero(result == 0);
	this->f.setFlagSubtract(false);
	this->f.setFlagHalfCarry(false);
	this->f.setFlagCarry(newCarry);

	targetReg.setValue(result);

	return result;
}

uint8_t CPU::insRRC(Register targetReg)
{
	
	uint8_t targetVal = targetReg.getValue();
	uint8_t result = targetVal >> 1;
	bool newCarry = targetVal >> 7;

	// SET FLAGS
	this->f.setFlagZero(result == 0);
	this->f.setFlagSubtract(false);
	this->f.setFlagHalfCarry(false);
	this->f.setFlagCarry(newCarry);

	targetReg.setValue(result);

	return result;
}

uint8_t CPU::insRLC(Register targetReg)
{

	uint8_t targetVal = targetReg.getValue();
	uint8_t result = (targetVal << 1) | (targetVal >> 7);
	bool newCarry = targetVal >> 7;

	// SET FLAGS
	this->f.setFlagZero(result == 0);
	this->f.setFlagSubtract(false);
	this->f.setFlagHalfCarry(false);
	this->f.setFlagCarry(newCarry);

	this->a.setValue(result);

	return result;
}

uint8_t CPU::insSRA(Register targetReg)
{
	
	uint8_t targetVal = targetReg.getValue();
	uint8_t oldMSB = targetVal >> 7; //Get the MSB of the targetVal
	uint8_t result = targetVal >> 1;
	result ^= (-oldMSB ^ result) & (1 << 7); //Set the MSB of the logical shifted result to the MSB of the original number in targetReg
	bool newCarry = targetVal & 0x1;

	// SET FLAGS
	this->f.setFlagZero(result == 0);
	this->f.setFlagSubtract(false);
	this->f.setFlagHalfCarry(false);
	this->f.setFlagCarry(newCarry);

	targetReg.setValue(result);

	return result;
}

uint8_t CPU::insSLA(Register targetReg)
{
	
	uint8_t targetVal = targetReg.getValue();
	uint8_t result = targetVal << 1;
	bool newCarry = targetVal >> 7;

	// SET FLAGS
	this->f.setFlagZero(result == 0);
	this->f.setFlagSubtract(false);
	this->f.setFlagHalfCarry(false);
	this->f.setFlagCarry(newCarry);

	targetReg.setValue(result);

	return result;
}

uint8_t CPU::insSWAP(Register targetReg)
{

	uint8_t targetVal = targetReg.getValue();
	uint8_t result = ((targetVal & 0x0F) << 4 | (targetVal & 0xF0) >> 4);

	// SET FLAGS
	this->f.setFlagZero(result == 0);
	this->f.setFlagSubtract(false);
	this->f.setFlagHalfCarry(false);
	this->f.setFlagCarry(false);

	targetReg.setValue(result);

	return result;
}

