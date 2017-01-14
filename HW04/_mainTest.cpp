/*
 * main.cpp
 * This is the main (driver) file
 * 
 * This main file has copied from the HW4 definition PDF to test all classes
 * acquired for homework. It creates objects of all 3 classes (CPU, CPUProgram,
 * Memory) with implemented constructors, makes a few tests of their functions
 * and then buries them into 2 different Computer object to test Computer class
 * Repeats function tests for Computer class
 *
 * This file coded for the homework 4 of GTU's CSE241 lecture, Fall 2016
 * File belongs to Deniz Can Erdem Yılmaz - 151044001
 * 
 * Initial date    - 27.10.2016
 * Completion date - 06.11.2016
 * Dead-line       - 06.11.2016 / 23:55
 */



/* Include(s) */
#include "requiredIncs.h"

using namespace std;



int main(int argc, char **argv)
{
	/* Checking the parameter count and printing error if necessary */
	if (argc < 3)
		cerr << "Parameter error: Not enough parameters given" << endl;
	
	else if (argc > 3)
		cerr << "Parameter error: Too much parameters given" << endl;
	
	/* Program can continue if enough arguments has given */
	else
	{
		////////////////////////////////////////////////////////////////////////
		//command line parameters 
		const char* filename = argv[1];
		int option = atoi(argv[2]);
		////////////////////////////////////////////////////////////////////////



		////////////////////////////////////////////////////////////////////////
		//Testing class Memory
		Memory myMemory(option);
		//index, value
		myMemory.setMem(0, 100);
		cout << myMemory.getMem(0) << endl;
		//should print in a way that similar to this:
		//Memory Values:
		//[0] -> 100
		//[1] -> 0
		//[2] -> 0
		//. 
		//.
		//[49] -> 0
		myMemory.printAll();
		////////////////////////////////////////////////////////////////////////



		////////////////////////////////////////////////////////////////////////
		//Testing class CPU
		//
		// READ PLEASE!!
		// In order to let any CPU object work, lines should be re-organized by 
		// formatEditor() function inside CPUProgram class. Else there must be
		// a constant format to give execution lines to execute function which
		// is :"INS PR,PR ". The order of blanks and parameters are important
		// Test conditions changed due to the explanation above
		CPU myCPU(option);
		myCPU.execute("MOV #0,R1 ", myMemory);
		myCPU.execute("MOV R1,#1 ", myMemory);

		//should print in a way that similar to this:
		//CPU Register Values:
		//[0] -> 100
		//[1] -> 0
		//[2] -> 0
		//[3] -> 0
		//[4] -> 0
		myCPU.print();

		//should print in a way that similar to this:
		//Memory Values:
		//[0] -> 100
		//[1] -> 100
		//[2] -> 0
		//.
		//.
		//[49] -> 0
		myMemory.printAll();
		////////////////////////////////////////////////////////////////////////



		////////////////////////////////////////////////////////////////////////
		//Testing class CPUProgram
		// READ PLEASE !!
		CPUProgram myCPUProgram(option);
		myCPUProgram.readFile(filename);
		cout << myCPUProgram.getLine(0) << endl;
		cout << myCPUProgram.getLine(myCPUProgram.size( ) - 1) << endl;
		////////////////////////////////////////////////////////////////////////



		////////////////////////////////////////////////////////////////////////
		//Testing class Computer
		Computer myComputer1(myCPU, myCPUProgram, myMemory, option);
		Computer myComputer2(option);

		myComputer2.setCPU( myComputer1.getCPU());
		myComputer2.setCPUProgram(myComputer1.getCPUProgram());
		myComputer2.setMemory(myComputer1.getMemory());

		myComputer2.execute();
		////////////////////////////////////////////////////////////////////////
	}
	
	
	return (0);
}

/* End of main.cpp */
