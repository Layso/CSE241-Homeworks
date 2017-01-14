/*
 * BigramMap.cpp
 * Contains BigramMap function implementations
 * 
 * This will be a class derivated from Bigram base class to work on bigrams.
 * BigramMap will use STL for the datas it will contain
 *
 * This class coded for the homework 7 of GTU's CSE241 lecture, Fall 2016
 * File belongs to Deniz Can Erdem Yılmaz - 151044001
 * 
 * Creation date   - 26.12.2016
 * Completion date - 30.12.2016
 * Dead-line       - 30.12.2016 / 00:00
 */

/* Include(s) */
#include <iostream>
#include <fstream>
#include "BigramMap.h"
#include "Exceptions.h"

/* Using Statement(s) */
using std::cout;
using std::endl;
using std::ifstream;
using std::ostream;
using namespace cen;



/* Function Implementation(s) */
template <typename T>
BigramMap<T> :: BigramMap()
{
	throw ERROR(INITIALIZE_ERROR);
}



template <typename T>
BigramMap<T> :: BigramMap(int type) : dataType(type), gram(2), fileName("")
{
	/* Checking data tyoe error */
	switch (type)
	{
		case 1:
		case 2:
		case 3: break;
		default: throw ERROR(DATA_TYPE_ERROR);
	}
}



template <typename T>
void BigramMap<T> :: readFile(const string inputFile) /*EXCEPTION, WRONG INPUT TYPE */
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
	
	/* Reading data to vector */
	while (file>>input)
		data.push_back(input);
	
	/* Checking if any bad data has found */
	if (!file.eof())
		throw ERROR(FILE_INPUT_ERROR);
	
	/* Checking if there is an error after reading file */
	if (data.size() < gram)
		throw ERROR(FEW_INPUT_ERROR);
	
	
	file.close();
	bigramCalculator();
}



template <typename T>
int BigramMap<T> :: numGrams() const
{
	/* Constant basic variables */
	const int ZERO = 0;
	
	/* Data variables for function */
	int count = ZERO;
	typename map <pair <T,T>, int> :: const_iterator it;
	//Using constant iterator to surf on map due to const function
	
	
	/* Checking for errors */
	if (bigrams.size() == ZERO)
		throw ERROR(NO_DATA_ERROR);
	
		
	/* Counting all bigrams */
	for (it=bigrams.begin(); it!=bigrams.end(); ++it)
		count += it->second;
	
	
	return count;
}



template <typename T>
int BigramMap<T> :: numOfGrams(const T& first, const T& second) const
{
	/* Constant basic variables */
	const int ZERO = 0;
	
	/* Data variables for function */
	pair <T,T> newPair;
	int count = ZERO;
	
	
	/* Checking for errors */
	if (bigrams.size() == ZERO)
		throw ERROR(NO_DATA_ERROR);
	
	
	newPair.first = first;
	newPair.second = second;
	
	/* Searching for the given pair in bigrams. Returns 0 if not found */
	if (bigramSearch(first, second))
		count = bigrams.at(newPair);
	
	
	return count;
}



template <typename T>
pair<T,T> BigramMap<T> :: maxGrams() const
{
	/* Constant basic variables */
	const int ZERO = 0;
	
	/* Needed variables for function */
	int max = ZERO;
	pair <T,T> newPair;
	typename map <pair <T,T>, int> :: const_iterator it;
	//Using constant iterator to surf on map due to const function


	/* Checking for errors */
	if (bigrams.size() == ZERO)
		throw ERROR(NO_DATA_ERROR);
		
	
	for (it=bigrams.begin(); it!=bigrams.end(); ++it)
		if (it->second > max)
		{
			newPair = it->first;	
			max = it->second;
		}
	
	
	return newPair;
}



template <typename T>
void BigramMap<T> :: toString(ostream& out) const
{
	/* Constant basic variables */
	const int ZERO = 0;
	const int ONE = 1;
	const int FIRST = 0;
	const int SECOND = 1;
	const int VALID = -1;
	
	/* Needed variables for function */ 
	vector <int> sort;
	int count;
	vector <pair <T,T>> pairs;
	vector <int> counts;
	typename map <pair <T,T>, int> :: const_iterator it;
	
	
	/* Checking for errors */
	if (bigrams.size() == ZERO)
		throw ERROR(NO_DATA_ERROR);
		
	
	/* Initializing valid index spaces in number of bigrams */
	for (int i=0; i<bigrams.size(); ++i)
		sort.push_back(VALID);
	
	/* Taking bigrams and their counts to vectors to print them sorted */
	for (it=bigrams.begin(); it!=bigrams.end(); ++it)
	{
		pairs.push_back(it->first);
		counts.push_back(it->second);
	}
	
	/* Counting how many elements are there larger than selected element for */
	/* each element of counts array to sort them */
	for (int i=ZERO; i<bigrams.size(); ++i)
	{
		int index = ZERO;
		
		for (int k=ZERO; k<bigrams.size(); ++k)
			if (counts[i] < counts[k])
				++index;
		
		/* If there are equal counts then they will show same index. To */
		/* prevent the misplaces, increasing index until a valid one found */
		while (sort[index] != VALID)
			++index;
		
		sort[index] = i;
	}
	
	
	/* Printing bigrams from bigger to lesser */
	for (int i=ZERO; i<bigrams.size(); ++i)
		out << "Pair: [" << pairs[sort[i]].first << "," 
			<< pairs[sort[i]].second << "]    Count: "
			<< counts[sort[i]] << endl;
}



template <typename T>
void BigramMap<T> :: bigramCalculator()
{
	/* Constant basic variables */
	const int ZERO = 0;
	const int ONE = 1;
	
	
	for (int i=ZERO; i<data.size()-ONE; ++i)
	{
		/* Checking each data member to see if there is a map key on data */
		/* Adding new key-value to bigrams if it is a new pair */
		/* Increasing the value if it is not new */
		if (!bigramSearch(data[i],data[i+ONE]))
			addElement(data[i],data[i+ONE]);
		
		else
			increaseCount(data[i],data[i+ONE]);
	}
}



template <typename T>
bool BigramMap<T> :: bigramSearch(const T& first, const T& second) const
{
	/* Needed function variables */
	bool retVal = false;
	pair <T,T> newPair;	
	typename map <pair <T,T>, int> :: const_iterator it;
	//Using constant iterator to surf on map due to const function
	
	
	/* Preparing pair variable to compare */
	newPair.first = first;
	newPair.second = second;
	
	/* Looking through each pair until the end of map */
	for (it=bigrams.begin(); it!=bigrams.end(); ++it)
		/* If a match has found, change the return value */
		if (it->first == newPair)
			retVal = !retVal;


	return retVal;
}



template <typename T>
void BigramMap<T> :: addElement(const T& first, const T& second)
{
	/* Constant basic variables */
	const int NEW_COUNT = 1;
	
	/* Needed variables for function */
	pair <T,T> newPair;
	
	
	/* Creating element to bigrams map with new pair */
	newPair.first = first;
	newPair.second = second;
	bigrams[newPair] = NEW_COUNT;
}



template <typename T>
void BigramMap<T> :: increaseCount(const T& first, const T& second)
{
	/* Constant basic variables */
	const int ONE = 1;
	
	/* Needed variables for function */
	pair <T,T> newPair;
	
	
	/* Increasing value of given key pair */
	newPair.first = first;
	newPair.second = second;
	bigrams[newPair] += ONE;
}

/* End of BigramMap.cpp */
