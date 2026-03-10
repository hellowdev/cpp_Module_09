#include "PmergeMe.hpp"

PmergeMe::PmergeMe(char **av)
{
	for (int i = 1; av[i]; i++)
	{
		unsigned int nb = parseNumber(av[i]);
		vec.push_back(nb);
	}
}

void PmergeMe::TrimStr(std::string& str)
{
	size_t start = str.find_first_not_of(" \t\n\r\f\v");
	if (start == std::string::npos)
		throw std::runtime_error("Error: invalid input.");
	size_t end = str.find_last_not_of(" \t\n\r\f\v");
	str = str.substr(start, end - start + 1);
}

unsigned int PmergeMe::parseNumber(std::string in)
{
	if (in.empty() || in.find("0123456789 \t\r\v\n") != in.npos)
		throw std::runtime_error("Error: invalid input.");
	TrimStr(in); // remove spaces from begin and end of string
	char *end = NULL;
	long number = std::strtol(in.c_str(), &end, 10);
	if (*end || errno == ERANGE || number < 0 || number > INT_MAX)
		throw std::runtime_error("Error: invalid input.");
	return number;
}

void PmergeMe::printVec(std::vector<int> vect)
{
	for (size_t i = 0; i < vect.size(); i++)
		std::cout << vect[i] << " ";
	std::cout << "\n";
}


// void PmergeMe::group(std::vector<int> sequance, std::vector<int>& bigs, std::vector<int>& smalls)
// {
// 	size_t size = sequance.size();
	
// 	for (size_t i = 0; i < size; i++)
// 	{
		
// 	}
// }

void PmergeMe::pairing(std::vector<std::pair<int, int>>& newPairs, std::vector<std::pair<int, int>> oldPairs) // WHY REF??
{
    
    
	size_t size = oldPairs.size();
	// int j = 0;
	for (size_t i = 0; i < size; i += 2)
	{
		if (oldPairs[i].first > oldPairs[i + 1].first)
        {
            newPairs.push_back(std::make_pair(oldPairs[i].first, oldPairs[i + 1].first));
            // winners[j] = oldPairs[i];
        }
        else
        {
            newPairs.push_back(std::make_pair(oldPairs[i + 1].first, oldPairs[i].first));
            // winners[j] = seq[i + 1];
        }
	}
}
void PmergeMe::firstPairs(std::vector<int> seq, std::vector<std::pair<int, int>>& pairs)
{
    size_t size = seq.size();
	for (size_t i = 0; i < size; i += 2)
	{
		if (seq[i] > seq[i + 1])
            pairs.push_back(std::make_pair(seq[i], seq[i + 1])); // vector [pairs(winner, loser), so on..]
        else
            pairs.push_back(std::make_pair(seq[i + 1], seq[i])); // vector [pairs(winner, loser), so on..]
	}
}
std::vector<std::pair<int, int>> PmergeMe::fordJohnsonVec(std::vector<std::pair<int, int>> oldPairs)
{
	if (oldPairs.size() == 1)
		return oldPairs;

	odd = oldPairs.size() % 2;
	std::pair<int, int> stragler;
    bool hasStragler = false;
	if (odd)
    {
		stragler = oldPairs.back();
        oldPairs.pop_back();
        hasStragler = true;
    }
    std::vector<std::pair<int, int>> newPairs;
	pairing(newPairs, oldPairs);// pairing and grouping
	// group(pairs, winners);
	fordJohnsonVec(newPairs);
	std::vector<int> mainChain;
	
	return oldPairs;
}

void PmergeMe::sort()
{
    if (vec.size() == 1)
		return ;

	odd = vec.size() % 2;
	int stragler = 0;
    bool hasStragler = false;
	if (odd)
    {
		stragler = vec.back();
        vec.pop_back();
        hasStragler = true;
    }
	// std::vector<int> winners;
	// pairing(vec, winners); // pairing and grouping
    std::vector<std::pair<int, int>> pairs;
    firstPairs(vec, pairs);
	// group(vec, winners);
	fordJohnsonVec(pairs);
	std::vector<int> mainChain;

	fordJohnsonVec(pairs);
}

PmergeMe::~PmergeMe(){}