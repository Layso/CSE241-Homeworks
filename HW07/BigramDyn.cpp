/*
 * BigramDyn.cpp
 * Contains BigramDyn function implementations
 * 
 * This will be a class derivated from Bigram base class to work on bigrams
 * BigramDyn will use dynamically allocated memory for the datas it will contain
 *
 * This class coded for the homework 7 of GTU's CSE241 lecture, Fall 2016
 * File belongs to Deniz Can Erdem Yılmaz - 151044001
 * 
 * Creation date   - 18.12.2016
 * Completion date - 30.12.2016
 * Dead-line       - 30.12.2016 / 23:55
 */

/* Include(s) */
#include <iostream>
#include <fstream>
#include "BigramDyn.h"
#include "Exceptions.h"

/* Using statement(s) */
using std::cout;
using std::endl;
using std::ifstream;
using std::ostream;
using namespace cen;



/* Function Implementation(s) */
template <typename T>
BigramDyn<T> :: BigramDyn()
{
	throw ERROR(INITIALIZE_ERROR);
}



template <typename T>
BigramDyn<T> :: BigramDyn(int type) : dataType(type), cap(2), size(0),
sizeBi(0), capBi(2), gram(2), fileName("") /*EXCEPTION, WRONG DATA TYPE */
{
	/* Checking data tyoe error */
	switch (type)
	{
		case 1:
		case 2:
		case 3: break;
		default: throw ERROR(DATA_TYPE_ERROR);
	}
	
	
	/* Capacity is 2, the least number of elements needed for a bigram */
	/* Size is 0, which means array is clean for now */
	/* Allocating memory for data and bigram arrays */
	data = new T[cap];
	
	bigrams = new T*[capBi];
	for (int i=0; i<capBi; ++i)
		bigrams[i] = new T[gram];
	
	counts = new int[capBi];
}



template <typename T>
BigramDyn<T> :: BigramDyn(const BigramDyn<T>& other)
{
	/* Constant basic variables */
	const int ZERO = 0;
	const int FIRST = 0;
	const int SECOND = 1;
	
	
	/* Copying data variables */
	size = other.size;
	cap = other.cap;
	sizeBi = other.sizeBi;
	capBi = other.capBi;
	gram = other.gram;
	dataType = other.dataType;
	fileName = other.fileName;
	
	
	/* Handling with pointer allocation/deallocation */
	data = new T[other.cap];
	counts = new int[other.capBi];
	bigrams = new T*[other.capBi];
	
	for (int i=ZERO; i<capBi; ++i)
		bigrams[i] = new T[gram];
	
	
	for (int i=ZERO; i<sizeBi; ++i)
	{
		bigrams[i][FIRST] = other.bigrams[i][FIRST];
		bigrams[i][SECOND] = other.bigrams[i][SECOND];
		counts[i] = other.counts[i];
	}
	
	for (int i=ZERO; i<size; ++i)
	{
		data[i] = other.data[i];
	}
}



template <typename T>
BigramDyn<T> :: ~BigramDyn()
{
	/* Constant basic variables */
	const int ZERO = 0;
	
	
	for (int i=ZERO; i<capBi; ++i)
		delete [] bigrams[i];
	
	delete [] bigrams;
	delete [] counts;
	delete [] data;
}



template <typename T>
BigramDyn<T>& BigramDyn<T> :: operator = (const BigramDyn<T>& other)
{
	/* Constant basic variables */
	const int ZERO = 0;
	const int FIRST = 0;
	const int SECOND = 1;
	
	if (this != &other)
	{
		/* Deleting old arrays */
		for (int i=ZERO; i<capBi; ++i)
			delete [] bigrams[i];
	
		delete [] bigrams;
		delete [] counts;
		delete [] data;
		
		/* Copying data variables */
		size = other.size;
		cap = other.cap;
		sizeBi = other.sizeBi;
		capBi = other.capBi;
		gram = other.gram;
		dataType = other.dataType;
		fileName = other.fileName;
	
		/* Handling with pointer allocation/deallocation */
		data = new T[other.cap];
		counts = new int[other.capBi];
		bigrams = new T*[other.capBi];
	
		for (int i=ZERO; i<capBi; ++i)
			bigrams[i] = new T[gram];
	
	
		for (int i=ZERO; i<sizeBi; ++i)
		{
			bigrams[i][FIRST] = other.bigrams[i][FIRST];
			bigrams[i][SECOND] = other.bigrams[i][SECOND];
			counts[i] = other.counts[i];
		}
	
		for (int i=ZERO; i<size; ++i)
		{
			data[i] = other.data[i];
		}
	}
	
	
	return *this;
}



