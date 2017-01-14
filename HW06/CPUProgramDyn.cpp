/*
 * CPUProgramDyn.cpp
 * Contains CPUProgramDyn class function implementations 
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
 
 

/* Include(s) */
#include <string>
#include <fstream>
#include <iostream>
#include "CPUProgramDyn.h"
using namespace std;


namespace mySpace
{
	/* Constant int variables instead of defines */
	const int MEM_COUNT = 50;

	/* Instruction set of CPU */
	const string ADD = "ADD";
	const string SUB = "SUB";
	const string MOV = "MOV";
	const string JMP = "JMP";
	const string JPN = "JPN";
	const string PRN = "PRN";
	const string HLT = "HLT";



	/* Setting display mode 0 as default if it doesn't given */
	CPUProgramDyn :: CPUProgramDyn() : CPUProgramDyn(0)
	{/* Intentionally blank */}



	CPUProgramDyn :: CPUProgramDyn(int option) :
	count(0), maxCount(1), mode(option), errorFlag(true), fileParameter("")
	{
		/* Setting all data to their initial values */
		lines = new string[maxCount];
	}



	CPUProgramDyn :: CPUProgramDyn(const CPUProgramDyn& other) :
	count(other.size()), maxCount(other.getCap()), mode(other.getMode()),
	errorFlag(other.getFlag()), fileParameter(other.getFName())
	{
		/* Setting all data to other objects data */
		lines = new string[other.getCap()];
		for (int i=0; i<size(); i++)
			lines[i] = other[i];
	}



	CPUProgramDyn :: ~CPUProgramDyn()
	{
		/* Deallocating memory taken from heap */
		delete [] lines;
	}



	void CPUProgramDyn :: addLine(const string line)
	{
		/* Checking if size reached to capacity */
		if (size() == getCap())
		{
			/* Allocating new memory if size reached to capacity */
			maxCount *= 2;
			string* newArray = new string[maxCount];
			/* Backing up old list */
			for (int i=0; i<size(); i++)
				newArray[i] = lines[i];
			/* Deleting old list */
			delete[] lines;
			/* Assigning backup as new list with higher capacity */
			lines = newArray;
		}
	
		/* Inserting line to line list */
		lines[size()] = line;
		setCount(size()+1);
	}



	void CPUProgramDyn :: deleteLine()
	{
		/* Simply decreasing size to make last element unreachable */
		setCount(size()-1);
	}



	const CPUProgramDyn& CPUProgramDyn :: operator = (const CPUProgramDyn& other)
	{
		/* Checking if other equals to this */
		if (this != &other)
		{
			/* Assigning each data from other to this */
			fileParameter = other.getFName();
			count = other.size();
			maxCount = other.getCap();
			errorFlag = other.getFlag();
			mode = getMode();
			
			/* Allocating space from memory for line array */
			lines = new string[getCap()];
			for (int i=0; i<size(); i++)
				lines[i] = other[i];
		}
		
		/* Returning this */
		return *this;
	}



	string CPUProgramDyn :: operator [] (int lineNumber) const
	{
		/* Checking index errors */
		if (lineNumber<0 || lineNumber>size()-1 || size()==0)
		{
			cerr << "Invalid index number for '[]' operator: 'CPUProgramDyn["
				 << lineNumber << "]'" << endl;
			//exit(1);
		
			return "";
		}
	
		/* Returning wanted line */
		return (lines[lineNumber]);
	}



	const CPUProgramDyn CPUProgramDyn :: operator + (const string line) const
	{
		CPUProgramDyn newProgram;
	
		/* Checking input errors */
		if (line == "")
		{
			cerr << "Invalid input for '+' operator: '" + line + "'" << endl;
			//exit(1);
		}
	
		else
		{
			/* Assigning old program and new line to new program */
			newProgram = *this;
			newProgram.addLine(line);
		}
	
		
		/* Returning new program */
		return newProgram;
	}



	const CPUProgramDyn CPUProgramDyn :: operator + (const CPUProgramDyn& other) const
	{
		/* Creating a new program same as this */
		CPUProgramDyn newProgram(*this);
	
		/* Adding other program's strings to new program */
		for (int i=0; i<other.size(); i++)
		{
			newProgram = newProgram + other[i];
		}
	
	
		/* Returnin new program */
		return newProgram;
	}



