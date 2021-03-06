/*
 * cpuProgram.cpu
 * Contains cpuProgram class function implementations 
 * This class simulates a CPU helper. Objects are obligated to read
 * a CPU program from a text file. Upon declaration, a constructor
 * will be called to open file, read lines and check for errors.
 *
 * This class coded for the homework 3 of GTU's CSE241 lecture, Fall 2016
 * File belongs to Deniz Can Erdem Yılmaz - 151044001
 * 27/10/2016
 */
 
 

/* Include(s) */
#include <string>
#include <fstream>
#include <iostream>
#include "cpuProgram.h"

using namespace std;



/* Constant int variables instead of defines */
const int MAX_PARAM = 2;
const int ZERO_ASCII = 48;

/* Instruction set of CPU */
const string ADD = "ADD";
const string SUB = "SUB";
const string MOV = "MOV";
const string JMP = "JMP";
const string PRN = "PRN";
const string HLT = "HLT";



cpuProgram :: cpuProgram(char *fileName)
{
	/* Initializing variables */
	fileParameter = fileName;
	lineCount = 0;
	errorFlag = true;
	
	/* Calling function to load instructions */
	readFile(fileName);
}



cpuProgram :: cpuProgram() : cpuProgram(NULL)
{/* Intentionally blank */}



void cpuProgram :: readFile(char *fileName)
{
	/* Calling appropriate functions for loading instructions, formatting */
	/* lines and error checks */
	if (getFlag())
		fileOpener(fileName);
	
	if (getFlag())
		formatEditor();
	
	if (getFlag())
		syntaxCheck();
	
	
	return;
}



void cpuProgram :: fileOpener(char *fileName)
{
	int i=0;
	ifstream file;
	
	
	file.open(fileName);
	/* Printing error and changing flag if file doesn't exist */
	if (file == NULL)
	{
		cerr << fileParameter << ": " << endl
			 << "File error: Given file couldn't found in directory" << endl;
		
		setFlag();
	}
	/* Else take lines to an array, close the file and set line count */
	else
		while (getline(file, lines[i]))
		{
			i++;
		}
	
	file.close();	
	setLineCount(i);
	
	
	return;
}



void cpuProgram :: syntaxCheck()
{
	string instruction;
	int totalLines, currentLine=0;
	bool halt=false;
	
	
	totalLines = size();
	/* Creating a loop to check every line */
	while (currentLine<totalLines)
	{
		instruction = getInstruction(getLine(currentLine+1));
		/* Comparing instructions taken from file with CPU insctruction set */
		/* to find if there is any error on that line */
		if (instruction == ADD)
		{
			addSyntaxCheck(getLine(currentLine+1), currentLine);
		}
		
		else if (instruction == SUB)
		{
			subSyntaxCheck(getLine(currentLine+1), currentLine);
		}
		
		else if (instruction == MOV)
		{
			movSyntaxCheck(getLine(currentLine+1), currentLine);
		}
		
		else if (instruction == JMP)
		{
			jmpSyntaxCheck(getLine(currentLine+1), currentLine);
		}
		
		else if (instruction == PRN)
		{
			prnSyntaxCheck(getLine(currentLine+1), currentLine);
		}
		
		else if (instruction == HLT)
		{
			hltSyntaxCheck(getLine(currentLine+1), currentLine);
			
			halt = true;
		}
		
		else
		{
			cerr << fileParameter << ": line: " << currentLine+1 << endl
				 << "Syntax error: Undefined instruction: " << instruction << endl;
			
			setFlag();
		}
		
		currentLine++;
	}
	
	/* Also checking if CPU program has HLT command to terminate process */
	if (!halt)
	{
		cerr << fileParameter << ": " << endl
			 << "Termination error: HLT instruction couldn't found in file" << endl;
		
		setFlag();
	}
	
	
	return;
}



void cpuProgram :: addSyntaxCheck(string line, int lineNumber)
{
	string param1, param2;
	bool con;
	int reg;
	
	
	param1 = getFirstParam(line, lineNumber);
	param2 = getSecondParam(line, lineNumber);
	reg = isRegister(param1);
	/* ADD instruction can have (register-register) or (register-constant) */
	/* parameter sets */
	if (reg == 2)
	{
		cerr << fileParameter << ": line: " << lineNumber+1 << endl
			 << "Segmentation error: Register is out of range: " << param1 << endl;
			
		setFlag();
	}
	
	else if (reg == 0)
	{
		cerr << fileParameter << ": line: " << lineNumber+1 << endl
			 << "Syntax error: First parameter of ADD instruction must be register: " << param1 << endl;
			
		setFlag();
	}
	
	else
	{
		con = isConstant(param2);
		reg = isRegister(param2);
		
		if (reg == 2)
		{
			cerr << fileParameter << ": line: " << lineNumber+1 << endl
				 << "Segmentation error: Register is out of range: " << param2 << endl;
			
			setFlag();
		}
		
		else if (!(reg==1 || con))
		{
			cerr << fileParameter << ": line: " << lineNumber+1 << endl
				 << "Syntax error: Second parameter of ADD instruction must be register or constant: " << param2 << endl;
			
			setFlag();
		}
	}
	
	return;
}



