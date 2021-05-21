#include "gates.h"
#include <vector>
#include <iostream>
#include <variant>

//The o variant is for 1, while the z variant is for 0. (True & False)
std::variant<int, std::string> o, z;

//Prints out helpful information based on the command the user inputs.
void helpText(int arg)
{
	if(arg == 1 || arg == 4) //"HELP" or "INPUT" was typed.
	{
		std::cout << "Valid input arguments:" << std::endl;
		std::cout << "  true, True, TRUE" << std::endl;
		std::cout << "  false, False, FALSE" << std::endl;
		std::cout << "Valid gate arguments:" << std::endl;
		std::cout << "  NOT, OR, AND, XOR, NOR, NAND, SPLIT" << std::endl;
	}
	if(arg == 2 || arg == 4) //"HELP" or "SYNTAX" was typed.
	{
		std::cout << "To return an input argument, just type that argument by";
		std::cout << " itself." << std::endl;
		std::cout << "  true => 1" << std::endl;
		std::cout << "  True => 1" << std::endl;
		std::cout << "  FALSE => 0" << std::endl << std::endl;
		std::cout << "To run a NOT Gate:" << std::endl;
		std::cout << "  NOT [input]" << std::endl << std::endl;
		std::cout << "To run a SPLIT gate:" << std::endl;
		std::cout << "  SPLIT [input] [number of outputs]" << std::endl; 
		std::cout << std::endl;
		std::cout << "To run a different gate:" << std::endl;
		std::cout << "  [input1] [GATE] [input2]" << std::endl << std::endl;
	}
	if(arg == 3 || arg == 4) //"HELP" or "GLOSSARY" was typed.
	{
		std::cout << "Terminology:" << std::endl;
		std::cout << "  NOT: Returns the opposite of the given input."; 
		std::cout << std::endl;
		std::cout << "    NOT true => false" << std::endl << std::endl;
		std::cout << "  OR: Returns true if either input is true, otherwise, ";
		std::cout << "it returns false." << std::endl;
		std::cout << "        true OR false => true" << std::endl;
		std::cout << "        false OR false => false" << std::endl;
		std::cout << std::endl;
		std::cout << "  AND: Returns true if both inputs are true, otherwise, ";
		std::cout << "it returns false." << std::endl;
		std::cout << "        true AND true => true" << std::endl;
		std::cout << "        true AND false => false" << std::endl;
		std::cout << std::endl;
		std::cout << "  XOR: Returns true if the inputs do not match, ";
		std::cout << "otherwise, it returns false." << std::endl;
		std::cout << "        true XOR false => true" << std::endl;
		std::cout << "        true XOR true => false" << std::endl << std::endl;
		std::cout << "  NOR: Returns the opposite of the OR operation on both ";
		std::cout << "inputs." << std::endl;
		std::cout << "        true NOR true => false" << std::endl;
		std::cout << "        false NOR false => true" << std::endl;
		std::cout << std::endl;
		std::cout << "  NAND: Returns the opposite of the AND operation on ";
		std::cout << "both inputs." << std::endl;
		std::cout << "        true NAND false => true" << std::endl;
		std::cout << "        true NAND true => false" << std::endl;
		std::cout << "  SPLIT: Returns the given input in the same given ";
		std::cout << "amount." << std::endl;
		std::cout << "        SPLIT true 3 => true true true" << std::endl;
		std::cout << "        SPLIT false 2 => false false" << std::endl;
	}
	if(arg == 4) //"HELP" was typed.
	{
		std::cout << "To end the program, be sure to type \"END\".";
		std::cout << std::endl;
	}
	std::cout << std::endl << "What operation would you like to do?";
    std::cout << std::endl << "--> ";

}