	const CPUProgramDyn& CPUProgramDyn :: operator += (const string line)
	{
		/* Seperating + and = operators */
		*this = *this + line;
	
		/* Returning this */
		return *this;
	}



	const CPUProgramDyn CPUProgramDyn :: operator () (int top, int end) const
	{
		/* Assigning data variables to the new program */
		CPUProgramDyn newProgram;
		newProgram.fileParameter = this->fileParameter;
		newProgram.errorFlag = this->errorFlag;
		newProgram.mode = this->mode;
	
		/* Checking index errors */
		if (top>end || end>size() || end<0 || top<0)
		{
			cerr << "Invalid index number for '()' operator: 'CPUProgramDyn(" << top
				 << ", " << end << ")'" << endl;
			//exit(1);
		
			return newProgram;
		}
	
		/* Taking section between given indexes */
		for (int i=top; i<=end; i++)
		{
			newProgram = newProgram + (*this)[i];
		}
	
	
		/* Returning new program */
		return newProgram;
	}



	bool CPUProgramDyn :: operator == (const CPUProgramDyn& other) const
	{
		return (size() == other.size());
	}



	bool CPUProgramDyn :: operator != (const CPUProgramDyn& other) const
	{
		return !(*this==other);
	}



	bool CPUProgramDyn :: operator > (const CPUProgramDyn& other) const
	{
		return (size() > other.size());
	}



	bool CPUProgramDyn :: operator < (const CPUProgramDyn& other) const
	{
		return (size() < other.size());
	}



	bool CPUProgramDyn :: operator >= (const CPUProgramDyn& other) const
	{
		return !(*this < other);
	}



	bool CPUProgramDyn :: operator <= (const CPUProgramDyn& other) const
	{
		return !(*this > other);
	}



	void CPUProgramDyn :: operator -- ()
	{
		this->deleteLine();
	}



	void CPUProgramDyn :: operator -- (int)
	{
		--(*this);
	}



	ostream& operator << (ostream& out, const CPUProgramDyn& obj)
	{
		for (int i=0; i<obj.size(); i++)
			cout << obj[i] << endl;
	
	
		return out;
	}



	void CPUProgramDyn :: ReadFile(const char *fileName)
	{
		/* Changing the fileParameter in case object initialized without */
		/* parameters or with only option */
		string str(fileName);
		fileParameter = fileName;
	
	
		/* Calling appropriate functions for loading instructions, formatting */
		/* lines and error checks */
		if (getFlag())
			fileOpener(fileName);
	
		if (getFlag())
			formatEditor();
	
		if (getFlag())
			syntaxCheck();
	}



	void CPUProgramDyn :: fileOpener(const char *fileName)
	{
		int i=0;
		ifstream file;
		string line;
	
	
		file.open(fileName);
	
		/* Printing error and changing flag if file doesn't exist */
		if (file == NULL)
		{
			if (fileName != "")
				cerr << fileParameter << ": " << endl
					 << "File error: Given file couldn't found in directory" <<endl;
		
			else
				cerr << "(blank)" << ": " << endl
					 << "File error: Given file couldn't found in directory" <<endl; 
		
			setFlag();
		}
	
		/* Else take lines to an array, close the file and set line count */
		else
			while (getline(file, line))
			{
				addLine(line);
			}
	
		/* End of file process */
		file.close();
	
	
		return;
	}



