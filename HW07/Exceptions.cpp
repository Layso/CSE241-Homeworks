/*
 * Exceptions.cpp
 * Contains Exceptions class function implementations
 * 
 * This file contains an exception derived class to handle some errors
 * that Bigram derived classes may encounter. Exceptions class includes many
 * error case informations to throw when needed
 *
 * This class coded for the homework 7 of GTU's CSE241 lecture, Fall 2016
 * File belongs to Deniz Can Erdem Yılmaz - 151044001
 * 
 * Creation date   - 30.12.2016
 * Completion date - 30.30.2016
 * Dead-line       - 30.12.2016 / 23:55
 */

/* Include(s) */
#include "Exceptions.h"

/* Implementing namespace cen */
namespace cen
{
	Exceptions ERROR;

	/* Error codes */
	const int INITIALIZE_ERROR = 0;
	const int DATA_TYPE_ERROR = 1;
	const int FILE_OPEN_ERROR = 2;
	const int FILE_INPUT_ERROR = 3;
	const int FEW_INPUT_ERROR = 4;
	const int NO_DATA_ERROR = 5;
}



/* Function Implementation(s) */
Exceptions :: Exceptions() : Exceptions(-1)
{
	/* Preparing the error messages */
	INITIALIZE_ERROR = "Objects must initialize with int param constructor.";
	DATA_TYPE_ERROR = "Data type can only be 1-2-3";
	FILE_OPEN_ERROR = "Given file could not opened.";
	FILE_INPUT_ERROR = "Bad data occured.";
	FEW_INPUT_ERROR = "Input file does not include enough data.";
	NO_DATA_ERROR = "There is no data to work on. Call readFile() first";
	ERROR_ERROR = "Unknown error code.";
}



Exceptions :: Exceptions(int code) : errorCode(code)
{/* Intentionally blank */}



const char* Exceptions :: what() const noexcept
{
	/* Returning message by the given error code */
	switch (errorCode)
	{
		case 0: return INITIALIZE_ERROR;
		case 1: return DATA_TYPE_ERROR;
		case 2: return FILE_OPEN_ERROR;
		case 3: return FILE_INPUT_ERROR;
		case 4: return FEW_INPUT_ERROR;
		case 5: return NO_DATA_ERROR;
		default:return ERROR_ERROR;
	}
}



Exceptions& Exceptions :: operator () (int code)
{
	errorCode = code;
	return *this;
}

/* End of Exceptions.cpp */
