/*
 * Memory.cpp
 * Contains Memory class function implementations
 *
 * This class simulates a set of memory (50 cells) which are able to load and
 * unload unsigned integer data. Memory will be ready to used by a CPU
 * class coded for the homework 3, and both will be inside a computer object
 * along side with a CPU program to simulate a computer
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
#include "Memory.h"
using namespace std;



Memory :: Memory(int displayMode)
{
	setMode(displayMode=0);
	
	/* Setting all memory cells 0 as their initial value */
	for (int i=0; i<MEM_COUNT; i++)
		setMem(i, 0);
}



/* Setting display mode 0 as default if it doesn't given */
Memory :: Memory() : Memory(0)
{/* Intentionally blank */}



void Memory :: printAll() const
{
	cout << "Memory values:" << endl;
	/* Formatting the output and printing all memory cells */
	for (int i=0; i<MEM_COUNT; i++)
	{
		cout << "[" << i << "] -> " << getMem(i) << " ";
		
		if (i%10 == 9)
			cout << endl;
	}
}



int Memory :: strToInt(const string str) const
{
	int length, val=1, sum=0;
	const int cons = 10, ZERO_ASCII = 48;
	string temp=str;
	bool negative = false;
	
	
	/* Checking if constant is negative and shortening length */
	if (str[0] == '-')
	{
		temp.erase(0,1);
		negative = true;
	}
	
	
	length = temp.length();
	
	/* Multiplying each digit with its base value */
	for (int i=length-1; i>=0; i--)
	{
		sum += ((temp[i] - ZERO_ASCII) * val);
		val *= cons;
	}
	
	if (negative)
		sum = -sum;
	
	
	return (sum);
}

/* End of Memory.cpp */
