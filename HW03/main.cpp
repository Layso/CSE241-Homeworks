/*
 * main.cpp
 * This is the main (driver) file
 * main checks the parameters and creates 2 objects. Uses them in a loop to 
 * process the given CPU program
 *
 * This class coded for the homework 3 of GTU's CSE241 lecture, Fall 2016
 * File belongs to Deniz Can Erdem Yılmaz - 151044001
 * 27/10/2016
 */



/* Include(s) */
#include <iostream>
#include <string>
#include <fstream>
#include "cpuProgram.h"
#include "cpu.h"

using namespace std;



int main(int argc, char **argv)
{
	/* Checking parameter error */
	if (argc < 3)
		cerr << "Parameter error: Not enough parameters given" << endl;
	
	else if (argc > 3)
		cerr << "Parameter error: Too much parameters given" << endl;
	
	else
	{
		cpuProgram myProgram(argv[1]);
		cpu myCpu(argv[2]);
		string instruction;
		int pc;
		
		/* Creating a loop if error flag is not false */
		if (myProgram.getFlag())
			while (!myCpu.halted())
			{
				pc = myCpu.getPc();
				instruction = myProgram.getLine(pc);
				myCpu.execute(instruction);
			}
	}
	
	
	return (0);
}

/* End of main.cpp */
