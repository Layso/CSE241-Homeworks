/*
 * main.cpp
 * This 2nd homework for CSE241 lecture of Gebze Technical University
 * Homework made by Deniz Can Erdem Yılmaz - 151044001
 * 16.10.2016
 *
 * Program takes an input file of assembly instructions and performs them as
 * a CPU does
 *
 */



/* Include(s) */
#include <iostream>
#include <string>
#include <fstream>

using namespace std;



/* Constant variable(s) */
const int VALID_PARAM = 3;
const int ZERO_ASCII = 48;
const int REG_COUNT = 5;
const int MEMORY_COUNT = 50;
const int MAX_LINE = 200;
const char* TMP_FILE = "tmp.txt";
const string MODE_0 = "0";
const string MODE_1 = "1";
const string MODE_2 = "2";
const string ADD = "ADD";
const string SUB = "SUB";
const string MOV = "MOV";
const string JMP = "JMP";
const string JPN = "JPN";
const string PRN = "PRN";
const string HLT = "HLT";



/* Function prototype(s) */
/* Main instruction cycle function. Makes function calls */
void decode(int mode);

/* Overloaded fetch function, reads cleared temp file for execution */
int fetch(string *commandLines);

/* Instruction specialized execute functions */
void addExecute(string param1, string param2, int *reg, int *memory);
void subExecute(string param1, string param2, int *reg, int *memory);
bool movExecute(string param1, string param2, int *reg, int *memory);
void jmpExecute(string param1, string param2, int *reg, int& line);
void jpnExecute(string param1, string param2, int *reg, int& line);
void prnExecute(string param1, int *reg, int *memory);


/* Main error check file. Makes function calls*/
bool errorCheck(int argCount, char **arguments);

/* Checks the command line arguments */
bool argumentCheck(int argCount, char **arguments);

/* Checks if the given file is valid or not */
bool fileCheck(char *fileName);

/* Checks if there is any syntax error */
bool syntaxCheck();

/* Overloaded fetch function, reads cleared temp file for execution */
bool fetch(string *commandLines, int& lineCount);

/* Instruction specialized check functions, controlling parameters */
int hltCheck(string ins, string param1, string param2);
int movCheck(string param1, string param2);
int addSubCheck(string param1, string param2);
int jmpCheck(string param1, string param2);
int jpnCheck(string param1, string param2);
int prnCheck(string param1, string param2);
int movCheck(string param1, string param2);


/* Clears given file and writes it to another temp file for further usage */
void fileEdit(char *fileName);

/* Erases unwanted and junk characters from file */
void formatChanger(string *lines, int lineCount);

/* Takes instructions from file array to command array */
void getInstruction(string *lines, string *commandList, int lineNumber);

/* Takes parameters from file array to command array */
bool getParameters(string *lineList, string *commandList, int lineNumber, int paramCount, bool comment);


/* Simple helper functions */
/* Counts ',' on a string to found parameter number */
int parameterCounter(string *commandList, int lineNumber, bool comment);

/* Searches ';' on a string to set comment flag */
bool commentCheck(string *commandList, int lineNumber);

/* Checks if given string equals to a valid register */
int isRegister(string parameter);

/* Checks if given string equals to an constant */
bool isConstant(string parameter);

/* Checks if given string equals to a memory address */
int isMemory(string parameter);

/* Converts string to decimal integer */
int strToInt(string parameter);

/* Converts memory address to integer index */
int memToInt(string parameter);

/* Prints all registers to screen */
void registerDisplay(int *reg);

/* Prints all memory cells to screen */
void memoryDisplay(int *mem);

/* Sets all registers as 0 */
void registerSet(int *reg);

/* Sets all memories as 0 */
void memorySet(int *mem);

/* Prints current processed line */
void lineDisplay(string ins, string param1, string param2);



int main(int argc, char **argv)
{
	int mode;
	
	
	cout << endl;
	
	/* Checking all errors before execution to prevent run-time errors */
	if (errorCheck(argc, argv))
	{
		/* If there is no error, call decode function */
		mode = strToInt(argv[2]);
		decode(mode);
	}
	
	cout << endl;
	/* End of the program */
	return (0);
}