	void CPUProgramDyn :: syntaxCheck()
	{
		string instruction;
		int totalLines, currentLine=0;
		bool halt=false;
	
	
		totalLines = size();
		/* Creating a loop to check every line */
		while (currentLine<totalLines)
		{
			instruction = getInstruction(getLine(currentLine));
			/* Comparing instructions taken from file with CPU insctruction set */
			/* to find if there is any error on that line */
			if (instruction == ADD)
				addSyntaxCheck(getLine(currentLine), currentLine);
		
			else if (instruction == SUB)
				subSyntaxCheck(getLine(currentLine), currentLine);
		
			else if (instruction == MOV)
				movSyntaxCheck(getLine(currentLine), currentLine);
		
			else if (instruction == JMP)
				jmpSyntaxCheck(getLine(currentLine), currentLine);
		
			else if (instruction == JPN)
				jpnSyntaxCheck(getLine(currentLine), currentLine);
		
			else if (instruction == PRN)
				prnSyntaxCheck(getLine(currentLine), currentLine);
		
			else if (instruction == HLT)
			{
				hltSyntaxCheck(getLine(currentLine), currentLine);
				halt = true;
			}
		
			else
			{
				cerr << fileParameter << ": line: " << currentLine+1 << endl
					 << "Syntax error: Undefined instruction: " << instruction
					 << endl;
			
				setFlag();
			}
		
			currentLine++;
		}
	
		/* Also checking if CPU program has HLT command to terminate process */
		if (!halt)
		{
			cerr << fileParameter << ": " << endl
				 << "Termination error: HLT instruction couldn't found in file"
				 << endl;
		
			setFlag();
		}
	
	
		return;
	}



	void CPUProgramDyn :: addSyntaxCheck(string line, int lineNumber)
	{
		string param1, param2;
		bool con;
		int reg, mem;
	
	
		param1 = getFirstParam(line, lineNumber);
		param2 = getSecondParam(line, lineNumber);
		reg = isRegister(param1);
	
		/* ADD instruction can have (register-register), (register-memory) or */
		/* (register-constant) parameter sets */
		if (reg == 2)
		{
			cerr << fileParameter << ": line: " << lineNumber+1 << endl
				 << "Segmentation error: Register is out of range: " << param1 
				 << endl;
			
			setFlag();
		}
	
		else if (reg == 0)
		{
			cerr << fileParameter << ": line: " << lineNumber+1 << endl
				 << "Syntax error: First parameter of ADD instruction must be " 
				 << "register: " << param1 << endl;
			
			setFlag();
		}
	
		else
		{
			con = isConstant(param2);
			reg = isRegister(param2);
			mem = isMemory(param2);
		
			if (reg == 2)
			{
				cerr << fileParameter << ": line: " << lineNumber+1 << endl
					 << "Segmentation error: Register is out of range: "
					 << param2 << endl;
			
				setFlag();
			}
		
			else if (mem == 2)
			{
				cerr << fileParameter << ": line: " << lineNumber+1 << endl
					 << "Segmentation error: Memory is out of range: "
					 << param2 << endl;
			
				setFlag();
			}
		
			else if (!(reg==1 || mem==1 || con))
			{
				cerr << fileParameter << ": line: " << lineNumber+1 << endl
					 << "Syntax error: Second parameter of ADD instruction must "
					 << "be register, memory or constant: " << param2 << endl;
			
				setFlag();
			}
		}
	
		return;
	}



	void CPUProgramDyn :: subSyntaxCheck(string line, int lineNumber)
	{
		string param1, param2;
		bool con;
		int reg, mem;
	
	
		param1 = getFirstParam(line, lineNumber);
		param2 = getSecondParam(line, lineNumber);
		reg = isRegister(param1);
	
		/* SUB instruction can have (register-register), (register-memory) or */
		/* (register-constant) parameter sets */
		if (reg == 2)
		{
			cerr << fileParameter << ": line: " << lineNumber+1 << endl
				 << "Segmentation error: Register is out of range: " << param1
				 << endl;
			
			setFlag();
		}
	
		else if (reg == 0)
		{
			cerr << fileParameter << ": line: " << lineNumber+1 << endl
				 << "Syntax error: First parameter of SUB instruction must be "
				 << "register: " << param1 << endl;
			
			setFlag();
		}
	
		else
		{
			con = isConstant(param2);
			reg = isRegister(param2);
			mem = isMemory(param2);
		
			if (reg == 2)
			{
				cerr << fileParameter << ": line: " << lineNumber+1 << endl
					 << "Segmentation error: Register is out of range: "
					 << param2 << endl;
			
				setFlag();
			}
		
			else if (mem == 2)
			{
				cerr << fileParameter << ": line: " << lineNumber+1 << endl
					 << "Segmentation error: Memory is out of range: "
					 << param2 << endl;
		
				setFlag();
			}
		
			else if (!(reg==1 || mem==1 || con))
			{
				cerr << fileParameter << ": line: " << lineNumber+1 << endl
					 << "Syntax error: Second parameter of SUB instruction must be "
					 << "register, memory or constant: " << param2 << endl;
			
				setFlag();
			}
		}
	
		return;
	}



