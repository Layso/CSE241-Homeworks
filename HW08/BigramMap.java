/*
 * BigramMap.java is the implementation of BigramMap class
 * 
 * This is one of the sub classes of the interface Bigram. It uses Map for the
 * implementation and datas. Function definitions given on homework definition
 *
 * This class is coded for the homework 8 of GTU's CSE241 lecture, Fall 2016
 * File belongs to Deniz Can Erdem Yılmaz - 151044001
 * 
 * Creation date   - Jan 01, 2017
 * Completion date - Jan 07, 2017
 * Dead-line       - Jan 07, 2017 - 23:55
 */



/* Import(s) */
import java.util.Scanner;
import java.util.HashMap;
import java.util.Map;
import java.io.File;
import java.io.FileNotFoundException;
import java.util.InputMismatchException;



/* Class Definition */
public class BigramMap<T> implements Bigram<T>
{
	private Object[] datas;
	private int dataType;
	private int dataSize;
	private Map<myPair<Object>, Integer> bigrams;
	final private int INTEGER;
	final private int DOUBLE;
	final private int STRING;
	
	
	BigramMap()
	{
		INTEGER = 1;
		STRING = 2;
		DOUBLE = 3;
		System.out.println("Exception: Misuse of constructor"); /* CONVERT TO EXCEPTION */
		System.exit(1);
	}
	
	BigramMap(int type)
	{
		switch (type)
		{
			case 1:
			case 2:
			case 3:	dataType = type; break;
			default: System.out.println("Exception: Undefined data type"); /* CONVERT TO EXCEPTION */
					 System.exit(1);
		}
		
		bigrams = new HashMap<>();
		datas = null;
		dataSize = 0;
		INTEGER = 1;
		STRING = 2;
		DOUBLE = 3;
	}
	
	public void readFile(String fileName) throws Exception
	{
		T inp;
		int dataInt, size = 0;
		double dataDbl;
		String dataStr;
		File inputFile = new File(fileName);
		Scanner input = new Scanner(inputFile);
		
		
		/* Checking for the file error */
		if (!inputFile.exists())
		{
			System.out.println("Exception: File not found"); /* CONVERT TO EXCEPTION */
			System.exit(1);
		}
		
		
		/* Finding data count */
		while (input.hasNext())
		{
			input.next();
			++size;
		}
		

		datas = (T[]) new Object[size];
		
		
		/* Reopening file to take datas */
		input.close();
		input = new Scanner(inputFile);
		
		while (input.hasNext())
		{
			/* Checking input type error */
			try
			{
				/* Taking input data and adding to datas array */
				if (dataType == INTEGER)
				{
					dataInt = input.nextInt();
					addElement(dataInt);
				}
				
				else if (dataType == STRING)
				{
					dataStr = input.next();
					addElement(dataStr);
				}
				
				else if (dataType == DOUBLE)
				{
					dataDbl = input.nextDouble();
					addElement(dataDbl);
				}
			}
			catch (InputMismatchException e)
			{
				System.out.println("Exception: Input mismatch occured"); /* CONVERT TO EXCEPTION */
				System.exit(1);
			}
		}
		
		if (dataSize < 2)
		{
			System.out.println("Exception: Not enough data"); /* CONVERT TO EXCEPTION */
			System.exit(1);
		}
		
		bigramCalculator();
		input.close();		
	}
	
	public int numGrams()
	{
		if (dataSize < 2)
		{
			System.out.println("Exception: Not enough data"); /* CONVERT TO EXCEPTION */
			System.exit(1);
		}
		
		return dataSize-1;
	}
	
	public int numOfGrams(T first, T second)
	{
		int number = 0;
		
		
		if (dataSize < 2)
		{
			System.out.println("Exception: Not enough data"); /* CONVERT TO EXCEPTION */
			System.exit(1);
		}
		
		
		myPair<Object> newPair;
		newPair = new myPair<>();
		
		newPair.first = first;
		newPair.second = second;
		
		if (bigrams.get(newPair) != null)
			number = (int) bigrams.get(newPair);
		
		return number;
	}
	
	public String toString()
	{
		return "toString()";
	}
	
	private <T> void addElement(T newData)
	{
		datas[dataSize] = newData;
		++dataSize;
	}
	
	private void bigramCalculator()
	{
		for (int i=0; i<dataSize-1; ++i)
		{
			myPair<Object> newPair;
			newPair = new myPair<>();
			
			newPair.first = datas[i];
			newPair.second = datas[i+1];
			
			
			if (bigrams.containsKey(newPair))
			{
				int count = (int) bigrams.get(newPair);
				bigrams.put(newPair, count+1);
			}
			
			else
				bigrams.put(newPair, 1);
		}
	}
}