void decode(int mode)
{
	bool exit = true;
	int lineCounter=0, lineCount, registers[REG_COUNT], i, arg0, arg1, arg2;
	int memory[MEMORY_COUNT];
	string fileLines[MAX_LINE], commands[MAX_LINE*3];
	
	
	/* Setting all register and memory cells as 0 and fetching lines from file */
	registerSet(registers);
	memorySet(memory);
	lineCount = fetch(commands);
	
	/* Creating a instruction cycle until encountering HALT command */
	while (exit)
	{
		/* Setting parameter indexes for command array */
		arg0 = (lineCounter*3);
		arg1 = (lineCounter*3) + 1;
		arg2 = (lineCounter*3) + 2;
		
		
		/* Checking mode to print instruction first */
		if ((mode == 1 || mode == 2) && commands[arg0] != HLT)
		{
			cout << "Line: " << lineCounter+1 << " - ";
			lineDisplay(commands[arg0], commands[arg1], commands[arg2]);
			cout << endl;
		}
		
		/* Checking and calling function suitable with instruction */ 
		if (commands[arg0] == ADD)
			addExecute(commands[arg1], commands[arg2], registers, memory);
		
		else if (commands[arg0] == SUB)
			subExecute(commands[arg1], commands[arg2], registers, memory);
		
		else if (commands[arg0] == MOV)
			exit = movExecute(commands[arg1], commands[arg2], registers, memory);
		
		else if (commands[arg0] == JMP)
			jmpExecute(commands[arg1], commands[arg2], registers, lineCounter);
		
		else if (commands[arg0] == JPN)
			jpnExecute(commands[arg1], commands[arg2], registers, lineCounter);
		
		else if (commands[arg0] == PRN)
			prnExecute(commands[arg1], registers, memory);
		
		else if (commands[arg0] == HLT){
			/* Giving information, printing all registers and quitting */
			cout << "Program halted without any errors" << endl;
			registerDisplay(registers);
			memoryDisplay(memory);
			exit = false;
		}
		
		/* Printing registers or memory after execution if wanted */
		if (commands[arg0] != HLT)
		{
			switch (mode)
			{
				case 1: registerDisplay(registers); cout << endl; break;
				case 2: memoryDisplay(memory); cout << endl; break;
				default: break;
			}
		}
		
		/* Checking if line counter is valid. Prints error message if */
		/* current line number is over the file line */
		if (lineCounter >= lineCount){
			cerr << "Error on run time:" << endl
				 << "Line count error: Couldn't find the current line on file: "
				 << lineCounter+1 << endl
				 << "Program halted due to an error" << endl;
					 
				
			/* Setting exit flag as false to break loop */
			exit = false;
		}
		
		/* Increasing line counter for next step */
		++lineCounter;
	}
	
	
	return;
}



void addExecute(string param1, string param2, int *reg, int *memory)
{
	/* If param2 is a register perform register addition */
	if (isRegister(param2))
		reg[(param1[1] - ZERO_ASCII) -1] += reg[(param2[1] - ZERO_ASCII) -1];
	
	/* If para2 is a constant perform register - const addition */
	else if (isConstant(param2))
		reg[(param1[1] - ZERO_ASCII) -1] += strToInt(param2);
	
	/* If param2 is an address perform register - address addition */
	else
		reg[(param1[1] - ZERO_ASCII) -1] += memory[memToInt(param2)];
}



void subExecute(string param1, string param2, int *reg, int *memory)
{
	/* If param2 is a register perform register subtraction */
	if (isRegister(param2))
		reg[(param1[1] - ZERO_ASCII) -1] -= reg[(param2[1] - ZERO_ASCII) -1];
	
	/* If para2 is a constant perform register - const subtraction */
	else if (isConstant(param2))
		reg[(param1[1] - ZERO_ASCII) -1] -= strToInt(param2);
	
	/* If param2 is an address perform register - address subtraction */
	else
		reg[(param1[1] - ZERO_ASCII) -1] -= memory[memToInt(param2)];
}



