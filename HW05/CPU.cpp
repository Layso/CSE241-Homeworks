/*
 * CPU.cpp
 * Contains CPU class function implementations
 * 
 * This class simulates a CPU which has 5 registers and program counter. It
 * has a instruction set inside it to call appropriate functions while 
 * processing a program
 *
 * This class coded for the homework 3 of GTU's CSE241 lecture, Fall 2016
 * It is now being re-used for homework 5
 * File belongs to Deniz Can Erdem Yılmaz - 151044001
 * 
 * Initial date    - ??.11.2016
 * Completion date - 15.11.2016
 * Dead-line       - 15.11.2016 / 23:55
 */



/* Include(s) */
#include <string>
#include <iostream>
#include "CPU.h"
#include "Memory.h"
using namespace std;



/* Instruction set of CPU */
const string ADD = "ADD";
const string SUB = "SUB";
const string JMP = "JMP";
const string JPN = "JPN";
const string MOV = "MOV";
const string PRN = "PRN";
const string HLT = "HLT";



CPU :: CPU(int displayMode)
{
	/* Setting program counter to 1, mode to given parameter and all */
	/* all registers to 0 on initialize of class object */
	setPc(1);
	setMode(displayMode);
	for (int i=0; i<NUM_OF_REG; i++)
		setReg(i, 0);
	halt = false;
}



/* Setting display mode 0 as default if it doesn't given */
CPU :: CPU() : CPU(0)
{/* Intentionally blank */}



void CPU :: print() const
{
	/* Formatting output and printing all registers to the screen as well */
	/* as the program counter */
	cout << "CPU Register Values:" << endl;
	for (int i=0; i<NUM_OF_REG; i++)
		cout << "[" << i+1 << "] -> " << getReg(i) << "     ";
	
	cout << endl << endl;
	cout << "Program counter: " << getPc()-1 << endl << endl << endl;
}



void CPU :: execute(const string line, Memory& mem)
{
	string instruction, param1, param2;
	int counter;
	
	
	/* Parsing line to instruction and parameters */
	instruction = getInstruction(line);
	param1 = getFirstParam(line);
	param2 = getSecondParam(line);
	
	/* Comparing instructions taken from file with CPU insctruction set */
	/* to call appropriate execute function */
	if (instruction == ADD)
		addExecute(param1, param2, mem);
	
	else if (instruction == SUB)
		subExecute(param1, param2, mem);
	
	else if (instruction == MOV)
		movExecute(param1, param2, mem);
	
	else if (instruction == JMP)
		jmpExecute(param1, param2);
		
	else if (instruction == JPN)
		jpnExecute(param1, param2);
	
	else if (instruction == PRN)
		prnExecute(param1, mem);
	
	else if (instruction == HLT)
		hltExecute(mem);
	
	/* Increasing program counter after each step */
	counter = getPc();
	setPc(counter+1);
	
	/* Printing memory and register depending on option */
	if (!halted())
		switch (getMode())
		{
			case 2: cout << endl; mem.printAll();
			case 1: cout << endl; print();
			case 0: break;
		}
	
	
	return;
}



void CPU :: addExecute(const string param1, const string param2, Memory& mem)
{
	int reg1, reg2, result, memo, reg, first, second;
	bool cons;
	
	
	/* Parameter type checks */
	memo = isMemory(param2);
	cons = isConstant(param2);
	reg = isRegister(param2);
	
	
	/* Taking the first value of target register */
	first = getReg(regToInt(param1));
	
	/* Making type checks and processing add instruction depends on param2 */
	if (cons)
	{
		second = strToInt(param2);
	}
	
	else if (reg)
	{
		second = getReg(regToInt(param2));
	}
	
	else if (memo)
	{
		second = mem.getMem(memToInt(param2));
	}
	
	/* Setting the last value of target register */
	setReg(regToInt(param1), first+second);
	
	/* Printing instruction if mode is 1 or 2 */
	if (getMode() == 1 || getMode() == 2)
		cout << ADD << " " << param1 << ", " << param2;
	
	
	return;
}



void CPU :: subExecute(const string param1, const string param2, Memory& mem)
{
	int reg1, reg2, result, memo, reg, first, second;
	bool cons;
	
	
	/* Parameter type checks */
	memo = isMemory(param2);
	cons = isConstant(param2);
	reg = isRegister(param2);
	
	
	/* Taking the first value of target register */
	first = getReg(regToInt(param1));
	
	/* Making type checks and processing sub instruction depends on param2 */
	if (cons)
		second = strToInt(param2);
	
	else if (reg)
		second = getReg(regToInt(param2));
	
	else if (memo)
		second = mem.getMem(memToInt(param2));
	
	/* Setting the last value of targe register */
	setReg(regToInt(param1), first-second);
	
	/* Printing instruction if mode is 1 or 2 */
	if (getMode() == 1 || getMode() == 2)
		cout << SUB << " " << param1 << ", " << param2;
	
	
	return;
}



