#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <cctype>

struct Element
{
	unsigned int value;
	std::vector<Element> chain;
};

class PmergeMe
{
private:
	// std::vector<int> vec;
	std::vector<Element> vec;
	int odd;

	//********************* ALGO *********************//
	std::vector<Element> fordJohnsonVec(std::vector<Element> elements);
	unsigned int parseNumber(std::string in);
	void TrimStr(std::string& str);

	void pairing(std::vector<Element>& winners, std::vector<Element> oldPairs);
	// void group(std::vector<int> vect, std::vector<int>& winners);
	//****************** ORTHODOX ******************//
	PmergeMe();
	PmergeMe(const PmergeMe& old);
	PmergeMe& operator=(const PmergeMe& old);
public:
	PmergeMe(char **av);
	void sort();
	void printVec(std::vector<int>);
	~PmergeMe();

};