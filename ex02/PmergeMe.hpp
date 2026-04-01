#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <cctype>
#include <cstdlib>
#include <cerrno>
#include <iomanip>
#include <ctime>
#include <unistd.h>
struct Element
{
	unsigned int value;
	std::vector<Element> losers;
};

class PmergeMe
{
	private:
		std::vector<Element> vec;
	
		void printVec(std::vector<int> vect);
		//******************** PARSE ********************//
		unsigned int parseNumber(std::string in);
		void parse_str(std::string& str);
		//********************* ALGO *********************//
		std::vector<Element> fordJohnsonVec(std::vector<Element> elements);
		void pairing(std::vector<Element>& winners, std::vector<Element> oldPairs);
		std::vector<int> generatejacobOrder(size_t pendSize);
		size_t jacob(size_t nb);
		void BinaryInsertionSearch(std::vector<int> jacobOrder, std::vector<Element> pend, std::vector<Element>& mainChain);
		void insertloser(Element, std::vector<Element>&, int, int);
		//****************** ORTHODOX ******************//
		PmergeMe();
		PmergeMe(const PmergeMe& old);
		PmergeMe& operator=(const PmergeMe& old);
	public:
		PmergeMe(char **av);
		std::vector<Element> sort();
		~PmergeMe();
};