/*
 * CPUProgram.cpp
 * Contains CPUProgram class function implementations 
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
 
 

/* Include(s) */
#include <string>
#include <fstream>
#include <iostream>
#include "CPUProgram.h"
using namespace std;



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



CPUProgram :: CPUProgram(const char *fileName)
{
	/* Setting all data to their initial values */
	fileParameter = fileName;
	count = 0;
	errorFlag = true;
	mode = 0;
	
	/* Calling function to load instructions from file */
	ReadFile(fileName);
}



CPUProgram :: CPUProgram(int option)
{
	/* Setting all data to their initial values */
	fileParameter = nullptr;
	count = 0;
	errorFlag = true;	
	mode = option;
}



/* Setting display mode 0 as default if it doesn't given */
CPUProgram :: CPUProgram() : CPUProgram(0)
{/* Intentionally blank */}



const string CPUProgram :: operator [] (int lineNumber) const
{
	/* Making error check for the index number */
	if (lineNumber<0 || lineNumber>size()-1 || size()==0)
	{
		cerr << "Invalid index number for '[]' operator: 'CPUProgram["
			 << lineNumber << "]'" << endl;
		//exit(1);
		/* PDF wanted program to be shut down after an error. But program */
		/* changed to return empty string upon error to continue testing */
		return "";
	}
	
	
	/* Calling getLine function to reach desired line */
	return (getLine(lineNumber));
}



const CPUProgram CPUProgram :: operator + (const string line) const
{
	/* Creating a new CPUProgram object to return */
	CPUProgram newProgram;
	
	
	/* Doing error check */
	if (line == "")
	{
		cerr << "Invalid string for '+' operator" << endl;
		//exit(1);
		/* PDF wanted program to be shut down after an error. But program */
		/* changed to let program continue testing */
	}
	
	else
	{
		/* If there is no error building inside of the new program */
		newProgram = *this;
		newProgram.lines.push_back(line);
		newProgram.setCount(newProgram.size() + 1);
	}
	
	
	/* If there is an error + operator will return empty program */
	return newProgram;
}



const CPUProgram CPUProgram :: operator + (const CPUProgram& other) const
{
	/* Creating a new CPUProgram to return and building inside with the */
	/* variables of 'this' parameter */
	CPUProgram newProgram;
	newProgram.fileParameter = this->fileParameter;
	newProgram.errorFlag = this->errorFlag;
	newProgram.mode = this->mode;
	

	/* After that calling + operator to add lines from first program to the */
	/* new program */
	for (int i=0; i<this->size(); i++)
	{
		newProgram = newProgram + (*this)[i];
	}
	
	/* Same thing for the second program */
	for (int i=0; i<other.size(); i++)
	{
		newProgram = newProgram + other[i];
	}
	
	
	/* Returning the new program */
	return newProgram;
}



const CPUProgram& CPUProgram :: operator += (const string line)
{
	/* Calling + operator as += stands for adding something with itself and */
	/* reassigning it to itself */
	*this = *this + line;
	
	
	/* Returning this as referance */
	return *this;
}



const CPUProgram CPUProgram :: operator () (int top, int end) const
{
	/* Creating a new program to return and building inside with given program*/
	CPUProgram newProgram;
	newProgram.fileParameter = this->fileParameter;
	newProgram.errorFlag = this->errorFlag;
	newProgram.mode = this->mode;
	
	/* Error checks for the invalid line numbers */
	if (top>end || end>size() || end<0 || top<0)
	{
		cerr << "Invalid index number for '()' operator: 'CPUProgram(" << top
			 << ", " << end << ")'" << endl;
		//exit(1);
		/* PDF wanted program to be shut down after an error. But program */
		/* changed to return empty CPUProgram upon error to continue testing */
		return newProgram;
	}
	
	/* If there is no error adding wanted lines to new program */
	for (int i=top; i<=end; i++)
	{
		newProgram = newProgram + (*this)[i];
	}
	
	
	/* Returning the new program */
	return newProgram;
}



bool CPUProgram :: operator == (const CPUProgram& other) const
{
	/* Doing a simple size compare over programs */
	return (size() == other.size());
}



bool CPUProgram :: operator != (const CPUProgram& other) const
{
	/* Returning opposite of the 'is equals to' operator */
	return !(*this==other);
}



bool CPUProgram :: operator > (const CPUProgram& other) const
{
	/* Doing a simple size compare over programs */
	return (size() > other.size());
}



bool CPUProgram :: operator < (const CPUProgram& other) const
{
	/* Doing a simple size compare over programs */
	return (size() < other.size());
}



bool CPUProgram :: operator >= (const CPUProgram& other) const
{
	/* Returning opposite of the 'is smaller than' operator */
	return !(*this < other);
}



bool CPUProgram :: operator <= (const CPUProgram& other) const
{
	/* Returning opposite of the 'is greater than' operator */
	return !(*this > other);
}



void CPUProgram :: operator -- ()
{
	/* Simply deleting last line from program as well as decreasing the count */
	setCount(size() - 1);
	this->lines.pop_back();
}



void CPUProgram :: operator -- (int)
{
	/* Calling prefix operator due to their same function */
	--(*this);
}



ostream& operator << (ostream& out, const CPUProgram& obj)
{
	/* Inserting each line to output stream object */
	for (int i=0; i<obj.size(); i++)
		out << obj[i] << endl;
	
	
	return out;
}



void CPUProgram :: ReadFile(const char *fileName)
{
	/* Changing the fileParameter in case object initialized without */
	/* parameters or with only option */
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



void CPUProgram :: fileOpener(const char *fileName)
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
			lines.push_back(line);
			setCount(size() + 1);
		}
	
	/* End of file process */
	file.close();
	
	
	return;
}



void CPUProgram :: syntaxCheck()
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



void CPUProgram :: addSyntaxCheck(string line, int lineNumber)
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



void CPUProgram :: subSyntaxCheck(string line, int lineNumber)
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



void CPUProgram :: movSyntaxCheck(string line, int lineNumber)
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



void CPUProgram :: jmpSyntaxCheck(string line, int lineNumber)
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



void CPUProgram :: jpnSyntaxCheck(const string line, const int lineNumber)
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



void CPUProgram :: prnSyntaxCheck(string line, int lineNumber)
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



void CPUProgram :: hltSyntaxCheck(string line, int lineNumber)
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



string CPUProgram :: getInstruction(string line)
{
	string ins;
	int i;
	
	
	for (i=0; line[i]!=' '; i++)
	; /* Finding the index of whitespace */
	/* Taking a sub string from the index of whitespace */
	ins = line.substr(0, i);
	
	
	return (ins);
}



string CPUProgram :: getFirstParam(string line, int lineNumber)
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



string CPUProgram :: getSecondParam(string line, int lineNumber)
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



void CPUProgram :: formatEditor()
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



int CPUProgram :: isMemory(const string parameter) const
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



bool CPUProgram :: isConstant(const string param) const
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



int CPUProgram :: isRegister(const string param) const
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



int CPUProgram :: strToInt(const string str) const
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

/* End of CPUProgram.cpp */