void CPU :: movExecute(const string param1, const string param2, Memory& mem)
{
	int reg1, reg2, result, memo, reg, data;
	bool cons;
	
	
	/* Parameter type checks */
	memo = isMemory(param1);
	reg = isRegister(param1);
	
	
	if (memo)
	{
		reg = isRegister(param2);
		cons = isConstant(param2);
		
		if (reg)
		{
			data = mem.getMem(memToInt(param1));
			setReg(regToInt(param2), data);
		}
		
		else if (cons)
		{
			data = strToInt(param2);
			mem.setMem(memToInt(param1), data);
		}
	}
	
	else if (reg)
	{
		reg = isRegister(param2);
		cons = isConstant(param2);
		memo = isMemory(param2);
		
		if (reg)
		{
			data = getReg(regToInt(param1));
			setReg(regToInt(param2), data);
		}
		
		else if (cons)
		{
			data = strToInt(param2);
			setReg(regToInt(param1), data);
		}
		
		else if (memo)
		{
			data = getReg(regToInt(param1));
			mem.setMem(memToInt(param2), data);
		}
	}
	
	
	/* Printing instruction if mode is 1 or 2 */
	if (getMode() == 1 || getMode() == 2)
		cout << MOV << " " << param1 << "," << param2;
	
	
	return;
}



void CPU :: jmpExecute(const string param1, const string param2)
{
	int reg1;
	bool cons;
	
	
	/* Parameter type checks */
	cons = isConstant(param1);
	reg1 = regToInt(param1);
	
	/* First param of jmp must be a register or a constant. If it is a  */
	/* register then second param must be constant. Else it must be empty */
	if (cons)
	{
		setPc(strToInt(param1)-1);
		
		/* Printing instruction if mode is 1 or 2 */
		if (getMode() == 1 || getMode() == 2)
			cout << JMP << " " << param1;
	}
	
	else
	{
		if (getReg(reg1) == 0)
			setPc(strToInt(param2)-1);
		
		/* Printing instruction if mode is 1 or 2 */
		if (getMode() == 1 || getMode() == 2)
			cout << JMP << " " << param1 << ", " << param2;
	}
	
	
	return;
}



void CPU :: jpnExecute(const string param1, const string param2)
{
	int reg1;
	bool cons;
	
	
	/* Parameter type checks */
	cons = isConstant(param1);
	reg1 = regToInt(param1);
	
	/* Jumping to indicated line if given register is lesser or equal than 0 */
	if (getReg(reg1) <= 0)
		setPc(strToInt(param2)-1);
	
	/* Printing instruction if mode is 1 or 2 */
	if (getMode() == 1 || getMode() == 2)
		cout << JPN << " " << param1 << ", " << param2;
	
	
	return;
}



void CPU :: prnExecute(const string param1, Memory& mem)
{
	int reg, memo;
	bool cons;
	
	
	cons = isConstant(param1);
	reg = isRegister(param1);
	memo = isMemory(param1);
	
	
	/* Formatting output for both display option and print instruction */
	if (getMode() == 1 || getMode() == 2)
		cout << PRN << " " << param1 << " : ";
	
	if (cons)
		cout << strToInt(param1);
	
	else if (reg)
		cout << getReg(regToInt(param1));
	
	else if (memo)
		cout << mem.getMem(memToInt(param1));
	
	if (getMode() == 0)
		cout << endl;
	
	
	return;
}



void CPU :: hltExecute(Memory& mem)
{
	if (getMode() == 1 || getMode() == 2)
		cout << HLT;
	
	/* Increasing program counter one more time to print correct PC */
	setPc(getPc()+1);
	

	cout << endl;
	mem.printAll();
	
	cout << endl;
	print();

	
	/* Information message before turn off */
	cout << "Program halted without any errors" << endl;
	setHalt();
	
	
	return;
}



string CPU :: getInstruction(const string line) const
{
	string ins;
	int i;
	
	
	/* Finding the index of whitespace */
	for (i=0; line[i]!=' '; i++)
	; 
	
	/* Taking instruction part of the line */
	ins = line.substr(0, i);
	
	
	return (ins);
}



