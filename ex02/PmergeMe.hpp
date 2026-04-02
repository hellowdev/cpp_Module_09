#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <deque>
#include <sstream>
#include <cctype>
#include <cstdlib>
#include <cerrno>
#include <iomanip>
#include <ctime>

struct ElementVec
{
	unsigned int value;
	std::vector<ElementVec> losers;
};
struct ElementDeq
{
	unsigned int value;
	std::vector<ElementDeq> losers;
};

class PmergeMe
{
	private:
		std::vector<ElementVec> vec;
		std::deque<ElementDeq> deq;
	
		//******************** PARSE ********************//
		unsigned int parseNumber(std::string in);
		void parse_str(std::string& str);
		//********************* ALGO VECTOR*********************//
		std::vector<ElementVec> fordJohnsonVec(std::vector<ElementVec> elements);
		void pairing(std::vector<ElementVec>& winners, std::vector<ElementVec> oldPairs);
		std::vector<int> generatejacobOrder(size_t pendSize);
		size_t jacob(size_t nb);
		void BinaryInsertionSearch(std::vector<int> jacobOrder, std::vector<ElementVec> pend, std::vector<ElementVec>& mainChain);
		void insertloser(ElementVec, std::vector<ElementVec>&, int, int);

		//********************* ALGO DEQUE*********************//
		std::deque<ElementDeq> fordJohnsonDeq(std::deque<ElementDeq> elements);
		void pairingDeq(std::deque<ElementDeq>& winners, std::deque<ElementDeq> oldPairs);
		std::deque<int> generatejacobOrderDeq(size_t pendSize);
		size_t jacobDeq(size_t nb);
		void BinaryInsertionSearchDeq(std::deque<int> jacobOrder, std::deque<ElementDeq> pend, std::deque<ElementDeq>& mainChain);
		void insertloserDeq(ElementDeq, std::deque<ElementDeq>&, int, int);
		//****************** ORTHODOX ******************//
		PmergeMe();
		PmergeMe(const PmergeMe& old);
		PmergeMe& operator=(const PmergeMe& old);
	public:
		PmergeMe(char **av);
		std::vector<ElementVec> sortVec();
		std::deque<ElementDeq> sortDeq();
		~PmergeMe();
};