/*
 * main.cpp
 * This is the main (driver) file
 * 
 * This main file has copied from the HW6 definition PDF to test all classes
 * acquired for homework. It creates objects of CPUProgramDyn class with 
 * implemented constructors, makes a few tests of its functions
 *
 * This file coded for the homework 6 of GTU's CSE241 lecture, Fall 2016
 * File belongs to Deniz Can Erdem Yılmaz - 151044001
 * 
 * Initial date    - 29.11.2016
 * Completion date - 02.12.2016
 * Dead-line       - 30.11.2016 / 23:55
 */



/* Include(s) */
#include "requiredIncs.h"

void testFunc(CPUProgramDyn myCPUProgram, const char* filename, int option)
{
	myCPUProgram.ReadFile(filename);
	cout << myCPUProgram[0] << endl;
	cout << myCPUProgram[myCPUProgram.size() - 1] << endl;
	
	//op +
	cout << ((myCPUProgram + "MOV R1, #45")[myCPUProgram.size()]) << endl;
	
	//op +=
	myCPUProgram += "MOV R2, #50";
	cout << myCPUProgram[myCPUProgram.size() - 1] << endl;
	
	
	//op + <<
	CPUProgramDyn myOtherCPUProgram(option);
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
	//////////////////////////////////////////////////////////////////////////*/
}

int main(int argc, char** argv){
	//////////////////////////////////////////////////////////////////////////
	//command line parameters
	const char* filename = argv[1];
	int option = atoi(argv[2]);
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	//Testing class CPUProgramDyn
	CPUProgramDyn myProg(option);
	testFunc(myProg, filename, option);
	// Test again	
	testFunc(myProg, filename, option);
	// Test with a copy
	CPUProgramDyn myProgCopy(myProg);	
	testFunc(myProgCopy, filename, option);
	//////////////////////////////////////////////////////////////////////////

	return 0;
}

/* End of main.cpp */
