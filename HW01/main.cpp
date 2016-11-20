/*
 * main.cpp
 * This 1st homework for CSE241 of Gebze Technical University
 * Homework made by Deniz Can Erdem Yılmaz - 151044001
 * 09.10.2016
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
const int MAX_LINE = 200;
const int MODE_0 = 0;
const int MODE_1 = 1;
const char* TMP_FILE = "tmp.txt";
const string ADD = "ADD";
const string SUB = "SUB";
const string MOV = "MOV";
const string JMP = "JMP";
const string PRN = "PRN";
const string HLT = "HLT";



/* Function prototype(s) */
/* Main instruction cycle function. Makes function calls */
void decode(int mode);

/* Overloaded fetch function, reads cleared temp file for execution */
int fetch(string *commandLines);

/* Instruction specialized execute functions */
void addExecute(string param1, string param2, int *reg);
void subExecute(string param1, string param2, int *reg);
void movExecute(string param1, string param2, int *reg);
void jmpExecute(string param1, string param2, int *reg, int& line, int lineCount);
void prnExecute(string param1, int *reg);


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
int addSubMovCheck(string param1, string param2);
int jmpCheck(string param1, string param2);
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

/* Converts string to decimal integer */
int strToInt(string parameter);

/* Prints all registers to screen */
void registerDisplay(int *reg);

/* Sets all registers as 0 */
void registerSet(int *reg);

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
	string fileLines[MAX_LINE], commands[MAX_LINE*3];
	
	
	/* Setting all registers as 0 and fetching lines from file */
	registerSet(registers);
	lineCount = fetch(commands);
	
	/* Creating a instruction cycle until encountering HALT command */
	while (exit)
	{
		/* Setting parameter indexes for command array */
		arg0 = (lineCounter*3);
		arg1 = (lineCounter*3) + 1;
		arg2 = (lineCounter*3) + 2;
		
		
		/* Checking mode to print instruction first */
		if (mode == 1 && commands[arg0] != HLT)
			lineDisplay(commands[arg0], commands[arg1], commands[arg2]);
		
		/* Checking if line counter is valid. Prints error message if */
		/* current line number is over the file line */
		if (lineCounter >= lineCount){
			cerr << "Error on run time:" << endl
				 << "Line count error: Couldn't find the current line on file: " 
				 << lineCounter+1 << endl;
				
			/* Setting exit flag as false to break loop */
			exit = false;
		}
		
		/* Checking and calling function suitable with instruction */ 
		else if (commands[arg0] == ADD)
			addExecute(commands[arg1], commands[arg2], registers);
		
		else if (commands[arg0] == SUB)
			subExecute(commands[arg1], commands[arg2], registers);
		
		else if (commands[arg0] == MOV)
			movExecute(commands[arg1], commands[arg2], registers);
		
		else if (commands[arg0] == JMP)
			jmpExecute(commands[arg1], commands[arg2], registers, lineCounter, lineCount);
		
		else if (commands[arg0] == PRN)
			prnExecute(commands[arg1], registers);
		
		else if (commands[arg0] == HLT){
			/* Giving information, printing all registers and quitting */
			cout << "Program halted without any errors" << endl;
			registerDisplay(registers);
			exit = false;
		}
		
		/* Printing registers after execution */
		if (mode == 1 && commands[arg0] != HLT)
		{
			registerDisplay(registers);
			cout << endl;
		}
		
		/* Increasing line counter for next step */
		++lineCounter;
	}
	
	
	return;
}



void addExecute(string param1, string param2, int *reg)
{
	/* Checking if second param is a register or not and then */
	/* calculating the addition */
	if (isRegister(param2))
		reg[(param1[1] - ZERO_ASCII) -1] += reg[(param2[1] - ZERO_ASCII) -1];
	
	else
		reg[(param1[1] - ZERO_ASCII) -1] += strToInt(param2);
	
	
	return;
}



void subExecute(string param1, string param2, int *reg)
{
	/* Checking if second param is a register or not and then */
	/* calculating the subtraction */
	if (isRegister(param2))
		reg[(param1[1] - ZERO_ASCII) -1] -= reg[(param2[1] - ZERO_ASCII) -1];
	
	else
		reg[(param1[1] - ZERO_ASCII) -1] -= strToInt(param2);
	
	
	return;
}



void movExecute(string param1, string param2, int *reg)
{
	/* Checking if second param is a register or not and then */
	/* moving the value of it to first one */
	if (isRegister(param2))
		reg[(param2[1] - ZERO_ASCII) -1] = reg[(param1[1] - ZERO_ASCII) -1];
	
	else
		reg[(param1[1] - ZERO_ASCII) -1] = strToInt(param2);
	
	
	return;
}



