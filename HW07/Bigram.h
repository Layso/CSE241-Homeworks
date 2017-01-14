/*
 * Bigram.h is the header file of Bigram class
 * Contains Bigram class prototype
 * 
 * This is the base class of bigram homework. It includes pure virtual 
 * functions to override on derivated classes to use later on and no data
 * members. Function definitions given on homework definition
 *
 * This class coded for the homework 7 of GTU's CSE241 lecture, Fall 2016
 * File belongs to Deniz Can Erdem Yılmaz - 151044001
 * 
 * Creation date   - 16.12.2016
 * Completion date - 18.12.2016
 * Dead-line       - 30.12.2016 / 23:55
 */

/* ifndef Shield */
#ifndef BIGRAM_H
#define BIGRAM_H

/* Include(s) */
#include <string>
#include <utility>
#include <iostream>

/* Using Statement(s) */
using std::string;
using std::pair;
using std::ostream;



/* Class Definition */
template <typename T>
class Bigram
{
public:
	virtual void readFile(string fileName) = 0;
	// readFile: Reads the file and calculates the bigrams
	
	virtual int numGrams() const = 0;
	// numGrams: Returns the total number of bigrams found in input file
	
	virtual int numOfGrams(const T& first, const T& second) const = 0;
	// numOfGrams: Returns the number of bigrams of given pair in input file
	
	virtual pair<T,T> maxGrams() const = 0;
	// maxGrams: Returns the most occured bigram as std::pair
	
	virtual void toString(ostream& out) const = 0;
	// toString: This function will be used to print any Bigram object to screen
	// Operator << can not be inherited hence this function will force every
	// derived class to have print function. Then it can be used in << operator
	
	friend ostream& operator << (ostream& out, const Bigram& obj)
	{
		obj.toString(out);
		return out;
	}

private:
	//No private members for base class
};

#endif
/* End of Bigram.h */
