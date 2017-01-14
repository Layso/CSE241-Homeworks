/*
 * CPUProgramDyn.h is the header file of CPUProgramDyn.cpp
 * Contains CPU Program class prototype
 * 
 * This class simulates a CPU helper. Objects are obligated to read
 * a CPU program from a text file. It uses dynamically allocated memory for its
 * array.
 *
 * This class coded for the homework 3 of GTU's CSE241 lecture as CPUProgram
 * class, Fall 2016
 * It is now being re-used for homework 6 with minor changes
 * File belongs to Deniz Can Erdem Yılmaz - 151044001
 * 
 * Initial date    - 29.11.2016
 * Completion date - 02.12.2016
 * Dead-line       - 30.11.2016 / 23:55
 */



/* Using ifndef to prevent redefinitions */
#ifndef _CPUPROGRAMDYN_H__
#define _CPUPROGRAMDYN_H__

#include <vector>
using namespace std;


namespace mySpace
{
	class CPUProgramDyn
	{
	public:
		CPUProgramDyn();							//Constructor without parameters
		CPUProgramDyn(int option);					//Constructor with int parameter
		CPUProgramDyn(const CPUProgramDyn& other);	//Copy constructor
		~CPUProgramDyn();							//Destructor
	
	
		/* Functions to process file and return lines */
		void ReadFile(const char *fileName);
		string getLine(int lineNumber) const {return (lines[lineNumber]);}
	
		/* count setter/getter */
		void setCount(int newCount) {count = newCount;}
		int size() const {return count;}
	
		/* Capacity getter */
		int getCap() const {return maxCount;}
	
		/* errorFlag setter/getter */
		void setFlag() {errorFlag = false;}
		bool getFlag() const {return (errorFlag);}
		    
		/* Mode setter/getter */
		void setMode(int display) {mode = display;}
		int getMode() const {return mode;}
	
		/* File name getter */
		string getFName() const {return fileParameter;}
	
	
		/* Opeartor overloads */
		string operator[] (int lineNumber) const;
		const CPUProgramDyn& operator = (const CPUProgramDyn& other);
		const CPUProgramDyn operator + (const string line) const;
		const CPUProgramDyn operator + (const CPUProgramDyn& other) const;
		const CPUProgramDyn& operator += (const string line);
		bool operator == (const CPUProgramDyn& other) const;
		bool operator != (const CPUProgramDyn& other) const;
		bool operator > (const CPUProgramDyn& other) const;
		bool operator < (const CPUProgramDyn& other) const;
		bool operator >= (const CPUProgramDyn& other) const;
		bool operator <= (const CPUProgramDyn& other) const;
		void operator -- ();
		void operator -- (int);
		const CPUProgramDyn operator () (int top, int end) const;
		friend ostream& operator << (ostream& out, const CPUProgramDyn& obj);
	private:
		/* Functions to process file and lines */
		void fileOpener(const char *fileName);
		void formatEditor();
		void addLine(const string line);
		void deleteLine();
	
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
	
		/* Data variables of CPUProgramDyn class */
		string *lines;
		string fileParameter;
		int count;
		int maxCount;
		bool errorFlag;
		int mode;
	};



	ostream& operator << (ostream& out, const CPUProgramDyn& obj);
}


#endif

/* End of CPUProgramDyn.h */
