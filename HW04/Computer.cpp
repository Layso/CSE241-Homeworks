/*
 * Computer.cpp
 * Contains Computer class function implementations
 *
 * This class simulates a computer. It contains a memory object of 50 cells, a
 * CPU object that takes assembly instructions to process data, which has 5
 * registers and permission to reach and make changes inside memory and a 
 * program object to let CPU work on
 *
 * This class coded for the homework 4 of GTU's CSE241 lecture, Fall 2016
 * File belongs to Deniz Can Erdem Yılmaz - 151044001
 * 
 * Initial date    - 27.10.2016
 * Completion date - 06.11.2016
 * Dead-line       - 06.11.2016 / 23:55
 */



/* Include(s) */
#include <string>
#include <iostream>
#include "Computer.h"
using namespace std;



Computer :: Computer(CPU myCpu, CPUProgram myProgram, Memory myMemory, int option)
{
	/* Assigning all parameters to the computers components after changing */
	/* their display option to prevent any conclusion  */
	myProgram.setMode(option);
	setCPUProgram(myProgram);
	
	myMemory.setMode(option);
	setMemory(myMemory);
	
	setMode(option);
	
	/* Also resetting program counter for CPU to prevent program malfunction */
	myCpu.setMode(option);
	myCpu.setPc(1);
	setCPU(myCpu);
}



Computer :: Computer(int option)
{
	/* Setting mode, all other components will be initialized by their */
	/* no parameter constructors */
	setMode(option);
}



/* Setting mode 0 as default if it doesn't given */
Computer :: Computer() : Computer(0)
{/* Intentionally blank */}



void Computer :: execute()
{
	string instruction;
	int pc;

	
	/* Checking program to see if there is any error before starting */
	if (program.getFlag())
		/* Creating a loop until CPU halts */
		while (!processor.halted())
		{
			/* Taking line equivalent to program counter from program */
			/* to execute instruction by processor */
			pc = processor.getPc();
			instruction = program.getLine(pc-1);
			processor.execute(instruction,ram);
		}
}

/* End of Computer.cpp */
