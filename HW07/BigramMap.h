/*
 * BigramMap.h is the header file of BigramMap class
 * Contains BigramMap class prototype
 * 
 * This will be a class derivated from Bigram base class to work on bigrams.
 * BigramMap will use STL for the datas it will contain
 *
 * This class coded for the homework 7 of GTU's CSE241 lecture, Fall 2016
 * File belongs to Deniz Can Erdem Yılmaz - 151044001
 * 
 * Creation date   - 26.12.2016
 * Completion date - 30.30.2016
 * Dead-line       - 30.12.2016 / 23:55
 */

/* ifndef Shield */
#ifndef BIGRAMMAP_H
#define BIGRAMMAP_H

/* Include(s) */
#include <string>
#include <utility>
#include <map>
#include <vector>
#include <iostream>
#include "Bigram.h"

/* Using Statements(s) */
using std::string;
using std::vector;
using std::pair;
using std::map;
using std::ostream;
using namespace cen;



/* Class Definition */
template <typename T>
class BigramMap: public Bigram<T>
{
public:
	BigramMap();			//No parameter constructor
	BigramMap(int type);	//One parameter constructor
	
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

private:
	/* Data members */
	vector <T> data;
	map <pair <T,T>, int> bigrams;
	int gram;
	int dataType;
	string fileName;
	
	/* Private mutator functions to manipulate data members */
	void bigramCalculator();
	void addElement(const T& first, const T& second);
	void increaseCount(const T& first, const T& second);
	
	/* Private accessor functions to work on class */
	bool bigramSearch(const T& first, const T& second) const;
};

#endif
/* End of BigramMap.h */
