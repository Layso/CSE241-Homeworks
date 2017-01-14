/*
 * Computer.h is the header file of Computer.cpp
 * Contains Computer class prototype
 *
 * This class simulates a computer. It contains a memory object of 50 cells, a
 * CPU object that takes assembly instructions to process data, which has 5
 * registers and permission to reach and make changes inside memory and a 
 * program object to let CPU work on
 *
 * This class coded for the homework 4 of GTU's CSE241 lecture, Fall 2016
 * File belongs to Deniz Can Erdem Yılmaz - 151044001
 * 
 * Initial date    - ??.11.2016
 * Completion date - 15.11.2016
 * Dead-line       - 15.11.2016 / 23:55
 */



/* Using ifndef to prevent redefinitions */
#ifndef _COMPUTER_H__
#define _COMPUTER_H__

#include "CPU.h"
#include "CPUProgram.h"
#include "Memory.h"
using namespace std;



class Computer
{
public:
    Computer(CPU myCpu, CPUProgram myProgram, Memory myMemory, int option);
                            //Constructor with all members to initialize
    Computer(int option);   //Constructor with only int parameter
    Computer();             //Constructor without parameters
    
    
    /* Main function to run computer*/
    void execute();
    
    /* Processor setter/getter */
    void setCPU(CPU cpuParam) {processor = cpuParam;}
    CPU getCPU() const {return processor;}
    
    /* Program setter/getter */
    void setCPUProgram(CPUProgram programParam) {program = programParam;}
    CPUProgram getCPUProgram() const {return program;}
    
    /* RAM setter/getter */
    void setMemory(Memory memoryParam) {ram = memoryParam;}
    Memory getMemory() const {return ram;}
    
    /* Mode setter/getter */
    void setMode(int modeParam) {mode = modeParam;}
    int getMode() const {return mode;}
    
private:
    /* Data variables */
    CPU processor;
    CPUProgram program;
    Memory ram;
    int mode;
};

#endif

/* End of Computer.h */