	void CPUProgramDyn :: movSyntaxCheck(string line, int lineNumber)
	{
		string param1, param2;
		bool con;
		int reg, mem;
	
	
		param1 = getFirstParam(line, lineNumber);
		param2 = getSecondParam(line, lineNumber);
		reg = isRegister(param1);
		mem = isMemory(param1);
	
		/* MOV instruction can have (register-register), (register-memory) */
		/* (register-constant), (memory-constant) or (memory-register) */
		/* parameter sets */
		if (reg == 2)
		{
			cerr << fileParameter << ": line: " << lineNumber+1 << endl
				 << "Segmentation error: Register is out of range: " << param1
				 << endl;
			
			setFlag();
		}
	
		else if (mem == 2)
		{
			cerr << fileParameter << ": line: " << lineNumber+1 << endl
				 << "Segmentation error: Memory is out of range: "
				 << param2 << endl;
		
			setFlag();
		}
	
		else if (reg == 0 && mem == 0)
		{
			cerr << fileParameter << ": line: " << lineNumber+1 << endl
				 << "Syntax error: First parameter of MOV instruction must be "
				 << "register or memory address: " << param1 << endl;
			
			setFlag();
		}
	
		else
		{
			con = isConstant(param2);
			reg = isRegister(param2);
			mem = isMemory(param2);
		
			if (reg == 2)
			{
				cerr << fileParameter << ": line: " << lineNumber+1 << endl
					 << "Segmentation error: Register is out of range: "
					 << param2 << endl;
			
				setFlag();
			}
		
			else if (mem == 2)
			{
				cerr << fileParameter << ": line: " << lineNumber+1 << endl
					 << "Segmentation error: Memory is out of range: "
					 << param2 << endl;
		
				setFlag();
			}
		
			else if (!(reg==1 || mem==1 || con))
			{
				cerr << fileParameter << ": line: " << lineNumber+1 << endl
					 << "Syntax error: Second parameter of MOV instruction must be "
					 << "register, memory or constant: " << param2 << endl;
			
				setFlag();
			}
		}
	
		return;
	}



	void CPUProgramDyn :: jmpSyntaxCheck(string line, int lineNumber)
	{
		string param1, param2;
		int reg, totalLines;
		bool con;
	
	
		totalLines = size();
		param1 = getFirstParam(line, lineNumber);
		param2 = getSecondParam(line, lineNumber);
	
		/* JMP instruction can have two different parameter sets, if it has 2 */
		/* params first must be register and second is a constant (line number) */
		/* else first param must be constant (line number) and the other is null */
		if (param2 == "\0")
		{
			if (!isConstant(param1) || strToInt(param1)>totalLines || strToInt(param1)<=0)
			{
				cerr << fileParameter << ": line: " << lineNumber+1 << endl
					 << "Syntax error: JMP instruction needs a valid line number: "
					 << param1 << endl;
			
				setFlag(); 
			}
		}
	
		else
		{
			reg = isRegister(param1);
			con = isConstant(param2);
		
			if (reg == 2)
			{
				cerr << fileParameter << ": line: " << lineNumber+1 << endl
					 << "Segmentation error: Register is out of range: "
					 << param1 << endl;
		
				setFlag();
			}
		
			else if (reg == 1)
			{
				if (!(con && (strToInt(param2)>0 && strToInt(param2)<=totalLines)))
				{
					cerr << fileParameter << ": line: " << lineNumber+1 << endl
						 << "Syntax error: Second parameter of JMP instruction "
						 << "must be a valid line number: " << param2 << endl;
			
					setFlag();
				}
			}
		
			else
			{
				cerr << fileParameter << ": line: " << lineNumber+1 << endl
					 << "Syntax error: First parameter of JMP instruction must "
					 << "either be a valid line number or a register: "
					 << param2 << endl;
		
				setFlag();
			}
		}
	
	
		return;
	}