template <typename T>
void BigramDyn<T> :: readFile(const string inputFile)
{
	/* Data variables for function */
	ifstream file;
	T input;
	
	
	/* Opening file and saving file name */
	file.open(inputFile);
	fileName=inputFile;
	
	/* Checking if there is an error during file opening */
	if (file == nullptr)
		throw ERROR(FILE_OPEN_ERROR);
	
	/* Reading data to array */
	while (file>>input)
		addElementData(input);
	
	/* Checking if any bad data has found */
	if (!file.eof())
		throw ERROR(FILE_INPUT_ERROR);
	
	/* Checking if there is an error after reading file */
	if (size < gram)
		throw ERROR(FEW_INPUT_ERROR);
	
	
	file.close();
	bigramCalculator();
}



template <typename T>
int BigramDyn<T> :: numGrams() const
{
	/* Constant basic variables */
	const int ZERO = 0;
	
	/* Data variables for function */
	int count = ZERO;
	
	
	/* Checking for errors */
	if (sizeBi == ZERO)
		throw ERROR(NO_DATA_ERROR);
	
	
	/* Counting all bigrams */
	for (int i=0; i<sizeBi; ++i)
		count += counts[i];
	
	
	return count;
}



template <typename T>
int BigramDyn<T> :: numOfGrams(const T& first, const T& second) const
{
	/* Constant basic variables */
	const int ZERO = 0;
	const int FIRST = 0;
	const int SECOND = 1;
	
	/* Needed variables for function */
	int count=0;
	
	
	/* Checking for errors */
	if (sizeBi == ZERO)
		throw ERROR(NO_DATA_ERROR);
	
	
	/* Searching given pair in bigram array. Returning the count value */
	/* of same index on counts array if found. Else it will return 0 */
	for (int i=0; i<sizeBi; ++i)
		if ((bigrams[i][FIRST] == first) && (bigrams[i][SECOND] == second))
			count = counts[i];
	
	
	return count;
}



template <typename T>
pair<T,T> BigramDyn<T> :: maxGrams() const
{
	/* Constant basic variables */
	const int ZERO = 0;
	const int ONE = 1;
	const int FIRST = 0;
	const int SECOND = 1;
	
	/* Needed variables for function */
	int max=0;
	int index=-1;
	pair <T,T> retPair;


	/* Checking for errors */
	if (sizeBi == ZERO)
		throw ERROR(NO_DATA_ERROR);
		
		
	for (int i=0; i<sizeBi; ++i)
		if (counts[i] > max)
		{
			index = i;
			max = counts[i];
		}
	
	/* Preparing return pair */
	retPair.first = bigrams[index][FIRST];
	retPair.second = bigrams[index][SECOND];
	
	
	return retPair;
}



template <typename T>
void BigramDyn<T> :: toString(ostream& out) const
{
	/* Constant basic variables */
	const int ONE = 1;
	const int FIRST = 0;
	const int SECOND = 1;
	const int VALID = -1;
	
	/* Needed variables for function */ 
	int *sort = new int[sizeBi];
	int count;
	
	
	/* Initializing each element as valid spaces for index placement */
	for (int i=0; i<sizeBi; ++i)
		sort[i] = VALID;
	
	/* Counting how many elements are there larger than selected element for */
	/* each element of counts array to sort them */
	for (int i=0; i<sizeBi; ++i)
	{
		int index = 0;
		
		for (int k=0; k<sizeBi; ++k)
			if (counts[i] < counts[k])
				++index;
		
		/* If there are equal counts then they will show same index. To */
		/* prevent the misplaces, increasing index until a valid one found */
		while (sort[index] != VALID)
			++index;
		
		sort[index] = i;
	}
	
	
	/* Printing bigrams from bigger to lesser */
	for (int i=0; i<sizeBi; ++i)
		out << "Pair: [" << bigrams[sort[i]][FIRST] << "," 
			<< bigrams[sort[i]][SECOND] << "]    Count: "
			<< counts[sort[i]] << endl;
	
	delete [] sort;
}



