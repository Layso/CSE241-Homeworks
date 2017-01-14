/*
 * cpuProgram.h is the header file of cpuProgram.cpp
 * Contains cpuProgram class prototype
 * This class simulates a CPU helper. Objects are obligated to read
 * a CPU program from a text file. Upon declaration, a constructor
 * will be called to open file, read lines and check for errors.
 *
 * This class coded for the homework 3 of GTU's CSE241 lecture, Fall 2016
 * File belongs to Deniz Can Erdem Yılmaz - 151044001
 * 27/10/2016
 */



/* Using ifndef to prevent redefinitions */
#ifndef _CPUPROGRAM_H__
#define _CPUPROGRAM_H__

using namespace std;



/* Maximum lines CPU can read from program file */
const int MAX_LINE_COUNT = 200;



class cpuProgram
{
public:
	cpuProgram(char *fileName); //Constructor with 1 parameter
	cpuProgram();               //Constructor without parameter
	
	/* Functions to process file and return lines */
	void readFile(char *fileName);
	string getLine(int lineNumber) {return (lines[lineNumber-1]);}
	
	/* lineCount setter/getter */
	void setLineCount(int count) {lineCount = count;}
	int size() {return lineCount;}
	
	/* errorFlag setter/getter */
	void setFlag() {errorFlag = false;}
	bool getFlag() {return (errorFlag);}
	
	
private:
	/* Functions to process file and lines */
	void fileOpener(char *fileName);
	void formatEditor();
	
	/* Error checker functions */
	void syntaxCheck();
	void addSyntaxCheck(const string line, const int lineNumber);
	void subSyntaxCheck(const string line, const int lineNumber);
	void movSyntaxCheck(const string line, const int lineNumber);
	void jmpSyntaxCheck(const string line, const int lineNumber);
	void prnSyntaxCheck(const string line, const int lineNumber);
	void hltSyntaxCheck(const string line, const int lineNumber);
	
	/* Helper functions to parse lines */
	string getInstruction(const string line);
	string getFirstParam(const string line, const int lineNumber);
	string getSecondParam(const string line, const int lineNumber);
	
	/* Other helper functions that doesn't have relation with this class but */
	/* hided in private section to fulfill the requirements of information */
	/* hiding */
	bool isConstant(const string param);
	int isRegister(const string param);
	int strToInt(const string str);
	
	/* Data variables of cpuProgram class */
	char *fileParameter;
	string lines[MAX_LINE_COUNT];
	int lineCount;
	bool errorFlag;
};

#endif

/* End of cpuProgram.h */
