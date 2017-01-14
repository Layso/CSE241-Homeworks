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
	////////////////////////////////////////////////////////////////////////////
	//command line parameters
	const char* filename = argv[1];
	int option = atoi(argv[2]);
	////////////////////////////////////////////////////////////////////////////
	
	////////////////////////////////////////////////////////////////////////////
	//Testing class CPUProgram
	//op []
	CPUProgram myCPUProgram(option);
	myCPUProgram.ReadFile(filename);
	cout << myCPUProgram[0] << endl;
	cout << myCPUProgram[myCPUProgram.size() - 1] << endl;
	
	//op +
	cout << ((myCPUProgram + "MOV R1, #45")[myCPUProgram.size() - 1]) << endl;
	
	//op +=
	myCPUProgram += "MOV R2, #50";
	cout << myCPUProgram[myCPUProgram.size() - 1] << endl;
	
	//op + <<
	CPUProgram myOtherCPUProgram(option);
	myOtherCPUProgram.ReadFile(filename);
	cout << (myCPUProgram + myOtherCPUProgram) << endl;
	
	//op COMP --
	cout << (myCPUProgram == myOtherCPUProgram ? "DONE" : "FAIL") << endl;
	cout << (myCPUProgram <= myOtherCPUProgram ? "DONE" : "FAIL") << endl;
	cout << (myCPUProgram > myOtherCPUProgram ? "FAIL" : "DONE") << endl;
	
	--myOtherCPUProgram;
	
	cout << (myCPUProgram != myOtherCPUProgram ? "DONE" : "FAIL") << endl;
	cout << (myCPUProgram >= myOtherCPUProgram ? "DONE" : "FAIL") << endl;
	cout << (myCPUProgram < myOtherCPUProgram ? "FAIL" : "DONE") << endl;
	
	//op ()
	cout << myCPUProgram(5, 10) << endl;
	
	//error check
	cout << myCPUProgram[myCPUProgram.size()] << endl;
	
	myCPUProgram += "";
	cout << myCPUProgram[myCPUProgram.size() - 1] << endl;
	////////////////////////////////////////////////////////////////////////////

	
	return (0);
}

/* End of main.cpp */
