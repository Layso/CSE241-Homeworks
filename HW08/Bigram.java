/*
 * Bigram.java is the interface of Bigram class
 * 
 * This is the interface of Bigram class. It includes some functions to work on
 * bigrams. There will be 2 sub classes for the Bigram, one is BigramDyn and the
 * other is BigramMap. Function definitions given on homework definition
 *
 * This interface is coded for the homework 8 of GTU's CSE241 lecture, Fall 2016
 * File belongs to Deniz Can Erdem Yılmaz - 151044001
 * 
 * Creation date   - Jan 01, 2017
 * Completion date - Jan 07, 2017
 * Dead-line       - Jan 07, 2017 - 23:55
 */



public interface Bigram<T>
{
	/* Reads data from file and calculates bigrams */
	public void readFile(String fileName) throws Exception;

	/* Returns the total number of bigrams */	
	public int numGrams();

	/* Returns the number of bigrams for given pair */	
	public int numOfGrams(T first, T second);

	/* Overriding toString function */	
	public String toString();
}

