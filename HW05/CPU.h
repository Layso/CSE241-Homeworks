/*
 * CPU.h is the header file of CPU.cpp
 * Contains CPU class prototype
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
 
 

/* Using ifndef to prevent redefinitions */
#ifndef _CPU_H__
#define _CPU_H__

#include "Memory.h"
using namespace std;



/* Constant int number instead of define */
const int NUM_OF_REG = 5;



class CPU
{
public:
	CPU(int displayMode); //Constructor with int parameter
	CPU();                //Constructor without parameters
	
	/* Main CPU functions */
	void print() const;
	void execute(const string line, Memory& mem);
	
	/* Halt flag setter/getter */
	void setHalt() {halt = true;}
	bool halted() const {return halt;}
	
	/* Program counter setter/getter */
	void setPc(const int pc) {programCounter = pc;}
	int getPc() const {return programCounter;}
	
	/* Mode setter/getter */
	void setMode(const int display) {mode = display;}
	int getMode() const {return mode;}
	
	/* Register setter/getter */
	void setReg(const int reg, const int value) {registers[reg] = value;}
	int getReg(const int reg) const {return registers[reg];}

private:
	/* Instruction functions */
	void addExecute(const string param1, const string param2, Memory& mem);
	void subExecute(const string param1, const string param2, Memory& mem);
	void movExecute(const string param1, const string param2, Memory& mem);
	void jpnExecute(const string param1, const string param2);
	void jmpExecute(const string param1, const string param2);
	void prnExecute(const string param1, Memory& mem);
	void hltExecute(Memory& mem);
	
	/* Line parser functions */
	string getInstruction(const string line) const;
	string getFirstParam(const string line) const;
	string getSecondParam(const string line) const;
	
	/* Helper functions for converting and controlling */
	int isMemory(const string parameter) const;
	int isRegister(const string param) const;
	bool isConstant(const string param) const;
	int memToInt(const string parameter) const;
	int regToInt(const string param) const;
	int strToInt(const string str) const;
	
	/* Class variables */
	bool halt;
	int mode;
	int registers[NUM_OF_REG];
	int programCounter;
};

#endif

/* End of CPU.h */