bool movExecute(string param1, string param2, int *reg, int *memory)
{
	bool flag = true;
	
	
	/* If first parameter is register */
	if (isRegister(param1))
	{
		if (isMemory(param2))
		{
			if (reg[param1[1] - ZERO_ASCII -1] >= 0)
				memory[memToInt(param2)] = reg[param1[1] - ZERO_ASCII -1];
			
			else
			{
				flag = false;
				
				cerr << "Error on run time:" << endl
					 << "Memory error: Memory can not hold negative integers" << endl
					 << "Program halted due to an error" << endl;
			}
		}
		
		else if (isRegister(param2))
			reg[param2[1] - ZERO_ASCII -1] = reg[param1[1] - ZERO_ASCII -1];
		
		else
			reg[param1[1] - ZERO_ASCII -1] = strToInt(param2);
	}
	
	/* Else it must be memory */
	else
	{
		if (isRegister(param2))
			reg[param2[1] - ZERO_ASCII -1] = memory[memToInt(param1)];
		
		else
		{
			if (strToInt(param2) >= 0)
				memory[memToInt(param1)] = strToInt(param2);
			
			else
				cerr << "Error on run time:" << endl
					 << "Memory error: Memory can not hold negative integers" << endl
					 << "Program halted due to an error" << endl;
		}
			
	}
	
	
	return (flag);
}



void jmpExecute(string param1, string param2, int *reg, int& line)
{
	/* Checking if first param is a register or not and then */
	/* doing the jump operation */
	if (isRegister(param1))
	{
		/* If first param is register, it must be 0 to allow jump */
		if (reg[(param1[1] - ZERO_ASCII) -1] == 0)
			line = strToInt(param2)-2;
	}
	
	else
		line = strToInt(param1)-2;
	
	
	return;
}



void jpnExecute(string param1, string param2, int *reg, int& line)
{
	int number;
	
	/* If first param is register, it must be 0 to allow jump */
	if (reg[(param1[1] - ZERO_ASCII) -1] <= 0)
	{
		number = strToInt(param2);
		line = number-2;
	}
		
	
	return;
}



void prnExecute(string param1, int *reg, int *memory)
{
	int address;
	string temp;
	
	
	/* Checking the given parameter and printing it */
	if (isMemory(param1))
	{
		temp = param1;
		temp.erase(0,1);
		address = strToInt(temp);
		
		cout << memory[address] << endl;
	}
	
	else if (isRegister(param1))
		cout << reg[(param1[1] - ZERO_ASCII) -1] << endl;
	
	else
		cout << strToInt(param1) << endl;
	
	
	return;
}



void lineDisplay(string ins, string param1, string param2)
{
	/* Formatting the instruction and parameters and then printing to screen */
	if (param2 == "\0")
		if (param1 == "\0")
			cout << ins;
		
		else
			cout << ins << " " << param1;
	
	else
		cout << ins << " " << param1 << ", " << param2;
}



void registerDisplay(int *reg)
{
	/* Formatting the registers and then printing to screen */
	for (int i=0; i<REG_COUNT; i++)
	{
		cout << "R" << i+1 << " = " << reg[i];
		
		if (i+1 != REG_COUNT)
			cout << ", ";
	}
	
	cout << endl << endl;
	
	
	return;
}



void memoryDisplay(int *mem)
{
	/* Formatting the cells and then printing to screen */
	for (int i=0; i<MEMORY_COUNT; i++)
	{
		cout << "#" << i << " = " << mem[i];
		
		
		if ((i+1) % 10 == 0)
		{
			cout << endl;
		}
		
		else
		{
			cout << ", ";
		}
	}
	
	cout << endl << endl;
	
	
	return;
}



void registerSet(int *reg)
{
	/* Setting all registers as 0 on the start of the program */
	for (int i=0; i<REG_COUNT; i++)
		reg[i] = 0;
	
	
	return;
}



void memorySet(int *mem)
{
	/* Setting all cells as 0 on the start of the program */
	for (int i=0; i<MEMORY_COUNT; i++)
		mem[i] = 0;
	
	
	return;
}



