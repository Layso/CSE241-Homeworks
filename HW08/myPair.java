/*
 * myPair.java is the implementation of myPair class
 * 
 * This is a copy of Java pair class to work on bigrams using maps
 *
 * This class is coded for the homework 8 of GTU's CSE241 lecture, Fall 2016
 * File belongs to Deniz Can Erdem Yılmaz - 151044001
 * 
 * Creation date   - Jan 07, 2017
 * Completion date - Jan 07, 2017
 * Dead-line       - Jan 07, 2017 - 23:55
 */
 
 
 
public class myPair<T>
{
	public T first;
	public T second;
	
	
	public String toString()
	{
		return ("<" + first + "," + second + ">");
	}
	
	public boolean equals(Object o)
	{
		return (first == ((myPair)o).first && second == ((myPair)o).second);
	}
	
	public int hashCode()
	{
		return 0;
	}
}
