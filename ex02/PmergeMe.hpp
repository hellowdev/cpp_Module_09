#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <cctype>

class PmergeMe
{
private:
	std::vector<int> vec;
	int odd;

	//********************* ALGO *********************//
	std::vector<std::pair<int, int>> fordJohnsonVec(std::vector<std::pair<int, int>> inp);
	unsigned int parseNumber(std::string in);
	void TrimStr(std::string& str);

	void pairing(std::vector<std::pair<int, int>>& newPairs, std::vector<std::pair<int, int>> oldPairs);
	// void group(std::vector<int> vect, std::vector<int>& winners);
    void firstPairs(std::vector<int> seq, std::vector<std::pair<int, int>>& fPairs);
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