void jmpExecute(string param1, string param2, int *reg, int& line, int lineCount)
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



void prnExecute(string param1, int *reg)
{
	/* Printing given register or constant */
	
	if (isRegister(param1))
		cout << reg[(param1[1] - ZERO_ASCII) -1] << endl;
	
	else
		cout << strToInt(param1) << endl;
}



void lineDisplay(string ins, string param1, string param2)
{
	/* Formatting the instruction and parameters and then printing to screen */
	if (param2 == "\0")
		if (param1 == "\0")
			cout << ins << " – ";
		
		else
			cout << ins << " " << param1 << " – ";
	
	else
		cout << ins << " " << param1 << ", " << param2 << " – ";
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
	
	cout << endl;
	
	
	return;
}



void registerSet(int *reg)
{
	/* Setting all registers as 0 on the start of the program */
	for (int i=0; i<REG_COUNT; i++)
		reg[i] = 0;
	
	
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



int strToInt(string parameter)
{
	int length, cons=10, val=1, sum=0;
	
	
	length = parameter.length();
	/* Multiplying each digit with its base value */
	for (int i=length-1; i>=0; i--)
	{
		sum += ((parameter[i] - ZERO_ASCII) * val);
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
	int mode;
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
		mode = strToInt(arguments[argCount-1]);
		
		
		/* Checking for the error and printing message if there is one */
		if ((mode != MODE_0) && (mode != MODE_1))
		{
			cerr << "Error on command line:" << endl
				 << "Parameter error: Mode argument must be 1 or 0" << endl;
			
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
			switch (addSubMovCheck(commands[(i*3)+1], commands[(i*3)+2]))
			{
				case 1: cerr << "Error on line " << i+1 << ":" << endl
							 << "Syntax error: Add instruction needs 2 valid parameters" << endl
							 << "(register,integer)-(register,register)" << endl;
						retVal = false;
						break;
				
				case 2: cerr << "Error on line " << i+1 << ":" << endl
							 << "Segmentation error: Register is not permitted to user" << endl;
						retVal = false;
						break;
						
				default: break;
			}
		}
	
		else if ((commands[i*3] == SUB) && (retVal))
		{
			switch (addSubMovCheck(commands[(i*3)+1], commands[(i*3)+2]))
			{
				case 1: cerr << "Error on line " << i+1 << ":" << endl
							 << "Syntax error: Subtract instruction needs 2 valid parameters" << endl
							 << "(register,integer)-(register,register)" << endl;
						retVal = false;
						break;
				
				case 2: cerr << "Error on line " << i+1 << ":" << endl
							 << "Segmentation error: Register is not permitted to user" << endl;
						retVal = false;
						break;
						
				default: break;
			}
		}
		
		else if ((commands[i*3] == MOV) && (retVal))
		{
			switch (addSubMovCheck(commands[(i*3)+1], commands[(i*3)+2]))
			{
				case 1: cerr << "Error on line " << i+1 << ":" << endl
							 << "Syntax error: Move instruction needs 2 valid parameters" << endl
							 << "(register,integer)-(register,register)" << endl;
						retVal = false;
						break;
				
				case 2: cerr << "Error on line " << i+1 << ":" << endl
							 << "Segmentation error: Register is not permitted to user" << endl;
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
							 << "Segmentation error: Register is not permitted to user" << endl;
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



int addSubMovCheck(string param1, string param2)
{
	int retVal, flag;
	
	
	flag = isRegister(param1);
	/* First param must be register */
	
	if (flag == 0)
		retVal = 1;
	
	else if (flag == 2)
		retVal = flag;
	
	else
	{
		flag = isRegister(param2);
		
		/* Second can be either register or constant */
		if (flag == 2)
			retVal = flag;
			
		else if ((flag == 1) || isConstant(param2))
			retVal = 0;
		
		else
			retVal = 1;
	}
	
	
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
		if (isConstant(param1) && (param2 == "\0"))
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



int prnCheck(string param1, string param2)
{
	int retVal=0, flag;
	
	
	flag = isRegister(param1);
	/* There must be only 1 parameter. A register or a constant */
	if (flag == 0)
		if (isConstant(param1) && (param2 == "\0"))
			retVal = 0;
		
		else
			retVal = 1;
	
	else if (flag == 1)
		if (param2 == "\0")
			retVal = 0;
		
		else
			retVal = 1;
	
	else
		retVal = flag;
	
	
	return (retVal);
}

/* End of main.cpp */