//Returns true or false depending on if variant i is a 0 or 1, respectively.
bool NOT(std::variant<int, std::string> i)
{
	o = 1;
	z = 0;
	if(i == o || i == z) //Makes sure i is either 1 or 0, exits if invalid.
	{
		if(i == o) //Return false if variant i is 1, or true if 0.
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	else
	{
		std::cout << "invalid input." << std::endl;
		exit(-1);
	}
}

/*
 * Compares all variants to the left and right of the OR, and returns
 * true if at least one of them is true. 
 * Returns false if none of them are true.
 */
bool OR(std::vector<std::variant<int, std::string>> i1, std::vector<std::variant<int, std::string>> i2)
{
	o = 1; //Set o to 1.
	z = 0; //Set z to 0.
	for(int i = 0; i < i1.size(); i++) //For each variant in the vector i1.
	{
		//Makes sure the current element in i1 is valid -- either 1 or 0.
		if(i1[i] == o || i1[i] == z)
		{
			//Return true if the element is 1. Otherwise, continue.
			if(i1[i] == o)
			{
				return true;
			}
			//For each variant in the vector i2.
			for(int j = 0; j < i2.size(); j++)
			{
				//Makes sure the current element in i2 is valid -- 1 or 0.
				if(i2[i] == o || i2[i] == z)
				{
					//Return true if the element is 1. Otherwise, continue.
					if(i2[j] == o)
					{
						return true;
					}
				}
			}
		}
	}
	return false; //Otherwise, return false.
}

/*
 * Compares all variants to the left and right of the AND, and returns
 * true if ALL of them are true. 
 * Returns false if at least one of them are false.
 */
bool AND(std::vector<std::variant<int, std::string>> i1, std::vector<std::variant<int, std::string>> i2)
{
	o = 1; //Set o to 1.
	z = 0; //Set z to 0.
	int all = i1.size() + i2.size(); //The combined size of both vectors.
	int count = 0; //Counts true variants in vectors.
	for(int i = 0; i < i1.size(); i++) //For each variant in the vector i1.
	{
		/*
		 * Adds 1 to the count if the current element if true.
		 * Otherwise, continue.
		 */
		if(i1[i] == o)
		{
			count++;
		}
		for(int j = 0; j < i2.size(); j++) //For each variant in the vector i2.
		{
			/*
			 * Adds 1 to the count if the current element if true.
			 * Otherwise, continue.
			 */
			if(i2[j] == o)
			{
				count++;
			}
		}
	}
	/*
	 * If the count of trues is equal to the total, return true.
	 * Otherwise, return false.
	 */
	if(count == all)
	{
		return true;
	}
	else
	{
		return false;
	}
}

/*
 * Compares all variants to the left and right of the XOR, and returns
 * true if the number of true inputs is odd. 
 * Returns false if the number of true inputs are even.
 */
bool XOR(std::vector<std::variant<int, std::string>> i1, std::vector<std::variant<int, std::string>> i2)
{
	o = 1; //Set o to 1.
	z = 0; //Set z to 1.
	int count = 0; //Counts true variants in vectors.
	for(int i = 0; i < i1.size(); i++) //For each variant in vector i1.
	{
		/*
		 * Adds 1 to the count if the current element if true.
		 * Otherwise, continue.
		 */
		if(i1[i] == o)
		{
			count++;
		}
		for(int j = 0; j < i2.size(); j++) //For each variant in vector i2.
		{
			/*
			 * Adds 1 to the count if the current element if true.
			 * Otherwise, continue.
			 */
			if(i2[j] == o)
			{
				count++;
			}
		}
	}
	/*
	 * Return true if the count modulo 2 equals 1 (meaning it is odd).
	 * Otherwise, return false.
	 */
	if(count % 2 == 1)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//Return the opposite of the return of an OR operation.
bool NOR(std::vector<std::variant<int, std::string>> i1, std::vector<std::variant<int, std::string>> i2)
{
	std::variant<int, std::string> o = OR(i1, i2);
	return NOT(o);
}

//Return the opposite of the return of an AND operation.
bool NAND(std::vector<std::variant<int, std::string>> i1, std::vector<std::variant<int, std::string>> i2)
{
	std::variant<int, std::string> o = AND(i1, i2);
	return NOT(o);
}

//Return a vector of the given size with copies of the given variant.
std::vector<bool> SPLIT(std::variant<int, std::string> in, int size)
{
	o = 1; //Set o to 1.
	z = 0; //Set z to 1.
	std::vector<bool> output; //Output vector.
	//Push back the vector for the given size number.
	for(int i = 0; i < size; i++) 
	{
		if(in == o)
		{
			output.push_back(1);
		}
		else
		{
			output.push_back(0);
		}
	}
	return output;
}