void cpuProgram :: subSyntaxCheck(string line, int lineNumber)
{
	string param1, param2;
	bool con;
	int reg;
	
	
	param1 = getFirstParam(line, lineNumber);
	param2 = getSecondParam(line, lineNumber);
	reg = isRegister(param1);
	/* SUB instruction can have (register-register) or (register-constant) */
	/* parameter sets */
	if (reg == 2)
	{
		cerr << fileParameter << ": line: " << lineNumber+1 << endl
			 << "Segmentation error: Register is out of range: " << param1 << endl;
			
		setFlag();
	}
	
	else if (reg == 0)
	{
		cerr << fileParameter << ": line: " << lineNumber+1 << endl
			 << "Syntax error: First parameter of SUB instruction must be register: " << param1 << endl;
			
		setFlag();
	}
	
	else
	{
		con = isConstant(param2);
		reg = isRegister(param2);
		
		if (reg == 2)
		{
			cerr << fileParameter << ": line: " << lineNumber+1 << endl
				 << "Segmentation error: Register is out of range: " << param2 << endl;
			
			setFlag();
		}
		
		else if (!(reg==1 || con))
		{
			cerr << fileParameter << ": line: " << lineNumber+1 << endl
				 << "Syntax error: Second parameter of SUB instruction must be register or constant: " << param2 << endl;
			
			setFlag();
		}
	}
	
	return;
}



void cpuProgram :: movSyntaxCheck(string line, int lineNumber)
{
	string param1, param2;
	bool con;
	int reg;
	
	
	param1 = getFirstParam(line, lineNumber);
	param2 = getSecondParam(line, lineNumber);
	reg = isRegister(param1);
	/* MOV instruction can have (register-register) or (register-constant) */
	/* parameter sets */
	if (reg == 2)
	{
		cerr << fileParameter << ": line: " << lineNumber+1 << endl
			 << "Segmentation error: Register is out of range: " << param1 << endl;
			
		setFlag();
	}
	
	else if (reg == 0)
	{
		cerr << fileParameter << ": line: " << lineNumber+1 << endl
			 << "Syntax error: First parameter of MOV instruction must be register: " << param1 << endl;
			
		setFlag();
	}
	
	else
	{
		con = isConstant(param2);
		reg = isRegister(param2);
		
		if (reg == 2)
		{
			cerr << fileParameter << ": line: " << lineNumber+1 << endl
				 << "Segmentation error: Register is out of range: " << param2 << endl;
			
			setFlag();
		}
		
		else if (!(reg==1 || con))
		{
			cerr << fileParameter << ": line: " << lineNumber+1 << endl
				 << "Syntax error: Second parameter of MOV instruction must be register or constant: " << param2 << endl;
			
			setFlag();
		}
	}
	
	return;
}



void cpuProgram :: jmpSyntaxCheck(string line, int lineNumber)
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
				 << "Syntax error: JMP instruction needs a valid line number: " << param1 << endl;
			
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
				 << "Segmentation error: Register is out of range: " << param1 << endl;
		
			setFlag();
		}
		
		else if (reg == 1)
		{
			if (!con)
			{
				cerr << fileParameter << ": line: " << lineNumber+1 << endl
					 << "Syntax error: Second parameter of JMP instruction must be a valid line number: " << param2 << endl;
			
				setFlag();
			}
		}
		
		else
		{
			cerr << fileParameter << ": line: " << lineNumber+1 << endl
				 << "Syntax error: First parameter of JMP instruction must either be a valid line number or a register: " << param2 << endl;
		
			setFlag();
		}
	}
	
	
	return;
}



void cpuProgram :: prnSyntaxCheck(string line, int lineNumber)
{
	string param1, param2;
	int reg;
	bool con;
	
	
	param1 = getFirstParam(line, lineNumber);
	param2 = getSecondParam(line, lineNumber);
	
	/* PRN instruction can only take 1 parameter, second param must be empty */
	if (param2 != "\0")
	{
		cerr << fileParameter << ": line: " << lineNumber+1 << endl
			 << "Syntax error: PRN instruction can not take more than 1 parameters: " << param2 << endl;
	
		setFlag();
	}
	
	/* First param must be register or a constant */
	else
	{
		reg = isRegister(param1);
		con = isConstant(param1);
		
		if (reg == 2)
		{
			cerr << fileParameter << ": line: " << lineNumber+1 << endl
				 << "Segmentation error: Register is out of range: " << param1 << endl;
			
			setFlag();
		}
		
		else if (reg == 0 && !con)
		{
			cerr << fileParameter << ": line: " << lineNumber+1 << endl
				 << "Syntax error: PRN instruction needs a register or constant as parameter: " << param1 << endl;
			
			setFlag();
		}
	}
	
	
	return;
}



void cpuProgram :: hltSyntaxCheck(string line, int lineNumber)
{
	string param1, param2;
	
	param1 = getFirstParam(line, lineNumber);
	param2 = getSecondParam(line, lineNumber);
	
	/* HLT instruction can not take parameters, both must be empty string */
	if (param1 != "\0")
	{
		cerr << fileParameter << ": line: " << lineNumber+1 << endl
			 << "Syntax error: HLT instruction can not take parameter(s): " << param1 << endl;
		
		setFlag();
	}
	
	else if (param2 != "\0")
	{
		cerr << fileParameter << ": line: " << lineNumber+1 << endl
			 << "Syntax error: HLT instruction can not take parameters: " << param2 << endl;
		
		setFlag();
	}
	
	
	return;
}



string cpuProgram :: getInstruction(string line)
{
	string ins;
	int i;
	
	
	for (i=0; line[i]!=' '; i++)
	; /* Finding the index of whitespace */
	/* Taking a sub string from the index of whitespace */
	ins = line.substr(0, i);
	
	
	return (ins);
}



string cpuProgram :: getFirstParam(string line, int lineNumber)
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
			 << "Syntax error: Instructions can not take more than 2 parameters" << endl;
			 
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



string cpuProgram :: getSecondParam(string line, int lineNumber)
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



void cpuProgram :: formatEditor()
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



bool cpuProgram :: isConstant(const string param)
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



int cpuProgram :: isRegister(const string param)
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



int cpuProgram :: strToInt(const string str)
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

/* End of cpuProgram.cpp */