template <typename T>
void BigramDyn<T> :: addElementData(const T& newElement)
{
	/* Constant basic variable */
	const int DOUBLE = 2;
	
	
	/* Checking if data array has enough space */
	if (size == cap)
	{
		/* Increasing capacity if it does not */
		cap *= DOUBLE;
		T *tempData = new T[cap];
		
		for (int i=0; i<size; ++i)
			tempData[i] = data[i];
		
		delete [] data;
		data = tempData;
	}
	

	/* Assigning new element to the data array */
	data[size] = newElement;
	++size;
}



template <typename T>
void BigramDyn<T> :: increaseCapacity()
{
	/* Constant basic variables */
	const int FIRST = 0;
	const int SECOND = 1;
	const int DOUBLE = 2;
	
	
    /* Increasing capacity */
	capBi *= DOUBLE;
	
	/* Creating temporary arrays */
	T **tempBigrams = new T*[capBi];
	int *tempCounts = new int[capBi];
	
	for (int i=0; i<capBi; ++i)
		tempBigrams[i] = new T[gram];
	
	/* Backing up the old arrays */
	for (int i=0; i<sizeBi; ++i)
	{
		tempBigrams[i][FIRST] = bigrams[i][FIRST];
		tempBigrams[i][SECOND] = bigrams[i][SECOND];
		tempCounts[i] = counts[i];
	}
	
	
	/* Deleting old arrays */
	for (int i=0; i<sizeBi; ++i)
		delete [] bigrams[i];
			
	delete [] bigrams;
	delete [] counts;
	
	/* Assigning increased sized arrays to data members */
	bigrams = tempBigrams;
	counts = tempCounts;
}




template <typename T>
void BigramDyn<T> :: addElementBigram(const T& first, const T& second)
{
	/* Constant basic variables */
	const int FIRST = 0;
	const int SECOND = 1;
	
	
	/* Checking if array is full to increase size */
	if (sizeBi == capBi)
		increaseCapacity();
	
	/* Adding new elements to the array */
	bigrams[sizeBi][FIRST] = first;
	bigrams[sizeBi][SECOND] = second;
	counts[sizeBi] = 1;
	++sizeBi;
}



template <typename T>
void BigramDyn<T> :: bigramCalculator()
{
	/* Constant basic variables */
	const int ONE = 1;
	
	
	for (int i=0; i<size-ONE; ++i)
	{
		if (!bigramSearch(data[i],data[i+ONE]))
			addElementBigram(data[i],data[i+1]);
		
		else
			increaseCount(data[i],data[i+ONE]);
	}
}



template <typename T>
bool BigramDyn<T> :: bigramSearch(const T& first, const T& second) const
{
	/* Constant basic variables */
	const int FIRST = 0;
	const int SECOND = 1;
	
	/* Needed function variables */
	bool retVal = false;
	
	
	for (int i=0; i<sizeBi; ++i)
		if ((bigrams[i][FIRST] == first) && (bigrams[i][SECOND] == second))
			retVal = true;
	
	return retVal;
}



template <typename T>
void BigramDyn<T> :: increaseCount(const T& first, const T& second)
{
	/* Constant basic variables */
	const int ONE = 1;
	const int FIRST = 0;
	const int SECOND = 1;
	
	/* Needed function variables */
	int index;
	
	
	for (int i=0; i<sizeBi; ++i)
		if ((bigrams[i][FIRST] == first) && (bigrams[i][SECOND] == second))
			index = i;
	
	counts[index] += ONE;
}

/* End of BigramDyn.cpp */
