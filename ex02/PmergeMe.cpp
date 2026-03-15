#include "PmergeMe.hpp"

PmergeMe::PmergeMe(char **av)
{
	Element elemtents;
	for (int i = 1; av[i]; i++)
	{
		unsigned int nb = parseNumber(av[i]);
		elemtents = {nb};
		vec.push_back(elemtents);
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
	if (*end || errno == ERANGE || number < 0 || number > INT32_MAX)
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


void PmergeMe::sort()
{
    if (vec.size() == 1)
		return ;
	
	odd = vec.size() % 2;
	Element stragler;
  	bool hasStragler = false;
	if (odd)
    {
		stragler = vec.back();
        vec.pop_back();
        hasStragler = true;
    }
	
	fordJohnsonVec(vec);
	std::vector<int> mainChain;
}

PmergeMe::~PmergeMe(){}