int isRegister(string parameter)
{
	int retVal, length;
	
	
	length = parameter.length();
	/* If parameter's first character is 'R' */
	if (parameter[0] == 'R')
		/* But length is bigger than 2 (2 or more digits) or the register */
		/* number is not in the range of registers return 2 to indicate */
		/* segmentation error */
		if ((length > 2) || ((parameter[1] < '1') || (parameter[1] > '5')))
			retVal = 2;
		
		/* Else return 1 to indicate parameter is a valid register */
		else
			retVal = 1;
	
	/* Else return 0 to indicate it is not a register */	
	else
		retVal = 0;
	
	
	return (retVal);
}



bool isConstant(string parameter)
{
	int length;
	bool retVal=true;
	
	
	/* Taking length of string */
	length = parameter.length();
	
	if (parameter == "\0")
		retVal = false;
	
	/* Searching if there is any characters out of range */
	for (int i=0; i<length; ++i)
		if ((parameter[i] < '0') || (parameter[i] > '9'))
			if (!((parameter[i] == '-') && (i == 0)))
				retVal = false;
	
		
	
	return (retVal);
}



int isMemory(string parameter)
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
			if (address >= 0 && address <= MEMORY_COUNT-1)
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



int strToInt(string parameter)
{
	int length, val=1, sum=0;
	const int cons = 10;
	string temp=parameter;
	bool negative = false;
	
	
	/* Checking if constant is negative and shortening length */
	if (parameter[0] == '-')
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



int memToInt(string parameter)
{
	int length, val=1, sum=0;
	const int cons = 10;
	string temp=parameter;
	
	
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



bool errorCheck(int argCount, char **arguments)
{
	bool flag;
	
	
	/* Initializing first value of flag with checking parameters */
	flag = argumentCheck(argCount, arguments);
	
	/* Checking flag on each next step to prevent printing multiple errors */
	if (flag)
		flag = fileCheck(arguments[1]);
		
	if (flag)
		flag = syntaxCheck();
	
	
	/* Returning flag */
	return (flag);
}



bool argumentCheck(int argCount, char **arguments)
{
	char *mode;
	bool retVal=true;
	
	
	/* If argument count isn't equals to needed count print error message */
	if (argCount != VALID_PARAM)
	{
		/* Finding fitting error message */
		if (argCount > VALID_PARAM)
			cerr << "Error on command line:" << endl
				 << "Parameter error: Too much arguments given" << endl;
		
		else
			cerr << "Error on command line:" << endl
				 << "Parameter error: Too few arguments given" << endl;
		
		
		cerr << "Parameter format should be like "
			 << "'./programName assemblyCodeFileName mode'" << endl;
		
		/* Changing return value to indicate an error */
		retVal = false;
	}
	
	/* If argument count is fine check the mode parameter */
	else
	{
		/* Converting string to integer */
		mode = arguments[argCount-1];
		
		/* Checking for the error and printing message if there is one */
		if ((mode != MODE_0) && (mode != MODE_1) && (mode != MODE_2))
		{
			cerr << "Error on command line:" << endl
				 << "Parameter error: Mode argument must be 0, 1 or 2" << endl;
			
			/* Changing return value to indicate an error */
			retVal = false;
		}
	}
	
	
	return (retVal);
}



bool fileCheck(char *fileName)
{
	ifstream fp;
	bool retVal = true;
	

	/* Opening file to check if it exists */
	fp.open(fileName);
	
	/* Print error message if it doesn't exist */
	if (fp == NULL)
	{
		cerr << "Error on file name:" << endl
			 << "File error: Can not found given file name" << endl;
		retVal = false;
	}
	
	/* Close the file and call file editor if it does */
	else
	{
		fp.close();
		fileEdit(fileName);
	}
	
	
	return (retVal);
}



void fileEdit(char *fileName)
{
	ifstream filePtr;
	ofstream tempPtr;
	string fileLines[MAX_LINE];
	int lineCount=0;
	
	
	/* Opening source file on read mode */
	filePtr.open(fileName);
	
	/* Reading file line by line to an array */
	while (getline(filePtr, fileLines[lineCount]))
	{
		lineCount++;
	}
	
	/* Closing source file */
	filePtr.close();

	
	/* Sending command lines to an editor function to clear */
	/* unwanted characters and make instruction decoding easier */
	formatChanger(fileLines, lineCount);
	
	
	/* Opening target temp file on write mode */
	tempPtr.open(TMP_FILE);
	
	/* Writing array line by line to a file */
	for (int i=0; i<lineCount; i++)
	{
		tempPtr << fileLines[i] << endl;
	}
	
	/* Closing temp file */
	tempPtr.close();
	
	
	return;
}



void formatChanger(string *lines, int lineCount)
{
	int i, j;
	bool comment=false;
	
	
	for (i=0; i<lineCount; i++)
	{
		for (j=0; lines[i][j] != '\0'; j++)
		{
			if (lines[i][j] == '	')
			{
				lines[i].erase(j, 1);
				j -= 1;
			}
			
			if (lines[i][j] == ';')
			{
				comment = true;
			}
			
			if ((lines[i][j] == ' ') && (lines[i][j+1] == ' '))
			{
				lines[i].erase(j, 1);
				j -= 1;
			}
			
			if ((lines[i][j] == ',') && (lines[i][j+1] == ' '))
			{
				lines[i].erase(j+1, 1);
				j -= 1;
			}
			
			if ((lines[i][j] == ',') && (lines[i][j-1] != ' '))
			{
				lines[i].insert(j, " ");
				j -= 1;
			}
			
			if ((lines[i][j] == ';') && (lines[i][j-1] != ' '))
			{
				lines[i].insert(j-1, " ");
				j -= 1;
			}
			
			if ((lines[i][j] == ';') && (lines[i][j+1] == ' '))
			{
				lines[i].erase(j+1, 1);
				j -= 1;
			}
			
			if ((lines[i][j+1] == '\0') && (lines[i][j] == ' '))
			{
				lines[i].erase(j, 1);
				j -= 1;
			}
			
			if (lines[i][j] >= 'a' && lines[i][j] <= 'z')
				lines[i][j] -= 'a'-'A';
		}
		
		if (lines[i][0] == ' ')
			lines[i].erase(0, 1);
		
		lines[i].insert(lines[i].length(), " ");
	}
	
	return;
}



bool syntaxCheck()
{
	string commands[MAX_LINE*3];
	int lineCount, i, result;
	bool retVal, hltCheck=false;
	
	
	/* Taking commands and number of lines */
	retVal = fetch(commands, lineCount);
	
	/* Creating a loop to check each line */
	for (i=0; i<lineCount; i++)
	{
		/* Printing error messages depending to parameters */
		if ((commands[i*3] == HLT) && (retVal))
		{
			if ((commands[(i*3)+1] != "\0") || (commands[(i*3)+2] != "\0"))
			{
				cerr << "Error on line " << i+1 << ":" << endl
					 << "Syntax error: Halt instruction can not take any parameters" << endl;
				retVal = false;
			}
			
			hltCheck = true;
		}
	
		else if ((commands[i*3] == ADD) && (retVal))
		{
			switch (addSubCheck(commands[(i*3)+1], commands[(i*3)+2]))
			{
				case 1: cerr << "Error on line " << i+1 << ":" << endl
							 << "Syntax error: Add instruction needs 2 valid parameters" << endl
							 << "(register,integer)-(register,register)-(register,memory)" << endl;
						retVal = false;
						break;
				
				case 2: cerr << "Error on line " << i+1 << ":" << endl
							 << "Segmentation error: Register or memory is out of range" << endl;
						retVal = false;
						break;
						
				default: break;
			}
		}
	
		else if ((commands[i*3] == SUB) && (retVal))
		{
			switch (addSubCheck(commands[(i*3)+1], commands[(i*3)+2]))
			{
				case 1: cerr << "Error on line " << i+1 << ":" << endl
							 << "Syntax error: Subtract instruction needs 2 valid parameters" << endl
							 << "(register,integer)-(register,register)-(register,memory)" << endl;
						retVal = false;
						break;
				
				case 2: cerr << "Error on line " << i+1 << ":" << endl
							 << "Segmentation error: Register or memory is out of range" << endl;
						retVal = false;
						break;
						
				default: break;
			}
		}
		
		else if ((commands[i*3] == MOV) && (retVal))
		{
			switch (movCheck(commands[(i*3)+1], commands[(i*3)+2]))
			{
				case 1: cerr << "Error on line " << i+1 << ":" << endl
							 << "Syntax error: Move instruction needs 2 valid parameters" << endl
							 << "(register,integer)-(register,register)-(register,memory)-(memory,register)" << endl;
						retVal = false;
						break;
				
				case 2: cerr << "Error on line " << i+1 << ":" << endl
							 << "Segmentation error: Register or memory is out of range" << endl;
						retVal = false;
						break;
						
				default: break;
			}
		}
	
		else if ((commands[i*3] == JMP) && (retVal))
		{
			switch (jmpCheck(commands[(i*3)+1], commands[(i*3)+2]))
			{
				case 1: cerr << "Error on line " << i+1 << ":" << endl
							 << "Jump instruction needs valid parameter(s)" << endl
							 << "(register,integer)-(integer)" << endl;
						retVal = false;
						break;
				
				case 2: cerr << "Error on line " << i+1 << ":" << endl
							 << "Segmentation error: Register is out of range" << endl;
						retVal = false;
						break;
						
				default: break;
			}
		}
		
		else if ((commands[i*3] == JPN) && (retVal))
		{
			switch (jpnCheck(commands[(i*3)+1], commands[(i*3)+2]))
			{
				case 1: cerr << "Error on line " << i+1 << ":" << endl
							 << "JPN instruction needs valid parameter(s)" << endl
							 << "(register,integer)" << endl;
						retVal = false;
						break;
				
				case 2: cerr << "Error on line " << i+1 << ":" << endl
							 << "Segmentation error: Register is out of range" << endl;
						retVal = false;
						break;
						
				default: break;
			}
		}
	
		else if ((commands[i*3] == PRN) && (retVal))
		{
			switch (prnCheck(commands[(i*3)+1], commands[(i*3)+2]))
			{
				case 1: cerr << "Error on line " << i+1 << ":" << endl
							 << "Print instruction needs a valid parameter" << endl
							 << "(register)-(integer)" << endl;
						retVal = false;
						break;
				
				case 2: cerr << "Error on line " << i+1 << ":" << endl
							 << "Segmentation error: Register is not permitted to user" << endl;
						retVal = false;
						break;
						
				default: break;
			}
		}
		
		else
		{
			cerr << "Error on line " << i+1 << ":" << endl
				 << "Syntax error: Unknown instruction" << endl;
			retVal = false;
		}
		
		if (!retVal)
			i = lineCount;
	}
	
	if (retVal && !hltCheck)
	{
		cerr << "Error on instructions:" << endl
			 << "Termination error: HALT instruction can not found on program" << endl;
		retVal = false;
	}
	
	return (retVal);
}



bool fetch(string *commandLines, int& lineCount)
{
	string fileLines[MAX_LINE];
	ifstream tempFile;
	int paramCount;
	bool comment, retVal = true;
	
	/* Opening edited file on read mode */
	tempFile.open(TMP_FILE);
	
	/* Reading file line by line to an array */
	while (getline(tempFile, fileLines[lineCount]))
	{
		lineCount++;
	}
	
	
	/* Creating a loop to fetch all lines to array */
	for (int i=0; i<lineCount; i++)
	{
		comment = commentCheck(fileLines, i);
		paramCount = parameterCounter(fileLines, i, comment);
		
		
		/* Taking instruction from line */
		getInstruction(fileLines, commandLines, i);
		
		/* Checking if the first char after instruction is ',' */
		if (fileLines[i][0] == ',')
		{
			cerr << "Error on line " << i+1 << ":\nSyntax error: ',' operator used without any pre-parameter" << endl;
			
			retVal = false;
			i = lineCount;
		}
		
		
		/* Taking parameters from line */
		getParameters(fileLines, commandLines, i, paramCount, comment);
	}
	
	
	/* Returning number of the lines */
	return (retVal);
}



int fetch(string *commandLines)
{
	string fileLines[MAX_LINE];
	ifstream tempFile;
	int lineCount = 0, paramCount;
	bool comment;
	
	/* Opening edited file on read mode */
	tempFile.open(TMP_FILE);
	
	/* Reading file line by line to an array */
	while (getline(tempFile, fileLines[lineCount]))
	{
		lineCount++;
	}


	/* Creating a loop to fetch all lines to array */
	for (int i=0; i<lineCount; i++)
	{
		comment = commentCheck(fileLines, i);
		paramCount = parameterCounter(fileLines, i, comment);
		
		
		/* Taking instruction from line */
		getInstruction(fileLines, commandLines, i);		
		
		/* Taking parameters from line */
		getParameters(fileLines, commandLines, i, paramCount, comment);
	}
	
	
	/* Returning number of the lines */
	return (lineCount);
}



bool commentCheck(string *commandList, int lineNumber)
{
	bool comment=false;
	
	/* Looking for the ';' to understand if there are characters to ignore */
	for (int i=0; commandList[lineNumber][i]!='\0'; ++i){
		
		if (commandList[lineNumber][i] == ';'){
			comment = true;
		}
	}
	
	
	/* Returning the result */
	return (comment);
}



int parameterCounter(string *commandList, int lineNumber, bool comment)
{
	int parameter=1;
	
	
	/* If line has comment, look for ',' character and count until comments */
	if (comment)
		for (int i=0; commandList[lineNumber][i]!=';'; ++i){
			if (commandList[lineNumber][i] == ',')
				++parameter;
		}
	/* If there isn't look until null character */
	else
		for (int i=0; commandList[lineNumber][i]!='\0'; ++i){
			if (commandList[lineNumber][i] == ',')
				++parameter;
		}
	
	/* Returning total number of parameters */
	return (parameter);
}



void getInstruction(string *lineList, string *commandList, int lineNumber)
{
	int index, i;
	
	
	/* Multiplying line number with 3 to find i'th location of instruction */
	index = lineNumber*3;
	
	/* Creating a loop to find the location of first witespace */
	for (i=0; lineList[lineNumber][i]!=' '; ++i)
	;
	
	/* Taking first word as instruction with using substr */
	commandList[index] = lineList[lineNumber].substr(0,i);
	
	/* Deleting taken characters from main list */
	lineList[lineNumber].erase(0,i+1);
	
	
	return;
}



bool getParameters(string *lineList, string *commandList, int lineNumber, int paramCount, bool comment)
{
	int i, index, length;
	bool retVal=true;
	
	
	/* Multiplying line number with 3 and adding 1 to */
	/* find first parameter location of the i'th line */
	index = lineNumber*3 + 1;
	
	
	/* Taking param until the end space and setting second param as NULL */
	if (paramCount == 1)
	{
		if (comment)
		{
			for (i=0; lineList[lineNumber][i]!=' '; i++)
			;
		}
		
		else
		{
			for (i=0; lineList[lineNumber][i]!=' '; i++)
			;
		}
		
		commandList[index] = lineList[lineNumber].substr(0,i);
		commandList[index+1] = "\0";
		lineList[lineNumber].erase(0,i);
		
		/* Halt instruction can not take parameters, setting them as null */
		if (commandList[lineNumber*3] == HLT)
		{
			commandList[lineNumber*3+1] = "\0";
			commandList[lineNumber*3+2] = "\0";
		}
	}
	
	else if (paramCount == 2)
	{
		for (i=0; lineList[lineNumber][i]!=','; i++)
		;
		
		commandList[index] = lineList[lineNumber].substr(0,i-1);
               
		lineList[lineNumber].erase(0,i+1);
               
		index ++;
		
		if (comment)
		{
			for (i=0; lineList[lineNumber][i]!=';'; i++)
			;
		}
		
		else
		{
			for (i=0; lineList[lineNumber][i]!='\0'; i++)
			;
		}

		commandList[index] = lineList[lineNumber].substr(0,i);
		lineList[lineNumber].erase(0,i);
		
		length = commandList[index].length();
		
		if (commandList[index][length-1] == ' ')
		{
			commandList[index].erase(length-1);
		}
		
		if (commandList[index] == "\0")
		{
			cerr << "Error on line " << lineNumber+1 << ":\nSyntax error: ',' operator used without any post-parameter" << endl;
			retVal = false;
		}
	}
	
	else 
	{
		cerr << "Error on line " << lineNumber+1 << ":\nSyntax error: Too much parameters for this instruction" << endl;
		retVal = false;
	}
	
	
	return (retVal);
}



int movCheck(string param1, string param2)
{
	int retVal, reg, memory;
	bool constant;
	
	
	/* First param can be register or memory */
	reg = isRegister(param1);
	memory = isMemory(param1);
	
	/* Checking the type of first parameter */
	if (reg || memory)
	{
		/* Second param can be register, memory or a constant */
		reg = isRegister(param2);
		memory = isMemory(param2);
		constant = isConstant(param2);
		
		/* Return 2 if register or memory is out of range */
		if (reg == 2 || memory == 2)
			retVal = 2;
		
		/* If condition is provided return 0 as correct flag */
		else if (reg || memory || constant)
			retVal = 0;
		
		else
			retVal = 1;
	}
	
	else
		retVal = 1;
	
	
	return (retVal);
}



int addSubCheck(string param1, string param2)
{
	int retVal, reg, memory;
	bool constant;
	
	
	/* First param must be register */
	reg = isRegister(param1);
	
	if (reg)
	{
		/* Second param can be register or a constant */
		reg = isRegister(param2);
		constant = isConstant(param2);
		memory = isMemory(param2);
		
		/* If condition is provided return 0 as correct flag */
		if (reg || constant || memory)
			retVal = 0;
		
		/* Return 2 if register or memory is out of range */
		else if (reg == 2 || memory == 2)
			retVal = 2;
		
		/* Return error 1 as syntax flag */
		else
			retVal = 1;
	}
	
	/* If it isn't a register return 1 as syntax flag */
	else
		retVal = 1;
	
	
	return (retVal);
}



int jmpCheck(string param1, string param2)
{
	int retVal, flag;
	
	
	flag = isRegister(param1);
	
	/* If there are two parameters, first must be register and second must be */
	/* integer (line number). If there is one parameter it must be integer */
	if (flag == 0)
	{
		if (isConstant(param1) && param2 == "\0" && param1[0] != '-')
			retVal = 0;
		
		else
			retVal = 1;
	}
	
	else if (flag == 1)
	{
		if (isConstant(param2))
			retVal = 0;
		
		else
			retVal = 1;
	}	
	
	else
		retVal = flag;
	
	
	return (retVal);
}



int jpnCheck(string param1, string param2)
{
	int retVal, flag;
	
	
	flag = isRegister(param1);
	
	/* If there are two parameters, first must be register and second must be */
	/* integer (line number). If there is one parameter it must be integer */
	if (flag == 1)
	{
		if (isConstant(param2) && param2[0] != '-')
			retVal = 0;
		
		else
			retVal = 1;
	}
	
	else if (flag == 0)
		retVal = 1;	
	
	else
		retVal = flag;
	
	
	return (retVal);
}



int prnCheck(string param1, string param2)
{
	int retVal, reg, memory;
	bool constant;
	
	
	reg = isRegister(param1);
	memory = isMemory(param1);
	constant = isConstant(param1);
	
	
	/* There must be only 1 parameter. A register, memory address or constant */
	if (param2 != "\0")
		retVal = 1;
	
	else
	{
		if (reg == 1 || memory == 1 || constant)
			retVal = 0;
		
		else
			retVal = 1;
	}
	
	return (retVal);
}

/* End of main.cpp */

