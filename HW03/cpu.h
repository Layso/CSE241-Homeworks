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
 
 

/* Using ifndef to prevent redefinitions */
#ifndef _CPU_H__
#define _CPU_H__

using namespace std;



/* Constant int number instead of define */
const int NUM_OF_REG = 5;



class cpu
{
public:
	cpu(char *displayMode); //Constructor with 1 parameter
	cpu();                  //Constructor without parameter
	
	/* Main CPU functions */
	void print();
	void execute(string line);
	
	/* Halt flag setter/getter */
	void setHalt() {halt = true;}
	bool halted() {return halt;}
	
	/* Program counter setter/getter */
	void setPc(int pc) {programCounter = pc;}
	int getPc() {return programCounter;}
	
	/* Mode setter/getter */
	void setMode(int display) {mode = display;}
	int getMode() {return mode;}
	
	/* Register setter/getter */
	void setReg(int reg, int value) {registers[reg] = value;}
	int getReg(int reg) {return registers[reg];}
private:
	/* Instruction functions */
	void addExecute(string param1, string param2);
	void subExecute(string param1, string param2);
	void movExecute(string param1, string param2);
	void jmpExecute(string param1, string param2);
	void prnExecute(string param1);
	void hltExecute();
	
	/* Line parser functions */
	string getInstruction(string line);
	string getFirstParam(string line);
	string getSecondParam(string line);
	
	/* Not so related but needed functions that hided inside private block */
	bool isConstant(const string param);
	int regToInt(const string param);
	int strToInt(const string str);
	
	/* Class variables */
	bool halt;
	int mode;
	int registers[NUM_OF_REG];
	int programCounter;
};

#endif

/* End of cpu.h */
