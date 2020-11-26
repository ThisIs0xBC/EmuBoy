// EmuBoy.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include "CPU.h"
#include "tests.h"

CPU* gbCPU = nullptr;

void printCPUFlags() {
    // Get the current CPU flags listed as an 8 bit uint where the LSB nibble has contains 4 bools, each one being a flag
    uint8_t currentFlags = gbCPU->f.get8BitValue();

    if (currentFlags & FLAG_ZERO) std::cout << "FLAG_ZERO Set" << std::endl;
    if (currentFlags & FLAG_SUBTRACT) std::cout << "FLAG_SUBTRACT Set" << std::endl;
    if (currentFlags & FLAG_HALF_CARRY) std::cout << "FLAG_HALF_CARRY Set" << std::endl;
    if (currentFlags & FLAG_CARRY) std::cout << "FLAG_CARRY Set" << std::endl;
}

int main()
{

    gbCPU = new CPU();

    /*// The A register's value is casted to a uint16 due to iostream trying to processs and print uint8s as 
    // unsigned chars because that is what they are typedef'ed as. This makes them print as an integer instead
    std::cout << "Current Accumulator Value: " << (uint16_t)gbCPU->a->getValue() << std::endl;
    std::cout << "Setting Register C's Value to 220" << std::endl;
    gbCPU->c->setValue(220ui8);
    std::cout << "Adding Register C's Value to Register A's Value" << std::endl;
    gbCPU->insADD(gbCPU->c);
    printCPUFlags(); //See if any flags changed, they shouldn't have changed at this point
    std::cout << "Current Accumulator Value: " << (uint16_t)gbCPU->a->getValue() << std::endl;
    std::cout << "Setting Register B's Value to 65" << std::endl;
    gbCPU->b->setValue(65ui8);
    std::cout << "Adding Register B's Value to Register A's Value" << std::endl;
    gbCPU->insADD(gbCPU->b);
    printCPUFlags(); //See if any flags changed, carry should've been set by now
    std::cout << "Current Accumulator Value: " << (uint16_t)gbCPU->a->getValue() << std::endl;

    std::cout << "\nResetting CPU...\n" << std::endl;

    gbCPU = new CPU();

    std::cout << "Current Accumulator Value: " << (uint16_t)gbCPU->a->getValue() << std::endl;
    std::cout << "Setting Register C's Value to 250" << std::endl;
    gbCPU->c->setValue(250ui8);
    std::cout << "Adding Register C's Value to Register A's Value" << std::endl;
    gbCPU->insADD(gbCPU->c);
    printCPUFlags(); //See if any flags changed, they shouldn't have changed at this point
    std::cout << "Current Accumulator Value: " << (uint16_t)gbCPU->a->getValue() << std::endl;
    std::cout << "Setting Register B's Value to 65" << std::endl;
    gbCPU->b->setValue(65ui8);
    std::cout << "Subtracting Register B's Value from Register A's Value" << std::endl;
    gbCPU->insSUB(gbCPU->b);
    printCPUFlags(); //See if any flags changed, subtract and half carry should've been set by now
    std::cout << "Current Accumulator Value: " << (uint16_t)gbCPU->a->getValue() << std::endl;

    //((var) & (1 << (pos)))
    std::cout << "\nResetting CPU...\n" << std::endl;

    gbCPU = new CPU();
    gbCPU->a.setValue(0ui8);
    std::cout << "Current Accumulator Value In Binary: 00000000 (" << (uint16_t)gbCPU->a.getValue() << ")" << std::endl;
    gbCPU->f.setFlagCarry(false);
    std::cout << "FLAG_CARRY Is false (0)" << std::endl;
    std::cout << "Calling RRA Instruction" << std::endl;
    gbCPU->insRRA();
    std::cout << "Current Accumulator Value In Binary: ";
    for (int i = 7; i >= 0; i--) {
        if ((gbCPU->a.getValue()) & (1 << (i)))
            std::cout << "1";
        else
            std::cout << "0";
    }
    std::cout << "(" << (uint16_t)gbCPU->a.getValue() << ")" << std::endl;

    if (gbCPU->f.getFlagCarry())
        std::cout << "FLAG_CARRY Is True (1)" << std::endl;
    else
        std::cout << "FLAG_CARRY Is false (0)" << std::endl;

    std::cout << std::endl;

    gbCPU = new CPU();
    gbCPU->a.setValue(255ui8);
    std::cout << "Current Accumulator Value In Binary: 11111111 (" << (uint16_t)gbCPU->a.getValue() << ")" << std::endl;
    gbCPU->f.setFlagCarry(false);
    std::cout << "FLAG_CARRY Is false (0)" << std::endl;
    std::cout << "Calling RRA Instruction" << std::endl;
    gbCPU->insRRA();
    std::cout << "Current Accumulator Value In Binary: ";
    for (int i = 7; i >= 0; i--) {
        if ((gbCPU->a.getValue()) & (1 << (i)))
            std::cout << "1";
        else
            std::cout << "0";
    }
    std::cout << "(" << (uint16_t)gbCPU->a.getValue() << ")" << std::endl;

    if (gbCPU->f.getFlagCarry())
        std::cout << "FLAG_CARRY Is True (1)" << std::endl;
    else
        std::cout << "FLAG_CARRY Is false (0)" << std::endl;

    std::cout << std::endl;

    gbCPU = new CPU();
    gbCPU->a.setValue(15ui8);
    std::cout << "Current Accumulator Value In Binary: 00001111 (" << (uint16_t)gbCPU->a.getValue() << ")" << std::endl;
    gbCPU->f.setFlagCarry(true);
    std::cout << "FLAG_CARRY Is True (1)" << std::endl;
    std::cout << "Calling RRA Instruction" << std::endl;
    gbCPU->insRRA();
    std::cout << "Current Accumulator Value In Binary: ";
    for (int i = 7; i >= 0; i--) {
        if ((gbCPU->a.getValue()) & (1 << (i)))
            std::cout << "1";
        else
            std::cout << "0";
    }
    std::cout << "(" << (uint16_t)gbCPU->a.getValue() << ")" << std::endl;

    if (gbCPU->f.getFlagCarry())
        std::cout << "FLAG_CARRY Is True (1)" << std::endl;
    else
        std::cout << "FLAG_CARRY Is false (0)" << std::endl;

    std::cout << std::endl;

    gbCPU = new CPU();
    gbCPU->a.setValue(170ui8);
    std::cout << "Current Accumulator Value In Binary: 10101010 (" << (uint16_t)gbCPU->a.getValue() << ")" << std::endl;
    gbCPU->f.setFlagCarry(true);
    std::cout << "FLAG_CARRY Is True (1)" << std::endl;
    std::cout << "Calling RRA Instruction" << std::endl;
    gbCPU->insRRA();
    std::cout << "Current Accumulator Value In Binary: ";
    for (int i = 7; i >= 0; i--) {
        if ((gbCPU->a.getValue()) & (1 << (i)))
            std::cout << "1";
        else
            std::cout << "0";
    }
    std::cout << "(" << (uint16_t)gbCPU->a.getValue() << ")" << std::endl;

    if (gbCPU->f.getFlagCarry())
        std::cout << "FLAG_CARRY Is True (1)" << std::endl;
    else
        std::cout << "FLAG_CARRY Is false (0)" << std::endl;

    std::cout << std::endl;

    gbCPU = new CPU();
    gbCPU->a.setValue(85ui8);
    std::cout << "Current Accumulator Value In Binary: 01010101 (" << (uint16_t)gbCPU->a.getValue() << ")" << std::endl;
    gbCPU->f.setFlagCarry(false);
    std::cout << "FLAG_CARRY Is false (0)" << std::endl;
    std::cout << "Calling RRA Instruction" << std::endl;
    gbCPU->insRRA();
    std::cout << "Current Accumulator Value In Binary: ";
    for (int i = 7; i >= 0; i--) {
        if ((gbCPU->a.getValue()) & (1 << (i)))
            std::cout << "1";
        else
            std::cout << "0";
    }
    std::cout << "(" << (uint16_t)gbCPU->a.getValue() << ")" << std::endl;

    if (gbCPU->f.getFlagCarry())
        std::cout << "FLAG_CARRY Is True (1)" << std::endl;
    else
        std::cout << "FLAG_CARRY Is false (0)" << std::endl;

    std::cout << "\n\nROTATE LEFT\n\n" << std::endl;




    gbCPU = new CPU();
    gbCPU->a.setValue(0ui8);
    std::cout << "Current Accumulator Value In Binary: 00000000 (" << (uint16_t)gbCPU->a.getValue() << ")" << std::endl;
    gbCPU->f.setFlagCarry(false);
    std::cout << "FLAG_CARRY Is false (0)" << std::endl;
    std::cout << "Calling RRA Instruction" << std::endl;
    gbCPU->insRLA();
    std::cout << "Current Accumulator Value In Binary: ";
    for (int i = 7; i >= 0; i--) {
        if ((gbCPU->a.getValue()) & (1 << (i)))
            std::cout << "1";
        else
            std::cout << "0";
    }
    std::cout << "(" << (uint16_t)gbCPU->a.getValue() << ")" << std::endl;

    if (gbCPU->f.getFlagCarry())
        std::cout << "FLAG_CARRY Is True (1)" << std::endl;
    else
        std::cout << "FLAG_CARRY Is false (0)" << std::endl;

    std::cout << std::endl;

    gbCPU = new CPU();
    gbCPU->a.setValue(255ui8);
    std::cout << "Current Accumulator Value In Binary: 11111111 (" << (uint16_t)gbCPU->a.getValue() << ")" << std::endl;
    gbCPU->f.setFlagCarry(false);
    std::cout << "FLAG_CARRY Is false (0)" << std::endl;
    std::cout << "Calling RRA Instruction" << std::endl;
    gbCPU->insRLA();
    std::cout << "Current Accumulator Value In Binary: ";
    for (int i = 7; i >= 0; i--) {
        if ((gbCPU->a.getValue()) & (1 << (i)))
            std::cout << "1";
        else
            std::cout << "0";
    }
    std::cout << "(" << (uint16_t)gbCPU->a.getValue() << ")" << std::endl;

    if (gbCPU->f.getFlagCarry())
        std::cout << "FLAG_CARRY Is True (1)" << std::endl;
    else
        std::cout << "FLAG_CARRY Is false (0)" << std::endl;

    std::cout << std::endl;

    gbCPU = new CPU();
    gbCPU->a.setValue(15ui8);
    std::cout << "Current Accumulator Value In Binary: 00001111 (" << (uint16_t)gbCPU->a.getValue() << ")" << std::endl;
    gbCPU->f.setFlagCarry(false);
    std::cout << "FLAG_CARRY Is false (0)" << std::endl;
    std::cout << "Calling RRA Instruction" << std::endl;
    gbCPU->insRLA();
    std::cout << "Current Accumulator Value In Binary: ";
    for (int i = 7; i >= 0; i--) {
        if ((gbCPU->a.getValue()) & (1 << (i)))
            std::cout << "1";
        else
            std::cout << "0";
    }
    std::cout << "(" << (uint16_t)gbCPU->a.getValue() << ")" << std::endl;

    if (gbCPU->f.getFlagCarry())
        std::cout << "FLAG_CARRY Is True (1)" << std::endl;
    else
        std::cout << "FLAG_CARRY Is false (0)" << std::endl;

    std::cout << std::endl;

    gbCPU = new CPU();
    gbCPU->a.setValue(170ui8);
    std::cout << "Current Accumulator Value In Binary: 10101010 (" << (uint16_t)gbCPU->a.getValue() << ")" << std::endl;
    gbCPU->f.setFlagCarry(true);
    std::cout << "FLAG_CARRY Is True (1)" << std::endl;
    std::cout << "Calling RRA Instruction" << std::endl;
    gbCPU->insRLA();
    std::cout << "Current Accumulator Value In Binary: ";
    for (int i = 7; i >= 0; i--) {
        if ((gbCPU->a.getValue()) & (1 << (i)))
            std::cout << "1";
        else
            std::cout << "0";
    }
    std::cout << "(" << (uint16_t)gbCPU->a.getValue() << ")" << std::endl;

    if (gbCPU->f.getFlagCarry())
        std::cout << "FLAG_CARRY Is True (1)" << std::endl;
    else
        std::cout << "FLAG_CARRY Is false (0)" << std::endl;

    std::cout << std::endl;

    gbCPU = new CPU();
    gbCPU->a.setValue(85ui8);
    std::cout << "Current Accumulator Value In Binary: 01010101 (" << (uint16_t)gbCPU->a.getValue() << ")" << std::endl;
    gbCPU->f.setFlagCarry(true);
    std::cout << "FLAG_CARRY Is True (1)" << std::endl;
    std::cout << "Calling RRA Instruction" << std::endl;
    gbCPU->insRLA();
    std::cout << "Current Accumulator Value In Binary: ";
    for (int i = 7; i >= 0; i--) {
        if ((gbCPU->a.getValue()) & (1 << (i)))
            std::cout << "1";
        else
            std::cout << "0";
    }
    std::cout << "(" << (uint16_t)gbCPU->a.getValue() << ")" << std::endl;

    if (gbCPU->f.getFlagCarry())
        std::cout << "FLAG_CARRY Is True (1)" << std::endl;
    else
        std::cout << "FLAG_CARRY Is false (0)" << std::endl;

    std::cout << std::endl;*/

    std::cout << Tests::testInstructions() << std::endl;
}