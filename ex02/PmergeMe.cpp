#include "PmergeMe.hpp"

PmergeMe::PmergeMe(char **av)
{
	Element elemtents;
	for (int i = 1; av[i]; i++)
	{
		unsigned int nb = parseNumber(av[i]);
		elemtents = {nb}; // initlize our vector of struct element with vl and empty chain
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

void PmergeMe::pairing(std::vector<Element>& winners, std::vector<Element> elements) // 
{
	size_t size = elements.size();
	for (size_t i = 0; i < size; i += 2)
	{
		if (elements[i].value > elements[i + 1].value)
		{
			elements[i].chain.push_back(elements[i + 1]);
			winners.push_back(elements[i]);
		}
		else	
		{
			elements[i + 1].chain.push_back(elements[i]);
			winners.push_back(elements[i + 1]);
		}
	}
}

std::vector<Element> PmergeMe::fordJohnsonVec(std::vector<Element> elements)
{
	if (elements.size() == 1)
		return elements;

	odd = elements.size() % 2;
	Element stragler;
    bool hasStragler = false;
	if (odd)
    {
		stragler = elements.back();
        elements.pop_back();
        hasStragler = true;
    }
    std::vector<Element> winners;
	pairing(winners, elements); // Each winner now carries its loser in its chain!
	std::vector<Element> mainChain;
	mainChain = fordJohnsonVec(winners);
	std::vector<Element> pend;

	return winners;
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