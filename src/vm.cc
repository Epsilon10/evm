#include "vm.h"

/*
    *Instruction format:
    * 2 bit header
    * data: 30 bits
    * 
    * header format:
    * 0 => positive integer
    * 1 => Primitive instruction
    * 2 => negative integer
    * 3 => undefined
*/

StackVM::StackVM() {
     memory.reserve(1000000);
}

i32 StackVM::getType(i32 instruction) {
    i32 type = 0xc0000000;
    // every instruction has a 2 bit header which says what sort of instruction it is
    type = (type & instruction) >> 30; // shift by 30 bits to capture the 3 bit header 
    return type;

}

i32 StackVM::getData(i32 instruction) {
    i32 data = 0x3fffffff; // 30 bit representation
    data = data & instruction;
    return data;
}

inline void StackVM::fetch() {
    pc++; // incrementing our program counter
}

void StackVM::decode() {
    typ = getType(memory[pc]); // getting the instruction at memory. Pc is where u r in the memory. THis sets the first two bits in the thing
    dat = getData(memory[pc]);
}

void StackVM::execute() {
    if (typ == 0 || typ == 3) { // if its a positive or negative number
        sp++;
        memory[sp] = dat;
    }
    else {
        doPrimitive(); // TODO: implement this
    }

}

void StackVM::doPrimitive() {
    switch(dat) {
        case 0: // halt
            std::cout << "halt" << std::endl;
            running = 0;
            break;
        case 1: // add
            std::cout << "add" << memory[sp - 1] << " " << memory[sp] << std::endl;
            // when we add to values from the stack, we will pop two values off the stack 
            memory[sp - 1] = memory[sp-1] + memory[sp];
            break;

    }

}

void StackVM::run() {
    pc -= 1; // put it to the instruction b4 because when we fetch(), it gets the first instruction u want
    while (running == 1) {
        fetch(); // go to the next instruction
        decode(); // decode the instruction
        execute(); // execute the instruction and write the data to the memory
        std::cout << "top of the stack: " << memory[sp] << std::endl;

    }
}

void StackVM::loadProgram(std::vector<i32>& program) {
    for (i32 i = 0; i < program.size(); i++) {
        memory[pc + i] = program[i];
    }
}