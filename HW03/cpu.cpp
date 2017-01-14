/*
 * cpu.h is the header file of cpu.cpp
 * Contains cpu class prototype
 * This class simulates a CPU which has 5 registers and nothing else. It
 * has a instruction set inside it to call propriate functions while processing
 * a cpu program
 *
 * This class coded for the homework 3 of GTU's CSE241 lecture, Fall 2016
 * File belongs to Deniz Can Erdem Yılmaz - 151044001
 * 27/10/2016
 */



/* Include(s) */
#include <string>
#include <iostream>
#include "cpu.h"

using namespace std;



/* Constant int variables instead of define(s) */
const int ZERO_ASCII = 48;
const string ADD = "ADD";
const string SUB = "SUB";
const string JMP = "JMP";
const string MOV = "MOV";
const string PRN = "PRN";
const string HLT = "HLT";



cpu :: cpu(char *displayMode)
{
	/* Setting program counter to 1, mode to given parameter and all */
	/* all registers to 0 on initialize of class object */
	setPc(1);
	setMode(strToInt(displayMode));
	for (int i=0; i<NUM_OF_REG; i++)
		setReg(i, 0);
}



cpu :: cpu()
{
	/* If mode parameter was not given, set it to 0 as default option */
	setPc(1);
	setMode(0);
	for (int i=0; i<NUM_OF_REG; i++)
		setReg(i, 0);
}



void cpu :: print()
{
	/* Formatting output and printing all registers to the screen */
	for (int i=0; i<NUM_OF_REG; i++)
		cout << "R" << i+1 << " = " << getReg(i) << " ";
			
	cout << endl;
	cout << "Program counter: " << getPc() << endl;
	return;
}



void cpu :: execute(string line)
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
		addExecute(param1, param2);
	
	else if (instruction == SUB)
		subExecute(param1, param2);
	
	else if (instruction == MOV)
		movExecute(param1, param2);
	
	else if (instruction == JMP)
		jmpExecute(param1, param2);
	
	else if (instruction == PRN)
		prnExecute(param1);
	
	else if (instruction == HLT)
		hltExecute();
	
	if (getMode() == 1 && !halted())
	{
		cout << endl;
		print();
		cout << endl;
	}
	
	
	/* Increasing program counter after each step */
	counter = getPc();
	setPc(counter+1);
	
	
	return;
}



void cpu :: addExecute(string param1, string param2)
{
	int reg1, reg2, result;
	bool cons;
	
	
	/* Parameter type checks */
	cons = isConstant(param2);
	reg1 = regToInt(param1);
	reg2 = regToInt(param2);
	
	/* First param of add must be register. Second can be either register */
	/* or a constant number */
	if (cons)
		result = getReg(reg1) + strToInt(param2);
	
	else
		result = getReg(reg1) + getReg(reg2);
	
	setReg(reg1, result);
	
	/* Printing instruction if mode is 1 */
	if (getMode() == 1)
		cout << ADD << " " << param1 << ", " << param2;
	
	
	return;
}



void cpu :: subExecute(string param1, string param2)
{
	int reg1, reg2, result;
	bool cons;
	
	
	/* Parameter type checks */
	cons = isConstant(param2);
	reg1 = regToInt(param1);
	reg2 = regToInt(param2);
	
	/* First param of sub must be register. Second can be either register */
	/* or a constant number */
	if (cons)
		result = getReg(reg1) - strToInt(param2);
	
	else
		result = getReg(reg1) - getReg(reg2);
	
	setReg(reg1, result);
	
	/* Printing instruction if mode is 1 */
	if (getMode() == 1)
		cout << SUB << " " << param1 << ", " << param2;
	
	
	return;
}



void cpu :: movExecute(string param1, string param2)
{
	int reg1, reg2, result;
	bool cons;
	
	
	/* Parameter type checks */
	cons = isConstant(param2);
	reg1 = regToInt(param1);
	reg2 = regToInt(param2);
	
	/* First param of mov must be register. Second can be either register */
	/* or a constant number */
	if (cons)
		setReg(reg1,strToInt(param2));
	
	else
		setReg(reg2,getReg(reg1));
	
	/* Printing instruction if mode is 1 */
	if (getMode() == 1)
		cout << MOV << " " << param1 << ", " << param2;
	
	
	return;
}



void cpu :: jmpExecute(string param1, string param2)
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
		
		/* Printing instruction if mode is 1 */
		if (getMode() == 1)
			cout << JMP << " " << param1;
	}
	
	else
	{
		if (getReg(reg1) == 0)
			setPc(strToInt(param2)-1);
		
		/* Printing instruction if mode is 1 */
		if (getMode() == 1)
			cout << JMP << " " << param1 << ", " << param2;
	}
	
	
	return;
}



void cpu :: prnExecute(string param1)
{
	int reg;
	bool cons;
	
	
	cons = isConstant(param1);
	reg = regToInt(param1);
	/* Printing the given constant or register after formatting */
	if (getMode() == 1)
		cout << PRN << " " << param1 << " - ";
	
	if (cons)
		cout << strToInt(param1);
	
	else
		cout << getReg(reg);
	
	if (getMode() == 0)
	cout << endl;
	
	
	return;
}



void cpu :: hltExecute()
{
	cout << HLT << endl;
	for (int i=0; i<NUM_OF_REG; i++)
	{
		cout << "R" << i+1 << " = " << getReg(i);
		if (i+1 != NUM_OF_REG)
			cout << ", ";
	}
	
	/* Information message before turn off */
	cout << endl;
	cout << "Program halted without any errors" << endl;
	setHalt();
	
	
	return;
}



string cpu :: getInstruction(string line)
{
	string ins;
	int i;
	
	
	for (i=0; line[i]!=' '; i++)
	; /* Finding the index of whitespace */
	
	ins = line.substr(0, i);
	
	
	return (ins);
}



string cpu :: getFirstParam(string line)
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



string cpu :: getSecondParam(string line)
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
		
		param = line.substr(j+1,i-j-1);
	}
	
	
	return (param);
}



bool cpu :: isConstant(const string param)
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



int cpu :: regToInt(const string param)
{
	int reg;
	
	/* Finding the index equavellent of register number */
	reg = param[1] - ZERO_ASCII - 1;
	
	return reg;
}



int cpu :: strToInt(const string str)
{
	int length, val=1, sum=0;
	const int cons = 10;
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