	void CPUProgramDyn :: jpnSyntaxCheck(const string line, const int lineNumber)
	{
		string param1, param2;
		int reg, totalLines;
		bool con;
	
	
		totalLines = size();
		param1 = getFirstParam(line, lineNumber);
		param2 = getSecondParam(line, lineNumber);
		/* JPN instruction can have two parameters, first must be register */
		/* and the second one must be valid line number to jump */

		reg = isRegister(param1);
		con = isConstant(param2);
	
		if (reg == 2)
		{
			cerr << fileParameter << ": line: " << lineNumber+1 << endl
				 << "Segmentation error: Register is out of range: "
				 << param1 << endl;
	
			setFlag();
		}
	
		else if (reg == 1)
		{
			if (!(con && (strToInt(param2)>0 && strToInt(param2)<=totalLines)))
			{
				cerr << fileParameter << ": line: " << lineNumber+1 << endl
					 << "Syntax error: Second parameter of JPN instruction must "
					 << "be a valid line number: " << param2 << endl;
		
				setFlag();
			}
		}
	
		else
		{
			cerr << fileParameter << ": line: " << lineNumber+1 << endl
				 << "Syntax error: First parameter of JPN instruction must be a "
				 << "register: " << param2 << endl;
	
			setFlag();
		}
	
	
		return;
	}



	void CPUProgramDyn :: prnSyntaxCheck(string line, int lineNumber)
	{
		string param1, param2;
		int reg, mem;
		bool con;
	
	
		param1 = getFirstParam(line, lineNumber);
		param2 = getSecondParam(line, lineNumber);
	
		/* PRN instruction can only take 1 parameter, second param must be empty */
		if (param2 != "\0")
		{
			cerr << fileParameter << ": line: " << lineNumber+1 << endl
				 << "Syntax error: PRN instruction can not take more than 1 "
				 << "parameters: " << param2 << endl;
	
			setFlag();
		}
	
		/* First param must be register or a constant */
		else
		{
			reg = isRegister(param1);
			con = isConstant(param1);
			mem = isMemory(param1);
		
			if (reg == 2)
			{
				cerr << fileParameter << ": line: " << lineNumber+1 << endl
					 << "Segmentation error: Register is out of range: "
					 << param1 << endl;
			
				setFlag();
			}
		
			else if (reg == 0 && mem == 0 && con == false)
			{
				cerr << fileParameter << ": line: " << lineNumber+1 << endl
					 << "Syntax error: PRN instruction needs a register or constant"
					 << " as parameter: " << param1 << endl;
			
				setFlag();
			}
		}
	
	
		return;
	}



	void CPUProgramDyn :: hltSyntaxCheck(string line, int lineNumber)
	{
		string param1, param2;
	
		param1 = getFirstParam(line, lineNumber);
		param2 = getSecondParam(line, lineNumber);
	
		/* HLT instruction can not take parameters, both must be empty string */
		if (param1 != "\0")
		{
			cerr << fileParameter << ": line: " << lineNumber+1 << endl
				 << "Syntax error: HLT instruction can not take parameter(s): "
				 << param1 << endl;
		
			setFlag();
		}
	
		else if (param2 != "\0")
		{
			cerr << fileParameter << ": line: " << lineNumber+1 << endl
				 << "Syntax error: HLT instruction can not take parameters: "
				 << param2 << endl;
		
			setFlag();
		}
	
	
		return;
	}



	string CPUProgramDyn :: getInstruction(string line)
	{
		string ins;
		int i;
	
	
		for (i=0; line[i]!=' '; i++)
		; /* Finding the index of whitespace */
		/* Taking a sub string from the index of whitespace */
		ins = line.substr(0, i);
	
	
		return (ins);
	}



	string CPUProgramDyn :: getFirstParam(string line, int lineNumber)
	{
		string param;
		int i, j, commaCount=0;
		const int MAX_PARAM = 2;
		bool comma=false;
	
	
		/* Looking for comma to figure out the number of parameters */
		for (i=0; line[i]!='\0'; i++)
		{
			if (line[i] == ',')
			{
				comma = true;
				commaCount++;
			}
		}
	
	
		if (commaCount >= MAX_PARAM)
		{
			cerr << fileParameter << ": line: " << lineNumber+1 << endl
				 << "Syntax error: Instructions can not take more than 2 parameters"
				 << endl;
				 
			setFlag();
		}
	
		else if (comma)
		{
			/* Finding the index of comma */
			for (i=0; line[i]!=','; i++)
			{
				if (line[i] == ' ')
					j=i;
			}
			/* Taking sub string from whitespace to comma */
			param = line.substr(j+1,i-j-1);
		}
	
		else
		{
			/* Finding the second whitespace */
			for (i=0; line[i]!='\0'; i++)
			{
				if (line[i] == ' ')
					j=i;
			}
		
			for (i=0; line[i]!=' '; i++)
			; /* Finding the first whitespace */
			/* Taking sub string from whitespace to whitespace */
			param = line.substr(i+1,j-i-1);
		}
	
	
		return (param);
	}



