/*
 * CPUProgram.h is the header file of CPUProgram.cpp
 * Contains CPU class prototype
 * 
 * This class simulates a CPU helper. Objects are obligated to read
 * a CPU program from a text file. Upon declaration, a constructor
 * will be called to open file, read lines and check for errors.
 *
 * This class coded for the homework 3 of GTU's CSE241 lecture, Fall 2016
 * It is now being re-used for homework 5 with some minor changes and operator
 * overloads
 * File belongs to Deniz Can Erdem Yılmaz - 151044001
 * 
 * Initial date    - ??.11.2016
 * Completion date - 15.11.2016
 * Dead-line       - 15.11.2016 / 23:55
 */



/* Using ifndef to prevent redefinitions */
#ifndef _CPUPROGRAM_H__
#define _CPUPROGRAM_H__

#include <vector>
using namespace std;



/* Maximum lines CPU can read from program file */
const int MAX_LINE_COUNT = 200;



class CPUProgram
{
public:
	explicit CPUProgram(const char *fileName); //Constructor with char ptr parameter
	CPUProgram(int option);     //Constructor with int parameter
	CPUProgram();               //Constructor without parameters
	
	
	/* Functions to process file and return lines */
	void ReadFile(const char *fileName);
	string getLine(int lineNumber) const {return (lines[lineNumber]);}
	
	/* count setter/getter */
	void setCount(int newCount) {count = newCount;}
	int size() const {return count;}
	
	/* errorFlag setter/getter */
	void setFlag() {errorFlag = false;}
	bool getFlag() const {return (errorFlag);}
        
	/* Mode setter/getter */
	void setMode(int display) {mode = display;}
	int getMode() const {return mode;}
	
	
	/* Opeartor overloads */
	const string operator[] (int lineNumber) const;
	const CPUProgram operator + (const string line) const;
	const CPUProgram operator + (const CPUProgram& other) const;
	const CPUProgram& operator += (const string line);
	bool operator == (const CPUProgram& other) const;
	bool operator != (const CPUProgram& other) const;
	bool operator > (const CPUProgram& other) const;
	bool operator < (const CPUProgram& other) const;
	bool operator >= (const CPUProgram& other) const;
	bool operator <= (const CPUProgram& other) const;
	void operator -- ();
	void operator -- (int);
	const CPUProgram operator () (int top, int end) const;
	friend ostream& operator << (ostream& out, const CPUProgram& obj);
private:
	/* Functions to process file and lines */
	void fileOpener(const char *fileName);
	void formatEditor();
	
	/* Error checker functions */
	void syntaxCheck();
	void addSyntaxCheck(const string line, const int lineNumber);
	void subSyntaxCheck(const string line, const int lineNumber);
	void movSyntaxCheck(const string line, const int lineNumber);
	void jmpSyntaxCheck(const string line, const int lineNumber);
	void jpnSyntaxCheck(const string line, const int lineNumber);
	void prnSyntaxCheck(const string line, const int lineNumber);
	void hltSyntaxCheck(const string line, const int lineNumber);
	
	/* Helper functions to parse lines */
	string getInstruction(const string line);
	string getFirstParam(const string line, const int lineNumber);
	string getSecondParam(const string line, const int lineNumber);
	
	/* Other helper functions that doesn't have relation with this class */
	/* but hided in private section to fulfill the requirements of */
	/* information hiding */
	int isMemory(const string parameter) const;
	bool isConstant(const string param) const;
	int isRegister(const string param) const;
	int strToInt(const string str) const;
	
	/* Data variables of cpuProgram class */
	vector<string> lines;
	const char *fileParameter;
	int count;
	bool errorFlag;
	int mode;
};



ostream& operator << (ostream& out, const CPUProgram& obj);



#endif

/* End of CPUProgram.h */
