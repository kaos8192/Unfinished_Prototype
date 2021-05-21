#include "gates.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <variant>
#include <fstream>
using namespace std;

int main(int argc, char* argv[])
{
	ofstream myfile;
	myfile.open("example.txt"); //Inputs and Outputs are saved here.
	string i1; //First input string.
	string op; //Operator/Gate string
	string i2; //Second input string.
	string input; //THe entire line of input from user.
	bool invalid = false; //CHeck for if the input is invalid or not.

	//Boot-Up Help Information.
	cout << "Welcome to the Terminal!" << endl;
	cout << "Here, you can create your own logic maps." << endl;
	cout << "For general help, type \"HELP\"." << endl;
	cout << "To see valid inputs and gates, type \"INPUT\"." << endl;
	cout << "To learn and understand terms in this program, type \"GLOSSARY\"";
	cout << endl;
	cout << "To see how to correctly type logic, type \"SYNTAX\"." << endl;
	cout << "To end the program, type \"END\"." << endl;
	cout << "Only type the terms, and do not include the quotes." << endl;
	cout << endl << "What operation would you like to do?" << endl;
	cout << "--> ";

	while(getline(cin, input)) //While user input
	{
		/*
		 * End program if user types "END." Saves current written contents to
		 * myfile.
		*/
		if(input == "END")
		{
			break;
		}

		/*
		 * If the user types any of the following information, the program
		 * will print out helpful information for proper input types,
		 * syntax, and teach them terminology.
		*/
		if(input == "HELP")
		{
			helpText(4);
			continue;
		}
		if(input == "INPUT")
		{
			helpText(1);
			continue;
		}
		if(input == "GLOSSARY")
		{
			helpText(3);
			continue;
		}
		if(input == "SYNTAX")
		{
			helpText(2);
			continue;
		}

		vector<string> inputLine; //Parse input into vector of strings.
		istringstream iss(input);
		while(iss >> i1)
		{
			inputLine.push_back(i1);
		}
		/*
		 * Stores input based on its perceived type:
		 * If it's true or false, it will be stored as an int 1 or 0.
		 * If it's a gate name, it will be stored as a string.
		*/
		vector<variant<int, string>> typedLine;
		string il = "";
		for(int i = 0; i < inputLine.size(); i++) //For each parsed input.
		{
			il = inputLine[i];
			//If any of these, store as 1 (True).
			if(il == "true" || il == "True" || il == "TRUE")
			{
				typedLine.push_back(1);
			}
			//If any of these, store as 0 (False).
			else if (il == "false" || il == "False" || il == "FALSE")
			{
				typedLine.push_back(0);
			}
			//If any of these, store as string of itself.
			else if (il == "NOT" || il == "OR" || il == "AND" || il == "XOR" || il == "NOR" || il == "NAND" || il == "SPLIT")
			{
				typedLine.push_back(il);
			}
			/*
			 * Otherwise, check to see if the input is for the SPLIT command.
			 * If not, then throw the Invalid Argument error.
			*/
			else
			{
				//Check input if SPLIT was called.
				if(inputLine[i-2] == "SPLIT")
				{
					size_t t;
					int in;
					try //See if input can be converted to int.
					{
						in = stoi(il, &t);
					}
					//Throw error if unable to convert.
					catch(const std::invalid_argument& ia) 
					{
						cerr << "Failed to convert " << il << " into an int." << endl;
						invalid = true;
						break;
					}
					typedLine.push_back(in);
					continue;
				}
				cout << "Invalid argument. Please try again." << endl;
				cout << "Refer to either \"HELP\", \"INPUT\", or \"SYNTAX\" ";
				cout << "in case the input or syntax of" << endl;
				cout << "the argument is wrong." << endl;
				invalid = true;
				break;
			}
		}
		/*
		 * For every input in typedLine (-1, since the last input should
		 * never be a Gate.
		*/
		for(int i = 0; i < typedLine.size(); i++)
		{
			variant<int, string> o, z; //Possible input values
			o = 1;
			z = 0;
			/*
			if(typedLine[i] == o && (i == typedLine.size()-1 || i == 0))
			{
				myfile << "True ";
				cout << "True ";
			}
			else if (typedLine[i] == z && (i == typedLine.size()-1 || i == 0))
			{
				myfile << "False ";
				cout << "False ";
			}
			*/
			//If the argument is not 1 or 0 and the argument is valid.
			if((typedLine[i] != o || typedLine[i] != z) && invalid != true)
			{
				//Possible gates
				variant<int, string> n, a, r, xr, na, nr, s;
				n = "NOT";
				r = "OR";
				a = "AND";
				xr = "XOR";
				nr = "NOR";
				na = "NAND";
				s = "SPLIT";
				//input1 [gate] input2
				vector<variant<int, string>> input1, input2;
				input2.push_back(typedLine[i+1]);
				if(typedLine[i] == n) //If the argument is "NOT."
				{
					myfile << input << "\n";
					myfile << NOT(typedLine[i+1]) << "\n";
					cout << NOT(typedLine[i+1]) << " ";
				}
				else if(typedLine[i] == r) //If the argument is "OR."
				{
					input1.push_back(typedLine[i-1]);
					myfile << input << "\n";
					myfile << OR(input1, input2) << "\n";
					cout << OR(input1, input2) << " ";
					//cout << OR(typedLine[i-1], typedLine[i+1]) << " ";
				}
				else if(typedLine[i] == a) //If the argument is "AND."
				{
					input1.push_back(typedLine[i-1]);
					myfile << input << "\n";
					myfile << AND(input1, input2) << "\n";
					cout << AND(input1, input2) << " ";
					//cout << AND(typedLine[i-1], typedLine[i+1]) << " ";
				}
				else if(typedLine[i] == xr) //If the argument is "XOR."
				{
					input1.push_back(typedLine[i-1]);
					myfile << input << "\n";
					myfile << XOR(input1, input2) << "\n";
					cout << XOR(input1, input2) << " ";
					//cout << AND(typedLine[i-1], typedLine[i+1]) << " ";
				}
				else if(typedLine[i] == nr) //If the argument is "NOR."
				{
					input1.push_back(typedLine[i-1]);
					myfile << input << "\n";
					myfile << NOR(input1, input2) << "\n";
					cout << NOR(input1, input2) << " ";
					//cout << AND(typedLine[i-1], typedLine[i+1]) << " ";
				}
				else if(typedLine[i] == na) //If the argument is "NAND."
				{
					input1.push_back(typedLine[i-1]);
					myfile << input << "\n";
					myfile << NAND(input1, input2) << "\n";
					cout << NAND(input1, input2) << " ";
					//cout << AND(typedLine[i-1], typedLine[i+1]) << " ";
				}
				else if(typedLine[i] == s) //If the argument is "SPLIT."
				{
					myfile << input << "\n";
					vector<bool> out;
					int size = get<int>(typedLine[i+2]);
					out = SPLIT(typedLine[i+1], size);
					for(bool v : out)
					{
						myfile << v << " ";
						cout << v << " ";
					}
					myfile << "\n";
					//cout << AND(typedLine[i-1], typedLine[i+1]) << " ";
				}
			}
		}
		invalid = false;
		cout << endl;
		cout << endl << "What operation would you like to do?" << endl;
		cout << "--> ";
	}
	myfile.close();
}