	string CPUProgramDyn :: getSecondParam(string line, int lineNumber)
	{
		string param;
		int i, j;
		bool comma=false;
	
	
		for (i=0; line[i]!='\0'; i++)
		{
			if (line[i] == ',')
				comma = true;
		}
	
	
		if (comma)
		{
			/* Finding the second whitespace */
			for (i=0; line[i]!='\0'; i++)
			{
				if (line[i] == ' ')
					j=i;
			}
		
			for (i=0; line[i]!=','; i++)
			; /* Finding the comma */
		
			param = line.substr(i+1,j-i-1);
		}
	
		else
		{
			/* Finding the second whitespace */
			for (i=0; line[i]!='\0'; i++)
			{
				if (line[i] == ' ')
					j=i;
			}
		
			for (i=0; line[i]!='\0'; i++)
			; /* Finding the end of line */
		
			param = line.substr(j+1,i-j-1);
		}
	
	
		return (param);
	}



	void CPUProgramDyn :: formatEditor()
	{
		int totalLines, currentLine=0;
	
	
		totalLines = size();
	
		/* Creating a loop to check every line read from file */
		while (currentLine < totalLines)
		{
			int length=lines[currentLine].length(), i=0;
		
			/* Creating another loop to check and edit every character of the */
			/* string until an error has occured or end of the string has reached */
			while (i<length && getFlag())
			{
			
				if (lines[currentLine][i] == ';')
				{
					lines[currentLine].erase(i);
					break;
				}
			
				if (lines[currentLine][i] == '	')
					lines[currentLine][i] = ' ';
			
				if (lines[currentLine][i]>='a' && lines[currentLine][i]<='z')
					lines[currentLine][i] -= 'a'-'A';
			
				if (lines[currentLine][i]==' ' && lines[currentLine][i+1]==',')
					lines[currentLine].erase(i, 1);
			
				if (lines[currentLine][i]==',' && lines[currentLine][i+1]==' ')
				{
					lines[currentLine].erase(i+1, 1);
					i -= 1;
				}
			
				if (lines[currentLine][i]==' ' && lines[currentLine][i+1]==' ')
				{
					lines[currentLine].erase(i, 1);
					i -= 1;
				}
			
				if (lines[currentLine][i]==' ' && lines[currentLine][i+1]=='	')
				{
					lines[currentLine].erase(i+1, 1);
					i -= 1;
				}
			
				if (lines[currentLine][i]=='	' && lines[currentLine][i+1]=='	')
				{
					lines[currentLine].erase(i, 1);
					i -= 1;
				}
			
				if (lines[currentLine][i]=='	' && lines[currentLine][i+1]==' ')
				{
					lines[currentLine].erase(i, 1);
					i -= 1;
				}
			
				i++;
			}
		
			if (lines[currentLine][0]==' ' || lines[currentLine][0]=='	')
				lines[currentLine].erase(0, 1);
			
			i=lines[currentLine].length();
			if (lines[currentLine][i-1] != ' ')
				lines[currentLine].insert(i, " ");
		
			if (length == 0)
			{
				cerr << fileParameter << ": line: " << currentLine+1 << endl
					 << "Syntax error: Lines can not be blank or empty" << endl;
					 
				setFlag();
			}
		
			currentLine++;
		}
	
	
		return;
	}



	int CPUProgramDyn :: isMemory(const string parameter) const
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



	bool CPUProgramDyn :: isConstant(const string param) const
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



	int CPUProgramDyn :: isRegister(const string param) const
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



	int CPUProgramDyn :: strToInt(const string str) const
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
}
/* End of CPUProgramDyn.cpp */
