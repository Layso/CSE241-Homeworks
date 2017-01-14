/*
 * Memory.h is the header file of Memory.cpp
 * Contains Memory class prototype
 *
 * This class simulates a set of memory (50 cells) which are able to load and
 * unload unsigned integer data. Memory will be ready to used by a CPU
 * class coded for the homework 3, and both will be inside a computer object
 * along side with a CPU program to simulate a computer
 *
 * This class coded for the homework 4 of GTU's CSE241 lecture, Fall 2016
 * It is now being re-used for homework 5
 * File belongs to Deniz Can Erdem Yılmaz - 151044001
 * 
 * Initial date    - ??.11.2016
 * Completion date - 15.11.2016
 * Dead-line       - 15.11.2016 / 23:55
 */



/* Using ifndef to prevent redefinitions */
#ifndef _MEMORY_H__
#define _MEMORY_H__

using namespace std;



/* Constant variables to prevent using define */
const int MEM_COUNT = 50;



class Memory{
public:
	Memory(int displayMode); //Constructor with 1 parameter
	Memory();                //Constructor without parameters
	
	/* Print function */
	void printAll() const;
	
	/* Mode setter/getters */
	void setMode(int display) {mode = display;}
	int getMode() const {return mode;}
	
	/* Memory setter/getters */
	void setMem(int index, unsigned int data) {memories[index] = data;}
	unsigned int getMem(int index) const {return memories[index];}

private:
	/* Unrelated to memory class functions hidden into private section */
	int strToInt(const string str) const;
	
	/* Data variables */
	unsigned int memories[MEM_COUNT];
	int mode;
};

#endif

/* End of Memory.h */
