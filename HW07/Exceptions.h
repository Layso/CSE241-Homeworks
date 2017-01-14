/*
 * Exceptions.h is the header file of Exceptions class
 * Contains Exceptions class prototype
 * 
 * This file contains an exception derived class to handle some errors
 * that Bigram derived classes may encounter. Exceptions class includes many
 * error case informations to throw when needed
 *
 * This class coded for the homework 7 of GTU's CSE241 lecture, Fall 2016
 * File belongs to Deniz Can Erdem Yılmaz - 151044001
 * 
 * Creation date   - 30.12.2016
 * Completion date - 30.12.2016
 * Dead-line       - 30.12.2016 / 23:55
 */



#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H



/* Include(s) */
#include <exception>

/* Using statement(s) */
using std::exception;



/* Class Definition */
class Exceptions : public exception
{
public:
	Exceptions(); 								//No param constructor
	Exceptions(int code);						//int param constructor
	const char* what() const noexcept override; //Message returner
	Exceptions& operator () (int code);			//Operator to specify error code

private:
	int errorCode;
	const char* INITIALIZE_ERROR;
	const char* DATA_TYPE_ERROR;
	const char* FILE_OPEN_ERROR;
	const char* FILE_INPUT_ERROR;
	const char* FEW_INPUT_ERROR;
	const char* NO_DATA_ERROR;
	const char* ERROR_ERROR;
};



/* Namespace Definition */
namespace cen
{
	extern Exceptions ERROR;
	
	extern const int INITIALIZE_ERROR;
	extern const int DATA_TYPE_ERROR;
	extern const int FILE_OPEN_ERROR;
	extern const int FILE_INPUT_ERROR;
	extern const int FEW_INPUT_ERROR;
	extern const int NO_DATA_ERROR;
}

#endif
/* End of Exceptions.h */
