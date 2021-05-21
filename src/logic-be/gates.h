#ifndef _GATES_H_
#define _GATES_H_
#include <vector>
#include <iostream>
#include <variant>

/*
 * These functions now use Variants. For more info on Variants,
 * check out the RESOURCES.txt file.
*/

//Stream struct, for making variants work.
template<class T>
struct strm
{
	const T& val;
};

//Used for the "HELP" line of commands. Prints information if users need it.
void helpText(int arg);

/*
 * NOT Gate.
 * Returns true or false depending on if variant i is a 0 or 1, respectively.
*/
bool NOT(std::variant<int, std::string> i);

/*
 * OR Gate.
 * Compares all variants to the left and right of the OR, and returns
 * true if at least one of them is true. 
 * Returns false if none of them are true.
*/
bool OR(std::vector<std::variant<int, std::string>> i1, std::vector<std::variant<int, std::string>> i2);

/*
 * AND Gate.
 * Compared all variants to the left and right of the AND, and returns
 * true if ALL of them are true. 
 * Returns false if at least one of them are false.
*/
bool AND(std::vector<std::variant<int, std::string>> i1, std::vector<std::variant<int, std::string>> i2);

/*
 * XOR Gate.
 * Compares all variants to the left and right of the XOR, and returns
 * true if the number of true inputs is odd.
 * Returns false if the number of true inputs are even.
*/
bool XOR(std::vector<std::variant<int, std::string>> i1, std::vector<std::variant<int, std::string>> i2);

/* 
 * NOR Gate.
 * Return the opposite of the return of an OR operation.
*/
bool NOR(std::vector<std::variant<int, std::string>> i1, std::vector<std::variant<int, std::string>> i2);

/*
 * NAND Gate.
 * Return the opposite of the return of an AND operation.
*/
bool NAND(std::vector<std::variant<int, std::string>> i1, std::vector<std::variant<int, std::string>> i2);

/*
 * SPLIT Gate
 * Return a vector of the given size with copies of the given variant.
*/
std::vector<bool> SPLIT(std::variant<int, std::string> in, int size);

//Compare vectors, for testing.
bool operator== (const std::vector<bool>& a, const std::vector<bool>& b);

//Operator for testing SPLIT Gates.
std::ostream& operator<< (std::ostream& out, const std::vector<bool>& vals);

//Operators for printing variant types.

template<class T> strm(T) -> strm<T>;
template<class T>
std::ostream& operator<< (std::ostream& os, strm<T> s)
{
	os << s.val;
	return os;
}

template<class... Ts>
std::ostream& operator<< (std::ostream& os, strm<std::variant<Ts...>> vs)
{
	std::visit([&os](const auto& v) { os << strm{v}; }, vs.val); 
	return os;
}

#endif
