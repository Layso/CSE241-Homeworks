/*
 * BigramDyn.h is the header file of BigramDyn class
 * Contains BigramDyn class prototype
 * 
 * This will be a class derivated from Bigram base class to work on bigrams.
 * BigramDyn will use dynamically allocated memory for the datas it will contain
 *
 * This class coded for the homework 7 of GTU's CSE241 lecture, Fall 2016
 * File belongs to Deniz Can Erdem Yılmaz - 151044001
 * 
 * Creation date   - 18.12.2016
 * Completion date - 30.30.2016
 * Dead-line       - 30.12.2016 / 23:55
 */

/* ifndef Shield */
#ifndef BIGRAMDYN_H
#define BIGRAMDYN_H

/* Include(s) */
#include <string>
#include <utility>
#include <iostream>
#include "Bigram.h"

/* Using Statement(s) */
using std::string;
using std::pair;
using std::ostream;



/* Class Definition */
template <typename T>
class BigramDyn: public Bigram<T>
{
public:
	BigramDyn();							//No parameter constructor
	BigramDyn(int type);					//One parameter constructor
	BigramDyn(const BigramDyn<T>& other);	//Copy constructor
	~BigramDyn();							//Destructor
	
	void readFile(const string inputFile) override;
	// readFile: Reads the file and calculates the bigrams
	
	int numGrams() const override;
	// numGrams: Returns the total number of bigrams found in input file
	
	int numOfGrams(const T& first, const T& second) const override;
	// numOfGrams: Returns the number of bigrams of given pair in input file

	pair<T,T> maxGrams() const override;
	// maxGrams: Returns the most occured bigram as std::pair
	
	void toString(ostream& out) const override;
	// toString: Prints the bigrams and their counts that object holds

	BigramDyn<T>& operator = (const BigramDyn<T>& other);
	// Assignment operator overload needed due to pointers
	

private:
	/* Data members */
	T *data;
	T **bigrams;
	int *counts;
	int size;
	int cap;
	int sizeBi;
	int capBi;
	int gram;
	int dataType;
	string fileName;
	
	/* Private mutator functions to manipulate data members */
	void addElementData(const T& newElement);
	void addElementBigram(const T& first, const T& second);
	void bigramCalculator();
	void increaseCapacity();
	void increaseCount(const T& first, const T& second);
	
	/* Private accessor functions to work on class */
	bool bigramSearch(const T& first, const T& second) const;
};

#endif
/* End of BigramDyn.h */