string CPU :: getFirstParam(const string line) const
{
	string param;
	int i, j;
	bool comma=false;
	
	
	/* Looking for comma to figure the number of parameters */
	for (i=0; line[i]!='\0'; i++)
		if (line[i] == ',')
			comma = true;
	
	if (comma)
	{
		/* Finding the index of comma */
		for (i=0; line[i]!=','; i++)
			if (line[i] == ' ')
				j=i;
		
		/* Taking sub string from whitespace to comma */
		param = line.substr(j+1,i-j-1);
	}
	
	else
	{
		/* Finding the second whitespace */
		for (i=0; line[i]!='\0'; i++)
			if (line[i] == ' ')
				j=i;
		
		for (i=0; line[i]!=' '; i++)
		; /* Finding the first whitespace */
		
		/* Taking sub string from whitespace to whitespace */
		param = line.substr(i+1,j-i-1);
	}
	
	
	return (param);
}



string CPU :: getSecondParam(const string line) const
{
	string param;
	int i, j;
	bool comma=false;
	
	
	for (i=0; line[i]!='\0'; i++)
		if (line[i] == ',')
			comma = true;
	
	if (comma)
	{
		/* Finding the second whitespace */
		for (i=0; line[i]!='\0'; i++)
			if (line[i] == ' ')
				j=i;
		
		for (i=0; line[i]!=','; i++)
		; /* Finding the comma */
		
		/* Taking second param from line */
		param = line.substr(i+1,j-i-1);
	}
	
	else
	{
		/* Finding the second whitespace */
		for (i=0; line[i]!='\0'; i++)
			if (line[i] == ' ')
				j=i;
		
		for (i=0; line[i]!='\0'; i++)
		; /* Finding the end of line */
		
		/* Taking second param from line */
		param = line.substr(j+1,i-j-1);
	}
	
	
	return (param);
}



int CPU :: isMemory(const string parameter) const
{
	bool constant;
	int length, address, retVal;
	string temp;
	
	
	/* Checking if there is address sign */
	if (parameter[0] == '#')
	{
		/* Creating a temp string to erase sign */
		temp = parameter;
		temp.erase(0,1);
		
		/* Converting string to integer to check validness */
		address = strToInt(temp);
		constant = isConstant(temp);
		
		/* If given param is a number check the range of addresses */
		if (constant)
			/* If valid return true flag */
			if (address >= 0 && address <= MEM_COUNT-1)
				retVal = 1;
			
			/* If number is out of range return segmentation flag */
			else
				retVal = 2;
		
		/* Else return not valid flag */
		else
			retVal = 0;
	}
		
	else
		retVal = 0;
	
	
	return (retVal);
}



int CPU :: isRegister(const string param) const
{
	int retVal, length;
	
	
	/* Taking length of string */
	length = param.length();
	
	/* First character of param must be 'R' */
	if (param[0] == 'R')
		/* It must be 2 characters long and second parameter must be in */
		/* between 1 and 5 for a valid register */
		if ((length > 2) || ((param[1] < '1') || (param[1] > '5')))
			retVal = 2;
		
		/* Else return 1 to indicate param is a valid register */
		else
			retVal = 1;
	
	/* Else return 0 to indicate param is not a register */	
	else
		retVal = 0;
	
	
	return (retVal);
}



bool CPU :: isConstant(const string param) const
{
	int length;
	bool retVal=true;
	
	
	/* Taking length of string */
	length = param.length();
	
	if (length == 0)
		retVal = false;
	
	/* Searching if there is any characters out of range */
	for (int i=0; i<length; ++i)
		if ((param[i] < '0') || (param[i] > '9'))
			if (!((param[i] == '-') && (i == 0)))
				retVal = false;
	
	
	return (retVal);
}



int CPU :: memToInt(const string parameter) const
{
	int length, val=1, sum=0;
	const int cons = 10, ZERO_ASCII = 48;
	string temp=parameter;
	
	
	/* Erasing the memory indicator character */
	temp.erase(0,1);
	length = temp.length();
	
	/* Multiplying each digit with its base value */
	for (int i=length-1; i>=0; i--)
	{
		sum += ((temp[i] - ZERO_ASCII) * val);
		val *= cons;
	}
		
	
	return (sum);
}



int CPU :: regToInt(const string param) const
{
	int reg;
	const int ZERO_ASCII = 48;
	
	
	/* Finding the index equavellent of register number */
	reg = param[1] - ZERO_ASCII - 1;
	
	
	return reg;
}



int CPU :: strToInt(const string str) const
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

/* End of CPU.cpp */
